<?php
/**
 * @file
 *    theme registry and preprocess functions for the default templates
 */

/**
 * Implements hook_theme().
 */
function google_appliance_theme() {

  $registry = array();
  $gsa_template_dir = drupal_get_path('module', 'asu_gsa') . '/theme';
  unset($theme_registry['google_appliance_results']);
  // Full search form on results pages.
  $registry['asu_gsa_results'] = array(
    'render element' => 'form',
    'template' => 'asu-gsa-search-results',
    'path' => $gsa_template_dir,
  );

}
