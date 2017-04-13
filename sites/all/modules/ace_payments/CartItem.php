<?php

/**
 * A product that can be placed in a cart and purchased. 
 * 
 * @author Tyler Coles
 * @abstract
 */
abstract class CartItem {
  
  public abstract function getTitle();
  public abstract function getCac();
  public abstract function getType();
  public abstract function getNode();
  public abstract function canPurchase($user);
  public abstract function startPurchase($user, $order_id);
  public abstract function finishPurchase($registration_record, $user);
  public abstract function getMemberPrice();
  public abstract function getNonMemberPrice();
  public abstract function getOwnerPrice();
  public abstract function getMemberGiftAmount();
  public abstract function getNonMemberGiftAmount();
  public abstract function getOwnerGiftAmount();
  
  private $override_price = NULL;
  private $override_gift_amount = NULL;
  private $referrer;
  
  public function getGateway() {
    return ace_payments_gateways('quikpay');
  }
  
  public function getTitleLink() {
    $node = $this->getNode();
    return l($this->getTitle(), "node/{$node->nid}");
  }
  
  /**
   * Set a price which overrides the standard 
   * member and non-member prices.
   */
  final public function setOverridePrice($price) {
    if (is_numeric($price) && $price >= 0) {
      $this->override_price = $price;
    }
  }
  
  final public function getOverridePrice() {
    return $this->override_price;
  }
  
  /**
   * Set a gift amount which overrides the standard 
   * member and non-member gift amounts.
   */
  final public function setOverrideGiftAmount($amount) {
    if (is_numeric($amount) && $amount >= 0) {
      $this->override_gift_amount = $amount;
    }
  }
  
  final public function getOverrideGiftAmount() {
    return $this->override_gift_amount;
  }
  
  /**
   * Gets the applicable price. If an override
   * price is set, that is used. This method
   * should be used to get the price that the user
   * should be charged, and you should only
   * use getMemberPrice() or getNonMemberPrice()
   * directly if you specifically need to know
   * what the original price points were. 
   * @param $account The user account of the purchaser; special pricing may apply.
   */
  final public function getPrice($account) {
    if (!is_null($this->override_price)) {
      return $this->override_price;
    }
    
    $member = is_member($account);
    $owner = user_is_owner($account);
    
    $nonMemberPrice = $this->getNonMemberPrice();
    $memberPrice = $this->getMemberPrice();
    $ownerPrice = $this->getOwnerPrice();
    
    // An array of prices to consider. We'll return the lowest of the valid prices.
    $consider = array();
    if ($member && $owner) {
      if (!empty($memberPrice))
        $consider[] = $memberPrice;
      if (!empty($ownerPrice))
        $consider[] = $ownerPrice;
    } else if ($member) {
      if (!empty($memberPrice))
        $consider[] = $memberPrice;
    } else if ($owner) {
      if (!empty($nonMemberPrice))
        $consider[] = $nonMemberPrice;
      if (!empty($ownerPrice))
        $consider[] = $ownerPrice;
    } else {
      if (!empty($nonMemberPrice))
        $consider[] = $nonMemberPrice;
    }
    return max(0, min($consider)); // Return lowest price, but never return negative.
  }
  
  /**
   * Gets the applicable gift amount. If an override
   * gift amount is set, that is used. This method
   * should be used to get the gift amount for this item, 
   * and you should only use getMemberGiftAmount() or 
   * getNonMemberGiftAmount() directly if you specifically need 
   * to know what the original amounts were. 
   * @param $account The user account of the purchaser; special pricing may apply.
   */
  final public function getGiftAmount($account) {
    if (!is_null($this->override_gift_amount)) {
      return $this->override_gift_amount;
    }
    
    $member = is_member($account);
    $owner = user_is_owner($account);
    
    if ($member && $owner) {
      $price = min($this->getMemberGiftAmount(), $this->getOwnerGiftAmount());
    } else if ($member) {
      $gift = $this->getMemberGiftAmount();
    } else if ($owner) {
      $price = $this->getOwnerGiftAmount();
    } else {
      $gift = $this->getNonMemberGiftAmount();
    }
    
    // Gift amount can never be greater than price.
    if ($gift > $this->getPrice($account)) {
      return $this->getPrice($account);
    } else {
      return $gift;
    }
  }
  
  final public function setReferrer($referrer) {
    $this->referrer = $referrer;
  }
  
  final public function getReferrer() {
    return $this->referrer;
  }
  
  /**
   * Loads details of a past order into this item. Any subclass
   * overriding this method should most likely keep a call to 
   * the superclass' implementation.
   * @param $order the order whose details to load.
   */
  public function loadForOrder($order = NULL) {
    if ($order && $order_item = $order->items[$this->getCac()]) {
      $this->setOverridePrice($order_item->amount);
      $this->setOverrideGiftAmount($order_item->gift_amount);
      $this->setReferrer($order_item->referrer);
    }
  }
  
  /**
   * Allows a cart item to react to being added to the cart
   * and perform any additional actions required to maintain
   * its own state. By default, this does nothing.
   * @param $cart the cart the item was added to.
   */
  public function addedToCart($cart) {}
  
  /**
   * Gets a subclass-appropriate instance of the CartItem with the given CAC.
   * If the order record is also given, additional information
   * will be loaded specific to that order.
   * In this way, calling this method with just CAC creates a fresh
   * cart item; calling it with CAC and an order record fetches an
   * item that was already purchased.
   * @param $cac the item accounting code.
   * @param $order (optional) an order in which this item was
   * purchased.
   */
  public static function get($cac, $order = NULL) {
    $items = module_invoke_all('get_cart_item', $cac, $order);
    if (count($items) === 1) {
      return $items[0];
    }
    return NULL;
  }
}