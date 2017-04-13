<?php

class Order {
  
  public static function load($order_id) {
    $order_result = db_query('SELECT * FROM {ace_order} WHERE order_id  = %d', $order_id);
    $orders = Order::loadFromResult($order_result);
    return (!empty($orders)) ? $orders[0] : NULL;
  }
  
  public static function loadHistory($uid) {
    $sql = 'SELECT * FROM {ace_order} o LEFT JOIN {ace_order_status} s ON o.status = s.status '
         . 'WHERE uid = ' . $uid . ' AND s.successful = 1 ORDER BY create_time DESC';
    $count = 'SELECT COUNT(order_id) FROM {ace_order} o LEFT JOIN {ace_order_status} s ON o.status = s.status '
           . 'WHERE uid = %d AND s.successful = 1';
    //$order_result = pager_query($sql, 5, 0, $count, $uid);
    $order_result = db_query($sql);
    return Order::loadFromResult($order_result);
  }
  
  private static function loadFromResult($result) {
    $orders = array();
    foreach($result as $order) {
      $item_result = db_query('SELECT * FROM {ace_order_item} WHERE order_id = %d ORDER BY cac ASC', $order->order_id);
      $order->items = array();
      foreach($item_result as $order_item) { 
        $order->items[$order_item->cac] = $order_item;
      }
      $orders[] = $order;
    }
    return $orders;
  }
  
  public static function save($cart, $purchaser, $admin = NULL) {
    // Write ace_order record.
    $order = new stdClass();
    $order->uid = $purchaser->uid;
    if ($admin) {
      $order->admin_uid = $admin->uid;
    }
    $totals = $cart->getTotals($purchaser);
    $order->total = $totals['actual'];
    $order->gift_total = $cart->getGiftTotal($purchaser);
    $order->create_time = time();
    
    $write = drupal_write_record('ace_order', $order);
    if ($write === FALSE) {
      return FALSE; // Failed to write order record.
    }
    
    // Write each ace_order_item record.
    $success = TRUE;
    foreach ($cart->getItems() as $i) {
      $order_item = new stdClass();
      $order_item->order_id = $order->order_id;
      $order_item->cac = $i->getCac();
      $order_item->quantity = $cart->getQuantity($i->getCac());
      $order_item->amount = $i->getPrice($purchaser);
      $order_item->gift_amount = $i->getGiftAmount($purchaser);
      $order_item->type = $i->getType();
      $referrer = $i->getReferrer();
      if (!empty($referrer)) {
        $order_item->referrer = $referrer;
      }
      
      $write = drupal_write_record('ace_order_item', $order_item);
      if ($write === FALSE) {
        $success = FALSE; // Failed to write item record.
      }
      
      $order->items[$order_item->cac] = $order_item;
    }
    return $order;
  }
}
