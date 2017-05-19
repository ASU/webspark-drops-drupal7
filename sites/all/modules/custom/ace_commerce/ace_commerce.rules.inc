<?php

/**
 * @file - ace_commerce.rules.inc
 * Extending Rules Conditionals for Commerce payment methods checking
 */

/**
 * Implements hook_commerce_rules_condition_info()
 */
function ace_commerce_rules_condition_info() {
  $conditions = array();

  $conditions['commerce_order_payment_method_empty'] = array(
    'label' => t('No payment method already attached to order'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
        'description' => t('No payment method already been enabled for this order.'),
      ),
    ),
    'group' => t('Commerce Order'), // Group the action will appear under when selecting an action/condition
    'callbacks' => array( // Function that actually returns true or false
      'execute' => 'commerce_order_rules_no_payment_method',
    ),
  );

  return $conditions;
}

/**
 * Condition callback - No payment methods already attached to $order?
 */
function commerce_order_rules_no_payment_method($order) {
  if (isset($order->payment_methods)) {
    $payment_methods = array_filter($order->payment_methods);
    if (empty($payment_methods)) {
      return TRUE;
    }
  }
  return FALSE;
}
