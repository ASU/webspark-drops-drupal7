<?php
/**
 * @file
 * asu_degrees_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_degrees_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function asu_degrees_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function asu_degrees_feature_image_default_styles() {
  $styles = array();

  // Exported image style: asu_degree_image.
  $styles['asu_degree_image'] = array(
    'label' => 'ASU Degree Image',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 261,
          'height' => 187,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function asu_degrees_feature_node_info() {
  $items = array(
    'asu_degree' => array(
      'name' => t('ASU Degree'),
      'base' => 'node_content',
      'description' => t('ASU Degrees Feed will create ASU Degree nodes.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'asu_degree_feed' => array(
      'name' => t('ASU Degrees Feed'),
      'base' => 'node_content',
      'description' => t('Creates a new ASU degree feed.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
