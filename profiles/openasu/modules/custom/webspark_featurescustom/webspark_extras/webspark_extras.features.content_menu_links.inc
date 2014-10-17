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

  // Exported menu link: main-menu:node/32
  $menu_links['main-menu:node/32'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/32',
    'router_path' => 'node/%',
    'link_title' => 'Help & Examples',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Help & Examples');


  return $menu_links;
}
