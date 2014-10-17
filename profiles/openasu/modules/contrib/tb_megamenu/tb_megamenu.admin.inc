<?php

include_once drupal_get_path('module', 'tb_megamenu') . '/tb_megamenu.functions.inc';

function tb_megamenu_admin_settings($form) {
  $menus = tb_megamenu_get_megamenus();
  foreach ($menus as $menu) {
    $form[$menu->menu_name]['#tb_megamenu'] = $menu;
    $form[$menu->menu_name]['menu_name'] = array('#markup' => $menu->menu_name);
    $form[$menu->menu_name]['title'] = array('#markup' => $menu->title);
    $form[$menu->menu_name]['config_megamenu'] = array('#type' => 'link', '#title' => t('Config'), '#href' => "admin/structure/tb-megamenu/$menu->menu_name");
    $form[$menu->menu_name]['config_links'] = array('#type' => 'link', '#title' => t('Edit links'), '#href' => "admin/structure/menu/manage/$menu->menu_name");
  }
  return $form;
}

function theme_tb_megamenu_admin_settings($variables) {
  $form = $variables['form'];
  $rows = array();
  foreach (element_children($form) as $key) {
    if (isset($form[$key]['#tb_megamenu'])) {
      $menu = &$form[$key];
      $menu['enabled']['#parents'] = array($key, 'enabled');
      $menu['enabled']['#name'] = $key . "[enabled]";
      $row = array();
      $row[] = drupal_render($menu['menu_name']);
      $row[] = drupal_render($menu['title']);
      $row[] = drupal_render($menu['config_megamenu']);
      $row[] = drupal_render($menu['config_links']);
      $rows[] = $row;
    }
  }
  $header = array(t('Menu Name'), t('Menu Title'));
  $header[] = array('data' => t('Operations'), 'colspan' => 2);
  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No MegaMenu block available. <a href="@link">Add MegaMenu Block</a>.', array('@link' => url('admin/config/user-interface/tb_megamenu/add'))), 'attributes' => array('id' => 'tb_megamenu'))) . drupal_render_children($form);
}

function tb_megamenu_configure_form($form, &$form_state, $menu_names = array()) {
  if(module_exists('fontawesome') && file_exists(libraries_get_path('fontawesome') . '/css/font-awesome.css')) {
    tb_megamenu_add_css(libraries_get_path('fontawesome') . '/css/font-awesome.css');
  }
  
  if(module_exists('chosen') && file_exists(libraries_get_path('chosen') . '/chosen/chosen.css')) {
    tb_megamenu_add_css(libraries_get_path('chosen') . '/chosen/chosen.css');
  }
  else {
    tb_megamenu_add_css(drupal_get_path('module', 'tb_megamenu') . '/css/chosen/chosen.css');
  }
  tb_megamenu_add_css(drupal_get_path('module', 'tb_megamenu') . '/css/bootstrap.css');
  tb_megamenu_add_css(drupal_get_path('module', 'tb_megamenu') . '/css/base.css');
  tb_megamenu_add_css(drupal_get_path('module', 'tb_megamenu') . '/css/admin.css');
  tb_megamenu_add_css(drupal_get_path('module', 'tb_megamenu') . '/css/backend.css');
  if(module_exists('chosen') && file_exists(libraries_get_path('chosen') . '/chosen/chosen.jquery.js')) {
    drupal_add_js(libraries_get_path('chosen') . '/chosen/chosen.jquery.js');
  }
  else {
    drupal_add_js(drupal_get_path('module', 'tb_megamenu') . '/js/chosen.jquery.js');
  }  
  drupal_add_js('
    (function ($) {
      Drupal.TBMegaMenu = Drupal.TBMegaMenu || {};
      Drupal.TBMegaMenu.ajax_link = "' . (variable_get('clean_url', 0) ? '' : '?q=') . '";
    })(jQuery);
  ', 'inline');    
  
  drupal_add_js(drupal_get_path('module', 'tb_megamenu') . '/js/tb-megamenu-backend.js');
  drupal_add_js(drupal_get_path('module', 'tb_megamenu') . '/js/tb-megamenu-object.js');
  if(!empty($menu_names)) {
    $form['tb_megamenu'] = array(
      '#markup' => theme('tb_megamenu_backend', array(
        'menu_name' => $menu_names[0],
      )),
    );
  }
  return $form;
}
