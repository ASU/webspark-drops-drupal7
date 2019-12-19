<?php

/**
 * POSTs form data to Salesforce.
 * Used by long form and the multiform, for both UNDERGRAD and GRADUATE submissions.
 * Done one submission at a time.
 * @param array $data - form data to submit
 * @param string $type - Undergrad or graduate
 */
function asu_rfi_post_to_middleware($data, $type) {
  global $base_url;
  $submission_data = array();
  $college_code = $url = $body = '';
  $form_mode = variable_get('asu_rfi_form_mode');
  $sf_multi_pending = FALSE;

  // Get RFI submission node
  $degreeMappings = _asu_rfi_get_degree_field_mappings();
  $nid = $data['submission_nodeid'];
  $node = node_load($nid);
  $nodeArr = array(
    $node->field_rfi_program[LANGUAGE_NONE][0]['value'] => $node->field_rfi_program_name[LANGUAGE_NONE][0]['value']
  );
  $availableCampuses = _asu_rfi_get_campus_location_options($nodeArr);
  $node_wrapper = entity_metadata_wrapper('node', $node);

  // Get information for logging
  $nid_info = (isset($node_wrapper->nid)) ? $node_wrapper->nid->value() : '';

  // Incomplete multiform submissions logic
  if (isset($node_wrapper->field_rfi_submission_status)) {
    if ($node_wrapper->field_rfi_submission_status->value() === "Form_Multi_Partial") {
      // Do not send to SalesForce yet because this is NOT a cron run.
      // This is the initial form submission.
      $sf_multi_pending = TRUE;
      $node_wrapper->field_rfi_submission_status->set('SF_Multi_Pending');
      if (isset($node_wrapper->field_rfi_error_message)) {
        $node_wrapper->field_rfi_error_message->set('Multiform is now pending to be submitted in the NEXT iteration of submissions (regardless of completion state).');
      }
      $node_wrapper->save();
    } elseif ($node_wrapper->field_rfi_submission_status->value() === "SF_Multi_Pending") {
      if (isset($node_wrapper->created) && isset($node_wrapper->field_rfi_error_message)) {
        $created = $node_wrapper->created->value();
        $message = _asu_rfi_create_expired_message($created);
        $node_wrapper->field_rfi_error_message->set($message);
        $node_wrapper->save();
      }
    }
  }

  ////////////////////////////
  // Start building data for middleware submission
  ////////////////////////////
  $prog_code = $data['program_code'];
  $campus = _asu_rfi_get_salesforce_campus_id($data['campus']);
  $phone = preg_replace('[\D]', '', $data['phone']);
  $mobile = (isset($data['mobile_check']))
    ? str_replace('-', '', $data['mobile_check'])
    : ''; // mobile phone
  $dob = (isset($data['birthdate'])) ? $data['birthdate'] : ''; // date of birth
  $military = (isset($data['military'])) ? $data['military'] : '';  // Military
  $comment = (isset($data['questions'])) ? $data['questions'] : ''; // Comment
  $location = (isset($data['location'])) ? $data['location'] : ''; // Location
  // Online campus check
  if ($location === "no_preference" || $type === ASU_RFI_PROSPECT_LEVEL_GRAD) {
    if (!isset($campus) && count($availableCampuses) == 1
      && (ucfirst($availableCampuses[0]) == "Online")) {
      $location = "Online";
    }
  }
  $address = (isset($data['address'])) ? $data['address'] : ''; // Address
  $city = (isset($data['city'])) ? $data['city'] : ''; // City
  $state = (isset($data['state'])) ? $data['state'] : ''; // State
  $country = (isset($data['country'])) ? $data['country'] : ''; // country

  // GA enterpriseclientid for use in EdPlus Leads submissions.
  $enterpriseclientid = (isset($data['enterpriseclientid'])) ? $data['enterpriseclientid'] : '';
  // Get authentication key
  $mw_auth_key = variable_get('asu_rfi_form_auth_key');

  // Get server diagnostic data for submissions
  $server = _asu_rfi_get_aux_submission_data($data, $type);
  $environ = (array) _asu_rfi_detect_environment();

  // Submission customization - UNDERGRAD vs GRAD
  if ($type === ASU_RFI_PROSPECT_LEVEL_UNDERGRAD) {
    $hashkey = sha1($mw_auth_key . '+' . $nid);
    // Default submission URL (non-Online)
    // @TODO - Add $environ check to hit testing/dev version of webforms.asu.edu?
    $url = "https://webforms.asu.edu/asu_rfi_dedupe/submit_rfi/$hashkey/$nid";

    // Get college code from database based on program code
    if ($prog_code == "" || empty($prog_code)) {
      $prog_code = "Exploratory";
      $college_code = null;
    } else {
      $college_code = _asu_rfi_get_college_code($degreeMappings, $prog_code);
    }

    // Compile DEFAULT Undergrad RFI submission data array
    $submission_data = array(
      'source_id' => $server['source'],
      'base_url' => $server['domain'],
      'prod_test_flag' => $form_mode,
      'first_name' => $data['first_name'],
      'last_name' => $data['last_name'],
      'prospect_level' => ASU_RFI_PROSPECT_LEVEL_UNDERGRAD,
      'student_type' => $data['student_type'],
      'program' => $prog_code,
      'starting_semester' => $data['start_date'],
      'email' => $data['email'],
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

    // Build default submission for email
    $body = json_encode($submission_data);
  }

  if ($type === ASU_RFI_PROSPECT_LEVEL_GRAD) {
    // Semester term name
    $term = (isset($data['semester_name'])) ? $data['semester_name'] : '';
    // If NEITHER the USA NOR Canada, drop the address fields' data.
    if ($country !== "United States" && $country !== "Canada") {
      $address = '';
      $state = '';
      $city = '';
    }

    // Select proper ENV for Salesforce GRAD POSTs.
    // Is it a dev or qa site, or in "test mode"?
    if (($environ['type'] === "dev") || ($environ['type'] === "qa")) {
      $url = 'https://requestinfo-qa.asu.edu/prospect_form_post';
    } else {
      if ($form_mode === 'test') {
        $url = 'https://requestinfo-qa.asu.edu/prospect_form_post';
      }
      else {
        $url = 'https://requestinfo.asu.edu/prospect_form_post';
      }
    }

    // Build DEFAULT Graduate data array for Salesforce
    // @TODO Review camelCase usage
    $submission_data = array(
      'source' => $server['source'],
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
      'poiCode' => $prog_code,
      'zip' => $data['zipcode'],
      'iStudent' => $data['citizenship'],
      'smsNumber' => $mobile,
      'campusSelection' => $campus,
    );
  }

  // Alter Online campus submission data
  if (strtolower($location) === "online") {
    if ($type === ASU_RFI_PROSPECT_LEVEL_GRAD) {
      // Match different "Online" campus spelling
      $submission_data['campusSelection'] = "ONLNE";
    }
    $asuOnlineList = _asu_rfi_parse_programs();
    $managedOnline = _asu_rfi_check_managed_online($prog_code, $asuOnlineList);

    if ($managedOnline == true) {
      if ($type === ASU_RFI_PROSPECT_LEVEL_GRAD) {
        $college_code = _asu_rfi_get_college_code($degreeMappings, $prog_code);
        // Make sure all submissions to webforms.asu.edu are attempted.
        $environ['endpoint_access'] = true;
      }
      $submission_data = _asu_rfi_online_fields_alter($type, $submission_data, $server, $college_code, $enterpriseclientid, $nid, $form_mode);
      $body = json_encode($submission_data);
      $fieldHash = sha1($mw_auth_key . '+' .  $body);
      $url = "https://webforms.asu.edu/asu_edplus_middleware/submit/$fieldHash";
    }
  } else {
    // Remove meaningless data points
    if ($type === ASU_RFI_PROSPECT_LEVEL_GRAD) {
      foreach ($submission_data as $key_value => $result_array) {
        if (($result_array == "None")) {
          unset($submission_data[$key_value]);
        }
      }
    }
  }

  ///////////////////////////////////
  // POST data to SalesForce middleware via cURL if the form is ready to submit.
  // NOTE: Some middleware servers (test_mode and/or ENV URLs) are not available
  // outside the ASU network (specifically Pantheon sites).
  ///////////////////////////////////

  if (($environ['endpoint_access'] === true || $type === ASU_RFI_PROSPECT_LEVEL_UNDERGRAD)
    && (!$sf_multi_pending)) {
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
      $curl_info = curl_getinfo($ch); // Used by your drupal messages below

      variable_set('asu_rfi_last_attempt_SF_posting', time());

      // Get the response from Salesforce middleware
      // $message = (strpos($response, "-1 ") === 0) ? explode(':', $response) : '';

      // SUCCESSFUL POST
      if (($curl_info['http_code'] === 200)) {
        $curl_message = 'SUCCESS - Submission ' . $nid_info . ' posted to middleware. Will be deleted by the next cron run.';
        if (isset($node_wrapper->field_rfi_submission_status)) {
          $node_wrapper->field_rfi_submission_status->set('SF_Completed');
        }
        if (isset($node_wrapper->field_rfi_error_message)) {
          $node_wrapper->field_rfi_error_message->set($curl_message);
        }
        $node_wrapper->save();
        // Record time of latest successful post
        variable_set('asu_rfi_last_success_SF_posting', time());
        if (function_exists('drush_log')) {
          drush_log($curl_message, 'success');
        }
        if (drupal_valid_path('admin')) {
          drupal_set_message($curl_message, 'status');
        }
      }
      // FAILED POST
      else {
        $created = $node_wrapper->created->value();
        $expired_message = _asu_rfi_create_expired_message($created);
        $curl_message = 'NID ' . $nid_info . ' submission to ' . $url . ' failed. HTTP CODE ' . $curl_info['http_code']
          . ': ' . $response . "\n -- " . $expired_message;

        if (($curl_info['http_code'] >= 400)) {
          // update error message
          // Get admin email address from admin settings page
          $to_email = variable_get('asu_rfi_error_email', NULL);
          // Send error email to admins.
          if (!empty($to_email) && !empty($mw_auth_key)) { // Admin email and middleware key are locally set
            if (!isset($data['cron_run']) || ($data['cron_run'] != "Cron_running")) { // Not a cron job
              _asu_rfi_create_failed_post_email($to_email, $nid);
            }
          }
        }
        // Save the error message in the submission node
        if (isset($node_wrapper->field_rfi_submission_status)) { //
          $node_wrapper->field_rfi_submission_status->set('SF_Failed');
        }
        if (isset($node_wrapper->field_rfi_error_message)) {
          $node_wrapper->field_rfi_error_message->set($curl_message);
        }
        $node_wrapper->save();
        // Log/print messaging to end user and set timestamp
        watchdog('asu_rfi', $curl_message, array(), WATCHDOG_ERROR);
        if (function_exists('drush_log')) {
          drush_log("\n" . $curl_message . "\n", 'error');
        }
        variable_set('asu_rfi_last_failure_SF_posting', time());
      }
      if (drupal_valid_path('admin')) {
        drupal_set_message($curl_message);
      }

      curl_close($ch);

      if ($response === FALSE) {
        throw new Exception(curl_error($ch), curl_errno($ch));
      }
    } catch (Exception $e) {
      $msg_start = 'Submission POST to ' . $base_url . ' failed. HTTP CODE: '
        . ((isset($curl_info)) ? $curl_info['http_code'] : 'unknown') . '. ';
      $message_final = $msg_start . (((int) $e->getCode() <= 0) ? ' This may have been due to
      ASU network access restrictions.' : '');
      watchdog('asu_rfi', $message_final, array(), WATCHDOG_ERROR);
      trigger_error(sprintf(
        'Curl failed with error #%d: %s' . $message_final,
        $e->getCode(), $e->getMessage()),
        E_USER_ERROR);
    }
  }
  else { // Do not attempt submission to SF middleware
    if ($sf_multi_pending) { // Multiform submission not ready to submit yet
      $message_final = 'NID ' . $nid . ' MF submission will be submitted when 1) the student completes
      the form, or 2) it is resubmitted by either a cron job or manual administrator submission.';
    } else { // Other connectivity issue?
      $message_final = 'NID ' . $nid_info . ' RFI submission ' . $nid_info . ' to ' . $url . ' will not work
       due to ASU network access restrictions.';
      if (isset($node_wrapper->field_rfi_error_message)) {
        $node_wrapper->field_rfi_error_message->set($message_final);
      }
      if (isset($node_wrapper->field_rfi_submission_status)) {
        $node_wrapper->field_rfi_submission_status->set('SF_Failed');
      }
      $node_wrapper->save();
    }
    if (function_exists('drush_log')) {
      drush_log($message_final, 'notice');
    }
    if (drupal_valid_path('admin')) {
      drupal_set_message($message_final, 'info');
    }
  }
}
