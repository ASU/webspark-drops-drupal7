<?php
/**
 * @file
 * webspark_jumbohero.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function webspark_jumbohero_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fieldable jumbohero'.
  $permissions['create fieldable jumbohero'] = array(
    'name' => 'create fieldable jumbohero',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable jumbohero'.
  $permissions['delete fieldable jumbohero'] = array(
    'name' => 'delete fieldable jumbohero',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable jumbohero'.
  $permissions['edit fieldable jumbohero'] = array(
    'name' => 'edit fieldable jumbohero',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  return $permissions;
}
