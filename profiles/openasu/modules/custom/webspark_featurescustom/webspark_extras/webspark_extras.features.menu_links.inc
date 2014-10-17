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

  // Exported menu link: main-menu_help:node/24
  $menu_links['main-menu_help:node/24'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/24',
    'router_path' => 'node/%',
    'link_title' => 'Help',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'main-menu_help:node/24',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 50,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Help');


  return $menu_links;
}
