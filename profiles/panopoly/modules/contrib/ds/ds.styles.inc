<?php

/**
 * @file
 * Administrative functions for managing styles.
 */

/**
 * Menu callback, show styles form.
 */
function ds_styles_form($form, $form_state) {
  $form = array();

  $form['ds_styles_regions'] = array(
    '#type' => 'textarea',
    '#title' => t('Styles for regions'),
    '#default_value' => variable_get('ds_styles_regions', ''),
    '#description' => t('Configure styles which you can add to regions on the "manage display" screens. Add multiple styles line per line.<br />If you want to have a friendly name, separate class and friendly name by |, but this is not required. eg:<br /><em>class_name_1<br />class_name_2|Friendly name<br />class_name_3</em>')
  );

  return system_settings_form($form);
}