<?php

/**
 * @file
 * Callbacks used by hook_commerce_payment_method_info().
 */

/**
 * Payment method callback: settings form.
 */
function commerce_cybersource_sawm_settings_form($settings = array()) {
  $settings = (array) $settings + array(
    'access_key' => '',
    'profile_id' => '',
    'secret_key' => '',
    'transaction_mode' => 'test',
    'transaction_type' => COMMERCE_CYBERSOURCE_SAWM_TRANSACTION_SALE,
    'payment_method' => 'card',
    'locale' => 'en-US',
    'checkout_button' => t('Complete checkout'),
    'cardonfile' => '0',
  );

  $form['profile_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile ID'),
    '#required' => TRUE,
    '#description' => t('CyberSource secure acceptance profile ID from the "General Settings" page of your CyberSource Secure Acceptance profile.'),
    '#default_value' => $settings['profile_id'],
  );
  $form['access_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Access key'),
    '#required' => TRUE,
    '#description' => t('First, shorter, 42-character component of the security key generated in the Secure Acceptance profile section titled "Security Keys".'),
    '#default_value' => $settings['access_key'],
  );
  $form['secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret key'),
    '#required' => TRUE,
    '#description' => t('Second, longer, 256-character component of the security key generated in the Secure Acceptance profile section titled "Security Keys".'),
    '#default_value' => $settings['secret_key'],
    '#size' => 256,
    '#maxlength' => 256,
  );
  $form['transaction_mode'] = array(
    '#type' => 'select',
    '#title' => t('Transaction mode'),
    '#description' => t('Transaction mode used for processing orders.'),
    '#options' => array(
      'test' => t('Test'),
      'live' => t('Live'),
    ),
    '#multiple' => FALSE,
    '#default_value' => $settings['transaction_mode'],
  );
  $form['transaction_type'] = array(
    '#type' => 'select',
    '#title' => t('Transaction type'),
    '#options' => array(
      COMMERCE_CYBERSOURCE_SAWM_TRANSACTION_SALE => t('Capture funds'),
      COMMERCE_CYBERSOURCE_SAWM_TRANSACTION_AUTH => t('Authorize funds'),
      /*
      Using these options dynamically seems more appropriate.
      COMMERCE_CYBERSOURCE_SAWM_TRANSACTION_CREATE_TOKEN => t('Create payment token'),
      COMMERCE_CYBERSOURCE_SAWM_TRANSACTION_AUTH_CREATE_TOKEN => t('Authorize funds and create payment token'),
      COMMERCE_CYBERSOURCE_SAWM_TRANSACTION_SALE_CREATE_TOKEN => t('Capture funds and create payment token'),
      COMMERCE_CYBERSOURCE_SAWM_TRANSACTION_UPDATE_TOKEN => t('Update payment token'),
      COMMERCE_CYBERSOURCE_SAWM_TRANSACTION_AUTH_UPDATE_TOKEN => t('Authorize funds and update payment token'),
      COMMERCE_CYBERSOURCE_SAWM_TRANSACTION_SALE_UPDATE_TOKEN => t('Capture funds and update payment token'),
      */
    ),
    '#multiple' => FALSE,
    '#default_value' => $settings['transaction_type'],
  );
  /*
  Secure Acceptance documentation references "27 languages for localization
  purposes", but lists far more codes than that, and only general 24 languages.

  The locale API field is required for submission.
  @code
  <input type="hidden" name="locale" value="en-us">
  @endcode
  @link http://apps.cybersource.com/library/documentation/dev_guides/Secure_Acceptance_WM/Secure_Acceptance_WM.pdf CyberSource Secure Acceptance Web/Mobile September 2013, Page 31, "Localization" @endlink
  */
  $form['locale'] = array(
    '#type' => 'select',
    '#title' => t('Locale'),
    '#options' => array(
      'ar-XN' => t('Arabic'),
      'km-KH' => t('Cambodia'),
      'zh-HK' => t('Chinese - Hong Kong'),
      'zh-MO' => t('Chinese - Maco'),
      'zh-CN' => t('Chinese - Mainland'),
      'zh-SG' => t('Chinese - Singapore'),
      'zh-TW' => t('Chinese - Taiwan'),
      'cz-CZ' => t('Czech'),
      'nl-nl' => t('Dutch'),
      'en-US' => t('English - American'),
      'en-AU' => t('English - Australia'),
      'en-GB' => t('English - Britain'),
      'en-CA' => t('English - Canada'),
      'en-IE' => t('English - Ireland'),
      'en-NZ' => t('English - New Zealand'),
      'fr-FR' => t('French'),
      'fr-CA' => t('French - Canada'),
      'de-DE' => t('German'),
      'de-AT' => t('German - Austria'),
      'hu-HU' => t('Hungary'),
      'id-ID' => t('Indonesian'),
      'it-IT' => t('Italian'),
      'ja-JP' => t('Japanese'),
      'ko-KR' => t('Korean'),
      'lo-LA' => t("Lao People's Democratic Republic"),
      'ms-MY' => t('Malaysian Bahasa'),
      'tl-PH' => t('Philippines Tagalog'),
      'pl-PL' => t('Polish'),
      'pt-BR' => t('Portuguese - Brazil'),
      'ru-RU' => t('Russian'),
      'sk-SK' => t('Slovakian'),
      'es-ES' => t('Spanish'),
      'es-AR' => t('Spanish - Argentina'),
      'es-CL' => t('Spanish - Chile'),
      'es-CO' => t('Spanish - Colombia'),
      'es-MX' => t('Spanish - Mexico'),
      'es-PE' => t('Spanish - Peru'),
      'es-US' => t('Spanish - American'),
      'tam'   => t('Tamil'),
      'th-TH' => t('Thai'),
      'tr-TR' => t('Turkish'),
      'vi-VN' => t('Vietnamese'),
    ),
    '#default_value' => $settings['locale'],
  );
  $form['payment_method'] = array(
    '#type' => 'select',
    '#options' => array('card' => t('Card'), 'echeck' => t('eCheck')),
    '#title' => t('Payment method'),
    '#default_value' => $settings['payment_method'],
  );
  $form['checkout_button'] = array(
    '#type' => 'textfield',
    '#title' => t('Payment submit button text'),
    '#description' => t('Specify the text for the payment form submit button.'),
    '#default_value' => $settings['checkout_button'],
  );
  if (module_exists('commerce_cardonfile')) {
    $form['cardonfile'] = array(
      '#type' => 'radios',
      '#options' => array('0' => t('Disabled'), '1' => t('Enabled')),
      '#title' => t('Request and use payment tokens'),
      '#description' => t('If your CyberSource SA profile has Payment Tokenization and Recurring Billing or Secure Storage service enabled, this feature stores payment tokens for users to re-use payment cards. Failure to enable both payment tokenization and either recurring billing or secure storage service with CyberSource will cause payments to fail.'),
      '#default_value' => $settings['cardonfile'],
      // Disabled until it can be tested.
      '#access' => FALSE,
    );
  }
  return $form;
}

