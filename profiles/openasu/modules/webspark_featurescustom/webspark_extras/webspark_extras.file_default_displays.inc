<?php
/**
 * @file
 * webspark_extras.file_default_displays.inc
 */

/**
 * Implements hook_file_default_displays().
 */
function webspark_extras_file_default_displays() {
  $export = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__responsive_image__file_field_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'panopoly_image_full',
    'image_link' => '',
  );
  $export['image__responsive_image__file_field_image'] = $file_display;

  return $export;
}
