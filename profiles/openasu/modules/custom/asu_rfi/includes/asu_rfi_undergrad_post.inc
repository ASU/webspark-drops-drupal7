<?php

/**
 * Post data stored in an ASU RFI node to SalesForce middleware
 * Done one submission at a time.
 * @param $data
 */
function asu_rfi_undergrad_post($data) {
  $degreeMappings = _asu_rfi_degree_field_mappings();
  $nid = $data['submission_nodeid'];
  $node = node_load($nid);
  $nodeArr = array(
    $node->field_rfi_program['und'][0]['value'] => $node->field_rfi_program_name['und'][0]['value']
  );
  $availableCampuses = _asu_rfi_campus_location_options($nodeArr);

  $node_wrapper = entity_metadata_wrapper('node', $node);
  if (isset($node_wrapper->field_rfi_submission_status)) {
    if ($node_wrapper->field_rfi_submission_status->value() == "Incomplete") {
      $node_wrapper->field_rfi_submission_status->set('Pending');
      $node_wrapper->save();
    } else {
      if ($node_wrapper->field_rfi_submission_status->value() == "Pending") {
        $node_wrapper->field_rfi_submission_status->set('action_required');
        $node_wrapper->save();
      }
    }
  }

  $mw_auth_key = variable_get('asu_rfi_form_auth_key');
  $f_name = $data['first_name'];
  $l_name = $data['last_name'];
  $email = $data['email'];
  $ipAddress = isset($data['ip_address']) ? $data['ip_address'] : $_SERVER['REMOTE_ADDR'];
  $phone = preg_replace('[\D]', '', $data['phone']);
  $location = $data['location'];
  $campus = $data['campus'];
  $state = $data['state'];

  $prog_code = $data['program_code'];
  if ($prog_code == "" || empty($prog_code)) {
    $prog_code = "Exploratory";
    $college_code = null;
  } else {
    // Get college code from database based on program code
    $college_code = db_query(
      'select ' . $degreeMappings['field_academic_program_value'] . ' from ' .
      $degreeMappings['table_asu_academic_program'] . ' prog join ' .
      $degreeMappings['table_asu_academic_plan'] .
      ' plan on prog.entity_id = plan.entity_id where plan.' .
      $degreeMappings['field_academic_plan_value'] .
      ' = :plancode',
      array(':plancode' => $prog_code))
      ->fetchField();
  }

  $form_mode = variable_get('asu_rfi_form_mode');
  $hashkey = sha1($mw_auth_key . '+' . $nid);
  $type_of_form = $data['type_of_form'];
  $domain = isset($data['domain']) ? $data['domain'] : $_SERVER['HTTP_HOST'];
  $source = $domain . '-' . $type_of_form . '-UG';
  $campus = _asu_rfi_get_correct_campus_id($campus);

  $mobile = (isset($data['mobile_check']))
    ? str_replace('-', '', $data['mobile_check'])
    : ''; // mobile phone
  $dob = (isset($data['birthdate'])) ? $data['birthdate'] : ''; // date of birth
  $military = (isset($data['military'])) ? $data['military'] : '';  // Military
  $comment = (isset($data['questions'])) ? $data['questions'] : ''; // Comment
  $city = (isset($data['city'])) ? $data['city'] : ''; // City
  $address = (isset($data['address'])) ? $data['address'] : ''; // Address
  $country = (isset($data['country'])) ? $data['country'] : ''; // country
  $enterpriseclientid = (isset($data['enterpriseclientid']))
    ? $data['enterpriseclientid'] : ''; // Enterprise clientid for EdPlus Leads

  if ($location == "no_preference" &&
    sizeof($availableCampuses) == 1 &&
    ($availableCampuses[0] == "Online" || $availableCampuses[0] == "online")) {
    $location = "Online";
  }

  // Compile Undergrad RFI submission data array
  $url = "https://webforms.asu.edu/asu_rfi_dedupe/submit_rfi/$hashkey/$nid";
  $fields = array(
    'source_id' => $source,
    'base_url' => $domain,
    'prod_test_flag' => $form_mode,
    'first_name' => $f_name,
    'last_name' => $l_name,
    'prospect_level' => ASU_RFI_PROSPECT_LEVEL_UNDERGRAD,
    'student_type' => $data['student_type'],
    'program' => $prog_code,
    'starting_semester' => $data['start_date'],
    'email' => $email,
    'zip' => $data['zipcode'],
    'phone' => $phone,
    'birth_date' => $dob,
    'country' => $country,
    'sms' => $mobile,
    'comments' => $comment,
    'street' => $address,
    'city' => $city,
    'state' => $state,
    'intnl_student' => $data['citizenship'],
    'veteran_status' => $military,
    'campus' => $campus,
    'location' => $location,
  );
  $body = json_encode($fields);

  // Alter middleware submission data IF Online program
  if (strtolower($location) == 'online') {
    $asuOnlineList = _asu_rfi_parse_programs();
    $managedOnline = _asu_rfi_check_managed_online($prog_code, $asuOnlineList);
    if ($managedOnline == true) {
      $fields = asu_rfi_online_fields($fields, $nid, $ipAddress, $college_code, $type_of_form, $enterpriseclientid);
      $body = json_encode($fields);
      $fieldHash = sha1($mw_auth_key . '+' . $body);
      $url = "https://webforms.asu.edu/asu_edplus_middleware/submit/$fieldHash";
    }
  }

  ///////////////////////////////////
  // Post data to SalesForce middleware via cURL
  // NOTE: Unlike the graduate level submissions, the Salesforce endpoint for
  // testing submissions is publicly available for undergraduate submissions.
  ///////////////////////////////////
  try {
    $ch = curl_init();
    $options = array(
      CURLOPT_URL => $url,
      CURLOPT_POST => 1,
      CURLOPT_POSTFIELDS => $body,
      CURLOPT_RETURNTRANSFER => 1,
      CURLOPT_HTTPHEADER => array('Content-Type: text/json'),
      CURLOPT_SSL_VERIFYPEER => FALSE,
    );
    curl_setopt_array($ch, $options);
    $response = curl_exec($ch);
    $curl_info = curl_getinfo($ch);

    // If response from middleware is a fail (HTTP code !== 200),
    // 1) save the error message in the submission node and send message
    // onto the confirmation page screen. And set the submission status to
    // Incomplete.

    // if ($response == "Access Denied - hashed value does not match any registered site") {
    if (($curl_info['http_code'] >= 400)) {
      $error_message = (isset($node_wrapper->field_rfi_error_message)) ? $response
        : 'cURL error - HTTP CODE: ' . $curl_info['http_code'];

      $node_wrapper->field_rfi_error_message->set($error_message);
      $node_wrapper->field_rfi_submission_status->set('Incomplete');  // Why wasn't this here before???
      $node_wrapper->save();

      // Get admin email address from admin settings page
      $to_email = variable_get('asu_rfi_error_email', NULL);
      // Get middleware app key. If it's empty, don't send error email to admins.
      if (!empty($mw_auth_key)) {
        if (!empty($to_email)) {
          if (!isset($data['cron_run']) || ($data['cron_run'] != "Cron_running")) {
            _asu_rfi_failed_post_email($to_email, $nid);
          }
        }
      }
      if (drupal_valid_path('admin')) {
        drupal_set_message('Error message from Middleware: ' . $error_message);
      }
    }
    curl_close($ch);

    if (FALSE === $response) {
      throw new Exception(curl_error($ch), curl_errno($ch));
    }
  } catch (Exception $e) {
    trigger_error(sprintf(
      'Curl failed with error #%d: %s',
      $e->getCode(), $e->getMessage()),
      E_USER_ERROR);
  }
}

/**
 * Build online submission data array
 * @param $fields
 * @param $nid
 * @param $ip
 * @param $college_code
 * @param $type_of_form
 * @param $enterpriseclientid
 * @return array
 */
function asu_rfi_online_fields($fields, $nid, $ip, $college_code, $type_of_form, $enterpriseclientid) {
  $fieldsUpdated = array(
    'first_name' => $fields['first_name'],
    'last_name' => $fields['last_name'],
    'program' => $college_code . '-' . $fields['program'],
    'email' => $fields['email'],
    'phone' => $fields['phone'],
    'prod_test_flag' => $fields['prod_test_flag'],
    'base_url' => $fields['base_url'],
    'origin_uri' => $GLOBALS['base_url'] . '/' . request_path(),
    'remote_nid' => $nid,
    'ldetect_v' => $ip,
    'campaign' => $fields['base_url'] . '-' . $type_of_form . '-UG',
    'sourceid' => $nid, // Overwritten with API key in Middleware.
    'enterpriseclientid' => $enterpriseclientid,
  );
  return $fieldsUpdated;
}
