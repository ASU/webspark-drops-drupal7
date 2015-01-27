<?php
/**
 * @file
 * uto_carousel.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function uto_carousel_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'fieldable_panels_pane-uto_carousel-field_items'
  $field_instances['fieldable_panels_pane-uto_carousel-field_items'] = array(
    'bundle' => 'uto_carousel',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'uto_carousel',
        'settings' => array(
          'caption' => FALSE,
          'image_style' => 'thumbnail',
          'optionset' => '4_item_carousel',
        ),
        'type' => 'uto_carousel',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_items',
    'label' => 'Items',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'general',
      'file_extensions' => 'jpg jpeg gif png',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'uto_carousel',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'uto_carousel_form',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Items');

  return $field_instances;
}
