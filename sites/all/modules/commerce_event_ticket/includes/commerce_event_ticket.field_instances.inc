<?php
/**
 * @file
 * Default field instances for the Commerce Event Ticket module.
 */

/**
 * Get default field instances for products.
 *
 * @return array
 *   An array of field instance definitions.
 */
function _commerce_event_ticket_product_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'commerce_product-ticket-cet_enable'
  $field_instances['cet_enable'] = array(
    'bundle' => 'ticket',
    'commerce_cart_settings' => array(
      'attribute_field' => 0,
      'attribute_widget' => 'select',
      'attribute_widget_title' => 'Enable tickets',
    ),
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Enable this if you want tickets to be created for purchases of this product.',
    'display' => array(
      'attribute_view' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'line_item' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'node_full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'node_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'commerce_product',
    'field_name' => 'cet_enable',
    'label' => 'Enable tickets',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 10,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Enable this if you want tickets to be created for purchases of this product.');
  t('Enable tickets');

  return $field_instances;
}
