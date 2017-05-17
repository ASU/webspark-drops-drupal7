<?php
/**
 * @file
 * Commerce Registration modified validation and submit handlers for
 * registration settings for commerce products.
 */

/**
 * Registration settings form for product display nodes.
 */
function commerce_registration_node_registrations_settings_form($form, &$form_state, $type, $entity) {
  // Loop through all products on the entity and add the settings form to a
  // fieldset.
  form_load_include($form_state, 'inc', 'registration', 'includes/registration.forms');
  $form = array();
  if ($type == 'node') {
    $fields = field_read_fields(array('type' => 'registration'));
    foreach ($fields as $field) {
      if (isset($entity->{$field['field_name']})) {
        $form['settings'] = array(
          '#type' => 'container',
          '#tree' => TRUE,
        );
        $settings = registration_entity_settings('node', $entity->nid);
        $fieldset = 'node-' . $entity->nid;
        $form['settings'][$fieldset] = array(
          '#type' => 'fieldset',
          '#title' => t('Registration Settings for !node',
            array(
              '!node' => '<em>Node: ' . $entity->title . '</em>',
            )
          ),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
        );
        $addform = registration_entity_settings_form($form, $form_state, $settings, 'node', $entity);
        unset($addform['save']);
        $addform['status']['#weight'] = -10;
        $addform['capacity']['#weight'] = -9;
        $addform['reminder']['reminder_settings']['#states']['visible'] = array(
          ':input[name="settings[' . $fieldset . '][reminder][send_reminder]"]' => array(
            'checked' => TRUE,
          ),
        );
        $form['settings'][$fieldset] += $addform;
        $form['settings'][$fieldset]['reminder']['#parents'] = array('settings', $fieldset, 'reminder');
      }
    }
  }
  $fields = field_read_fields(array('type' => 'commerce_product_reference'));
  foreach ($fields as $field) {
    if (!empty($entity->{$field['field_name']})) {
      $settings = array();
      if (isset($form['settings'])) {
        $settings = $form['settings'];
      }
      $form['settings'] = $settings + array(
        '#type' => 'container',
        '#tree' => TRUE,
      );
      foreach ($entity->{$field['field_name']}['und'] as $product) {
        if (commerce_registration_product_has_registration_field($product['product_id'])) {
          $product = commerce_product_load($product['product_id']);
          $settings = registration_entity_settings('commerce_product', $product->product_id);
          $prod = 'commerce_product-' . check_plain($product->product_id);
          $form['settings'][$prod] = array(
            '#type' => 'fieldset',
            '#title' => t('Registration Settings for !product (@sku)',
              array(
                '!product' => '<em>Commerce Product: ' . $product->title . '</em>',
                '@sku' => $product->sku,
              )
            ),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
          );
          if (!function_exists('registration_entity_settings_form')) {
            module_load_include('inc', 'registration', 'includes/registration.forms');
          }
          $addform = registration_entity_settings_form($form, $form_state, $settings, 'commerce_product', $product);
          unset($addform['save']);
          $addform['status']['#weight'] = -10;
          $addform['capacity']['#weight'] = -9;
          $addform['reminder']['reminder_settings']['#states']['visible'] = array(
            ':input[name="settings[' . $prod . '][reminder][send_reminder]"]' => array(
              'checked' => TRUE,
            ),
          );
          $form['settings'][$prod] += $addform;
          $form['settings'][$prod]['reminder']['#parents'] = array('settings', $prod, 'reminder');
        }
      }
    }
  }
  if (empty($form)) {
    list($entity_id) = entity_extract_ids($type, $entity);
    $settings = registration_entity_settings($type, $entity_id);
    $form = registration_entity_settings_form($form, $form_state, $settings, $type, $entity);
    $form['#submit'] = array('registration_entity_settings_form_submit');
    $form['#validate'] = array('registration_entity_settings_form_validate');
  }
  else {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save Settings'),
      '#validate' => array('commerce_registration_node_registrations_settings_form_validate'),
      '#submit' => array('commerce_registration_node_registrations_settings_form_submit'),
    );
  }
  return $form;
}

/**
 * Registration settings form validation for product display nodes.
 */
function commerce_registration_node_registrations_settings_form_validate($form, &$form_state) {
  foreach ($form_state['values']['settings'] as $id => $settings) {
    list($type, $id) = explode('-', $id);
    $temp_form_state = array(
      'entity' => array(
        'entity_id' => $id,
        'entity_type' => $type,
      ),
      'values' => $settings,
    );
    registration_entity_settings_form_validate($form, $temp_form_state);
  }
}

