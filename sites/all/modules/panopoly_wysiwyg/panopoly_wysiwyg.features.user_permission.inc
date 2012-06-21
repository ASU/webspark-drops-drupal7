<?php
/**
 * @file
 * panopoly_wysiwyg.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function panopoly_wysiwyg_user_default_permissions() {
  $permissions = array();

  // Exported permission: use text format panopoly_html_text.
  $permissions['use text format panopoly_html_text'] = array(
    'name' => 'use text format panopoly_html_text',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: use text format panopoly_wysiwyg_text.
  $permissions['use text format panopoly_wysiwyg_text'] = array(
    'name' => 'use text format panopoly_wysiwyg_text',
    'roles' => array(),
    'module' => 'filter',
  );

  return $permissions;
}
