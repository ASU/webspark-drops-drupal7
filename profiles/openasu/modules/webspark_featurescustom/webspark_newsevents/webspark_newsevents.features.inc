<?php
/**
 * @file
 * webspark_newsevents.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function webspark_newsevents_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function webspark_newsevents_views_api($module = NULL, $api = NULL) {
		  //return array("api" => "3.0");
		  return array("api" => "3.0", 'template path' => drupal_get_path('module', 'webspark_newsevents') .'/templates');  // To include Views template files - Chizuko  
}

/**
 * Implements hook_image_default_styles().
 */
function webspark_newsevents_image_default_styles() {
  $styles = array();

  // Exported image style: asuevent_image_style.
  $styles['asuevent_image_style'] = array(
    'name' => 'asuevent_image_style',
    'label' => 'asuevent_image_style',
    'effects' => array(
      4 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 745,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: asunews_image_style.
  $styles['asunews_image_style'] = array(
    'name' => 'asunews_image_style',
    'label' => 'asunews_image_style',
    'effects' => array(
      6 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 745,
          'height' => 414,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: asunews_thumbnail.
  $styles['asunews_thumbnail'] = array(
    'name' => 'asunews_thumbnail',
    'label' => 'asunews_thumbnail',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 360,
          'height' => 200,
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
function webspark_newsevents_node_info() {
  $items = array(
    'asu_event' => array(
      'name' => t('ASU Event'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'asu_news' => array(
      'name' => t('ASU News'),
      'base' => 'node_content',
      'description' => t('Receiving content type for ASU News feed'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
