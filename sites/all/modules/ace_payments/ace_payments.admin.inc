<?php

function ace_payments_admin_settings($form, &$form_state) 
{
  $form['Order Confirmation Emails'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Order Confirmation Emails',
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
    '#weight'      => -3,
  );
  
  $form['Order Confirmation Emails']['Admin Email'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Admin Email',
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#weight'      => -2,
  );

  $form['Order Confirmation Emails']['Admin Email']['order_confirmation_admin_emails'] = array(
    '#type'	         => 'textarea',
    '#title'         => 'Admin Email Recipients',
    '#description'   => 'The email addresses of the administrators that should be notified when a user registers. Separate email addresses with commas.',
    '#default_value' => variable_get('order_confirmation_admin_emails', 'ace.asu@asu.edu'),
    '#cols'          => 60,
    '#rows'          => 2,
    '#resizable'     => FALSE,
    '#required'      => TRUE,
  );

  $form['Order Confirmation Emails']['Admin Email']['order_confirmation_admin_email_subject'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Subject',
    '#default_value' => variable_get('order_confirmation_admin_email_subject', ''),
    '#maxlength'     => '128',
    '#size'          => 70,
    '#required'      => TRUE,
  );

  $form['Order Confirmation Emails']['Admin Email']['order_confirmation_admin_email_body']['order_confirmation_admin_email_body'] = array(
    '#type'	         => 'textarea',
    '#title'         => 'Body',
    '#default_value' => variable_get('order_confirmation_admin_email_body', ''),
    '#cols'          => 60,
    '#rows'          => 6,
    '#resizable'     => TRUE,
    '#required'      => TRUE,
  );

  /*$form['Order Confirmation Emails']['Admin Email']['order_confirmation_admin_email_body']['format'] = 
    filter_form(FILTER_FORMAT_SIMPLE, NULL, array('Order Confirmation Emails', 'Admin Email', 'order_confirmation_admin_email_body', 'format'));*/

  $form['Order Confirmation Emails']['User Email'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'User Email',
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#weight'      => -1,
  );

  $form['Order Confirmation Emails']['User Email']['order_confirmation_user_email_subject'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Subject',
    '#default_value' => variable_get('order_confirmation_user_email_subject', ''),
    '#maxlength'     => '128',
    '#size'          => 70,
    '#required'      => TRUE,
  );

  $form['Order Confirmation Emails']['User Email']['order_confirmation_user_email_body']['order_confirmation_user_email_body'] = array(
    '#type'	         => 'textarea',
    '#title'         => 'Body',
    '#default_value' => variable_get('order_confirmation_user_email_body', ''),
    '#cols'          => 60,
    '#rows'          => 6,
    '#resizable'     => TRUE,
    '#required'      => TRUE,
  );

  /*$form['Order Confirmation Emails']['User Email']['order_confirmation_user_email_body']['format'] = 
    filter_form(FILTER_FORMAT_SIMPLE, NULL, array('Order Confirmation Emails', 'User Email', 'order_confirmation_user_email_body'));*/
  
  return system_settings_form($form);
}
