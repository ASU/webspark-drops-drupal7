<?php
/**
 * @file
 *    admin callbacks for the Google Appliance module
 */

/**
 * Implements hook_admin_settings().
 *    displays the Search ASU GSA module settings page.
 *
 */
function asu_gsa_admin_settings($form) {

  // grab current settings
  $settings = _asu_gsa_get_settings();

  $form['connection_info']['local_search'] = array(
    '#type' => 'select',
    '#title' => t('Local Search'),
    '#description' => t('Do you want to use the default Drupal search instead of the GSA search? (Select No if you will set your own custom collection below)'),
    '#default_value' => $settings['local_search'],
     '#options' => array(
      'No' => t('No'),
      'Yes' => t('Yes'),
       ),
    '#required' => TRUE,
  );

  $form['connection_info']['collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection'),
    '#description' => t('The name of a valid collection on the GSA (default value: default_collection). Email webconsulting@asu.edu if you need a custom collection setup'),
    '#default_value' => $settings['collection'],
    '#required' => TRUE,
  );

 $form['#submit'][] = 'asu_gsa_admin_settings_submit';

  return system_settings_form($form);
}


function asu_gsa_admin_settings_submit($form, &$form_state) {

  
  $field_keys =  array(
    'collection',
    'local_search',
  );
  $original = $form_state['values']['collection'];
  variable_set("original_collection",$original);
  // save settings
  foreach ($field_keys as $field) {
    variable_set('google_appliance_' . $field, trim($form_state['values'][$field]));
  }

  // refresh settings getter
  $settings = _asu_gsa_get_settings(TRUE);

  // make the 'search_title' setting change take effect right away
  menu_rebuild();

}

