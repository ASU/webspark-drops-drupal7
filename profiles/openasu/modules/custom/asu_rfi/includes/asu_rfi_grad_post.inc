<?php

function asu_rfi_grad_post($data) {
  $degreeMappings = _asu_rfi_get_degree_mappings();
  $form_mode = variable_get('asu_rfi_form_mode');

  $nodeid = $data['submission_nodeid'];
  $node = node_load($nodeid);
  $nodeArr = array(
    $node->field_rfi_program['und'][0]['value'] => $node->field_rfi_program_name['und'][0]['value']
  );
  $availableCampuses = _asu_rfi_query_codes($nodeArr);

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
  $campus = _asu_rfi_correct_campus_id($data['campus']);
  $phone = preg_replace('[\D]', '', $data['phone']);
  $mobile = (isset($data['mobile_check'])) ? str_replace('-', '', $data['mobile_check']) : '';   // mobile phone
  $dob = (isset($data['birthdate'])) ? $data['birthdate'] : ''; // date of birth
  $military = (isset($data['military'])) ? $data['military'] : '';  // Military
  $comment = (isset($data['questions'])) ? $data['questions'] : ''; // Comment
  $address = (isset($data['address'])) ? $data['address'] : ''; // Address
  $city = (isset($data['city'])) ? $data['city'] : ''; // City
  $state = (isset($data['state'])) ? $data['state'] : ''; //
  $country = (isset($data['country'])) ? $data['country'] : ''; // country
  if ($country !== "United States" || $country !== "Canada") {
    $address = '';
    $state = '';
    $city = '';
  }
  $location = (isset($data['location'])) ? $data['location'] : '';

  // enterpriseclientid for use in EdPlus Leads submissions.
  $enterpriseclientid = (isset($data['enterpriseclientid'])) ? $data['enterpriseclientid'] : '';

  // See if it's dev or qa site.
  $environ = _asu_rfi_determine_environment();

  // Salesforce URL for posting data
  if (($environ == "dev") || ($environ == "qa")) {
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

  if(!isset($campus) && sizeof($availableCampuses) == 1 && ($availableCampuses[0] == "Online" || $availableCampuses[0] == "online")) {
    $location = "Online";
  }

  if (strtolower($location) == 'online') {
    $submission_data['campusSelection'] = "ONLNE";
    $asuOnlineList = _asu_rfi_parse_programs();
    $managedOnline = asu_rfi_check_managed_online($data['program_code'], $asuOnlineList);

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
  } else {
    foreach ($submission_data as $key_value => $result_array) {
      if (($result_array == "None")) {
        unset($submission_data[$key_value]);
      }
    }
  }

  // Post data to salesforce via cURL
  $curl = curl_init($url);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE); // If you don't want to use any of the return information, set to false
  curl_setopt($curl, CURLOPT_HEADER, FALSE); // FALSE Remove informational headers
  curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'POST');
  curl_setopt($curl, CURLOPT_POSTFIELDS, $submission_data); // data mapping
  // curl_setopt($curl, CURLOPT_SSLVERSION, 1); // Sets the security protocol to TLSv1
  // UPDATE: Disabling to let the web server choose a default SSL Version is better.
  curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);

  $response = curl_exec($curl);
  $info = curl_getinfo($curl); // Used by your drupal messages below
  curl_close($curl);

  if (strpos($response, "-1 ") == 0) {
    $message = explode(':', $response);
  }

  // Get the response from Salesforce. If the submission is not successful, update the previous submission status to Incomplete
  if (($info['http_code'] == 400) || ($info['http_code'] == 500)) {
    //update error message
    if (isset($node_wrapper->field_rfi_error_message)) {
      if (isset($message)) {
        $node_wrapper->field_rfi_error_message->set($message[1]);
      }
      $node_wrapper->save();
    }
  }

  if (($info['http_code'] == 200)) {
    $node_wrapper->field_rfi_submission_status->set('SF_Complete');
    $node_wrapper->field_rfi_error_message->set('');
    $node_wrapper->save();
    // If this successfully posts to SF, the set "asu_rfi_last_failure_SF_posting"
    // variable to current time.
    variable_set('asu_rfi_last_attempt_SF_posting', time());
  }

  // If failed to post to SF, the set "asu_rfi_last_failure_SF_posting" variable
  // to current time
  if (($info['http_code'] != 200)) {
    variable_set('asu_rfi_last_failure_SF_posting', time());
  }
}
