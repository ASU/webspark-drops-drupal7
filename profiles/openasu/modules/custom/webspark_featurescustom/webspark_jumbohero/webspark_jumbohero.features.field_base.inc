<?php
/**
 * @file
 * webspark_jumbohero.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function webspark_jumbohero_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_webspark_jumbo_position'
  $field_bases['field_webspark_jumbo_position'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_webspark_jumbo_position',
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
        'top-left' => 'top-left',
        'top-center' => 'top-center',
        'top-right' => 'top-right',
        'bottom-left' => 'bottom-left',
        'bottom-center' => 'bottom-center',
        'bottom-right' => 'bottom-right',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_webspark_jumbohero_bgimg'
  $field_bases['field_webspark_jumbohero_bgimg'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_webspark_jumbohero_bgimg',
    'foreign keys' => array(
      'file_managed' => array(
        'columns' => array(
          'fid' => 'fid',
        ),
        'table' => 'file_managed',
      ),
    ),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'backgroundfield',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'backgroundfield',
  );

  // Exported field_base: 'field_webspark_jumbohero_blurb'
  $field_bases['field_webspark_jumbohero_blurb'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_webspark_jumbohero_blurb',
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
    'type' => 'text_long',
  );

  return $field_bases;
}
