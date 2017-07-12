<?php
/**
 * @file
 * Contains Commerce hooks, callbacks and helper functions for Commerce payment
 * received.
 *
 * @todo Use a hook alter to ensure the new state comes after checkout.
 */

/**
 * Implements hook_commerce_order_state_info().
 */
function commerce_paymentreceived_commerce_order_state_info() {
  return array(
    'commerce_paymentreceived' => array(
      'name' => 'commerce_paymentreceived',
      'title' => t("Payment received"),
      'description' => t("Orders in this state have been paid in full, but haven't been completely processed."),
      'weight' => 5,
      'default_status' => 'commerce_paymentreceived',
      'cart' => FALSE,
      'status' => TRUE,
    ),
  );
}

/**
 * Implements hook_commerce_order_status_info().
 */
function commerce_paymentreceived_commerce_order_status_info() {
  return array(
    'commerce_paymentreceived' => array(
      'name' => 'commerce_paymentreceived',
      'title' => t("Payment received"),
      'state' => 'commerce_paymentreceived',
      'cart' => FALSE,
    ),
  );
}
