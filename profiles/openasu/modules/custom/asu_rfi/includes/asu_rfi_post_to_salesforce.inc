<?php

/**
 * POSTs form data to Salesforce for both UNDERGRAD and GRADUATE submissions.
 * Used by multiple forms (long form, multiform)
 * Done one submission at a time.
 * @param array $data
 * @param string $type - Undergrad or graduate
 */
function asu_rfi_post_to_sf_middleware($data, $type) {
  global $base_url;
  $submission_data = array();
  $college_code = $url = $body = '';
  $form_mode = variable_get('asu_rfi_form_mode');

  // Pull up RFI submission node
  $degreeMappings = _asu_rfi_degree_field_mappings();
  $nid = $data['submission_nodeid'];
  $node = node_load($nid);
  $nodeArr = array(
    $node->field_rfi_program['und'][0]['value'] => $node->field_rfi_program_name['und'][0]['value']
  );
  $availableCampuses = _asu_rfi_campus_location_options($nodeArr);

  // Pull up RFI submission node
  $node_wrapper = entity_metadata_wrapper('node', $node);

  // Get information for logging
  $nid_info = (isset($node_wrapper->nid)) ? ' for NID ' . $node_wrapper->nid->value() : '';

  // Status updated for incomplete/pending submissions
  if (isset($node_wrapper->field_rfi_submission_status)) {
    if ($node_wrapper->field_rfi_submission_status->value() == "Form_Multi_Partial") {
      $node_wrapper->field_rfi_submission_status->set('SF_Pending');
      $node_wrapper->save();
    } else { // Attempt already made to submit to ; Set to "I Need help"
      if ($node_wrapper->field_rfi_submission_status->value() == "SF_Pending") {
        $node_wrapper->field_rfi_submission_status->set('SF_Failed');
        $node_wrapper->save();
      }
    }
  }

  ////////////////////////////
  // Start building data for middleware submission
  ////////////////////////////
  $prog_code = $data['program_code'];
  $campus = _asu_rfi_get_correct_campus_id($data['campus']);
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
    if (!isset($campus) && sizeof($availableCampuses) == 1
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
  $server = _asu_rfi_detect_source($data, $type);
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
      if ($form_mode == 'test') {
        $url = 'https://requestinfo-qa.asu.edu/prospect_form_post';
      }
      else {
        $url = 'https://requestinfo.asu.edu/prospect_form_post';
      }
    }

    // Build DEFAULT Graduate data array for Salesforce (the camelCase field keys
    // don't match the usual key formatting).
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
    // Legacy code for GRADUATE level only(?)
    if ($type === ASU_RFI_PROSPECT_LEVEL_GRAD) {
      foreach ($submission_data as $key_value => $result_array) {
        if (($result_array == "None")) {
          unset($submission_data[$key_value]);
        }
      }
    }
  }

  ///////////////////////////////////
  // Post data to SalesForce middleware via cURL
  // NOTE: The Salesforce endpoint for undergraduate testing submissions is
  // publicly available for undergraduate submissions.
  // The graduate endpoint for testing (currently requestinfo-qa.asu.edu) is not available
  // for testing from outside the ASU network (including Pantheon sites).
  ///////////////////////////////////

  if ($environ['endpoint_access'] === true || $type === ASU_RFI_PROSPECT_LEVEL_UNDERGRAD) {
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

      dpm(CURLOPT_SSLVERSION, 'curlopt_sslversion');
      dpm($options, 'curl - options');

      $response = curl_exec($ch);
      $curl_info = curl_getinfo($ch); // Used by your drupal messages below

      variable_set('asu_rfi_last_attempt_SF_posting', time());

      // DEBUG
      dpm($response, 'curl - response');
      dpm($curl_info, 'curl - curl_info');

      // Get the response from Salesforce middleware
      $message = (strpos($response, "-1 ") == 0) ? explode(':', $response) : '';

      // DEBUG
      dpm($message, 'message');

      // SUCCESSFUL CURL POST submission to SF middleware
      if (($curl_info['http_code'] == 200)) {
        $curl_message = 'SF SUCCESS - Posted form submission' . $nid_info . ' to ' . $url . ' middleware.';
        if (isset($node_wrapper->field_rfi_submission_status)) {
          $node_wrapper->field_rfi_submission_status->set('SF_Complete');
        }
        if (isset($node_wrapper->field_rfi_error_message)) {
          $node_wrapper->field_rfi_error_message->set('');
        }
        $node_wrapper->save();
        // Record time of latest successful post
        variable_set('asu_rfi_last_success_SF_posting', time());
        watchdog('asu_rfi', $curl_message,
          array(), WATCHDOG_INFO);
      }
      // FAILED CURL submission to SF middleware
      // Save the error message in the submission node and send message
      // onto the confirmation page screen.
      else {
        $curl_message = (isset($node_wrapper->field_rfi_error_message))
          ? 'FAILED - Could not post form submission ' . $nid_info
          . ' to SF middleware at ' . $url . '. HTTP CODE: '
          . $curl_info['http_code'] . ' - ' . $response : '';

        if (($curl_info['http_code'] >= 400)) {
          // update error message
          if (isset($node_wrapper->field_rfi_error_message)) {
            $curl_message = (is_array($message)) ? $curl_message . ' - ' . $message[0] : $curl_message;
          }
          // Get admin email address from admin settings page
          $to_email = variable_get('asu_rfi_error_email', NULL);
          // Send error email to admins. Don't send if any of the following is true:
          // - middleware app key is empty
          // - no admin email is set
          // - this is a cron job
          if (!empty($mw_auth_key)) {
            if (!empty($to_email)) {
              if (!isset($data['cron_run']) || ($data['cron_run'] != "Cron_running")) {
                _asu_rfi_failed_post_email($to_email, $nid);
              }
            }
          }
        }
        $node_wrapper->field_rfi_error_message->set($curl_message);
        $node_wrapper->save();
        watchdog('asu_rfi', $curl_message, array(), WATCHDOG_ERROR);
        variable_set('asu_rfi_last_failure_SF_posting', time());
      }

      curl_close($ch);

      if (drupal_valid_path('admin')) {
        drupal_set_message($curl_message);
      }

      if (FALSE === $response) {
        throw new Exception(curl_error($ch), curl_errno($ch));
      }
    } catch (Exception $e) {
      $msg_start = '<strong>ERROR</strong>: RFI submission failed to post to '
        . $base_url . ' SF middleware. HTTP CODE: ' . $curl_info['http_code'] . '. ';
      $msg_ending = ' Please contact <a href="https://drupal.asu.edu/wcs">Web Consulting</a> for assistance.';
      $message_final = $msg_start . (((int) $e->getCode() === 0) ? ' This may have been due to
      ASU network access restrictions.' : '') . $msg_ending;
      watchdog('asu_rfi', $message_final, array(), WATCHDOG_ERROR);
      trigger_error(sprintf(
        'Curl failed with error #%d: %s' . $message_final,
        $e->getCode(), $e->getMessage()),
        E_USER_ERROR);
    }
  }
  else { // Do not attempt a JSON submission to a SF middleware endpoint.
    $message_final = 'NO RFI SUBMISSION ATTEMPTED. RFI test submissions to the Salesforce middleware at ' . $url
      . ' from (' . $base_url . ') will not work due to ASU network access restrictions.';
    watchdog('asu_rfi', $message_final, array(), WATCHDOG_WARNING);
    if (drupal_valid_path('admin')) {
      drupal_set_message($message_final, 'warning');
    }

    if (isset($node_wrapper->field_rfi_error_message)) {
      $node_wrapper->field_rfi_error_message->set($message_final);
    }
    $node_wrapper->save();
  }
}
