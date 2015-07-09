<?php
/**
 * @file
 * asu_directory.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function asu_dir_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_asu_maps_enhanced_items'
  $field_bases['field_asu_directory_items'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_asu_directory_items',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'asu_dir',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'asu_directory',
  );

  return $field_bases;
}
