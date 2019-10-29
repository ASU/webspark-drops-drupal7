<?php

/**
 * Get degree mappings
 * Same as grad
 *
 * Example usage:
 * $degreeMappings = _asu_rfi_get_degree_mappings();
 * $degreeContentType = $degreeMappings['content_type'];
 */
function asu_rfi_get_degree_mappings_undergrad_post() {
  return _asu_rfi_get_degree_mappings();
}

function asu_rfi_undergrad_post($data) {
  $degreeMappings = asu_rfi_get_degree_mappings_undergrad_post();
  $nodeid = $data['submission_nodeid'];
  $node = node_load($nodeid);
  $nodeArr = array(
    $node->field_rfi_program['und'][0]['value'] => $node->field_rfi_program_name['und'][0]['value']
  );
  $availableCampuses = _asu_rfi_query_codes($nodeArr);

  $node_wrapper = entity_metadata_wrapper('node', $node);
  if ($node_wrapper->field_rfi_submission_status->value() == "Incomplete") {
    $node_wrapper->field_rfi_submission_status->set('Pending');
    $node_wrapper->save();
  } else if ($node_wrapper->field_rfi_submission_status->value() == "Pending") {
    $node_wrapper->field_rfi_submission_status->set('action_required');
    $node_wrapper->save();
  }

  $mw_auth_key = variable_get('asu_rfi_form_auth_key');
  $f_name = $data['first_name'];
  $l_name = $data['last_name'];
  $email = $data['email'];
  $ipAddress = isset($data['ip_address']) ? $data['ip_address'] : $_SERVER['REMOTE_ADDR'];
  $phone = preg_replace('[\D]', '', $data['phone']);
  // $term = (!empty($data['start_date'])) ? $data['start_date'] : '';

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
  $hashkey = sha1($mw_auth_key . '+' . $nodeid);
  $type_of_form = $data['type_of_form'];
  $domain = isset($data['domain']) ? $data['domain'] : $_SERVER['HTTP_HOST'];
  $source = $domain . '-' . $type_of_form . '-UG';
  $campus = _asu_rfi_correct_campus_id($campus);

  $mobile = (isset($data['mobile_check'])) ? str_replace('-', '', $data['mobile_check']) : '';   // mobile phone
  $dob = (isset($data['birthdate'])) ? $data['birthdate'] : ''; // date of birth
  $military = (isset($data['military'])) ? $data['military'] : '';  // Military
  $comment = (isset($data['questions'])) ? $data['questions'] : ''; // Comment
  $city = (isset($data['city'])) ? $data['city'] : ''; // City
  $address = (isset($data['address'])) ? $data['address'] : ''; // Address
  $country = (isset($data['country'])) ? $data['country'] : ''; // country
  $enterpriseclientid = (isset($data['enterpriseclientid'])) ? $data['enterpriseclientid'] : '';   // Enterprise clientid for EdPlus Leads

  if ($location == "no_preference" &&
    sizeof($availableCampuses) == 1 &&
    ($availableCampuses[0] == "Online" || $availableCampuses[0] == "online")) {
    $location = "Online";
  }

  // Compile RFI submission data

  $url = "https://webforms.asu.edu/asu_rfi_dedupe/submit_rfi/$hashkey/$nodeid";

  $fields = array(
    'source_id' => $source,
    'base_url' => $domain,
    'prod_test_flag' => $form_mode,
    'first_name' => $f_name,
    'last_name' => $l_name,
    'prospect_level' => 'Undergraduate',
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

  if (strtolower($location) == 'online') {

    $asuOnlineList = asu_rfi_parse_programs();
    $managedOnline = asu_rfi_check_managed_online($prog_code, $asuOnlineList);

    if ($managedOnline == true) {
      $fields = asu_rfi_online_fields($fields, $nodeid, $ipAddress, $college_code, $type_of_form, $enterpriseclientid);
      $body = json_encode($fields);
      $fieldHash = sha1($mw_auth_key . '+' . $body);
      $url = "https://webforms.asu.edu/asu_edplus_middleware/submit/$fieldHash";
    }
  }

  try {
    $ch = curl_init();
    $options = array(
      CURLOPT_URL => $url,
      CURLOPT_POST => 1,
      CURLOPT_POSTFIELDS => $body,
      CURLOPT_RETURNTRANSFER => 1,
      CURLOPT_HTTPHEADER => array('Content-Type: text/json'),
      CURLOPT_SSLVERSION => 1,
      CURLOPT_SSL_VERIFYPEER => FALSE,
    );
    curl_setopt_array($ch, $options);
    $response = curl_exec($ch);
    $curl_code = curl_getinfo($ch);

    // If response from middleware is not a success message, save the error message
    // submission node and send message onto the confirmation page screen
    // if ($response == "Access Denied - hashed value does not match any registered site") {
    if (($curl_code['http_code'] == 403 || $curl_code['http_code'] == 500)) {
      $error_message = $response;
      $node_wrapper->field_rfi_error_message->set($error_message);
      $node_wrapper->save();
      $to_email = variable_get('asu_rfi_error_email', NULL); //get error reporting email address from rfi admin settings page
      //get middleware app key. If it's empty, don't send error email to admins.
      if (!empty($mw_auth_key)) {
        if (!empty($to_email)) {
          if (!isset($data['cron_run']) || ($data['cron_run'] != "Cron_running")) {
            $host = $_SERVER['HTTP_HOST'];
            //send email to admin reporting the issue
            $content = "The following <a href='https://$host/node/$nodeid'>submission</a> from " . $_SERVER['HTTP_HOST'] . " has some problem and hasn't been submitted to middleware";
            $subject = "Failed submissions to Sales Force from " . $_SERVER['HTTP_HOST'];
            $my_module = 'mimemail';
            $my_mail_token = '';
            $MimeMailSystem = drupal_mail_system($my_module, $my_mail_token);
            $default_from = variable_get('site_mail', ini_get('sendmail_from'));
            $message = array(
              'id' => $my_module . '_' . $my_mail_token,
              'from' => $default_from,
              'key' => '',
              'subject' => $subject,
              'body' => array($content),
              'to' => $to_email,
              'module' => 'mimemail',
              'headers' => array(
                'From' => $default_from,
                'Sender' => $default_from,
                'Return-Path' => $default_from,
                'Content-Type' => 'text/html; charset=UTF-8;',
                'to' => $to_email
              ),
            );

            $emailmessage = $MimeMailSystem->format($message);
            if ($MimeMailSystem->mail($emailmessage)) {
              watchdog('asu_rfi', 'SF Error message email sent to ' . $to_email);
              variable_set('SF_error_message_sent', time());
            }
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

function asu_rfi_check_managed_online($program, $getProgramsList) {
  foreach ($getProgramsList as $onlineItem){
    if ($onlineItem->plancode == $program && $onlineItem->crmdestination !== "asu"){
      return true;
    }
  }
  return false;
}

function asu_rfi_online_fields($fields, $nodeid, $ip, $college_code, $type_of_form, $enterpriseclientid) {
  $fieldsUpdated = array(
    'first_name' => $fields['first_name'],
    'last_name' => $fields['last_name'],
    'program' => $college_code . '-' . $fields['program'],
    'email' => $fields['email'],
    'phone' => $fields['phone'],
    'prod_test_flag' => $fields['prod_test_flag'],
    'base_url' => $fields['base_url'],
    'origin_uri' => $GLOBALS['base_url'] . '/' . request_path(),
    'remote_nid' => $nodeid,
    'ldetect_v' => $ip,
    'campaign' => $fields['base_url'] . '-' . $type_of_form . '-UG',
    'sourceid' => $nodeid, // Overwritten with API key in Middleware.
    'enterpriseclientid' => $enterpriseclientid,
  );
  return $fieldsUpdated;
}
