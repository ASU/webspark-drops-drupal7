<?php
/**
 * @file
 * Entity property info hooks for the Commerce Event Ticket module.
 */

/**
 * Implements hook_entity_property_info().
 */
function commerce_event_ticket_entity_property_info() {
  $info = array();
  $properties = &$info['commerce_event_ticket']['properties'];
  $properties = array(
    'ticket_id' => array(
      'label' => t('Ticket ID'),
      'description' => t('Primary key'),
      'type' => 'integer',
      'schema field' => 'ticket_id',
      'required' => TRUE,
    ),
    'type' => array(
      'label' => t('Type'),
      'description' => t('The type of ticket.'),
      'type' => 'token',
      'schema field' => 'type',
      'required' => TRUE,
    ),
    'barcode_token' => array(
      'label' => t('Barcode token'),
      'description' => t('The barcode token for the ticket.'),
      'type' => 'text',
      'schema field' => 'barcode_token',
      'required' => TRUE,
    ),
    'order_id' => array(
      'label' => t('Order'),
      'description' => t('The Commerce order associated with the ticket.'),
      'type' => 'commerce_order',
      'schema field' => 'order_id',
      'required' => TRUE,
    ),
    'line_item_id' => array(
      'label' => t('Line item'),
      'description' => t('The Commerce line item associated with the ticket.'),
      'type' => 'commerce_line_item',
      'schema field' => 'line_item_id',
      'required' => TRUE,
    ),
    'product_id' => array(
      'label' => t('Product'),
      'description' => t('The Commerce product associated with the ticket.'),
      'type' => 'commerce_product',
      'schema field' => 'product_id',
      'required' => TRUE,
    ),
    'nid' => array(
      'label' => t('Node'),
      'description' => t('The content node associated with the ticket.'),
      'type' => 'node',
      'schema field' => 'nid',
      'required' => FALSE,
    ),
    'used' => array(
      'label' => t('Used'),
      'description' => t('Whether the ticket has already been used for admittance to the event.'),
      'type' => 'boolean',
      'schema field' => 'used',
      'required' => TRUE,
    ),
    'number' => array(
      'label' => t('Number'),
      'description' => t('The number of the ticket within the line item quantity.'),
      'type' => 'integer',
      'schema field' => 'number',
      'required' => FALSE,
    ),
    'quantity' => array(
      'label' => t('Total'),
      'description' => t('The total line item quantity.'),
      'type' => 'integer',
      'schema field' => 'quantity',
      'required' => FALSE,
    ),
    'created' => array(
      'label' => t('Created date'),
      'type' => 'date',
      'description' => t('The date when the ticket was created.'),
      'schema field' => 'created',
      'required' => TRUE,
    ),
    'changed' => array(
      'label' => t('Updated date'),
      'type' => 'date',
      'description' => t('The date when the ticket was last updated.'),
      'schema field' => 'changed',
      'required' => TRUE,
    ),
  );
  return $info;
}
