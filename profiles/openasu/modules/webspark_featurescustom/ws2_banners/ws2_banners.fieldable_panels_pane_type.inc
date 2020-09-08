<?php

/**
 * @file
 * ws2_banners.fieldable_panels_pane_type.inc
 */

/**
 * Implements hook_default_fieldable_panels_pane_type().
 */
function ws2_banners_default_fieldable_panels_pane_type() {
  $export = array();

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'banners_ws2';
  $fieldable_panels_pane_type->title = 'WS2L Banner';
  $fieldable_panels_pane_type->description = '';
  $export['banners_ws2'] = $fieldable_panels_pane_type;

  return $export;
}
