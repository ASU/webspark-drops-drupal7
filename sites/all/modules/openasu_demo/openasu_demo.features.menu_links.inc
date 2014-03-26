<?php
/**
 * @file
 * openasu_demo.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function openasu_demo_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_how-to-edit-a-site:node/19
  $menu_links['main-menu_how-to-edit-a-site:node/19'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/19',
    'router_path' => 'node/%',
    'link_title' => 'How to Edit a Site',
    'options' => array(
      'identifier' => 'main-menu_how-to-edit-a-site:node/19',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'main-menu_about:node/2',
  );
  // Exported menu link: main-menu_maps:node/18
  $menu_links['main-menu_maps:node/18'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/18',
    'router_path' => 'node/%',
    'link_title' => 'Maps',
    'options' => array(
      'identifier' => 'main-menu_maps:node/18',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'main-menu_features:node/1',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('How to Edit a Site');
  t('Maps');


  return $menu_links;
}
