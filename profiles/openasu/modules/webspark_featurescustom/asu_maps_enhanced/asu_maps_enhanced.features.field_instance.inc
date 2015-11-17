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

  // Exported field_instance: 'fieldable_panels_pane-asu_maps_enhanced-field_map_action_link'
  $field_instances['fieldable_panels_pane-asu_maps_enhanced-field_map_action_link'] = array(
        'bundle' => 'asu_maps_enhanced',
        'default_value' => array(
          0 => array(
            'title' => 'plan a visit ',
            'url' => 'http://visit.asu.edu',
          ),
        ),
        'deleted' => 0,
        'description' => '',
        'display' => array(
          'default' => array(
            'label' => 'hidden',
            'settings' => array(),
            'type' => 'hidden',
            'weight' => 2,
          ),
        ),
        'entity_type' => 'fieldable_panels_pane',
        'field_name' => 'field_map_action_link',
        'label' => 'Map Action Link',
        'required' => 0,
        'settings' => array(
          'attributes' => array(
            'class' => '',
            'configurable_title' => 0,
            'rel' => '',
            'target' => 'default',
            'title' => '',
          ),
          'display' => array(
            'url_cutoff' => 80,
          ),
          'enable_tokens' => 1,
          'linkit' => array(
            'button_text' => 'Search',
            'enable' => 0,
            'profile' => '',
          ),
          'rel_remove' => 'default',
          'title' => 'required',
          'title_maxlength' => 128,
          'title_value' => '',
          'url' => 0,
          'user_register_form' => FALSE,
          'validate_url' => 1,
        ),
        'widget' => array(
          'active' => 0,
          'module' => 'link',
          'settings' => array(
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
          ),
          'type' => 'link_field',
          'weight' => -5,
          ),
      );

      // Exported field_instance: 'fieldable_panels_pane-asu_maps_enhanced-field_map_info'
      $field_instances['fieldable_panels_pane-asu_maps_enhanced-field_map_info'] = array(
          'bundle' => 'asu_maps_enhanced',
          'default_value' => NULL,
          'deleted' => 0,
          'description' => '',
          'display' => array(
              'default' => array(
                  'label' => 'hidden',
                  'settings' => array(),
                  'type' => 'hidden',
                  'weight' => 1,
              ),
          ),
          'entity_type' => 'fieldable_panels_pane',
          'field_name' => 'field_map_info',
          'label' => 'Map Info',
          'required' => 0,
          'settings' => array(
          'display_summary' => 0,
          'text_processing' => 1,
          'user_register_form' => FALSE,
          ),
          'widget' => array(
              'active' => 1,
              'module' => 'text',
              'settings' => array(
                  'maxlength_js' => '',
                  'maxlength_js_enforce' => 0,
                  'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
                  'maxlength_js_truncate_html' => 0,
                  'rows' => 20,
                  'summary_rows' => 5,
              ),
          'type' => 'text_textarea_with_summary',
          'weight' => -6,
          ),
      );

  // Translatables
  // Included for use with string extractors like potx.
  t('ASU Enhanced Map Items');

  return $field_instances;
}
