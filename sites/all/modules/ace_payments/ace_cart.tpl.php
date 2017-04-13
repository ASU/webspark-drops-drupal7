<?php 
  /**
   * 'ace_cart' template for rendering the Cart on the page.
   * Arguments:
   *   $cart: the cart being rendered
   *   $purchaser: the user that is checking out
   *   $disable_checkout: TRUE to disable the checkout button, FALSE otherwise
   *   $index: the index of this cart on the page, 0-based
   *   $show_fmv: TRUE to show the Fair Market Value, FALSE to hide it
   */
  
  global $user;
  $cart_items = $cart->getItems();
  $totals = $cart->getTotals($user);
  $savings = $cart->getDiscountSavings($user);
  
  $is_member = is_member($user);
  $is_owner  = user_is_owner($user);
  
  $gw_key = $cart->getGatewayKey();
  $gateway = ace_payments_gateways($gw_key);
  $new_page = ($totals['actual'] > 0) ? "true" : "false";
  
  $attributes = array(
    'id' => "cart_{$cart->getGatewayKey()}",
    'class' => 'cart',
  );
  
  $headers = array();
  $headers[] = array('data' => 'Item', 'class' => 'title');
  $headers[] = array('data' => 'Date', 'class' => 'date');
  $headers[] = array('data' => 'Price', 'class' => 'price');
  if ($show_fmv) {
    $headers[] = array('data' => 'Fair Market<br/>Value', 'class' => 'gift');
  }
  //$headers[] = array('data' => 'Send Calendar<br/>Invites', 'class' => 'invites'),
  $headers[] = array('data' => '', 'class' => 'remove');
  
  $rows = array();
  foreach ($cart_items as $item) {
    $node = $item->getNode();
    
    if (isset($node->field_date)) {
      $start_date = ace_format_cck_date($node->field_date[0], 'm/d/Y', 'field_date', 'value');
    } else {
      $start_date = NULL;
    }
    if ($item->getGiftAmount($user) > 0) {
      $fmv = '$' . number_format($item->getPrice($user) - $item->getGiftAmount($user), 2);
    } else {
      $fmv = '';
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
      'data' => '$' . number_format($item->getPrice($user), 2),
      'class' => 'price',
    );
    if ($show_fmv) {
      $row[] = array(
        'data' => $fmv,
        'class' => 'gift',
      );
    }
//    $row[] = array(
//      'data' => '',
//      'class' => 'invites',
//    );
    $row[] = array(
      'data' => "<a href='cart/remove/{$item->getCac()}'>x</a>",
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
        'data' => '&nbsp;',
        'colspan' => ($show_fmv) ? '2' : '1',
      ),
    ),
  );
  
  // Display savings or upsell.
  if ($savings['actual'] > 0) {
    // User saved *something*, figure out how:
    $savings_line = NULL;
    if ($is_member && $is_owner && ($savings['member'] > 0 || $savings['owner'] > 0)) {
      $savings_line = 'As a member and owner, you saved';
    } else if ($is_member && $savings['member'] > 0) {
      $savings_line = 'As a member, you saved';
    } else if ($is_owner && $savings['owner'] > 0) {
      $savings_line = 'As an owner, you saved';
    }
    
    if ($savings_line) {
      $rows[] = array(
        'class' => 'savings',
        'data' => array(
          array(
            'data' => $savings_line,
            'colspan' => '2',
            'class' => 'savings-label member',
          ),
          array(
            'data' => '$' . number_format($savings['actual'], 2),
            'class' => 'savings member',
          ),
          array(
            'data' => '&nbsp;',
            'colspan' => ($show_fmv) ? '2' : '1',
          ),
        ),
      );
    }
    
  } else if ($savings['member'] > 0) {
    // User didn't save anything but could have as a member:
    $rows[] = array(
      'class' => 'savings',
      'data' => array(
        array(
          'data' => 'As a member you could save',
          'colspan' => '2',
          'class' => 'savings-label nonmember',
        ),
        array(
          'data' => '$' . number_format($savings['member'], 2),
          'class' => 'savings nonmember',
        ),
        array(
          'data' => l('Become a member now!', 'membership/apply'),
          'colspan' => ($show_fmv) ? '2' : '1',
        ),
      ),
    );
  }
?>

<h2 class="cart-title"><?php print $gateway->getCartName(); ?></h2>
<?php if ($index === 1) : ?>
	<div class="two-carts-info">
		<a href="/page/why-two-carts" target="_blank">Why two carts?</a>
	</div>
<?php endif; ?>
<?php print theme('table', $headers, $rows, $attributes); ?>
<form id="checkoutForm_<?php print $gw_key; ?>" class="checkoutform" action="/cart/checkout/<?php print $gw_key; ?>" method="GET">
	<div class="cancellation-policy">
		I understand and agree to the terms of the 
		<a href="/cancellation-policy" target="_blank">ACE Cancellation Policy</a>
		<input type="checkbox" name="accept_terms" />
	</div>
	<div class="checkout-button">
		<?php if ($disable_checkout) : ?>
			<input type="button" value="-Disabled-" disabled="disabled" /><br/>
			<span>Please complete the Membership Cart checkout first so that we can apply your membership discounts.
				After paying for your membership, return to this page and this cart will be enabled.
			</span>
		<?php else : ?>
    		<input id="checkout" type="submit" name="checkout" value="Check Out" /><br/>
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
