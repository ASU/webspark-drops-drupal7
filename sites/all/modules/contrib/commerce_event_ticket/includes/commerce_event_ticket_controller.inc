<?php
/**
 * @file
 * Entity controller class for Commerce Event Ticket.
 */

class CommerceEventTicketController extends EntityAPIController {

  /**
   * Overrides EntityAPIController::save().
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $ticket = $entity;

    // Determine whether the ticket is new.
    $ticket->is_new = empty($ticket->ticket_id);

    // Set the 'created' and 'changed' properties.
    if (empty($ticket->created)) {
      $ticket->created = REQUEST_TIME;
    }
    $ticket->changed = REQUEST_TIME;

    // Reset the static cache of whether the ticket is valid.
    // @see commerce_event_ticket_explain_validity()
    if (!$ticket->is_new) {
      $reasons = &drupal_static('commerce_event_ticket_explain_validity', array());
      unset($reasons[$ticket->ticket_id]);
    }

    // If a new revision is being created, make sure the log entry, timestamp,
    // and user ID are set for the revision.
    if ($ticket->is_new || !empty($ticket->revision)) {
      $ticket->revision_timestamp = REQUEST_TIME;
      $ticket->revision_uid = $GLOBALS['user']->uid;
      if (!isset($ticket->log)) {
        $ticket->log = '';
      }
    }

    parent::save($ticket, $transaction);
  }

}
