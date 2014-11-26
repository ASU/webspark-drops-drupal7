<?php
/**
 * @file
 * asu_eadvisor_degree_feed_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_eadvisor_degree_feed_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function asu_eadvisor_degree_feed_feature_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function asu_eadvisor_degree_feed_feature_node_info() {
  $items = array(
    'asu_eadvisor_degree' => array(
      'name' => t('ASU eAdvisor Degree'),
      'base' => 'node_content',
      'description' => t('ASU eAdvisor Degree Feed will create ASU eAdvisor Degree nodes.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'asu_eadvisor_degree_feed' => array(
      'name' => t('ASU eAdvisor Degree Feed'),
      'base' => 'node_content',
      'description' => t('Creates a new ASU eAdvisor degree feed'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
