<?php
/**
 * @file
 * asu_maps_enhanced.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function asu_maps_enhanced_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_asu_maps_enhanced_items'
  $field_bases['field_asu_maps_enhanced_items'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_asu_maps_enhanced_items',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'asu_maps_enhanced',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'asu_maps_enhanced',
  );

  return $field_bases;
}
