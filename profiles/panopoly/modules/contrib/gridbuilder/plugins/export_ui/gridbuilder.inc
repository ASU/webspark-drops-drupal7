<?php

/**
 * @file
 * Export / edit UI plugin for grids.
 */

$plugin = array(
  'schema' => 'gridbuilder',
  'access' => 'administer gridbuilder',

  // Define the menu item.
  'menu' => array(
    // This menu item is modified in layout_menu_alter() to be a local task
    // under the regular panels layout UI.
    'menu prefix' => 'admin/structure/panels/layouts',
    'menu item' => 'grids',
    'menu title' => 'Grids',
  ),

  // Define user interface texts.
  'title singular' => t('grid'),
  'title singular proper' => t('Grid'),
  'title plural' => t('grids'),
  'title plural proper' => t('Grids'),

  'form' => array(
    'settings' => 'gridbuilder_grid_edit_form',
    'validate' => 'gridbuilder_grid_edit_form_validate',
  ),
);

/**
 * Grid item settings form.
 *
 * @see gridbuilder_grid_edit_form_validate().
 */
function gridbuilder_grid_edit_form(&$form, $form_state) {
  $grid = $form_state['item'];

  // Common form elements are already provided by ctools for admin_title
  // (human readable label) and name (machine name).

  if (empty($grid->width)) {
    // Set some defaults for the user if this is a new grid.
    $grid->grid_type = GRIDBUILDER_FLUID;
    $grid->width = 100;
    $grid->columns = 12;
    $grid->padding_width = 1.5;
    $grid->gutter_width = 2;
  }

  // Master grid configuration.
  $form['grid_type'] = array(
    '#type' => 'radios',
    '#title' => t('Type of grid'),
    '#options' => array(GRIDBUILDER_FLUID => t('Fluid'), GRIDBUILDER_FIXED => t('Fixed to specific width')),
    '#default_value' => $grid->grid_type,
  );
  $form['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Grid width'),
    '#description' => t('Only meaningful if using a fixed grid. Enter a pixel size (eg. 960).'),
    '#default_value' => $grid->width,
    '#states' => array(
      'visible' => array('input[name="grid_type"]' => array('value' => GRIDBUILDER_FIXED)),
    ),
    '#field_suffix' => $grid->grid_type == GRIDBUILDER_FIXED ? 'px' : '%',
  );

  // Grid detail configuration.
  $form['columns'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of grid columns'),
    '#default_value' => $grid->columns,
  );
  $form['padding_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Column padding'),
    '#description' => t('Column padding in pixels (for fixed grids, eg. 10) or percentages (for fluid grids, eg. 1.5). Enter 0 for no padding.'),
    '#default_value' => $grid->padding_width,
    '#field_suffix' => $grid->grid_type == GRIDBUILDER_FIXED ? 'px' : '%',
  );

  $form['gutter_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Gutter width'),
    '#description' => t('Gutter width in pixels (for fixed grids, eg. 20) or percentages (for fluid grids, eg. 2). Enter 0 for no gutter.'),
    '#default_value' => $grid->gutter_width,
    '#field_suffix' => $grid->grid_type == GRIDBUILDER_FIXED ? 'px' : '%',
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'gridbuilder') . '/gridbuilder-admin.css';
  $form['#attached']['js'][] = drupal_get_path('module', 'gridbuilder') . '/gridbuilder-admin.js';
}

/**
 * Validation for grid item settings form.
 *
 * @see gridbuilder_grid_edit_form().
 */
function gridbuilder_grid_edit_form_validate(&$form, $form_state) {
  // Force width to 100 if fluid width. That is in percentages.
  if ($form_state['values']['grid_type'] == GRIDBUILDER_FLUID) {
    $form_state['values']['width'] = 100;
  }

  if ((intval($form_state['values']['width']) != $form_state['values']['width']) || $form_state['values']['width'] == 0) {
    // Width should be a positive integer.
    form_set_error('columns', t('The width should be a positive number.'));
  }
  if ((intval($form_state['values']['columns']) != $form_state['values']['columns']) || $form_state['values']['columns'] == 0) {
    // Columns should be a positive integer.
    form_set_error('columns', t('The number of columns should be a positive number.'));
  }
  if (!is_numeric($form_state['values']['padding_width'])) {
    // Padding can be float as well (eg. 1.5 for 1.5% for fluid grids).
    form_set_error('padding_width', t('The column padding should be a number. Enter 0 (zero) for no padding.' . $form_state['values']['padding_width']));
  }
  if (!is_numeric($form_state['values']['gutter_width'])) {
    // Gutter can be float too (eg. 1.5 for 1.5% for fluid grids).
    form_set_error('gutter_width', t('The gutter width should be a number. Enter 0 (zero) for no gutter.'));
  }
}
