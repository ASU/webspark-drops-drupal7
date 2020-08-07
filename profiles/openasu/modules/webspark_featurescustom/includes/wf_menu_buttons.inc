<?php /** @noinspection PhpDocSignatureInspection */
/**
 * @file - Customizes/overrides LH menu item styling for links to be styled as buttons
 */

/**
 * Implements hook_form_alter().
 */
function webspark_featurescustom_form_alter(&$form, &$form_state, &$form_id) {
  $asu_button_style = (isset($form['options']['#value']['attributes']['asu_themed_button']))
    ? $form['options']['#value']['attributes']['asu_themed_button']
    : 0;
  if ($form_id === 'menu_edit_item') {
    $options = array(
      0 => '-- None --',
      1 => 'Primary (Maroon)',
      2 => 'Alternate (Gray)',
      3 => 'Request Info (Gold) - restricted',
    );
    $form['asu_themed_button'] = array(
      '#type' => 'select',
      '#title' => t('Style as ASU Web standards button?'),
      '#options' => $options,
      '#default_value' => $asu_button_style,
      '#description' => 'If an option is selected, the link will appear as an ASU Web standards button. NOTE: Per 
      ASU Web standards, gold styling may only be used for "Request Info" buttons that point to an ASU degree page.',
      '#weight' => 1,
    );
    $init_submit = $form['#submit'];
    $form['#submit'] = array();
    $form['#submit'][] = '_webspark_featurescustom_button_theming';
    foreach($init_submit as $key => $value) {
      $form['#submit'][] = $value;
    }
  }
}

/**
 * Menu link edit form submit callback
 * Save asu_themed_button setting in $options array for theming
 * @param $form
 * @param $form_state
 */
function _webspark_featurescustom_button_theming($form, &$form_state) {
  $asu = (isset($form_state['values']['asu_themed_button']))
    ? $form_state['values']['asu_themed_button']
    : 0;
  $form_state['values']['options']['attributes']['asu_themed_button'] = $asu;
}
