<?php
/**
 * @file
 * asu_directory.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_directory_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "quicktabs" && $api == "quicktabs") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function asu_directory_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function asu_directory_image_default_styles() {
  $styles = array();

  // Exported image style: asu_directory_profile.
  $styles['asu_directory_profile'] = array(
    'name' => 'asu_directory_profile',
    'label' => 'ASU Directory Profile',
    'effects' => array(
      2 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_resize',
        'data' => array(
          'width' => 191,
          'height' => 191,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: asu_directory_table_profile.
  $styles['asu_directory_table_profile'] = array(
    'name' => 'asu_directory_table_profile',
    'label' => 'ASU Directory Table Profile',
    'effects' => array(
      1 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_resize',
        'data' => array(
          'width' => 116,
          'height' => 116,
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
function asu_directory_node_info() {
  $items = array(
    'asu_directory_feed' => array(
      'name' => t('ASU Directory Feed'),
      'base' => 'node_content',
      'description' => t('Creates a new ASU Directory Feed.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'asu_directory_person' => array(
      'name' => t('ASU Directory Person'),
      'base' => 'node_content',
      'description' => t('ASU Directory feed will create ASU Directory Person nodes.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
