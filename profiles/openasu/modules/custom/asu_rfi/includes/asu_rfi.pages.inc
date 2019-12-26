<?php /** @noinspection PhpInconsistentReturnPointsInspection */
/** @noinspection PhpUnused */
/** @noinspection SqlDialectInspection */
/** @noinspection SqlNoDataSourceInspection */
/** @noinspection PhpIllegalStringOffsetInspection */
/** @noinspection HtmlUnknownTarget */
/** @noinspection PhpUnusedParameterInspection */
/**
 * @file
 * Request info form generation using Form API
 */

// clear page cache
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Cache-Control: no-store, no-cache, must-revalidate");
header("Cache-Control: post-check=0, pre-check=0", FALSE);
header("Pragma: no-cache");

/**
 * INIT configs
 */
module_load_include('inc', 'asu_rfi', 'includes/asu_rfi_email');
module_load_include('inc', 'asu_rfi', 'includes/asu_rfi_post_to_salesforce');

/**
 * Implementation of hook_form().
 * @param $delta
 * @return array|mixed
 */
function asu_rfi_form($delta) {
  // MULTIFORM - Form definition
  return drupal_get_form('asu_rfi_form_data');
}

/** @noinspection PhpUnused */

/**
 * MULTIFORM - Form definition, generation
 * @param $form
 * @param $form_state
 * @return array|mixed
 */
function asu_rfi_form_data($form, &$form_state) {
  // INIT form settings (JS, HTTP headers, etc.)
  _asu_rfi_form_initial_web_assets('multiform');

  ///////////////// Do we want the 2nd form instead? Return second form
  /// from asu_rfi_second_form
  if (isset($form_state['storage'])) {
    if ($form_state['storage']['step'] == 'asu_rfi_second_form') {
      return asu_rfi_second_form($form, $form_state);
    }
  }

  ///////////////// Otherwise, we BUILD THE FIRST FORM below

  $domain = $_SERVER['HTTP_HOST'];
  // Get form options
  $degreeMappings = _asu_rfi_get_degree_field_mappings();
  $start_dates = _asu_rfi_get_sem_dates();
  $country = _asu_rfi_get_country_list();

  // Dates
  for ($idate = 0; $idate < 4; $idate++) {
    $date = date('Y') + $idate;
    $date_key = substr_replace($date, '', 1, -2);
    $year[$date_key] = $date;
  }

  // Load the current node object to get program name and degree type
  $node = menu_get_object();
  if (!empty($node)) {
    if (!empty($degreeMappings)) {
      $field_academic_plan = $degreeMappings['field_academic_plan'];
      $field_degree_awarded = $degreeMappings['field_degree_awarded'];
      $field_degree_program = $degreeMappings['field_degree_program'];
      $field_academic_program = $degreeMappings['field_academic_program'];
      $field_diploma_description = $degreeMappings['field_diploma_description'];
      $academic_plan = &$node->$field_academic_plan;
      $degree_awarded = &$node->$field_degree_awarded;
      $degree_program = &$node->$field_degree_program;
      $academic_program = &$node->$field_academic_program;
      $diploma_description = &$node->$field_diploma_description;
    } else {
      $academic_plan = '';
      $degree_awarded = '';
      $degree_program = '';
      $academic_program = '';
      $diploma_description = '';
    }
    $deg_code = (!empty($academic_plan[LANGUAGE_NONE][0]['value'])) ? $academic_plan[LANGUAGE_NONE][0]['value'] : '';
    $deg_name = (!empty($degree_awarded[LANGUAGE_NONE][0]['value'])) ? $degree_awarded[LANGUAGE_NONE][0]['value'] : '';
    $degree[$deg_code] = $deg_name;
    $college_code = (!empty($academic_program)) ? $academic_program[LANGUAGE_NONE][0]['value'] : "None";
    $college_name = (!empty($diploma_description)) ? $diploma_description[LANGUAGE_NONE][0]['value'] : '';
    $type_degree = (!empty($degree_program[LANGUAGE_NONE][0]['value'])) ? $degree_program[LANGUAGE_NONE][0]['value'] : '';

    $form = array();
    honeypot_add_form_protection($form, $form_state, array(
      'honeypot',
      'time_restriction'
    ));

    // If the session is set for more than 3 min, clear the session data
    if (isset($_SESSION['rfi_data'])) {
      $current_time = time();
      $session_start_time = $_SESSION['rfi_data']['start_time'];
      $session_diff = $current_time - $session_start_time;
      if ($session_diff >= 180) {
        unset($_SESSION['rfi_data']);
        unset($form_state['storage']);
        unset($form_state['values']);
        $form['sess_expire_message'] = array(
          '#type' => 'item',
          '#markup' => '<div class="alert alert-danger" style="padding: 2%;">Your session has expired. Please fill out the form again.</div>',
        );
      }
    }

    // Is the form in "Test Mode"? If so, add markup
    _asu_rfi_form_test_mode_markup($form, $form_state['build_info']['form_id']);

    // Form field definitions
    $form['req_header_text'] = array(
      '#type' => 'item',
      '#markup' => _asu_rfi_form_header_text(),
    );
    $form['req_helper'] = array(
      '#type' => 'item',
      '#markup' => '<p>Fields marked with <span style = "color:black;">*</span> are required.</p>',
      '#size' => 10,
    );
    $form['domain'] = array(
      '#type' => 'hidden',
      '#size' => 30,
      '#maxlength' => 64,
      '#default_value' => $domain,
    );
    $form['degree_type'] = array(
      '#type' => 'hidden',
      '#size' => 30,
      '#maxlength' => 64,
      '#default_value' => $type_degree,
    );
    $form['my_interest'] = array(
      '#type' => 'fieldset',
      '#title' => 'I\'m interested in...',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#size' => 10,
    );
    $form['my_interest']['student_type'] = array(
      '#type' => 'select',
      '#title' => t('I will be a future'),
      '#options' => array(
        'First Time Freshman' => 'First Time Freshman',
        'Transfer' => 'Transfer',
        ' Readmission' => 'Readmission'
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="degree_type"]' => array('value' => 'undergrad'),
        ),
      ),
      '#required' => TRUE,
      '#attributes' => array('class' => array('reqinfo_student_type')),
      '#default_value' => isset($_SESSION['rfi_data']['student_type']) ? $_SESSION['rfi_data']['student_type'] : NULL,
    );
    $form['my_interest']['prog_plan'] = array(
      '#type' => 'textfield',
      '#title' => t('My program of interest'),
      '#required' => TRUE,
      '#default_value' => $deg_name,
      '#disabled' => TRUE,
      '#size' => 30,
    );
    $form['my_interest']['campus'] = array(
      '#type' => 'select',
      '#title' => t('My campus of choice is'),
      '#options' => array(),
      '#required' => TRUE,
      '#attributes' => array('class' => array('reqinfo_campus')),
    );
    $form['program_code'] = array(
      '#type' => 'hidden',
      '#maxlength' => 64,
      '#default_value' => $deg_code,
      '#size' => 50,
    );
    $form['college_name'] = array(
      '#type' => 'hidden',
      '#maxlength' => 128,
      '#default_value' => $college_name,
      '#size' => 50,
    );
    $form['enterpriseclientid'] = array(
      '#type' => 'hidden',
      '#maxlength' => 255,
      // Will be filled in using JS to obtain from GA, per EdPlus.
      // See WEBSPARK-1198.
      '#default_value' => '',
      '#size' => 60,
    );
    $form['my_interest']['start_date'] = array(
      '#type' => 'select',
      '#title' => t('My start date'),
      '#options' => $start_dates,
      '#required' => TRUE,
      '#default_value' => isset($_SESSION['rfi_data']['start_date']) ? $_SESSION['rfi_data']['start_date'] : NULL,
    );
    $form['about_me'] = array(
      '#type' => 'fieldset',
      '#title' => 'About me...',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $form['about_me']['first_name'] = array(
      '#type' => 'textfield',
      '#title' => t('First name'),
      '#size' => 30,
      '#maxlength' => 30,
      '#required' => TRUE,
      '#prefix' => '<div id ="req_info_form">',
      '#default_value' => isset($_SESSION['rfi_data']['first_name']) ? $_SESSION['rfi_data']['first_name'] : NULL,
    );
    $form['about_me']['last_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Last name'),
      '#size' => 30,
      '#maxlength' => 64,
      '#required' => TRUE,
      '#default_value' => isset($_SESSION['rfi_data']['last_name']) ? $_SESSION['rfi_data']['last_name'] : NULL,
    );
    $form['about_me']['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#size' => 30,
      '#maxlength' => 100,
      '#required' => TRUE,
      '#default_value' => isset($_SESSION['rfi_data']['email']) ? $_SESSION['rfi_data']['email'] : NULL,
    );
    $form['about_me']['phone'] = array(
      '#prefix' => '<div class="phone_field_rfi">',
      '#suffix' => '</div>',
      '#type' => 'textfield',
      '#title' => t('Preferred phone number'),
      '#description' => t('USA Format: xxx-xxx-xxxx'),
      '#size' => 30,
      '#maxlength' => 40,
      '#required' => TRUE,
      '#attributes' => array('class' => array('rfi_phone')),
      '#default_value' => isset($_SESSION['rfi_data']['phone']) ? $_SESSION['rfi_data']['phone'] : NULL,
    );
    $form['about_me']['mobile_check'] = array(
      '#type' => 'checkbox',
      '#title' => t('This is a USA mobile number and I would like to receive information via SMS text messaging'),
      '#size' => 30,
      '#maxlength' => 30,
      '#required' => FALSE,
      '#attributes' => array('class' => array('rfi_mobile')),
      '#default_value' => isset($_SESSION['rfi_data']['mobile_check']) ? $_SESSION['rfi_data']['mobile_check'] : NULL,
    );
    $form['about_me']['country'] = array(
      '#id' => 'rfi-country',
      '#type' => 'select',
      '#options' => $country,
      '#title' => t('Country'),
      '#required' => TRUE,
      '#default_value' => isset($_SESSION['rfi_data']['country']) ? $_SESSION['rfi_data']['country'] : NULL,
    );
    $form['about_me']['zipcode'] = array(
      '#type' => 'textfield',
      '#title' => t('Postal code'),
      '#size' => 30,
      '#maxlength' => 15,
      '#states' => array(
        'required' => array(
          ':input[name="country"]' => array('value' => 'United States'),
        ),
      ),
      '#default_value' => isset($_SESSION['rfi_data']['zipcode']) ? $_SESSION['rfi_data']['zipcode'] : NULL,
    );

    // Birthday field disclaimer
    $modal_data = '<!-- Button trigger modal -->
	    <span class="fa fa-info-circle" data-toggle="modal" data-target="#myModal"></span>
	    <!-- Modal -->
	    <div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-hidden="true">
    		<div class="modal-dialog">
		      <div class="modal-content">
			      <div class="modal-body">
			        Your birthday is important! It helps us keep your information secure as a unique identifier for your online submission.
			      </div>
            <div class="modal-footer">
              <div class="btn btn-default" data-dismiss="modal">Close</div>
            </div>
          </div>
        </div>
      </div>';

    // The below field creates illusion as part of date of birth field. I had to
    // add this field to avoid validation error message containing modal data
    $form['about_me']['dob_field'] = array(
      '#type' => 'item',
      '#markup' => '<label><strong>Date of birth <span class="form-required">*</span></strong></label>' . $modal_data,
    );
    $form['about_me']['birthdate'] = array(
      '#type' => 'textfield',
      '#title' => t('Date of birth'),
      '#description' => t('Format: mm/dd/yyyy'),
      '#title_display' => 'invisible',
      '#size' => 30,
      '#maxlength' => 30,
      '#required' => TRUE,
      '#default_value' => isset($_SESSION['rfi_data']['birthdate']) ? $_SESSION['rfi_data']['birthdate'] : NULL,
    );
    $form['ip_address'] = array(
      '#type' => 'hidden',
      '#size' => 30,
      '#maxlength' => 64,
      '#default_value' => $_SERVER['REMOTE_ADDR'],
    );
    $form['college'] = array(
      '#type' => 'hidden',
      '#size' => 30,
      '#maxlength' => 64,
      '#default_value' => $college_code,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#attributes' => array('class' => array('rfi-button')),
      '#submit' => array('asu_rfi_form_data_submit'),
      '#value' => t('Next'),
    );
    return $form;
  }
}


