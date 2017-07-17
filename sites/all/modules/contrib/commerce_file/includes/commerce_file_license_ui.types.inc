<?php

/**
 * @file
 * Page callbacks and form builder functions for administering orders.
 */


/**
 * Form callback: edit the global order settings.
 */
function commerce_file_license_settings_form($form, &$form_state) {
  $form['commerce_file_license_help_text'] = array(
    '#type' => 'textarea',
    '#title' => t('License creation help text'),
    '#description' => t('Supply an optional help message to be displayed above the license add form.'),
    '#default_value' => variable_get('commerce_file_license_help_text', ''),
  );

  return system_settings_form($form);
}
