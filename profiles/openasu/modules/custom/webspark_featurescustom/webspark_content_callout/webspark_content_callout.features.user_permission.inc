<?php
/**
 * @file
 * webspark_content_callout.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function webspark_content_callout_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer panelizer node content_callout defaults'.
  $permissions['administer panelizer node content_callout defaults'] = array(
    'name' => 'administer panelizer node content_callout defaults',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'create content_callout content'.
  $permissions['create content_callout content'] = array(
    'name' => 'create content_callout content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any content_callout content'.
  $permissions['delete any content_callout content'] = array(
    'name' => 'delete any content_callout content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own content_callout content'.
  $permissions['delete own content_callout content'] = array(
    'name' => 'delete own content_callout content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any content_callout content'.
  $permissions['edit any content_callout content'] = array(
    'name' => 'edit any content_callout content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own content_callout content'.
  $permissions['edit own content_callout content'] = array(
    'name' => 'edit own content_callout content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
