<?php
/**
 * @file
 * Admin functions for the Commerce Event Ticket PDF module.
 */

/**
 * Configuration form.
 */
function commerce_event_ticket_pdf_config($form, &$form_state) {
  $form = array();

  $options = _commerce_event_ticket_pdf_elements_options();
  $defaults = drupal_map_assoc(array_keys($options));
  $form['commerce_event_ticket_pdf_elements'] = array(
    '#type' => 'checkboxes',
    '#title' => t('PDF elements'),
    '#description' => t('The elements to add to the generated PDF.'),
    '#options' => $options,
    '#default_value' => variable_get('commerce_event_ticket_pdf_elements', $defaults),
  );

  $form['commerce_event_ticket_pdf_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Limit'),
    '#description' => t('The maximum number of tickets that a PDF can contain.'),
    '#size' => 3,
    '#maxlength' => 5,
    '#default_value' => variable_get('commerce_event_ticket_pdf_limit', 100),
  );

  return system_settings_form($form);
}

/**
 * Validate callback for the configuration form.
 */
function commerce_event_ticket_pdf_config_validate(&$form, &$form_state) {
  $limit = $form_state['values']['commerce_event_ticket_pdf_limit'];
  if (!is_numeric($limit) || $limit < 1) {
    form_set_error('commerce_event_ticket_pdf_limit', t('The limit must be a positive integer.'));
  }
}
