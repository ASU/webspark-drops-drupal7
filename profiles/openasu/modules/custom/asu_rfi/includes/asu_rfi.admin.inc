<?php /** @noinspection PhpUnusedParameterInspection */
/** @noinspection PhpUnused */

/**
 * Form definition for ASU RFI form admin settings
 * @return array $form
 */
function asu_rfi_admin_settings() {
  $form_modes = array('test' => 'Test', 'prod' => 'Production', 'none' => 'None (No middleware)');
  $form_mode = variable_get('asu_rfi_form_mode', 'test');
  $middleware_target_envs = array('test' => 'QA/Test', 'prod' => 'Production');
  $middleware_env = variable_get('asu_rfi_middleware_env', 'prod');
  // Middleware QA access check (for non-ASU-Enterprise sites))
  $not_a_bool = (int) 0;
  $enterprise_access = variable_get('asu_rfi_enterprise_access_', $not_a_bool);
  $special_action_modes = array(
    'all' => 'RFI Report page actions + cron jobs',
    'form_only' => 'RFI Report page actions',
  );
  $expiration_options = array(
    0 => 'Zero days (immediate)',
    1 => 'One day',
    14 => '14 days',
    30 => '30 days',
    45 => '45 days',
  );
  $expiration_range = round((float) (ASU_RFI_SUBMISSION_EXP_PERIOD) / 86400 , 2) . ' days';

  ////////////////////////

  $form = array();

  // Middleware authorization warning if necessary
  $auth_key = variable_get('asu_rfi_form_auth_key');
  if (!empty($auth_key) && strlen($auth_key) === 32) { // All SHAs should be 32 characters long.
    $stage = array(
      'message' => 'A middleware authentication code has been configured for this site.'
      . ' (NOTE: This does not validate that the code works.)',
      'css' => 'messages status',
    );
  } else {
    $stage = array(
      'message' => 'WARNING: All undergrad (and many graduate) submissions'
        . ' will not be successfully posted to Salesforce via Middleware'
        . ' unless a valid authentication code has been configured.'
        . ' <a href="https://webforms.asu.edu/content/access-rfi-middleware-request">Request an'
        . ' authentication key</a>',
      'css' => 'messages warning',
    );
  }
  $message = '<div class="' . $stage['css'] . '">' . $stage['message'] . '</div>';
  $form['form_stage'] = array(
    '#type' => 'item',
    '#markup' => $message,
  );

  // RFI submissions turned off completely in the site?
  if ($form_mode === 'none') {
    $stage = array(
      'message' => 'The RFI form submissions will not be sent to any RFI middleware (or Salesforce environment). To re-enable,'
      . ' change the Test mode setting below.',
      'css' => 'messages warning',
    );
    $message = '<div class="' . $stage['css'] . '">' . $stage['message'] . '</div>';
    $form['form_stage'] = array(
      '#type' => 'item',
      '#markup' => $message,
    );
  }

  // CONFIRMATION SETTINGS
  ////////////////////////////

  $form['confirm_settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'Confirmation messaging',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => 'Management of RFI form responses to prospective (or current) students.',
  );

  // CONF PAGES
  ////////////////////////////
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
  ////////////////////////
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


  // GENERAL SETTINGS
  ///////////////////////

  $form['general_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('asu-rfi-admin-field asu_rfi_form_access asu-rfi-general-settings')),
  );
  $form['general_settings']['asu_rfi_form_mode'] = array(
    '#type' => 'select',
    '#title' => t('Test mode'),
    '#options' => $form_modes,
    '#default_value' => $form_mode,
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#description' => t("OPTIONS: <br>"
      . " * 'None' = No RFI form submissions are sent to middleware target environment (or Salesforce). All will be treated as 'FAILED' submissions. Forms are hidden from non-admin users.<br>"
      . " * 'Test' = Submitted to middleware target environment ONLY (not onto Salesforce), with a confirmation message returned and recorded in the RFI submission status field. Forms are hidden from non-admin users.<br>"
      . " * 'Production' = Submitted to middleware target environment and Salesforce"),
    '#required' => TRUE,
  );

  $form['general_settings']['expired_nodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expired submissions handling'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('asu-rfi-admin-field asu-rfi-general-settings asu-rfi-expiration')),
  );
  $form['general_settings']['expired_nodes']['notes'] = array(
    '#type' => 'item',
    '#markup' => '<p>If "Report page actions + cron jobs" are selected below (HIGHLY'
      . ' recommended), your expired RFI submissions (' . $expiration_range
      . ' past their initial submission date) will be automatically queued for resubmission (or deletion)'
      . ' every time <a href="/admin/config/system/cron">a cron job runs</a> at periodic'
      . ' intervals.</p>'
      . ' <p>If you want to manually manage the resubmission (or deletion) of RFI submissions,'
      . ' select "<a href="/admin/reports/asu-rfi-submissions-report">Report page</a>'
      . ' actions ONLY". (NOT recommended). (<strong>NOTE</strong>: If a cron job has'
      . ' already queued existing expired submissions, selecting this setting will not'
      . ' stop their resubmission (or deletion) even if it has not happened yet.'
      . ' It will only stop <em><strong>future</strong></em>'
      . ' submissions from also being placed in the resubmission (or deletion) queue.)</p>'
  );
  $form['general_settings']['expired_nodes']['asu_rfi_expired_submit'] = array(
    '#type' => 'select',
    '#title' => t('Submit ALL expired submissions using...'),
    '#options' => $special_action_modes,
    '#default_value' => variable_get('asu_rfi_expired_submit', 'all'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#required' => TRUE,
  );
  $form['general_settings']['expired_nodes']['asu_rfi_expired_delete'] = array(
    '#type' => 'select',
    '#title' => t('Delete all expired submissions using...'),
    '#options' => $special_action_modes,
    '#default_value' => variable_get('asu_rfi_expired_delete', 'all'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#required' => TRUE,
  );
  $form['general_settings']['expired_nodes']['asu_rfi_expired_period'] = array(
    '#type' => 'select',
    '#title' => t('Expiration period (days)'),
    '#options' => $expiration_options,
    '#default_value' => variable_get('asu_rfi_expired_period', 45),
    '#description' => t('RFI submissions will be automatically deleted this number of days after the initial'
      . ' RFI form submission. NOTES: 1) The zero or one day options are not recommended for production (debugging only).'
      . ' They could lead to submission loss. 2) In the future, this setting may be removed and be preset'
      . ' with a value that complies with any ASU and UTO security standards.'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#required' => TRUE,
  );
  // MAY be enabled in future (currently handled externally)
  $form['general_settings']['asu_rfi_form_auth_key'] = array(
    '#type' => 'hidden',
    '#title' => t('Authentication code'),
    '#default_value' => variable_get('asu_rfi_form_auth_key'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#description' => t('Don\'t have a code? @url.',
      array('@url' => l(
          'Request authentication key',
          'https://webforms.asu.edu/content/access-rfi-middleware-request'),
      )),
    '#required' => FALSE,
  );

  // ERROR REPORTING
  /////////////////////////

  $form['general_settings']['error_reporting'] = array(
    '#type' => 'fieldset',
    '#title' => 'Submission alerts',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('What to do if a submission fails, etc..'),
    '#attributes' => array('class' => array('asu-rfi-admin-error-reporting')),
  );
  $form['general_settings']['error_reporting']['asu_rfi_error_email'] = array(
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

  // DEVELOPER SETTINGS
  /////////////////////////

  $form['general_settings']['developer_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Developer settings (Advanced)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('asu-rfi-admin-field asu-rfi-developer-settings')),
  );

  // Which middleware environment? For developers only.
  $form['general_settings']['developer_settings']['asu_rfi_middleware_env'] = array(
    '#type' => 'select',
    '#title' => t('Middleware target environment'),
    '#options' => $middleware_target_envs,
    '#default_value' => $middleware_env,
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#required' => TRUE,
  );
  if ($enterprise_access === 0) {
    $form['general_settings']['developer_settings']['asu_rfi_middleware_env']['#default_value'] = 'prod';
    $form['general_settings']['developer_settings']['asu_rfi_middleware_env']['#disabled'] = TRUE;
    $extra_text = (defined('PANTHEON_ENVIRONMENT'))
      ? 'Pantheon-hosted sites like this one'
      : 'This site';
    $message = 'DISABLED - ' . $extra_text . ' (' . $_SERVER['HTTP_HOST'] . ') cannot reach the QA middleware servers.';
  } else {
    $message = t("Leave this set to the default (Production) if you don't understand this setting.<br>")
      . "OPTIONS:<br> * 'Production' = Submitted to PROD middleware (and then pushed into the real Salesforce.)<br>"
      . " * 'Test' = Submitted to QA middleware (and then pushed to Salesforce QA (not available in some web hosting environments.)";
  }
  $form['general_settings']['developer_settings']['asu_rfi_middleware_env']['#description'] = $message;

  $form['general_settings']['developer_settings']['asu_rfi_google_analytics_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Site identifier for Google Analytics'),
    '#default_value' => variable_get('asu_rfi_google_analytics_key'),
    '#attributes' => array('class' => array('asu-rfi-admin-field')),
    '#description' => t('Must be 6-10 alphanumeric (or dashes/underscores) characters.'
    . ' This will be used to differentiate your RFI submissions from other website submissions in Google Analytics. Example:'
    . ' If your site is collegename.asu.edu, use "CollegeNam", "Col-Name", etc. IMPORTANT: Once this has been set, it will'
    . ' not be alterable in this form.'),
    '#required' => TRUE,
    '#disabled' => FALSE,
  );
  $form['general_settings']['developer_settings']['asu_rfi_online_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Online programs feed URL'),
    '#description' => t('The URL for the asuonline.asu.edu JSON feed that'
      . ' lists all Online campus programs. This should have been set when this module'
      . ' was enabled, and will rarely be changed.'),
    '#default_value' => variable_get('asu_rfi_online_url'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );
  $form['general_settings']['developer_settings']['asu_rfi_hide_online_alerts'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide Online "not available" alerts'),
    '#description' => t('Suppress the "this program is not yet online" message that is displayed when'
      . ' a degree is available in the Degree Search feed but not in the Online feed.'),
    '#default_value' => variable_get('asu_rfi_hide_online_alerts'),
    '#return_value' => 1,
    '#required' => FALSE,
  );
  $form['general_settings']['developer_settings']['asu_rfi_use_jr_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable old ASU RFI Javascript for debugging'),
    '#description' => t('For UTO developer debugging only. Leave unchecked.'),
    '#default_value' => variable_get('asu_rfi_use_jr_js'),
    '#return_value' => 1,
    '#required' => FALSE,
  );

  // HIDDEN
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

  // EXTRA submission actions for confirmation pages
  $form['#validate'][] = '_asu_rfi_admin_settings_validate';
  $form['#submit'][] = '_asu_rfi_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Validation handler for ASU RFI admin configuration form
 * @param $form
 * @param $form_state
 */
function _asu_rfi_admin_settings_validate($form, &$form_state) {
  if (!valid_url($form_state['values']['asu_rfi_online_url'], TRUE)) {
    form_set_error('asu_rfi_online_url',
      'A valid JSON feed URL for pulling in Online campus degrees is required.');
  }
  if (isset($form_state['values']['asu_rfi_from_email_field'])
    && (!empty($form_state['values']['asu_rfi_from_email_field']))) {
    asu_libs_validate_email($form_state['values']['asu_rfi_from_email_field'],
      'asu_rfi_from_email_field');
  }
  if (isset($form_state['values']['asu_rfi_google_analytics_key'])) {
    $form_state['values']['asu_rfi_google_analytics_key'];
    if (!preg_match("/^[a-zA-Z0-9\-_]{6,10}$/", $form_state['values']['asu_rfi_google_analytics_key'])) {
      form_set_error('asu_rfi_google_analytics_key',
        'Your Google Analytics key must be 6-10 alphanumeric (or dashes/underscores) are allowed.');
    }
  } else {
    form_set_error('asu_rfi_google_analytics_key',
      'Your Google Analytics key must be 6-10 alphanumeric (or dashes/underscores).');
  }
}

/**
 * Defines keys and saves their values in the variable DB table (extra form submit callback)
 * @param $form
 * @param $form_state
 */
function _asu_rfi_admin_settings_submit($form, $form_state) {
  $keys = array(
    'asu_rfi_online_url' => 0,
    'asu_rfi_middleware_env' => 0,
    'asu_rfi_hide_online_alerts' => 0,
    'asu_rfi_grad_confirm' => 1,
    'asu_rfi_undergrad_confirm' => 1,
    'asu_rfi_expired_delete' => 0,
    'asu_rfi_expired_submit' => 0,
    'asu_rfi_expired_period' => 0,
    'asu_rfi_use_jr_js' => 0,
  );
  foreach ($keys as $element => $is_entity) {
    $key = ($is_entity === 1) ? $element . '_nid' : $element;
    $value = ($is_entity === 1)
      ? ((isset($form_state['values'][$element]['entity_id']))
        ? $form_state['values'][$element]['entity_id']
        : '')
      : $form_state['values'][$element];
    variable_set($key, $value);
  }
}
