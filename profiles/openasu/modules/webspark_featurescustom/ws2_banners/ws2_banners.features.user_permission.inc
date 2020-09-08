<?php

/**
 * @file
 * ws2_banners.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ws2_banners_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fieldable banners_ws2'.
  $permissions['create fieldable banners_ws2'] = array(
    'name' => 'create fieldable banners_ws2',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable banners_ws2'.
  $permissions['delete fieldable banners_ws2'] = array(
    'name' => 'delete fieldable banners_ws2',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable banners_ws2'.
  $permissions['edit fieldable banners_ws2'] = array(
    'name' => 'edit fieldable banners_ws2',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  return $permissions;
}
