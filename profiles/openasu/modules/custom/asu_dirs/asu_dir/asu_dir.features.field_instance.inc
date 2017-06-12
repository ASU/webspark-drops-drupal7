<?php
/**
 * @file
 * asu_directory.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function asu_dir_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-asu_directory-field_asu_directory_items'
  $field_instances['node-asu_directory-field_asu_directory_items'] = array(
    'bundle' => 'asu_directory',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'asu_dir',
        'settings' => array(),
        'type' => 'asu_directory',
        'weight' => 0,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_asu_directory_items',
    'label' => 'ASU Directory Items',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'asu_dir',
      'settings' => array(),
      'type' => 'asu_directory_form',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('ASU Directory Items');

  return $field_instances;
}