/**
 * Registration settings form submission for product display nodes.
 */
function commerce_registration_node_registrations_settings_form_submit($form, &$form_state) {
  foreach ($form_state['values']['settings'] as $id => $settings) {
    list($type, $id) = explode('-', $id);
    $temp_form_state = array(
      'entity' => array(
        'entity_id' => $id,
        'entity_type' => $type,
      ),
      'values' => $settings,
    );
    registration_entity_settings_form_submit(array(), $temp_form_state);
  }
}

/**
 * Registration broadcast form for product display nodes.
 */
function commerce_registration_registrations_broadcast_form($form, &$form_state, $type, $entity) {
  // Loop through all products on the entity and add the broadcast form to a
  // fieldset.
  form_load_include($form_state, 'inc', 'registration', 'includes/registration.forms');
  $form = array();
  $all = array('all' => 'All Registrants');
  $products = array();
  if ($type == 'node') {
    $fields = field_read_fields(array('type' => 'registration'));
    foreach ($fields as $field) {
      if (isset($entity->{$field['field_name']})) {
        $products['node-' . $entity->nid] = t('Node: !title', array('!title' => $entity->title));
      }
    }
  }
  $fields = field_read_fields(array('type' => 'commerce_product_reference'));
  foreach ($fields as $field) {
    if (isset($entity->{$field['field_name']})) {
      foreach ($entity->{$field['field_name']}[LANGUAGE_NONE] as $product) {
        if (commerce_registration_product_has_registration_field($product['product_id'])) {
          $product = commerce_product_load($product['product_id']);
          $products['commerce_product-' . $product->product_id] = t('Commerce Product: !title', array('!title' => $product->title));
        }
      }
    }
  }
  if (empty($products)) {
    $form = registration_registrations_broadcast_form($form, $form_state, $type, $entity);
    $form['#submit'] = array('registration_registrations_broadcast_form_submit');
  }
  else {
    $form['product'] = array(
      '#type' => 'select',
      '#options' => $all + $products,
      '#title' => t('Select One'),
      '#description' => t('The email message will be sent to all registrants for this item.'),
      '#required' => TRUE,
    );
    $form += registration_registrations_broadcast_form($form, $form_state, $type, $entity);
    $form['#submit'] = array('commerce_registration_registrations_broadcast_form_submit');
  }
  return $form;
}

/**
 * Broadcast email form submit handler.
 */
function commerce_registration_registrations_broadcast_form_submit($form, &$form_state) {
  $id = $form_state['values']['product'];
  $subject = $form_state['values']['subject'];
  $message = $form_state['values']['message'];
  if ($id == 'all') {
    foreach ($form['product']['#options'] as $key => $value) {
      if (count(explode('-', $key)) == 2) {
        list($type, $id) = explode('-', $key);
        registration_send_broadcast(
          $type,
          $id,
          $subject,
          $message
        );
      }
    }
  }
  else {
    list($type, $id) = explode('-', $id);
    registration_send_broadcast(
      $type,
      $id,
      $subject,
      $message
    );
  }
}

/**
 * New registration settings validation handler to use with Commerce Products.
 */
function commerce_registration_registration_settings_form_validate($form, $form_state) {
  if (!function_exists('registration_entity_settings_form_validate')) {
    form_load_include($form_state, 'inc', 'registration', 'includes/registration.forms');
  }
  $temp_form_state = array('values' => $form_state['values']['registration_settings']);
  $temp_form_state['values']['status'] = $temp_form_state['values']['reg_status'];
  return registration_entity_settings_form_validate($form, $temp_form_state);
}

/**
 * New registration settings submit handler to use with Commerce Products.
 */
function commerce_registration_registration_settings_form_submit($form, &$form_state) {
  list($entity_id) = entity_extract_ids("commerce_product", $form_state['commerce_product']);
  $temp_form_state = array(
    'entity' => array(
      'entity_type' => 'commerce_product',
      'entity_id' => $entity_id,
    ),
    'values' => $form_state['values']['registration_settings'],
  );
  $temp_form_state['values']['status'] = $temp_form_state['values']['reg_status'];
  registration_entity_settings_form_submit($form, $temp_form_state);
}
