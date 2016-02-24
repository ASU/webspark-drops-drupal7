<?php
// $Id: asu_rfi.pages.inc 

/**
 * @file
 * Request info form generation using form API
 */
//clear page cache
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Cache-Control: no-store, no-cache, must-revalidate");
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache");


 /* Implementation of hook_int() ***/
module_load_include('inc', 'asu_rfi', 'includes/asu_rfi_email');
module_load_include('inc', 'asu_rfi', 'includes/asu_rfi_grad_post');
module_load_include('inc', 'asu_rfi', 'includes/asu_rfi_undergrad_post');
drupal_add_css(drupal_get_path('module', 'asu_rfi') .'/theme/asu_rfi.css','file');




/* Implementation of hook_form **/

function asu_rfi_form($delta){
    return drupal_get_form('asu_rfi_form_data');
     // Add no-store in Cache-Control.
    drupal_add_http_header(
     'Cache-Control', 
     'no-store, no-cache, must-revalidate, post-check=0, pre-check=0, max-age=0', 
     FALSE
   );
   // Hack for Safari
    drupal_add_js('jQuery(window).unload(function(){});', array('type' => 'inline')); 
}

function asu_rfi_form_data($form, &$form_state) {
    
    //Clear all data when browser back button is clicked
    session_set_cookie_params(0);
    // Add no-store in Cache-Control to clear all data when browser back button is clicked
    drupal_add_http_header(
     'Cache-Control', 
     'no-store, no-cache, must-revalidate, post-check=0, pre-check=0, max-age=0', 
     FALSE
    );
    // Hack for Safari
    drupal_add_js('jQuery(window).unload(function(){});', array('type' => 'inline'));  
   
    
    if(isset($form_state['storage'])){
	
        if($form_state['storage']['step'] == 'asu_rfi_second_form'){
	   return asu_rfi_second_form($form, $form_state);
        }
    }
    
   
    //get states
    $start_dates = _asu_rfi_sem_dates();
  
    for($idate = 0; $idate < 4; $idate++){
        $date = date('Y') + $idate;
        $datekey = substr_replace($date,'',1,-2);
        $year[$datekey] = $date;
    }
    
    //Load the current node object to get program name and degree type
    $country = asu_rfi_countries_data();
    $node = menu_get_object();
    if(!empty($node)){
	if(!empty($node->field_asu_academic_plan[LANGUAGE_NONE][0]['value'])){
	    $dcode = $node->field_asu_academic_plan[LANGUAGE_NONE][0]['value'];
	}
	else{
	    $dcode = '';
	}
    
        if(!empty($node->field_asu_degree_awarded[LANGUAGE_NONE][0]['value'])){
            $dname = $node->field_asu_degree_awarded[LANGUAGE_NONE][0]['value'];
	}
	else{
	    $dname = '';
	}
        $degree[$dcode] = $dname;
        if(!empty($node->field_asu_degree_program[LANGUAGE_NONE][0]['value'])){
	    $type_degree = $node->field_asu_degree_program[LANGUAGE_NONE][0]['value'];
        }
        else{
	    $type_degree = '';
        }
        if(!empty($node->field_asu_academic_program)){
	    $college_code = $node->field_asu_academic_program[LANGUAGE_NONE][0]['value'];
        }
        else{
	    $college_code = "None";
        }
        if(!empty($node->field_asu_diploma_description)){
	   $college_name = $node->field_asu_diploma_description[LANGUAGE_NONE][0]['value'];
        }
        else{
	   $college_name = '';
        }
    
	 $form = array();
    
	 honeypot_add_form_protection($form, $form_state, array('honeypot', 'time_restriction'));  
    
	 //if the session is set for more than 5 min, clear the session data
	if(isset($_SESSION['rfi_data'])){
	    $current_time = time();
	    $session_start_time = $_SESSION['rfi_data']['start_time'];
	    $session_diff = $current_time - $session_start_time;
	
	    if($session_diff >= 180){
		unset($_SESSION['rfi_data']);
		unset($form_state['storage']);
		unset($form_state['values']);
		// drupal_set_message('Your session has expired, please fill out the form again.');
		$form['sess_expire_message'] = array(
		    '#type' => 'item',
		    '#markup' => '<div class="alert-danger" style="padding:2%;">Your session has expired, please fill out the form again.</div>',
		);
	    }
	}
	$form_mode = variable_get('asu_rfi_form_mode');
	if(($form_mode == "test") || (empty($form_mode))){
	    $form['form_stage'] = array(
		'#type' => 'item',
		'#markup' => t('<div class="rfi_test_mode">The form is in test mode, you can change the mode in <a href="/admin/config/content/asurfi">admin settings page</a></div>')
	    );
	}
    
	/* $middleware_key = variable_get('asu_rfi_form_auth_key',NULL);
	if(empty($middleware_key)){
	    $form['form_middle_post'] = array(
		'#type' => 'item',
		'#markup' => t('<div class="rfi_middlekey">The middleware authentication key is currently not set, it is required to post data to middleware. You can request the key from <a href="https://webforms.asu.edu/content/access-rfi-middleware-request">here</a> and add the key provided at the <a href="/admin/config/asu/asurfi">RFI admin settings page</a></div>')
	    );
	}
	*/
	$form['req_header_text'] = array(
	    '#type' => 'item',
	    '#markup' => '<h4>Please complete and submit the form below, and a representative will contact you about enrolling at ASU</h4>'
	);
    
	$form['req_helper'] = array(
	    '#type' => 'item',
	    '#markup' => '<p>Fields marked with <span style = "color:#FF0000;">*</span> are required.</p>',
	    '#size' => 10,
	    );
    
	$form['degree_type'] = array(
	    '#type' => 'hidden',
	    '#size' => 30,
	    '#maxlength' => 64,
	    '#default_value' => $type_degree,
	); 
    
	$form['my_interest'] = array(
	    '#type' => 'fieldset',
	    '#title' => 'My interests',
	    '#collapsible' => TRUE,
	    '#collapsed' => FALSE,
	    '#size' => 10,
	);
     
	$form['my_interest']['student_type'] = array(
	    '#type' => 'select',
	    '#title' => t('I will be a future'),
	    '#options' => array('First Time Freshman'=>'First Time Freshman', 'Transfer'=>'Transfer',' Readmission'=>'Readmission'),
	    '#states' => array(
		'visible' => array(
		    ':input[name="degree_type"]' => array('value' => 'undergrad'),
		),
	    ),
	'#required' => TRUE,
	'#attributes' => array('class' => array('reqinfo_student_type')),
	'#default_value' =>  isset($_SESSION['rfi_data']['student_type']) ? $_SESSION['rfi_data']['student_type'] : NULL,
	);
  
	$form['my_interest']['prog_plan'] = array(
	    '#type' => 'textfield',
	    '#title' => t('My program of interest'),
	    '#required' => TRUE,
	    '#default_value' => $dname,
	    '#disabled' => TRUE,
	    '#size' => 30,
	);
     
	$form['program_code'] = array(
	    '#type' => 'hidden',
	    '#size' => 30,
	    '#maxlength' => 64,
	    '#default_value' => $dcode,
	    '#size' => 50,
	);
     
	$form['college_name'] = array(
	    '#type' => 'hidden',
	    '#size' => 30,
	    '#maxlength' => 64,
	    '#default_value' => $college_name,
	    '#size' => 50,
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
	    '#title' => 'About me',
	    '#collapsible' => TRUE,
	    '#collapsed' => FALSE,
	);
   
   
	$form['about_me']['first_name'] = array(
	    '#type' => 'textfield',
	    '#title' => t('First name'),
	    '#size' => 30,
	    '#maxlength' => 30,
	    '#required' => TRUE,
	    '#prefix' => '<div id ="req_info_form">',
	    '#default_value' => isset($_SESSION['rfi_data']['first_name']) ?  $_SESSION['rfi_data']['first_name'] : NULL,
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
	    '#attributes' =>  array('class' => array('rfi_phone')),
	    '#default_value' => isset($_SESSION['rfi_data']['phone']) ? $_SESSION['rfi_data']['phone'] : NULL,
	);
   
	$form['about_me']['mobile_check'] = array(
	    '#type' => 'checkbox',
	    '#title' => t('This is a USA mobile number and I would like to receive information via SMS text messaging'),
	    '#size' => 30,
	    '#maxlength' => 30,
	    '#required' => FALSE,
	    '#attributes' =>  array('class' => array('rfi_mobile')),
	    '#default_value' => isset($_SESSION['rfi_data']['mobile_check']) ? $_SESSION['rfi_data']['mobile_check'] : NULL,
	);
   
	$form['about_me']['country'] = array(
	    '#id' => 'rfi-country',
	    '#type' => 'select',
	    '#options' => $country,
	    '#title' => t('Country'),
	    '#required' => TRUE,
	    '#default_value' =>  isset($_SESSION['rfi_data']['country']) ? $_SESSION['rfi_data']['country'] : NULL,
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
	    '#default_value' => isset($_SESSION['rfi_data']['zipcode']) ?  $_SESSION['rfi_data']['zipcode'] : NULL,
	);
   
	/*Birthday field disclaimer*/
	$modal_data = '<!-- Button trigger modal -->
	    <span class="fa fa-info-circle" data-toggle="modal" data-target="#myModal"></span>
	    <!-- Modal -->
	    <div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
		<div class="modal-dialog">
		    <div class="modal-content">
			<div class="modal-body">
			    Your birthday is important! Not only will we send you a birthday message, it helps us keep your information secure as a unique identifier for your online submission.
			</div>
			<div class="modal-footer">
			    <div class="btn btn-default" data-dismiss="modal">Close</div>
			</div>
		    </div>
		</div>
	</div>';
     
	// The below field creates illusion as part of date of birth field. I had to add this field to avoid validation error message containing modal data
	$form['about_me']['dob_field'] = array(
	    '#type' => 'item',
	    '#markup' => '<label><strong>Date of birth <span class="form-required">*</span></strong></label>'.$modal_data,
	);
   
	$form['about_me']['birthdate'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Date of birth'),
	    '#description' => t('Format: mm/dd/yyyy'),
	    '#title_display' => 'invisible',
	    '#size' => 30,
	    '#maxlength' => 30,
	    '#required' => TRUE,
	    '#default_value' =>  isset($_SESSION['rfi_data']['birthdate']) ? $_SESSION['rfi_data']['birthdate'] : NULL,
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
	    '#attributes' =>  array('class' => array('rfi_button')),
	    '#submit' => array('asu_rfi_form_data_submit'),
	    '#value' => t('Next'),
	);
	return $form;
    }
 
}


