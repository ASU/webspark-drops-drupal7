<?php
/**
 * @file
 * webspark_banner.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function webspark_banner_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fieldable banner'.
  $permissions['create fieldable banner'] = array(
    'name' => 'create fieldable banner',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable banner'.
  $permissions['delete fieldable banner'] = array(
    'name' => 'delete fieldable banner',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable banner'.
  $permissions['edit fieldable banner'] = array(
    'name' => 'edit fieldable banner',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  return $permissions;
}
