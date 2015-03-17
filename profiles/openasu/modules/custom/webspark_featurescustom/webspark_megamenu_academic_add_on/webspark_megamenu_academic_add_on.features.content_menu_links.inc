<?php
/**
 * @file
 * webspark_megamenu_academic_add_on.features.content_menu_links.inc
 */

/**
 * Implements hook_content_menu_links_defaults().
 */
function webspark_megamenu_academic_add_on_content_menu_links_defaults() {
  $menu_links = array();

  // Exported menu link: main-menu_about:https
  $menu_links['main-menu_about:https'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'https://webspark.asu.edu/',
    'router_path' => '',
    'link_title' => 'About',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
  );
  // Exported menu link: main-menu_admissions:https
  $menu_links['main-menu_admissions:https'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'https://webspark.asu.edu/',
    'router_path' => '',
    'link_title' => 'Admissions',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
  );
  // Exported menu link: main-menu_degree-programs:https
  $menu_links['main-menu_degree-programs:https'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'https://webspark.asu.edu/',
    'router_path' => '',
    'link_title' => 'Degree Programs',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
  );
  // Exported menu link: main-menu_student-life:https
  $menu_links['main-menu_student-life:https'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'https://webspark.asu.edu/',
    'router_path' => '',
    'link_title' => 'Student Life',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About');
  t('Admissions');
  t('Degree Programs');
  t('Student Life');


  return $menu_links;
}
