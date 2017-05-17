<?php
/**
 * @file
 * Checkout pane callback functions.
 */

/**
 * Commerce checkout pane form builder callback.
 */
function commerce_registration_information_checkout_form($form, &$form_state, $checkout_pane, $order) {
  global $user;
  $pane_form = array();
  $show_form = FALSE;
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  // Determine if we should create a new entity or if the user has gone back in
  // the checkout process and we should load previously stored values from
  // either the checkout pane or from the order.
  $find_values = isset($form_state['values'][$checkout_pane['pane_id']]['register_entities']);
  $order_values = isset($order->data['register_entities']);
  $override_title = variable_get('commerce_registration_product_title', NULL);
  $hide_email = variable_get('commerce_registration_hide_email_logged_in', FALSE);
  $i = 0; // Main counter for all the registrations
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      continue;
    }
    $id = (int) $line_item_wrapper->commerce_product->product_id->value();
    if (commerce_registration_product_has_registration_field($id)
      && registration_status('commerce_product', $id, TRUE) == 1) {
      $show_form = TRUE;
      $product = $line_item_wrapper->commerce_product;
      $line_item_id = $line_item_wrapper->line_item_id->value();
      $quantity = (int) $line_item_wrapper->quantity->value();
      $prodkey = $line_item_id . 'prod-' . $product->sku->value();
      for ($k = 0; $k < $quantity; $k++) {
        // We add a single registration for the quantity of the product being
        // purchased/registered for.
        $label = $i + 1;
        $title_vars = array(
          '@product' => $product->title->value(),
          '@count' => $label,
        );
        $title = t('@product - Registrant #@count', $title_vars);
        if (!empty($override_title)) {
          $title = str_replace('[title]', $product->title->value(), $override_title);
          $title = str_replace('[index]', $label, $title);
        }
        $pane_form[$prodkey][$prodkey . '-reg-' . $i] = array(
          '#type' => 'fieldset',
          '#title' => $title,
          '#collapsible' => TRUE,
          '#tree' => TRUE,
          '#description' => variable_get('commerce_registration_registrant_help', ''),
        );
        $entity = NULL;
        $bundle = registration_get_entity_registration_type('commerce_product',
                    $product->value());
        if ($find_values &&
          isset($form_state['values'][$checkout_pane['pane_id']]['register_entities'][$prodkey][$i])) {
          // The entity exists already, so let's just load it from the
          // form_state.
          $entity = $form_state['values'][$checkout_pane['pane_id']]['register_entities'][$prodkey][$i];
        }
        elseif ($order_values && isset($order->data['register_entities'][$prodkey][$i])) {
          // The entity is not in form_state, but is in the order data, so we
          // load it from there instead.
          $entity = $order->data['register_entities'][$prodkey][$i];
        }
        else {
          // Entity doesn't exist, so we need to create a new registration.
          $entity = commerce_registration_create_product_registration(
            $line_item_wrapper->commerce_product->product_id->value(),
            $bundle,
            $order->order_id
          );
        }
        // -------------------------------------------------------------------------
        // All the following code can be deleted if we use the form builder from ER.
        // -------------------------------------------------------------------------
        $options = registration_access_people($entity);
        if ((count($options) == 0)
          || !registration_register_page_access('commerce_product', $product->value())) {
          $pane_form[$prodkey][$prodkey . '-reg-' . $i]['no_reg'] = array(
            '#markup' => t('You do not have permission to register for this item.'),
          );
          $pane_form[$prodkey][$prodkey . '-reg-' . $i]['no_reg_permission'] = array(
            '#type' => 'hidden',
            '#value' => TRUE,
          );
          return $pane_form;
        }
        $register_form = registration_form($pane_form, $form_state, $entity);
        // Copy fields from the registration form so we don't duplicate functionality.
        if (isset($register_form['who_message'])) {
          $pane_form[$prodkey][$prodkey . '-reg-' . $i]['who_message'] = $register_form['who_message'];
        }
        $pane_form[$prodkey][$prodkey . '-reg-' . $i]['register_for'] = $register_form['who_is_registering'];
        // Default value for select list if user has saved registration.
        if (!is_null($entity->registrant_type($user))) {
          $pane_form[$prodkey][$prodkey . '-reg-' . $i]['register_for']['#default_value'] = $entity->registrant_type($user);
        }
        $find_name = "registration_information[$prodkey][$prodkey-reg-$i][register_for]";
        $pane_form[$prodkey][$prodkey . '-reg-' . $i]['user'] = $register_form['user'];
        // Default value for user autocomplete if user has saved regitration by
        // proceeding forward/backward in the checkout process.
        if (!empty($entity->user_uid)) {
          $referenced_user = user_load($entity->user_uid);
          $pane_form[$prodkey][$prodkey . '-reg-' . $i]['user']['#default_value'] = $referenced_user->name;
        }
        $pane_form[$prodkey][$prodkey . '-reg-' . $i]['user']['#states'] = array(
          'visible' => array(
            ':input[name="' . $find_name . '"]' => array('value' => REGISTRATION_REGISTRANT_TYPE_USER),
          ),
        );
        $pane_form[$prodkey][$prodkey . '-reg-' . $i]['anon_mail'] = $register_form['anon_mail'];
        $pane_form[$prodkey][$prodkey . '-reg-' . $i]['anon_mail']['#states'] = array(
          'visible' => array(
            ':input[name="' . $find_name .'"]' => array('value' => REGISTRATION_REGISTRANT_TYPE_ANON),
          ),
        );
        $pane_form[$prodkey][$prodkey . '-reg-' . $i]['#parents'] = array(
          'registration_information',
          $prodkey,
          $prodkey . '-reg-' . $i
        );
        // Attach the entity's fields to the form.
        field_attach_form(
          'registration',
          $entity,
          $pane_form[$prodkey][$prodkey . '-reg-' . $i],
          $form_state
        );
        // -------------------------------------------------------------------------
        $pane_form['register_entities'][$prodkey][$i] = array(
          '#type' => 'value',
          '#value' => $entity,
        );
        // Update the total registration counter
        $i++;
      }
    }
  }

  if (!$show_form) {
    // No register enabled products, so go to next step of checkout process.
    $pane_form['no_reg_products'] = array(
      '#markup' => t('No information required. You may skip this page.'),
    );
  }

  // Allow other modules to alter the pane form.
  // Using hook_commerce_registration_information_checkout_form_alter().
  drupal_alter('commerce_registration_information_checkout_form', $pane_form, $form_state);
  return $pane_form;
}