/**
 * Submit handler for the first form.
 *
 * @see asu_rfi_first_data().
 */


function asu_rfi_form_data_validate($form, &$form_state) {
    if(isset($form_state['storage'])){
	if($form_state['storage']['step'] == 'asu_rfi_second_form') { 
	     return asu_rfi_second_form_validate($form, $form_state);
	}		
    }
 
    $degree_type = $form_state['values']['degree_type'];
  
    $stype = $form_state['values']['student_type'];
    $fname = $form_state['values']['first_name'];
    $lname = $form_state['values']['last_name'];
    $email = $form_state['values']['email'];
    $phone = $form_state['values']['phone'];
    $zip =  $form_state['values']['zipcode'];
    $country = $form_state['values']['country'];
    $birthdate = $form_state['values']['birthdate'];
    $mobile_check = $form_state['values']['mobile_check'];
  
   
    //validate first name
    if( !preg_match("/^[a-zA-Z\.\s-_]+$/",$fname)){
        form_set_error('first_name', t('First name field accepts only plain text.'));
	$fname = ucfirst($fname);
    }
    //validate last name
    if( !preg_match("/^[a-zA-Z\.\s-_]+$/",$lname)){
        form_set_error('last_name', t('Last name field accepts only plain text.'));
	$lname = ucfirst($lname);
    }
    //validation for email
    if( !preg_match("/^([a-zA-Z0-9])+([a-zA-Z0-9\._-])*@([a-zA-Z0-9_-])+([a-zA-Z0-9\._-]+)*(\.[a-zA-Z]{2,6})+$/", $email)){
        form_set_error('email', t('You entered an invalid email.'));
    }
    //validation for phone number
    /** If mobile number field is checked, then check for USA format, else check for special characters **/
  
    $scam_num = substr($phone, 0, 3);
    if($mobile_check != 0){
	if( !preg_match("/^([1]-)?([0-9]{3}[-|.][0-9]{3}[-|.][0-9]{4})$/i", $phone) || ($scam_num == "555" )) {
	    form_set_error('phone', t('You entered an invalid Phone number.'));
	}
    }
    else{
	if( !preg_match("/^[0-9\.\s-_+\(\)]+$/", $phone) || ($scam_num == "555" )) {
	    form_set_error('phone', t('You entered an invalid Phone number.'));
	}
    }

    //validate zip code
  
    if(empty($zip)){
	if(!empty($country) && ($country == "United States")){
	    form_set_error('zipcode', t('Postal code field is required.'));
	}
    }
  
    if(!empty($zip)){
	if($country == "United States"){
	    if((strlen($zip) < 5)){
		form_set_error('zipcode', t('Postal code cannot be less than 5 digits.'));
	    }
	    if( !preg_match("/^[0-9]{5}+$/",$zip)){
		form_set_error('zipcode', t('Postal code accepts 5 digits only.'));
	    }
	}
	else{
	    if( !preg_match("/^[a-zA-Z0-9\s-_+-]+$/",$zip)){
		form_set_error('zipcode', t('Postal code is not valid'));
	    }
	    if((strlen($zip) < 4)){
		form_set_error('zipcode', t('Postal code cannot be less than 4 characters.'));
	    }
	    if(strlen($zip) > 20){
		form_set_error('zipcode', t('Postal code cannot be longer than 20 characters.'));
	    }
	}
    }
  
    //validate birthdate
  
    if(!empty($birthdate)){ 
	//get number of occurences of '/' in dob
	$slashes = substr_count($birthdate, '/');
	if($slashes == 2){
	    $date_format = explode('/',$birthdate);
	    $month = $date_format[0];
	    $day = $date_format[1];
	    $year = $date_format[2];
	    $current_year = date('Y');
	    $year_limit = $current_year - 1;
	    $isLeapYear = date("L");
    
	    if(strlen($birthdate) < 11){
		if(($month < 1) || ($month > 12)){
		    form_set_error('birthdate', t('Month range has to be between 1 and 12.'));
		    form_set_error('dob_field',t(' '));
		}
		
		if(($month == 1) || ($month == 3) || ($month == 5) || ($month == 7) || ($month == 8) || ($month == 10) || ($month == 12)){
		    if(($day < 1) || ($day > 31)){
			form_set_error('birthdate', t('Date range has to be between 1 and 31.'));
			form_set_error('dob_field',t(' '));
		    }
		}
		
		if(($month == 4) || ($month == 6) || ($month == 9) || ($month == 11)){
		    if(($day < 1) || ($day > 30)){
			form_set_error('birthdate', t('Date range has to be between 1 and 30.'));
			form_set_error('dob_field',t(' '));
		    }
		}
		
		if($month == 2) {
		    if($isLeapYear == 1){
			if(($day < 1) || ($day > 29)){
			    form_set_error('birthdate', t('Date range has to be between 1 and 29.'));
			    form_set_error('dob_field',t(' '));
			}
		    }
		    if($isLeapYear == 0){
			if(($day < 1) || ($day > 28)){
			    form_set_error('birthdate', t('Date range has to be between 1 and 28.'));
			    form_set_error('dob_field',t(' '));
			}
		    }
		}
		
		if(strlen($year) != 4){
		    form_set_error('birthdate', t('Year has to be 4 digits.'));
		}
		
		if($year > $year_limit){
		    form_set_error('birthdate', t('Year cannot be greater than '.$year_limit));
		}
    
		if(!preg_match("/^(0[1-9]|1[012])[\-\/.](0[1-9]|[12][0-9]|3[01])[\-\/.](19|20)\d\d$/", $birthdate)){
		    form_set_error('birthdate', t('Date of birth accepts the format mm/dd/yyyy.'));
		    form_set_error('dob_field',t(' '));
		}
		
	    }
	    else{
		form_set_error('birthdate', t('Date of birth is invalid, it accepts the format mm/dd/yyyy.'));
		form_set_error('dob_field',t(' '));
	    }
	}
	else{
	    form_set_error('birthdate', t('Date of birth is invalid, it accepts the format mm/dd/yyyy.'));
	    form_set_error('dob_field',t(' '));
	}
    }
    else{
	form_set_error('birthdate', t('Date of birth is required.'));
	form_set_error('dob_field',t(' '));
    }
  
}



