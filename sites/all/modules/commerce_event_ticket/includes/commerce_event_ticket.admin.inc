<?php
/**
 * @file
 * Admin functions for the Commerce Event Ticket module.
 */

/**
 * Configuration form.
 */
function commerce_event_ticket_config($form, &$form_state) {
  $form = array();

  $form['barcodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Barcodes'),
  );

  $form['barcodes']['commerce_event_ticket_barcode_length'] = array(
    '#type' => 'select',
    '#title' => t('Length'),
    '#description' => t('Select the length of the barcode tokens.'),
    '#options' => drupal_map_assoc(range(6, 12)),
    '#default_value' => variable_get('commerce_event_ticket_barcode_length', 10),
    '#required' => TRUE,
  );

  $form['barcodes']['commerce_event_ticket_token_type'] = array(
    '#type' => 'select',
    '#title' => t('Token type'),
    '#options' => array(
      'alphanumeric' => t('Alphanumeric'),
      'numeric' => t('Numeric'),
    ),
    '#required' => TRUE,
    '#default_value' => variable_get('commerce_event_ticket_token_type', 'alphanumeric'),
  );

  $form['order_statuses'] = array(
    '#type' => 'fieldset',
    '#title' => t('Order statuses'),
  );

  $status_options = commerce_order_status_options_list();

  $form['order_statuses']['commerce_event_ticket_statuses_create'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('When to create tickets'),
    '#description' => t('Select the order statuses that trigger the creation of ticket entities.'),
    '#options' => $status_options,
    '#default_value' => variable_get('commerce_event_ticket_statuses_create', array('checkout_complete', 'completed')),
    '#required' => TRUE,
  );

  $form['order_statuses']['commerce_event_ticket_valid_statuses'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Validating tickets'),
    '#description' => t('Select the order statuses that are considered to be valid to allow entry with a ticket.'),
    '#options' => $status_options,
    '#default_value' => variable_get('commerce_event_ticket_valid_statuses', array('checkout_complete', 'completed')),
  );

  // Check whether there is any point in providing date validation settings,
  // i.e. find out whether there are any Date fields attached to product display
  // node types.
  $date_validation = FALSE;
  if (module_exists('date')) {
    $date_field_names = commerce_event_ticket_get_date_fields();
    $date_field_options = array();
    foreach ($date_field_names as $field_name) {
      $field = field_info_field($field_name);
      if ($field && $field['active'] && !$field['deleted']) {
        $date_field_options[$field_name] = $field_name;
      }
    }
    if (count($date_field_options)) {
      $date_validation = TRUE;
    }
  }

  if ($date_validation) {
    $form['date'] = array(
      '#type' => 'fieldset',
      '#title' => t('Date validation'),
    );
    $form['date']['commerce_event_ticket_date_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Consider tickets invalid for past events'),
      '#description' => t("This invalidates a ticket after the event. The event is the product display node associated with the ticket's product."),
      '#default_value' => variable_get('commerce_event_ticket_date_enabled', 1),
    );
    $form['date']['commerce_event_ticket_date_strict'] = array(
      '#type' => 'checkbox',
      '#title' => t("Consider tickets invalid for events with no date"),
      '#description' => t('If enabled, tickets will be invalid if no date is found for the event (or if no event can be found).'),
      '#default_value' => variable_get('commerce_event_ticket_date_strict', 0),
    );
    $form['date']['commerce_event_ticket_date_fields'] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $date_field_options,
      '#title' => t('Date fields'),
      '#description' => t('Use these date fields to determine the event dates.'),
      '#default_value' => variable_get('commerce_event_ticket_date_fields', $date_field_names),
    );
    $form['date']['commerce_event_ticket_date_default_duration'] = array(
      '#type' => 'textfield',
      '#title' => t('Default event duration'),
      '#size' => 4,
      '#maxlength' => 6,
      '#description' => t('If the event does not have an end time, then set a default length of time during which tickets will still be valid.'),
      '#default_value' => variable_get('commerce_event_ticket_date_default_duration', 5400),
      '#field_suffix' => ' ' . t('seconds'),
      '#element_validate' => array('element_validate_integer'),
    );
    $form['date']['commerce_event_ticket_date_validity_period'] = array(
      '#type' => 'textfield',
      '#title' => t('Validity period'),
      '#size' => 4,
      '#maxlength' => 6,
      '#description' => t('Consider tickets valid for this length of time after the event ends.'),
      '#default_value' => variable_get('commerce_event_ticket_date_validity_period', 0),
      '#field_suffix' => ' seconds',
      '#element_validate' => array('element_validate_integer'),
    );
  }

  return system_settings_form($form);
}
