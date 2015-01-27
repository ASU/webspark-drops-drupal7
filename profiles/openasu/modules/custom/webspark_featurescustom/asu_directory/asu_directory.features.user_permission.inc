<?php
/**
 * @file
 * asu_directory.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function asu_directory_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer panelizer node asu_directory_person breadcrumbs'.
  $permissions['administer panelizer node asu_directory_person breadcrumbs'] = array(
    'name' => 'administer panelizer node asu_directory_person breadcrumbs',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node asu_directory_person content'.
  $permissions['administer panelizer node asu_directory_person content'] = array(
    'name' => 'administer panelizer node asu_directory_person content',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node asu_directory_person context'.
  $permissions['administer panelizer node asu_directory_person context'] = array(
    'name' => 'administer panelizer node asu_directory_person context',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node asu_directory_person defaults'.
  $permissions['administer panelizer node asu_directory_person defaults'] = array(
    'name' => 'administer panelizer node asu_directory_person defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node asu_directory_person layout'.
  $permissions['administer panelizer node asu_directory_person layout'] = array(
    'name' => 'administer panelizer node asu_directory_person layout',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node asu_directory_person overview'.
  $permissions['administer panelizer node asu_directory_person overview'] = array(
    'name' => 'administer panelizer node asu_directory_person overview',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node asu_directory_person settings'.
  $permissions['administer panelizer node asu_directory_person settings'] = array(
    'name' => 'administer panelizer node asu_directory_person settings',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'clear asu_directory_feed feeds'.
  $permissions['clear asu_directory_feed feeds'] = array(
    'name' => 'clear asu_directory_feed feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: 'create asu_directory_feed content'.
  $permissions['create asu_directory_feed content'] = array(
    'name' => 'create asu_directory_feed content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create asu_directory_person content'.
  $permissions['create asu_directory_person content'] = array(
    'name' => 'create asu_directory_person content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any asu_directory_feed content'.
  $permissions['delete any asu_directory_feed content'] = array(
    'name' => 'delete any asu_directory_feed content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any asu_directory_person content'.
  $permissions['delete any asu_directory_person content'] = array(
    'name' => 'delete any asu_directory_person content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own asu_directory_feed content'.
  $permissions['delete own asu_directory_feed content'] = array(
    'name' => 'delete own asu_directory_feed content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own asu_directory_person content'.
  $permissions['delete own asu_directory_person content'] = array(
    'name' => 'delete own asu_directory_person content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any asu_directory_feed content'.
  $permissions['edit any asu_directory_feed content'] = array(
    'name' => 'edit any asu_directory_feed content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any asu_directory_person content'.
  $permissions['edit any asu_directory_person content'] = array(
    'name' => 'edit any asu_directory_person content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own asu_directory_feed content'.
  $permissions['edit own asu_directory_feed content'] = array(
    'name' => 'edit own asu_directory_feed content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own asu_directory_person content'.
  $permissions['edit own asu_directory_person content'] = array(
    'name' => 'edit own asu_directory_person content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'import asu_directory_feed feeds'.
  $permissions['import asu_directory_feed feeds'] = array(
    'name' => 'import asu_directory_feed feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: 'unlock asu_directory_feed feeds'.
  $permissions['unlock asu_directory_feed feeds'] = array(
    'name' => 'unlock asu_directory_feed feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: 'use text format asu_feeds'.
  $permissions['use text format asu_feeds'] = array(
    'name' => 'use text format asu_feeds',
    'roles' => array(),
    'module' => 'filter',
  );

  return $permissions;
}
