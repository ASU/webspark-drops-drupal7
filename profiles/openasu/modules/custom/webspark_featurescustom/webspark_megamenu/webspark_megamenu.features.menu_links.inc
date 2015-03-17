<?php
/**
 * @file
 * webspark_megamenu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function webspark_megamenu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_home:<front>
  $menu_links['main-menu_home:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => variable_get('site_frontpage', 'node'),
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_home:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  
  // Translatables
  // Included for use with string extractors like potx.
  t('Home');


  return $menu_links;
}