/* First form submit handler */
function asu_rfi_form_data_submit($form, &$form_state){
    if(isset($form_state['storage'])){
	if($form_state['storage']['step'] == 'asu_rfi_second_form'){
	    return asu_rfi_second_form_submit($form, $form_state);
	    $form_state['complete'] = TRUE;
	}
    }
 
    //build session variables to be used later
 
    $_SESSION['rfi_data'] = $form_state['values'];
    $_SESSION['rfi_data']['start_time'] = time();
    global $user;
    // Save values to the form storage, add the next step function callback
    $form_state['rebuild'] = TRUE;
    $form_state['storage']['first_name'] = check_plain($form_state['values']['first_name']);
    $form_state['storage']['last_name'] = check_plain($form_state['values']['last_name']);
    $form_state['storage']['phone'] = $form_state['values']['phone'];
    $sms_opted = $form_state['values']['mobile_check'];
 
    //check if the phone number already has 1 prepeneded. If yes, just pass phome number to sms field, else prepend 1.
    if(!empty($sms_opted)){
	if(substr($form_state['values']['phone'], 0,1) != "1"){
	    $form_state['storage']['mobile_check'] = '1'.$form_state['values']['phone'];
	}
	else{
	    $form_state['storage']['mobile_check'] = $form_state['values']['phone'];
	}
    }
    else{
	$form_state['storage']['mobile_check'] =  '';
    }
 
    $dobdate = $form_state['values']['birthdate'];
  
    $form_state['storage']['email'] = check_plain($form_state['values']['email']);
  
    $form_state['storage']['zipcode'] = check_plain($form_state['values']['zipcode']);
  
    $form_state['storage']['start_date'] = check_plain($form_state['values']['start_date']);
  
    $form_state['storage']['country'] = check_plain($form_state['values']['country']);
  
    $form_state['storage']['college_name'] = check_plain($form_state['values']['college_name']);
  
    $form_state['storage']['birthdate'] = $dobdate;
   
    //get start date array
   
    $semdates = _asu_rfi_sem_dates();
  
    if(array_key_exists($form_state['storage']['start_date'], $semdates)){
	$form_state['storage']['semester_name'] = $semdates[$form_state['storage']['start_date']];
    }
   
    $form_state['storage']['prog_plan'] = check_plain($form_state['values']['prog_plan']);
 
    if(($form_state['values']['degree_type']) != "undergrad"){
        $form_state['values']['student_type'] = "Graduate";
	$form_state['storage']['student_type'] = "Graduate";
	$multi_form_type = "Graduate multi form";
	$form_state['storage']['prospect_level'] = "Graduate";
    }
    else{
	$form_state['storage']['student_type'] = $form_state['values']['student_type'];
	$multi_form_type = "Undergraduate multi form";
	$form_state['storage']['prospect_level'] = "Undergraduate";
    }
  
    $form_state['storage']['ip_address'] =  $form_state['values']['ip_address'];
    $form_state['storage']['college_code'] =  $form_state['values']['college'];
    $form_state['storage']['program_code'] =  $form_state['values']['program_code'];
    $ip_address = $form_state['values']['ip_address'];
  
    $current_time = time();
    $form_state['storage']['submit_time'] = $current_time ;
    $uniqueid = $form_state['values']['first_name'].$form_state['values']['email'].$form_state['values']['prog_plan'];
   
    //Check for duplicate submissions
    $check_duplicate = db_select('field_data_field_rfi_uniquedata','afu')
    ->fields('afu')
    ->condition('field_rfi_uniquedata_value',$uniqueid,'=')
    ->execute()
    ->fetchField();
  
    //check if unique id exists in the database
    $node_unique = db_query('SELECT field_rfi_uniquedata_value FROM {field_data_field_rfi_uniquedata} WHERE field_rfi_uniquedata_value = :unid', array(':unid' => $uniqueid))->fetchField();
  
	    //if unique id doesn't exist, create the nodes
	    if(empty($node_unique)){
		$ent_values = array(
		    'type' => 'asu_rfi',
		    'uid' => $user->uid,
		    'status' => 0,
		    'comment' => 1,
		    'promote' => 0,
		);
		$entity = entity_create('node', $ent_values);
		$ewrapper = entity_metadata_wrapper('node', $entity);
		$ewrapper->title->set($form_state['storage']['first_name']);
		$ewrapper->field_rfi_first_name->set($form_state['storage']['first_name']);
	    	$ewrapper->field_rfi_last_name->set($form_state['storage']['last_name']);
		$ewrapper->field_rfi_student_type->set($form_state['storage']['student_type']);
		$ewrapper->field_rfi_email->set($form_state['storage']['email']);
		$ewrapper->field_rfi_phone->set($form_state['storage']['phone']);
		$ewrapper->field_rfi_country->set($form_state['storage']['country']);
		$ewrapper->field_rfi_zipcode->set($form_state['storage']['zipcode']);
		$ewrapper->field_rfi_start_term_code->set($form_state['storage']['start_date']);
		$ewrapper->field_rfi_program->set($form_state['storage']['program_code']);
		$ewrapper->field_rfi_form_type->set($multi_form_type);
		$ewrapper->field_rfi_ip_address->set(intval($form_state['storage']['ip_address']));
		$ewrapper->field_rfi_college_code->set($form_state['storage']['college_code']);
		$ewrapper->field_rfi_submission_status->set('Incomplete');
		$ewrapper->field_rfi_dob->set(base64_encode($dobdate));
		$ewrapper->field_rfi_uniquedata->set($uniqueid);
		$ewrapper->field_rfi_start_term->set($form_state['storage']['semester_name']);
		$ewrapper->field_rfi_sms_opted->set($form_state['storage']['mobile_check']);
		$ewrapper->field_rfi_program_name->set($form_state['storage']['prog_plan']);
		$ewrapper->field_rfi_college_name->set($form_state['storage']['college_name']);
		$ewrapper->field_rfi_prospect_level->set($form_state['storage']['prospect_level']);
		$ewrapper->save();
		
		$form_state['storage']['submission_nodeid'] = $entity->nid;
		$form_state['storage']['step'] = 'asu_rfi_second_form';
		$form_state['storage']['submission_nodeid'] = $entity->nid; 
      
		//Load asu_rfi_email.inc file to send email
		asu_rfi_email($form_state['storage']['program_code'], $form_state['storage']['email']);
	    }
	    if(!empty($node_unique)){
		//get the node id of the current node to be updated 
		$get_nodeid = db_query('SELECT entity_id FROM {field_data_field_rfi_uniquedata} WHERE field_rfi_uniquedata_value = :unid', array(':unid' => $uniqueid))->fetchField();
	
		$node = node_load($get_nodeid);
		$ewrapper = entity_metadata_wrapper('node', $node);
		$ewrapper->title->set($form_state['storage']['first_name']);
		$ewrapper->field_rfi_first_name->set($form_state['storage']['first_name']);
		$ewrapper->field_rfi_last_name->set($form_state['storage']['last_name']);
		$ewrapper->field_rfi_student_type->set($form_state['storage']['student_type']);
		$ewrapper->field_rfi_email->set($form_state['storage']['email']);
		$ewrapper->field_rfi_phone->set($form_state['storage']['phone']);
		$ewrapper->field_rfi_country->set($form_state['storage']['country']);
		$ewrapper->field_rfi_zipcode->set($form_state['storage']['zipcode']);
		$ewrapper->field_rfi_start_term_code->set($form_state['storage']['start_date']);
		$ewrapper->field_rfi_program->set($form_state['storage']['program_code']);
		$ewrapper->field_rfi_form_type->set($multi_form_type);
		$ewrapper->field_rfi_ip_address->set(intval($form_state['storage']['ip_address']));
		$ewrapper->field_rfi_college_code->set($form_state['storage']['college_code']);
		$ewrapper->field_rfi_submission_status->set('Incomplete');
		$ewrapper->field_rfi_dob->set(base64_encode($dobdate));
		$ewrapper->field_rfi_uniquedata->set($uniqueid);
		$ewrapper->field_rfi_start_term->set($form_state['storage']['semester_name']);
		$ewrapper->field_rfi_sms_opted->set($form_state['storage']['mobile_check']);
		$ewrapper->field_rfi_program_name->set($form_state['storage']['prog_plan']);
		$ewrapper->field_rfi_college_name->set($form_state['storage']['college_name']);
		$ewrapper->field_rfi_prospect_level->set($form_state['storage']['prospect_level']);
		$ewrapper->save();
		$form_state['storage']['submission_nodeid'] = $get_nodeid;
		$form_state['storage']['step'] = 'asu_rfi_second_form';
	    }

}

