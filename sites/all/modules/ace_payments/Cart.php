<?php

/**
 * A cart for containing items for purchase. 
 * 
 * @author Tyler Coles
 */
class Cart {
  
  public static function get($gateway_key) {
    $cart = $_SESSION['ace_payments_cart'][$gateway_key];
    if (!$cart) {
      $gateway = ace_payments_gateways($gateway_key);
      if (!$gateway) {
        return NULL;
      }
      $cart = new Cart($gateway_key);
      Cart::save($cart);
    }
    return $cart;
  }
  
  public static function deleteCarts($gateway_key = NULL) {
    if ($gateway_key) {
      unset($_SESSION['ace_payments_cart'][$gateway_key]);
    } else {
      unset($_SESSION['ace_payments_cart']);
    }
  }
  
  public static function addItemStatic($cartItem) {
    $gateway_key = $cartItem->getGateway()->getKey();
    $cart = Cart::get($gateway_key);
    $cart->addItem($cartItem);
    Cart::save($cart, $gateway_key);
  }
  
  public static function removeItemStatic($cartItem) {
    $gateway_key = $cartItem->getGateway()->getKey();
    $cart = Cart::get($gateway_key);
    $cart->removeItem($cartItem->getCac());
    Cart::save($cart, $gateway_key);
  }
  
  public static function save($cart) {
    $_SESSION['ace_payments_cart'][$cart->gateway_key] = $cart;
  }
  
  public static function getItemCount() {
    $count = 0;
    $gateways = ace_payments_gateways();
    foreach ($gateways as $gw) {
      $cart = Cart::get($gw->getKey());
      $count = $count + count($cart->items);
    }
    return $count;
  }
  
  private $gateway_key;
  private $items = array();
  private $quantities = array();
  
  public function __construct($gateway_key) {
    $this->gateway_key = $gateway_key;
  }
  
  public function getGatewayKey() {
    return $this->gateway_key;
  }
  
  public function addItem(CartItem $i) {
    $cac = $i->getCac();
    if ($this->getItem($cac)) {
      // Item is already in cart, don't change quantity.
      return;
    } else {
      $this->items[$cac] = $i;
      $this->quantities[$cac] = 1;
      $i->addedToCart($this);
    }
  }
  
  public function getItem($cac) {
    return $this->items[$cac];
  }
  
  public function getItems() {
    return $this->items;
  }
  
  public function getQuantity($cac) {
    if (!$this->getItem($cac))
      return 0;
    return $this->quantities[$cac];
  }
  
  public function setQuantity($cac, $qty) {
    if ($qty === 0) {
      removeItem($cac);
    } else if ($this->getItem($cac)) {
      $this->quantities[$cac] = $qty;
    }
  }
  
  public function getTotals($account) {
    $totals = array(
      'actual' => 0,
      'base'   => 0,
      'member' => 0,
      'owner'  => 0,
    );
    foreach ($this->items as $cac => $i) {
      $qty = $this->quantities[$cac];
      $totals['actual'] += $i->getPrice($account)  * $qty;
      $totals['base']   += $i->getNonMemberPrice() * $qty;
      $totals['member'] += $i->getMemberPrice()    * $qty;
      $totals['owner']  += $i->getOwnerPrice()     * $qty;
    }
    return $totals;
  }
  
  public function getDiscountSavings($account) {
    $savings = $this->getTotals($account);
    $savings['actual'] = $savings['base'] - $savings['actual'];
    $savings['member'] = $savings['base'] - $savings['member'];
    $savings['owner']  = $savings['base'] - $savings['owner'];
    $savings['base']   = 0;
    return $savings;
  }
  
  public function getGiftTotal($account) {
    $total = 0;
    foreach ($this->items as $cac => $i) {
      $qty = $this->quantities[$cac];
      $subtotal = $i->getGiftAmount($account) * $qty;
      $total += $subtotal;
    }
    return $total;
  }
  
  public function removeItem($cac) {
    unset($this->items[$cac]);
    unset($this->quantities[$cac]);
  }
  
  public function clear() {
    $this->items = array();
    $this->quantities = array();
  }
}