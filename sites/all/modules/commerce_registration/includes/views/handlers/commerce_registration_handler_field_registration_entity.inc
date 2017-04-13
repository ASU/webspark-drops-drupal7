<?php
/**
 * @file
 * Commerce Registration attached entity views field handler.
 */

class CommerceRegistrationHandlerFieldRegistrationEntity extends views_handler_field {
  /**
   * Views handler constructor.
   */
  function construct() {
    parent::construct();
  }

  /**
   * Returns a link to the registration's Commerce Product.
   *
   * @return string
   *   The HTML link to the product.
   */
  function render($values) {
    $product = commerce_product_load($values->registration_entity_id);
    if (!empty($product)) {
      $uri = entity_uri('commerce_product', $product);
      $text = t('@product (@sku)', array('@product' => $product->title, '@sku' => $product->sku));
      return l($text, $uri['path']);
    }
  }
}
