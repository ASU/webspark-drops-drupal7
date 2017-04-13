<?php

/**
 * @file
 * Form callbacks for the membership entity commerce module.
 */

/**
 * Defines the form to create a membership order.
 *
 * We borrow liberally from commerce_cart_add_to_cart_form().
 */
function membership_entity_commerce_create_order_form(&$form, &$form_state, $form_id) {
  $membership = $form['#membership_entity'];

  // Load all active membership products.
  $product_ids = db_query('SELECT product_id FROM {commerce_product} WHERE type = :type AND status = 1', array(':type' => 'membership_entity_product'))->fetchAllAssoc('product_id');
  $products = commerce_product_load_multiple(array_keys($product_ids));
  foreach ($products as $product_id =>  $product) {
    if ($product->data['membership_entity_commerce']['type'] != $membership->type) {
      unset($products[$product_id]);
    }
  }
  $product_ids = array_keys($products);

  if (empty($products)) {
    return;
  }

  $form['#attributes']['class'][] = drupal_html_class('membership-entity-commerce-add-to-cart');
  $form['#attributes']['class'][] = drupal_html_class(commerce_cart_add_to_cart_form_id($product_ids));

  // Add the form id as a class for ajax replacement.
  $class = drupal_html_class($form['#form_id']);
  if (!in_array($class, $form['#attributes']['class'])) {
    $form['#attributes']['class'][] = $class;
  }

  $line_item = commerce_product_line_item_new(reset($products), 1, 0, array(), 'membership_entity_line_item');
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
  $form_state['line_item'] = $line_item;

  $qualifying_fields = array();
  $matching_products = array();
  $default_product = NULL;
  $attribute_names = array();
  $unchanged_attributes = array();

  foreach ($products as $product_id => $product) {
    $product_wrapper = entity_metadata_wrapper('commerce_product', $product);

    // If the form state contains a set of attribute data, use it to try
    // and determine the default product.
    $changed_attribute = NULL;

    if (!empty($form_state['values']['attributes'])) {
      $match = TRUE;

      // Set an array of checked attributes for later comparison against the
      // default matching product.
      if (empty($attribute_names)) {
        $attribute_names = (array) array_diff_key($form_state['values']['attributes'], array('product_select' => ''));
        $unchanged_attributes = $form_state['values']['unchanged_attributes'];
      }

      foreach ($attribute_names as $key => $value) {
        // If this is the attribute widget that was changed...
        if ($value != $unchanged_attributes[$key]) {
          // Store the field name.
          $changed_attribute = $key;

          // Clear the input for the "Select a product" widget now if it
          // exists on the form since we know an attribute was changed.
          unset($form_state['input']['attributes']['product_select']);
        }

        // If a field name has been stored and we've moved past it to
        // compare the next attribute field...
        if (!empty($changed_attribute) && $changed_attribute != $key) {
          // Wipe subsequent values from the form state so the attribute
          // widgets can use the default values from the new default product.
          unset($form_state['input']['attributes'][$key]);

          // Don't accept this as a matching product.
          continue;
        }

        if ($product_wrapper->{$key}->raw() != $value) {
          $match = FALSE;
        }
      }

      // If the changed field name has already been stored, only accept the
      // first matching product by ignoring the rest that would match. An
      // exception is granted for additional matching products that share
      // the exact same attribute values as the first.
      if ($match && !empty($changed_attribute) && !empty($matching_products)) {
        reset($matching_products);
        $matching_product = $matching_products[key($matching_products)];
        $matching_product_wrapper = entity_metadata_wrapper('commerce_product', $matching_product);

        foreach ($attribute_names as $key => $value) {
          if ($product_wrapper->{$key}->raw() != $matching_product_wrapper->{$key}->raw()) {
            $match = FALSE;
          }
        }
      }

      if ($match) {
        $matching_products[$product_id] = $product;
      }
    }
  }

  // Set the default product now if it isn't already set.
  if (empty($matching_products)) {
    // If a product ID value was passed in, use that product if it exists.
    if (!empty($form_state['values']['product_id']) && !empty($products[$form_state['values']['product_id']])) {
      $default_product = $products[$form_state['values']['product_id']];
    }
    elseif (empty($form_state['values']) && !empty($line_item_wrapper->commerce_product) && !empty($products[$line_item_wrapper->commerce_product->raw()])) {
      // If this is the first time the form is built, attempt to use the
      // product specified by the line item.
      $default_product = $products[$line_item_wrapper->commerce_product->raw()];
    }
    else {
      reset($products);
      $default_product = $products[key($products)];
    }
  }
  else {
    // If the product selector has a value, use that.
    if (!empty($form_state['values']['attributes']['product_select']) && !empty($products[$form_state['values']['attributes']['product_select']]) && in_array($products[$form_state['values']['attributes']['product_select']], $matching_products)) {
      $default_product = $products[$form_state['values']['attributes']['product_select']];
    }
    else {
      reset($matching_products);
      $default_product = $matching_products[key($matching_products)];
    }
  }

  $default_product_wrapper = entity_metadata_wrapper('commerce_product', $default_product);
  $form_state['default_product'] = $default_product;
  $line_item_wrapper->commerce_product->set($default_product);

  $membership_fields = field_info_instances('membership_entity', $membership->type);
  foreach (field_info_instances('commerce_product', 'membership_entity_product') as $field_name => $instance) {
    $field = field_info_field($field_name);
    if (commerce_cart_field_attribute_eligible($field) && commerce_cart_field_instance_is_attribute($instance)) {
      $commerce_cart_settings = commerce_cart_field_instance_attribute_settings($instance);
      switch ($commerce_cart_settings['attribute_widget']) {
        case 'checkbox':
          $widget_type = 'onoff';
          break;

        case 'radios':
          $widget_type = 'buttons';
          break;

        default:
          $widget_type = 'select';
      }
      $properties = _options_properties($widget_type, FALSE, TRUE, TRUE);
      $allowed_values = _options_get_options($field, $instance, $properties, 'commerce_product', $default_product);

      if (!empty($allowed_values)) {
        if (isset($membership_fields[$field_name])) {
          // Remove the matching membership field.
          $form[$field_name]['#access'] = FALSE;
        }

        $qualifying_fields[$field_name] = array(
          'field' => $field,
          'instance' => $instance,
          'commerce_cart_settings' => $commerce_cart_settings,
          'options' => $allowed_values,
          'weight' => $instance['widget']['weight'],
          'required' => $instance['required'],
          'description' => $instance['description'],
        );
      }
    }
  }

  // Add term length as an attribute.
  $term_options = $form['membership_term']['term']['#options'];
  $form['membership_term']['term']['#access'] = FALSE;
  $qualifying_fields['term'] = array(
    'field' => array(),
    'instance' => array(),
    'commerce_cart_settings' => array(
      'attribute_field' => TRUE,
      'attribute_widget' => 'radios',
      'attribute_widget_title' => $form['membership_term']['term']['#title'],
    ),
    'description' => $form['membership_term']['term']['#description'],
    'options' => $term_options,
    'weight' => 0,
    'required' => TRUE,
  );

  if (!empty($qualifying_fields)) {
    $used_options = array();
    $field_has_options = array();
    uasort($qualifying_fields, 'drupal_sort_weight');

    foreach ($qualifying_fields as $field_name => $data) {
      foreach ($products as $product_id => $product) {
        $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
        foreach ($used_options as $used_field_name => $unused) {
          if ($used_field_name == $field_name) {
            continue;
          }

          if (isset($form['attributes'][$used_field_name]['#default_value'])) {
            if ($product_wrapper->{$used_field_name}->raw() != $form['attributes'][$used_field_name]['#default_value']) {
              continue 2;
            }
          }
        }

        if ($product_wrapper->{$field_name}->raw() != NULL) {
          $field_has_options[$field_name] = TRUE;
        }

        $used_options[$field_name][] = $product_wrapper->{$field_name}->raw();
      }

      // If for some reason no options for this field are used, remove it
      // from the qualifying fields array.
      if (empty($field_has_options[$field_name]) || empty($used_options[$field_name])) {
        unset($qualifying_fields[$field_name]);
      }
      else {
        $options = array_intersect_key($data['options'], drupal_map_assoc($used_options[$field_name]));
        if (isset($form_state['values']['attributes'][$field_name]) && in_array($form_state['values']['attributes'][$field_name], array_keys($options))) {
          $default = $form_state['values']['attributes'][$field_name];
        }
        else {
          $default = $default_product_wrapper->{$field_name}->raw();
        }
        $form['attributes'][$field_name] = array(
          '#type' => $data['commerce_cart_settings']['attribute_widget'],
          '#title' => $data['commerce_cart_settings']['attribute_widget_title'],
          '#options' => $options,
          '#default_value' => $default,
          '#description' => $data['description'],
          '#weight' => $data['weight'],
          '#ajax' => array(
            'callback' => 'commerce_cart_add_to_cart_form_attributes_refresh',
          ),
        );

        if (!$data['required'] && in_array('', $used_options[$field_name])) {
          $form['attributes'][$field_name]['#empty_value'] = '';
        }

        $form['unchanged_attributes'][$field_name] = array(
          '#type' => 'value',
          '#value' => $default_product_wrapper->{$field_name}->raw(),
        );
      }
    }

    if (!empty($form['attributes'])) {
      $form['attributes'] += array(
        '#tree' => TRUE,
        '#prefix' => '<div class="attribute-widgets">',
        '#suffix' => '</div>',
        '#weight' => $form['actions']['#weight'] - 2,
      );
      $form['unchanged_attributes'] += array(
        '#tree' => TRUE,
      );

      // If the matching products array is empty, it means this is the first
      // time the form is being built. We should populate it now with
      // products that match the default attribute options.
      if (empty($matching_products)) {
        foreach ($products as $product_id => $product) {
          $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
          $match = TRUE;

          foreach (element_children($form['attributes']) as $field_name) {
            if ($product_wrapper->{$field_name}->raw() != $form['attributes'][$field_name]['#default_value']) {
              $match = FALSE;
            }
          }

          if ($match) {
            $matching_products[$product_id] = $product;
          }
        }
      }

      // Add a products selection if there are more than one matching products.
      if (count($matching_products) > 1) {
        $options = array();

        foreach ($matching_products as $product_id => $product) {
          $options[$product_id] = $product->title;
        }

        $form['attributes']['product_select'] = array(
          '#type' => 'select',
          '#title' => t('Select a product'),
          '#options' => $options,
          '#default_value' => $default_product->product_id,
          '#weight' => 40,
          '#ajax' => array(
            'callback' => 'commerce_cart_add_to_cart_form_attributes_refresh',
          ),
        );
      }

      $form['product_id'] = array(
        '#type' => 'hidden',
        '#value' => $default_product->product_id,
      );
    }
  }
  else {
    if (count($products) == 1) {
      $form['product_id'] = array(
        '#type' => 'hidden',
        '#value' => $default_product->product_id,
      );
    }
    else {
      $options = array();
      foreach ($products as $product_id => $product) {
        $options[$product_id] = $product->title;
      }

      $form['product_id'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => $default_product->product_id,
        '#weight' => 0,
        '#ajax' => array(
          'callback' => 'commerce_cart_add_to_cart_form_attributes_refresh',
        ),
      );
    }
  }

  $form['quantity'] = array(
    '#type' => 'value',
    '#value' => 1,
  );

  // Add the line item's fields to a container on the form.
  $form['line_item_fields'] = array(
    '#type' => 'fieldset',
    '#title' => $default_product->title,
    '#parents' => array('line_item_fields'),
    '#weight' => $form['actions']['#weight'] - 1,
    '#tree' => TRUE,
  );

  field_attach_form('commerce_line_item', $line_item, $form['line_item_fields'], $form_state);

  // Loop over the fields we just added and remove any that haven't been
  // marked for inclusion on this form.
  foreach (element_children($form['line_item_fields']) as $field_name) {
    $info = field_info_instance('commerce_line_item', $field_name, $line_item->type);
    $form['line_item_fields'][$field_name]['#commerce_cart_settings'] = commerce_cart_field_instance_access_settings($info);

    if (empty($form['line_item_fields'][$field_name]['#commerce_cart_settings']['field_access'])) {
      $form['line_item_fields'][$field_name]['#access'] = FALSE;
    }
  }

  // Add the select product information.
  $product_display = entity_view('commerce_product', array($default_product->product_id => $default_product), 'membership_entity_commerce');
  $form['line_item_fields']['product_display'] = $product_display;

  $form['#validate'][] = 'membership_entity_commerce_create_order_form_validate';
  $form['actions']['submit']['#value'] = user_access('administer memberships') ? t('Continue to checkout') : t('Add to cart');
  $form['actions']['submit']['#submit'][] = 'membership_entity_commerce_create_order_form_submit';

  // Do not allow products without a price to be purchased.
  $values = commerce_product_calculate_sell_price($form_state['default_product']);

  if (is_null($values) || is_null($values['amount']) || is_null($values['currency_code'])) {
    $form['actions']['submit']['#value'] = t('Product not available');
    $form['actions']['submit']['#attributes']['disabled'] = 'disabled';
    $form['actions']['submit']['#validate'] = array('commerce_cart_add_to_cart_form_disabled_validate');
  }
}

