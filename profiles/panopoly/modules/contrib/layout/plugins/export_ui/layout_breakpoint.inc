<?php

/**
 * @file
 * Export / edit UI plugin for breakpoints.
 */

$plugin = array(
  'schema' => 'layout_breakpoint',
  'access' => 'administer layouts',

  // Define the menu item.
  'menu' => array(
    // This menu item is modified in layout_menu_alter() to be a local task
    // under the regular panels layout UI.
    'menu prefix' => 'admin/structure/panels/layouts',
    'menu item' => 'breakpoints',
    'menu title' => 'Breakpoints',
  ),

  // Define user interface texts.
  'title singular' => t('breakpoint'),
  'title singular proper' => t('Breakpoint'),
  'title plural' => t('breakpoints'),
  'title plural proper' => t('Breakpoints'),

  'form' => array(
    'settings' => 'layout_breakpoint_edit_form',
    'validate' => 'layout_breakpoint_edit_form_validate',
  ),
);

/**
 * Breakpoint item settings form.
 *
 * @see layout_breakpoint_edit_form_validate().
 */
function layout_breakpoint_edit_form(&$form, $form_state) {
  $breakpoint = $form_state['item'];

  // Common form elements are already provided by ctools for admin_title
  // (human readable label) and name (machine name).

  $form['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Breakpoint'),
    // http://blog.cloudfour.com/the-ems-have-it-proportional-media-queries-ftw/
    // has some great points for em based responsive layouts, we allow for pixel
    // and em based layouts so long as the same unit is used. We do not explicitly
    // deny separate units, but our orderings assumes the same unit is used.
    '#description' => t('Width point where this breakpoint is applied. Examples: 960px, 41em. Do not mix pixel and em based widths.'),
    '#default_value' => @$breakpoint->width,
  );
  $form['grid_name'] = array(
    '#type' => 'select',
    '#options' => layout_breakpoint_grid_name_list(),
    '#default_value' => @$breakpoint->grid_name,
    '#description' => t('Grid to be applied to this breakpoint. <a href="@editgrids">You can edit and add grids</a>.', array('@editgrids' => url('admin/structure/panels/layouts/grids'))),
  );
}

/**
 * Validation for breakpoint item settings form.
 *
 * @see layout_breakpoint_edit_form().
 */
function layout_breakpoint_edit_form_validate(&$form, $form_state) {
  if (!preg_match('!^\d+(px|em)$!', $form_state['values']['width'])) {
    form_set_error('width', t('Only pixel or em based breakpoints are supported, for example 960px or 41em.'));
  }
}

/**
 * Produce a list of grid/name pairs for form selection.
 */
function layout_breakpoint_grid_name_list() {
  $grids = gridbuilder_load_all();
  $grid_list = array();
  foreach ($grids as $grid) {
    $grid_list[$grid->name] = $grid->admin_title;
  }
  return $grid_list;
}
