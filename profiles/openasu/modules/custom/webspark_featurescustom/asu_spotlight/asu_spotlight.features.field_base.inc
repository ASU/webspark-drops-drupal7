<?php
/**
 * @file
 * panopoly_widgets.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function asu_spotlight_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_basic_spotlight_items'
  $field_bases['field_asu_spotlight_items'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_asu_spotlight_items',
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
    'module' => 'panopoly_widgets',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'asu_spotlight',
  );

  return $field_bases;
}