/**
 * Create order form validate handler.
 */
function membership_entity_commerce_create_order_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  $membership = $form['#membership_entity'];

  // If the attributes matching product selector was used, set the value of the
  // product_id field to match; this will be fixed on rebuild when the actual
  // default product will be selected based on the product selector value.
  if (!empty($values['attributes']['product_select'])) {
    form_set_value($form['product_id'], $values['attributes']['product_select'], $form_state);
  }

  // Since we are creating an order set the membership status to pending.
  form_set_value($form['membership_term']['status'], MEMBERSHIP_ENTITY_PENDING, $form_state);

  $membership_fields = field_info_instances('membership_entity', $membership->type);
  foreach ($values['attributes'] as $field_name => $value) {
    // Save membership fields for submit handlers.
    if (isset($membership_fields[$field_name])) {
      $field = field_info_field($field_name);

      // I'm going to assume all options list fields have a single column.
      $column = key($field['columns']);
      $language = field_language('membership_entity', $membership, $field_name);
      form_set_value($form[$field_name], array($language => array(array($column => $value))), $form_state);
    }
  }

  // Set the selected membership term length.
  form_set_value($form['membership_term']['term'], $values['attributes']['term'], $form_state);

  // Validate any line item fields that may have been included on the form.
  field_attach_form_validate('commerce_line_item', $form_state['line_item'], $form['line_item_fields'], $form_state);
}

