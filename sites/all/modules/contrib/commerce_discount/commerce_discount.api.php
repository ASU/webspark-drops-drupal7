<?php

/**
 * @file
 * Hooks provided by the Commerce Discount module.
 */

/**
 * Defines the types of discounts available for creation on the site.
 *
 * Each defined type is a bundle of the commerce_discount entity type, hence
 * able to have its own fields attached.
 *
 * The discount type array structure includes the following keys:
 * - label: a translatable, human-readable discount type label.
 * - event: the machine name of the rules event used to apply a discount of
 *   the defined type.
 * - entity type: The type of entity to which the discount will be applied.
 *
 * @return array
 *   An array of discount type arrays keyed by the machine name of the type.
 */
function hook_commerce_discount_type_info() {
  $types = array();
  $types['order_discount'] = array(
    'label' => t('Order Discount'),
    'event' => 'commerce_order_presave',
    'entity type' => 'commerce_order',
  );
  $types['product_discount'] = array(
    'label' => t('Product Discount'),
    'event' => 'commerce_product_calculate_sell_price',
    'entity type' => 'commerce_line_item',
  );

  return $types;
}

/**
 * Defines the types of discount offers available for creation on the site.
 *
 * Each defined type is a bundle of the commerce_discount_offer entity type,
 * hence able to have its own fields attached.
 *
 * The discount offer type array structure includes the following keys:
 * - label: a translatable, human-readable discount offer type label.
 * - action: the Rules function callback used to apply a discount offer
 *   of the defined type to an entity.
 * - event (optional): the machine name of the rules event used to apply a
 *   discount of the defined type. This one will override the default discount
 *   type event. If you need to alter event parameters, you have to implement
 *   the hook_commerce_discount_rule_build() in your module.
 * - entity types: The entity types that this offer handles. Only offers
 *   that support the "entity type" of the selected discount type are shown in
 *   the UI.
 *
 * @return array
 *   An array of discount offer type arrays keyed by the machine name of the
 *   type.
 */
function hook_commerce_discount_offer_type_info() {
  $types = array();
  $types['random_amount'] = array(
    'label' => t('Random $ off'),
    'action' => 'foo_random_amount',
    'event' => 'foo_random_rules_event',
    'entity types' => array('commerce_order', 'commerce_line_item'),
  );

  return $types;
}

/**
 * Allow modules alter the rule object, with commerce discount configuration.
 *
 * @param RulesPlugin $rule
 *   The rule configuration entity, passed by reference.
 * @param CommerceDiscount $commerce_discount
 *   The commerce discount entity.
 */
function hook_commerce_discount_rule_build(RulesPlugin $rule, CommerceDiscount $commerce_discount) {
  if ($commerce_discount->name == 'foo') {
    $rule->action('drupal_message', array('message' => 'Discount FOO was applied.'));
  }
}

/**
 * Alter the context that is going to be passed into a bonus product line item.
 *
 * Use this to modify the display path.
 *
 * @param array $context
 *   The context that is about to be passed into a new free bonus product line
 *   item.
 * @param object $product
 *   The product that is being offered as free.
 * @param CommerceDiscount $discount
 *   The discount containing this offer.
 */
function hook_commerce_discount_free_product_context_alter(&$context, $product, CommerceDiscount $discount) {
  $context['display_path'] = 'any/page';
}