/**
 * Commerce checkout pane form validation callback.
 */
function commerce_registration_information_checkout_form_validate($form, &$form_state, $checkout_pane, $order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $ret = TRUE;
  $i = 0; // Main counter for all the registrations
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      continue;
    }
    $id = (int) $line_item_wrapper->commerce_product->product_id->value();
    if (commerce_registration_product_has_registration_field($id)
      && registration_status('commerce_product', $id, TRUE) == 1) {
      $product = $line_item_wrapper->commerce_product;
      $line_item_id = $line_item_wrapper->line_item_id->value();
      $quantity = (int) $line_item_wrapper->quantity->value();
      $emails = array();
      $self_products = array();
      for ($k = 0; $k < $quantity; $k++) {
        $prodkey = $line_item_id . 'prod-' . $product->sku->value();
        // Delete the following when we use ER's validation handler.
        if (isset($form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['no_reg_permission'])) {
          form_set_error("registration_information][" . $prodkey . "]["
              . $prodkey . "-reg-" . $i . "][no_reg",
            t("Unable to continue, you are unable to register for this item. Please remove it from your cart."));
            $ret = FALSE;
          continue;
        }
        $entity = $form_state['values'][$checkout_pane['pane_id']]['register_entities'][$prodkey][$i];
        $type = $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['register_for'];
        $is_registered = FALSE;
        switch ($type) {
          case REGISTRATION_REGISTRANT_TYPE_ANON:
            $mail = $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['anon_mail'];
            $mail_is_required = $form['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['anon_mail']['#required'];
            if (registration_is_registered($entity, $mail)) {
              form_set_error(
                "registration_information][" . $prodkey . "]["
                    . $prodkey . "-reg-" . $i . "][anon_mail",
                  t("The email address entered is already registered for this item.")
              );
              $ret = FALSE;
            }
            elseif (in_array($mail, $emails)) {
              form_set_error(
                "registration_information][" . $prodkey . "]["
                  . $prodkey . "-reg-" . $i . "][anon_mail",
                t("Email addresses must be unique for each registrant."));
              $ret = FALSE;
            }
            else {
              // If email is not empty, or is set to required, then validate email address.
              if ((!empty($mail) || $mail_is_required) && !valid_email_address($mail)) {
                form_set_error(
                  "registration_information][" . $prodkey . "]["
                      . $prodkey . "-reg-" . $i . "][anon_mail",
                    t("You must provide a valid email address.")
                );
                $ret = FALSE;
              }
              else if (!empty($mail)) {
                $emails[] = $mail;
              }
            }
            break;
          case REGISTRATION_REGISTRANT_TYPE_USER:
            $account = user_load_by_name($form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['user']);
            if ($account !== FALSE) {
              if (registration_is_registered($entity, NULL, $account->uid)) {
                form_set_error(
                  "registration_information][" . $prodkey . "]["
                      . $prodkey . "-reg-" . $i . "][user",
                  t("That user is already registered for this item.")
                );
                $ret = FALSE;
              }
            }
            else {
              form_set_error(
                "registration_information][$prodkey][$prodkey-reg-$i][user",
                t("Cannot find a user by that username.")
              );
              $ret = FALSE;
            }
            break;
          case REGISTRATION_REGISTRANT_TYPE_ME:
            global $user;
            if (registration_is_registered($entity, NULL, $user->uid)) {
              form_set_error(
                "registration_information][" . $prodkey . "]["
                    . $prodkey . "-reg-" . $i . "][register_for",
                  t("You are already registered for this item.")
              );
              $ret = FALSE;
            }
            if (isset($self_products[$product->product_id->value()])
              && $self_products[$product->product_id->value()] == $user->uid) {
              form_set_error("registration_information][" . $prodkey . "]["
                    . $prodkey . "-reg-" . $i . "][register_for",
                t("You cannot register yourself for the same item more than once."));
              $ret = FALSE;
            }
            else {
              // Set a flag that the current user is registering 'self' for
              // this product.
              $self_products[$product->product_id->value()] = $user->uid;
            }
            break;
        }
        // Let other modules do any field API validation if necessary.
        field_attach_form_validate(
          'registration',
          $entity,
          $form['registration_information'][$prodkey][$prodkey . '-reg-' . $i],
          $form_state
        );
        // Update the total registration counter
        $i++;
      }
    }
  }

  return $ret;
}

