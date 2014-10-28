<?php
/**
 * @file
 * webspark_extras.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function webspark_extras_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_view_modes';
  $strongarm->value = array(
    'file' => array(
      'responsive_image' => array(
        'label' => 'Responsive image',
        'custom settings' => 1,
      ),
    ),
  );
  $export['entity_view_modes'] = $strongarm;

  return $export;
}
