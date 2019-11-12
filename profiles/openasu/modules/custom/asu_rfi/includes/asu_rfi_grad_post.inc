<?php

/**
 * Actually POSTs form data to Salesforce for GRADUATE submissions.
 * Used by multiple forms (long form, multiform)
 * @param $data (was $post - why renamed here??)
 */

function asu_rfi_grad_post($data) {
  $degreeMappings = _asu_rfi_degree_field_mappings();
  $form_mode = variable_get('asu_rfi_form_mode');

  dpm($data, __FUNCTION__ . ' $data');

  $nodeid = $data['submission_nodeid'];
  $node = node_load($nodeid);
  $nodeArr = array(
    $node->field_rfi_program['und'][0]['value'] => $node->field_rfi_program_name['und'][0]['value']
  );
  $availableCampuses = _asu_rfi_campus_location_options($nodeArr);

  $node_wrapper = entity_metadata_wrapper('node', $node);
  if (isset($node_wrapper->field_rfi_submission_status)) {
    if ($node_wrapper->field_rfi_submission_status->value() == "Incomplete") {
      $node_wrapper->field_rfi_submission_status->set('Pending');
    } else {
      if ($node_wrapper->field_rfi_submission_status->value() == "Pending") {
        $node_wrapper->field_rfi_submission_status->set('Action Required');
      }
    }
  }

  $domain = isset($data['domain']) ? $data['domain'] : $_SERVER['HTTP_HOST'];
  $type_of_form = $data['type_of_form'];
  $source = $domain . '-' . $type_of_form . '-G';

  // Get authentication key
  $mw_auth_key = variable_get('asu_rfi_form_auth_key');
  //$hashkey = sha1($mw_auth_key . '+' . $nodeid); // Not used??

  $ipAddress = isset($data['ip_address']) ? $data['ip_address'] : $_SERVER['REMOTE_ADDR'];
  $term = (isset($data['semester_name'])) ? $data['semester_name'] : '';
  $campus = _asu_rfi_get_correct_campus_id($data['campus']);
  $phone = preg_replace('[\D]', '', $data['phone']);
  $mobile = (isset($data['mobile_check'])) ? str_replace('-', '', $data['mobile_check']) : '';   // mobile phone
  $dob = (isset($data['birthdate'])) ? $data['birthdate'] : ''; // date of birth
  $military = (isset($data['military'])) ? $data['military'] : '';  // Military
  $comment = (isset($data['questions'])) ? $data['questions'] : ''; // Comment

  $address = (isset($data['address'])) ? $data['address'] : ''; // Address
  $city = (isset($data['city'])) ? $data['city'] : ''; // City
  $state = (isset($data['state'])) ? $data['state'] : ''; // State
  $country = (isset($data['country'])) ? $data['country'] : ''; // country
  // If NEITHER the USA NOR Canada, drop the address data.
  if ($country !== "United States" && $country !== "Canada") {
    $address = '';
    $state = '';
    $city = '';
  }
  $location = (isset($data['location'])) ? $data['location'] : '';

  // enterpriseclientid for use in EdPlus Leads submissions.
  $enterpriseclientid = (isset($data['enterpriseclientid'])) ? $data['enterpriseclientid'] : '';

  // Salesforce URL for posting data
  // Is it a dev or qa site, or in "test mode"?
  $environ = (array) _asu_rfi_detect_environment();
  if (($environ['type'] === "dev") || ($environ['type'] === "qa")) {
    $url = 'https://requestinfo-qa.asu.edu/prospect_form_post';
  } else {
    if ($form_mode == 'test') {
      $url = 'https://requestinfo-qa.asu.edu/prospect_form_post';
    } else {
      $url = 'https://requestinfo.asu.edu/prospect_form_post';
    }
  }

  // Build data array to post to Salesforce
  $submission_data = array(
    'source' => $source,
    'firstName' => $data['first_name'],
    'lastName' => $data['last_name'],
    'emailAddress' => $data['email'],
    'phoneNumber' => $phone,
    'projectedEnrollment' => $term,
    'addressLine1' => $address,
    'city' => $city,
    'state' => $state,
    'countryOfResidence' => $country,
    'birthdate' => $dob,
    'militaryStatus' => $military,
    'questions' => $comment,
    'poiCode' => $data['program_code'],
    'zip' => $data['zipcode'],
    'iStudent' => $data['citizenship'],
    'smsNumber' => $mobile,
    'campusSelection' => $campus,
  );

  // But WAIT! There's custom management for Online (and ONLY online) campus people
  if(!isset($campus) && sizeof($availableCampuses) == 1
    && (ucfirst($availableCampuses[0]) == "Online")) {
    $location = "Online";
  }
  if (strtolower($location) == 'online') {
    $submission_data['campusSelection'] = "ONLNE";
    $asuOnlineList = _asu_rfi_parse_programs();
    $managedOnline = _asu_rfi_check_managed_online($data['program_code'], $asuOnlineList);

    if ($managedOnline == true) {
      $college_code = db_query('select ' . $degreeMappings['field_academic_program_value']
        . ' from ' . $degreeMappings['table_asu_academic_program'] . ' prog join '
        . $degreeMappings['table_asu_academic_plan'] . ' plan on prog.entity_id = plan.entity_id where plan.'
        . $degreeMappings['field_academic_plan_value'] . ' = :plancode',
        array(':plancode' => $data['program_code']))->fetchField();

      $submission_data = array(
        'first_name' => $data['first_name'],
        'last_name' => $data['last_name'],
        'program' => $college_code . '-' . $data['program_code'],
        'email' => $data['email'],
        'phone' => $data['phone'],
        'prod_test_flag' => $form_mode,
        'base_url' => $data['domain'],
        'origin_uri' => $GLOBALS['base_url'] . '/' . request_path(),
        'remote_nid' => $nodeid,
        'ldetect_v' => $ipAddress,
        'campaign' => $data['domain'] . '-' . $type_of_form . '-G',
        'sourceid' => $nodeid, // Overwritten with API key in Middleware.
        'enterpriseclientid' => $enterpriseclientid,
      );

      $submission_data = json_encode($submission_data);
      $fieldHash = sha1($mw_auth_key . '+' . $submission_data);
      $url = "https://webforms.asu.edu/asu_edplus_middleware/submit/$fieldHash";
    }
  }
  // NOT online campus
  else {
    foreach ($submission_data as $key_value => $result_array) {
      if (($result_array == "None")) {
        unset($submission_data[$key_value]);
      }
    }
  }

  ///////////////////////////////////
  // Post data to SalesForce middleware via cURL
  // Attempt only if access to the endpoint is available
  ///////////////////////////////////
  if ($environ['endpoint_access'] === true) {
    try {
      $ch = curl_init();
      $options = array(
        CURLOPT_URL => $url,
        CURLOPT_POST => 1,
        CURLOPT_POSTFIELDS => $submission_data,
        CURLOPT_RETURNTRANSFER => 1,
        CURLOPT_HTTPHEADER => array('Content-Type: text/json'),
        CURLOPT_SSL_VERIFYPEER => FALSE,
      );
      curl_setopt_array($ch, $options);

      // DEBUG
      dpm(CURLOPT_SSLVERSION, 'curlopt_sslversion');
      dpm($options, 'curl - options');

      $response = curl_exec($ch);
      $curl_info = curl_getinfo($ch); // Used by your drupal messages below

      // DEBUG
      dpm($response, 'curl - response');
      dpm($curl_info, 'curl - curl_info');

      // Get the response from Salesforce middleware
      if (strpos($response, "-1 ") == 0) {
        $message = explode(':', $response);
      }

      // DEBUG
      dpm($message, 'message');

      // Successful POST of submission to middleware.
      if (($curl_info['http_code'] == 200)) {
        $node_wrapper->field_rfi_submission_status->set('SF_Complete');
        $node_wrapper->field_rfi_error_message->set('');
        $node_wrapper->save();
        // If this successfully posts to SF, set "asu_rfi_last_failure_SF_posting"
        // variable to current time.
        variable_set('asu_rfi_last_attempt_SF_posting', time());
      }
      // If the POST to the middleware is not successful
      else {
        if (($curl_info['http_code'] >= 400)) { // errors !== 400
          // update error message
          if (isset($node_wrapper->field_rfi_error_message)) {
            if (isset($message)) {
              $msg = $message[1];
            }
            else {
              $msg = 'HTTP Code: ' . $curl_info['http_code'] . ' - See Exception error.';
            }
          }
        }
        // Update the failed submission status to Incomplete.
        $node_wrapper->field_rfi_error_message->set($msg);
        $node_wrapper->field_rfi_submission_status->set('Incomplete');
        $node_wrapper->save();
        variable_set('asu_rfi_last_failure_SF_posting', time());
      }

      curl_close($ch);

      if (FALSE === $response) {
        throw new Exception(curl_error($ch), curl_errno($ch));
      }
    } catch (Exception $e) {
      $msg_added = ($e->getCode() == 0) ? ' -- IMPORTANT: Testing SalesForce RFI
      submissions is not possible in this web hosting environment. The SalesForce
      endpoint for testing is not reachable from this web server due to ASU network access
      restrictions.' : '';
      trigger_error(sprintf(
        'Curl failed with error #%d: %s' . $msg_added,
        $e->getCode(), $e->getMessage()),
        E_USER_ERROR);
    }
  } else {
    $msg_added = 'IMPORTANT: Testing SalesForce RFI
      submissions is not possible in this web hosting environment. The SalesForce
      endpoint for testing is not reachable from this web server due to ASU network access
      restrictions.';
    watchdog('asu_rfi', $msg_added, array(), WATCHDOG_WARNING);
    drupal_set_message($message, 'warning');
  }
}
