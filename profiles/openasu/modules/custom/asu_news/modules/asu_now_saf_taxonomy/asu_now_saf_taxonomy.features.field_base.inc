<?php
/**
 * @file
 * asu_now_saf_taxonomy.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function asu_now_saf_taxonomy_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_home_page_display'
  $field_bases['field_home_page_display'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_home_page_display',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  return $field_bases;
}
