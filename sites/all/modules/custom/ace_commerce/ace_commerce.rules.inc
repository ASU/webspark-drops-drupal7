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
      'execute' => 'ace_commerce_order_rules_no_payment_method',
    ),
  );
  $conditions['commerce_product_selected_product_type'] = array(
    'label' => t('Single product is of product type'),
    'parameter' => array(
      'new_product' => array(
        'type' => 'commerce_product',
        'label' => t('Product to compare'),
        'description' => t('The product needed for comparison.'),
      ),
      // Re-using commerce_product_selected_product_type from commerce_order.rules.inc
      'product_type' => array(
        'label' => t('Product type(s)'),
        'type' => 'list<text>',
        'description' => t('The product type(s) to compare to the product.'),
        'options list' => 'commerce_product_type_options_list',
      ),
    ),
    // Group the action will appear under when selecting an action/condition
    'group' => t('Commerce Product'),
    'callbacks' => array( // Function that actually returns true or false
      'execute' => 'ace_commerce_product_rules_selected_product_type',
    ),
  );

  return $conditions;
}

/**
 * Rules Condition helper function - No payment methods already attached to $order?
 */
function ace_commerce_order_rules_no_payment_method($order) {
  if (isset($order->payment_methods)) {
    $payment_methods = array_filter($order->payment_methods);
    if (empty($payment_methods)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Rules Conditional helper function - Is submitted product type in product list?
 */
function ace_commerce_product_rules_selected_product_type($product, $product_types) {
  if (isset($product) && !empty($product)) {
    foreach($product_types as $type_from_list) {
      if ($product->type === $type_from_list) {
        return TRUE;
      }
    }
  }
  return FALSE;
}