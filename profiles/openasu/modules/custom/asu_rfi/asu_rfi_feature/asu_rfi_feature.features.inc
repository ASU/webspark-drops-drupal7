<?php
/**
 * @file
 * asu_rfi_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_rfi_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function asu_rfi_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function asu_rfi_feature_node_info() {
  $items = array(
    'asu_rfi' => array(
      'name' => t('ASU RFI form submissions'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
