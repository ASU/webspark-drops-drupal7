<?php

/**
 * Helper functions
 * Get list names and IDs for various RFI form dropdowns
 * @param $name - (str) Which dataset to pull (state_province, country, rfi_dedupe_list_terms (aka sem_dates))
 * @param $installing - (bool) Module installing for the first time (TRUE)
 *   or just running via cron (FALSE).
 */
function asu_rfi_get_options_data($name, $installing = FALSE) {

  // Get configs
  $config = (array) _asu_rfi_get_data_configs($name);
  $url = $config['url'];
  $db_tbl = $config['db_tbl'];
  $json_options = $config['json_options'];

  // Do CURL call to JSON feed
  try {
    $ch = curl_init();
    curl_setopt_array($ch, $json_options);
    $response = curl_exec($ch);
    $result = json_decode($response);
    curl_close($ch);

    if (FALSE === $response) {
      throw new Exception(curl_error($ch), curl_errno($ch));
    }
  } catch (Exception $e) {
    trigger_error(sprintf(
      'Curl call to get ' . $name . ' from ' . $url . ' failed with error #%d: %s',
      $e->getCode(), $e->getMessage()),
      E_USER_ERROR);
  }

  // Do DB upsert if values are returned from JSON feed...
  if (count($result)) {
    $cntry_cnt = 0;
    foreach ($result as $datum) {
      $datum_key = (!empty($datum->{$config['datum_key']})) ? check_plain($datum->{$config['datum_key']}) : 'EMPTY';
      $datum_value = (!empty($datum->{$config['datum_value']})) ? check_plain($datum->{$config['datum_value']}) : 'EMPTY';
      $db_key = $config['db_key'];
      $db_value = $config['db_value'];
      if ($datum_key !== 'EMPTY' || $datum_value !== 'EMPTY') {
        db_merge($db_tbl)
          ->key(array($db_key => $datum_key))
          ->fields(array(
            $db_key => $datum_key,
            $db_value => $datum_value,
          ))
          ->execute();
        $cntry_cnt++;
      }
      else {
        $message = t($name . ' record from ' . $url . ' was rejected. Debugging info: key - :key, value - :name ',
          array(':key' => $datum_key, ':name' => $datum_value,));
        watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
      }
    }
    if ($cntry_cnt > 0) {
      $message = $cntry_cnt . ' out of ' . count($result) . ' ' . $name . ' entries were
        upserted in ' . $db_tbl . ' DB table.';
      watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
    } else { // no $result entries got in
      watchdog('asu_rfi', 'None of the ' . count($result) . ' ' . $name . ' entries were
        added to the ' . $db_tbl . ' DB table.');
    }
  }

  // Or error out if no data is in list...
  else {
    $status = 'warning';
    $wd_status = WATCHDOG_WARNING;
    $message = 'No ' . $name . ' for RFI forms were pulled from ' . $url .
      ' to insert into ' . $db_tbl . '. Check your existing RFI forms to see if they still have all expected ' . $name . ' options.' .
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

/**
 * Helper function
 * Stores configs for all three types
 * @param $dataset - Which dataset to pull (states, country, semester dates, etc.)
 * @return $config - Array of configurations
 */
function _asu_rfi_get_data_configs($dataset) {
  $config = array();
  if ($dataset == 'state_province') {
    $config = array(
      'type' => 'fieldinfo',
      'name' => 'state_province',
      'db_tbl' => 'asu_rfi_states_list',
      'db_key' => 'stateCode',
      'db_value' => 'stateDesc',
      'datum_key' => 'value',
      'datum_value' => 'label',
    );
    $config['url'] = 'https://webforms.asu.edu/salesforce_query/api/' . $config['type'] . '/' . $config['name'];
    $config['json_options'] = array(
      CURLOPT_URL => $config['url'],
      CURLOPT_RETURNTRANSFER => 1,
      CURLOPT_HTTPHEADER => _asu_rfi_get_curl_auth(),
    );
  }
  elseif ($dataset == 'country') {
      $config = array(
        'type' => 'fieldinfo',
        'name' => 'country',
        'db_tbl' => 'asu_rfi_countries',
        'db_key' => 'countryCode3',
        'db_value' => 'countryDesc',
        'datum_key' => 'value',
        'datum_value' => 'label',
      );
      $config['url'] = 'https://webforms.asu.edu/salesforce_query/api/' . $config['type'] . '/' . $config['name'];
      $config['json_options'] = array(
        CURLOPT_URL => $config['url'],
        CURLOPT_RETURNTRANSFER => 1,
        CURLOPT_HTTPHEADER => _asu_rfi_get_curl_auth(),
      );
  }
  elseif ($dataset == 'rfi_dedupe_list_terms') {
    $config = array(
      'type' => 'select',
      'name' => 'rfi_dedupe_list_terms',
      'db_tbl' => 'asu_rfi_sem_dates',
      'db_key' => 'semId',
      'db_value' => 'semLabel',
      'datum_key' => 'Id',
      'datum_value' => 'Name',
    );
    $config['url'] = 'https://webforms.asu.edu/salesforce_query/api/' . $config['type'] . '/' . $config['name'];
    $fields = array(
      'condition_Term_Status__c' => TRUE,
    );
    $body = json_encode($fields);
    $config['json_options'] = array(
      CURLOPT_URL => $config['url'],
      CURLOPT_POST => 1,
      CURLOPT_POSTFIELDS => $body,
      CURLOPT_RETURNTRANSFER => 1,
      CURLOPT_HTTPHEADER => _asu_rfi_get_curl_auth(),
    );
  }

  return $config;
}