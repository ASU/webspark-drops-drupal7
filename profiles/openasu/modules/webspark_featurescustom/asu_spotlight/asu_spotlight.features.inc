<?php
/**
 * @file
 * asu_spotlight.features.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function asu_spotlight_image_default_styles() {
  $styles = array();

  // Exported image style: asu_spotlight_image.
  $styles['asu_spotlight_image'] = array(
    'name' => 'asu_spotlight_image',
    'label' => 'asu_spotlight_image',
    'effects' => array(),
  );

  return $styles;
}
