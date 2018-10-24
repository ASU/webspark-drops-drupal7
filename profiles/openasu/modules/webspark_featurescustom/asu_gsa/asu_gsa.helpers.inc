<?php
/**
 * @file
 *    helper functions for the Search Google Appliance module
 *
 * @see google_search_appliance.module
 */

/**
 * default module settings
 */
define('SGA_DEFAULT_LOCAL_SEARCH', 'Yes');

/**
 * Setting all our custom GSA search parameters
 */
function _asu_gsa_get_settings($refresh = FALSE) {
  static $settings;
  $field_keys = array(
    'collection',
    'local_search',
  );

  if ($refresh || empty($settings)) {
    // Settings fall back to default constants.
    foreach ($field_keys as $field) {
      $settings[$field] = variable_get(
        'google_appliance_' . $field,
        constant('SGA_DEFAULT_' . strtoupper($field))
      );
    }
  }
  return $settings;
}