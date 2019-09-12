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

  $form['asu_mega_footer'] = array(
    '#type' => 'fieldset',
    '#title' => t('ASU Mega Footer'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 10,
  );
  $form['asu_mega_footer']['social_media_exit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Open social media pages in new window'),
    '#default_value' => theme_get_setting('social_media_exit'),
    '#description' => t("If checked, social media links in the ASU Mega Footer will open in a new window or tab."),
  );

  // Removed old Webspark theme settings;
  // Leaving in submt callback to clear caches for ASU Brand module
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
