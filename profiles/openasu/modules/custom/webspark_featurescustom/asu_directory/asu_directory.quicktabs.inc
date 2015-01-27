<?php
/**
 * @file
 * asu_directory.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function asu_directory_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'asu_directory_profile_tabs';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = TRUE;
  $quicktabs->default_tab = 999999;
  $quicktabs->title = 'ASU Directory Profile Tabs';
  $quicktabs->tabs = array(
    0 => array(
      'bid' => 'views_delta_asu_directory_people-block_1',
      'hide_title' => 1,
      'title' => 'Bio',
      'weight' => '-100',
      'type' => 'block',
    ),
    1 => array(
      'bid' => 'views_delta_asu_directory_people-block_2',
      'hide_title' => 1,
      'title' => 'Research Interests',
      'weight' => '-99',
      'type' => 'block',
    ),
  );
  $quicktabs->renderer = 'ui_tabs';
  $quicktabs->style = 'default';
  $quicktabs->options = array(
    'history' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('ASU Directory Profile Tabs');
  t('Bio');
  t('Research Interests');

  $export['asu_directory_profile_tabs'] = $quicktabs;

  return $export;
}
