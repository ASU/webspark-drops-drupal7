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

  // Exported permission: 'create fieldable spotlight'.
  $permissions['create fieldable spotlight'] = array(
    'name' => 'create fieldable spotlight',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable spotlight'.
  $permissions['delete fieldable spotlight'] = array(
    'name' => 'delete fieldable spotlight',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable spotlight'.
  $permissions['edit fieldable spotlight'] = array(
    'name' => 'edit fieldable spotlight',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // WEBSPARK-462 - update perms
  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(),
    'module' => 'system',
  );

  return $permissions;
}
