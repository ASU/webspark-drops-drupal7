<?php 
  /**
   * 'order_details' template for rendering order details for an email receipt.
   * Arguments:
   *    $order: the order
   */
  $timezone = date_default_timezone_name();
  $timezone = date_get_timezone($field['tz_handling'], $timezone);
  $date = date_make_date($order->create_time, $timezone, DATE_UNIX);
  $date = date_format_date($date, 'custom', 'm-d-Y g:i a');
  $purchaser = user_load(array('uid' => $order->uid));
?>
<table cellpadding="3">
	<thead>
		<tr>
    		<th style="border-bottom: 1px solid black;">Name</th>
    		<th style="border-bottom: 1px solid black;">Quantity</th>
    		<th style="border-bottom: 1px solid black;">Price</th>
    		<th style="border-bottom: 1px solid black;">Fair Market Value</th>
		</tr>
	</thead>
	<tbody>
    	<?php 
    	  foreach ($order->items as $item) :
    	    $cartItem = CartItem::get($item->cac, $order);
    	    $node = $cartItem->getNode();
    	    $price = $cartItem->getPrice($purchaser);
    	    $gift = $cartItem->getGiftAmount($purchaser);
    	    $fmv = $price - $gift;
    	?>
        	<tr>
        		<td><?php print $cartItem->getTitle(); ?></td>
        		<td><?php print $item->quantity; ?></td>
        		<td>$<?php print number_format($price, 2); ?></td>
        		<?php if ($gift > 0) : ?>
        			<td>$<?php print number_format($fmv, 2); ?></td>
        		<?php else : ?>
        			<td>&nbsp;</td>
        		<?php endif; ?>
        	</tr>
    	<?php endforeach; ?>
	</tbody>
</table>
<p>
	Total Price: $<?php print number_format($order->total, 2); ?><br/>
	<?php if ($order->gift_total > 0) : ?> 
	Total Fair Market Value: $<?php print number_format($order->total - $order->gift_total, 2); ?><br/>
	<?php endif; ?>
	Order Placed: <?php print $date; ?>
</p>
