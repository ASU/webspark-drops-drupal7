<?php
/**
 * @file
 * uto_carousel.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function uto_carousel_defaultconfig_features() {
  return array(
    'uto_carousel' => array(
      'field_default_fields' => 'field_default_fields',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function uto_carousel_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'fieldable_panels_pane-uto_carousel-field_items'.
  $fields['fieldable_panels_pane-uto_carousel-field_items'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_items',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'uto_carousel',
      'settings' => array(
        'default_image' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'uto_carousel',
    ),
    'field_instance' => array(
      'bundle' => 'uto_carousel',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'uto_carousel',
          'settings' => array(
            'caption' => FALSE,
            'image_style' => 'thumbnail',
            'optionset' => '4_item_carousel',
          ),
          'type' => 'uto_carousel',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_items',
      'label' => 'Items',
      'required' => 0,
      'settings' => array(
        'alt_field' => 0,
        'default_image' => 0,
        'file_directory' => 'general',
        'file_extensions' => 'jpg jpeg gif png',
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'uto_carousel',
        'settings' => array(
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        ),
        'type' => 'uto_carousel_form',
        'weight' => -4,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Items');

  return $fields;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function uto_carousel_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fieldable uto_carousel'.
  $permissions['create fieldable uto_carousel'] = array(
    'name' => 'create fieldable uto_carousel',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable uto_carousel'.
  $permissions['delete fieldable uto_carousel'] = array(
    'name' => 'delete fieldable uto_carousel',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable uto_carousel'.
  $permissions['edit fieldable uto_carousel'] = array(
    'name' => 'edit fieldable uto_carousel',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  return $permissions;
}
