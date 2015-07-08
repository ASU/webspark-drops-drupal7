<?php
/**
 * @file
 * uto_carousel.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function uto_carousel_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_items'
  $field_bases['field_items'] = array(
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
  );

  return $field_bases;
}
