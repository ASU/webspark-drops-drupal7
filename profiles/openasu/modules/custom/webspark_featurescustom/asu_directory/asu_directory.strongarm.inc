<?php
/**
 * @file
 * asu_directory.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function asu_directory_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_asu_directory_person';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_asu_directory_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_asu_directory_person';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_asu_directory_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_asu_directory_person';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_asu_directory_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_asu_directory_person';
  $strongarm->value = '1';
  $export['node_preview_asu_directory_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_asu_directory_person';
  $strongarm->value = 1;
  $export['node_submitted_asu_directory_person'] = $strongarm;

  return $export;
}
