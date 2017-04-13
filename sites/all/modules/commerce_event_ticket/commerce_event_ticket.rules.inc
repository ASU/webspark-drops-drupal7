<?php
/**
 * @file
 * Rules integration for the Commerce Event Ticket module.
 */

/**
 * Implements hook_rules_condition_info().
 */
function commerce_event_ticket_rules_condition_info() {
  $conditions = array();

  $conditions['commerce_event_ticket_order_should_have_tickets'] = array(
    'label' => t('Order should have tickets'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
        'description' => t('The order that will be checked.'),
      ),
    ),
    'group' => t('Commerce Event Ticket'),
    'callbacks' => array(
      'execute' => 'commerce_event_ticket_order_should_have_tickets',
    ),
    'module' => 'commerce_event_ticket',
  );

  return $conditions;
}
