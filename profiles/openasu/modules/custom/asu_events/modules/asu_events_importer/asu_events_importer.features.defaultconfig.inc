<?php
/**
 * @file
 * asu_events_importer.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function asu_events_importer_defaultconfig_features() {
  return array(
    'asu_events_importer' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function asu_events_importer_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_asu_event_pattern';
  $strongarm->value = 'events/[node:title]';
  $export['pathauto_node_asu_event_pattern'] = $strongarm;

  return $export;
}
