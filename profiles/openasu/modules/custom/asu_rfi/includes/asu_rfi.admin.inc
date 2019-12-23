<?php /** @noinspection PhpUnusedParameterInspection */
/** @noinspection PhpUnused */

/**
 * Form definition for ASU RFI form admin settings
 * @return array $form
 */
function asu_rfi_admin_settings() {
  $form = array();
  $form_modes = array('test' => 'Test', 'prod' => 'Production');

  $form['form_stage'] = array(
    '#type' => 'item',
    '#markup' => t('<div class="rfi_note">Important: The RFI submissions will not be'
    . ' posted to Salesforce via Middleware unless a valid authentication code has been added.'
    . ' <a href="https://webforms.asu.edu/content/access-rfi-middleware-request">Request '
    . ' authentication key</a></div>'),
  );
  $form['asu_rfi_form_access'] = array(
    '#type' => 'fieldset',
    '#title' => 'General settings',
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
    '#description' => t("Specify if the forms are in Test mode or Live mode. '
     . 'Note: This is a sitewide configuration and will affect all forms. Only '
     . 'site admins can view the forms if they are in Test mode."),
    '#required' => TRUE,
  );
  // Will be enabled in future
  $form['asu_rfi_form_access']['asu_rfi_form_auth_key'] = array(
    '#type' => 'hidden',
    '#title' => t('Authentication code'),
    '#default_value' => variable_get('asu_rfi_form_auth_key'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t('Don\'t have a code? <a href="https://webforms.asu.edu/content/access-rfi-middleware-request">Request'
    . ' authentication key</a>.'),
    '#required' => FALSE,
  );

  $form['asu_rfi_error_reporting'] = array(
    '#type' => 'fieldset',
    '#title' => 'Error reporting',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('What to do if a submission fails, etc..'),
    '#attributes' => array('class' => array('asu-rfi-admin-error-reporting')),
  );
  $form['asu_rfi_error_reporting']['asu_rfi_error_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email(s) for error notification'),
    '#default_value' => variable_get('asu_rfi_error_email', NULL),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#description' => t("Email addresses to be notified if site cannot post'
     . ' RFI submissions to Salesforce for more than 2 days. Use a comma-delimited'
     . ' list of emails if more than one recipient. (NOTE: Keep the number of email'
     . ' addresses here to a minimum to avoid being blocked as spam by some email (SMTP) servers.)'
     . ' "),
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
    '#default_value' => variable_get('asu_rfi_ugrad_degree_type'),
  );
  $form['grad_degree_type'] = array(
    '#type' => 'hidden',
    '#size' => 30,
    '#maxlength' => 64,
    '#default_value' => variable_get('asu_rfi_graduate_degree_type'),
  );
  $form['confirm_settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'Confirmation settings',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => 'Management of RFI form responses to prospective (or current) students.',
  );
  $form['confirm_settings']['asu_rfi_confirm_content'] = array(
    '#type' => 'fieldset',
    '#title' => 'Confirmation pages',
    '#description' => 'If custom confirmation pages to display (upon successful'
      . ' submission) have been created in this site, please'
      . ' enter its NODE ID in the appropriate field(s) below. If left empty, a'
      . ' default confirmation template will instead be output.',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('asu_rfi_confirm_email_fields')),
  );
  $form['confirm_settings']['asu_rfi_confirm_content']['asu_rfi_undergrad_confirm_node'] = array(
    '#type' => 'textfield',
    '#title' => t('Undergraduate NID'),
    '#default_value' => variable_get('asu_rfi_undergrad_confirm_node'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#size' => 10,
    '#maxlength' => 20,
    '#states' => array(
      'visible' => array(
        ':input[name="undergrad_degree_type"]' => array('value' => 'undergrad'),
      ),
    ),
  );
  $form['confirm_settings']['asu_rfi_confirm_content']['asu_rfi_grad_confirm_node'] = array(
    '#type' => 'textfield',
    '#title' => t('Graduate NID'),
    '#default_value' => variable_get('asu_rfi_grad_confirm_node'),
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#size' => 10,
    '#maxlength' => 20,
    '#states' => array(
      'visible' => array(
        ':input[name="grad_degree_type"]' => array('value' => 'graduate'),
      ),
    ),
  );
  $form['confirm_settings']['asu_rfi_confirm_email'] = array(
    '#type' => 'fieldset',
    '#title' => 'Confirmation Email',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('If desired, enter the following information that'
      . ' will be used when a receipt/confirmation email is sent to the submitter.'),
    '#attributes' => array('class' => array('asu_rfi_confirm_email_fields')),
  );
  $form['confirm_settings']['asu_rfi_confirm_email']['asu_rfi_from_email_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Displayed "From" email address'),
    '#default_value' => variable_get('asu_rfi_from_email_field'),
    '#size' => 50,
    '#maxlength' => 100,
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
  );
  $form['confirm_settings']['asu_rfi_confirm_email']['asu_rfi_from_name_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Displayed "From" name'),
    '#default_value' => variable_get('asu_rfi_from_name_field'),
    '#size' => 50,
    '#maxlength' => 100,
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
  );
  $form['confirm_settings']['asu_rfi_confirm_email']['asu_rfi_email_subject_field'] = array(
    '#type' => 'textfield',
    '#title' => t('"Subject" field'),
    '#default_value' => variable_get('asu_rfi_email_subject_field'),
    '#size' => 100,
    '#maxlength' => 100,
    '#attributes' => array('class' => array('asu_rfi_admin_field')),
    '#siffix' => '</div>',
  );
  $form['#validate'][] = '_asu_rfi_admin_settings_validate';
  return system_settings_form($form);
}

/**
 * Custom hook_form_validate helper function
 * Validate confrimation page NIDs
 * @param $form
 * @param $form_state
 */
function _asu_rfi_admin_settings_validate($form, $form_state) {
  $confirm = array(
    'asu_rfi_undergrad_confirm_node' => $form_state['values']['asu_rfi_undergrad_confirm_node'],
    'asu_rfi_grad_confirm_node' => $form_state['values']['asu_rfi_grad_confirm_node'],
  );
  foreach ($confirm as $field => $nid) {
    if (!empty($nid)) {
      if (!preg_match('/^\d+$/', $nid)) {
        form_set_error($field, 'Node IDs must be integers.');
      }
      if (!drupal_lookup_path('alias', 'node/' . $nid)) {
        form_set_error($field, t('Node ID @nid does not exist.', array('@nid' => $nid)));
      }
    }
  }
  $email = $form_state['values']['asu_rfi_from_email_field'];
  if (!preg_match("/^([a-zA-Z0-9])+([a-zA-Z0-9._-])*@([a-zA-Z0-9_-])+([a-zA-Z0-9._-]+)*(\.[a-zA-Z]{2,6})+$/", $email)) {
    form_set_error('email', t('You entered an invalid email.'));
  }
}
