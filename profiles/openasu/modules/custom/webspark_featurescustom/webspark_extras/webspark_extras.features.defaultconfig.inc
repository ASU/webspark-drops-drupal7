<?php
/**
 * @file
 * webspark_extras.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function webspark_extras_defaultconfig_features() {
  return array(
    'webspark_extras' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function webspark_extras_defaultconfig_strongarm() {
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
