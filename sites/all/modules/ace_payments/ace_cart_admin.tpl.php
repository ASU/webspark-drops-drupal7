<?php 
  /**
   * 'ace_cart' template for rendering the Cart on the page.
   * Arguments:
   *   $cart: the cart to render
   *   $purchaser: the user that the admin is purchasing for
   *   $disable_checkout: TRUE to disable the checkout button, FALSE otherwise
   *   $index: the index of this cart on the page, 0-based
   *   $show_fmv: TRUE to show the Fair Market Value, FALSE to hide it
   */
  
  $cart_items = $cart->getItems();
  $totals = $cart->getTotals($purchaser);
  $savings = $cart->getDiscountSavings($purchaser);
  
  $is_member = is_member($purchaser);
  $is_owner  = user_is_owner($purchaser);
  
  $gw_key = $cart->getGatewayKey();
  $gateway = ace_payments_gateways($gw_key);
  $new_page = ($totals['actual'] > 0) ? "true" : "false";
  
  $attributes = array(
    'id' => "cart_{$cart->getGatewayKey()}",
    'class' => 'cart admin-cart',
  );
  
  $headers = array();
  $headers[] = array('data' => 'Item', 'class' => 'title');
  $headers[] = array('data' => 'Date', 'class' => 'date');
  $headers[] = array('data' => 'Price', 'class' => 'price');
  if ($show_fmv) {
    $headers[] = array('data' => 'Gift Amount', 'class' => 'gift');
  }
//$headers[] = array('data' => 'Send Calendar<br/>Invites', 'class' => 'invites'),
  $headers[] = array('data' => 'Remove', 'class' => 'remove');
  
  $rows = array();
  foreach ($cart_items as $item) {
    $node = $item->getNode();
    
    if (isset($node->field_date)) {
      $start_date = ace_format_cck_date($node->field_date[0], 'm/d/Y', 'field_date', 'value');
    } else {
      $start_date = NULL;
    }
    
    $row = array();
    $row[] = array(
      'data' => $item->getTitleLink(),
      'class' => 'title',
    );
    $row[] = array(
      'data' => $start_date,
      'class' => 'date',
    );
    $row[] = array(
      'data' => "$<input type='text' name='price_{$item->getCac()}' value='{$item->getPrice($purchaser)}' size='6' />",
      'class' => 'price',
    );
    if ($show_fmv) {
      $row[] = array(
        'data' => "$<input type='text' name='gift_{$item->getCac()}' value='{$item->getGiftAmount($purchaser)}' size='6' />",
        'class' => 'gift',
      );
    }
//    $row[] = array(
//      'data' => '',
//      'class' => 'invites',
//    );
    $row[] = array(
      'data' => "<input type='checkbox' name='remove_{$item->getCac()}' />",
      'class' => 'remove',
    );
    
    $rows[] = array('data' => $row);
  }
  $rows[] = array(
    'class' => 'total',
    'data' => array(
      array(
        'data' => 'Total',  
        'colspan' => '2',
        'class' => 'total-label',
      ),
      array(
        'data' => '$' . number_format($totals['actual'], 2),
        'class' => 'total',
      ),
      array(
        'data' => '<input id="updatecart" type="submit" name="update" value="Update Cart" />',
        'colspan' => ($show_fmv) ? '2' : '1',
      ),
    ),
  );
?>

<h2 class="cart-title"><?php print $gateway->getCartName(); ?></h2>
<?php if ($index === 1) : ?>
	<div class="two-carts-info">
		<a href="/page/why-two-carts" target="_blank">Why two carts?</a>
	</div>
<?php endif; ?>
<form id="checkoutForm_<?php print $gw_key; ?>" class="checkoutform" action="/cart/checkout/<?php print $gw_key; ?>" method="GET">
    <?php print theme('table', $headers, $rows, $attributes); ?>
	<div class="cancellation-policy">
		I understand and agree to the terms of the 
		<a href="/cancellation-policy" target="_blank">ACE Cancellation Policy</a>
		<input type="checkbox" name="accept_terms" checked="checked" />
	</div>
	<div class="checkout-button">
		<input id="checkout" type="submit" name="checkout" value="Check Out" /><br/>
		<?php if ($disable_checkout) : ?>
			<span>You should complete the Membership Cart checkout first.</span>
		<?php else : ?>
    		<span><?php print $gateway->getCartCheckoutMessage(); ?></span>
		<?php endif; ?>
	</div>
	<?php if ($gw_key === 'asuf') : ?>
		<div class="asuf-notice">All funds will be deposited with the ASU Foundation for a New American University, a separate non-profit organization 
			that exists to support ASU. Due to the fair market value of benefits provided, only payments in excess of 
			fair market value may be considered a charitable contribution. Please consult your tax advisor regarding the 
			deductibility of charitable contributions. Fair market value per item is listed where applicable.</div>
	<?php endif; ?>
	<input type="hidden" name="new-page" value="<?php print $new_page; ?>" />
</form>