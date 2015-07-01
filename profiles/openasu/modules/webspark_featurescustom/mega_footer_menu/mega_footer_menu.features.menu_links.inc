<?php
/**
 * @file
 * mega_footer_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mega_footer_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-mega-footer-menu_academics:<front>
  $menu_links['menu-mega-footer-menu_academics:<front>'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Academics',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_academics:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-mega-footer-menu_connect:http://www.asu.edu
  $menu_links['menu-mega-footer-menu_connect:http://www.asu.edu'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'http://www.asu.edu',
    'router_path' => '',
    'link_title' => 'Connect',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_connect:http://www.asu.edu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-mega-footer-menu_impact:http://www.asu.edu
  $menu_links['menu-mega-footer-menu_impact:http://www.asu.edu'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'http://www.asu.edu',
    'router_path' => '',
    'link_title' => 'Impact',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_impact:http://www.asu.edu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-mega-footer-menu_people:http://www.asu.edu
  $menu_links['menu-mega-footer-menu_people:http://www.asu.edu'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'http://www.asu.edu',
    'router_path' => '',
    'link_title' => 'People',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_people:http://www.asu.edu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-mega-footer-menu_testlink1:http://asu.edu
  $menu_links['menu-mega-footer-menu_testlink1:http://asu.edu'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'http://asu.edu',
    'router_path' => '',
    'link_title' => 'Testlink1',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_testlink1:http://asu.edu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-mega-footer-menu_impact:http://www.asu.edu',
  );
  // Exported menu link: menu-mega-footer-menu_testlink2:http://asu.edu
  $menu_links['menu-mega-footer-menu_testlink2:http://asu.edu'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'http://asu.edu',
    'router_path' => '',
    'link_title' => 'Testlink2',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_testlink2:http://asu.edu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-mega-footer-menu_people:http://www.asu.edu',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Academics');
  t('Connect');
  t('Impact');
  t('People');
  t('Testlink1');
  t('Testlink2');


  return $menu_links;
}
