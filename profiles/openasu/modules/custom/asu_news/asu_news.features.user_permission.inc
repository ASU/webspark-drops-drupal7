<?php
/**
 * @file
 * asu_news.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function asu_news_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer features.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: administer feeds.
  $permissions['administer feeds'] = array(
    'name' => 'administer feeds',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'feeds',
  );

  // Exported permission: administer fieldgroups.
  $permissions['administer fieldgroups'] = array(
    'name' => 'administer fieldgroups',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'field_group',
  );

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

  // Exported permission: clear asu_news_importer feeds.
  $permissions['clear asu_news_importer feeds'] = array(
    'name' => 'clear asu_news_importer feeds',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'feeds',
  );

  // Exported permission: create asu_news content.
  $permissions['create asu_news content'] = array(
    'name' => 'create asu_news content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any asu_news content.
  $permissions['delete any asu_news content'] = array(
    'name' => 'delete any asu_news content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own asu_news content.
  $permissions['delete own asu_news content'] = array(
    'name' => 'delete own asu_news content',
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

  // Exported permission: edit any asu_news content.
  $permissions['edit any asu_news content'] = array(
    'name' => 'edit any asu_news content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own asu_news content.
  $permissions['edit own asu_news content'] = array(
    'name' => 'edit own asu_news content',
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

  // Exported permission: import asu_news_importer feeds.
  $permissions['import asu_news_importer feeds'] = array(
    'name' => 'import asu_news_importer feeds',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'feeds',
  );

  // Exported permission: manage features.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'features',
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
