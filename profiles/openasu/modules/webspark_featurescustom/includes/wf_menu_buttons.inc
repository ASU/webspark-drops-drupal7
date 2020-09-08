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
    if (_webspark_featurescustom_get_ws2_suffix(TRUE) === "_ws2") { // WS2.0
      $options = array(
        0 => '-- None --',
        1 => 'Maroon',
        4 => 'Black',
      );
      $desc_text = '';
    } else { // Innovation, etc.
      $options = array(
        0 => '-- None --',
        1 => 'Primary (Maroon)',
        2 => 'Alternate (Gray)',
        3 => 'Request Info (Gold) - restricted',
      );
      $desc_text = "\n<br>" . "Gold styling may only be used for 'Request Info' buttons that point to an ASU degree page.";
    }

    $form['asu_themed_button'] = array(
      '#type' => 'select',
      '#title' => t('Style as ASU Web standards button in secondary menu?'),
      '#options' => $options,
      '#default_value' => $asu_button_style,
      '#description' => 'If an option is selected, the link will appear as an ASU Web standards button (vs. a link)'
        . ' in the secondary menu.' . $desc_text
        . "\n<br><b>IMPORTANT:</b>" . ' Styling of buttons in the primary menu is handled in the '
        . "<a href='/admin/structure/tb-megamenu'>TB Megamenu UI</a>. ",
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