/**
 * Payment method callback: submit form validation.
 *
 * Makes sure the payment rule is configured before redirecting.
 *
 * @param array $payment_method
 *   An array containing CyberSource SAWM info hook values and user settings.
 * @param array $pane_form
 * @param array $pane_values
 * @param object $order
 * @param array $charge
 */
function commerce_cybersource_sawm_submit_form_validate($payment_method, $pane_form, $pane_values, $order, $charge) {
  if (empty($payment_method['settings']['profile_id']) || empty($payment_method['settings']['access_key']) || empty($payment_method['settings']['secret_key'])) {
    drupal_set_message(t('The CyberSource payment method is missing !essential_configuration. Access the CyberSource Business Center at https://ebctest.cybersource.com/ebctest/login/Login.do to find required information.', array('!essential_configuration' => 'admin/commerce/config/payment-methods')), 'error');
    return FALSE;
  }
}

/**
 * Payment method callback.
 *
 * Builds an array of form fields for sending a POST to CyberSource.
 *
 * @return array
 *   Form fields for a POST to CyberSource.
 */
function commerce_cybersource_sawm_redirect_form($form, &$form_state, $order, $payment_method) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

  /*
  Required fields are listed first except for the signature, which is a hash of
  and can't be set until all the values of other fields are in place.
  */

  // Required. Access key generated in the Business Center SA profile.
  $form['access_key'] = array(
    '#type' => 'hidden',
    '#value' => $payment_method['settings']['access_key'],
  );

  // Required. Currency should be in ISO format.
  $currency_code = $order_wrapper->commerce_order_total->currency_code->value();
  if (empty($currency_code)) {
    $currency_code = commerce_default_currency();
  }
  $form['currency'] = array(
    '#type' => 'hidden',
    '#value' => $currency_code,
  );

  // Required. Add the charge amount if this is an auth or sale transaction.
  $amount = $order_wrapper->commerce_order_total->amount->value();
  // Allow other modules to alter the transaction amount.
  drupal_alter('commerce_cybersource_sawm_amount', $amount);

  // Should be greater than or equal to zero and include tax.
  $form['amount'] = array(
    '#type' => 'hidden',
    '#value' => number_format(commerce_currency_amount_to_decimal($amount, $currency_code), 2, '.', ''),
  );
  // Required. Language code, with country variant in ISO format, e.g. en-us.
  $form['locale'] = array(
    '#type' => 'hidden',
    '#value' => $payment_method['settings']['locale'],
  );
  // Required. See General Settings in the Secure Acceptance profile.
  $form['profile_id'] = array(
    '#type' => 'hidden',
    '#value' => $payment_method['settings']['profile_id'],
  );
  /*
  Required.
  The uniqid() function is not a UUID, but CyberSource's demo script uses it.
  Since they're not looking for a genuine UUID, we'll send the transaction ID.

  The Commerce CyberSource SASOP module doesn't generate the transaction ID
  until CyberSource makes a request back to the override_custom_receipt_page
  because it uses the uniqid() function here and stores that as metadata on the
  order. By generating a transaction in Commerce before the redirect, the site
  owner can have a log of transactions that may help debug payment issues
  evidenced by having a bunch of pending transactions on an order.
  */
  $transaction = commerce_payment_transaction_new('cybersource_sawm', $order->order_id);
  $transaction->instance_id = $payment_method['instance_id'];
  $transaction->remote_id = '';
  // An order amount of $1.00 probably shows here as simply 100.
  $transaction->amount = $amount;
  // Default Commerce currency code value: USD.
  $transaction->currency_code = $currency_code;
  $transaction->status = COMMERCE_PAYMENT_STATUS_PENDING;
  $transaction->message = 'Initialized transaction';
  $transaction->message_variables = array();
  commerce_payment_transaction_save($transaction);

  $form['transaction_uuid'] = array(
    '#type' => 'hidden',
    '#value' => $transaction->transaction_id,
  );

  // Required. CyberSource recommends either an order or transaction ID here.
  $form['reference_number'] = array(
    '#type' => 'hidden',
    '#value' => $order->order_id,
  );

  /*
  Required.
  Date and time signature was generated. Must be in UTC date & time format.
  Used by CyberSource to detect duplicate transaction attempts.
  */
  $form['signed_date_time'] = array(
    '#type' => 'hidden',
    '#value' => gmdate("Y-m-d\TH:i:s\Z"),
  );

  /*
  Required.
  Possible values:
    authorization
    sale
    create_payment_token
    authorization,create_payment_token
    sale,create_payment_token
    authorization,update_payment_token
    sale,update_payment_token
  */
  $form['transaction_type'] = array(
    '#type' => 'hidden',
    '#value' => $payment_method['settings']['transaction_type'],
  );
  // Required. Value is set later. Seeding here for signed field array.
  $form['signed_field_names'] = array(
    '#type' => 'hidden',
  );
  // Required. The ideal case is to have no fields un-signed.
  // Fields submitted by Drupal, useless to CyberSource.
  if (user_is_anonymous()) {
    /*
    Drupal doesn't add a form_token for Anonymous on the redirect form.
    Telling CyberSource that we're sending it, then not sending it, causes
    CyberSource to throw an access denied mystery error.
    @link https://drupal.org/node/2121409 Checkout as anonymous doesn't work @endlink
    */
    $form['unsigned_field_names'] = array(
      '#type' => 'hidden',
      '#value' => 'form_build_id,form_id',
    );
  }
  else {
    $form['unsigned_field_names'] = array(
      '#type' => 'hidden',
      '#value' => 'form_build_id,form_id,form_token',
    );
  }
  /*
  Optional.
  The substring is required because the CyberSource API only accepts 15
  characters for IP address; IPv6 addresses are 45 characters in length.
  */
  $form['customer_ip_address'] = array(
    '#type' => 'hidden',
    '#value' => substr(ip_address(), 0, 15),
  );
  // Optional. Possible values: card, echeck. Otherwise use SA profile default.
  $form['payment_method'] = array(
    '#type' => 'hidden',
    '#value' => $payment_method['settings']['payment_method'],
  );
  // Optional. Overrides the custom receipt profile setting in the SA profile.
  $form['override_custom_receipt_page'] = array(
    '#type' => 'hidden',
    '#value' => url('cybersource_sawm/reply', array('absolute' => TRUE)),
  );
  // Optional. Customer email.
  if (!empty($order->mail)) {
    $form['bill_to_email'] = array(
      '#type' => 'hidden',
      '#value' => $order->mail,
    );
  }

  // Prepare the billing address for use in the request.
  $billing_address = $order_wrapper->commerce_customer_billing->commerce_customer_address->value();

  if (!empty($billing_address) && is_array($billing_address)) {
    // If there is no first_name field, break apart the name_line field.
    if (empty($billing_address['first_name'])) {
      $name_parts = explode(' ', $billing_address['name_line']);
      $billing_address['first_name'] = array_shift($name_parts);
      $billing_address['last_name'] = implode(' ', $name_parts);
    }

    // Optional. First name.
    if (!empty($billing_address['first_name'])) {
      $form['bill_to_forename'] = array(
        '#type' => 'hidden',
        '#value' => $billing_address['first_name'],
      );
    }
    // Optional. Last name.
    if (!empty($billing_address['last_name'])) {
      $form['bill_to_surname'] = array(
        '#type' => 'hidden',
        '#value' => $billing_address['last_name'],
      );
    }
    // Optional. Company name.
    if (!empty($billing_address['organisation_name'])) {
      $form['bill_to_company_name'] = array(
        '#type' => 'hidden',
        '#value' => $billing_address['organisation_name'],
      );
    }
    // Optional. Address line 1.
    if (!empty($billing_address['thoroughfare'])) {
      $form['bill_to_address_line1'] = array(
        '#type' => 'hidden',
        '#value' => $billing_address['thoroughfare'],
      );
    }
    // Optional. Address line 2.
    if (!empty($billing_address['premise'])) {
      $form['bill_to_address_line2'] = array(
        '#type' => 'hidden',
        '#value' => $billing_address['premise'],
      );
    }
    // Optional.
    if (!empty($billing_address['locality'])) {
      $form['bill_to_address_city'] = array(
        '#type' => 'hidden',
        '#value' => $billing_address['locality'],
      );
    }
    // Optional. @link https://drupal.org/node/2112947 UK optional state @endlink
    if (!empty($billing_address['administrative_area'])) {
      $form['bill_to_address_state'] = array(
        '#type' => 'hidden',
        '#value' => $billing_address['administrative_area'],
      );
    }
    // Optional.
    if (!empty($billing_address['country'])) {
      $form['bill_to_address_country'] = array(
        '#type' => 'hidden',
        '#value' => $billing_address['country'],
      );
    }
    // Optional.
    if (!empty($billing_address['postal_code'])) {
      $form['bill_to_address_postal_code'] = array(
        '#type' => 'hidden',
        '#value' => $billing_address['postal_code'],
      );
    }
  }
  // Optional, helpful for sorting transactions in Business Center.
  $form['merchant_defined_data5'] = array(
    '#type' => 'hidden',
    '#value' => substr(variable_get('site_name', 'Drupal'), 0, 100),
  );

  /*
  Commerce Kickstart doesn't implement a user profile phone field.
  @code
  $form['bill_to_phone'] = array(
    '#type' => 'hidden',
    '#value' => ?,
  );
  @endcode
  */

  // Send line items. CyberSource limits items listed on the invoice to 0-49.
  $send_line_items = 0;
  for ($i = 0, $j = count($order->commerce_line_items['und']); $i < $j && $i < 50; $i++) {
    $line_item = commerce_line_item_load($order->commerce_line_items['und'][$i]['line_item_id']);

    if (isset($line_item->commerce_unit_price['und'][0]['amount'])) {
      $amount = commerce_currency_amount_to_decimal($line_item->commerce_unit_price['und'][0]['amount'], $line_item->commerce_unit_price['und'][0]['currency_code']);
      // Supporting known tax modules so tax is sent as tax instead of line.
      if (in_array($line_item->type, array('avatax', 'exactor_calc'))) {
        $form['tax_amount'] = array(
          '#type' => 'hidden',
          '#value' => $amount,
        );
        continue;
      }

      // Handle common line item data, as long as the amount is greater than zero. Cybersource does not currently allow
      // sending of negative amount line items.
      if ($amount >= 0) {
        $send_line_items++;
        $form['item_' . $i . '_unit_price'] = array(
          '#type' => 'hidden',
          '#value' => $amount,
        );
        $form['item_' . $i . '_quantity'] = array(
          '#type' => 'hidden',
          '#value' => (int)$line_item->quantity,
        );
        $form['item_' . $i . '_sku'] = array(
          '#type' => 'hidden',
          '#value' => $line_item->line_item_label,
        );

        // Handle product data.
        if (isset($line_item->commerce_product['und'][0]['product_id'])) {
          $product = commerce_product_load($line_item->commerce_product['und'][0]['product_id']);
          $form['item_' . $i . '_name'] = array(
            '#type' => 'hidden',
            '#value' => $product->title,
          );
        }
      }
    }
  }

  // Add "line_item_count" field if we are sending any line items.
  if ($send_line_items > 0) {
    $form['line_item_count'] = array(
      '#type' => 'hidden',
      '#value' => $send_line_items
    );
  }

  if (module_exists('commerce_cardonfile') && !empty($payment_method['settings']['cardonfile'])) {
    $cardsonfile = commerce_cardonfile_load_multiple_by_uid($order->uid, $order->data['payment_method'], TRUE);
    if (isset($order->data['cybersource_sawm']['cardonfile']) && $order->data['cybersource_sawm']['cardonfile'] == 'new') {
      $form['transaction_type']['#value'] .= ',create_payment_token';
    }
    elseif (!empty($cardsonfile)) {
      $form['transaction_type']['#value'] .= ',update_payment_token';
      $form['payment_token'] = array(
        '#type' => 'hidden',
        /*
        @todo
        This is the wrong #value to set. After I figure out how to get
        CyberSource to let me test tokens, then I can save one, then load it
        and see what the value of this would be to know what part of it to set.
        */
        '#value' => $cardsonfile,
      );
    }
  }

  /*
  All fields should be added to $form by now so they can be signed.
  The signed_field_names is a required field and should list itself.
  */
  $signed_field_names_list = implode(',', array_keys($form));
  $form['signed_field_names']['#value'] = $signed_field_names_list;

  /*
  Add the signature field of signed name value pairs.
  Generated as SHA256 base64 using the secret key.
  */
  $form['signature'] = array(
    '#type' => 'hidden',
    '#value' => commerce_cybersource_sawm_sign($form, $payment_method['settings']['secret_key']),
  );

  // Set the form action to the appropriate CyberSource URL.
  switch ($payment_method['settings']['transaction_mode']) {
    case 'live':
      $url = COMMERCE_CYBERSOURCE_SAWM_LIVE_TRANSACTION_SERVER;
      break;

    case 'test':
    default:
      $url = COMMERCE_CYBERSOURCE_SAWM_TEST_TRANSACTION_SERVER;
  }

  $form['#action'] = $url;

  // Allow other modules an opportunity to add to or alter the transaction data.
  drupal_alter('commerce_cybersource_sawm_transaction_data', $form);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Redirect for payment'),
  );

  return $form;
}

/**
 * Returns a signed string of parameters.
 *
 * @param array $data
 *   The array of form fields to be submitted to CyberSource.
 * @param array $secret_key
 *   The secret key configured as part of the payment method rule.
 *
 * @return string
 *   A SHA256 hmac of data values hashed with the secret key.
 */
function commerce_cybersource_sawm_sign($data, $secret_key) {
  foreach ($data as $key => $value) {
    $data_to_sign[] = $key . "=" . $value['#value'];
  }
  return _commerce_cybersource_sawm_hash($data_to_sign, $secret_key);
}
