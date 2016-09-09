<?php
/**
 * @file
 * asu_events_importer.feeds_tamper_default.inc
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function asu_events_importer_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'asu_events_importer-xpathparser_31-rewrite';
  $feeds_tamper->importer = 'asu_events_importer';
  $feeds_tamper->source = 'xpathparser:31';
  $feeds_tamper->plugin_id = 'rewrite';
  $feeds_tamper->settings = array(
    'text' => 'Tickets/RSVP',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Rewrite';

  $export[$feeds_tamper->id] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'asu_events_importer-xpathparser_1-html_entity_decode';
  $feeds_tamper->importer = 'asu_events_importer';
  $feeds_tamper->source = 'xpathparser:1';
  $feeds_tamper->plugin_id = 'html_entity_decode';
  $feeds_tamper->settings = '';
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'HTML entity decode';

  $export[$feeds_tamper->id] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'asu_events_importer-xpathparser_1-html_entity_decode_1';
  $feeds_tamper->importer = 'asu_events_importer';
  $feeds_tamper->source = 'xpathparser:1';
  $feeds_tamper->plugin_id = 'html_entity_decode';
  $feeds_tamper->settings = '';
  $feeds_tamper->weight = 1;
  $feeds_tamper->description = 'HTML entity decode';

  $export[$feeds_tamper->id] = $feeds_tamper;

  return $export;
}
