<?php
/**
 * @file
 * asu_ap_feature.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function asu_ap_feature_defaultconfig_features() {
  return array(
    'asu_ap_feature' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function asu_ap_feature_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_minimum_multiple';
  $strongarm->value = '25';
  $export['chosen_minimum_multiple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_minimum_single';
  $strongarm->value = '25';
  $export['chosen_minimum_single'] = $strongarm;

  return $export;
}
