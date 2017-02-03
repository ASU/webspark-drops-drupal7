<?php

/**
 * @file
 * Module Update Status list alteration - remove any Webspark-maintained
 * projects.
 */

/**
 * Implememtation of hook_system_info_alter()
 *
 * This is designed to update the subtheme from openasu_bootstrap to
 * asu_webspark_bootstrap as part of the 1.0 release.
 *
 * @TODO - Remove when Webspark Classic is removed.
 */
function webspark_featurescustom_system_info_alter(&$info, $file, $type) {
  if ($type == 'theme' && isset($info['base theme']) && $info['base theme'] == 'openasu_bootstrap') {
    $info['base theme'] = 'asu_webspark_bootstrap';
  }
}

/**
 * Implementation of hook_libraries_info_alter()
 *
 * This is designed to make sure that if a subtheme has been created before
 * Kalatheme 1.4 that we are connecting it to the default ASU Bootstrap
 * library. We also want to make sure that the user doesn't actually have a
 * correct Bootstrap library already set up for their subtheme.
 */
function webspark_featurescustom_libraries_info_alter(&$libraries) {
  global $theme_info;
  if (isset($theme_info->name) && isset($theme_info->base_theme)) {
    $library_path = DRUPAL_ROOT . '/sites/all/libraries/' . $theme_info->name . '_bootstrap/css/bootstrap.css';
    if ($theme_info->name != 'asu_webspark_bootstrap' && $theme_info->base_theme == 'asu_webspark_bootstrap' && !file_exists($library_path)) {
      $libraries[$theme_info->name . '_bootstrap']['machine name'] = 'asu_webspark_bootstrap_bootstrap';
    }
  }
}

/**
 * Implements hook_update_projects_alter()
 *
 * This function will remove any Webspark-managed project from
 * the core Drupal Update Manager.
 */
function webspark_featurescustom_update_projects_alter(&$projects) {
  // List of managed components to remove from update manager
  // WEBSPARK-639 - Update "Do Not Update" project list logic

  // First check to see if the current enabled modules and themes are in the
  // Webspark profile directory AND being used as the active, default codebase
  // for the module (vs. code elsewhere, such as sites/*, etc.)
  $query = db_select('system', 's')
    ->fields('s', array('name', 'filename'))
    ->condition('status', 1)
    ->condition(db_or()
      ->condition('type', 'module')
      ->condition('type', 'theme')
    )
    ->condition('filename', 'profiles_openasu_%', 'LIKE')
    ->orderBy('name', 'ASC');

  $managed_things = $query
    ->execute()
    ->fetchCol();

  // Then add any dependencies to components managed by Webspark
  $profile_info = install_profile_info('openasu');
  foreach ($profile_info['dependencies'] as $module) {
    if (!in_array($module, $managed_things)) {  // Dupe check
      $managed_things[] = $module;
    }
    $module_info = drupal_parse_info_file(drupal_get_path('module', $module) . '/' . $module . '.info');
    if (!empty($module_info['dependencies'])) {
      foreach ($module_info['dependencies'] as $dependency) {
        $parts = explode(' (', $dependency, 2);
        $dependency_candidate = array_shift($parts);
        if (!in_array($dependency_candidate, $managed_things)) { // Dupe check
          $managed_things[] = $dependency_candidate;
        }
      }
    }
  }
  // Now remove all modules and themes managed by this distribution
  foreach ($managed_things as $managed_module) {
    unset($projects[$managed_module]);
  }
  // WEBSPARK-1043 - Remove LDAP Servers from updates list manually
  unset($projects['ldap']);
}

/**
 * Implements hook_update_status_alter()
 *
 * This function will remove any module managed by ASU WebSpark from
 * the list of modules in the Drupal Update Manager.
 */
function webspark_featurescustom_update_status_alter(&$projects) {
  // Don't want to unset this in hook_update_projects_later as per
  // https://drupal.org/node/1875386
  // But we do want to make sure the user isn't aware of updates through the GUI
  // so we mark as always up to date.
  foreach ($projects as $project_name => $project_info) {
    if ($project_name == 'drupal') {
      $projects[$project_name]['status'] = UPDATE_CURRENT;
      $projects[$project_name]['reason'] = t('Drupal core is managed by WebSpark. Do not update ANY code outside of the /sites directory manually.');
    }
  }
}
