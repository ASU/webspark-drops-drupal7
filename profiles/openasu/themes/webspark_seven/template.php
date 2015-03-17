<?php

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
