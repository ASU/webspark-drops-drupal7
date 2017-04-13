<?php

/**
 * @file
 * Default rules configuration for membership transactions.
 */

/**
 * Implements hook_default_rules_configuration().
 *
 * Scans the /rules directory for files with the .rule extension. A .rule
 * file must populate the $rule variable with the exported rule string.
 */
function membership_entity_commerce_default_rules_configuration() {
  // Import rule definitions. @see https://drupal.org/node/884584.
  $config = array();
  $rules_path = drupal_get_path('module', 'membership_entity_commerce') . '/rules';
  $files = file_scan_directory($rules_path, '/\.rule$/');
  foreach ($files as $filepath => $file) {
    require $filepath;
    if (isset($rule)) {
      $config['membership_entity_commerce_' . $file->name] = rules_import($rule);
    }
  }
  return $config;
}
