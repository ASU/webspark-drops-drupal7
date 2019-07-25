<?php

/**
 * Helper functions
 * Get state names and IDs for RFI form dropdowns
 */
function _asu_rfi_get_state_names($installing = FALSE) {
  // JSON configs
  $type = 'fieldinfo';
  $name = 'state_province';
  $middleware_host = 'webforms.asu.edu';
  $url = "https://$middleware_host/salesforce_query/api/$type/$name";
  $db_tbl = 'asu_rfi_states_list';

  // Clean out DB table if initial install
  if ($installing) {
    db_truncate($db_tbl)->execute();
  }

  // Do CURL call to JSON feed
  try {
    $ch = curl_init();
    $options = array(
      CURLOPT_URL => $url,
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
      'Curl call to get states list from ' . $url . ' failed with error #%d: %s',
      $e->getCode(), $e->getMessage()),
      E_USER_ERROR);
  }

  // Do DB upsert if values are returned from JSON feed...
  if (count($result)) {
    foreach ($result as $state) {
      $value = (!empty($state->value)) ? check_plain($state->value) : 'EMPTY';
      $label = (!empty($state->label)) ? check_plain($state->label) : 'EMPTY';
      if ($value !== 'EMPTY' || $label !== 'EMPTY') {
        db_merge($db_tbl)
          ->key(array('stateCode' => $value))
          ->fields(array(
            'stateCode' => $value,
            'stateDesc' => $label,
          ))
          ->execute();
        $message = $label . ' with state ID ' . $value . ' inserted into (or updated in) ' . $db_tbl . '.';
        watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
      }
      else {
        $message = t('State value returned from ' . $url . ' were rejected: value - :key, label - :name ',
          array(':key' => $value, ':name' => $value,));
        watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
      }
    }
  }

  // Or error out if no states are in list...
  else {
    $status = 'warning';
    $wd_status = WATCHDOG_WARNING;
    $message = 'No states for RFI forms could be pulled from ' . $url .
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