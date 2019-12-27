<?php /** @noinspection PhpUnusedParameterInspection */
/** @noinspection PhpUnused */

/**
 * Form definition for ASU RFI form admin settings
 * @return array $form
 */
function asu_rfi_admin_settings() {
  $form_modes = array('test' => 'Test', 'prod' => 'Production');
  $special_action_modes = array(
    'all' => 'Report page actions + Cron runs',
    'form_only' => 'Report page actions ONLY',
  );

  ////////////////////////

  $form = array();

  $form['form_stage'] = array(
    '#type' => 'item',
    '#markup' => t('<div class="messages warning">Important: The RFI submissions will not be'
    . ' posted to Salesforce via Middleware unless a valid authentication code has been added.'
    . ' <a href="https://webforms.asu.edu/content/access-rfi-middleware-request">Request '
    . ' authentication key</a></div>'),
  );

  // GENERAL SETTINGS
  ///////////////////////

  $form['asu_rfi_form_access'] = array(
    '#type' => 'fieldset',
    '#title' => 'General settings',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('asu-rfi-admin-field asu_rfi_form_access')),
  );
  $form['asu_rfi_form_access']['asu_rfi_form_mode'] = array(
    '#type' => 'select',
    '#title' => t('Test/Live Mode'),
    '#options' => $form_modes,
    '#default_value' => variable_get('asu_rfi_form_mode'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#description' => t("Specify if the forms are in Test mode or Live mode. '
     . 'Note: This is a sitewide configuration and will affect all forms. Only '
     . 'site admins can view the forms if they are in Test mode."),
    '#required' => TRUE,
  );
  $form['asu_rfi_form_access']['asu_rfi_expired_submit'] = array(
    '#type' => 'select',
    '#title' => t('Submit all expired submissions using...'),
    '#options' => $special_action_modes,
    '#default_value' => variable_get('asu_rfi_expired_submit', 'all'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#description' => t("Submit ALL expired RFI submissions to Salesforce "
      . " middleware when the above actions are executed - even though they are more than "
      . round((float) (ASU_RFI_SUBMISSION_EXP_PERIOD) / 86400 , 2)
      . ' days old and may not be relevant leads anymore.'
      . ' <a href="/admin/reports/asu-rfi-submissions-report">RFI submissions report</a>'),
    '#required' => TRUE,
  );
  $form['asu_rfi_form_access']['asu_rfi_expired_delete'] = array(
    '#type' => 'select',
    '#title' => t('Delete all expired submissions using...'),
    '#options' => $special_action_modes,
    '#default_value' => variable_get('asu_rfi_expired_delete', 'all'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#description' => t("Delete any expired RFI submissions when the above actions"
      . " are executed, even if they are more than "
      . round((float) (ASU_RFI_SUBMISSION_EXP_PERIOD) / 86400 , 2) . " days old."
      . ' <a href="/admin/reports/asu-rfi-submissions-report">RFI submissions report</a>'),
    '#required' => TRUE,
  );
  // Will be enabled in future
  $form['asu_rfi_form_access']['asu_rfi_form_auth_key'] = array(
    '#type' => 'hidden',
    '#title' => t('Authentication code'),
    '#default_value' => variable_get('asu_rfi_form_auth_key'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#description' => t('Don\'t have a code? <a href="https://webforms.asu.edu/content/access-rfi-middleware-request">Request'
    . ' authentication key</a>.'),
    '#required' => FALSE,
  );

  // ERROR REPORTING
  /////////////////////////

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
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#description' => t('Email addresses to be notified if site cannot post'
     . ' RFI submissions to Salesforce for more than 2 days. Use a comma-delimited'
     . ' list of emails if more than one recipient. (NOTE: Keep the number of email'
     . ' addresses here to a minimum to avoid being blocked as spam by some email (SMTP) servers.)'),
    '#size' => 60,
    '#maxlength' => 150,
  );
  $form['asu_rfi_form_access']['asu_rfi_google_analytics_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Site identifier for Google Analytics'),
    '#default_value' => variable_get('asu_rfi_google_analytics_key'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
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

  // CONFIRMATION SETTINGS
  ////////////////////////////

  $form['confirm_settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'Confirmation messaging',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => 'Management of RFI form responses to prospective (or current) students.',
  );

  //// CONF PAGES
  $form['confirm_settings']['asu_rfi_confirm_content'] = array(
    '#type' => 'fieldset',
    '#title' => 'Confirmation pages',
    '#description' => 'If custom confirmation pages to display (upon successful'
      . ' submission) have been created in this site, please'
      . ' enter its title in the appropriate field(s) below. If left empty, a'
      . ' default confirmation template will instead be output.',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('asu-rfi-confirm-email-fields')),
  );
  $form['confirm_settings']['asu_rfi_confirm_content']['asu_rfi_undergrad_confirm'] = array(
    '#type' => 'entityreference',
    '#title' => t('Undergraduate confirmation page'),
    '#era_entity_type' => 'node',
    '#era_bundles' => array('panopoly_page'),
    '#era_query_settings' => array(
      'limit' => 25, // Default is 50.
    ),
    '#default_value' => variable_get('asu_rfi_undergrad_confirm', ''),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
  );
  $form['confirm_settings']['asu_rfi_confirm_content']['asu_rfi_grad_confirm'] = array(
    '#type' => 'entityreference',
    '#title' => t('Graduate confirmation page'),
    '#era_entity_type' => 'node',
    '#era_bundles' => array('panopoly_page'),
    '#era_query_settings' => array(
      'limit' => 25, // Default is 50.
    ),
    '#default_value' => variable_get('asu_rfi_grad_confirm', ''),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
  );

  //// CONF EMAIL
  $form['confirm_settings']['asu_rfi_confirm_email'] = array(
    '#type' => 'fieldset',
    '#title' => 'Confirmation Email',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('If desired, enter the following information that'
      . ' will be used/displayed when a receipt/confirmation email is sent to the submitter.'),
    '#attributes' => array('class' => array('asu-rfi-confirm-email-fields')),
  );
  $form['confirm_settings']['asu_rfi_confirm_email']['asu_rfi_from_email_field'] = array(
    '#type' => 'textfield',
    '#title' => t('"From" email address'),
    '#default_value' => variable_get('asu_rfi_from_email_field'),
    '#size' => 50,
    '#maxlength' => 100,
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
  );
  $form['confirm_settings']['asu_rfi_confirm_email']['asu_rfi_from_name_field'] = array(
    '#type' => 'textfield',
    '#title' => t('"From" name'),
    '#default_value' => variable_get('asu_rfi_from_name_field'),
    '#size' => 50,
    '#maxlength' => 100,
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
  );
  $form['confirm_settings']['asu_rfi_confirm_email']['asu_rfi_email_subject_field'] = array(
    '#type' => 'textfield',
    '#title' => t('"Subject" field'),
    '#default_value' => variable_get('asu_rfi_email_subject_field'),
    '#size' => 100,
    '#maxlength' => 100,
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#siffix' => '</div>',
  );

  // EXTRA submission actions for confirmation pages
  $form['#submit'][] = '_asu_rfi_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Defines keys and saves their values in the variable DB table (extra form submit callback)
 * @param $form
 * @param $form_state
 */
function _asu_rfi_admin_settings_submit($form, $form_state) {
  $keys = array(
    'asu_rfi_grad_confirm' => 1,
    'asu_rfi_undergrad_confirm' => 1,
    'asu_rfi_expired_delete' => 0,
    'asu_rfi_expired_submit' => 0,
  );
  foreach ($keys as $element => $is_entity) {
    $value = ($is_entity === 1)
      ? ((isset($form_state['values'][$element]['entity_id']))
        ? $form_state['values'][$element]['entity_id']
        : '')
      : $form_state['values'][$element];
    $key = ($is_entity === 1) ? $element . '_nid' : $element;
    variable_set($key, $value );
  }
}
