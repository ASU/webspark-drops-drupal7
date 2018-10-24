<?php
/**
 * @file
 * asu_news_importer.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function asu_news_importer_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format asu_feeds_input_format'.
  $permissions['use text format asu_feeds_input_format'] = array(
    'name' => 'use text format asu_feeds_input_format',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
