<?php

/**
 * Inplements hook_preprocess_html()
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

/**
 * Override of theme_fieldset().
 *
 * Added odd/even classes for more fieldset theming options.
 */
function webspark_seven_fieldset($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));

  $no_of_parents = (isset($element['#parents'])) ? count($element['#parents']) - 1 : 0;
  $additional_class = ($no_of_parents % 2 == 0) ? 'fieldset-nested-even' : 'fieldset-nested-odd';
  _form_set_class($element, array('form-wrapper', $additional_class));

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    // Always wrap fieldset legends in a SPAN for CSS positioning.
    $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';
  }
  $output .= '<div class="fieldset-wrapper">';
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= '</div>';
  $output .= "</fieldset>\n";
  return $output;
}
