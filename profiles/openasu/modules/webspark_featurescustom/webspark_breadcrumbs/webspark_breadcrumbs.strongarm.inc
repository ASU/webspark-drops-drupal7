<?php
/**
 * @file
 * webspark_breadcrumbs.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function webspark_breadcrumbs_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_default';
  $strongarm->value = array(
    'entity_field' => 'entity_field',
    'entity_field_extra' => 'entity_field_extra',
    'entity_view' => 'entity_view',
    'fieldable_panels_pane' => 'fieldable_panels_pane',
    'menu_tree' => 'menu_tree',
    'views_panes' => 'views_panes',
    'other' => 'other',
    'token' => 'token',
    'entity_form_field' => 'entity_form_field',
    'custom' => 'custom',
    'block' => 'block',
  );
  $export['panels_page_default'] = $strongarm;

  return $export;
}
