<?php
/**
 * @file
 * asu_news_importer.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function asu_news_importer_defaultconfig_features() {
  return array(
    'asu_news_importer' => array(
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function asu_news_importer_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_asu_news_pattern';
  $strongarm->value = 'news/[node:title]';
  $export['pathauto_node_asu_news_pattern'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function asu_news_importer_defaultconfig_user_default_permissions() {
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
