<?php
/**
 * @file
 * panopoly_widgets.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function asu_spotlight_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'fieldable_panels_pane-spotlight-field_basic_spotlight_items'
  $field_instances['fieldable_panels_pane-asu_spotlight-field_asu_spotlight_items'] = array(
    'bundle' => 'asu_spotlight',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'asu_spotlight',
        'settings' => array(
          'image_style' => 'panopoly_image_spotlight',
        ),
        'type' => 'asu_spotlight_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_asu_spotlight_items',
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
      'module' => 'panopoly_widgets',
      'settings' => array(),
      'type' => 'asu_spotlight_form',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  
  t('Items');
  

  return $field_instances;
}
