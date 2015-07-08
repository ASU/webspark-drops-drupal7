<?php
/**
 * @file
 * webspark_extras.features.content_menu_links.inc
 */

/**
 * Implements hook_content_menu_links_defaults().
 */
function webspark_extras_content_menu_links_defaults() {
  $menu_links = array();

  // Exported menu link: management_help:webspark-help
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
    'parent_path' => 'admin',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Help');


  return $menu_links;
}
