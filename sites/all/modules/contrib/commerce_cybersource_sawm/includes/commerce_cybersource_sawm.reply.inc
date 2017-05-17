<?php

/**
 * @file
 * Verify CyberSource reply POST and update relevant transactions.
 */

/**
 * Callback function for posted CyberSource SAWM payment response.
 */
function commerce_cybersource_sawm_reply() {
  if (isset($_POST['req_reference_number']) && is_numeric($_POST['req_reference_number'])) {
    $order = commerce_order_load(check_plain($_POST['req_reference_number']));
  }
  else {
    watchdog('commerce_cybersource_sawm', 'Invalid reference number.');
    return;
  }

  if (isset($_POST['req_transaction_uuid']) && is_numeric($_POST['req_transaction_uuid'])) {
    $transaction = commerce_payment_transaction_load(check_plain($_POST['req_transaction_uuid']));
  }
  else {
    watchdog('commerce_cybersource_sawm', 'Invalid transaction UUID.');
    return;
  }

  if (commerce_cybersource_sawm_reply_validate($order, $transaction) !== FALSE) {
    // Perform any submit functions if necessary.
    commerce_cybersource_sawm_update_transaction($order, $transaction);
  }
  else {
    // Otherwise display the failure message and send the customer back to
    // the order payment page.
    $order = commerce_order_status_update($order, 'checkout_review');
    drupal_set_message(t('Payment failed at the payment server. Please review your information and try again. If issues persist please contact your issuing bank.'), 'error');
  }
  drupal_goto(commerce_checkout_order_uri($order));
}

/**
 * Validate user's arrival at the success page.
 *
 * If necessary, move the user back to the previous page.
 *
 * @return bool
 *   Returns TRUE if the signature for signed fields is valid, otherwise FALSE.
 */
function commerce_cybersource_sawm_reply_validate($order, $transaction) {
  // Validate the returned data against its signature.
  if (!commerce_cybersource_sawm_verify_callback($transaction)) {
    watchdog(
      'commerce_cybersource_sawm',
      'Order @order_number with remote id: @remote_id has failed signature validation.',
      array(
        '@order_number' => $order->order_id,
        '@remote_id' => check_plain($_POST['transaction_id']),
      )
    );
    return FALSE;
  }
  return TRUE;
}

/**
 * Validate data returned from CyberSource is not forged.
 *
 * @param object $transaction
 *   Need enough information about the transaction to be able to load the value
 *   of the secret key to hash the fields in the POST.
 *
 * @return bool
 *   Returns TRUE if the signature hash sent from CyberSource is equal to the
 *   hmac of the signed_field_names with the secret key from the Secure
 *   Acceptance profile, otherwise FALSE.
 */
function commerce_cybersource_sawm_verify_callback($transaction) {
  $payment_method = commerce_payment_method_instance_load($transaction->instance_id);

  // Apparently, transactions can get this far with no secret_key set.
  if (isset($payment_method['settings']['secret_key'])) {
    if (isset($_POST['signed_field_names'])) {
      if (isset($_POST['signature'])) {
        $fields = explode(',', $_POST['signed_field_names']);

        foreach ($fields as $field) {
          $data_to_sign[] = $field . "=" . $_POST[$field];
        }
        $signed_string = _commerce_cybersource_sawm_hash($data_to_sign, $payment_method['settings']['secret_key']);
        return ($signed_string == $_POST['signature']);
      }
      else {
        watchdog('commerce_cybersource_sawm', 'Reply POST had no signature.');
      }
    }
    else {
      watchdog('commerce_cybersource_sawm', 'Reply POST had no signed field names.');
    }
  }
  else {
    watchdog('commerce_cybersource_sawm', 'The secret key is not setup.');
  }
  return FALSE;
}

/**
 * Save the transaction information returned from CyberSource.
 */
