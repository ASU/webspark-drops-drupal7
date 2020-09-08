<?php

/**
 * @file
 * asu_ap_feature.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function asu_ap_feature_defaultconfig_features() {
  return array(
    'asu_ap_feature' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function asu_ap_feature_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format asu_feeds_text_format'.
  $permissions['use text format asu_feeds_text_format'] = array(
    'name' => 'use text format asu_feeds_text_format',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
