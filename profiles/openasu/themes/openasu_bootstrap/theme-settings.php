<?php

/**
 * @file
 * Theme setting callbacks for open_asu.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function openasu_bootstrap_form_system_theme_settings_alter(&$form, &$form_state) {
  // Build the config form
  $form['theme_configuration'] = array(
    '#title' => t('OpenASU Theme Settings'),
    '#type' => 'fieldset',
  );

  $form['theme_configuration']['asu_brand_header_selector'] = array(
    '#title' => t('Color Scheme'),
    '#type' => 'radios',
    '#options' => array(
      'default' => t('Gold'),
      'default_maroon' => t('Maroon'),
      'default_white' => t('White'),
      'custom' => t('Custom'),
    ),
    '#default_value' => variable_get('asu_brand_header_selector', ASU_BRAND_HEADER_TEMPLATE_DEFAULT),
  );
  
  $form['theme_configuration']['asu_brand_header_template'] = array(
    '#title' => t('Enter Custom Template Key'),
    '#type' => 'textfield',
    '#states' => array(
     'visible' => array(
       ':input[name="asu_brand_header_selector"]' => array('value' => 'custom'),
     ),
    ),
    '#default_value' => variable_get('asu_brand_header_template', variable_get('asu_brand_header_selector')),
  );

  $form['theme_configuration']['asu_brand_is_student'] = array(
    '#title' => t('Footer Type'),
    '#type' => 'select',
    '#options' => array(
      'default' => t('Default Footer'),
      'student' => t('Student Footer'),
    ),
    '#default_value' => variable_get('asu_brand_is_student', 'student'),
    '#access' => FALSE,
  );

  $form['theme_configuration']['asu_brand_student_color'] = array(
    '#title' => t('Menu Color'),
    '#type' => 'radios',
    /*'#states' => array(
     'visible' => array(
       ':input[name="asu_brand_is_student"]' => array('value' => 'student'),
     ),
    ),*/
    '#options' => array(
      'black' => t('Black'),
      'gold' => t('Gold'),
      'grey' => t('Grey'),
    ),
    '#default_value' => variable_get('asu_brand_student_color', 'black'),
  );
  $form['theme_configuration']['hide_local_menu_navicon'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide local menu Navicon'),
    '#default_value' => theme_get_setting('hide_local_menu_navicon', 'openasu_bootstrap'),
    '#tree' => FALSE,
    '#description' => t('This will disable the navicon for the local menu on mobile and tablet devices. The ASU Header navicon will now activate the local menu.'),
  );
  $form['theme_configuration']['default_picture'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use a global header image?'),
    '#default_value' => theme_get_setting('default_picture', 'openasu_bootstrap'),
    '#tree' => FALSE,
    '#description' => t('Upload an image the be displayed across all of the pages of your site'),
  );
  $form['theme_configuration']['settings'] = array(
    '#type' => 'container',
    '#states' => array(
      // Hide the logo settings when using the default logo.
      'invisible' => array(
        'input[name="default_picture"]' => array('checked' => FALSE),
      ),
    ),
  );
  $form['theme_configuration']['settings']['picture_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Current header image'),
    '#attributes' => array('disabled' => TRUE),
    '#default_value' => theme_get_setting('picture_path', 'openasu_bootstrap'),
  );
  $form['theme_configuration']['settings']['picture_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload new header image'),
    '#maxlength' => 40,
    '#description' => t("If you don't have direct file access to the server, use this field to upload your logo.")
  );

  $form['#submit'][] = 'openasu_bootstrap_settings_submit';
  $form['#validate'][] = 'openasu_bootstrap_settings_validate';
}

function openasu_bootstrap_settings_submit($form, &$form_state) {
  // Set the variables, need to use this instead of theme_get_settings
  // because the scop of the vars is more global.
  if ($form_state['values']['asu_brand_header_selector'] != 'custom') {
    variable_set('asu_brand_header_template', $form_state['values']['asu_brand_header_selector']);
  }
  else {
    variable_set('asu_brand_header_template', $form_state['values']['asu_brand_header_template']);
  }
  variable_set('asu_brand_is_student', $form_state['values']['asu_brand_is_student']);
  variable_set('asu_brand_student_color', $form_state['values']['asu_brand_student_color']);
  variable_set('asu_brand_header_selector', $form_state['values']['asu_brand_header_selector']);

  if ($file = $form_state['values']['picture_upload']) {
    unset($form_state['values']['picture_upload']);
    $filename = file_unmanaged_copy($file->uri);
    $form_state['values']['default_picture'] = 1;
    $form_state['values']['picture_path'] = $filename;
  }

  // If the user entered a path relative to the system files directory for
  // a logo or favicon, store a public:// URI so the theme system can handle it.
  if (!empty($form_state['values']['picture_path'])) {
    $form_state['values']['picture_path'] = _system_theme_settings_validate_path($form_state['values']['picture_path']);
  }
  
  // ASU header needs a cache_clear
  if (module_exists('asu_brand')) {
    asu_brand_cache_clear();
  }
}

function openasu_bootstrap_settings_validate($form, &$form_state) {
  // Handle file uploads.
  $validators = array('file_validate_is_image' => array());

  // Check for a new uploaded logo.
  $file = file_save_upload('picture_upload', $validators);
  if (isset($file)) {
    // File upload was attempted.
    if ($file) {
      // Put the temporary file in form_values so we can save it on submit.
      $form_state['values']['picture_upload'] = $file;
    }
    else {
      // File upload failed.
      form_set_error('logo_picture', t('The logo could not be uploaded.'));
    }
  }
  if ($form_state['values']['picture_path']) {
    $path = _system_theme_settings_validate_path($form_state['values']['picture_path']);
    if (!$path) {
      form_set_error('picture_path', t('The custom logo path is invalid.'));
    }
  }
}
