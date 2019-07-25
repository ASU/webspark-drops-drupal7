<?php

/**
 * Helper functions
 * Get state names and IDs for RFI form dropdowns
 */
function _asu_rfi_get_countries_data($installing = FALSE) {
  // JSON configs
  $type = 'fieldinfo';
  $name = 'country';
  $middleware_host = "webforms.asu.edu";
  $url = "https://$middleware_host/salesforce_query/api/$type/$name";
  $db_tbl = 'asu_rfi_countries';

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
      'Curl call to get country info from ' . $url . ' failed with error #%d: %s',
      $e->getCode(), $e->getMessage()),
      E_USER_ERROR);
  }

  // Do DB upsert if values are returned from JSON feed...
  if (count($result)) {
    foreach ($result as $country) {
      $code = (!empty($country->value)) ? check_plain($country->value) : 'EMPTY';
      $desc = (!empty($country->label)) ? check_plain($country->label) : 'EMPTY';
      if (!($code === 'EMPTY') && !($desc === 'EMPTY')) {
        db_merge($db_tbl)
          ->key(array('countryCode3' => $code))
          ->fields(array(
            'countryCode3' => $code,
            'countryDesc' => $desc,
          ))
          ->execute();
        $message = $desc . ' with country code ' . $code . ' inserted into (or updated in ) ' . $db_tbl . ' options list.';
        watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
      }
      else {
        $message = t('Country code or description returned from ' . $url . ' were rejected: Code - :code, Desc - :desc ',
          array(':code' => $code, ':desc' => $desc));
        watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
      }
    }
  }

  // Or error out if no country values.
  else {
    $status = 'warning';
    $wd_status = WATCHDOG_WARNING;
    $message = 'No country codes for RFI forms could be pulled from ' . $url .
      ' to insert into ' . $db_tbl . '. Check your existing RFI forms to see if they still have all expected country code options.' .
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