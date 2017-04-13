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
    'asu_events_interests' => array(
      'name' => 'ASU Events Interests',
      'machine_name' => 'asu_events_interests',
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
    'asu_events_units' => array(
      'name' => 'ASU Events College Units',
      'machine_name' => 'asu_events_units',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'asu_news_audiences' => array(
      'name' => 'ASU News Audiences',
      'machine_name' => 'asu_news_audiences',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'asu_news_interests' => array(
      'name' => 'ASU News Interests',
      'machine_name' => 'asu_news_interests',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'asu_news_locations' => array(
      'name' => 'ASU News Locations',
      'machine_name' => 'asu_news_locations',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'asu_news_types' => array(
      'name' => 'ASU News Types',
      'machine_name' => 'asu_news_types',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'asu_news_units' => array(
      'name' => 'ASU News Units',
      'machine_name' => 'asu_news_units',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
