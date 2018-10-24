<?php
/**
 * @file
 * asu_events_importer.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function asu_events_importer_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_asu_event_pattern';
  $strongarm->value = 'events/[node:title]';
  $export['pathauto_node_asu_event_pattern'] = $strongarm;

  return $export;
}
