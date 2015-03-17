<?php
/**
 * @file
 * mega_footer_menu.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function mega_footer_menu_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-mega-footer-menu.
  $menus['menu-mega-footer-menu'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'title' => 'Mega Footer Menu',
    'description' => 'The top level menu items will not be rendered as links, and instead as titles for each column of links.  Adding any more than 4 top-level links will result in the remainder being pushed to the 2nd row.  ',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Mega Footer Menu');
  t('The top level menu items will not be rendered as links, and instead as titles for each column of links.  Adding any more than 4 top-level links will result in the remainder being pushed to the 2nd row.  ');


  return $menus;
}
