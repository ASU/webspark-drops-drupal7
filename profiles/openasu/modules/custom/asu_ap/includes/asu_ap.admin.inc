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
  $form['#submit'][] = 'asu_ap_admin_settings_submit';
  return system_settings_form($form);
}

/**
 * Implements hook_form_submit()
 * @noinspection PhpUnusedParameterInspection
 */
function asu_ap_admin_settings_submit($form, $form_state) {
  variable_set('asu_ap_ds_marketing_video', $form_state['values']['video_handling']);
}
