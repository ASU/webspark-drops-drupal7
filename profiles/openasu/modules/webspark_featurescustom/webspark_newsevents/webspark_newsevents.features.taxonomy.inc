<?php
/**
 * @file
 * webspark_newsevents.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function webspark_newsevents_taxonomy_default_vocabularies() {
  return array(
    'asu_events_audience' => array(
      'name' => 'ASU Events Audience',
      'machine_name' => 'asu_events_audience',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'asu_events_category' => array(
      'name' => 'ASU Events Category',
      'machine_name' => 'asu_events_category',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'asu_events_type' => array(
      'name' => 'ASU Events Type',
      'machine_name' => 'asu_events_type',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
