<?php
/**
 * @file
 * asu_isearch_office_hours.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function asu_isearch_office_hours_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_isearch_local_office_hours'
  $field_bases['field_isearch_local_office_hours'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_isearch_local_office_hours',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'office_hours',
    'settings' => array(
      'cardinality' => 2,
      'granularity' => 15,
      'hoursformat' => 0,
      'limitend' => '',
      'limitstart' => '',
      'valhrs' => 0,
    ),
    'translatable' => 0,
    'type' => 'office_hours',
  );

  return $field_bases;
}
