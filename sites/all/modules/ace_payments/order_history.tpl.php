<?php 
  /**
   * 'order_history' theme for displaying a user's orders.
   * Arguments:
   *   $orders: the user's orders
   */
  
  drupal_add_css(drupal_get_path('module', 'ace_payments') . '/styles/order-history.css');
  
  $attributes = array(
    'class' => 'order-history',
  );
  
  $headers = array(
    array('data' => 'Date', 'class' => 'date'),
    array('data' => 'Amount', 'class' => 'amount'),
    array('data' => 'Fair Market<br/>Value', 'class' => 'fmv'),
    array('data' => 'Items', 'class' => 'items'),
  );
  
  $rows = array();
  foreach ($orders as $o) {
    $row = array();
    
    $items = array();
    if (empty($o->items)) {
      $items[] = '-Items deleted-';
    } else { 
      foreach ($o->items as $i) {
        $cart_item = CartItem::get($i->cac);
        if ($cart_item) {
          $node = $cart_item->getNode();
          if ($cart_item && ($node || $cart_item->getType() == MEMBERSHIP_TYPE)) {
            $items[] = $cart_item->getTitleLink();
          } else {
            $items[] = '-Item deleted-';
          }
        } else {
          $items[] = '-Item deleted-';
        }
      }
    }
    $items_html = theme('item_list', $items);
    
    $row[] = array(
      'data' => format_date($o->create_time, 'custom', 'm/d/Y'),
      'class' => 'date',
    );
    $row[] = array(
      'data' => '$' . number_format($o->total, 2),
      'class' => 'amount',
    );
    $row[] = array(
      'data' => '$' . number_format($o->total - $o->gift_total, 2),
      'class' => 'fmv',
    );
    $row[] = array(
      'data' => $items_html,
      'class' => 'items',
    );
    
    $rows[] = $row;
  }
  
  print theme('pager', NULL, 5, 0);
  print theme('table', $headers, $rows, $attributes);
  print theme('pager', NULL, 5, 0);
?>
