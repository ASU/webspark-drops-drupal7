<?php
/**
 * @file
 * webspark_hero.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function webspark_hero_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function webspark_hero_image_default_styles() {
  $styles = array();

  // Exported image style: webspark_hero.
  $styles['webspark_hero'] = array(
    'name' => 'webspark_hero',
    'label' => 'Webspark hero large',
    'effects' => array(
      3 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 380,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
