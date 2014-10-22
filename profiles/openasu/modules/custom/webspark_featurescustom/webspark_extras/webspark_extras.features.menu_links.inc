<?php
/**
 * @file
 * webspark_extras.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function webspark_extras_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_help:http://webspark.asu.edu/help
  $menu_links['management_help:webspark-help'] = array(
    'menu_name' => 'management',
    'link_path' => 'http://webspark.asu.edu/help',
    'router_path' => '',
    'link_title' => 'Help',
    'options' => array(
      'attributes' => array(
        'title' => 'WebSpark Help',
      ),
      'identifier' => 'management_help:webspark-help',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 42,
    'customized' => 1,
    'parent_identifier' => 'management_administration:admin',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Help');


  return $menu_links;
}
