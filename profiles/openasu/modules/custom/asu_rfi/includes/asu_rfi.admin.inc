<?php
// $Id: asu_rfi.admin.inc 

/**
 * @file
 * Administrative request info module settings
 */


function asu_rfi_admin_settings($form_state){
  
  $form = array();
  
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
    '#options' => array('test'=>'Test','live'=>'Production'),
    '#default_value' => variable_get('asu_rfi_form_mode'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Specifiy if the form is in Test mode or Live mode."),
    '#required' => TRUE,
    );
   
   //Will be enabled in future
   /* $form['asu_rfi_form_access']['asu_rfi_form_auth_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Authentication code'),
    '#default_value' => variable_get('asu_rfi_form_auth_key'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Specifiy the form authentication key from middle wear."),
    '#required' => TRUE,
    );
    */ 
     //Error notification email if submissions to Sales force failed for more than 2 days
    $form['asu_rfi_error_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email(s) for error notification'),
    '#default_value' => variable_get('asu_rfi_error_email', NULL),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Email ID(s) of the personnal to be notified if site cannot post RFI submissions to salesforce for more than 2 days."),
    '#size' => 60, 
    '#maxlength' => 150,
    );
   
    
    $form['asu_rfi_form_access']['asu_rfi_google_analytics_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Site identifier for Google Analytics'),
    '#default_value' => variable_get('asu_rfi_google_analytics_key'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Enter 6-10 character string that identifies your site Google Analytics transactions."),
    '#required' => TRUE,
    '#disabled' => FALSE,
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
    '#default_value' => variable_get('asu_rfi_from_email_field'),
    '#description' => t('Subject line of the email to be sent to the user upon form submission'),
    '#size' => 100,
    '#maxlength' => 100,
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#siffix' => '</div>',
    );
    
  
  
   return system_settings_form($form);
 
}