/**
 * MULTIFORM (BOTH)- VALIDATE handler
 * Defaults to FIRST FORM
 * // NOT GETTING DEFINED OR USED??
 *
 * @param $form
 * @param $form_state
 * @return bool
 * @see asu_rfi_first_data().
 */
function asu_rfi_form_data_validate($form, &$form_state) {
  if (isset($form_state['storage'])) {
    if ($form_state['storage']['step'] == 'asu_rfi_second_form') {
      return asu_rfi_second_form_validate($form, $form_state);
    }
  }

  $f_name = $form_state['values']['first_name'];
  $l_name = $form_state['values']['last_name'];
  $email = $form_state['values']['email'];
  $phone = $form_state['values']['phone'];
  $zip = $form_state['values']['zipcode'];
  $country = $form_state['values']['country'];
  $birth_date = $form_state['values']['birthdate'];

  // validate first name
  if (!preg_match("/^[a-zA-Z.\s-_]+$/", $f_name)) {
    form_set_error('first_name', t('First name field accepts only plain text.'));
  }
  // validate last name
  if (!preg_match("/^[a-zA-Z.\s-_]+$/", $l_name)) {
    form_set_error('last_name', t('Last name field accepts only plain text.'));
  }
  // Validation for email and phone
 _asu_rfi_validate_electronic_contacts($email, $phone);

  // validate zip code
  if (empty($zip)) {
    if (!empty($country) && ($country == "United States")) {
      form_set_error('zipcode', t('Postal code field is required.'));
    }
  } else {
    _asu_rfi_validate_zipcode($country, $zip);
  }

  // Validate birth date
  if (!empty($birth_date)) {
    _asu_rfi_validate_birthdate($birth_date);
  } else {
    form_set_error('birthdate', t('Date of birth is required.'));
    form_set_error('dob_field', t(' '));
  }
}

/**
 * MULTIFORM (BOTH) - SUBMIT handler
 * as defined by the form from asu_rfi_form_data().
 * Defaults to FIRST FORM
 * @param $form
 * @param $form_state
 * @throws \Exception
 */
function asu_rfi_form_data_submit($form, &$form_state) {
  // SECOND FORM? Go to other submit
  if (isset($form_state['storage'])) {
    if ($form_state['storage']['step'] == 'asu_rfi_second_form') {
      /** @noinspection PhpVoidFunctionResultUsedInspection */
      return asu_rfi_second_form_submit($form, $form_state);
    }
  }

  // Build session variables to be used later
  $_SESSION['rfi_data'] = $form_state['values'];
  $_SESSION['rfi_data']['start_time'] = time();
  global $user;
  // Save values to the form storage, add the next step function callback
  $form_state['rebuild'] = TRUE;
  $form_state['storage']['domain'] = $form_state['values']['domain'];
  $form_state['storage']['first_name'] = check_plain($form_state['values']['first_name']);
  $form_state['storage']['last_name'] = check_plain($form_state['values']['last_name']);
  $form_state['storage']['phone'] = $form_state['values']['phone'];
  $sms_opted = $form_state['values']['mobile_check'];

  // Check if the phone number already has 1 prepended. If not, prepend with 1.
  if (!empty($sms_opted)) {
    $form_state['storage']['mobile_check'] = (substr($form_state['values']['phone'], 0, 1) != "1")
      ? '1' . $form_state['values']['phone']
      : $form_state['values']['phone'];
  } else {
    $form_state['storage']['mobile_check'] = '';
  }

  $dob_date = $form_state['values']['birthdate'];
  $form_state['storage']['email'] = check_plain($form_state['values']['email']);
  $form_state['storage']['zipcode'] = check_plain($form_state['values']['zipcode']);
  $form_state['storage']['start_date'] = check_plain($form_state['values']['start_date']);
  $form_state['storage']['country'] = check_plain($form_state['values']['country']);
  $form_state['storage']['college_name'] = check_plain($form_state['values']['college_name']);
  $form_state['storage']['enterpriseclientid'] = check_plain($form_state['values']['enterpriseclientid']);
  $form_state['storage']['birthdate'] = $dob_date;

  // get start date array
  $sem_dates = _asu_rfi_get_sem_dates();
  if (array_key_exists($form_state['storage']['start_date'], $sem_dates)) {
    $form_state['storage']['semester_name'] = $sem_dates[$form_state['storage']['start_date']];
  }

  $form_state['storage']['prog_plan'] = check_plain($form_state['values']['prog_plan']);

  if (($form_state['values']['degree_type']) != "undergrad") { // Graduate
    $form_state['values']['student_type'] = ASU_RFI_PROSPECT_LEVEL_GRAD;
    $form_state['storage']['student_type'] = ASU_RFI_PROSPECT_LEVEL_GRAD;
    $multi_form_type = "Graduate multi form";
    $form_state['storage']['prospect_level'] = ASU_RFI_PROSPECT_LEVEL_GRAD;
  }
  else { // Undergraduate
    $form_state['values']['student_type'] = ASU_RFI_PROSPECT_LEVEL_UNDERGRAD;
    $form_state['storage']['student_type'] = $form_state['values']['student_type'];
    $multi_form_type = "Undergraduate multi form";
    $form_state['storage']['prospect_level'] = ASU_RFI_PROSPECT_LEVEL_UNDERGRAD;
  }

  $form_state['storage']['campus'] = $form_state['values']['campus'];
  $form_state['storage']['ip_address'] = $form_state['values']['ip_address'];
  $form_state['storage']['college_code'] = $form_state['values']['college'];
  $form_state['storage']['program_code'] = $form_state['values']['program_code'];
  //$ip_address = $form_state['values']['ip_address']; // UNUSED

  $current_time = time();
  $form_state['storage']['submit_time'] = $current_time;
  $unique_id = $form_state['values']['first_name'] . $form_state['values']['email']
    . $form_state['values']['prog_plan'];

  // Check for duplicate submissions - check_duplicate never used
  // by looking to see if unique id already exists in the database
  $node_unique = db_select('field_data_field_rfi_uniquedata', 'afu')
    ->fields('afu')
    ->condition('field_rfi_uniquedata_value', $unique_id, '=')
    ->execute()
    ->fetchField();

  // If unique id doesn't exist, create the RFI submission node...
  if (empty($node_unique)) {
    $ent_values = array(
      'type' => 'asu_rfi',
      'uid' => $user->uid,
      'status' => 0,
      'comment' => 1,
      'promote' => 0,
    );
    $entity = entity_create('node', $ent_values);

    // ...and update new submission entity/node field values using entity_metadata_wrapper.
    _asu_rfi_update_multiform_submission_fields($entity, $form_state, $multi_form_type, $dob_date, $unique_id);

    $form_state['storage']['submission_nodeid'] = $entity->nid;
    $form_state['storage']['step'] = 'asu_rfi_second_form';

    // Then send the email
    if ($form_state['storage']['prospect_level'] == ASU_RFI_PROSPECT_LEVEL_GRAD) { // graduate
      asu_rfi_grad_email($form_state['storage']['program_code'],
        $form_state['storage']['email'],
        $form_state['storage']['first_name']);
    } else { // undergrad
      asu_rfi_undergrad_email($form_state['storage']['program_code'],
        $form_state['storage']['email'],
        $form_state['storage']['first_name']);
    }
  }

  // Or update the existing submission node.
  else {
    $get_nodeid = db_select('field_data_field_rfi_uniquedata', 'afu')
      ->fields('afu', array('entity_id'))
      ->condition('field_rfi_uniquedata_value', $unique_id, '=')
      ->execute()
      ->fetchField();

    // Update ASU RFI node values
    $node = node_load($get_nodeid);
    _asu_rfi_update_multiform_submission_fields($node, $form_state, $multi_form_type, $dob_date, $unique_id);

    $form_state['storage']['submission_nodeid'] = $get_nodeid;
    $form_state['storage']['step'] = 'asu_rfi_second_form';
  }
}

