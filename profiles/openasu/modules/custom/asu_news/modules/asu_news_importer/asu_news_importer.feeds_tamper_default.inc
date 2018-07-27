<?php
/**
 * @file
 * asu_news_importer.feeds_tamper_default.inc
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function asu_news_importer_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'asu_news_importer-xpathparser_1-html_entity_decode';
  $feeds_tamper->importer = 'asu_news_importer';
  $feeds_tamper->source = 'xpathparser:1';
  $feeds_tamper->plugin_id = 'html_entity_decode';
  $feeds_tamper->settings = array();
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'HTML entity decode';
  $export['asu_news_importer-xpathparser_1-html_entity_decode'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'asu_news_importer-xpathparser_1-html_entity_decode_1';
  $feeds_tamper->importer = 'asu_news_importer';
  $feeds_tamper->source = 'xpathparser:1';
  $feeds_tamper->plugin_id = 'html_entity_decode';
  $feeds_tamper->settings = array();
  $feeds_tamper->weight = 2;
  $feeds_tamper->description = 'HTML entity decode 1';
  $export['asu_news_importer-xpathparser_1-html_entity_decode_1'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'asu_news_importer-xpathparser_28-asu_feeds2_timezone';
  $feeds_tamper->importer = 'asu_news_importer';
  $feeds_tamper->source = 'xpathparser:28';
  $feeds_tamper->plugin_id = 'asu_feeds2_timezone';
  $feeds_tamper->settings = array(
    'timezone' => 'America/Phoenix',
  );
  $feeds_tamper->weight = 1;
  $feeds_tamper->description = 'Adjust imported time for timezone';
  $export['asu_news_importer-xpathparser_28-asu_feeds2_timezone'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'asu_news_importer-xpathparser_28-strtotime';
  $feeds_tamper->importer = 'asu_news_importer';
  $feeds_tamper->source = 'xpathparser:28';
  $feeds_tamper->plugin_id = 'strtotime';
  $feeds_tamper->settings = array();
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'String to Unix timestamp';
  $export['asu_news_importer-xpathparser_28-strtotime'] = $feeds_tamper;

  return $export;
}
