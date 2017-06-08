<?php

/**
 * @file
 * Module Update Status list alteration - remove any Webspark-maintained
 * projects.
 */

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
  // WEBSPARK-1043 - Remove LDAP modules from updates list manually
  $package_toremove = 'ldap';
  $length = strlen($package_toremove);
  foreach ($projects as $project) {
    if (strpos($project['name'], $package_toremove) === 0) {
      // ensure only module and module_submodules (i.e. ldap, ldap_*) are removed
      if (strlen($project['name']) === $length ||
        (strlen($project['name']) > $length && strpos($project['name'], '_', $length))) {
        unset($projects[$project['name']]);
      }
    }
  }
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
      $projects[$project_name]['reason'] = t('Drupal core is managed by WebSpark. ' .
          'Do not update ANY code outside of the /sites directory manually.');
    }
  }
}