/**
 * Commerce checkout pane form submit callback.
 */
function commerce_registration_information_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  $order->data['register_entities'] = array();
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      continue;
    }
    $id = (int) $line_item_wrapper->commerce_product->product_id->value();
    if (commerce_registration_product_has_registration_field($id)
      && registration_status('commerce_product', $id, TRUE) == 1) {
      $product = $line_item_wrapper->commerce_product;
      $line_item_id = $line_item_wrapper->line_item_id->value();
      $quantity = (int) $line_item_wrapper->quantity->value();
      for ($i = 0; $i < $quantity; $i++) {
        $prodkey = $line_item_id . 'prod-' . $product->sku->value();
        if (isset($form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['no_reg_permission'])) {
          continue;
        }
        $entity = &$form_state['values'][$checkout_pane['pane_id']]['register_entities'][$prodkey][$i];
        $type = $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['register_for'];
        $is_registered = FALSE;
        switch ($type) {
          case REGISTRATION_REGISTRANT_TYPE_ANON:
            $entity->anon_mail = $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['anon_mail'];
            break;
          case REGISTRATION_REGISTRANT_TYPE_USER:
            $account = user_load_by_name($form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['user']);
            $entity->user_uid = $account->uid;
            break;
          case REGISTRATION_REGISTRANT_TYPE_ME:
            global $user;
            $entity->user_uid = $user->uid;
            break;
        }
        // Notify the field API that values were submitted.
        field_attach_submit(
          'registration',
          $entity,
          $form['registration_information'][$prodkey][$prodkey . '-reg-' . $i],
          $form_state
        );
        registration_save($entity);
        $order->data['register_entities'][$prodkey][$i] = $entity;
      }
    }
  }
  // Save the order since we added registration entities to the data array.
  commerce_order_save($order);
}

