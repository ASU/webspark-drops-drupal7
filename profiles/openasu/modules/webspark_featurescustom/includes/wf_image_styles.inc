<?php

/**
 * @file - Adds image styling that was removed from asu_cas module.
 */

/**
 * Implements hook_init()
 */
function webspark_featurescustom_init() {
  // Adding the asu images css file to the theme so it will show up in the WYSIWYG
  drupal_add_css(drupal_get_path('module', 'webspark_featurescustom') . '/includes/css/wf_image_styles.css', array('group' => CSS_THEME, 'type' => 'file'));
}

/**
 * Implements hook_image_default_styles().
 */
function webspark_featurescustom_image_default_styles() {
  $styles = array();

  // Exported image style: asu_header_image.
  $styles['asu_header_image'] = array(
    'name' => 'asu_header_image',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 1000,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