/**
 * MULTIFORM - SECOND FORM - Construct the second form
 * @param $form
 * @param $form_state
 * @return mixed
 */
function asu_rfi_second_form($form, &$form_state) {

  // JS, HTTP header INIT ALREADY DONE IN asu_rfi_form_data call

  $current_time = time();
  $session_start_time = $_SESSION['rfi_data']['start_time'];
  $session_diff = $current_time - $session_start_time;
  if ($session_diff >= 180) {
    unset($form_state['storage']);
  }

  if (isset($_SESSION['rfi_data'])) {
    $current_time = time();
    $session_start_time = $_SESSION['rfi_data']['start_time'];
    $session_diff = $current_time - $session_start_time;

    if ($session_diff >= 180) {
      unset($_SESSION['rfi_data']);
      unset($form_state['values']);
      unset($form_state['storage']);
      $form['sess_expire_message'] = array(
        '#type' => 'item',
        '#markup' => '<div class="alert-danger" style="padding:2%;">Your session has expired. Please fill out the form again.</div>',
      );
      $form_state['storage']['step'] = 'asu_rfi_form_data';
    }
  }

  $states = _asu_rfi_get_state_list();
  honeypot_add_form_protection($form, $form_state, array(
    'honeypot',
    'time_restriction'
  ));

  // FORM SETTINGS, FIELDS

  $form['#id'] = 'asu_rfi_second_form';
  $form['#prefix'] = '<div id="rfi-second-form">';
  $form['#suffix'] = '</div>';

  // If the form in "Test Mode", add Test mode warning message markup
  _asu_rfi_form_test_mode_markup($form, $form_state['build_info']['form_id']);

  // Thank you for submitting first part of form messaging.
  $thanks_msg = _asu_rfi_multiform_thanks_part1();
  drupal_set_message($thanks_msg, 'success', FALSE);

  $form['citizenship'] = array(
    '#type' => 'checkbox',
    '#title' => t('I am not a U.S. citizen and do not have a green card.'),
  );
  $form['military'] = array(
    '#type' => 'radios',
    '#title' => t('U.S. Veteran admission information and services'),
    '#options' => array(
      "None" => "None",
      "Active Duty" => "Active Duty",
      "National Guard" => "National Guard",
      "Veteran" => "Veteran",
      "Armed forces reserve" => "Armed forces reserve",
      "Spouse/Dependent" => "Spouse/Dependent"
    ),
    '#size' => 30,
  );
  if (isset($_SESSION['rfi_data']) && isset($_SESSION['rfi_data']['country']) && ($_SESSION['rfi_data']['country'] == "United States" || $_SESSION['rfi_data']['country'] == "Canada")) {
    $form['address_info'] = array(
      '#type' => 'fieldset',
      '#title' => 'Please also send me information to the following address...',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $form['address_info']['country'] = array(
      '#type' => 'textfield',
      '#title' => 'Country',
      '#size' => 30,
      '#maxlength' => 64,
      '#attributes' => array(
        'disabled' => TRUE,
      ),
      '#default_value' => $_SESSION['rfi_data']['country'],
    );
    $form['address_info']['address'] = array(
      '#type' => 'textfield',
      '#title' => t('Address'),
      '#size' => 30,
      '#maxlength' => 64,
    );
  $form['address_info']['city'] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#size' => 30,
      '#maxlength' => 30,
    );
  $form['address_info']['state'] = array(
      '#id' => 'rfi-state',
      '#type' => 'select',
      '#options' => $states,
      '#title' => t('State/Province'),
      '#required' => FALSE,
      '#default_value' => isset($_SESSION['rfi_data']['state']) ? $_SESSION['rfi_data']['state'] : NULL,
    );
  $form['address_info']['zipcode'] = array(
      '#type' => 'textfield',
      '#title' => t('Postal code'),
      '#size' => 30,
      '#maxlength' => 15,
      '#default_value' => $form_state['storage']['zipcode'],
    );
  }
  $form['questions'] = array(
    '#type' => 'textarea',
    '#title' => t('I also need assistance with the following:'),
    '#cols' => 60,
    '#resizable' => TRUE,
    '#rows' => 5,
    '#description' => '(Limit of 255 characters)',
  );
  $form['webform_url'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => $_SERVER['HTTP_HOST'],
  );
  $form['first_enity_id'] = array(
    '#type' => 'hidden',
    '#default_value' => $form_state['storage']['submission_nodeid'],
  );
  $form['type_of_form'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => 'MF',
  );
  $form['gdpr_message'] = array(
    '#type' => 'item',
    '#markup' => _asu_rfi_get_gdpr_markup()
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#attributes' => array('class' => array('rfi-button')),
    '#value' => t('I Agree / Submit'),
  );
  $form['back'] = array(
    '#type' => 'submit',
    '#attributes' => array('class' => array('rfi-button')),
    '#value' => t('Back'),
    '#submit' => array('asu_rfi_form_data'),
  );

  return $form;
}

/**
 * MULTIFORM SECOND FORM - Validation handler
 * @param $form
 * @param $form_state
 * @return bool
 */
function asu_rfi_second_form_validate($form, &$form_state) {
  // When Back button on multi-step form is clicked, skip validation on the current page
  if ($form_state['values']['op'] == 'Back') {
    drupal_get_messages('error');
    drupal_add_js("$('html, body').animate({ scrollTop: $('#asu-rfi-form-data').offset().top - 100}, 1000);", 'inline');
    return TRUE;
  }
  $country = $form_state['storage']['country'];
  $address = check_plain($form_state['values']['address']);
  $city = check_plain($form_state['values']['city']);
  // $state = check_plain($form_state['values']['state']);
  $zip = check_plain($form_state['values']['zipcode']);
  // validate address
  if (!empty($address)) {
    if (!preg_match("/^[a-zA-Z0-9.\s-_,#]+$/", $address)) {
      form_set_error('address', t('Address field accepts only plain text.'));
    }
  }
  // validate city
  if (!empty($city)) {
    if (!preg_match('/^[\p{L}\p{N} .-]+$/u', $city)) {
      form_set_error('city', t('City is invalid.'));
    }
  }

  // validate zip code
  if (empty($zip)) {
    if (!empty($country) && ($country == "United States")) {
      form_set_error('zipcode', t('Postal code field is required.'));
    }
  } else {
    _asu_rfi_validate_zipcode($country, $zip);
  }

  // validate comments
  if (!empty($form_state['values']['questions'])) {
    if (strlen($form_state['values']['questions']) > 255) {
      form_set_error('questions', t('Comments are limited to a maximum of 255 characters.'));
    }
  }
}

/**
 * MULTIFORM - SECOND FORM submit (for undergrad and grad students)
 * @param $form
 * @param $form_state
 * @throws \Exception
 */