/**
 * Commerce checkout pane review callback.
 */
function commerce_registration_information_review($form, $form_state, $checkout_pane, $order) {
  $msg = '';
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $i = 0; // Main counter for all the registrations
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      continue;
    }
    $id = (int) $line_item_wrapper->commerce_product->product_id->value();
    if (commerce_registration_product_has_registration_field($id)
      && registration_status('commerce_product', $id, TRUE) == 1) {
      $product = $line_item_wrapper->commerce_product;
      $line_item_id = $line_item_wrapper->line_item_id->value();
      $quantity = (int) $line_item_wrapper->quantity->value();
      $msg .= '<em>' . $product->title->value() . ' ('
        . format_plural($quantity, '1 registration', '@count registrations')
        . '):</em><br />';
      for ($k = 0; $k < $quantity; $k++) {
        $prodkey = $line_item_id . 'prod-' . $product->sku->value();
        $entity = $order->data['register_entities'][$prodkey][$i];
        $l = $i + 1;
        $reg_wrapper = entity_metadata_wrapper('registration', $entity);
        $email = $reg_wrapper->mail->value();
        $msg .= "<hr><em><u>" . t("Registrant #@count", array('@count' => $l)) . "</u></em><br />";
        $msg .= "<strong>" . t("Email") . "</strong>: " . check_plain($email) . "<br />";
        $field_view = field_attach_view('registration', $entity, 'review_pane');
        $msg .= drupal_render($field_view);
        // Update the total registration counter
        $i++;
      }
    }
  }

  return $msg;
}

/**
 * Commerce checkout pane settings form builder.
 */
function commerce_registration_information_settings_form($checkout_pane) {
  $form = array();

  $form['commerce_registration_product_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Product Registration Title'),
    '#description' => t('The text to populate the fieldset label for a registrant\'s information.') . '<br>'
        . t('Available tokens are [title] for the product title, and [index] for a countable index value.'),
    '#default_value' => variable_get('commerce_registration_product_title', ''),
  );

  $form['commerce_registration_registrant_help'] = array(
    '#type' => 'textarea',
    '#title' => t('Product Registration Fieldset Help Text'),
    '#description' => t('The help text to display to the user entering registration information.'),
    '#default_value' => variable_get('commerce_registration_registrant_help', ''),
  );

  $form['commerce_registration_hide_email_logged_in'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide the Email field for logged in users'),
    '#default_value' => variable_get('commerce_registration_hide_email_logged_in', ''),
  );

  return $form;
}

/**
 * Helper function to create a new registration for a product.
 *
 * @param int $product_id
 * @param string $bundle
 * @param int $order_id
 *
 * @return RegistrationEntity
 */
function commerce_registration_create_product_registration($product_id, $bundle, $order_id) {
  global $user;
  $entity = entity_get_controller('registration')->create(array('type' => $bundle));
  $entity->registration_id = NULL;
  $entity->entity_type = 'commerce_product';
  $entity->entity_id = $product_id;
  $entity->created = REQUEST_TIME;
  $entity->updated = REQUEST_TIME;
  $entity->author_uid = $user->uid;
  $entity->order_id = $order_id;
  $entity->count = 1;
  return $entity;
}
