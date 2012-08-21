<?php

/**
 * @file
 * Export / edit UI plugin for regions.
 */

$plugin = array(
  'schema' => 'layout_region',
  'access' => 'administer layouts',

  // Define the menu item.
  'menu' => array(
    // This menu item is modified in layout_menu_alter() to be a local task
    // under the regular panels layout UI.
    'menu prefix' => 'admin/structure/panels/layouts',
    'menu item' => 'regions',
    'menu title' => 'Regions',
  ),

  // Define user interface texts.
  'title singular' => t('region'),
  'title singular proper' => t('Region'),
  'title plural' => t('regions'),
  'title plural proper' => t('Regions'),
);

// No need for any more code since regions are just machine names with fancy
// admin facing titles, and that's it. They get meaning in layouts.