<?php

/**
 * @file
 * asu_ap_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_ap_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function asu_ap_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function asu_ap_feature_image_default_styles() {
  $styles = array();

  // Exported image style: asu_ap_image.
  $styles['asu_ap_image'] = array(
    'label' => 'ASU Academic Programs Image',
    'effects' => array(
      1 => array(
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
function asu_ap_feature_node_info() {
  $items = array(
    'asu_ap' => array(
      'name' => t('ASU Academic Programs'),
      'base' => 'node_content',
      'description' => t('ASU Academic Programs Feed nodes create these pre-populated degree pages. These pages should not be created manually.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'asu_ap_feed' => array(
      'name' => t('ASU Academic Programs Feed'),
      'base' => 'node_content',
      'description' => t('Creates a new ASU Academic Programs feed.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