function asu_rfi_second_form_submit($form, &$form_state) {
  unset($_SESSION['rfi_data']);

  $zipcode = check_plain($form_state['values']['zipcode']);
  $country = $form_state['storage']['country'];
  //$student_type = $form_state['storage']['student_type']; // unused??
  $address = check_plain($form_state['values']['address']);
  $form_state['storage']['address'] = $address;

  //$email = check_plain($form_state['storage']['email']); // UNUSED??
  //$major = $form_state['storage']['prog_plan']; // UNUSED?
  // $unique_id = $email . $major; // UNUSED??
  // $webform_url = $form_state['values']['webform_url']; // unused??
  // $ip_address = $form_state['storage']['ip_address']; // unused??

  // Make sure various fields have been updated in the second form
  $form_state['storage']['zipcode'] = $zipcode;
  $city = check_plain($form_state['values']['city']);
  $form_state['storage']['city'] = $city;
  $state = ($form_state['values']['state'] == '0') ? '' : $form_state['values']['state'];
  $form_state['storage']['state'] = $state;
  $veteran = $form_state['values']['military'];
  $form_state['storage']['military'] = $veteran;

  $citizen = $form_state['values']['citizenship'];
  $node_entity_id = $form_state['storage']['submission_nodeid'];
  $form_state['storage']['type_of_form'] = $form_state['values']['type_of_form'];

  $international = (empty($citizen)) ? "FALSE" : "TRUE";
  $form_state['storage']['citizenship'] = $international;
  $military = (!empty($veteran)) ? $form_state['values']['military'] : "";
  $form_state['storage']['military'] = $military;

  $questions = check_plain($form_state['values']['questions']);
  $form_state['storage']['questions'] = $questions;
  //$current_time = time(); // unused??

  $node = node_load($node_entity_id);
  $node->field_rfi_state[LANGUAGE_NONE][0]['value'] = $state;
  $node->field_rfi_veteran[LANGUAGE_NONE][0]['value'] = $veteran;
  $node->field_rfi_question[LANGUAGE_NONE][0]['value'] = check_plain($questions);
  $node->field_rfi_submission_status[LANGUAGE_NONE][0]['value'] = 'Form_Completed';
  $node->field_rfi_address[LANGUAGE_NONE][0]['value'] = $address;
  $node->field_rfi_city[LANGUAGE_NONE][0]['value'] = $city;
  $node->field_rfi_international[LANGUAGE_NONE][0]['value'] = $international;
  $node->field_rfi_zipcode[LANGUAGE_NONE][0]['value'] = $zipcode;
  node_save($node);

  // Info used in confirmation nodes
  $coded_nid = base64_encode($node_entity_id);
  $coded_major = base64_encode($form_state['storage']['program_code']);
  $coded_college = base64_encode($form_state['storage']['college_name']);
  $coded_college_code = base64_encode($form_state['storage']['college_code']);
  $coded_zip = base64_encode($zipcode);
  $coded_country = base64_encode($country);

  /* If undergraduate degree is submitted, route the from to undergraduate posting
   * function below.
   * Grab the node id of information page from admin settings page if exists and
   * redirect the user to confirmation node.
   * If the node id doesn't exist, redirect the user to builtin confirmation page.
   */
  if ($form_state['storage']['prospect_level'] == ASU_RFI_PROSPECT_LEVEL_UNDERGRAD) {
    asu_rfi_post_to_middleware($form_state['storage'], ASU_RFI_PROSPECT_LEVEL_UNDERGRAD); //-- To be used in future
    $undergrad_conf_id = ASU_RFI_UNDERGRAD_CONFIRMATION_NID;

    if ($undergrad_conf_id && $undergrad_conf_id !== 0 ) {
      $u_alias = drupal_lookup_path('alias', $path = "node/$undergrad_conf_id", $path_language = NULL);
      if (!empty($u_alias)) {
        drupal_goto("$u_alias", array(
          'query' => array(
            'pro' => $coded_college,
            'maj' => $coded_major,
            'sub' => $coded_nid,
            'ccode' => $coded_college_code,
            'cat' => 'UG RFI',
            'zcode' => $coded_zip,
            'con' => $coded_country
          )
        ));
      } else {
        drupal_goto("node/$undergrad_conf_id", array(
          'query' => array(
            'pro' => $coded_college,
            'maj' => $coded_major,
            'sub' => $coded_nid,
            'ccode' => $coded_college_code,
            'cat' => 'UG RFI',
            'zcode' => $coded_zip,
            'con' => $coded_country
          )
        ));
      }
    } else {
      drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
    }
    unset($_SESSION['rfi_data']);
  }

  /* If graduate degree is submitted, root the from to graduate posting function.
   * Grab the node id of information page from admin settings page if it exists and
   * redirect the user to confirmation node. If the node id doesn't exist, take
   * the user to built in confirmation page.
   */
  if ($form_state['storage']['prospect_level'] == ASU_RFI_PROSPECT_LEVEL_GRAD) {
    asu_rfi_post_to_middleware($form_state['storage'], ASU_RFI_PROSPECT_LEVEL_GRAD);
    $grad_conf_id = ASU_RFI_GRAD_CONFIRMATION_NID;
    if (isset($grad_conf_id) && (int) $grad_conf_id !== 0) {
      $galias = drupal_lookup_path('alias', $path = "node/$grad_conf_id", $path_language = NULL);
      if (!empty($alias)) {
        drupal_goto("$galias", array(
          'query' => array(
            'pro' => $coded_college,
            'maj' => $coded_major,
            'sub' => $coded_nid,
            'ccode' => $coded_college_code,
            'cat' => 'Grad RFI',
            'zcode' => $coded_zip,
            'con' => $coded_country
          )
        ));
      } else {
        drupal_goto("node/$grad_conf_id", array(
          'query' => array(
            'pro' => $coded_college,
            'maj' => $coded_major,
            'sub' => $coded_nid,
            'ccode' => $coded_college_code,
            'cat' => 'Grad RFI',
            'zcode' => $coded_zip,
            'con' => $coded_country
          )
        ));
      }
    } else {
      drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
    }
    //clear session data
    unset($_SESSION['rfi_data']);
  }
}

/**
 * MULTIFORM - Updates fields in entity/node generated by form submission,
 * using entity_metadata_wrapper().
 *
 * @param $entity - submission entity/node
 * @param $form_state
 * @param $multi_form_type
 * @param $dob_date
 * @param $unique_id -
 */
function _asu_rfi_update_multiform_submission_fields($entity, $form_state, $multi_form_type, $dob_date, $unique_id) {
  $wrapper = entity_metadata_wrapper('node', $entity);
  if (isset($wrapper->title)) {
    $wrapper->title->set($form_state['storage']['first_name']);
  }
  if (isset($wrapper->field_rfi_domain)) {
    $wrapper->field_rfi_domain->set($form_state['storage']['domain']);
  }
  if (isset($wrapper->field_rfi_first_name)) {
    $wrapper->field_rfi_first_name->set($form_state['storage']['first_name']);
  }
  if (isset($wrapper->field_rfi_last_name)) {
    $wrapper->field_rfi_last_name->set($form_state['storage']['last_name']);
  }
  if (isset($wrapper->field_rfi_student_type)) {
    $wrapper->field_rfi_student_type->set($form_state['storage']['student_type']);
  }
  if (isset($wrapper->field_rfi_email)) {
    $wrapper->field_rfi_email->set($form_state['storage']['email']);
  }
  if (isset($wrapper->field_rfi_phone)) {
    $wrapper->field_rfi_phone->set($form_state['storage']['phone']);
  }
  if (isset($wrapper->field_rfi_country)) {
    $wrapper->field_rfi_country->set($form_state['storage']['country']);
  }
  if (isset($wrapper->field_rfi_zipcode)) {
    $wrapper->field_rfi_zipcode->set($form_state['storage']['zipcode']);
  }
  if (isset($wrapper->field_rfi_start_term_code)) {
    $wrapper->field_rfi_start_term_code->set($form_state['storage']['start_date']);
  }
  if (isset($wrapper->field_rfi_program)) {
    $wrapper->field_rfi_program->set($form_state['storage']['program_code']);
  }
  if (isset($wrapper->field_rfi_form_type)) {
    $wrapper->field_rfi_form_type->set($multi_form_type);
  }
  if (isset($wrapper->field_rfi_ip_address)) {  // IP address == (int)? Who did this and why???
    $wrapper->field_rfi_ip_address->set(intval($form_state['storage']['ip_address']));
  }
  if (isset($wrapper->field_rfi_college_code)) {
    $wrapper->field_rfi_college_code->set($form_state['storage']['college_code']);
  }
  if (isset($wrapper->field_rfi_submission_status)) {
    $wrapper->field_rfi_submission_status->set('Form_Multi_Partial');
  }
  if (isset($wrapper->field_rfi_dob)) {
    $wrapper->field_rfi_dob->set(base64_encode($dob_date));
  }
  if (isset($wrapper->field_rfi_uniquedata)) {
    $wrapper->field_rfi_uniquedata->set($unique_id);
  }
  if (isset($wrapper->field_rfi_start_term)) {
    $wrapper->field_rfi_start_term->set($form_state['storage']['semester_name']);
  }
  if (isset($wrapper->field_rfi_sms_opted)) {
    $wrapper->field_rfi_sms_opted->set($form_state['storage']['mobile_check']);
  }
  if (isset($wrapper->field_rfi_program_name)) {
    $wrapper->field_rfi_program_name->set($form_state['storage']['prog_plan']);
  }
  if (isset($wrapper->field_rfi_college_name)) {
    $wrapper->field_rfi_college_name->set($form_state['storage']['college_name']);
  }
  if (isset($wrapper->field_rfi_enterpriseclientid)) {
    $wrapper->field_rfi_enterpriseclientid->set($form_state['storage']['enterpriseclientid']);
  }
  if (isset($wrapper->field_rfi_prospect_level)) {
    $wrapper->field_rfi_prospect_level->set($form_state['storage']['prospect_level']);
  }
  if (isset($wrapper->field_rfi_campus)) {
    $wrapper->field_rfi_campus->set($form_state['storage']['campus']);
  }
  $wrapper->save();
}

/**
 * LONG FORM RFI generation
 * @param $delta
 * @param $programs
 * @param $form_type
 * @return array|mixed
 */
function asu_rfi_long_form($delta, $programs, $form_type) {
  return drupal_get_form('asu_rfi_long_form_data', $programs, $form_type);
}

/**
 * LONG FORM - Form API construction of the form
 * @param $form
 * @param $form_state
 * @param $programs
 * @param $form_type
 * @return array
 */
