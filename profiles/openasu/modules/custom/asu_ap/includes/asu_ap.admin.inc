<?php /** @noinspection PhpDocSignatureInspection */
/** @noinspection PhpUnused */
/**
 * Admin settings form
 */

/**
 * Callback for AP config settings form
 * @return array
 */
function asu_ap_admin_settings() {
  $form = array();
  $form['ds'] = array(
    '#type' => 'fieldset',
    '#title' => 'Degree Search data',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['ds']['hide_ds_fields'] = array(
    '#type' => 'checkbox',
    '#title' => 'Hide Degree Search fields',
    '#description' => 'Hides the fields that hold Degree Search generated degree information'
      . ' on degree page edit forms. '
      . ' <strong>IMPORTANT</strong>:'
      . ' Disabling this setting and updating the Degree Search field data '
      . ' in this site will be overwritten with the'
      . ' next pull of degree data from Degree Search.'
      . ' Use this feature for debugging local differences from Degree Search ONLY.',
    '#default_value' => variable_get('asu_ap_hide_ds_fields', 1),
  );
  $form['ds']['video_handling'] = array(
    '#type' => 'select',
    '#title' => 'Display Degree Search marketing video',
    '#description' => 'This only affects videos that have been pulled in from the Degree Search feed. It has no bearing on other videos manually added in degree page edit forms in this site.',
    '#options' => array(
      'marketing_top' => 'Displayed',
      'none' => 'Hidden',
    ),
    '#default_value' => variable_get('asu_ap_ds_marketing_video', 'marketing_top'),
  );
  $form['local'] = array(
    '#type' => 'fieldset',
    '#title' => 'Local degree content',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['local']['views_grid_styling'] = array(
    '#type' => 'checkbox',
    '#title' => 'Apply extra Views grid styling',
    '#description' => t('Apply views_grid.css file in ASU AP folder to clean up the degrees listing view\'s Grid layout'),
    '#default_value' => variable_get('asu_ap_views_grid_styling', 1),
    '#return_value' => 1,
  );
  $form['#submit'][] = 'asu_ap_admin_settings_submit';
  return system_settings_form($form);
}

/**
 * Implements hook_form_submit()
 * @noinspection PhpUnusedParameterInspection
 */
function asu_ap_admin_settings_submit($form, $form_state) {
  variable_set('asu_ap_ds_marketing_video', $form_state['values']['video_handling']);
  variable_set('asu_ap_views_grid_styling', $form_state['values']['views_grid_styling']);
  variable_set('asu_ap_hide_ds_fields', $form_state['values']['hide_ds_fields']);
}
