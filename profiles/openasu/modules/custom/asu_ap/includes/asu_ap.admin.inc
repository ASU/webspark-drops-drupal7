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
    '#title' => 'Degree Search settings',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
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
    '#title' => 'Local content settings',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['local']['views_grid_styling'] = array(
    '#type' => 'checkbox',
    '#title' => 'Apply extra styling to Views grid',
    '#description' => t('Apply extra styling to clean up the Views -> Grid layout'),
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
}
