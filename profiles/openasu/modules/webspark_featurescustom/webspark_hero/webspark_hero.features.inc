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
    'label' => 'Webspark hero large',
    'effects' => array(
      3 => array(
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
