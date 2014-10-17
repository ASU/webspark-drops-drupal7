<?php

/**
 * @file
 * Theme setting callbacks for innovation subtheme.
 *
 * TODO - Footer controls?
 *
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function innovation_form_system_theme_settings_alter(&$form, &$form_state) {
  // Removed old Webspark theme settings;
  // Leaving in submt callback to clear caches for ASU Brand module
  // TODO - Remove costumization from install profile
  // TODO - Set header to default white header in this value
    // variable_set('asu_brand_header_selector', $form_state['values']['asu_brand_header_selector']);
  $form['#submit'][] = 'innovation_settings_submit';
  //$form['#validate'][] = 'innovation_settings_validate';
}

function innovation_settings_submit($form, &$form_state) {
  // Turning this all off - Webstandards header
  // ASU header needs a cache_clear
  if (module_exists('asu_brand')) {
    asu_brand_cache_clear();
  }
}

/* Removed validation */
