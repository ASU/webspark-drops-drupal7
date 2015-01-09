<?php
/**
 * @file
 * asu_maps_enhanced.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function asu_maps_enhanced_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fieldable asu_maps_enhanced'.
  $permissions['create fieldable asu_maps_enhanced'] = array(
    'name' => 'create fieldable asu_maps_enhanced',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable asu_maps_enhanced'.
  $permissions['delete fieldable asu_maps_enhanced'] = array(
    'name' => 'delete fieldable asu_maps_enhanced',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable asu_maps_enhanced'.
  $permissions['edit fieldable asu_maps_enhanced'] = array(
    'name' => 'edit fieldable asu_maps_enhanced',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  return $permissions;
}
