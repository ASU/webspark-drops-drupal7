<?php

/**
 * Inplements hook_preprocess_html()
 */

/**
 * Didn't work with preprocess_html, so doing page
 */
function webspark_seven_preprocess_html(&$variables) {
  // WEBSPARK-667 - Add meta tag to identify Innovation as a "Webspark" theme
  // in the DOM
  $meta_webspark_id = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'content' => 'Webspark',
      'http-equiv' => 'X-Name-of-Distro',
    )
  );
  drupal_add_html_head($meta_webspark_id, 'meta_webspark_id');
}

/* Alters label title to prevent panopoly-admin.js
   from removing label text when field is required */
function webspark_seven_form_required_marker($variables) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();
  $attributes = array(
    'class' => 'form-required',
    'title' => $t('This field is required.'),
  );
  return '<span' . drupal_attributes($attributes) . '> * </span>';
}
