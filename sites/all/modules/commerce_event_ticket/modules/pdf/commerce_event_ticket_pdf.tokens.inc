<?php
/**
 * @file
 * Token integration for the Commerce Event Ticket PDF module.
 */

/**
 * Implements hook_token_info().
 */
function commerce_event_ticket_pdf_token_info() {
  $info = array();
  $info['tokens'] = array(
    'commerce-event-ticket' => array(
      'ticket-pdf' => array(
        'name' => t('Ticket PDF'),
        'description' => t('The URL to a PDF for this ticket.'),
      ),
    ),
    'commerce-line-item' => array(
      'ticket-pdf' => array(
        'name' => t('Ticket PDF'),
        'description' => t("The URL to a PDF for this line item's tickets."),
      ),
    ),
    'commerce-order' => array(
      'ticket-pdf' => array(
        'name' => t('Ticket PDF'),
        'description' => t("The URL to a PDF for this order's tickets."),
      ),
    ),
  );
  return $info;
}

/**
 * Implements hook_tokens().
 */
function commerce_event_ticket_pdf_tokens($type, array $tokens, array $data = array(), array $options = array()) {
  $sanitize = !empty($options['sanitize']);
  $replacements = array();
  $types = array(
    'commerce-event-ticket',
    'commerce-order',
    'commerce-line-item',
  );
  if (in_array($type, $types) && !empty($data[$type])) {
    $entity = $data[$type];
    $entity_type = str_replace('-', '_', $type);
    $entity_ids = entity_extract_ids($entity_type, $entity);
    $entity_id = $entity_ids[0];
    foreach ($tokens as $name => $original) {
      if ($name != 'ticket-pdf') {
        continue;
      }
      $uri = commerce_event_ticket_pdf_get_link($entity_id, $entity_type, 'view', FALSE);
      if ($uri) {
        $uri['absolute'] = TRUE;
        $url = url($uri['path'], $uri);
        $replacements[$original] = $sanitize ? check_plain($url) : $url;
      }
    }
  }
  return $replacements;
}
