<?php
/**
 * @file
 * webspark_hero.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function webspark_hero_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fieldable hero'.
  $permissions['create fieldable hero'] = array(
    'name' => 'create fieldable hero',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable hero'.
  $permissions['delete fieldable hero'] = array(
    'name' => 'delete fieldable hero',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable hero'.
  $permissions['edit fieldable hero'] = array(
    'name' => 'edit fieldable hero',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  return $permissions;
}
