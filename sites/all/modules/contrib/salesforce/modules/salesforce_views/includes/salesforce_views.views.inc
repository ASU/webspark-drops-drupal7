<?php

/**
 * @file
 * Contains relationship handlers.
 */

/**
 * Implements hook_views_data_alter().
 */
function salesforce_views_views_data_alter(&$data) {
  $mappings = salesforce_mapping_load();
  $mapped_entities = array();
  foreach ($mappings as $mapping) {
    $entity_info = entity_get_info($mapping->drupal_entity_type);
    $mapped_entities[$mapping->drupal_entity_type] = $entity_info;
  }
  foreach ($mapped_entities as $entity_type => $info) {
    $data[$info['base table']]['salesforce_mapping_object'] = array(
      'group' => t('Salesforce Mapping Object'),
      'title' => t('Salesforce Mapping'),
      'help' => t('The mapping object associated with the entity.'),
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'label' => t('Salesforce Object'),
        'base' => 'salesforce_mapping_object',
        'base field' => 'entity_id',
        'relationship field' => $info['entity keys']['id'],
        'extra' => array(
          array(
            'field' => 'entity_type',
            'value' => $entity_type,
            'numeric' => FALSE
          ),
        ),
      ),
    );
  }
}
