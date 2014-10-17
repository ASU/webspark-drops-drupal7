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
  // Exported menu link: menu-mega-footer-menu_alumni:features
  $menu_links['menu-mega-footer-menu_alumni:features'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'features',
    'router_path' => 'features',
    'link_title' => 'Alumni',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_alumni:features',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-mega-footer-menu_people:http://www.asu.edu',
  );
  // Exported menu link: menu-mega-footer-menu_calendar-of-events:features
  $menu_links['menu-mega-footer-menu_calendar-of-events:features'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'features',
    'router_path' => 'features',
    'link_title' => 'Calendar of Events',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_calendar-of-events:features',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-mega-footer-menu_connect:http://www.asu.edu',
  );
  // Exported menu link: menu-mega-footer-menu_china-programs:features
  $menu_links['menu-mega-footer-menu_china-programs:features'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'features',
    'router_path' => 'features',
    'link_title' => 'China Programs',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_china-programs:features',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-mega-footer-menu_impact:http://www.asu.edu',
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
  // Exported menu link: menu-mega-footer-menu_departments:features
  $menu_links['menu-mega-footer-menu_departments:features'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'features',
    'router_path' => 'features',
    'link_title' => 'Departments',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_departments:features',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-mega-footer-menu_academics:<front>',
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
  // Exported menu link: menu-mega-footer-menu_knowwpc:http://wpcarey.asu.edu/
  $menu_links['menu-mega-footer-menu_knowwpc:http://wpcarey.asu.edu/'] = array(
    'menu_name' => 'menu-mega-footer-menu',
    'link_path' => 'http://wpcarey.asu.edu/',
    'router_path' => '',
    'link_title' => 'KnowWPC',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-mega-footer-menu_knowwpc:http://wpcarey.asu.edu/',
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
  // Translatables
  // Included for use with string extractors like potx.
  t('Academics');
  t('Alumni');
  t('Calendar of Events');
  t('China Programs');
  t('Connect');
  t('Departments');
  t('Impact');
  t('KnowWPC');
  t('People');


  return $menu_links;
}