function asu_rfi_long_form_data($form, &$form_state, $programs, $form_type) {

  _asu_rfi_form_initial_web_assets('long_form');

  $form = array();
  $start_dates = _asu_rfi_get_sem_dates();
  $country = _asu_rfi_get_country_list();
  $states = _asu_rfi_get_state_list();
  for ($idate = 0; $idate < 4; $idate++) {
    $date = date('Y') + $idate;
    $date_key = substr_replace($date, '', 1, -2);
    $year[$date_key] = $date;
  }

  honeypot_add_form_protection($form, $form_state, array(
    'honeypot',
    'time_restriction'
  ));

  _asu_rfi_form_test_mode_markup($form, $form_state['build_info']['form_id']);

  $form['req_header_text'] = array(
    '#value' => _asu_rfi_form_header_text(),
  );
  $form['req_helper'] = array(
    '#value' => '<p>Fields marked with <span style = "color:black;">*</span> are required.</p>',
  );
  $form['domain'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => (string) $_SERVER['HTTP_HOST'],
  );
  $form['degree_type'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => $form_type,
  );
  $form['my_interest'] = array(
    '#type' => 'fieldset',
    '#title' => 'I\'m interested in...',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#size' => 10,
  );
  $form['my_interest']['location'] = array(
    '#type' => 'radios',
    '#title' => t('Location'),
    '#options' => array(
      'on_campus' => t('On Campus'),
      'online' => t('Online'),
      'no_preference' => t('No Preference')
    ),
    '#default_value' => 'no_preference',
    '#required' => TRUE,
  );

  if (count($programs) == 1) {
    $form['my_interest']['program_code'] = array(
      '#type' => 'select',
      '#title' => t('My program of interest'),
      '#options' => $programs,
      '#attributes' => array('class' => array('chosen-disable')),
      '#states' => array(
        'required' => array(
          ':input[name="degree_type"]' => array('value' => 'graduate_longform'),
        ),
      ),
    );
  } else {
    $form['my_interest']['program_code'] = array(
      '#type' => 'select',
      '#title' => t('My program of interest'),
      '#options' => $programs,
      "#empty_option" => t('- Select -'),
      '#attributes' => array('class' => array('chosen-disable')),
      '#states' => array(
        'required' => array(
          ':input[name="degree_type"]' => array('value' => 'graduate_longform'),
        ),
      ),
    );
  }
  $form['my_interest']['campus'] = array(
    '#type' => 'select',
    '#title' => t('My campus of choice is'),
    '#options' => array(),
    '#attributes' => array(
      'class' => array(
        'reqinfo_campus',
        'chosen-disable'
      )
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="location"]' => array('value' => 'on_campus'),
      ),
      'optional' => array(
        ':input[name="program_code"]' => array('value' => ''),
      ),
      'disabled' => array(
        ':input[name="program_code"]' => array('value' => ''),
      ),
    ),
    "#empty_option" => t('- Select -'),
  );
  $form['my_interest']['student_type'] = array(
    '#type' => 'select',
    '#title' => t('I will be a future'),
    '#options' => array(
      'First Time Freshman' => 'First Time Freshman',
      'Transfer' => 'Transfer',
      ' Readmission' => 'Readmission'
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="degree_type"]' => array('value' => 'ugrad_longform'),
      ),
      'optional' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
    '#attributes' => array(
      'class' => array(
        'reqinfo_student_type',
        'chosen-disable'
      )
    ),
    "#empty_option" => t('- Select -'),
  );
  $form['my_interest']['start_date'] = array(
    '#type' => 'select',
    '#title' => t('My start date'),
    '#options' => $start_dates,
    '#attributes' => array('class' => array('chosen-disable')),
    '#states' => array(
      'optional' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
      'invisible' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
    "#empty_option" => t('- Select -'),
  );
  $form['about_me'] = array(
    '#type' => 'fieldset',
    '#title' => 'About me...',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['about_me']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#size' => 30,
    '#maxlength' => 50,
    '#required' => TRUE,
    '#prefix' => '<div id ="req_info_form">',
  );
  $form['about_me']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#size' => 30,
    '#maxlength' => 50,
    '#required' => TRUE,
  );
  $form['about_me']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 30,
    '#maxlength' => 100,
    '#required' => TRUE,
  );
  $form['about_me']['phone'] = array(
    '#prefix' => '<div class="phone_field_rfi">',
    '#suffix' => '</div>',
    '#type' => 'textfield',
    '#title' => t('Preferred phone number'),
    '#description' => t('USA Format: xxx-xxx-xxxx'),
    '#size' => 30,
    '#maxlength' => 40,
    '#required' => TRUE,
    '#attributes' => array('class' => array('rfi_phone')),
  );
  $form['about_me']['mobile_check'] = array(
    '#type' => 'checkbox',
    '#title' => t('This is a USA mobile number and I would like to receive information via SMS text messaging'),
    '#size' => 30,
    '#maxlength' => 20,
    '#required' => FALSE,
    '#attributes' => array('class' => array('rfi_mobile')),
    '#states' => array(
      'invisible' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
  );
  $form['about_me']['country'] = array(
    '#id' => 'rfi-country',
    '#type' => 'select',
    '#options' => $country,
    '#title' => t('Country'),
    '#attributes' => array('class' => array('chosen-disable')),
    '#states' => array(
      'invisible' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
      'optional' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
    "#empty_option" => t('- Select -'),
  );
  $form['about_me']['zipcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#size' => 30,
    '#maxlength' => 15,
    '#states' => array(
      'required' => array(
        ':input[name="country"]' => array('value' => 'United States'),
      ),
      'invisible' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
  );

  //include modal help text for date of birth
  $modal_data = '<!-- Button trigger modal -->
    <span class="fa fa-info-circle" data-toggle="modal" data-target="#myModal"></span>
    <!-- Modal -->
    <div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-hidden="true">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-body">
            Your birthday is important! Not only will we send you a birthday message, 
            it helps us keep your information secure as a unique identifier for your online submission.
          </div>
          <div class="modal-footer">
            <div class="btn btn-default" data-dismiss="modal">Close</div>
          </div>
        </div>
      </div>
    </div>';

  // The below field creates illusion as part of date of birth field. I had to add
  // this field to avoid validation error message containing modal data.
  $form['about_me']['dob_field'] = array(
    '#type' => 'item',
    '#markup' => '<label><strong>Date of birth</strong></label> ' . $modal_data,
    '#states' => array(
      'optional' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
      'invisible' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
  );
  $form['about_me']['birthdate'] = array(
    '#type' => 'textfield',
    '#title' => t('Date of birth'),
    '#description' => t('Format: mm/dd/yyyy'),
    '#title_display' => 'invisible',
    '#size' => 30,
    '#maxlength' => 30,
    '#states' => array(
      'optional' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
      'invisible' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
  );
  $form['ip_address'] = array(
    '#type' => 'hidden',
    '#size' => 20,
    '#maxlength' => 64,
    '#default_value' => $_SERVER['REMOTE_ADDR'],
  );
  $form['about_me']['citizenship'] = array(
    '#type' => 'checkbox',
    '#title' => t('I am not a U.S. citizen and do not have a green card.'),
    '#states' => array(
      'invisible' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
  );
  $form['about_me']['military'] = array(
    '#type' => 'radios',
    '#title' => t('U.S. Veteran admission information and services'),
    '#options' => array(
      "None" => "None",
      "Active Duty" => "Active Duty",
      "National Guard" => "National Guard",
      "Veteran" => "Veteran",
      "Armed forces reserve" => "Armed forces reserve",
      "Spouse/Dependent" => "Spouse/Dependent"
    ),
    '#size' => 30,
    '#states' => array(
      'invisible' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
  );
  $form['address_info'] = array(
    '#type' => 'fieldset',
    '#title' => 'Please also send me information to the following address...',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'invisible' => array(
        ':input[name="location"]' => array('value' => 'online'),
      ),
    ),
  );
  $form['address_info']['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 30,
    '#maxlength' => 64,
  );
  $form['address_info']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 30,
    '#maxlength' => 30,
  );
  $form['address_info']['state'] = array(
    '#id' => 'rfi-state',
    '#type' => 'select',
    '#options' => $states,
    '#title' => t('State/Province'),
    '#required' => FALSE,
  );
  $form['questions'] = array(
    '#type' => 'textarea',
    '#title' => t('I also need assistance with the following:'),
    '#cols' => 60,
    '#resizable' => TRUE,
    '#rows' => 5,
    '#description' => '(Limit of 255 characters)',
  );
  $form['webform_url'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => $_SERVER['HTTP_HOST'],
  );
  $form['ip_address'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => $_SERVER['REMOTE_ADDR'],
  );
  $form['type_of_form'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => 'LF',
  );
  $form['enterpriseclientid'] = array(
    '#type' => 'hidden',
    '#maxlength' => 255,
    // Will be filled in using JS to obtain from GA, per EdPlus.
    // See WEBSPARK-1198.
    '#default_value' => '',
    '#size' => 60,
  );
  $form['gdpr_message'] = array(
    '#type' => 'item',
    '#markup' => _asu_rfi_get_gdpr_markup()
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('I Agree / Submit'),
    '#attributes' => array('class' => array('rfi-button')),
  );
  return $form;

}

/**
 * LONG FORM - Validation for ugrad and graduate RFI forms
 * @param $form
 * @param $form_state
 */
function asu_rfi_long_form_data_validate($form, &$form_state) {

  if ($form_state['input']['degree_type'] == 'graduate_longform' || $form_state['input']['location'] == 'online') {
    if (empty($form_state['input']['program_code'])) {
      form_set_error('program_code', t('My program of interest field required.'));
    }
  }
  if (!_asu_rfi_program_location_confirm($form_state['input']['program_code'], $form_state['input']['campus'], $form_state['input']['location'])) {
    form_set_error('campus', t('Your campus choice is not valid.'));
  }

  //// Shared form elements to validate
  $student_type = $form_state['values']['student_type'];
  $f_name = $form_state['values']['first_name'];
  $f_name = ucfirst($f_name);
  $l_name = $form_state['values']['last_name'];
  $l_name = ucfirst($l_name);
  $email = $form_state['values']['email'];
  $phone = $form_state['values']['phone'];

  // validate first name
  if (!preg_match("/^[a-zA-Z.\s-_]+$/", $f_name)) {
    form_set_error('first_name', t('First name field accepts only plain text.'));
  }
  // validate last name
  if (!preg_match("/^[a-zA-Z.\s-_]+$/", $l_name)) {
    form_set_error('last_name', t('Last name field accepts only plain text.'));
  }
  // validation for email and phone
  _asu_rfi_validate_electronic_contacts($email, $phone);

  // Custom fields per student type (online vs. all others)

  // ONLY Online student validation
  if (strtolower($form_state['input']['location']) == 'online') {
    // No fields not already included in shared validation above
  }

  // ONLY On-campus student validation
  else {
    $address = check_plain($form_state['values']['address']);
    $city = check_plain($form_state['values']['city']);
    $zip = $form_state['values']['zipcode'];
    $country = $form_state['values']['country'];
    $questions = check_plain($form_state['values']['questions']);
    $birth_date = $form_state['values']['birthdate'];
    $startDate = $form_state['values']['start_date'];

    if (empty($startDate)) {
      form_set_error('start_date', 'My start date field is required.');
    }
    if ($form_state['input']['degree_type'] !== 'graduate_longform') {
      if (empty($student_type)) {
        form_set_error('student_type', 'I will be a future field required.');
      }
    }
    if (empty($country)) {
      form_set_error('country', 'The Country field is required.');
    }
    // validate zip code
    if (empty($zip)) {
      if (!empty($country) && ($country == "United States")) {
        form_set_error('zipcode', t('Postal code field is required.'));
      }
    } else {
      _asu_rfi_validate_zipcode($country, $zip);
    }

    // Validate birth date
    if (!empty($birth_date)) {
      _asu_rfi_validate_birthdate($birth_date);
    } else {
      form_set_error('birthdate', t('Date of birth is required.'));
      form_set_error('dob_field', t(' '));
    }

    // validate address
    if (!empty($address)) {
      if (!preg_match("/^[a-zA-Z0-9.\s-_,#]+$/", $address)) {
        form_set_error('address', t('Address field accepts only plain text.'));
      }
    }
    // validate city
    if (!empty($city)) {
      if (!preg_match('/^[\p{L}\p{N} .-]+$/u', $city)) {
        form_set_error('city', t('City is invalid.'));
      }
    }
    // validation for questions
    if (!empty($questions)) {
      $len = strlen($questions); // validation for comments character limit to 255
      if ($len > 255) {
        form_set_error('questions', t('Comments are limited to a maximum of 255 characters.'));
      }
    }
  }
}

/**
 * LONG FORM - SUBMIT handler (undergrad and graduate)
 * @param $form
 * @param $form_state
 */
function asu_rfi_long_form_data_submit($form, &$form_state) {
  global $user;
  $degreeMappings = _asu_rfi_get_degree_field_mappings();

  // Get the type of the form. If the form is grad form, set prospect_level
  // value to "Graduate", else "Undergraduate"

  // @TODO - deal with Current Student forms
  $tof_data = _asu_rfi_get_type_of_form($form_state);
  $long_form_type = $tof_data['form_type'];
  $student_type = $tof_data['student_type'];

  ////////////////////////////////////////////
  // Bio information
  $f_name = check_plain($form_state['values']['first_name']);
  $l_name = check_plain($form_state['values']['last_name']);
  $dob_date = $form_state['values']['birthdate'];
  $email = check_plain($form_state['values']['email']);
  $phone = $form_state['values']['phone'];

  // Texting ok?
  $sms_opted = $form_state['values']['mobile_check'];
  if (!empty($sms_opted)) {
    // Check if the phone number already has 1 prepended. If not, prepend with 1.
    $form_state['values']['mobile_check'] = (substr($form_state['values']['phone'], 0, 1) != "1")
      ? '1' . $form_state['values']['phone']
      : $form_state['values']['phone'];
  } else {
    $form_state['values']['mobile_check'] = '';
  }
  $sms_number = $form_state['values']['mobile_check'];

  // Campus information
  $location = $form_state['values']['location'];
  $campus = $form_state['values']['campus'];
  $enterpriseclientid = $form_state['values']['enterpriseclientid'];
  $ip_address = $form_state['values']['ip_address'];
  $domain = check_plain($form_state['values']['domain']);

  // Address/location
  $address = check_plain($form_state['values']['address']);
  $city = check_plain($form_state['values']['city']);
  $state = ($form_state['values']['state'] == '0') ? '' : $form_state['values']['state'];
  $form_state['values']['state'] = $state;
  $zip = check_plain($form_state['values']['zipcode']);
  $country = (!empty($form_state['values']['country'])) ? check_plain($form_state['values']['country']) : '';

  // Questions
  $questions = (!empty($form_state['values']['questions'])) ? check_plain($form_state['values']['questions']) : '';

  // Citizenship
  if (empty($form_state['values']['citizenship'])) {
    $international = "FALSE";
    $form_state['values']['citizenship'] = "FALSE";
  } else {
    $international = "TRUE";
    $form_state['values']['citizenship'] = "TRUE";
  }
  // Veteran status
  $veteran = (!empty($form_state['values']['military'])) ? $form_state['values']['military'] : '';

  // Semester start dates
  $semester = check_plain($form_state['values']['start_date']);
  $sem_dates = _asu_rfi_get_sem_dates();
  $semester_name = (array_key_exists($semester, $sem_dates)) ? $sem_dates[$semester] : '';
  $form_state['values']['semester_name'] = (!empty($semester_name)) ? $semester_name : '';

  // Get program name based on the program code submitted in the form
  $program = $form_state['values']['program_code'];
  $program_name = db_query('select ' . $degreeMappings['field_degree_awarded_value'] . ' from ' . $degreeMappings['table_asu_degree_awarded'] . ' mj join ' . $degreeMappings['table_asu_academic_plan'] . ' ap on mj.entity_id = ap.entity_id where ap.' . $degreeMappings['field_academic_plan_value'] . ' = :plan', array(':plan' => $program))->fetchField();
  // Get college code from database based on program code
  $college_code = db_query('select ' . $degreeMappings['field_academic_program_value'] . ' from ' . $degreeMappings['table_asu_academic_program'] . ' prog join ' . $degreeMappings['table_asu_academic_plan'] . ' plan on prog.entity_id = plan.entity_id where plan.' . $degreeMappings['field_academic_plan_value'] . ' = :plancode', array(':plancode' => $program))->fetchField();
  // Get college name from database based on program code
  $college_name = db_query('select ' . $degreeMappings['field_diploma_description_value'] . ' from ' . $degreeMappings['table_asu_diploma_description'] . ' progn join ' . $degreeMappings['table_asu_academic_plan'] . ' plann on progn.entity_id = plann.entity_id where plann.' . $degreeMappings['field_academic_plan_value'] . ' = :plancode', array(':plancode' => $program))->fetchField();

  ////////////////////////////////////////////
  // Create new RFI submission node
  $ent_values = array(
    'type' => 'asu_rfi',
    'uid' => $user->uid,
    'status' => 0,
    'comment' => 1,
    'promote' => 0,
  );
  $entity = entity_create('node', $ent_values);

  // Now insert data into new RFI submission node
  $wrapper = entity_metadata_wrapper('node', $entity);
  if (isset($wrapper->title)) {
    $wrapper->title->set($f_name);
  }
  if (isset($wrapper->field_rfi_domain)) {
    $wrapper->field_rfi_domain->set($domain);
  }
  if (isset($wrapper->field_rfi_first_name)) {
    $wrapper->field_rfi_first_name->set($f_name);
  }
  if (isset($wrapper->field_rfi_last_name)) {
    $wrapper->field_rfi_last_name->set($l_name);
  }
  if (isset($wrapper->field_rfi_student_type)) {
    $wrapper->field_rfi_student_type->set($student_type);
  }
  if (isset($wrapper->field_rfi_email)) {
    $wrapper->field_rfi_email->set($email);
  }
  if (isset($wrapper->field_rfi_phone)) {
    $wrapper->field_rfi_phone->set($phone);
  }
  if (isset($wrapper->field_rfi_sms_opted)) {
    $wrapper->field_rfi_sms_opted->set($sms_number);
  }
  if (isset($wrapper->field_rfi_country)) {
    $wrapper->field_rfi_country->set($country);
  }
  if (isset($wrapper->field_rfi_zipcode)) {
    $wrapper->field_rfi_zipcode->set($zip);
  }
  if (isset($wrapper->field_rfi_start_term_code)) {
    $wrapper->field_rfi_start_term_code->set($semester);
  }
  if (isset($wrapper->field_rfi_program)) {
    $wrapper->field_rfi_program->set($program);
  }
  if (isset($wrapper->field_rfi_college_code)) {
    $wrapper->field_rfi_college_code->set($college_code);
  }
  if (isset($wrapper->field_rfi_form_type)) {
    $wrapper->field_rfi_form_type->set($long_form_type);
  }
  if (isset($wrapper->field_rfi_ip_address)) {
    $wrapper->field_rfi_ip_address->set(intval($ip_address));
  }
  if (isset($wrapper->field_rfi_state)) {
    $wrapper->field_rfi_state->set($state);
  }
  if (isset($wrapper->field_rfi_veteran)) {
    $wrapper->field_rfi_veteran->set($veteran);
  }
  if (isset($wrapper->field_rfi_question)) {
    $wrapper->field_rfi_question->set(check_plain($questions));
  }
  if (isset($wrapper->field_rfi_dob)) {
    $wrapper->field_rfi_dob->set(base64_encode($dob_date));
  }
  if (isset($wrapper->field_rfi_submission_status)) {
    $wrapper->field_rfi_submission_status->set('Form_Completed');
  }
  if (isset($wrapper->field_rfi_address)) {
    $wrapper->field_rfi_address->set($address);
  }
  if (isset($wrapper->field_rfi_city)) {
    $wrapper->field_rfi_city->set($city);
  }
  if (isset($wrapper->field_rfi_international)) {
    $wrapper->field_rfi_international->set($international);
  }
  if (isset($wrapper->field_rfi_start_term)) {
    $wrapper->field_rfi_start_term->set($semester_name);
  }
  if (isset($wrapper->field_rfi_program_name)) {
    $wrapper->field_rfi_program_name->set($program_name);
  }
  if (isset($wrapper->field_rfi_college_name)) {
    $wrapper->field_rfi_college_name->set($college_name);
  }
  if (isset($wrapper->field_rfi_enterpriseclientid)) {
    $wrapper->field_rfi_enterpriseclientid->set($enterpriseclientid);
  }
  if (isset($wrapper->field_rfi_prospect_level)) {
    $wrapper->field_rfi_prospect_level->set($form_state['values']['prospect_level']);
  }
  if (isset($wrapper->field_rfi_location)) {
    $wrapper->field_rfi_location->set($location);
  }
  if (isset($wrapper->field_rfi_campus)) {
    $wrapper->field_rfi_campus->set($campus);
  }

  $wrapper->save();

  // Send the confirmation email
  if (($location !== 'Online' && $location !== 'online')) {
    if ($form_state['values']['prospect_level'] == ASU_RFI_PROSPECT_LEVEL_GRAD) {
      asu_rfi_grad_email($form_state['values']['program_code'], $form_state['values']['email'], $form_state['values']['first_name']);
    } else {
      asu_rfi_undergrad_email($form_state['values']['program_code'], $form_state['values']['email'], $form_state['values']['first_name']);
    }
  }

  $form_state['values']['submission_nodeid'] = $entity->nid;

  // Used in confirmation nodes
  $coded_major = base64_encode($program);
  $coded_college = base64_encode($college_name);
  $coded_college_code = base64_encode($college_code);
  $coded_nid = base64_encode($entity->nid);
  $coded_zip = base64_encode($zip);
  $coded_country = base64_encode($country);

  //////////////////////////////////////////////
  // Post values to middleware, based on program level), and redirect to thank
  // you page. DONE!

  // Graduate
  if ($form_state['values']['prospect_level'] == ASU_RFI_PROSPECT_LEVEL_GRAD) {

    asu_rfi_post_to_middleware($form_state['values'], ASU_RFI_PROSPECT_LEVEL_GRAD);

    $grad_conf_id = ASU_RFI_GRAD_CONFIRMATION_NID;
    if (!empty($grad_conf_id) && (int) $grad_conf_id !== 0) {
      $grad_alias = drupal_lookup_path('alias', $path = "node/$grad_conf_id", $path_language = NULL);
      if (!empty($grad_alias)) {
        drupal_goto("$grad_alias", array(
          'query' => array(
            'pro' => $coded_college,
            'maj' => $coded_major,
            'sub' => $coded_nid,
            'ccode' => $coded_college_code,
            'cat' => 'Grad RFI',
            'zcode' => $coded_zip,
            'con' => $coded_country
          )
        ));
      } else {
        drupal_goto("node/$grad_conf_id", array(
          'query' => array(
            'pro' => $coded_college,
            'maj' => $coded_major,
            'sub' => $coded_nid,
            'ccode"' => $coded_college_code,
            'cat' => 'Grad RFI',
            'zcode' => $coded_zip,
            'con' => $coded_country
          )
        ));
      }
    } else {
      drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
    }
  }

  // Undergrad
  if ($form_state['values']['prospect_level'] == ASU_RFI_PROSPECT_LEVEL_UNDERGRAD) {

    asu_rfi_post_to_middleware($form_state['values'], ASU_RFI_PROSPECT_LEVEL_UNDERGRAD);

    $undergrad_conf_id = ASU_RFI_UNDERGRAD_CONFIRMATION_NID;
    if ($undergrad_conf_id && $undergrad_conf_id !== 0) {
      $u_alias = drupal_lookup_path('alias', $path = "node/$undergrad_conf_id", $path_language = NULL);
      if (!empty($u_alias)) {
        drupal_goto("$u_alias", array(
          'query' => array(
            'pro' => $coded_college,
            'maj' => $coded_major,
            'sub' => $coded_nid,
            'ccode' => $coded_college_code,
            'cat' => 'UG RFI',
            'zcode' => $coded_zip,
            'con' => $coded_country
          )
        ));
      } else {
        drupal_goto("node/$undergrad_conf_id", array(
          'query' => array(
            'pro' => $coded_college,
            'maj' => $coded_major,
            'sub' => $coded_nid,
            'ccode"' => $coded_college_code,
            'cat' => 'UG RFI',
            'zcode' => $coded_zip,
            'con' => $coded_country
          )
        ));
      }
    } else {
      drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
    }
  }
}

/**
 * CURRENT STUDENTS - $form construction call
 * @param $delta
 * @param $programs
 * @param $form_type
 * @return array|mixed
 */
function asu_rfi_current_form($delta, $programs, $form_type) {
  return drupal_get_form('asu_rfi_current_form_data', $programs, $form_type);
}

/**
 * CURRENT STUDENTS - $form definition
 * @param $form
 * @param $form_state
 * @param $programs
 * @param $form_type
 * @return array
 */
function asu_rfi_current_form_data($form, &$form_state, $programs, $form_type) {

  $form = array();
  honeypot_add_form_protection($form, $form_state, array(
    'honeypot',
    'time_restriction'
  ));

  // Is the form in "Test Mode"? If so, add markup
  _asu_rfi_form_test_mode_markup($form, $form_state['build_info']['form_id']);

  $form['req_header_text'] = array(
    '#value' => _asu_rfi_form_header_text(),
  );
  $form['req_helper'] = array(
    '#value' => '<p>Fields marked with <span style = "color:black;">*</span> are required.</p>',
  );
  $form['domain'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => (string) $_SERVER['HTTP_HOST'],
  );
  $form['degree_type'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => $form_type,
  );
  $form['about_me'] = array(
    '#type' => 'fieldset',
    '#title' => 'About me...',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['about_me']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
    '#prefix' => '<div id ="req_info_form">',
  );
  $form['about_me']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#size' => 30,
    '#maxlength' => 64,
    '#required' => TRUE,
  );
  $form['about_me']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 50,
    '#maxlength' => 100,
    '#required' => TRUE,
  );
  $form['about_me']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Preferred phone number'),
    '#description' => t('USA Format: xxx-xxx-xxxx<br />'),
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
  );
  $form['about_me']['prog_plan'] = array(
    '#type' => 'select',
    '#title' => t('My program interest'),
    '#options' => $programs,
    '#required' => TRUE,
  );
  $form['questions'] = array(
    '#type' => 'textarea',
    '#title' => t('I also need assistance with the following:'),
    '#cols' => 60,
    '#resizable' => TRUE,
    '#rows' => 5,
    '#description' => '(Limit of 255 characters)',
  );
  $form['webform_url'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => $_SERVER['HTTP_HOST'],
  );
  $form['ip_address'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => $_SERVER['REMOTE_ADDR'],
  );
  $form['gdpr_message'] = array(
    '#type' => 'item',
    '#markup' => _asu_rfi_get_gdpr_markup()
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#attributes' => array('class' => array('rfi-button')),
    '#value' => t('I Agree / Submit'),
  );
  return $form;
}

/**
 * CURRENT STUDENTS - Validate handler
 * @param $form
 * @param $form_state
 */
function asu_rfi_current_form_data_validate($form, &$form_state) {
  $f_name = $form_state['values']['first_name'];
  $f_name = ucfirst($f_name);
  $l_name = $form_state['values']['last_name'];
  $l_name = ucfirst($l_name);
  $email = $form_state['values']['email'];
  $phone = $form_state['values']['phone'];

  $questions = check_plain($form_state['values']['questions']);

  // validate first name
  if (!preg_match("/^[a-zA-Z0-9.\s-_]+$/", $f_name)) {
    form_set_error('first_name', t('First name field accepts only plain text.'));
  }
  // validate last name
  if (!preg_match("/^[a-zA-Z0-9.\s-_]+$/", $l_name)) {
    form_set_error('last_name', t('Last name field accepts only plain text.'));
  }
  // validation for email
  if (!preg_match("/^([a-zA-Z0-9])+([a-zA-Z0-9._-])*@([a-zA-Z0-9_-])+([a-zA-Z0-9._-]+)+$/", $email)) {
    form_set_error('email', t('You entered an invalid email.'));
  }
  // validation for phone number
  $scam_num = substr($phone, 0, 3);
  if (!preg_match("/^([1]-)?([0-9]{3}[-|.][0-9]{3}[-|.][0-9]{4})$/i", $phone) || ($scam_num == "555")) {
    form_set_error('phone', t('You entered an invalid Phone number.'));
  }
  // validation for questions
  if (!empty($questions)) {
    $len = strlen($questions); // validation for comments character limit to 255
    if ($len > 255) {
      form_set_error('questions', t('Comments are limited to a maximum of 255 characters.'));
    }
  }
}

/**
 * CURRENT STUDENTS - SUBMIT handler
 *
 * @param $form
 * @param $form_state
 */
function asu_rfi_current_form_data_submit($form, &$form_state) {
  global $user;

  $degreeMappings = _asu_rfi_get_degree_field_mappings();

  $domain = $form_state['values']['domain'];
  $f_name = $form_state['values']['first_name'];
  $l_name = $form_state['values']['last_name'];
  $email = $form_state['values']['email'];
  $phone = $form_state['values']['phone'];
  $form_type = $form_state['values']['degree_type'];
  $ip_address = $form_state['values']['ip_address'];
  $questions = (!empty($form_state['values']['questions'])) ? $form_state['values']['questions'] : '';
  $program = $form_state['values']['prog_plan'];

  // Get program name based on the program code submitted in the form
  $program_name = db_query('select ' . $degreeMappings['field_degree_awarded_value']
    . ' from ' . $degreeMappings['table_asu_degree_awarded']
    . ' mj join ' . $degreeMappings['table_asu_academic_plan']
    . ' ap on mj.entity_id = ap.entity_id where ap.'
    . $degreeMappings['field_academic_plan_value'] . ' = :plan',
    array(':plan' => $program))->fetchField();

  // Create node
  $ent_values = array(
    'type' => 'asu_rfi',
    'uid' => $user->uid,
    'status' => 0,
    'comment' => 1,
    'promote' => 0,
  );
  $entity = entity_create('node', $ent_values);

  $wrapper = entity_metadata_wrapper('node', $entity);
  if (isset($wrapper->title)) {
    $wrapper->title->set($f_name);
  }
  if (isset($wrapper->field_rfi_first_name)) {
    $wrapper->field_rfi_first_name->set($f_name);
  }
  if (isset($wrapper->field_rfi_domain)) {
    $wrapper->field_rfi_domain->set($domain);
  }
  if (isset($wrapper->field_rfi_last_name)) {
    $wrapper->field_rfi_last_name->set($l_name);
  }
  if (isset($wrapper->field_rfi_email)) {
    $wrapper->field_rfi_email->set($email);
  }
  if (isset($wrapper->field_rfi_phone)) {
    $wrapper->field_rfi_phone->set($phone);
  }
  if (isset($wrapper->field_rfi_program)) {
    $wrapper->field_rfi_program->set($program);
  }
  if (isset($wrapper->field_rfi_program_name)) {
    $wrapper->field_rfi_program_name->set($program_name);
  }
  if (isset($wrapper->field_rfi_form_type)) {
    $wrapper->field_rfi_form_type->set($form_type);
  }
  if (isset($wrapper->field_rfi_ip_address)) {
    $wrapper->field_rfi_ip_address->set(intval($ip_address));
  }
  if (isset($wrapper->field_rfi_question)) {
    $wrapper->field_rfi_question->set($questions);
  }
  if (isset($wrapper->field_rfi_submission_status)) {
    $wrapper->field_rfi_submission_status->set('Form_Completed_No_SF');
  }
  $wrapper->save();

  // Send email and redirect to thank you
  $coded_nid = base64_encode($entity->nid);
  if ($form_state['values']['degree_type'] !== "current_undergrad_form") {
    asu_rfi_grad_email($form_state['values']['prog_plan'],
      $form_state['values']['email'],
      $form_state['values']['first_name']);
  } else {
    asu_rfi_undergrad_email($form_state['values']['prog_plan'],
      $form_state['values']['email'],
      $form_state['values']['first_name']);
  }
  drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
}

/**
 * INIT settings/assets to optionally add to any RFI forms.
 * @param string $form_main_type - multiform, long_form, or current_form
 */
function _asu_rfi_form_initial_web_assets($form_main_type) {
  drupal_add_css(drupal_get_path('module', 'asu_rfi') . '/theme/asu_rfi.css', 'file');
  if ($form_main_type === 'multiform' || $form_main_type === 'long_form') {
    // Add no-store in Cache-Control to clear all data when browser back button is clicked
    drupal_add_http_header(
      'Cache-Control',
      'no-store, no-cache, must-revalidate, post-check=0, pre-check=0, max-age=0',
      FALSE
    );
    // Hack for Safari bug
    drupal_add_js('jQuery(window).unload(function(){});', array('type' => 'inline'));
    // Add js to gather enterpriseclientid from GA to add to payload for
    // submissions destined for EdPlus and their Lead API 4.0 by way of the Middleware.
    drupal_add_js(drupal_get_path('module', 'asu_rfi') . '/js/asu_rfi.fields.js', 'file');
  }
  if ($form_main_type === 'long_form') {
    drupal_page_is_cacheable(FALSE);
  }
}

/**
 * Confirms if the given locations available for a program?
 *
 * @param $prog - program
 * @param $campus - Campus
 * @param $loc - Location
 * @return bool
 */
function _asu_rfi_program_location_confirm($prog, $campus, $loc) {
  $degreeMappings = _asu_rfi_get_degree_field_mappings();
  $campusOptions = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', $degreeMappings['content_type'])
    ->fieldCondition($degreeMappings['field_academic_plan'], 'value', $prog)
    ->range(0, 10)
    ->addMetaData('account', user_load(1));

  $result = $query->execute();

  if (isset($result['node'])) {
    $result_nodes = $result['node'];
    $programs = _asu_rfi_get_program_codes($result_nodes, 'programs');
    $locations = $programs[$degreeMappings['field_degree_campus']][LANGUAGE_NONE];
    foreach ($locations as $location) {
      if (!in_array($location['value'], $campusOptions)) {
        array_push($campusOptions, $location['value']);
      }
    }
  }

  if ($loc == "on_campus" && $prog == '') {
    return TRUE;
  } else {
    if ($loc == "online" && ((!isset($campus) || $campus == '') || $campus == 'online' || $campus == 'Online')) {
      return TRUE;
    } else {
      if ($loc !== "online" && in_array($campus, $campusOptions)) {
        return TRUE;
      } else {
        if ($loc == 'no_preference') {
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

/**
 * Get countries list for forms
 */
function _asu_rfi_get_country_list() {
  $other_countries = &drupal_static(__FUNCTION__);
  if (!isset($other_countries)) {
    /*$countries = db_query("select countryDesc from asu_rfi_countries order by countryDesc asc"); */
    $countries = db_select('asu_rfi_countries', 'arc')
      ->fields('arc', array('countryDesc'))
      ->orderBy('countryDesc')
      ->execute()
      ->fetchAllKeyed(0,0);
    $us_cont = array("United States" => "United States");
    $other_countries = array_diff($countries, $us_cont);
    $other_countries = $us_cont + $other_countries;
  }
  return $other_countries;
}

/**
 * Get states list for forms
 */
function _asu_rfi_get_state_list() {
  $all_state_options = &drupal_static(__FUNCTION__);
  if (!isset($all_state_options)) {
    $all_state_options = db_select('asu_rfi_states_list', 'arsl')
      ->fields('arsl', array('stateDesc'))
      ->orderBy('stateDesc')
      ->execute()
      ->fetchAllKeyed(0,0);
    $option = 'None';
    array_unshift($all_state_options, $option);
  }
  return $all_state_options;
}

/**
 * Build semester start dates
 * @return array|mixed $sem_dates_array
 */
function _asu_rfi_get_sem_dates() {
  $sem_dates_array = &drupal_static(__FUNCTION__);

  $term_date = array();
  if (!isset($sem_dates_array)) {
    //Get semester dates from database
    $sem_dates_query = db_query("select * from {asu_rfi_sem_dates} order by CHAR_LENGTH(semId)");
    foreach ($sem_dates_query as $semester) {
      $term_date[$semester->semId] = $semester->semLabel;
    }

    // Web services from middleware pulls all the old semesters and saves into
    // database, the below code display only current and next three years in the drop down.
    // build the date array
    $date = array();
    $month = date('m');
    $day = date('d');
    $new = array();
    $options = array();
    $semester = array("1" => "Spring", "7" => "Fall");
    $year = date('Y');

    for ($i = 0; $i <= 2; $i++) {
      $date[$i] = $year + $i;
      $new[$i] = substr_replace($date[$i], "", 1, 1);
      if ($i == 0) {
        if ($year == $date[0]) { // check if it is current year
          if (($month <= 8)) {
            if (($month != 8) || ($month == 8) && ($day <= 14)) {
              $sem = $semester["7"];
              $trim_year = $new[$i] . "7";  // append 1 to the key depending on the season. For spring, add 1.
              $list = $date[$i];
              $options[$trim_year] = $list . " " . $sem;
            }
          }
          if (($month >= 8)) {
            if (($month != 8) || ($month == 8) && ($day > 14)) {
              $sem = $semester["1"];
              $trim_year = ($new[$i] + 1) . "1";  // append 1 to the key depending on the season. For spring, add 1.
              $list = $date[$i] + 1;
              $options[$trim_year] = $list . " " . $sem;

              $up_new = $new[$i] + 1;
              $new_date = $date[$i] + 1;
              $sem = $semester["7"];
              $trim_year = $up_new . "7";
              $list = $new_date;
              $options[$trim_year] = $list . " " . $sem;
            }
          }
        }
      } else {
        $sem = $semester["1"];
        $trim_year = ($new[$i]) . "1";  // append 1 to the key depending on the season. For spring, add 1.
        $list = $date[$i];
        $options[$trim_year] = $list . " " . $sem;

        $up_next_new = $new[$i];
        $next_new_date = $date[$i];
        $next_sem = $semester["7"];
        $next_trim_year = $up_next_new . "7";
        $next_list = $next_new_date;
        $options[$next_trim_year] = $next_list . " " . $next_sem;
      }
    }
    if (!empty($term_date)) {
      $sem_dates_array = array_intersect($term_date, $options);
    } else {
      $sem_dates_array = $options;
    }
  }
  return $sem_dates_array;
}

/**
 * ASU Get GDPR Markup - Creates simple HTML to append to end of all RFI forms to ensure GDPR compliance
 *
 * @return string - HTML containing all pertinent information and resources pertaining to GDPR
 */
function _asu_rfi_get_gdpr_markup() {
  $gdpr_markup =
    "
    <div>
        <h5>By completing and submitting your information to ASU, you consent to:</h5>
        <ol class='gdpr-list'>
            <li>ASU using this information to contact you regarding information as you requested</li>
            <li>The terms of <a class='gdpr-link' href='https://www.asu.edu/privacy/#asu-privacy-general'>ASU's Privacy Statement</a></li>
            <li>If you are in the European Union or another country or state that has adopted the GDPR
            (General Data Protection Regulation) or similar privacy protection, please also read the
            <a class='gdpr-link' href='https://www.asu.edu/privacy/#european-union-supplement'>ASU European Supplement to ASU's Privacy Statement</a>
            </li>
        </ol>
    </div>
  ";

  return $gdpr_markup;
}

/**
 * Get standardized form header for all forms (excluding part 2 of the multiform).
 * @return string
 */
function _asu_rfi_form_header_text() {
  return "<h4>Please complete and submit the form below, and a representative will contact you about enrolling at ASU.";
}
