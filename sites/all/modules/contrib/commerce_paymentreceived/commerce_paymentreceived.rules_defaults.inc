<?php
/**
 * @file
 * Default Rules configurations.
 *
 * @todo Use a hook alter to ensure the checkout completion rule fires after
 *   commerce_checkout_order_status_update.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_paymentreceived_default_rules_configuration() {

  $items = array();
  
  $items['rules_commerce_paymentreceived_checkout_order_state_update'] = entity_import('rules_config', '{ "rules_commerce_paymentreceived_checkout_order_state_update" : {
      "LABEL" : "Update the order state on checkout completion if fully paid",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "5",
      "REQUIRES" : [ "commerce_payment", "commerce_order", "commerce_checkout" ],
      "ON" : [ "commerce_checkout_complete" ],
      "IF" : [
        { "commerce_payment_order_balance_comparison" : { "commerce_order" : [ "commerce_order" ], "value" : "0" } }
      ],
      "DO" : [
        { "commerce_order_update_state" : {
            "commerce_order" : [ "commerce_order" ],
            "order_state" : "commerce_paymentreceived"
          }
        }
      ]
    }
  }');
  
  $items['rules_commerce_paymentreceived_full_payment_order_state_update'] = entity_import('rules_config', '{ "rules_commerce_paymentreceived_full_payment_order_state_update" : {
      "LABEL" : "Update the order state on full payment",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "commerce_order", "commerce_payment" ],
      "ON" : [ "commerce_payment_order_paid_in_full" ],
      "IF" : [
        { "NOT data_is" : { "data" : [ "commerce-order:state" ], "value" : "checkout" } }
      ],
      "DO" : [
        { "commerce_order_update_state" : {
            "commerce_order" : [ "commerce_order" ],
            "order_state" : "commerce_paymentreceived"
          }
        }
      ]
    }
  }');
  
  return $items;
}