/** construct the second form **/
function asu_rfi_second_form($form, &$form_state){
   
    $current_time = time();
    $session_start_time = $_SESSION['rfi_data']['start_time'];
    $session_diff = $current_time - $session_start_time;
    if($session_diff >= 180){
	unset($form_state['storage']);
    }
   
    drupal_add_js(drupal_get_path('module', 'asu_rfi') .'/theme/asu_rfi.js','file');
     // Add no-store in Cache-Control to clear all data when browser back button is clicked
    drupal_add_http_header(
	'Cache-Control', 
	'no-store, no-cache, must-revalidate, post-check=0, pre-check=0', 
	FALSE
    );
    // Hack for Safari
    drupal_add_js('jQuery(window).unload(function(){});', array('type' => 'inline'));
    
    //If the form is in test mode, display test mode message
    drupal_add_css(drupal_get_path('module', 'asu_rfi') .'/theme/asu_rfi.css','file');
   if(isset($_SESSION['rfi_data'])){
	$current_time = time();
	$session_start_time = $_SESSION['rfi_data']['start_time'];
	$session_diff = $current_time - $session_start_time;
	
	if($session_diff >= 180){
	    unset($_SESSION['rfi_data']);
	    unset($form_state['values']);
	    unset($form_state['storage']);
	   // drupal_set_message(t('Your session has expired, please fill out the form again'), 'error');
	    $form['sess_expire_message'] = array(
	    '#type' => 'item',
	    '#markup' => '<div class="alert-danger" style="padding:2%;">Your session has expired, please fill out the form again.</div>',
	   );
	    $form_state['storage']['step'] = 'asu_rfi_form_data';
	}
    }
   
    $states = asu_rfi_states_data();
    honeypot_add_form_protection($form, $form_state, array('honeypot', 'time_restriction'));
    $form['#id'] = 'asu_rfi_second_form';
    $form['#prefix'] = '<div id="rfi_second_form">';
    $form['#suffix'] = '</div>';
    $form_mode = variable_get('asu_rfi_form_mode');
    if(($form_mode == "test") || (empty($form_mode))){
	$form['form_stage'] = array(
	    '#type' => 'item',
	    '#markup' => t('<div class="rfi_test_mode">The form is in test mode, you can change the mode in <a href="/admin/config/asu/asurfi">admin settings page</a></div>')
	);
    }
   
    $form['markup'] = array(
	'#type' => 'item',
	'#markup' => '<div style="background: green; padding:2%; color: #ffffff !important; width: 100%; text-align: justify;"><strong>Thank you for your interest in Arizona State University!</strong> We will send you information that matches your unique interests. If you would like additional information, please specify below.</div>',
    );
    
    $form['citizenship'] = array(
	'#type' => 'checkbox',
	'#title' => t('I am not a U.S. citizen and do not have a green card.'),
    );
    
    $form['military'] = array(
	'#type' => 'radios',
	'#title' => t('U.S. Veteran admission information and services'),
	'#options' =>  array(
	        "None" => "None",
		"Active Duty" => "Active Duty",
		"National Guard" => "National Guard",
		"Veteran" => "Veteran",
		"Armed forces reserve" => "Armed forces reserve",
		"Spouse/Dependent" => "Spouse/Dependent"
	    ),
	'#size' => 30,
    );
     
    $form['address_info'] = array(
	'#type' => 'fieldset',
	'#title' => 'Please also send me information to the following address',
	'#collapsible' => TRUE,
	'#collapsed' => FALSE,
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
	'#default_value' =>  isset($_SESSION['rfi_data']['state']) ? $_SESSION['rfi_data']['state'] : NULL,
    );
  
    $form['address_info']['zipcode'] = array(
	'#type' => 'textfield',
	'#title' => t('Postal code'),
	'#size' => 30,
	'#maxlength' => 15,
	'#default_value' => $form_state['storage']['zipcode'],
    );
    
    $form['questions'] = array(
        '#type' => 'textarea',
        '#title' => t('I also need assistance with the following - limit 255 characters'),
        '#cols' => 60,
        '#resizable' => TRUE,
        '#rows' => 5,
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
    
    $form['back'] = array(
     '#type' => 'submit',
      '#attributes' =>  array('class' => array('rfi_button')),
      '#value' => t('Back'),
      '#submit' => array('asu_rfi_form_data'),
    );
    
    $form['submit'] = array(
     '#type' => 'submit',
      '#attributes' =>  array('class' => array('rfi_button')),
      '#value' => t('Request info'),
    );
    
    return $form;
}


function asu_rfi_second_form_validate($form,&$form_state){

//When Back button on multi-step form is clicked, skip validation on the current page
    if($form_state['values']['op'] == 'Back') {
	drupal_get_messages('error');
	drupal_add_js("$('html, body').animate({ scrollTop: $('#asu-rfi-form-data').offset().top - 100}, 1000);",'inline');
	return TRUE;
    }
    $stcountry = $form_state['storage']['country'];
    $address = check_plain($form_state['values']['address']);
    $city = check_plain($form_state['values']['city']);
    $state = check_plain($form_state['values']['state']);
    $zip = check_plain($form_state['values']['zipcode']);
    //validate address
    if(!empty($address)){
      if( !preg_match("/^[a-zA-Z0-9\.\s-_,#]+$/",$address)){
	  form_set_error('address', t('Address field accepts only plain text.'));
      }
    }
    //validate city
    if(!empty($city)){
	if( !preg_match('/^[\p{L}\p{N} .-]+$/u', $city)) {
	    form_set_error('city', t('City is invalid.'));
	}
    } 
  

    //validate zip code
    if(empty($zip)){
	if(!empty($stcountry) && ($stcountry == "United States")){
	    form_set_error('zipcode', t('Postal code field is required.'));
	}
    }
  
    if(!empty($zip)){
	if($stcountry == "United States"){
	    if((strlen($zip) < 5)){
		form_set_error('zipcode', t('Postal code cannot be less than 5 digits.'));
	    }
	    if( !preg_match("/^[0-9]{5}+$/",$zip)){
		form_set_error('zipcode', t('Postal code accepts 5 digits only.'));
	    }
	}
	else{
	    if( !preg_match("/^[a-zA-Z0-9\s-_]+$/",$zip)){
		form_set_error('zipcode', t('Postal code is not valid.'));
	    }
	    if((strlen($zip) < 4)){
		form_set_error('zipcode', t('Postal code cannot be less than 4 characters.'));
	    }
	    if(strlen($zip) > 20){
		form_set_error('zipcode', t('Postal code cannot be longer than 20 characters.'));
	    }
	}
    }

    //validate comments
    if(!empty($form_state['values']['questions']))
    {
	if(strlen($form_state['values']['questions']) > 255){
	    form_set_error('questions', t('Comments are limited to a maximum of 255 characters.'));
	}
    }
}



/* Second form submit handler */
function asu_rfi_second_form_submit($form, &$form_state){
	    unset($_SESSION['rfi_data']);
   
	    $fname =  check_plain($form_state['storage']['first_name']);
	    $lname = ucfirst(check_plain($fname));
	    $lname = check_plain($form_state['storage']['last_name']);
	    $lname = ucfirst(check_plain($lname));
	    $phone = $form_state['storage']['phone'];
	    $dob = check_plain($form_state['storage']['birthdate']);
	    $email = check_plain($form_state['storage']['email']) ;
	    $zipcode = check_plain($form_state['values']['zipcode']) ;
	    $country = $form_state['storage']['country'] ;
	    $semester = $form_state['storage']['semester_name'];
	    $major = $form_state['storage']['prog_plan'];
	    $student_type = $form_state['storage']['student_type'];
	    $address = check_plain($form_state['values']['address']);
	    $form_state['storage']['address'] = $address;
	    $uniqueid = $email.$major;
	    if($form_state['values']['state'] == '0'){
		$state = '';
	    }
	    else{
		$state = $form_state['values']['state'];
	    }
	    //just to make sure if the zipcode has been updated in the second form
	    $form_state['storage']['zipcode'] = $zipcode;
	    $city = check_plain($form_state['values']['city']);
	    $form_state['storage']['city'] = $city;
	    
	    $form_state['storage']['state'] = $state;
	    $veteran = $form_state['values']['military'];
	    $form_state['storage']['military'] = $veteran;
	    $webform_url = $form_state['values']['webform_url'];
	    $ip_address = $form_state['storage']['ip_address'];
	    $citizen = $form_state['values']['citizenship'];
	    $node_entity_id = $form_state['storage']['submission_nodeid'];
	    $form_state['storage']['type_of_form'] = $form_state['values']['type_of_form'];
	    
	    if(empty($citizen)){
		$international = "FALSE";
		$form_state['storage']['citizenship'] = "FALSE";
	    }
	    else{
		$international = "TRUE";
		$form_state['storage']['citizenship'] = "TRUE";
	    }
	    if(!empty($veteran)){
		$military = $form_state['values']['military'];
	    }
	    else{
		$military = "";
	    }
	    $form_state['storage']['military'] = $military;
	    
	    $questions = check_plain($form_state['values']['questions']);
	    $form_state['storage']['questions'] = $questions;
	    $current_time = time();
	    $node = node_load($node_entity_id);
	    
	    $node->field_rfi_state[LANGUAGE_NONE][0]['value'] = $state;
	    $node->field_rfi_veteran[LANGUAGE_NONE][0]['value'] = $veteran;
	    $node->field_rfi_question[LANGUAGE_NONE][0]['value'] = check_plain($questions);
	    $node->field_rfi_submission_status[LANGUAGE_NONE][0]['value'] = 'Complete';
	    $node->field_rfi_address[LANGUAGE_NONE][0]['value'] = $address;
	    $node->field_rfi_city[LANGUAGE_NONE][0]['value'] = $city;
	    $node->field_rfi_international[LANGUAGE_NONE][0]['value'] = $international;
	    $node->field_rfi_zipcode[LANGUAGE_NONE][0]['value'] = $zipcode;
	    
	    node_save($node);
	    
	    //used in confirmation nodes
	    $coded_nid = base64_encode($node_entity_id);
	    $coded_major = base64_encode($form_state['storage']['program_code']);
	    $coded_college =  base64_encode($form_state['storage']['college_name']);
	    $coded_college_code = base64_encode($form_state['storage']['college_code']);
	    $coded_zip = base64_encode($zipcode);
	    $coded_country = base64_encode($country);
	    /*If graduate degree is submitted, root the from to graduate posting function.
	     *Grab the node id of cinfirmation page from admin settings page if exists and redirect the user to confirmation node. If the node id doesn't exist, take the user to built in confirmation page*
	     */
	    if($form_state['storage']['prospect_level'] == "Graduate"){
		asu_rfi_grad_post($form_state['storage']);
		$grad_confid =  variable_get('asu_rfi_grad_confirm_node');
		if(!empty($grad_confid)){
		    $galias = drupal_lookup_path('alias', $path = "node/$grad_confid", $path_language = NULL);
		    if(!empty($alias)){
			drupal_goto("$galias",array('query' => array('pro' => $coded_college, 'maj' => $coded_major, 'sub' => $coded_nid, 'ccode'=> $coded_college_code,'cat' => 'Grad RFI', 'zcode' => $coded_zip, 'con' => $coded_country)));
		    }
		    else{
			drupal_goto("node/$grad_confid",array('query' => array('pro' => $coded_college, 'maj' => $coded_major, 'sub' => $coded_nid, 'ccode'=> $coded_college_code,'cat' => 'Grad RFI','zcode'=>$coded_zip,'con' => $coded_country)));
		    }
		}
		else{
		    drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
		}
		//clear session data
		unset($_SESSION['rfi_data']);
	    }
	    
	    /*If undergraduate degree is submitted, root the from to undergraduate posting function below.
	     *Grab the node id of cinfirmation page from admin settings page if exists and redirect the user to confirmation node. If the node id doesn't exist, take the user to built in confirmation page*
	     */
	    if($form_state['storage']['prospect_level'] == "Undergraduate"){
		asu_rfi_undergrad_post($form_state['storage']); //-- To be used in future
		$undergrad_confid = variable_get('asu_rfi_undergrad_confirm_node');
	      
		if(!empty($undergrad_confid)){
		    $ualias = drupal_lookup_path('alias', $path = "node/$undergrad_confid", $path_language = NULL);
		    if(!empty($ualias)){
			drupal_goto("$ualias",array('query' => array('pro' => $coded_college, 'maj' => $coded_major, 'sub' => $coded_nid, 'ccode'=> $coded_college_code, 'cat' => 'UG RFI', 'zcode' => $coded_zip, 'con' => $coded_country)));
		    }
		    else{
			drupal_goto("node/$undergrad_confid", array('query' => array('pro' => $coded_college, 'maj' => $coded_major, 'sub' => $coded_nid, 'ccode'=> $coded_college_code, 'cat' => 'UG RFI','zcode' => $coded_zip, 'con' => $coded_country)));
		    }
		}
		else{
		   drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
		}
		unset($_SESSION['rfi_data']);
	    }
}


/******Long RFI form generation******/
/***********************************/
/**********************************/
function asu_rfi_long_form($delta, $programs, $form_type){
    return drupal_get_form('asu_rfi_long_form_data',  $programs, $form_type);
  
    // Add no-store in Cache-Control.
    drupal_add_http_header(
	'Cache-Control', 
	'no-store, no-cache, must-revalidate, post-check=0, pre-check=0', 
	FALSE
    );
    // Hack for Safari
    drupal_add_js('jQuery(window).unload(function(){});', array('type' => 'inline'));  
}



/** construct the form **/
function asu_rfi_long_form_data($form, &$form_state, $programs, $form_type){
    //include theme css
    drupal_add_css(drupal_get_path('module', 'asu_rfi') .'/theme/asu_rfi.css');
    // Add no-store in Cache-Control to clear all data when browser back button is clicked
    drupal_add_http_header(
	'Cache-Control', 
	'no-store, no-cache, must-revalidate, post-check=0, pre-check=0', 
	FALSE
    );
    // Hack for Safari
    drupal_add_js('jQuery(window).unload(function(){});', array('type' => 'inline'));  
    drupal_page_is_cacheable(FALSE);
  
    $start_dates = _asu_rfi_sem_dates();
    $country = asu_rfi_countries_data();
    $states = asu_rfi_states_data();
    for($idate = 0; $idate < 4; $idate++){
        $date = date('Y') + $idate;
        $datekey = substr_replace($date,'',1,-2);
        $year[$datekey] = $date;
    }
    
    $form = array();
    
    honeypot_add_form_protection($form, $form_state, array('honeypot', 'time_restriction'));
    
    $form_mode = variable_get('asu_rfi_form_mode');
    if((variable_get('asu_rfi_form_mode') == "test") || empty($form_mode)){
	$form['form_stage'] = array(
	    '#type' => 'item',
	    '#markup' => t('<div class="rfi_test_mode">The form is in test mode, you can change the mode in <a href="/admin/config/content/asurfi">admin settings page</a></div>')
        );
    }
    
    /*$middleware_key = variable_get('asu_rfi_form_auth_key',NULL);
    if(empty($middleware_key)){
	$form['form_middle_post'] = array(
	'#type' => 'item',
        '#markup' => t('<div class="rfi_middlekey">The middleware authentication key is currently not set, it is required to post data to middleware. You can request the key fron <a href="https://webforms.asu.edu/content/access-rfi-middleware-request">here</a> and add the key provided at the <a href="/admin/config/asu/asurfi">RFI admin settings page</a></div>')
        );
    }*/
    
    $form['req_header_text'] = array(
        '#value' => '<h4>Please complete and submit the form below, and a representative will contact you about enrolling at ASU</h4>'
    );
    
    $form['req_helper'] = array(
        '#value' => '<p>Fields marked with <span style = "color:#FF0000;">*</span> are required.</p>',
    );
    
    $form['degree_type'] = array(
	'#type' => 'hidden',
	'#size' => 30,
	'#maxlength' => 64,
	'#default_value' => $form_type,
    ); 
    
    $form['my_interest'] = array(
	'#type' => 'fieldset',
	'#title' => 'My interests',
	'#collapsible' => TRUE,
	'#collapsed' => FALSE,
	'#size' => 30,
    );
     
    $form['my_interest']['student_type'] = array(
	'#type' => 'select',
	'#title' => t('I will be a future'),
	'#options' => array('First Time Freshman'=>'First Time Freshman', 'Transfer'=>'Transfer',' Readmission'=>'Readmission'),
	'#states' => array(
	    'visible' => array(
		':input[name="degree_type"]' => array('value' => 'ugrad_longform'),
	    ),
	), 
	'#required' => TRUE,
	'#attributes' => array('class' => array('reqinfo_student_type')),
    );
    
    $form['my_interest']['program_code'] = array(
	'#type' => 'select',
	'#title' => t('My program of interest'),
	'#options' => $programs,
	'#required' => TRUE,
    );
     
    $form['my_interest']['start_date'] = array(
	'#type' => 'select',
	'#title' => t('My start date'),
	'#options' => $start_dates,
	'#required' => TRUE,
    );
    
    $form['about_me'] = array(
	'#type' => 'fieldset',
	'#title' => 'About me',
	'#collapsible' => TRUE,
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
	'#attributes' =>  array('class' => array('rfi_phone')),
    );
   
   $form['about_me']['mobile_check'] = array(
	'#type' => 'checkbox',
	'#title' => t('This is a USA mobile number and I would like to receive information via SMS text messaging'),
	'#size' => 30,
	'#maxlength' => 20,
	'#required' => FALSE,
	'#attributes' =>  array('class' => array('rfi_mobile')),
    );
  
    $form['about_me']['country'] = array(
	'#id' => 'rfi-country',
	'#type' => 'select',
        '#options' => $country,
	'#title' => t('Country'),
	'#required' => TRUE,
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
    );
    
    
    //include modal help text for date of birth
    $modal_data = '<!-- Button trigger modal -->
    <span class="fa fa-info-circle" data-toggle="modal" data-target="#myModal"></span>
    <!-- Modal -->
    <div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
      <div class="modal-dialog">
	<div class="modal-content">
	  <div class="modal-body">
	    Your birthday is important! Not only will we send you a birthday message, it helps us keep your information secure as a unique identifier for your online submission.
	  </div>
	  <div class="modal-footer">
	    <div class="btn btn-default" data-dismiss="modal">Close</div>
	  </div>
	</div>
      </div>
    </div>';

    // The below field creates illusion as part of date of birth field. I had to add this field to avoid validation error message containing modal data
    $form['about_me']['dob_field'] = array(
	'#type' => 'item',
        '#markup' => '<label><strong>Date of birth <span class="form-required">*</span></strong></label> '.$modal_data,
    );

    $form['about_me']['birthdate'] = array(
	'#type' => 'textfield',
	'#title' => t('Date of birth'),
	'#description' => t('Format: mm/dd/yyyy'),
	'#title_display' => 'invisible',
	'#size' => 30,
	'#maxlength' => 30,
	'#required' => TRUE,
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
    );
    
    $form['about_me']['military'] = array(
	'#type' => 'radios',
	'#title' => t('U.S. Veteran admission information and services'),
	'#options' =>  array(
	    "None" => "None",
	    "Active Duty" => "Active Duty",
	    "National Guard" => "National Guard",
	    "Veteran" => "Veteran",
	    "Armed forces reserve" => "Armed forces reserve",
	    "Spouse/Dependent" => "Spouse/Dependent"
        ),
	'#size' => 30,
    );
     
    $form['address_info'] = array(
	'#type' => 'fieldset',
	'#title' => 'Please also send me information to the following address',
	'#collapsible' => TRUE,
	'#collapsed' => FALSE,
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
        '#title' => t('I also need assistance with the following - limit 255 characters'),
        '#cols' => 60,
        '#resizable' => TRUE,
        '#rows' => 5,
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
    
    
    $form['submit'] = array(
	'#type' => 'submit',
	'#value' => t('Request info'),
	'#attributes' =>  array('class' => array('rfi_button')),
    );
    return $form;
    
}
 

 
/* Function to validate submitted values*/

function asu_rfi_long_form_data_validate($form,&$form_state){
    $stype = $form_state['values']['student_type'];
    $fname = $form_state['values']['first_name'];
    $fname = ucfirst($fname);
    $lname = $form_state['values']['last_name'];
    $lname = ucfirst($lname);
    $email = $form_state['values']['email'];
    $phone = $form_state['values']['phone'];
    $zip =  $form_state['values']['zipcode'];
    $country = $form_state['values']['country'];
    $address = check_plain($form_state['values']['address']);
    $state = $form_state['values']['state'];
    $city = check_plain($form_state['values']['city']);
    
    $questions = check_plain($form_state['values']['questions']);
    $form_type = $form_state['values']['degree_type'];
    $birthdate = $form_state['values']['birthdate'];
    $mobile_check = $form_state['values']['mobile_check'];
   
    //validate first name
    if( !preg_match("/^[a-zA-Z\.\s-_]+$/",$fname)){
        form_set_error('first_name', t('First name field accepts only plain text.'));
    }
    //validate last name
   if( !preg_match("/^[a-zA-Z\.\s-_]+$/",$lname)){
        form_set_error('last_name', t('Last name field accepts only plain text.'));
	
   }
   //validation for email
   
    if( !preg_match("/^([a-zA-Z0-9])+([a-zA-Z0-9\._-])*@([a-zA-Z0-9_-])+([a-zA-Z0-9\._-]+)*(\.[a-zA-Z]{2,6})+$/", $email)){
	  form_set_error('email', t('You entered an invalid email.'));
    }
  
    //validation for phone number
    /** If mobile number field is checked, then check for USA format, else check for special characters **/
     $scam_num = substr($phone, 0, 3);
    if($mobile_check != 0){
	if( !preg_match("/^([1]-)?([0-9]{3}[-|.][0-9]{3}[-|.][0-9]{4})$/i", $phone) || ($scam_num == "555" )) {
	    form_set_error('phone', t('You entered an invalid Phone number.'));
	}
    }
    else{
	if( !preg_match("/^[0-9\.\s-_+\(\)]+$/", $phone) || ($scam_num == "555" )) {
	     form_set_error('phone', t('You entered an invalid Phone number.'));
	}
    }
    
    //validate zip code
    if(empty($zip)){
	if(!empty($country) && ($country == "United States")){
	    form_set_error('zipcode', t('Postal code field is required.'));
	}
    }
  
    if(!empty($zip)){
	if($country == "United States"){
	    if((strlen($zip) < 5)){
		form_set_error('zipcode', t('Postal code cannot be less than 5 digits.'));
	    }
	    if(!preg_match('/^[0-9]{5}+$/',$zip)){
		form_set_error('zipcode', t('Postal code accepts 5 digits only.'));
	    }
	}
	else{
	    if( !preg_match("/^[a-zA-Z0-9\s-]+$/",$zip)){
		form_set_error('zipcode', t('Postal code is not valid.'));
	     }
	    if((strlen($zip) < 4)){
		form_set_error('zipcode', t('Postal code cannot be less than 4 characters.'));
	    }
	    if(strlen($zip) > 20){
		form_set_error('zipcode', t('Postal code cannot be longer than 20 characters.'));
	    }
	}
    }
  
   //validate birthdate
  
   if(!empty($birthdate)){ 
	//get number of occurences of '/' in dob
	$slashes = substr_count($birthdate, '/');
	if($slashes == 2){
	    $date_format = explode('/',$birthdate);
	    $month = $date_format[0];
	    $day = $date_format[1];
	    $year = $date_format[2];
	    $current_year = date('Y');
	    $year_limit = $current_year - 1;
	    $isLeapYear = date('L');
	    if(strlen($birthdate) < 11){
		
		if(($month < 1) || ($month > 12)){
		    form_set_error('birthdate', t('Month range has to be between 1 and 12.'));
		    form_set_error('dob_field',t(' '));
		}
		
		if(($month == 1) || ($month == 3) || ($month == 5) || ($month == 7) || ($month == 8) || ($month == 10) || ($month == 12)){
		    if(($day < 1) || ($day > 31)){
			form_set_error('birthdate', t('Date range has to be between 1 and 31.'));
			form_set_error('dob_field',t(' '));
		    }
		}
		
		if(($month == 4) || ($month == 6) || ($month == 9) || ($month == 11)){
		    if(($day < 1) || ($day > 30)){
			form_set_error('birthdate', t('Date range has to be between 1 and 30.'));
			form_set_error('dob_field',t(' '));
		    }
		}
		
		if($month == 2) {
		    if($isLeapYear == 1){
			if(($day < 1) || ($day > 29)){
			    form_set_error('birthdate', t('Date range has to be between 1 and 29.'));
			    form_set_error('dob_field',t(' '));
			}
		    }
		    if($isLeapYear == 0){
			if(($day < 1) || ($day > 28)){
			    form_set_error('birthdate', t('Date range has to be between 1 and 28.'));
			    form_set_error('dob_field',t(' '));
			}
		    }
		}
		
		if(strlen($year) != 4){
		    form_set_error('birthdate', t('Year has to be 4 digits.'));
		}
		
		if($year > $year_limit){
		    form_set_error('birthdate', t('Year cannot be greater than '.$year_limit));
		}
		
		if(!preg_match("/^(0[1-9]|1[012])[\-\/.](0[1-9]|[12][0-9]|3[01])[\-\/.](19|20)\d\d$/", $birthdate)){
		    form_set_error('birthdate', t('Date of birth accepts the format mm/dd/yyyy.'));
		    form_set_error('dob_field',t(' '));
		}
	    }
	    else{
		form_set_error('birthdate', t('Date of birth is invalid, it accepts the format mm/dd/yyyy.'));
		form_set_error('dob_field',t(' '));
	    }
	}
	else{
	    form_set_error('birthdate', t('Date of birth is invalid, it accepts the format mm/dd/yyyy.'));
	    form_set_error('dob_field',t(' '));
	}
    }
    else{
	form_set_error('birthdate', t('Date of birth is required.'));
	form_set_error('dob_field',t(' '));
    }  
    
    //validate address
    if(!empty($address)){
	if( !preg_match("/^[a-zA-Z0-9\.\s-_,#]+$/",$address)){
	    form_set_error('address', t('Address field accepts only plain text.'));
	}
    }
 
    //validate city
    if(!empty($city)){
	if( !preg_match('/^[\p{L}\p{N} .-]+$/u', $city)) {
	    form_set_error('city', t('City is invalid.'));
	}
    }
 
    //validation for questions
    if(!empty($questions)){
	$len =  strlen($questions); // validation for comments character limit to 255
	if ($len > 255) 
	{
	    form_set_error('questions', t('Comments are limited to a maximum of 255 characters.'));
	}
    }
}

/* submit handler */
function asu_rfi_long_form_data_submit($form, &$form_state){
   
   global $user;
 
    //Get the type of the form. If the form is grad form, set prospect_level value to "Graduate", else "Undergraduate"
    if(($form_state['values']['degree_type']) == "graduate_longform"){
	$stype = 'Graduate';
	$long_form_type = "Graduate long form";
	$form_state['values']['prospect_level'] = "Graduate";
    }
    else{
	$stype = $form_state['values']['student_type'];
	$long_form_type = "Undergraduate long form";
	$form_state['values']['prospect_level'] = "Undergraduate";
    }
    $fname = check_plain($form_state['values']['first_name']);
    $lname = check_plain($form_state['values']['last_name']);
    $email = check_plain($form_state['values']['email']);
    $phone = $form_state['values']['phone'];
    $form_state['values']['phone'] = $form_state['values']['phone'];
    
    $sms_opted = $form_state['values']['mobile_check'];
  
    //check if the phone number already has 1 prepeneded. If yes, just pass phome number to sms field, else prepend 1.
    if(!empty($sms_opted)){
	if(substr($form_state['values']['phone'], 0,1) != "1"){
	  $form_state['values']['mobile_check'] = '1'.$form_state['values']['phone'];
	}
	else{
	    $form_state['values']['mobile_check'] = $form_state['values']['phone'];
	}
    }
    else{
	$form_state['values']['mobile_check'] =  '';
    }
   
    $zip =  check_plain($form_state['values']['zipcode']);
    $address = check_plain($form_state['values']['address']);
  
    if($form_state['values']['state'] == '0'){
      $state = '';
    }
    else{
       $state = $form_state['values']['state'];
    }
    $form_state['values']['state'] = $state;
    $city = check_plain($form_state['values']['city']);
    
    if(!empty($form_state['values']['country'])){
	$country = check_plain($form_state['values']['country']);
    }
    else{
	 $country = '';
    }
    $semester = check_plain($form_state['values']['start_date']);
    $ipaddress = $form_state['values']['ip_address'];
    
    //Questions
    if(!empty($form_state['values']['questions'])){
	$questions = check_plain($form_state['values']['questions']);
    }
    else{
	$questions = '';
    }
   
    //Citizenship
    if(empty($form_state['values']['citizenship'])){
	$international = "FALSE";
	$form_state['values']['citizenship'] = "FALSE";
    }
    else{
	$international = "TRUE";
	$form_state['values']['citizenship'] = "TRUE";
    }
    if(!empty($form_state['values']['military'])){
	$veteran = $form_state['values']['military'];
    }
    else{
	$veteran = '';
    }
 
    $program = $form_state['values']['program_code'];
    $dobdate =  $form_state['values']['birthdate'];
  
    //get start date array
   
    $semdates = _asu_rfi_sem_dates();
  
    if(array_key_exists($semester, $semdates)){
	$semester_name = $semdates[$semester];
    }
    $form_state['values']['semester_name'] = $semester_name;
    
    //Query database to get program name based on the program code submitted in the form
    $program_name = db_query('select field_asu_degree_awarded_value from field_data_field_asu_degree_awarded mj join field_data_field_asu_academic_plan ap on mj.entity_id = ap.entity_id where ap.field_asu_academic_plan_value = :plan', array(':plan' => $program))->fetchField();
    
    //Get college code from database based on program code
    $college_code = db_query('select field_asu_academic_program_value from field_data_field_asu_academic_program prog join field_data_field_asu_academic_plan plan on prog.entity_id = plan.entity_id where plan.field_asu_academic_plan_value = :plancode', array(':plancode' => $program))->fetchField();
    
    
    //Get college name from database based on program code
    $college_name = db_query('select field_asu_diploma_description_value from field_data_field_asu_diploma_description progn join field_data_field_asu_academic_plan plann on progn.entity_id = plann.entity_id where plann.field_asu_academic_plan_value = :plancode', array(':plancode' => $program))->fetchField();
    //Create node
    $ent_values = array(
	'type' => 'asu_rfi',
	'uid' => $user->uid,
	'status' => 0,
	'comment' => 1,
	'promote' => 0,
     );
    $entity = entity_create('node', $ent_values);
    $ewrapper = entity_metadata_wrapper('node', $entity);
    $ewrapper->title->set($fname);
    $ewrapper->field_rfi_first_name->set($fname);
    $ewrapper->field_rfi_last_name->set($lname);
    $ewrapper->field_rfi_student_type->set($stype);
    $ewrapper->field_rfi_email->set($email);
    $ewrapper->field_rfi_phone->set($phone);
    $ewrapper->field_rfi_country->set($country);
    $ewrapper->field_rfi_zipcode->set($zip);
    $ewrapper->field_rfi_start_term_code->set($semester);
    $ewrapper->field_rfi_program->set($program);
    $ewrapper->field_rfi_college_code->set($college_code);
    $ewrapper->field_rfi_form_type->set($long_form_type);
    $ewrapper->field_rfi_ip_address->set(intval($ipaddress));
    $ewrapper->field_rfi_state->set($state);
    $ewrapper->field_rfi_veteran->set($veteran);
    $ewrapper->field_rfi_question->set(check_plain($questions));
    $ewrapper->field_rfi_dob->set(base64_encode($dobdate));
    $ewrapper->field_rfi_submission_status->set('Complete');
    $ewrapper->field_rfi_address->set($address);
    $ewrapper->field_rfi_city->set($city);
    $ewrapper->field_rfi_international->set($international);
    $ewrapper->field_rfi_start_term->set($semester_name);
    $ewrapper->field_rfi_program_name->set($program_name);
    $ewrapper->field_rfi_college_name->set($college_name);
    $ewrapper->field_rfi_prospect_level->set($form_state['values']['prospect_level']);
    
    $ewrapper->save();
  
    //send the confirmation email
    asu_rfi_email($form_state['values']['program_code'], $email);
    
    $form_state['values']['submission_nodeid'] = $entity->nid;
    
    //used in confirmation nodes
    
    $coded_major = base64_encode($program);
    $coded_college =  base64_encode($college_name);
    $coded_college_code = base64_encode($college_code);
    $coded_nid = base64_encode($entity->nid);
    $coded_zip = base64_encode($zip);
    $coded_country = base64_encode($country);
    
    if($form_state['values']['prospect_level'] == "Graduate"){
	asu_rfi_grad_post($form_state['values']);
	$grad_confid =  variable_get('asu_rfi_grad_confirm_node');
	if(!empty($grad_confid)){
	    $galias = drupal_lookup_path('alias', $path = "node/$grad_confid_confid", $path_language = NULL);
	    if(!empty($galias)){
		drupal_goto("$galias", array('query' => array('pro' => $coded_college, 'maj' => $coded_major, 'sub' => $coded_nid, 'ccode'=> $coded_college_code,'cat' => 'Grad RFI','zcode' => $coded_zip,'con' => $coded_country)));
	    }
	    else{
	       drupal_goto("node/$grad_confid",array('query' => array('pro' => $coded_college, 'maj' => $coded_major, 'sub' => $coded_nid, 'ccode"'=> $coded_college_code,'cat' => 'Grad RFI','zcode' => $coded_zip,'con' => $coded_country )));
	    }
	}
	else{
	   drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
	}
    }
   
   
    if($form_state['values']['prospect_level'] == "Undergraduate"){
	asu_rfi_undergrad_post($form_state['values']);
	$undergrad_confid = variable_get('asu_rfi_undergrad_confirm_node');
	if(!empty($undergrad_confid)){
	    $ualias = drupal_lookup_path('alias', $path = "node/$undergrad_confid", $path_language = NULL);
	    if(!empty($ualias)){
	       drupal_goto("$ualias", array('query' => array('pro' => $coded_college, 'maj' => $coded_major, 'sub' => $coded_nid, 'ccode'=> $coded_college_code,'cat' => 'UG RFI','zcode' => $coded_zip, 'con' => $coded_country)));
	    }
	    else{
	       drupal_goto("node/$undergrad_confid", array('query' => array('pro' => $coded_college, 'maj' => $coded_major, 'sub' => $coded_nid, 'ccode"'=> $coded_college_code, 'cat' => 'UG RFI','zcode' => $coded_zip, 'con' => $coded_country )));
	    }
	}
	else{
	   drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
	}
   }
}

/******* General current students form *******/
/***********************************/
/**********************************/
function asu_rfi_current_form($delta, $programs, $form_type){
    return drupal_get_form('asu_rfi_current_form_data',  $programs, $form_type);
}



/** construct the form **/
function asu_rfi_current_form_data($form, &$form_state, $programs, $form_type){
   

    $form = array();
    honeypot_add_form_protection($form, $form_state, array('honeypot', 'time_restriction'));  
    $form_mode = variable_get('asu_rfi_form_mode');
    if((variable_get('asu_rfi_form_mode') == "test") || empty($form_mode)){
     $form['form_stage'] = array(
	'#type' => 'item',
        '#markup' => t('<div class="rfi_test_mode">The form is in test mode, you can change the mode in <a href="/admin/config/content/asurfi">admin settings page</a></div>')
        );
    } 
    $form['req_header_text'] = array(
        '#value' => '<h4>Please complete and submit the form below, and a representative will contact you about enrolling at ASU</h4>'
    );
    
    $form['req_helper'] = array(
        '#value' => '<p>Fields marked with <span style = "color:#FF0000;">*</span> are required.</p>',
    );
    
    $form['degree_type'] = array(
	'#type' => 'hidden',
	'#size' => 30,
	'#maxlength' => 64,
	'#default_value' => $form_type,
    ); 
   
    $form['about_me'] = array(
     '#type' => 'fieldset',
     '#title' => 'About me',
     '#collapsible' => TRUE,
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
        '#title' => t('I also need assistance with the following - limit 255 characters'),
        '#cols' => 60,
        '#resizable' => TRUE,
        '#rows' => 5,
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
    
    $form['submit'] = array(
     '#type' => 'submit',
      '#attributes' =>  array('class' => array('rfi_button')),
      '#value' => t('Request info'),
    );
    
   return $form;
}
 

 
/* Function to validate submitted values*/

function asu_rfi_current_form_data_validate($form,&$form_state){
    $fname = $form_state['values']['first_name'];
    $fname = ucfirst($fname);
    $lname = $form_state['values']['last_name'];
    $lname = ucfirst($lname);
    $email = $form_state['values']['email'];
    $phone = $form_state['values']['phone'];
   
    $questions = check_plain($form_state['values']['questions']);
    $form_type = $form_state['values']['degree_type'];
   
    //validate first name
    if( !preg_match("/^[a-zA-Z0-9\.\s-_]+$/",$fname)){
	form_set_error('first_name', t('First name field accepts only plain text.'));
	  
    }
    //validate last name
    if( !preg_match("/^[a-zA-Z0-9\.\s-_]+$/",$lname)){
	form_set_error('last_name', t('Last name field accepts only plain text.'));
	  
    }
    //validation for email
    if( !preg_match("/^([a-zA-Z0-9])+([a-zA-Z0-9\._-])*@([a-zA-Z0-9_-])+([a-zA-Z0-9\._-]+)+$/", $email)){
	form_set_error('email', t('You entered an invalid email.'));
    }
    //validation for phone number
     
    $scam_num = substr($phone, 0, 3);
    if( !preg_match("/^([1]-)?([0-9]{3}[-|.][0-9]{3}[-|.][0-9]{4})$/i", $phone) || ($scam_num == "555" )) {
	form_set_error('phone', t('You entered an invalid Phone number.'));
    }
  
    //validation for questions
    if(!empty($questions)){
	$len =  strlen($questions); // validation for comments character limit to 255
	if ($len > 255) 
	{
	    form_set_error('questions', t('Comments are limited to a maximum of 255 characters.'));
	}
    }
}

/* submit handler of current students form*/
function asu_rfi_current_form_data_submit($form, &$form_state){
    global $user;
   
    $fname = $form_state['values']['first_name'];
    $lname = $form_state['values']['last_name'];
    $email = $form_state['values']['email'];
    $phone = $form_state['values']['phone'];
    $form_type = $form_state['values']['degree_type'];
    $ipaddress = $form_state['values']['ip_address'];
   
    //Questions
    if(!empty($form_state['values']['questions'])){
	$questions = $form_state['values']['questions'];
    }
    else{
	$questions = '';
    }
    
    $program = $form_state['values']['prog_plan']; 
    $uniqueid = $email.$program ;
  
  
    //Query database to get program name based on the program code submitted in the form
    $program_name = db_query('select field_asu_degree_awarded_value from field_data_field_asu_degree_awarded mj join field_data_field_asu_academic_plan ap on mj.entity_id = ap.entity_id where ap.field_asu_academic_plan_value = :plan', array(':plan' => $program))->fetchField();
    
    //Create node
    $ent_values = array(
	'type' => 'asu_rfi',
	'uid' => $user->uid,
	'status' => 0,
	'comment' => 1,
	'promote' => 0,
    );
   
    $entity = entity_create('node', $ent_values);
    $ewrapper = entity_metadata_wrapper('node', $entity);
    
    $ewrapper->title->set($fname);
    $ewrapper->field_rfi_first_name->set($fname);
    $ewrapper->field_rfi_last_name->set($lname);
    $ewrapper->field_rfi_email->set($email);
    $ewrapper->field_rfi_phone->set($phone);
    $ewrapper->field_rfi_program->set($program);
    $ewrapper->field_rfi_program_name->set($program_name);
    $ewrapper->field_rfi_form_type->set($form_type);
    $ewrapper->field_rfi_ip_address->set(intval($ipaddress));
    $ewrapper->field_rfi_question->set($questions);
    $ewrapper->field_rfi_submission_status->set('Complete');
    $ewrapper->save();
    $coded_nid = base64_encode($entity->nid);
    asu_rfi_email($program, $email);
    drupal_goto("degree-programs/request-info-thank-you/$coded_nid");
 
}



/**Helper function for countries list****/

function asu_rfi_countries_data(){
  
    $countries = db_query("select countryDesc from asu_rfi_countries order by countryDesc asc");
    
    foreach($countries as $country_select){
	$all_countries[$country_select->countryDesc] = $country_select->countryDesc;
    }
    $sort_countries = asort($all_countries);
    $uscont = array("United States"=>"United States");
    $other_countries = array_diff($all_countries, $uscont);
    $other_countries= $uscont + $other_countries;
    
    return $other_countries;
}

/**Helper function for states field****/
function asu_rfi_states_data(){
    $states_query = db_query("select stateDesc from asu_rfi_states_list order by stateDesc asc");
    foreach($states_query as $states){
	$all_states[$states->stateDesc] = $states->stateDesc;
    }
    $option = 'None';
    array_unshift($all_states,$option); 
    return $all_states;
}


/**** Helper function for semester dates ***/
//Function to build start dates options array
function _asu_rfi_sem_dates(){
    
    //Get semester dates from dabatase
    $semdates_query = db_query("select * from {asu_rfi_sem_dates} order by CHAR_LENGTH(semId)");
    foreach($semdates_query as $semester){
	$termdate[$semester->semId] = $semester->semLabel;
    }
  
    //Webservices from middleware pulls all the old semesters and saves into database, the below code display only current and next three years in the drop down.
    // build the date array
    $date = array();
    $month = date('m');
    $day = date('d');
    $new = array();
    $options = array();
    $semester = array("1"=>"Spring","7"=>"Fall");
    $year = date('Y');
  
    for($i = 0;$i<=2; $i++)
    {
	$date[$i] = $year + $i;
	$new[$i]  = substr_replace($date[$i], "", 1, 1);
	if($i == 0){
	    if($year == $date[0] ) // check if it is current year
	    {
	       if(($month<=8))
		    {
		    if(($month != 8) || ($month == 8) &&  ($day <= 14)) {
			$sem = $semester["7"];
			$trim_year = $new[$i]."7";  // append 1 to the key depending on the season. For spring, add 1.
			$list = $date[$i];
			$options[$trim_year] = $list." ".$sem;
		    }
		 
		}
		if(($month >= 8))
		{
		    if(($month != 8) || ($month == 8) &&  ($day > 14)){
			$sem = $semester["1"];
			$trim_year = ($new[$i]+1)."1";  // append 1 to the key depending on the season. For spring, add 1.
			$list = $date[$i]+1;
			$options[$trim_year] = $list." ".$sem;
			
			
			$up_new = $new[$i]+1;
			$new_date = $date[$i]+1;
			$sem = $semester["7"];
			$trim_year = $up_new."7";
			$list = $new_date;
			$options[$trim_year] = $list." ".$sem;
		    }
		}
	    }
        }
	else{
	    $sem = $semester["1"];
	    $trim_year = ($new[$i])."1";  // append 1 to the key depending on the season. For spring, add 1.
	    $list = $date[$i];
	    $options[$trim_year] = $list." ".$sem;
	   
	    $upnext_new = $new[$i] ;
	    $nextnew_date = $date[$i];
	    $next_sem = $semester["7"];
	    $nexttrim_year = $upnext_new."7";
	    $next_list = $nextnew_date;
	    $options[$nexttrim_year] = $next_list." ".$next_sem;
	}
    }
    if(!empty($termdate)){
	$sem_dates_array = array_intersect($termdate, $options);
    }
    else{
	$sem_dates_array = $options;
    }
    return $sem_dates_array;
 
}


/*** Helper function for undergrad form program field****/
//Function to get program data from the node on which the block is displayed
function _asu_rfi_program(){
    $program = array();
    $node = menu_get_object();
    $dcode = $node->title;
    $dname = $node->field_asu_degree_awarded[LANGUAGE_NONE][0]['value'];
    $college_code = $node->field_asu_academic_plan[LANGUAGE_NONE][0]['value'];
    $program[$dcode] = $dname;
   
    return $program;
}
?>