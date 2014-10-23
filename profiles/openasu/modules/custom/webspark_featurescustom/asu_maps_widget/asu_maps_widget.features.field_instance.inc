<?php
/**
 * @file
 * asu_maps_widget.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function asu_maps_widget_field_default_field_instances() {
  $field_instances = array();


  // Exported field_instance: 'fieldable_panels_pane-asu_maps-field_map_address'
  $field_instances['fieldable_panels_pane-asu_maps_widget-field_asu_maps_address'] = array(
    'bundle' => 'asu_maps_widget',
    //'bundle' => 'panopoly_widgets',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The street address of the location you wish to map. This widget will contact Google and try to do its best to create a map!',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'asu_maps_widget',
        'settings' => array(
          'iframe_height' => 400,
          'iframe_width' => 600,
          'include_link' => 0,
          'include_map' => 1,
          'include_static_map' => 0,
          'include_text' => 0,
          'information_bubble' => 0,
          'langcode' => 'en',
          'link_text' => 'View larger map',
          'map_type' => 'm',
          'zoom_level' => 14,
        ),
        'type' => 'asu_maps',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_asu_maps_address',
    'label' => 'Address',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => -4,
    ),
  );

$field_instances['fieldable_panels_pane-asu_maps_widget-field_asu_maps_information'] = array(
    'bundle' => 'asu_maps_widget',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_asu_maps_information',
    'label' => 'Information',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 3,
      ),
      'type' => 'text_textarea',
      'weight' => -3,
    ),
  );

  return $field_instances;
}
