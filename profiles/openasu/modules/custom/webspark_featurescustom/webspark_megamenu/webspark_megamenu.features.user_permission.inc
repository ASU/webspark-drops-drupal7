<?php
/**
 * @file
 * webspark_megamenu.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function webspark_megamenu_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer tb_megamenu'.
  $permissions['administer tb_megamenu'] = array(
    'name' => 'administer tb_megamenu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'tb_megamenu',
  );

  return $permissions;
}
