<?php

/**
 * @file
 * Provide administration configuration pages to import users.
 */

function user_import_confirm_delete($form, &$form_state, $import_id) {

  $form['import_id'] = array(
    '#type' => 'value',
    '#value' => $import_id,
  );

  return confirm_form($form,
    t('Are you sure you want to delete the user import process?'),
    'admin/people/user_import',
    t('Deleting a user import process will also delete the file from which user data was being read. This action cannot be undone.'),
    t('Delete'), t('Cancel'));
}

function user_import_confirm_delete_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    user_import_delete($form_state['values']['import_id']);
  }
}

function user_import_list($action = NULL, $import_id = NULL) {

  // clear incomplete imports
  _user_import_incomplete_deletion();

  if (!empty($import_id) && is_numeric($import_id)) {

    $pager_id = 1;
    $limit    = 10;
    $rows     = array();
    $import   = _user_import_settings_select($import_id);

    $total = db_query('SELECT count(data) FROM {user_import_errors} WHERE import_id = :import_id', array(':import_id' => $import_id))->fetchField();

    // Select table
    $query = db_select('user_import_errors', 'imp_usr_errors');

    // Select fields
    $query->fields('imp_usr_errors', array('import_id', 'data', 'errors'));

    // Set conditions.
    $query->condition('import_id', $import['import_id']);

    // For pagination
    $query = $query->extend('TableSort')->extend('PagerDefault')->limit($limit);

    // Execute query
    $result = $query->execute();

    foreach ($result as $line) {
      $rows[] = array('import_id' => $line->import_id, 'data' => unserialize($line->data), 'errors' => unserialize($line->errors));
    }

    $output = theme('user_import_errors_display', array('import' => $import, 'file_lines' => $rows, 'total' => $total));

  }
  else {

    $output = theme('user_import_list');
  }

  return $output;
}

function user_import_preferences($import_id = NULL, $template_id = NULL) {

  if (empty($import_id)) {
    $private_path = variable_get('file_private_path', FALSE);

    // Private path hasn't been set, show a message instead of the form.
    if (!$private_path) {
      drupal_set_message(t('!path needs to be set before users can be imported.', array('!path' => l('Private file system path', 'admin/config/media/file-system', array('query' => array('destination' => 'admin/people/user_import/add'))))), 'warning');
      return ' ';
    }


    $output = drupal_get_form('user_import_add_form');
  }
  else {
    $output = drupal_get_form('user_import_edit', $import_id, $template_id);
  }

  return $output;
}



function user_import_confirm_continue($form, &$form_state, $import_id) {

  $form['import_id'] = array(
    '#type' => 'value',
    '#value' => $import_id,
  );

  return confirm_form($form,
    t('Are you sure you want to continue to import users?'),
    'admin/people/user_import',
    t('Restart user import from where it last finished.'),
    t('Continue'), t('Cancel'));
}

function user_import_confirm_continue_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    user_import_continue($form_state['values']['import_id']);
  }
}

function user_import_continue($import_id = NULL) {

  if (!empty($import_id) && is_numeric($import_id)) {
    module_load_include('inc', 'user_import', 'user_import.import');
    $import = _user_import_settings_select($import_id);
    _user_import_process($import);
  }

  drupal_goto('admin/people/user_import');
}

function user_import_confirm_import($form, &$form_state, $import_id) {

  $form['import_id'] = array(
    '#type' => 'value',
    '#value' => $import_id,
  );

  return confirm_form($form,
    t('Are you sure you want to import users?'),
    'admin/people/user_import',
    t('Start importing users.'),
    t('Import'), t('Cancel'));
}

function user_import_confirm_import_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    user_import_import($form_state['values']['import_id']);
  }
}

function user_import_import($import_id = NULL) {

  if (!empty($import_id) && is_numeric($import_id)) {

    $import = _user_import_settings_select($import_id);
    _user_import_initialise_import($import);
  }

  drupal_goto('admin/people/user_import');
}

function user_import_delete($import_id = NULL, $return_path = 'admin/people/user_import') {

  if (empty($import_id) || !is_numeric($import_id)) drupal_goto($return_path);

  $import = _user_import_settings_select($import_id);
  _user_import_settings_deletion($import_id);
  //_user_import_file_deletion($import['filepath'], $import['filename'], $import['oldfilename'], $import['ftp']);
  file_unmanaged_delete($import['filepath']);
  drupal_goto($return_path);

  return;
}

