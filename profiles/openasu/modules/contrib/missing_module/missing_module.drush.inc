<?php

/**
 * @file
 * Find modules missing in file system.
 */

/**
 * Implements hook_drush_command().
 */
function missing_module_drush_command() {
  $items = array();
  $items['list-missing-modules'] = array(
    'description' => "Lists modules activated in database, that are missing in filesystem.",
    'options' => array(
      'only-enabled' => dt('Only include enabled modules.'),
    ),
    'examples' => array(
      'drush lmm' => 'Lists modules activated in database, that are missing in filesystem.',
    ),
    'aliases' => array('lmm'),
  );
  $items['remove-missing-modules'] = array(
    'description' => "Remove modules from database, that are missing in filesystem.",
    'options' => array(
      'only-enabled' => dt('Only include enabled modules.'),
    ),
    'examples' => array(
      'drush rmm' => 'Remove modules from database, that are missing in filesystem.',
    ),
    'aliases' => array('rmm'),
  );
  return $items;
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_missing_module_list_missing_modules() {

  // Include the module file directly when run from drush.
  if (!function_exists('missing_module_find_missing')) {
    include_once(dirname(__FILE__) . '/missing_module.module');
  }

  $modules = missing_module_find_missing(drush_get_option('only-enabled', FALSE));

  if ($modules) {
    drush_log(count($modules) . " Missing module(s) found.", 'warning');
    $contrib_modules_name = array();
    $custom_modules_name = array();
    foreach ($modules as $name => $mm) {
      $title = $name;
      if (!empty($mm['info']['version'])) {
        $title .= ' ' . $mm['info']['version'];
      }

      if (!empty($mm['info']['project'])) {
        $contrib_modules_name[] = $title;
      }
      else {
        $custom_modules_name[] = $title;
      }

      if ($mm['status']) {
        $title .= ' (not disabled and not uninstalled)';
      }
      else {
        $title .= ' (disabled but not uninstalled)';
      }

      drush_log("MODULE: $title", 'warning');
    }

    if (!empty($contrib_modules_name)) {
      drush_log("Contrib modules. Just run this command: drush dl " . implode(', ', $contrib_modules_name), 'warning');
    }
    if (!empty($custom_modules_name)) {
      drush_log("Custom modules: " . implode(', ', $custom_modules_name), 'warning');
    }
  }
  else {
    drush_log("no missing modules found.", 'success');
  }
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_missing_module_remove_missing_modules() {

  // Include the module file directly when run from drush.
  if (!function_exists('missing_module_find_missing')) {
    include_once(dirname(__FILE__) . '/missing_module.module');
  }

  $modules = missing_module_find_missing(drush_get_option('only-enabled', FALSE));

  if ($modules) {
    drush_log(count($modules) . " Missing module(s) found.", 'warning');
    foreach (array_keys($modules) as $mm) {
      drush_log("MODULE: $mm", 'warning');
    }

    if (drush_confirm("Are you sure you want to remove these modules from Drupal's system table?")) {
      drush_log("Removing system records for: " . implode(array_keys($modules), " "), 'warning');
      // Delete if there is no modules.
        db_delete('system')
          ->condition('name', array_keys($modules), 'IN')
          ->execute();
    }

  }
  else {
    drush_log("no missing modules found.", 'success');
  }
}