/**
 * Form submit handler: create the membership order.
 */
function membership_entity_commerce_create_order_form_submit($form, &$form_state) {
  $values = &$form_state['values'];
  $membership = $form_state['membership_entity'];

  $product_id = $values['product_id'];
  $product = commerce_product_load($product_id);

  if (empty($form_state['line_item']->line_item_id)) {
    $line_item = commerce_product_line_item_new($product, $values['quantity'], 0, $form_state['line_item']->data, $form_state['line_item']->type);
    drupal_alter('commerce_product_calculate_sell_price_line_item', $line_item);

    // Remove line item field values the user didn't have access to modify.
    foreach ($values['line_item_fields'] as $field_name => $value) {
      if (empty($form['line_item_fields'][$field_name]['#commerce_cart_settings']['field_access'])) {
        unset($values['line_item_fields'][$field_name]);
      }
    }

    // Unset the line item field values array if it is now empty.
    if (empty($values['line_item_fields'])) {
      unset($values['line_item_fields']);
    }

    // Add field data to the line item.
    field_attach_submit('commerce_line_item', $line_item, $form['line_item_fields'], $form_state);

    // Add the membership term reference.
    $term = $form_state['membership_entity_term'];
    $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
    $line_item_wrapper->membership_entity_term_ref->set($term);
    $line_item_wrapper->save();

    rules_invoke_event('commerce_product_calculate_sell_price', $line_item);

    if (!is_null($line_item_wrapper->commerce_unit_price->value())) {
      if (user_access('administer commerce_order entities')) {
        $order = commerce_order_new($values['uid'], 'pending');
        commerce_order_save($order);

        // Add the line item to the order.
        $line_item_wrapper->order_id = $order->order_id;
        $line_item_wrapper->save();

        $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
        $order_wrapper->commerce_line_items[] = $line_item;
        $order_wrapper->save();

        $form_state['redirect'] = 'admin/commerce/orders/' . $order->order_id . '/edit';
      }
      else {
        // Add the product to the specified shopping cart.
        if (user_is_anonymous()) {
          // Save the new user account info for reference during checkout.
          $line_item = commerce_cart_product_add(0, $line_item, FALSE);
          $order = commerce_order_load($line_item->order_id);
          $order->mail = $values['user']['mail'];
          commerce_order_save($order);
          $form_state['line_item'] =$line_item;
        }
        else {
          $form_state['line_item'] = commerce_cart_product_add($values['uid'], $line_item, FALSE);
        }
        $form_state['redirect'] = 'cart';
      }
    }
    else {
      drupal_set_message(t('%title could not be added to your order.', array('%title' => $product->title)), 'error');
    }
  }
}
