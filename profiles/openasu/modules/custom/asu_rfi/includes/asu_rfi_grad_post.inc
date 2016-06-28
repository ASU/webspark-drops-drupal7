<?php

function asu_rfi_grad_post($data)
{

  $nodeid = $data['submission_nodeid'];

  $node = node_load($nodeid);

  $nodeArr = array(
    $node->field_rfi_program['und'][0]['value'] => $node->field_rfi_program_name['und'][0]['value']
  );
  $availableCampuses = asu_rfi_query_codes($nodeArr);

  $node_wrapper = entity_metadata_wrapper('node', $node);
  if ($node_wrapper->field_rfi_submission_status->value() == "Incomplete") {

    $node_wrapper->field_rfi_submission_status->set('Pending');

  } else if ($node_wrapper->field_rfi_submission_status->value() == "Pending") {

    $node_wrapper->field_rfi_submission_status->set('Action Required');

  }

  $domain = isset($data['domain']) ? $data['domain'] : $_SERVER['HTTP_HOST'];;
  $phone = preg_replace('[\D]', '', $data['phone']);
  $state = $data['state'];
  $form_mode = variable_get('asu_rfi_form_mode');
  $type_of_form = $data['type_of_form'];
  $source = $domain . '-' . $type_of_form . '-G';
  $campus = $data['campus'];
  $ipAddress = $data['ip_address'];
  //get athentication key
  $mw_auth_key = variable_get('asu_rfi_form_auth_key');
  $hashkey = sha1($mw_auth_key . '+' . $nodeid);

  //mobile number
  if (isset($data['mobile_check'])) {
    $mobile = str_replace('-', '', $data['mobile_check']);
  } else {
    $mobile = '';
  }


  //date of birth
  if (isset($data['birthdate'])) {
    $dob = $data['birthdate'];
  } else {
    $dob = '';
  }

  //Military
  if (isset($data['military'])) {
    $military = $data['military'];
  } else {
    $military = '';
  }

  if (isset($data['semester_name'])) {
    $term = $data['semester_name'];
  } else {
    $term = '';
  }

  //Comment
  if (isset($data['questions'])) {
    $comment = $data['questions'];
  } else {
    $comment = '';
  }

  //city
  if (isset($data['city'])) {
    $city = $data['city'];
  } else {
    $city = '';
  }
  if (isset($data['address'])) {
    $address = $data['address'];
  } else {
    $address = '';
  }

  //country
  if (isset($data['country'])) {
    $country = $data['country'];
  } else {
    $country = '';
  }

  if (isset($data['location'])) {
    $location = $data['location'];
  } else {
    $location = '';
  }

  //Get siteDomain variable to see if it's dev or qa site.
  global $base_url;

  if ((strpos($base_url, 'https://localhost') == 0) || (strpos($base_url, 'http://localhost') == 0)) {
    $environ = 'dev';
  }
  if ((strpos($base_url, 'https://dev-') == 0) || (strpos($base_url, 'http://dev-') == 0) || (strpos($base_url, '-dev') > 0)) {
    $environ = 'dev';
  }
  if ((strpos($base_url, 'https://qa-') == 0) || (strpos($base_url, 'http://qa-') == 0) || (strpos($base_url, '-qa') > 0)) {
    $environ = 'qa';
  }
  if ((strpos($base_url, 'https://test-') == 0) || (strpos($base_url, 'http://test-') > 0)) {
    $environ = 'qa';
  }

  // Salesforce URL to post data to
  if ((isset($environ) && $environ == "dev") || (isset($environ) && $environ == "qa")) {
    $url = 'https://requestinfo-qa.asu.edu/prospect_form_post';
  } else {
    if ($form_mode == 'test') {
      $url = 'https://requestinfo-qa.asu.edu/prospect_form_post';
    } else {
      $url = 'https://requestinfo.asu.edu/prospect_form_post';
    }
  }



  if ($country !== "United States" || $country !== "Canada") {
    $address = '';
    $state = '';
    $city = '';
  }

  // build data array to post
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
    'campus' => $campus,

  );

  if(!isset($campus) && sizeof($availableCampuses) == 1 && ($availableCampuses[0] == "Online" || $availableCampuses[0] == "online")){
    $location = "Online";
  }

  if ($location == 'Online' || $location == 'online') {

    $asuOnlineList = asu_rfi_parse_programs();
    $managedOnline = asu_rfi_check_managed_online($data['program_code'], $asuOnlineList);

    if ($managedOnline == true) {

      $college_code = db_query('select field_asu_academic_program_value from field_data_field_asu_academic_program prog join field_data_field_asu_academic_plan plan on prog.entity_id = plan.entity_id where plan.field_asu_academic_plan_value = :plancode', array(':plancode' => $data['program_code']))->fetchField();

      $submission_data = array(
        'first_name' => $data['first_name'],
        'last_name' => $data['last_name'],
        'program' => $college_code . '-' . $data['program_code'],
        'email' => $data['email'],
        'phone' => $data['phone'],
        'prod_test_flag' => $form_mode,
        'base_url' => $data['domain'],
        'remote_nid' => $nodeid,
        'ldetect_v' => $ipAddress,
        'campaign' => $data['domain'] . '-' . $type_of_form . '-G',
        'sourceid' => $nodeid,
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

  //url to post data to salesforce
  $curl = curl_init($url);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE); //If you don't want to use any of the return information, set to false
  curl_setopt($curl, CURLOPT_HEADER, FALSE); //Set this to false to remove informational headers
  curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'POST');
  curl_setopt($curl, CURLOPT_POSTFIELDS, $submission_data); //data mapping
  curl_setopt($curl, CURLOPT_SSLVERSION, 1); //This will set the security protocol to TLSv1
  curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
  $response = curl_exec($curl);

  $info = curl_getinfo($curl); //Used by your drupal messages below

  curl_close($curl);

  if (strpos($response, "-1 ") == 0) {
    $message = explode(':', $response);
  }

  //Get the response from Salesforce. If the submission is not successfull, update the previous submission status to Incomplete
  if (($info['http_code'] == 400) || ($info['http_code'] == 500)) {
    //update error message
    $node_wrapper->field_rfi_error_message->set($message[1]);
    $node_wrapper->save();
  }

  if (($info['http_code'] == 200)) {
    $node_wrapper->field_rfi_submission_status->set('SF_Complete');
    $node_wrapper->field_rfi_error_message->set('');
    $node_wrapper->save();
    //if succesfully to post to SF, the set "last_failure_SF_posting" variable to current time
    variable_set('last_success_SF_posting', time());
  }

  //if failed to post to SF, the set "last_failure_SF_posting" variable to current time
  if (($info['http_code'] != 200)) {
    variable_set('last_failure_SF_posting', time());
  }
}

