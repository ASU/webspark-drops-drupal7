<?php
/**
 * @file
 * Default field bases for the Commerce Event Ticket module.
 */

/**
 * Get default field bases.
 *
 * @return array
 *   An array of field base definitions.
 */
function _commerce_event_ticket_field_bases() {
  $field_bases = array();

  // Exported field_base: 'cet_enable'
  $field_bases['cet_enable'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array('commerce_product'),
    'field_name' => 'cet_enable',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  return $field_bases;
}
