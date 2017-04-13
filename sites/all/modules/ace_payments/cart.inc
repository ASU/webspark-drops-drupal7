<?php

function cart_page() 
{
  // Send anonymous user to login screen.
  if (!user_access('make payments')) 
  {
    drupal_set_message(t('Please log in before continuing with your purchase.'));
    drupal_goto('user', drupal_get_destination(), NULL, 307);
    return;
  }
  
  drupal_add_css(drupal_get_path('module', 'ace_payments') . '/styles/cart.css');
  drupal_add_js(drupal_get_path('module', 'ace_common') . '/scripts/jquery.simpletip-1.3.1.min.js');
  drupal_add_js(drupal_get_path('module', 'ace_payments') . '/scripts/cart.js');
  
  if (!user_access('admin registration')) 
  {
    $cart_theme = 'ace_cart';
  } 
  else 
  {
    $cart_theme = 'ace_cart_admin';
    $purchaser = user_load(array('uid' => $_SESSION['checkout_purchaser']));
    // User selection form.
    $output .= <<<EOT
      <div id="select_user">
        <form name="select_user" id="select_user_form" action="cart/select-user" method="post">
          <span>Select the user to purchase for:</span>
          <input type="text" name="email" size="50" value="{$purchaser->mail}" />
          <input type="submit" name="select" value="Select User" />
        </form>
      </div>
EOT;
  }
  
  $membership_in_cart = FALSE;
  $asuf = Cart::get('asuf');
  foreach ($asuf->getItems() as $item) 
  {
    if ($item->getType() == 'membership') 
    {
      $membership_in_cart = TRUE;
    }
  }
  
  // Render carts.
  $all_empty = TRUE;
  $gateways = ace_payments_gateways();
  $index = 0;

  foreach ($gateways as $gw) 
  {
    $cart = Cart::get($gw->getKey());
    $items = $cart->getItems();
    if (!empty($items)) 
    {
      $show_fmv = ($gw->getKey() == 'asuf');
      $disable_checkout = ($membership_in_cart && $gw->getKey() == 'quikpay');
      $output .= theme($cart_theme, $cart, $purchaser, $disable_checkout, $index, $show_fmv);
      $all_empty = FALSE;
      $index++;
    }
  }
  
  if ($all_empty) 
  {
    $output .= '<p class="empty-cart" style="padding: 20px;">Your cart is currently empty. We suggest you look at our ';
    $output .= l('available training', 'programs');
    $output .= ', ';
    $output .= l('upcoming taskforce meetings', 'taskforces');
    $output .= ', or the resources in our ';
    $output .= l('Store', 'store');
    $output .= '!</p>';
  }
  
  return $output;
}

function cart_add_item($cart_items) 
{
  global $user;
  
  // Send anonymous user to login screen.
  if (!user_access('make payments')) 
  {
    drupal_set_message(t('Please log in before continuing with your purchase.'));
    drupal_goto('user', drupal_get_destination(), NULL, 307);
    return;
  }
  
  if (empty($cart_items)) 
  {
    drupal_set_message('Unable to add item to cart: item is unknown.');
    drupal_goto(CART_PAGE);
    return;
  }
  
  foreach ($cart_items as $item) 
  {
    // Check that this item is still valid.
    $permit = $item->canPurchase($user);
    if ($permit['can_purchase'] == FALSE) 
    {
      drupal_set_message('Unable to add item ' . $item->getTitle() . ': ' . $permit['message']);
      continue;
    }
    
    // Check for valid gateway.
    $gateway = $item->getGateway();
    if (!$gateway) 
    {
      drupal_set_message('Unable to add item ' . $item->getTitle() . '.');
      continue;
    }
    
    // Check if the user has already bought this.
    if (has_purchased($item->getNode(), $item->getType(), $user)) 
    {
      drupal_set_message('You have already purchased ' . $item->getTitle() . ', there is no need to re-purchase it. ' 
        . 'If you are experiencing difficulties, please contact us!');
      continue;
    }
    
    Cart::addItemStatic($item);
  }
  
  drupal_goto(CART_PAGE);
}

function cart_remove_item($cart_items) 
{
  if (empty($cart_items)) 
  {
    drupal_set_message('Unable to remove item from cart: unknown item.');
  } 
  else 
  {
    foreach ($cart_items as $item) 
    {
      Cart::removeItemStatic($item);
    }
  }
  
  drupal_goto(CART_PAGE);
}

function cart_select_user() 
{
  if (user_access('admin registration')) 
  {
    $email = $_POST['email'];
    $return = $_POST['return'];
    $purchaser = user_load(array('mail' => $email));

    if (empty($email)) 
    {
      drupal_set_message('You must enter a valid email address.');
    }
    else if (!$purchaser) 
    {
      drupal_set_message('No user exists with the email address ' . $email);
    } 
    else 
    {
      $_SESSION['checkout_purchaser'] = $purchaser->uid;
    }

    if ($return) 
    {
      drupal_goto($return);
    } 
    else 
    {
      drupal_goto(CART_PAGE);
    }
  }

  drupal_goto(CART_PAGE);
}
