<?php
/**
 * @file
 * uto_carousel.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function uto_carousel_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function uto_carousel_image_default_styles() {
  $styles = array();

  // Exported image style: uto_carousel_thumbnail.
  $styles['uto_carousel_thumbnail'] = array(
    'name' => 'uto_carousel_thumbnail',
    'label' => 'UTO Carousel Thumbnail',
    'effects' => array(
      8 => array(
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
          'height' => 300,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
