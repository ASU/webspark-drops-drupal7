<?php

/**
 * Implements hook_form_FORM_ID_alter().
 */
function webspark_featurescustom_form_system_site_information_settings_alter(&$form, &$form_state, $form_id) {
  $suffix = _webspark_featurescustom_get_ws2_suffix();
  // Adds fields to /admin/config/system/site-information
  $form['site_information']['asu_brand'] = array(
    '#title' => 'Parent/Unit settings',
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => -3,
  );
  $form['site_information']['asu_brand']['explanation'] = array(
    '#markup' => t('Go to the '
      . l('ASU Brand block settings',
          '/admin/structure/block/manage/asu_brand/asu_brand_header' . $suffix . '/configure'))
      . ' form to do either of the following:'
      . "<ul><li>Add a parent/unit org title (and URL)</li>"
      . "<li>Override the main site title's URL</li></ul>",
  );
  $form['site_information']['site_name']['#weight'] = -4;
}
