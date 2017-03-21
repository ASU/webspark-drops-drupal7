<?php
/**
 * @file
 * asu_isearch.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_isearch_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function asu_isearch_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function asu_isearch_image_default_styles() {
  $styles = array();

  // Exported image style: asu_isearch_profile.
  $styles['asu_isearch_profile'] = array(
    'label' => 'asu_isearch_profile',
    'effects' => array(),
  );

  // Exported image style: asu_isearch_profile_list.
  $styles['asu_isearch_profile_list'] = array(
    'label' => 'asu_isearch_profile_list',
    'effects' => array(),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function asu_isearch_node_info() {
  $items = array(
    'asu_isearch_profile' => array(
      'name' => t('iSearch Profile'),
      'base' => 'node_content',
      'description' => t('This holds iSearch profile information for ASU staff, faculty, and students.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
