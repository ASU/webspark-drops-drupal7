<?php
/**
 * @file
 * asu_maps_enhanced.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function asu_maps_enhanced_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'fieldable_panels_pane-asu_maps_enhanced-field_asu_maps_enhanced_items'
  $field_instances['fieldable_panels_pane-asu_maps_enhanced-field_asu_maps_enhanced_items'] = array(
    'bundle' => 'asu_maps_enhanced',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'asu_maps_enhanced',
        'settings' => array(),
        'type' => 'asu_maps_enhanced',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_asu_maps_enhanced_items',
    'label' => 'ASU Enhanced Map Items',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'asu_maps_enhanced',
      'settings' => array(),
      'type' => 'asu_maps_enhanced_form',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('ASU Enhanced Map Items');

  return $field_instances;
}
