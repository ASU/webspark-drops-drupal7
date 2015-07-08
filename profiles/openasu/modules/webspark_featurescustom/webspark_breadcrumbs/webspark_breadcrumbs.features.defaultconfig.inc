<?php
/**
 * @file
 * webspark_breadcrumbs.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function webspark_breadcrumbs_defaultconfig_features() {
  return array(
    'webspark_breadcrumbs' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function webspark_breadcrumbs_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-capitalizator_ignored_words';
  $strongarm->value = array(
    'of' => 'of',
    'and' => 'and',
    'or' => 'or',
    'de' => 'de',
    'del' => 'del',
    'y' => 'y',
    'o' => 'o',
    'the' => 'the',
    'a' => 'a',
  );
  $export['easy_breadcrumb-capitalizator_ignored_words'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-capitalizator_mode';
  $strongarm->value = 'ucwords';
  $export['easy_breadcrumb-capitalizator_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-disable_drupal_breadcrumb';
  $strongarm->value = 1;
  $export['easy_breadcrumb-disable_drupal_breadcrumb'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-home_segment_title';
  $strongarm->value = 'Home';
  $export['easy_breadcrumb-home_segment_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-include_home_segment';
  $strongarm->value = 1;
  $export['easy_breadcrumb-include_home_segment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-include_invalid_paths';
  $strongarm->value = 1;
  $export['easy_breadcrumb-include_invalid_paths'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-include_title_segment';
  $strongarm->value = 1;
  $export['easy_breadcrumb-include_title_segment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-segments_separator';
  $strongarm->value = ' / ';
  $export['easy_breadcrumb-segments_separator'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-title_from_page_when_available';
  $strongarm->value = 1;
  $export['easy_breadcrumb-title_from_page_when_available'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-title_segment_as_link';
  $strongarm->value = 0;
  $export['easy_breadcrumb-title_segment_as_link'] = $strongarm;

  return $export;
}
