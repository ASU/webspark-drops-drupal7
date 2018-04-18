<?php
/**
 * @file
 * asu_dir_perms.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function asu_dir_user_default_permissions() {
  $permissions = array();

  // Exported permission: Administer ASU Directory Configuration
  $permissions['Administer ASU Directory Configuration'] = array(
    'name' => 'Administer ASU Directory Configuration',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'asu_dir',
  );

  return $permissions;
}
