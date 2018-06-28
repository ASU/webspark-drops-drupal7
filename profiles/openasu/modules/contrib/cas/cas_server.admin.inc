<?php

/**
 * @file
 * CAS Server module settings UI.
 */

/**
 * Provides settings pages.
 */
function cas_server_admin_settings() {
  $form = array();

  $form['whitelist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Service Whitelist Settings'),
  );

  $example_list_1 = array('http://example.com', 'http://example.com/*', 'https://example.com', 'https://example.com/*');
  $example_list_2 = array('https://example.com/some_directory/*');

  $form['whitelist']['cas_server_service_whitelist'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Whitelist'),
    '#description'   => t("Define which services CAS Server will accept. Leave blank to accept all services.<br/>
                           <strong>It is strongly recommended that you use this feature to prevent inadvertent information disclosure
                           about your users.</strong>
                           <br/><br/>
                           Enter the URL of each service you wish to accept, one per line. The '*' character is a wildcard.<br/>
                           As an example, if you wished to accept any and all validation requests from example.com, you would need the following lines:
                           !example_list_1
                           If you only wanted to accept secure connections from some_directory at example.com, you would just need this line:
                           !example_list_2", array('!example_list_1' => theme('item_list', array('items' => $example_list_1)),
                           '!example_list_2' => theme('item_list', array('items' => $example_list_2)),
                         )),
    '#default_value' => variable_get('cas_server_service_whitelist', ''),
  );

  $form['whitelist']['cas_server_whitelist_failure'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Whitelist failure message'),
    '#description'   => t('Message to display when an unauthorized service attempts to authenticate via this CAS server.'),
    '#default_value' => variable_get('cas_server_whitelist_failure', t('You do not have permission to login to CAS from this service.')),
  );

  $form['single_logout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Single Logout Settings'),
    '#description' => t('When a user logs out, this module will send a logout request (via HTTP POST request) to each service that the user authenticated with. These settings are related to that functionality.'),
  );

  $form['single_logout']['cas_server_slo_group_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Request timeout (all requests)'),
    '#description' => t('If this amount of time (in seconds) has elapsed when sending all logout requests, abort any remaining requests.'),
    '#default_value' => variable_get('cas_server_slo_group_timeout', 15),
  );
  $form['single_logout']['cas_server_slo_individual_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Request timeout (individual requests)'),
    '#description' => t('The number of seconds to allow an individual logout request to take before aborting it.'),
    '#default_value' => variable_get('cas_server_slo_group_timeout', 5),
  );

  return system_settings_form($form);
}
