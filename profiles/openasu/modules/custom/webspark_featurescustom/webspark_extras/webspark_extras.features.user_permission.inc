<?php
/**
 * @file
 * webspark_extras.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function webspark_extras_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contextual',
  );

  return $permissions;
}
