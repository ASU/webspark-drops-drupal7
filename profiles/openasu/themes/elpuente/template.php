<?php

/**
 * ASU Scholar theme customizations for template files 
 */

/**
 * Implements hook_preprocess_page()
 */
function elpuente_preprocess_page(&$variables) {
  elpuente_check_for_home();
  // Pull in ASU Brand generated blocks.
  module_load_include('inc', 'asu_brand', 'asu_brand.block');
  $header = asu_brand_get_block_header();
  $footer = asu_brand_get_block_footer();
  $variables['page']['asu_brand_header'] = $header;
  $variables['page']['asu_brand_footer'] = $footer;

  // Pull in more elements
  if (module_exists('asu_os_boxes')) {
    // Site info (will be header title below ASU logo
    module_load_include('inc', 'asu_os_boxes', 'asu_os_boxes_site_info');
    $site_info = asu_os_boxes_site_info::load('os_box_asu_more_site_info');
    $site_info = $site_info->render();
    $variables['page']['asu_site_title'] = $site_info['content'];
    // Main menu
    module_load_include('inc', 'asu_os_boxes', 'asu_os_boxes_main_menu');
    $main_menu = asu_os_boxes_main_menu::load('os_box_asu_more_main_menu');
    $main_menu = $main_menu->render();
    $variables['page']['asu_main_menu'] = $main_menu['content'];
  }
  // Front page customization
  if ($variables['is_front'] && !(module_exists('vsite') && vsite_get_vsite())) {
    $variables['theme_hook_suggestions'][] = 'page__designerfront';
    // Add CSS for front page
    $options = array(
      'type' => 'file',
      'group' => 'CSS_THEME',
      'every_page' => FALSE,
      'preprocess' => FALSE,
    );
    drupal_add_css(path_to_theme() . '/css/elpuente.front.css', $options);
  }
  // Add Breadcrumb
  if (isset($variables['breadcrumb'])) {
    $variables['breadcrumb'] = _elpuente_fix_breadcrumbs($variables['breadcrumb']);
  }
  // Default Open Scholar title
  $variables['page']['default_title'] = '<div class="asu-global--inner--padding header__sitename">' .
    '<span><a class="active" href="/">Open Scholar</a></span>' .
    '</div>';
}

/**
 * Breadcrumb Fix for custom, front page tpl:
 * Accepts the breadcrumb string. Removes all caps and capitalizes first letter in keeping with ASU Web Standards
 */
function _elpuente_fix_breadcrumbs($crumbs) {

  $dom = new domDocument;
  $dom->loadHTML($crumbs, LIBXML_HTML_NOIMPLIED | LIBXML_HTML_NODEFDTD);
  $content = $dom->getElementsByTagname('a');
  foreach ($content as $item) {
    $matches = [];
    $item->nodeValue = ucfirst(strtolower($item->nodeValue));
    preg_match('#([A-Za-z]{3})\ ([0-9]{3})+#', $item->nodeValue, $matches);
    if(isset($matches[0]) && !empty($matches[0])){
      $item->nodeValue = strtoupper($matches[0]);
    }
  }
  $spans = $dom->getElementsByTagname('span');
  $slen = $spans->length;
  $spans->item(--$slen)->nodeValue = '';
  return $dom->saveHTML();
}

/**
 * Checks the vsite's primary menu for the existence of a Home button
 */
function elpuente_check_for_home(){
  $menu_list = vsite_menu_os_menu_tree('primary-menu');

  if(isset($menu_list)){
    reset($menu_list);
    $arrkey = key($menu_list);

    if(isset($menu_list[$arrkey]['link']['title']) && strtolower($menu_list[$arrkey]['link']['title']) != "home") {
      $found = false;
      foreach($menu_list as $item){
        if(isset($item['link']['title']) && strtolower($item['link']['title']) == 'home') {
          $found = true;
        }
      }

      if($found == true){
        drupal_set_message('Web Standards warning. The Home button must be at the beginning of your site menu.', 'warning');
        watchdog('Web Standards', 'The Home button must be first in the primary menu.');
      } else {
        elpuente_inject_home();
        watchdog('Web Standards', 'Generating a home button for the primary menu');
      }

    }
  } else {
    watchdog('elpuente', 'The Primary Menu is missing from the site.');
  }
}

/**
 * Injects a Home button into the primary menu of the vsite
 */
function elpuente_inject_home() {
  $path = drupal_get_normal_path('<front>');
  $menu_item = array(
    'link_path' => $path,
    'link_title' => 'Home',
    'menu_name' => 'primary-menu',
    'weight' => '-10',
    'language' => 'en',
  );
  vsite_menu_menu_link_save($menu_item);
}
