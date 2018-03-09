<?php
/**
 * @file
 * asu_spotlight.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function asu_spotlight_defaultconfig_features() {
  return array(
    'asu_spotlight' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function asu_spotlight_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fieldable asu_spotlight'.
  $permissions['create fieldable asu_spotlight'] = array(
    'name' => 'create fieldable asu_spotlight',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable asu_spotlight'.
  $permissions['delete fieldable asu_spotlight'] = array(
    'name' => 'delete fieldable asu_spotlight',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable asu_spotlight'.
  $permissions['edit fieldable asu_spotlight'] = array(
    'name' => 'edit fieldable asu_spotlight',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  return $permissions;
}
