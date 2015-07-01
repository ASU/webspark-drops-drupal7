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

  // Exported field_base: 'field_map_action_link'
  $field_bases['field_map_action_link'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_map_action_link',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'link',
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'rel' => '',
        'target' => 'default',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'title' => 'optional',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
    ),
    'translatable' => 0,
    'type' => 'link_field',
  );

  // Exported field_base: 'field_map_info'
  $field_bases['field_map_info'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_map_info',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_with_summary',
    );

  return $field_bases;
}
