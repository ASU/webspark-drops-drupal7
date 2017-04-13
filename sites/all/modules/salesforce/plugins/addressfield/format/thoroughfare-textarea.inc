<?php
/**
 * @file
 * addressfield.inc
 *
 * Custom address formatters for compatibility with Salesforce addresses.
 */

/**
 * Plugin definition for address field format.
 */
$plugin = array(
  'title' => t('Thoroughfare as text area (Provided by Salesforce Module)'),
  'format callback' => 'salesforce_thoroughfare_textarea_generate',
  'type' => 'address',
  'weight' => -80,
);

/**
 * Callback for plugin definition.
 */
function salesforce_thoroughfare_textarea_generate(&$format, $address, $context = array()) {
  if (isset($format['street_block']['thoroughfare']) && isset($format['street_block']['premise'])) {
    // Change Thoroughfare (Address 1) field to a textarea.
    if ($context['mode'] == 'form') {
      $format['street_block']['thoroughfare']['#widget_type'] = 'textarea';
      $format['street_block']['thoroughfare']['#rows'] = '2';
      $format['street_block']['thoroughfare']['#title'] = t('Address');
      $format['street_block']['premise']['#access'] = FALSE;
    }
    // Convert newlines to breaks when displaying thoroughfare.
    elseif ($context['mode'] == 'render') {
      $format['street_block']['thoroughfare']['#render_type'] = 'markup';
      $format['street_block']['thoroughfare']['#markup'] = nl2br($address['thoroughfare']);
    }
  }
}
