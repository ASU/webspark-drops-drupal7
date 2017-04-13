<?php
/**
 * @file
 * Drush integration for the Commerce Event Ticket module.
 */

/**
 * Implements hook_drush_command().
 */
function commerce_event_ticket_drush_command() {
  $items = array();
  $items['commerce-event-ticket-validate'] = array(
    'description' => 'Validate an event ticket.',
    'arguments' => array(
      'ticket' => "The ticket's barcode or ticket ID (required).",
    ),
    'options' => array(
      'leave-unused' => array(
        'description' => 'Skip marking the ticket as used if validated.',
        'value' => 'optional',
      ),
    ),
    'required-arguments' => 1,
    'aliases' => array('cet-validate'),
  );
  $items['commerce-event-ticket-reset'] = array(
    'description' => 'Mark an event ticket as unused.',
    'arguments' => array(
      'ticket' => "The ticket's barcode or ticket ID (required).",
    ),
    'required-arguments' => 1,
    'aliases' => array('cet-reset'),
  );
  return $items;
}

/**
 * Validate a commerce event ticket barcode, via Drush.
 *
 * @param string $search
 *   The ticket's barcode token or ticket ID.
 */
function drush_commerce_event_ticket_validate($search) {
  if (is_numeric($search)) {
    $ticket = commerce_event_ticket_load($search);
  }
  if (empty($ticket)) {
    $ticket = commerce_event_ticket_load_by_barcode($search, TRUE);
  }
  if (!$ticket) {
    return drush_log(dt('No ticket found.'), 'error');
  }
  $mark_used = drush_get_option('leave-unused', FALSE) ? FALSE : TRUE;
  $validated = commerce_event_ticket_validate($ticket, $mark_used, TRUE, dt('Validated via command line.'));
  if ($validated !== TRUE) {
    return drush_log($validated, 'error');
  }
  return drush_log(
    $mark_used ? dt('The ticket is valid. It has been marked as used.') : dt('The ticket is valid.'),
    'success'
  );
}

/**
 * Reset an event ticket so that it is marked as unused.
 *
 * @param string $search
 *   The ticket's barcode token or ticket ID.
 */
function drush_commerce_event_ticket_reset($search) {
  if (is_numeric($search)) {
    $ticket = commerce_event_ticket_load($search);
  }
  if (empty($ticket)) {
    $ticket = commerce_event_ticket_load_by_barcode($search, TRUE);
  }
  if (!$ticket) {
    return drush_log(dt('No ticket found.'), 'error');
  }
  if (!$ticket->used) {
    return drush_log(dt('The ticket is not marked used.'), 'ok');
  }
  commerce_event_ticket_reset($ticket, TRUE, t('Reset via command line'));
  return drush_log(dt('The ticket has been marked as unused.'), 'success');
}
