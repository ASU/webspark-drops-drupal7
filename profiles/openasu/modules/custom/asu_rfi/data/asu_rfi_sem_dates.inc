<?php

/**
 * Helper function
 * Set up semester dates for RFI form dropdown
 */
function _asu_rfi_get_sem_dates($installing = FALSE) {
  // JSON configs
  $type = 'select';
  $name = 'rfi_dedupe_list_terms';
  $middleware_host = "webforms.asu.edu";
  $url = "https://$middleware_host/salesforce_query/api/$type/$name";
  $db_tbl = 'asu_rfi_sem_dates';

  $fields = array(
    'condition_Term_Status__c' => TRUE,
  );
  $body = json_encode($fields);

  // Clean out DB table if initial install
  if ($installing) {
    db_truncate($db_tbl)->execute();
  }

  // Make CURL call
  try {
    $ch = curl_init();
    $options = array(
      CURLOPT_URL => $url,
      CURLOPT_POST => 1,
      CURLOPT_POSTFIELDS => $body,
      CURLOPT_RETURNTRANSFER => 1,
      CURLOPT_HTTPHEADER => _asu_rfi_get_curl_auth(),
    );
    curl_setopt_array($ch, $options);
    $response = curl_exec($ch);
    $result = json_decode($response);
    curl_close($ch);

    if (FALSE === $response) {
      throw new Exception(curl_error($ch), curl_errno($ch));
    }
  } catch (Exception $e) {
    trigger_error(sprintf(
      'Curl call to get semester dates from ' . $url . ' failed with error #%d: %s',
      $e->getCode(), $e->getMessage()),
      E_USER_ERROR);
  }

  // Do DB upsert if values are returned from JSON feed...
  if (count($result)) {
    foreach ($result as $semester) {
      $id = (!empty($semester->Id)) ? check_plain($semester->Id) : 'NA';
      $name = (!empty($semester->Name)) ? check_plain($semester->Name) : 'NA';
      if ($id !== 'NA' && $name !== 'NA') {
        db_merge($db_tbl)
          ->key(array('semId' => $id))
          ->fields(array(
            'semId' => $id,
            'semLabel' => $name,
          ))
          ->execute();
        $message = $name . ' with key ID ' . $id . ' inserted into (or updated in ) ' . $db_tbl . ' options list.';
        watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
      }
      else {
        $message = t('Semester ID or name returned from JSON feed at ' . $url . ' were rejected: ID - :id, Name - :name ',
          array(':id' => $id, ':name' => $name));
        watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
      }
    }
  }

  // Or error out if no semester values...
  else {
    $status = 'warning';
    $wd_status = WATCHDOG_WARNING;
    $message = 'No semester IDs/names for RFI forms could be pulled from ' . $url .
      ' to insert into ' . $db_tbl . '. Check your existing RFI forms to see if they still have all expected semester date options.' .
      ' If it does not, please contact webconsulting@asu.edu for assistance.';

    // Check to see if any option entries (valid or not) still exist in the table from past pulls.
    if (_asu_rfi_check_form_values($db_tbl) === 0 ) {
      $message .= ' The RFI form will not function properly until this issue has been resolved.';
      $status = 'error';
      $wd_status = WATCHDOG_ERROR;
    }
    drupal_set_message($message, $status);
    watchdog('asu_rfi', $message, array(), $wd_status);
  }

}