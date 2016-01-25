<?php
// $Id: asu_rfi.admin.inc 

/**
 * @file
 * Administrative request info module settings
 */


function asu_rfi_admin_settings($form_state){
  
  $form = array();
  
  $form_modes = array('test'=>'Test','prod'=>'Production');
  
   $form['form_stage'] = array(
	'#type' => 'item',
        '#markup' => t('<div class="rfi_note">Important: The RFI submissions will not be posted to Sales force via Middleware unless Authentication code has been added. You can request the authentication key from <a href="https://webforms.asu.edu/content/access-rfi-middleware-request">here</a>. Note that RFI submissions will not be posted to Sales force via Middle ware unless this code has been added</div>'),
    );                 
  
  $form['asu_rfi_form_access'] = array(
    '#type' => 'fieldset',
    '#title' => 'Request info form access settings',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('asu_rfi_admin_field asu_rfi_form_access')),
    );
  
   
   $form['asu_rfi_form_access']['asu_rfi_form_mode'] = array(
    '#type' => 'select',
    '#title' => t('Test/Live Mode'),
    '#options' => $form_modes,
    '#default_value' => variable_get('asu_rfi_form_mode'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Specify if the forms are in Test mode or Live mode. Note: This is a sitewide configuration and will affect all forms. Only site admins can view the forms if they are in Test mode."),
    '#required' => TRUE,
    );
   
   //Will be enabled in future
  $form['asu_rfi_form_access']['asu_rfi_form_auth_key'] = array(
    '#type' => 'hidden',
    '#title' => t('Authentication code'),
    '#default_value' => variable_get('asu_rfi_form_auth_key'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Specifiy the form authentication key from middle wear. You can request the authentication key from <a href='https://webforms.asu.edu/content/access-rfi-middleware-request'>here</a>. Note that RFI submissions will not be posted to Sales force via Middle ware unless this code has been added"),
    '#required' => FALSE,
    );
    
     //Error notification email if submissions to Sales force failed for more than 2 days
    $form['asu_rfi_error_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email(s) for error notification'),
    '#default_value' => variable_get('asu_rfi_error_email', NULL),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Email ID(s) of the personnel to be notified if site cannot post RFI submissions to salesforce for more than 2 days."),
    '#size' => 60, 
    '#maxlength' => 150,
    );
   
    
    $form['asu_rfi_form_access']['asu_rfi_google_analytics_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Site identifier for Google Analytics'),
    '#default_value' => variable_get('asu_rfi_google_analytics_key'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Enter a 6-10 character string to identify your site in Google Analytics transactions."),
    '#required' => TRUE,
    '#disabled' => FALSE,
    );
   
     $form['undergrad_degree_type'] = array(
	'#type' => 'hidden',
	'#size' => 30,
	'#maxlength' => 64,
	'#default_value' =>  variable_get('asu_rfi_ugrad_degree_type'),
    ); 
   
   $form['grad_degree_type'] = array(
	'#type' => 'hidden',
	'#size' => 30,
	'#maxlength' => 64,
	'#default_value' =>  variable_get('asu_rfi_graduate_degree_type'),
    );
    
   $form['asu_rfi_confirm_content'] = array(
    '#type' => 'fieldset',
    '#title' => 'Confirmation webpage content settings. Text box to enter node id will appear after the form has been created.',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('asu_rfi_confirm_email_fields')),
    );
   
   $form['asu_rfi_confirm_content']['asu_rfi_undergrad_confirm_node'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter undergraduate confirmation node id'),
    '#default_value' => variable_get('asu_rfi_undergrad_confirm_node'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Enter a custom node id for the undergraduate form confirmation page. If left empty, default confirmation template will be used."),
    '#states' => array(
      'visible' => array(
        ':input[name="undergrad_degree_type"]' => array('value' => 'undergrad'),
	),
      ),
    );
   
   $form['asu_rfi_confirm_content']['asu_rfi_grad_confirm_node'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter graduate confirmation node id'),
    '#default_value' => variable_get('asu_rfi_grad_confirm_node'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Enter a custom node id for the graduate form confirmation page. If left empty, default confirmation template will be used."),
    '#states' => array(
      'visible' => array(
        ':input[name="grad_degree_type"]' => array('value' => 'graduate'),
	),
      ),
    );
   
    $form['asu_rfi_confirm_email'] = array(
    '#type' => 'fieldset',
    '#title' => 'Confirmation email settings',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('asu_rfi_confirm_email_fields')),
    );
   
    
    $form['asu_rfi_confirm_email']['asu_rfi_from_email_field'] =  array(
    '#type' => 'textfield',
    '#title' => t('"From" email field'),
    '#default_value' => variable_get('asu_rfi_from_email_field'),
    '#description' => t('From email address to be shown in the user\'s email'),
    '#size' => 50,
    '#maxlength' => 25,
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    );
    
    $form['asu_rfi_confirm_email']['asu_rfi_from_name_field'] =  array(
    '#type' => 'textfield',
    '#title' => t('"From" name field'),
    '#default_value' => variable_get('asu_rfi_from_name_field'),
    '#description' => t('Name to be shown in the user\'s email'),
    '#size' => 50,
    '#maxlength' => 25,
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    );
    
    
    $form['asu_rfi_confirm_email']['asu_rfi_email_subject_field'] =  array(
    '#type' => 'textfield',
    '#title' => t('"Subject" field'),
    '#default_value' => variable_get('asu_rfi_email_subject_field'),
    '#description' => t('Subject line of the email to be sent to the user upon form submission'),
    '#size' => 100,
    '#maxlength' => 100,
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#siffix' => '</div>',
    );
    
    return system_settings_form($form);
  
    drupal_set_message('Next steps: Please start adding instances of RFI Master form <a href="/admin/structure/block/instances"><strong>here</strong></a>');
 
}

