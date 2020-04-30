<?php /** @noinspection PhpUnusedParameterInspection */

/**
 * Get list names and IDs for various RFI form dropdowns
 *
 * @param $name - (str) Which dataset to pull (state_province, country, rfi_dedupe_list_terms (aka sem_dates))
 * @param $installing - (bool) Module installing for the first time (TRUE)
 *   or just running via cron (FALSE).
 * @throws InvalidMergeQueryException
 */
function asu_rfi_get_form_select_options($name, $installing = FALSE) {
  // Get configs
  $config = (array) _asu_rfi_get_select_options_config($name);
  $url = $config['url'];
  $db_tbl = $config['db_tbl'];
  $json_options = $config['json_options'];
  $results = array();

  // Do CURL call to JSON feed
  try {
    $ch = curl_init();
    curl_setopt_array($ch, $json_options);
    $response = curl_exec($ch);
    $results = json_decode($response);
    curl_close($ch);

    if ($response === FALSE) {
      throw new Exception(curl_error($ch), curl_errno($ch));
    }
  } catch (Exception $e) {
    trigger_error(sprintf(
      'Curl call to get ' . $name . ' from ' . $url . ' failed with error #%d: %s',
      $e->getCode(), $e->getMessage()),
      E_USER_ERROR);
  }

  // Do DB upsert of options if values are returned from JSON feed...
  if (count($results) > 0) {
    $mapped_terms = ($name === 'rfi_dedupe_list_terms')
      ? asu_libs_get_sem_codes_human_mapping(TRUE, array(), 'digits', 4)
      : array();
    $data_count = 0;
    foreach ($results as $result) {
      $datum_key = (!empty($result->{$config['datum_key']})) ? check_plain($result->{$config['datum_key']}) : 'EMPTY';
      $datum_value = (!empty($result->{$config['datum_value']})) ? check_plain($result->{$config['datum_value']}) : 'EMPTY';
      $db_key = $config['db_key'];
      $db_value = $config['db_value'];
      // Upsert since both aren't empty
      if ($datum_key !== 'EMPTY' || $datum_value !== 'EMPTY') {
        $fields = array(
          $db_key => $datum_key,
          $db_value => $datum_value,
        );
        // Add in semester four digit code from semLabel field @TODO 7208
        if (isset($config['db_sorter']) && !empty($config['db_sorter'])) {
          $value = $result->{$config['datum_value']};
          $code = array_search($value, $mapped_terms);
          if ($code !== FALSE && !empty($value)) {
            $fields[$config['db_sorter']] = $code;
          }
        }
        db_merge($db_tbl)
          ->key(array($db_key => $datum_key))
          ->fields($fields)
          ->execute();
        $data_count++;
      }
      else {
        $message = t($name . ' record from ' . $url . ' was rejected. Debugging info: key - :key, value - :name ',
          array(':key' => $datum_key, ':name' => $datum_value,));
        flogger('asu_rfi', $message, array(), WATCHDOG_DEBUG);
      }
    }
    if ($data_count > 0) {
      $message = $data_count . ' out of ' . count($results) . ' ' . $name . ' entries were
        upserted in ' . $db_tbl . ' DB table.';
      flogger('asu_rfi', $message, array(), WATCHDOG_INFO);
    } else { // no $results entries got in
      flogger('asu_rfi', 'None of the ' . count($results) . ' ' . $name . ' entries were
        added to the ' . $db_tbl . ' DB table.', array(), WATCHDOG_NOTICE);
    }
  }

  // Or error out if no dropdown data is in list...
  else {
    $status = WATCHDOG_WARNING;
    $message = 'No ' . $name . ' for RFI forms were pulled from ' . $url .
      ' to insert into ' . $db_tbl . '. Check your existing RFI forms to see if they still have all expected ' . $name . ' options.' .
      ' If it does not, please contact webconsulting@asu.edu for assistance.';

    // Check to see if any option entries (valid or not) still exist in the table from past pulls.
    if (_asu_rfi_check_form_values($db_tbl) === 0 ) {
      $message .= ' The RFI form will not function properly until this issue has been resolved.';
      $status = WATCHDOG_ERROR;
    }
    flogger('asu_rfi', $message, array(), $status, TRUE, FALSE, TRUE);
  }

}

/**
 * Store configs for all three RFI form dropdown types
 * Two columns of table data by default (third optional column - $db_sorter - available for sorting)
 *
 * @param string $dataset - Which dataset to pull (states, country, semester dates, etc.)
 * @return array $config
 */
function _asu_rfi_get_select_options_config($dataset) {
  // PROD or not?
  $env = asu_libs_detect_environment();
  $tld = ($env['type'] === 'dev' XOR $env['type'] === 'qa') ? 'webforms-qa.asu.edu' : 'webforms.asu.edu';

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
    $config['url'] = 'https://' . $tld . '/salesforce_query/api/' . $config['type'] . '/' . $config['name'];
    $config['json_options'] = array(
      CURLOPT_URL => $config['url'],
      CURLOPT_RETURNTRANSFER => 1,
      CURLOPT_HTTPHEADER => _asu_rfi_get_curl_auth($env['type']),
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
      $config['url'] = 'https://' . $tld . '/salesforce_query/api/' . $config['type'] . '/' . $config['name'];
      $config['json_options'] = array(
        CURLOPT_URL => $config['url'],
        CURLOPT_RETURNTRANSFER => 1,
        CURLOPT_HTTPHEADER => _asu_rfi_get_curl_auth($env['type']),
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
      'db_sorter' => 'semSortCode', // Optional param - semester sorting code
    );
    $config['url'] = 'https://' . $tld . '/salesforce_query/api/' . $config['type'] . '/' . $config['name'];
    $fields = array(
      'condition_Term_Status__c' => TRUE,
    );
    $body = json_encode($fields);
    $config['json_options'] = array(
      CURLOPT_URL => $config['url'],
      CURLOPT_POST => 1,
      CURLOPT_POSTFIELDS => $body,
      CURLOPT_RETURNTRANSFER => 1,
      CURLOPT_HTTPHEADER => _asu_rfi_get_curl_auth($env['type']),
    );
  }
  return $config;
}
