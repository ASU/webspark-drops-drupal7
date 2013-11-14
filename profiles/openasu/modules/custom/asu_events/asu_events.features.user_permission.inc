<?php
/**
 * @file
 * asu_events.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function asu_events_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer filters.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: administer image styles.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'image',
  );

  // Exported permission: clear asu_events_importer feeds.
  $permissions['clear asu_events_importer feeds'] = array(
    'name' => 'clear asu_events_importer feeds',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'feeds',
  );

  // Exported permission: create asu_event content.
  $permissions['create asu_event content'] = array(
    'name' => 'create asu_event content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any asu_event content.
  $permissions['delete any asu_event content'] = array(
    'name' => 'delete any asu_event content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own asu_event content.
  $permissions['delete own asu_event content'] = array(
    'name' => 'delete own asu_event content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete terms in 2.
  $permissions['delete terms in 2'] = array(
    'name' => 'delete terms in 2',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 3.
  $permissions['delete terms in 3'] = array(
    'name' => 'delete terms in 3',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 4.
  $permissions['delete terms in 4'] = array(
    'name' => 'delete terms in 4',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit any asu_event content.
  $permissions['edit any asu_event content'] = array(
    'name' => 'edit any asu_event content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own asu_event content.
  $permissions['edit own asu_event content'] = array(
    'name' => 'edit own asu_event content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit terms in 2.
  $permissions['edit terms in 2'] = array(
    'name' => 'edit terms in 2',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 3.
  $permissions['edit terms in 3'] = array(
    'name' => 'edit terms in 3',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 4.
  $permissions['edit terms in 4'] = array(
    'name' => 'edit terms in 4',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: import asu_events_importer feeds.
  $permissions['import asu_events_importer feeds'] = array(
    'name' => 'import asu_events_importer feeds',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'feeds',
  );

  // Exported permission: use text format asu_feeds_input_format.
  $permissions['use text format asu_feeds_input_format'] = array(
    'name' => 'use text format asu_feeds_input_format',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
