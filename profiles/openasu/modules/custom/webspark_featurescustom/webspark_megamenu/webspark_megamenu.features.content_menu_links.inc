<?php
/**
 * @file
 * webspark_megamenu.features.content_menu_links.inc
 */

/**
 * Implements hook_content_menu_links_defaults().
 */
function webspark_megamenu_content_menu_links_defaults() {
  $menu_links = array();

  // Exported menu link: main-menu_admissions:<front>
  $menu_links['main-menu_admissions:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'https://webspark.asu.edu/help',
    'router_path' => '',
    'link_title' => 'Admissions',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_admissions:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: main-menu_degree-programs:<front>
  $menu_links['main-menu_degree-programs:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'https://webspark.asu.edu/help',
    'router_path' => '',
    'link_title' => 'Degree Programs',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_degree-programs:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: main-menu_home:<front>
  $menu_links['main-menu_home:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
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
  // Exported menu link: main-menu_student-life:<front>
  $menu_links['main-menu_student-life:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'https://webspark.asu.edu/help',
    'router_path' => '',
    'link_title' => 'Student Life',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_student-life:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: main-menu_student-life:<front>
  $menu_links['main-menu_about:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'https://webspark.asu.edu/help',
    'router_path' => '',
    'link_title' => 'About',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_about:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Admissions');
  t('Degree Programs');
  t('Home');
  t('Student Life');
  t('About');


  return $menu_links;
}

