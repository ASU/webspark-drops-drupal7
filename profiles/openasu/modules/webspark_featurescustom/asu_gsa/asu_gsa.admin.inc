<?php
/**
 * @file - Admin callbacks for the Google Appliance module
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function asu_gsa_form_google_appliance_admin_settings_alter(&$form, &$form_state, $form_id) {

  // grab current settings
  $settings = _asu_gsa_get_settings();

  // Update description for GA Collection with ASU information (overrides google_appliance_form instantiation)
  // of this field
  $form['connection_info']['google_appliance_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection'),
    '#description' => t('The name of a valid collection on the GSA (default value: default_collection). Email webconsulting@asu.edu if you need a custom collection setup'),    '#default_value' => $settings['collection'],
    '#default_value' => $settings['collection'],
    '#required' => TRUE,
  );
  // Use Local Search results instead of GSA results
  $form['connection_info']['google_appliance_local_search'] = array(
    '#type' => 'select',
    '#title' => t('Local Search'),
    '#description' => t('Do you want to use the default Drupal search instead of the GSA search? (Select No if you will set your own custom collection below)'),
    '#default_value' => $settings['local_search'],
    '#options' => array(
      'No' => t('No'),
      'Yes' => t('Yes'),
    ),
    '#required' => TRUE,
    '#weight' => -255,
  );
  // Add 2nd submit handler to google_appliance_admin_settings
  $form['#submit'][] = 'asu_gsa_admin_settings_submit';
}

/**
 * Extra submit handler
 */
function asu_gsa_admin_settings_submit($form, &$form_state) {
  // Save the setting
  variable_set('google_appliance_local_search', trim($form_state['values']['connection_info']['google_appliance_local_search']));
  // make the 'search_title' setting change take effect right away
  menu_rebuild();
}
