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
  // Overrides of google_appliance module-set form values
  $form['query_param']["#collapsed"] = TRUE;
  $form['query_param']["#prefix"] = "<h5>Advanced users ONLY!</h5>";
  $form['display_settings']["#collapsed"] = TRUE;

  // Use Local Search results instead of GSA results
  $form['connection_info']['google_appliance_local_search'] = array(
    '#type' => 'select',
    '#title' => t('Local Search'),
    '#description' => t('Use the default Drupal search instead of the GSA search. 
        (Select "No" if you will be using your own custom GSA collection below.)'),
    '#default_value' => $settings['local_search'],
    '#options' => array(
      'No' => t('No'),
      'Yes' => t('Yes'),
    ),
    '#required' => TRUE,
    '#weight' => -255,
  );
  // Overrides google_appliance instantiation of this form field.
  $form['connection_info']['google_appliance_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('GSA Collection'),
    '#description' => t('The collection on the GSA that will be used when searches are done. 
        (The default option is "default_collection". Email webconsulting@asu.edu if you want a 
        custom GSA collection of search results set up for your site.'),
    '#default_value' => $settings['collection'],
    '#required' => TRUE,
    '#weight' => -254,
    '#suffix' => "<h5>IMPORTANT: ASU users should never need to alter the settings below. Advanced users only!</h5>"
  );
  // Add 2nd submit handler to google_appliance_admin_settings
  $form['#submit'][] = 'asu_gsa_admin_settings_submit';
}

/**
 * Extra submit handler
 */
function asu_gsa_admin_settings_submit($form, &$form_state) {
  // Save the setting...
  variable_set('google_appliance_local_search', trim($form_state['values']['google_appliance_local_search']));
  // ...and make the 'search_title' setting change take effect right away
  menu_rebuild();
}
