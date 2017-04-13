<?php
// $Id: 

/**
 * @file
 * Quikpay menu items.
 */

// Handles a complete sale reported by Real Time Payment Notification.
function quikpay_rtpn() { 

  // Default.
  $msg = "No data provided.";
  $post = $_POST;
  $get = $_GET;
  $method = "None";
  //Debug
  watchdog('quikpay', 'RTPN Page is hit.', array(), WATCHDOG_WARNING);

  if (empty($post) && empty($get)) {
    watchdog('quikpay', 'No data submitted to rtpn page.', array(), WATCHDOG_WARNING);
    return FALSE;
  }
  if (empty($post)) 
   {
 watchdog('quikpay', 'RTPN method is not used.', array(), WATCHDOG_WARNING);
  $msg = "No post data submitted";
   }
  else {
    $method = 'rtpn';
    watchdog('quikpay', 'Post data is submitted.', array(), WATCHDOG_WARNING);
    $msg .= "Processing data..";
    // Determine if we're operating with Test or Production values.
    $environ = quikpay_get_environ();
    $key = $environ['rtpn_key'];
    
    // Timestamp in milliseconds.
    $timestamp = quikpay_get_timestamp();
    // Values will be received as post. Should expect to get everything.
    $response = array(
      'transactionType' => $_POST['transactionType'],
      'transactionStatus' => $_POST['transactionStatus'],
      'transactionSource' => $_POST['transactionSource'],
      'transactionSourceRef' => $_POST['transactionSourceRef'],
      'transactionId' => $_POST['transactionId'],
      'originalTransactionId' => $_POST['originalTransactionId'],
      'transactionTotalAmount' => $_POST['transactionTotalAmount'],
      'transactionDate' => $_POST['transactionDate'],
      'transactionAcountType' => $_POST['transactionAcountType'],
      'transactionEffectiveDate' => $_POST['transactionEffectiveDate'],
      'transactionDescription' => $_POST['transactionDescription'],
      'transactionResultDate' => $_POST['transactionResultDate'],
      'transactionResultEffectiveDate' => $_POST['transactionResultEffectiveDate'],
      'transactionResultCode' => $_POST['transactionResultCode'],
      'transactionResultMessage' => $_POST['transactionResultMessage'],
      'orderNumber' => $_POST['orderNumber'],
      'orderType' => $_POST['orderType'],
      'orderName' => $_POST['orderName'],
      'orderDescription' => $_POST['orderDescription'],
      'orderAmount' => $_POST['orderAmount'], // TODO This an issue? amount or orderAmount?
      'orderFee' => $_POST['orderFee'],
      'orderDueDate' => $_POST['orderDueDate'],
      'orderAmountDue' => $_POST['orderAmountDue'],
      'orderBalance' => $_POST['orderBalance'],
      'orderCurrentStatusBalance' => $_POST['orderCurrentStatusBalance'],
      'orderCurrentStatusAmountDue' => $_POST['orderCurrentStatusAmountDue'],
      'payerType' => $_POST['payerType'],
      'payerIdentifier' => $_POST['payerIdentifier'],
      'payerFullName' => $_POST['payerFullName'],
      'actualPayerType' => $_POST['actualPayerType'],
      'actualPayerIdentifier' => $_POST['actualPayerIdentifier'],
      'actualPayerFullName' => $_POST['actualPayerFullName'],
      'accountHolderName' => $_POST['accountHolderName'],
      'streetOne' => $_POST['streetOne'],
      'streetTwo' => $_POST['streetTwo'],
      'city' => $_POST['city'],
      'state' => $_POST['state'],
      'zip' => $_POST['zip'],
      'country' => $_POST['country'],
      'daytimePhone' => $_POST['daytimePhone'],
      'eveningPhone' => $_POST['eveningPhone'],
      'email' => $_POST['email'],
      'userChoice1' => $_POST['userChoice1'],
      'userChoice2' => $_POST['userChoice2'],
      'userChoice3' => $_POST['userChoice3'],
      'userChoice4' => $_POST['userChoice4'],
      'userChoice5' => $_POST['userChoice5'],
      'userChoice6' => $_POST['userChoice6'],
      'userChoice7' => $_POST['userChoice7'],
      'userChoice8' => $_POST['userChoice8'],
      'userChoice9' => $_POST['userChoice9'],
      'userChoice10' => $_POST['userChoice10'],
      'timestamp' => $_POST['timestamp'],
    );
    }
   if (isset($_GET['orderNumber'])) {
      watchdog('quikpay', 'Get Redirect data is submitted.', array(), WATCHDOG_WARNING);
      $method = 'url';
      $environ = quikpay_get_environ();
      $key = $environ['rtpn_key'];
      $trans_variables = "transactionType,transactionStatus,transactionId,originalTransactionId,transactionTotalAmount,transactionDate,transactionAcountType,transactionEffectiveDate,transactionDescription,transactionResultDate,transactionResultEffectiveDate,transactionResultCode,transactionResultMessage,orderNumber,orderType,orderName,orderDescription,orderAmount,orderFee,orderAmountDue,orderDueDate,orderBalance,orderCurrentStatusBalance,orderCurrentStatusAmountDue";
      $response = array(
      'transactionType' => $_GET['transactionType'],
      'transactionStatus' => $_GET['transactionStatus'],
      'transactionId' => $_GET['transactionId'],
      'originalTransactionId' => $_GET['originalTransactionId'],
      'transactionTotalAmount' => $_GET['transactionTotalAmount'],
      'transactionDate' => $_GET['transactionDate'],
      'transactionAcountType' => $_GET['transactionAcountType'],
      'transactionEffectiveDate' => $_GET['transactionEffectiveDate'],
      'transactionDescription' => $_GET['transactionDescription'],
      'transactionResultDate' => $_GET['transactionResultDate'],
      'transactionResultEffectiveDate' => $_GET['transactionResultEffectiveDate'],
      'transactionResultCode' => $_GET['transactionResultCode'],
      'transactionResultMessage' => $_GET['transactionResultMessage'],
      'orderNumber' => $_GET['orderNumber'],
      'orderType' => $_GET['orderType'],
      'orderName' => $_GET['orderName'],
      'orderDescription' => $_GET['orderDescription'],
      'orderAmount' => $_GET['orderAmount'], 
      'orderFee' => $_GET['orderFee'],
      'orderDueDate' => $_GET['orderDueDate'],
      'orderAmountDue' => $_GET['orderAmountDue'],
      'orderBalance' => $_GET['orderBalance'],
      'orderCurrentStatusBalance' => $_GET['orderCurrentStatusBalance'],
      'orderCurrentStatusAmountDue' => $_GET['orderCurrentStatusAmountDue'],
      );
      $var = explode(",",$trans_variables);
      $key = $environ['rtpn_key'];
      foreach ($var as $param) {
            $$param = $_GET[$param];
            } 
     }
      else 
       {
  watchdog('quikpay', 'No data submitted to rtpn page.', array(), WATCHDOG_WARNING); 
  $msg = "No data provided";
        }
    if ($method != "None") 
   {
    // Convenience variables.
    $order_id = check_plain($response['orderNumber']);
    $transaction_id = check_plain($response['transactionId']);
    $transaction_result_code = check_plain($response['transactionResultCode']);
    $transaction_result_message = check_plain($response['transactionResultMessage']);
    // Reverse QuikPAY number handling.
    // TODO No divide by 100 ?
    //$transaction_total_amount = check_plain($response['transactionTotalAmount']) / 100; 
    $transaction_total_amount = check_plain($response['transactionTotalAmount']); 

    // Build a hash.
    if ($method == 'rtpn') 
     {
      $hash = md5(implode('', $response) . $key);
      $check_hash = $_POST['hash'];
     }
    else 
     {
      //$hash = md5($orderNumber.$orderType.$orderAmount.$key);
      $hash = $_GET['hash'];
      $check_hash = $_GET['hash'];
      }
    // Hash validation fails.
    if ($hash != $check_hash) { // Will also catch when no $_POST due to presence of $key.

      // If no match, set HTTP response code to anything but 200. So 418 it is.
      // This tells QuikPAY that there was a problem and an error report can be sent.
      //drupal_set_header("HTTP/1.1 418 I'm a teapot");
      drupal_add_http_header("Status", "418 I'm a teapot");

      if (is_numeric($order_id) && ($order_id > 0)) {

        // TODO Commerce version of this?
        //uc_order_comment_save($order_id, 0, t('QuikPAY Real Time Payment Notification failed. Could not validate response.'), 'admin');


        watchdog('quikpay', 'QuikPAY Real Time Payment Notification hash did not match for order # %order_id. Received hash %remote_hash and built %local_hash.', 
          array('%order_id' => $order_id, '%remote_hash' => check_plain($check_hash), '%local_hash' => $hash), WATCHDOG_NOTICE);
      }

      return t('Validation failed.');
    }

    
    // Debug
    //$response_data = '';
    //foreach ($_POST as $key => $value) {
    //  $response_data .= "$key => $value \r\n";
    //}
    //error_log($response_data, 0);
     global $base_url;
    watchdog('quikpay', 'Received QuikPay Real Time Payment Notification for order # %order_id. Result message: %result_msg', 
      array('%order_id' => $order_id, '%result_msg' => $transaction_result_message), WATCHDOG_NOTICE);

    // Determine whether to complete payment based on transactionResultMessage.
    // Maybe there's a better option, but this looks best for now. 
    switch ($transaction_result_message) {

      case 'Approved and completed':
      case 'This transaction has been approved.': // Success message in testing environ.
        // Pull the current order information
        $order = commerce_order_load($response['orderNumber']);
        $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
        $qp_payment = $order_wrapper->commerce_order_total->value();
        $payment_method = commerce_payment_method_load('quikpay');
        //Create new transaction for the order
        $trans = commerce_payment_transaction_new('quikpay', $order->order_id);
        $trans->currency_code = $qp_payment['currency_code'];
        $trans->instance_id = $order->data['payment_method'];
        $trans->amount = $transaction_total_amount;
        $trans->message = "Payment Confirmation Number: @paynum";
        $trans->message .= "<br />Result Code: @rescode";
        $trans->message_variables['@paynum'] = $transaction_id;
        $trans->message_variables['@rescode'] = $transaction_result_code;
    
        watchdog('quikpay', 'Transaction successful', array(), WATCHDOG_WARNING);
        $trans->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
        commerce_payment_transaction_save($trans);
        commerce_checkout_complete($order);
        rules_invoke_all('commerce_payment_order_paid_in_full', $order, $trans);
	global $user;
	$uid = $user->uid;
        $order_link = $base_url."/user/".$uid."/orders/".$orderNumber;
        $msg = $environ['success'];
	$msg .= "<br /><a href='$order_link'>View your order</a>";
	$msg .= "<br /><br /><a href='$base_url'>Return to the front page</a>";
         //$msg = "Payment was successful";	
        
        // LEGACY
        //$order = uc_order_load($order_id);
        //$context = array('revision' => 'formatted-original', 'location' => 'nelnet');
        //$options = array();//'sign' => FALSE);
        //$comment = t('QuikPAY transaction ID: @transaction_id', array('@transaction_id' => $transaction_id));
        //uc_payment_enter($order_id, 'nelnet', $transaction_total_amount, $order->uid, NULL, $comment);
        //uc_cart_complete_sale($order); 
        //uc_order_comment_save($order_id, 0, t('Payment of @amount submitted through QuikPAY.', 
        //  array('@amount' => uc_price($transaction_total_amount, $context, $options))), 
        //  'order', 'payment_received');
        //uc_order_comment_save($order_id, 0, t('QuikPAY Real Time Payment Notification reported a payment of @amount.', 
        //  array('@amount' => uc_price($transaction_total_amount, $context, $options))));

        // Empty cart
        // Triangulate our way to cart id (which is uid for authenticated users 
        // carts - the only users we should have) so we can empty it.
        // (An alternative way to get cart_id would be to send it for a roundtrip
        // through QuikPAY.)
        //$cart_id = db_result(db_query("SELECT uid FROM {uc_orders} WHERE order_id = %d", $order_id));
        //uc_cart_empty($cart_id); //db_query("DELETE FROM {uc_cart_products} WHERE cart_id = %d", $uid);

        break;

      default:
        
        // TODO Commerce version of this?
        //uc_order_comment_save($order_id, 0, t('Unrecognized transaction result message: @msg', 
        //  array('@msg' => $transaction_result_message)), 'admin');
        break;

    }

    // Let other modules do stuff here.
    // Hook signature mymodule_quikpay_order_save($transaction_result_message, $response, $order_id)
    module_invoke_all('quikpay_order_save', $transaction_result_message, $response, $order_id);

  }


return t('Payment Notification: ' . $msg);
}