function commerce_cybersource_sawm_update_transaction($order, $transaction) {
  // Coder module wants $_POST values to be filtered.
  $decision = check_plain($_POST['decision']);
  $message = check_plain($_POST['message']);
  $currency = check_plain($_POST['req_currency']);
  $transaction_uuid = check_plain($_POST['req_transaction_uuid']);

  $transaction->payload = $_POST;
  $transaction->remote_status = $decision;

  switch (strtoupper($decision)) {
    case 'ACCEPT':
      if (module_exists('commerce_cardonfile') && isset($transaction->payload['payment_token'])) {
        // Don't save cards for anonymous, unauthenticated users.
        if ($order->uid == 0) {
          watchdog('commerce_cybersource_sawm', 'Aborting order @id cardonfile for anonymous.', array('@id' => $order->order_id), WATCHDOG_DEBUG);
          return FALSE;
        }

        $card_data = array(
          'uid' => $order->uid,
          'payment_method' => $transaction->payment_method,
          'instance_id' => $transaction->instance_id,
          'remote_id' => $transaction->payload['payment_token'],
          'card_type' => _commerce_cybersource_sawm_card_type($transaction->payload['req_card_type']),
          'card_number' => substr(str_replace('x', '', $transaction->payload['req_card_number']), -4),
          'status' => '1',
        );

        $expiry_date = explode('-', $transaction->payload['req_card_expiry_date']);
        $card_data['card_exp_month'] = $expiry_date[0];
        $card_data['card_exp_year'] = $expiry_date[1];

        $card_entity = commerce_cardonfile_new($card_data);
        commerce_cardonfile_save($card_entity);
        if ($order->data['cybersource_sawm']['cardonfile']['cardonfile_instance_default']) {
          commerce_cardonfile_set_default_card($card_entity->card_id);
        }
      }

      $transaction->remote_id = check_plain($_POST['transaction_id']);
      $transaction->amount = commerce_currency_decimal_to_amount(check_plain($_POST['auth_amount']), $currency);

      // Get transaction type from post.
      $transaction_type = check_plain($_POST['req_transaction_type']);

      // Set transaction status to the appropriate status.
      switch ($transaction_type) {
        // Transaction type - Capture
        case 'sale':
          $transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
          $transaction->message = empty($message) ? t('The payment has completed/been captured.') : $message;
          break;
        // Transaction type  - Authorization
        case 'authorization';
          $transaction->status = COMMERCE_PAYMENT_STATUS_PENDING;
          $transaction->message = empty($message) ? t('The payment has been authorized.') : $message;
          break;
        // Transaction type - Authorization and Create payment token
        case 'authorization,create_payment_token':
          $transaction->status = COMMERCE_PAYMENT_STATUS_PENDING;
          $transaction->message = empty($message) ? t('The payment has been authorized and a payment token has been created.') : $message;
          break;
      }

      // Send the customer on to the next checkout page.
      commerce_order_status_update($order, 'checkout_complete');
      commerce_checkout_complete($order);
      break;

    case 'CANCEL':
    case 'DECLINE':
    case 'REVIEW':
    case 'ERROR':
      $transaction->remote_id = '';
      $transaction->amount = commerce_currency_decimal_to_amount($_POST['req_amount'], $currency);
      $transaction->status = COMMERCE_PAYMENT_STATUS_FAILURE;
      $transaction->message = empty($message) ? t('The payment has failed.') : $message;

      $order = commerce_order_status_update($order, 'checkout_review');
      watchdog(
        'commerce_cybersource_sawm',
        'Order @order_number with remote id: @remote_id has failed with the following code @code:@code_message',
        array(
          '@order_number' => $order->order_id,
          '@remote_id' => $transaction_uuid,
          '@code' => $decision,
          '@code_message' => $message . (empty($_POST['invalid_fields']) ? '' : ' - ' . check_plain($_POST['invalid_fields'])),
        )
      );
      break;
  }

  // Save the transaction information.
  commerce_payment_transaction_save($transaction);

  watchdog(
    'commerce_cybersource_sawm',
    'Order @order_number with remote id: @remote_id has been processed with the following code @code:@code_message',
    array(
      '@order_number' => $order->order_id,
      '@remote_id' => isset($_POST['transaction_id']) ? check_plain($_POST['transaction_id']) : $transaction_uuid,
      '@code' => $decision,
      '@code_message' => $message . (empty($_POST['invalid_fields']) ? '' : ' - ' . check_plain($_POST['invalid_fields'])),
    )
  );
}

function _commerce_cybersource_sawm_card_type($type_code) {
  // Card type strings are intentionally not translated because they will be
  // stored as strings when saved to cardonfile.
  $card_types = array(
    '001' => 'Visa',
    '002' => 'MasterCard',
    '003' => 'American Express',
    '004' => 'Discover',
    '005' => 'Diners Club',
    '006' => 'Carte Blanche',
    '007' => 'JCB',
    '014' => 'EnRoute',
    '021' => 'JAL',
    '024' => 'Maestro (UK Domestic)',
    '031' => 'Delta',
    '033' => 'Visa Electron',
    '034' => 'Dankort',
    '035' => 'Laser',
    '036' => 'Carte Bleue',
    '037' => 'Carta Si',
    '042' => 'Maestro (International)',
    '043' => 'GE Money UK card',
  );
  return $card_types[$type_code];
}
