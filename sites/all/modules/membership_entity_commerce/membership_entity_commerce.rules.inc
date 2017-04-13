<?php

/**
 * @file
 * Rules integration for membership transactions.
 */

/**
 * Implements hook_rules_event_info().
 */
function membership_entity_commerce_rules_event_info() {
  // So that we can use the entity_rules_events_variables() helper function.
  module_load_include('inc', 'entity', 'entity.rules');

  $events = array();
  return $events;
}

/**
 * Implements hook_rules_condition_info().
 */
function membership_entity_commerce_rules_condition_info() {
  $conditions = array();
  return $conditions;
}

/**
 * Implements hook_rules_action_info().
 */
function membership_entity_commerce_rules_action_info() {
  return array(
    'membership_entity_commerce_activate_term' => array(
      'label' => t('Activate membership term from order'),
      'group' => t('Membership term'),
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('Order', array(), array('context' => 'a drupal commerce order')),
        ),
      ),
    ),
  );
}

/**
 * Rules execute handler to activate a membership term.
 */
function membership_entity_commerce_activate_term_execute($order) {
  if (!empty($order)) {
    $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

    // Look for membership product line items on the order.
    foreach ($order_wrapper->commerce_line_items as $line_item_wrapper) {
      if ($line_item_wrapper->type->value() == 'membership_entity_line_item') {
        $term = $line_item_wrapper->membership_entity_term_ref->value();
        $term_wrapper = entity_metadata_wrapper('membership_entity_term', $term);

        // Only update "pending" terms.
        if ($term_wrapper->status->value() == MEMBERSHIP_ENTITY_PENDING) {
          $term_wrapper->status = MEMBERSHIP_ENTITY_ACTIVE;
          $term_wrapper->save();
        }
      }
    }
  }
}
