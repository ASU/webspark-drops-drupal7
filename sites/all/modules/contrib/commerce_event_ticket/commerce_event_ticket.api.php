<?php
/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Define event ticket types.
 */
function hook_commerce_event_ticket_info() {
  $types = array();
  $types['custom_module_ticket'] = array(
    'name' => t('Custom ticket'),
  );
  return $types;
}

/**
 * Alter event ticket types.
 */
function hook_commerce_event_ticket_info_alter(&$types) {
  $types['custom_module_ticket']['name'] = t('Renamed custom ticket');
}

/**
 * Act after tickets have been created for an order.
 *
 * @param array $tickets
 *   An array of the order's tickets (CommerceEventTicketEntity objects), keyed
 *   by ticket ID.
 * @param object $order
 *   The Commerce order object.
 */
function hook_commerce_event_tickets_created_order(array $tickets, $order) {
  // Do something with the tickets here.
}

/**
 * Alter whether a product is enabled to have tickets.
 *
 * @param bool &$enabled
 *   Whether purchases of the product should generate tickets.
 * @param object $product
 *   The Commerce product object.
 */
function hook_commerce_event_ticket_product_enabled_alter(&$enabled, $product) {
  if (strpos($product->title, 'ticket')) {
    $enabled = TRUE;
  }
}