/**
 * Configuration form define (settings affect all user imports)
 */
function user_import_configure_form() {

  $form['selectable_files'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Uploads Directory'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  );

  if (variable_get('user_import_selectable_files', 0) == 0) {
    $selectable_files_description = t('This option provides a directory where files can be uploaded, and then selected when setting up an import.');
  }
  else {
    $selectable_files_description = t('');
  }

  $form['selectable_files']['selectable_files'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable Uploads Directory'),
    '#description'   => $selectable_files_description,
    '#default_value' => variable_get('user_import_selectable_files', 0),
  );


  $form['auto_imports'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Automated Imports'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  );

  $form['auto_imports']['auto_imports_enabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable Automated Imports'),
    '#description'   => t('Each import template will have the option to create a directory which will be scanned for any files that have been uploaded to it,
                           and when a file is found it will automatically be used to create new user accounts. Directories are scanned durring !cron runs.', array('!cron' => l(t('cron'), 'admin/config/system/cron'))),
    '#default_value' => variable_get('user_import_auto_imports_enabled', 0),
  );

  $form['performance'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Performance'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  );

  $form['performance']['user_import_max'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Maximum Users/Process'),
    '#default_value' => variable_get('user_import_max', 250),
    '#size'          => 10,
    '#maxlength'     => 10,
    '#description'   => t('Maximum number of users to import each time the file is processed, useful for controling the rate at which emails are sent out.'),
  );

  $form['performance']['user_import_line_max'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Maximum length of line'),
    '#default_value' => variable_get('user_import_line_max', 1000),
    '#size'          => 10,
    '#maxlength'     => 10,
    '#description'   => t('The default is set at 1,000 characters, if a line in your csv is longer than this you should set a higher maximum here. Setting higher maximums will slow down imports.'),
  );

  if (module_exists('profile')) {
    $date_options                           = array(
      'MM/DD/YYYY' => 'MM/DD/YYYY',
      'DD/MM/YYYY' => 'DD/MM/YYYY',
      'YYYY/MM/DD' => 'YYYY/MM/DD',
      'YYYY/DD/MM' => 'YYYY/DD/MM',
    );
    $form['profile']                        = array(
      '#type'        => 'fieldset',
      '#title'       => t('Profile Settings'),
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
    );
    $form['profile']['profile_date_format'] = array(
      '#type'          => 'select',
      '#title'         => t('Date field format'),
      '#description'   => t('Select a format for importing dates into user profiles (Profile module).'),
      '#default_value' => variable_get('user_import_profile_date_format', 'MM/DD/YYYY'),
      '#options'       => $date_options,
    );
  }

  $saved_templates = _user_import_settings_select(NULL, TRUE);

  if (!empty($saved_templates)) {

    $form['settings_templates'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('Settings Templates'),
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
    );

    $templates_list = array('-- none --');

    foreach ($saved_templates AS $template) {
      $templates_list[$template['import_id']]   = $template['name'];
      $templates_delete[$template['import_id']] = $template['name'];
    }

    $form['settings_templates']['user_import_settings'] = array(
      '#type'          => 'select',
      '#title'         => t('Default Settings'),
      '#description'   => t('Select if you want to use a previously saved set of settings as default for all imports.'),
      '#default_value' => variable_get('user_import_settings', 0),
      '#options'       => $templates_list,
    );


    $form['settings_templates']['templates'] = array(
      '#type'    => 'checkboxes',
      '#title'   => t('Delete Templates'),
      '#options' => $templates_delete,
    );

  }

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function user_import_configure_form_validate($form, &$form_state) {

  if (is_numeric($form_state['values']['user_import_max'])) {
    if ($form_state['values']['user_import_max'] < 10) form_set_error('user_import_max', t("Value should be at least 10."));
  }
  else {
    form_set_error('user_import_max', t('Value must be a number.'));
  }

  if (is_numeric($form_state['values']['user_import_line_max'])) {
    if ($form_state['values']['user_import_line_max'] < 1000) form_set_error('user_import_line_max', t("Value must be higher than 1000."));
    if ($form_state['values']['user_import_line_max'] > 1000000) form_set_error('user_import_line_max', t("Value must be lower than 1,000,000."));
  }
  else {
    form_set_error('user_import_line_max', t('Value must be a number.'));
  }

  // Check private files path is set.
  if (!empty($form_state['values']['auto_imports_enabled'])) {
    $file_private_path = variable_get('file_private_path', FALSE);

    if (!$file_private_path) {
      form_set_error('auto_imports_enabled', t('The !private_file_path must be set to use this feature.', array('!private_file_path' => l(t('Private file system path'), 'admin/config/media/file-system'))));
    }
  }

  // Check private files path is set.
  if (!empty($form_state['values']['selectable_files'])) {
    $file_private_path = variable_get('file_private_path', FALSE);

    if (!$file_private_path) {
      form_set_error('selectable_files', t('The !private_file_path must be set to use the Uploads Directory feature.', array('!private_file_path' => l(t('Private file system path'), 'admin/config/media/file-system'))));
    }
  }

  return;
}

function user_import_configure_form_submit($form, &$form_state) {
  $deleted = '';
  settype($form_state['values']['user_import_max'], 'integer');
  settype($form_state['values']['user_import_line_max'], 'integer');
  variable_set('user_import_max', $form_state['values']['user_import_max']);
  variable_set('user_import_line_max', $form_state['values']['user_import_line_max']);

  $user_import_settings = isset($form_state['values']['user_import_settings']) ? $form_state['values']['user_import_settings'] : 0;
  variable_set('user_import_settings', $user_import_settings);

  $profile_date_format = isset($form_state['values']['profile_date_format']) ? $form_state['values']['profile_date_format'] : 0;
  variable_set('user_import_profile_date_format', $profile_date_format);

  variable_set('user_import_selectable_files', $form_state['values']['selectable_files']);
  variable_set('user_import_auto_imports_enabled', $form_state['values']['auto_imports_enabled']);

  // Create a directory for processing incoming files if auto imports are enabled.
  if (!empty($form_state['values']['auto_imports_enabled'])) {
    user_import_create_directory('processing', '');
  }

  // Create a directory for processing incoming files if auto imports are enabled.
  if (!empty($form_state['values']['selectable_files'])) {
    user_import_create_directory('selectable');
  }

  if (!empty($form_state['values']['templates'])) {

    foreach ($form_state['values']['templates'] as $import_id) {

      if (!empty($import_id)) {

        $template = _user_import_settings_select($import_id);
        if (!empty($deleted)) $deleted .= ', ';
        $deleted .= $template['name'];
        _user_import_settings_deletion($import_id);
      }
    }
  }

  if (!empty($deleted)) drupal_set_message(t('Settings templates deleted: @deleted', array('@deleted' => $deleted)));

  drupal_set_message(t('Configuration settings have been saved.'));
  $form_state['redirect'] = 'admin/people/user_import';
}

/**
 *  Start new import.
 *  Form to select file.
 **/
function user_import_add_form($import_id = NULL) {

  $form = array();
  $ftp_files = array();

  if (variable_get('user_import_selectable_files', 0) == 1) {
    $ftp_files = _user_import_ftp_files();
  }

  user_import_add_file_form($form, $ftp_files);

  user_import_delimiter_form($form);
  $settings = _user_import_settings_select(NULL, TRUE);

  if ($settings) {

    $saved_settings = array(t('-- none --'));
    foreach ($settings AS $settings_set) {
      $saved_settings[$settings_set['import_id']] = $settings_set['name'];
    }

    $form['import_template_select'] = array(
      '#type'          => 'select',
      '#title'         => t('Saved Settings'),
      '#description'   => t('Select if you want to use a previously saved set of settings.'),
      '#default_value' => variable_get('user_import_settings', 0),
      '#options'       => $saved_settings,
    );

  }

  $form['next'] = array(
    '#type'  => 'submit',
    '#value' => t('Next')
  );

  // Set form parameters so we can accept file uploads.
  $form['#attributes'] = array('enctype' => 'multipart/form-data');

  return $form;
}

function user_import_add_form_validate($form, &$form_state) {

  if (isset($form_state['values']['file_ftp']) && !empty($form_state['values']['file_ftp'])) {
    $file_ftp = $form_state['values']['file_ftp'];
  }
  else {
    $file_ftp = FALSE;
  }

  $file = _user_import_file(NULL, $file_ftp);

  // check file uploaded OK
  if (empty($file->filename)) {
    form_set_error('file_upload', t('A file must be uploaded or selected from FTP updates.'));
  }
  else {
    $form_state['values']['file_info'] = $file;
  }

  return;
}

function user_import_add_form_submit($form, &$form_state) {
  $redirect = 'admin/people/user_import/add/';

  if (isset($form_state['values']['file_ftp']) && !empty($form_state['values']['file_ftp'])) {
    $file_ftp = $form_state['values']['file_ftp'];
  }
  else {
    $file_ftp = FALSE;
  }

  $file = _user_import_file(NULL, $file_ftp);
  $file_name = user_import_move_file_for_processing($file->uri, $file->filename);

  $form_state['values']['ftp']         = $file_ftp;
  $form_state['values']['filename']    = $file_name;
  $form_state['values']['oldfilename'] = $file->filename;
  $form_state['values']['filepath']    = 'private://user_import/processing/' . $file_name;
  $form_state['values']['setting']     = 'file set';

  // create import setting
  $import = _user_import_settings_save($form_state['values']);
  $redirect .= $import['import_id'];

  if (!empty($form_state['values']['import_template_select'])) {
    $redirect .= '/' . check_plain($form_state['values']['import_template_select']);
  }

  $form_state['redirect'] = $redirect;
}

function user_import_delimiter_form(&$form, $value = ',') {
  $form['file_settings'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('File Settings'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#description' => t("File column delimiter"),
  );

  $form['file_settings']['delimiter'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Delimiter'),
    '#size'          => 4,
    '#default_value' => $value,
    '#required'      => TRUE,
    '#description'   => t("The column delimiter for the file. Use '/t' for Tab."),
  );
}

function user_import_edit($form, $form_state, $import_id, $template_id = NULL) {

  // load code for supported modules
  user_import_load_supported();

  $form = array();

  $import                = _user_import_settings_select($import_id);
  $import['template_id'] = $template_id;

  $form['ftp'] = array(
    '#type'  => 'value',
    '#value' => $import['options']['ftp'],
  );

  // add setting template values
  if ($import['setting'] == 'file set') {
    $import = _user_import_initialise_import($import);
  }

  $form['import_id'] = array(
    '#type'  => 'value',
    '#value' => $import_id,
  );

  $form['setting'] = array(
    '#type'  => 'value',
    '#value' => $import['setting'],
  );

  $form['return_path'] = array(
    '#type'          => 'value',
    '#default_value' => 'admin/people/user_import',
  );

  $form['og_id'] = array(
    '#type'          => 'value',
    '#default_value' => 0,
  );

  // don't use hook because these need to be added in this order;
  user_import_edit_file_fields($form, $import);
  user_import_form_field_match($form, $import);

  $collapsed            = (empty($import['name'])) ? FALSE : TRUE;
  $additional_fieldsets = module_invoke_all('user_import_form_fieldset', $import, $collapsed);
  if (is_array($additional_fieldsets)) $form = $form + $additional_fieldsets;

  $update_user = module_invoke_all('user_import_form_update_user');

  if (is_array($update_user)) {

    $form['update_user'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('Update Existing Users'),
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
      '#tree'        => TRUE,
    );

    foreach ($update_user as $module => $display) {

      $options = array(UPDATE_NONE => t('No Update'), UPDATE_REPLACE => t('Replace Data'), UPDATE_ADD => t('Add Data'));
      if (isset($display['exclude_add']) && $display['exclude_add'] == TRUE) unset($options[UPDATE_ADD]);
      if (isset($display['exclude_replace']) && $display['exclude_replace'] == TRUE) unset($options[UPDATE_REPLACE]);

      $form['update_user'][$module] = array(
        '#type'          => 'radios',
        '#title'         => $display['title'],
        '#options'       => $options,
        '#default_value' => empty($import['options']['update_user'][$module]) ? UPDATE_NONE : $import['options']['update_user'][$module],
        '#description'   => $display['description'],
      );
    }
  }

  // don't show test option if import has started
  if ($import['setting'] != 'import' && $import['setting'] != 'imported') {

    $form['test'] = array(
      '#type'   => 'submit',
      '#value'  => t('Test'),
      '#weight' => 100,
      '#submit' => array('user_import_test_submit', 'user_import_edit_submit'),
    );
  }

  $form['import'] = array(
    '#type'   => 'submit',
    '#value'  => t('Import'),
    '#weight' => 100,
    '#submit' => array('user_import_import_submit', 'user_import_edit_submit'),
  );

  $form['cancel'] = array(
    '#type'     => 'submit',
    '#value'    => t('Cancel'),
    '#weight'   => 100,
    '#validate' => array('user_import_edit_cancel_validate'),
  );

  return $form;
}

function user_import_edit_cancel_validate($form, &$form_state) {

  // if import was being added - delete file
  if ($form_state['values']['setting'] == 'file set') {
    $settings = _user_import_settings_select($form_state['values']['import_id']);
    _user_import_settings_deletion($form_state['values']['import_id']);
    // _user_import_file_deletion($settings['filepath'], $settings['filename'], $settings['oldfilename'], $settings['options']['ftp']);
    file_unmanaged_delete($settings['filepath']);
  }

  $form_state['redirect'] = 'admin/people/user_import';
}

function user_import_edit_validate($form, &$form_state) {
  $email  = FALSE;
  $fields = array();

  foreach ($form_state['values']['field_match'] as $row => $values) {

    // check each field is unique
    if ($values['field_match'] != '0' && $values['field_match'] != '-------------' && in_array($values['field_match'], $fields)) {
      form_set_error('field_match', t('Database fields can only be matched to one column of the csv file.'));
    }

    $fields[$values['field_match']] = $values['field_match'];

    // check email address has been selected
    if ($values['field_match'] == 'user-email') $email = TRUE;
  }

  if (!$email) form_set_error('email', t('One column of the csv file must be set as the email address.'));

  if ($form_state['values']['name']) {
    $form_state['values']['name'] = rtrim($form_state['values']['name']);

    if (drupal_strlen($form_state['values']['name']) < 1 || drupal_strlen($form_state['values']['name']) > 25) {
      form_set_error('name', t('Name of saved settings must be 25 characters or less.'));
    }
  }

  // Check auto uploads directory is not already in use by another template.
  if (!empty($form_state['values']['auto_import_directory'])) {
    $auto_import_directory = 'private://user_import/uploads/' . $form_state['values']['auto_import_directory'];

    if (file_prepare_directory($auto_import_directory, FILE_MODIFY_PERMISSIONS) || $form_state['values']['auto_import_directory'] == 'selectable') {
      form_set_error('auto_import_directory', t("Directory '%directory' already exists and can not be used.", array('%directory' => $form_state['values']['auto_import_directory'])));
    }
  }

  return;
}

/**
 *  Save a new template.
 */
function user_import_template_new_submit($form, &$form_state) {

  // save settings for import
  _user_import_settings_save($form_state['values']);

  // save settings for template
  $import_id                       = $form_state['values']['import_id'];
  $form_state['values']['setting'] = 'template';
  unset($form_state['values']['import_id']);

  if (isset($form_state['values']['auto_import_directory']) && !empty($form_state['values']['auto_import_directory'])) {
    user_import_create_directory($form_state['values']['auto_import_directory']);
  }


  _user_import_initialise_import($form_state['values']);
  drupal_set_message(t("'%name' was saved as a settings template.", array('%name' => $form_state['values']['name'])));

  // reload settings page
  $form_state['redirect'] = 'admin/people/user_import/add/' . $import_id;

  return;
}

/**
 *  Update an existing template.
 */
function user_import_template_update_submit($form, &$form_state) {

  // save settings for import
  $import_id = $form_state['values']['import_id'];
  _user_import_settings_save($form_state['values']);

  // get template details
  $template_id = db_query_range("SELECT import_id from {user_import} where setting = 'template' AND name = :name", 0, 1, array(':name' => $form['#current_template']))->fetchField();

  // save settings for template
  $form_state['values']['setting']   = 'template';
  $form_state['values']['import_id'] = $template_id;
  $form_state['values']['name']      = $form['#current_template'];
  _user_import_initialise_import($form_state['values']);
  drupal_set_message(t("'%name' settings template was updated.", array('%name' => $form['#current_template'])));

  // reload settings page
  $form_state['redirect'] = 'admin/people/user_import/add/' . $import_id;

  return;
}

/**
 *
 */
function user_import_test_submit($form, &$form_state) {
  $form_state['values']['setting'] = 'test';
  drupal_set_message(t('Tested'));
}

/**
 *
 */
function user_import_import_submit($form, &$form_state) {
  $form_state['values']['setting'] = 'import';
  drupal_set_message(t('Imported'));
}

function user_import_move_file_for_processing($source, $file_name) {
  // Make sure processing directory exists.
  user_import_create_directory(NULL, 'processing');

  $destination = 'private://user_import/processing/' . $file_name;
  $uri = file_unmanaged_move($source, $destination, FILE_EXISTS_RENAME);
  $file_name = substr($uri, 33);
  return $file_name;
}

/**
 *
 */
function user_import_edit_submit($form, &$form_state) {
  // Deal with import being canceled.
  if ($form_state['clicked_button']['#value'] == t('Cancel')) {
    $form_state['redirect'] = 'admin/people/user_import';

    return;
  }

  // Load import functions.
  module_load_include('inc', 'user_import', 'user_import.import');

  if ($form_state['values']['setting'] == 'file set') {
//    $file           = new stdClass();
//    $file->uri      = $form_state['values']['filepath'];
//    $file->filename = $form_state['values']['filename'];
    //$filepath       = file_move($file, file_directory_path() . '/' . $form_state['values']['filename']);
    $filepath       = user_import_move_file_for_processing($form_state['values']['filepath']);
  }

  if (!empty($form_state['values']['og_id'])) $form_state['values']['groups'][$form_state['values']['og_id']] = $form_state['values']['og_id'];
  $form_state['values']['ftp']                = $form_state['values']['ftp'];
  $form_state['values']                       = _user_import_settings_save($form_state['values']);
  $form_state['values']['save']['update']     = NULL;
  $form_state['values']['import_template_id'] = NULL;
  $form_state['values']['save']['name']       = NULL;
  $form_state['redirect']                     = $form_state['values']['return_path'];
  _user_import_process($form_state['values']);
}

function user_import_add_file_form(&$form, $ftp_files = NULL) {

  $form['browser'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Browser Upload'),
    '#collapsible' => TRUE,
    '#description' => t("Upload a CSV file."),
  );

  if (function_exists('file_upload_max_size')) {
    $file_size = t('Maximum file size: @size.', array('@size' => format_size(file_upload_max_size())));
  }

  $form['browser']['file_upload'] = array(
    '#type'        => 'file',
    '#title'       => t('CSV File'),
    '#size'        => 40,
    '#description' => check_plain(t('Select the CSV file to be imported.') . ' ' . $file_size),
  );

  if (!empty($ftp_files)) {

    $form['ftp'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('FTP Upload'),
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
      '#description' => t("Any files uploaded to the 'user_import' directory using FTP can be selected for import here. Useful if the import file is too large for upload via the browser."),
    );

    $form['ftp']['file_ftp'] = array(
      '#type'          => 'radios',
      '#title'         => t('Files'),
      '#default_value' => '0',
      '#options'       => $ftp_files,
    );

    // reload the page to show any files that have been added by FTP
    $form['ftp']['scan'] = array(
      '#type'     => 'submit',
      '#value'    => t('Check for new files'),
      '#validate' => array(),
      '#submit'   => array(),
    );

  }

  return;
}

function user_import_edit_file_fields(&$form, $import) {

  $form['filename'] = array(
    '#type'  => 'value',
    '#value' => $import['filename'],
  );

  $form['oldfilename'] = array(
    '#type'  => 'value',
    '#value' => $import['oldfilename'],
  );

  $form['filepath'] = array(
    '#type'  => 'value',
    '#value' => $import['filepath'],
  );

  return;
}

// - - - - - - - -  FILE HANDLING - - - - - - - -

/**
 * open file
 */
function _user_import_file_open($filepath, $filename) {

  ini_set('auto_detect_line_endings', TRUE);
  $handle = @fopen($filepath, "r");

  if (!$handle) {
    form_set_error('file', t("Could not find the csv file '%filename'", array('%filename' => $filename)), 'error');

    return t("Please add your file again.");
  }

  return $handle;
}

/*
 * File being used
 * $import_id - use file info stored in database
 * $ftp_file - chosen from FTP uploaded files
 * $uploaded_file - uploaded through browser
 */
function _user_import_file($import_id = NULL, $ftp_file_selected = NULL) {

  static $file;
  if (!empty($file)) return $file;

  // File was uploaded through browser.
  if (empty($ftp_file_selected) && empty($import_id)) {
    // Delete record from database management so we don't have duplicates problems.
    db_delete('file_managed')->condition('uri', 'temporary://' . $_FILES['files']['name']['file_upload'])->execute();

    $file = file_save_upload('file_upload', array('file_validate_extensions' => array('csv txt')), FALSE, FILE_EXISTS_RENAME);
    if (!empty($file)) return $file;
  }

  // File was uploaded by FTP
  if (!empty($ftp_file_selected)) {
    $ftp_files      = file_scan_directory('private://user_import/uploads/selectable', '/.*$/', array('key' => 'filename'));
    $file           = $ftp_files[$ftp_file_selected];
    $file->filepath = $file->uri;

    return $file;
  }

  // Use file info stored in database
  if (!empty($import_id)) {
    $import            = _user_import_settings_select($import_id);
    $file->uri         = $import['filepath'];
    $file->filepath    = $import['filepath'];
    $file->oldfilename = $import['oldfilename'];
    $file->filename    = $import['filename'];

    return $file;
  }

  return;
}

// get info on files  uploaded via FTP
function _user_import_ftp_files() {

  //$directory       = opendir(drupal_get_path('module', 'user_import'));

  $files       = file_scan_directory('private://user_import/uploads/selectable', '/.*$/');
  $filenames[] = t('none');

  foreach ($files as $file) {
    $filenames[$file->filename] = $file->filename;
  }

  return $filenames;
}

// delete incomplete import settings, where only the file has been uploaded
function  _user_import_incomplete_deletion() {

  $result = db_query("SELECT * FROM {user_import} WHERE setting = 'file set'");

  foreach ($result as $import) {
    $options = unserialize($import->options);
    //_user_import_file_deletion($import->filepath, $import->filename, $import->oldfilename, $options['ftp'], FALSE);
    file_unmanaged_delete($import->filepath);
    _user_import_settings_deletion($import->import_id);
  }

  return;
}

/**
 *  Create a directory in the private files directory.
 *
 **/
function user_import_create_directory($directory_name, $path_prefix = 'uploads/') {

  if (!file_stream_wrapper_valid_scheme('private')) {
    drupal_set_message(t('Directory %path could not be created as the Private files path has not been set.', array('%path' => $directory_name)), 'warning');
  }

  $path = 'private://user_import/' . $path_prefix . $directory_name;
  $directory_created = file_prepare_directory($path, FILE_CREATE_DIRECTORY);

  if ($directory_created) {
    file_create_htaccess($path);
  }
}

// - - - - - - - -  MISC - - - - - - - -

function user_import_form_field_match(&$form, $import) {

  $delimiter = isset($import['options']['delimiter']) && !empty($import['options']['delimiter']) ? $import['options']['delimiter'] : ',';
  $collapsed = (empty($import['name'])) ? FALSE : TRUE;
  $handle    = _user_import_file_open($form['filepath']['#value'], $form['filename']['#value']);
  $data_row  = _user_import_file_row($form['filename']['#value'], $handle, $delimiter);

  $fieldmatch_description_parts = array(
    '<strong>' . t('Drupal fields') . ':</strong> ' . t("Match columns in CSV file to drupal user fields, leave as '----' to ignore the column."),
    '<strong>' . t('Username') . ':</strong> ' . t("If username is selected for multiple fields, the username will be built in the order selected. Otherwise, the username will be randomly generated."),
    '<strong>' . t('Abbreviate') . ':</strong> ' . t("Use the first letter of a field in uppercase for the Username, e.g. 'john' -> 'J'."),
  );

  $fieldmatch_description = theme('item_list', array('items' => $fieldmatch_description_parts));

  $form['field_match'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Field Match'),
    '#description' => $fieldmatch_description,
    '#weight'      => -90,
    '#collapsible' => TRUE,
    '#collapsed'   => $collapsed,
    '#tree'        => TRUE,
  );

  // add default and email address options
  $user_fields[0]         = '-------------';
  $additional_user_fields = module_invoke_all('user_import_form_field_match');

  foreach ($additional_user_fields as $type => $type_options) {
    if (is_array($type_options)) {
      foreach ($type_options as $field_id => $label) {
        $user_fields["$type-$field_id"] = $label;
      }
    }
  }

  asort($user_fields);

  $row  = 0;
  $sort = array(t('--'), 1, 2, 3, 4);

  if (empty($data_row)) return;

  foreach ($data_row as $data_cell) {

    $form['field_match'][$row] = array(
      '#tree' => TRUE,
    );

    $form['field_match'][$row]['csv'] = array(
      '#markup' => check_plain(drupal_substr($data_cell, 0, 40)),
    );

    $form['field_match'][$row]['field_match'] = array(
      '#type'          => 'select',
      '#default_value' => isset($import['field_match'][$row]['field_match']) ? $import['field_match'][$row]['field_match'] : $user_fields[0],
      '#options'       => $user_fields,
    );

    $form['field_match'][$row]['username'] = array(
      '#type'          => 'select',
      '#default_value' => isset($import['field_match'][$row]['username']) ? $import['field_match'][$row]['username'] : $sort[0],
      '#options'       => $sort,
    );

    $form['field_match'][$row]['abbreviate'] = array(
      '#type'          => 'checkbox',
      '#default_value' => isset($import['field_match'][$row]['abbreviate']) ? $import['field_match'][$row]['abbreviate'] : NULL,
    );

    $row++;
  }

  return;
}

// get first row of file
function _user_import_file_row($filename, $handle, $delimiter = ',') {

  // Handle folks who may list 'tab' as 't' or 'tab'
  if (strtolower($delimiter) == 't' || strtolower($delimiter) == 'tab' || $delimiter == '\t' || $delimiter == '/t') {
    $delimiter = '\t';
  }

  $data_row = @fgetcsv($handle, 1000000, $delimiter);

  if (!$data_row) {
    form_set_error('file', t("Could not get data, the file '%filename' is either empty or has incompatible line endings.", array('%filename' => $filename)), 'error');
  }

  return $data_row;
}

// move from one stage to the next
// set up all necessary variables
function _user_import_initialise_import($import) {

  //_user_import_process won't work w/o this include
  module_load_include('inc', 'user_import', 'user_import.import');

  switch ($import['setting']) {
    case 'imported':
      drupal_set_message(t('File has already been imported'), 'error');
      break;

    // add setting template values to new import settings
    case 'file set':
      if (empty($import['template_id'])) return $import;
      $template                = _user_import_settings_select($import['template_id']);
      $template['import_id']   = $import['import_id'];
      $template['filename']    = $import['filename'];
      $template['oldfilename'] = $import['oldfilename'];
      $template['filepath']    = $import['filepath'];
      $template['started']     = 0;
      $template['setting']     = 'file set';

      return $template;

    case 'test':
    case 'tested':
      $import['setting']   = 'import';
      $import['started']   = 0;
      $import['pointer']   = 0;
      $import['processed'] = 0;
      $import['valid']     = 0;
      _user_import_errors_display_delete($import['import_id']);
      _user_import_settings_save($import);
      _user_import_process($import);
      break;

    case 'template':
      unset($import['filename']);
      unset($import['oldfilename']);
      unset($import['filepath']);
      $import['started']   = 0;
      $import['pointer']   = 0;
      $import['processed'] = 0;
      $import['valid']     = 0;
      _user_import_settings_save($import);
      break;

    default:
      _user_import_process($import);
      drupal_set_message(t('Imported'));
      break;
  }

  return;
}


/**
 * Delete errors from database for a specified import.
 * @param $import_id
 */
function _user_import_errors_display_delete($import_id) {
  db_query('DELETE FROM {user_import_errors} WHERE import_id = :import_id', array(':import_id' => $import_id));

  return;
}

function _user_import_profile($key = 'fid', $return_value = NULL) {

  if (!module_exists('profile')) return;

  static $fields_static;
  $fields = array();

  // avoid making more than one database call for profile info
  if (empty($fields_static)) {

    $results = db_query("SELECT * FROM {profile_field}");

    foreach ($results as $row) {
      // don't include private fields
      if (user_access('administer users') || $row->visibility != PROFILE_PRIVATE) {
        $fields_static[] = $row;
      }
    }
  }

  if (empty($fields_static)) return array();

  // return all profile fields info, or just specific type
  if (empty($return_value)) {

    foreach ($fields_static as $field) {
      $fields[$field->{$key}] = $field;
    }
  }
  else {
    foreach ($fields_static as $field) {
      $fields[$field->{$key}] = $field->{$return_value};
    }
  }

  asort($fields);

  return $fields;
}
