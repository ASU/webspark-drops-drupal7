<?php
/**
 * @file
 * Default rules configuration.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_registration_default_rules_configuration() {
  $rule1 = rules_reaction_rule();
  $rule1->label = "Set Registrations to Pending upon Order Completion";
  $rule1->active = TRUE;
  $rule1->event('commerce_checkout_complete')
    ->action('commerce_registration_set_state', array(
      'commerce_order:select' => "commerce-order",
      'registration_state' => 'pending',
    )
  );
  $rule2 = rules_reaction_rule();
  $rule2->label = "Set Registrations to Complete upon Full Payment";
  $rule2->active = TRUE;
  $rule2->event('commerce_payment_order_paid_in_full')
    ->action('commerce_registration_set_state', array(
      'commerce_order:select' => "commerce-order",
      'registration_state' => 'complete',
    )
  );

  return array(
    'commerce_registration_pending_upon_order_completion' => $rule1,
    'commerce_registration_complete_upon_full_payment' => $rule2,
  );
}
