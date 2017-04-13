<?php
/**
 * @file
 * Forms for the Commerce Event Ticket module.
 */

/**
 * Form for editing a ticket.
 */
function commerce_event_ticket_edit_form($form, &$form_state, CommerceEventTicketEntity $ticket) {
  $form_state['ticket'] = $ticket;

  $form['used'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#options' => array(
      'no' => t('Not used'),
      'yes' => t('Used'),
    ),
    '#default_value' => $ticket->used ? 'yes' : 'no',
  );

  $form['used']['#options'][$form['used']['#default_value']] .= ' ' . t('(current status)');

  $form['revision']['revision_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create a new revision'),
    '#default_value' => 0,
  );
  $form['revision']['revision_log'] = array(
    '#type' => 'textfield',
    '#title' => t('Revision log message'),
    '#description' => t('Optionally, provide an explanation of the changes you are making.'),
    '#maxlength' => 255,
    '#size' => 100,
    '#states' => array(
      'visible' => array(
        ':input[name="revision_enable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['buttons'] = array(
    '#type' => 'actions',
    '#weight' => 100,
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $cancel_path = 'admin/commerce/tickets/' . $ticket->ticket_id;
  if (!empty($_GET['destination'])) {
    $options = drupal_parse_url($_GET['destination']);
    $cancel_path = $options['path'];
  }
  $form['buttons']['cancel'] = array(
    '#type' => 'link',
    '#title' => t('Cancel'),
    '#href' => $cancel_path,
  );

  form_load_include($form_state, 'inc', 'commerce_event_ticket', 'includes/commerce_event_ticket.forms');

  field_attach_form('commerce_event_ticket', $ticket, $form, $form_state);

  return $form;
}

/**
 * Validation callback for the ticket edit form.
 */
function commerce_event_ticket_edit_form_validate(&$form, &$form_state) {
  field_attach_form_validate('commerce_event_ticket', $form_state['ticket'], $form, $form_state);
}

/**
 * Submit callback for the ticket edit form.
 */
function commerce_event_ticket_edit_form_submit($form, &$form_state) {
  $ticket = $form_state['ticket'];

  if (!empty($form_state['values']['used'])) {
    $ticket->used = $form_state['values']['used'] == 'yes' ? 1 : 0;
  }

  if (!empty($form_state['values']['revision_enable'])) {
    $ticket->revision = TRUE;
    $ticket->log = NULL;
    if (!empty($form_state['values']['revision_log'])) {
      $ticket->log = $form_state['values']['revision_log'];
    }
  }

  field_attach_submit('commerce_event_ticket', $ticket, $form, $form_state);
  commerce_event_ticket_save($ticket);

  // Notify the user that the ticket was saved.
  drupal_set_message(t('The ticket %id has been saved.', array(
    '%id' => $ticket->ticket_id,
  )));
}

/**
 * Form for validating a ticket (marking it as used).
 */
function commerce_event_ticket_validate_form($form, &$form_state, CommerceEventTicketEntity $ticket) {
  $form_state['ticket'] = $ticket;

  // Check the ticket validity regardless of its 'used' status.
  $explain = commerce_event_ticket_explain_validity($ticket);
  $valid = $explain === TRUE || $explain === t('Ticket already used');

  $form['actions'] = array('#type' => 'actions');

  $form['actions']['validate'] = array(
    '#type' => 'submit',
    '#value' => t('Validate ticket'),
    '#disabled' => $explain !== TRUE,
    '#access' => commerce_event_ticket_access('mark used', $ticket),
    '#submit' => array('commerce_event_ticket_validate_form_validate_submit'),
  );

  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset ticket'),
    '#disabled' => !$ticket->used || !$valid,
    '#access' => commerce_event_ticket_access('mark unused', $ticket),
    '#submit' => array('commerce_event_ticket_validate_form_reset_submit'),
  );

  form_load_include($form_state, 'inc', 'commerce_event_ticket', 'includes/commerce_event_ticket.forms');
  return $form;
}

/**
 * Reset (mark unused) callback for the ticket validating form.
 *
 * @see commerce_event_ticket_validate_form()
 */
function commerce_event_ticket_validate_form_reset_submit(&$form, &$form_state) {
  $ticket = $form_state['ticket'];
  if (!commerce_event_ticket_access('mark unused', $ticket)) {
    form_set_error('validate', t('Access denied'));
    return;
  }
  commerce_event_ticket_reset($ticket, TRUE);
  if (!$ticket->used) {
    drupal_set_message(t('The ticket @id was reset.', array(
      '@id' => $ticket->ticket_id,
    )));
  }
  $destination = drupal_get_destination();
  if (!$destination) {
    drupal_goto('admin/commerce/tickets/' . $ticket->ticket_id);
  }
}


/**
 * Validate (mark used) callback for the ticket validating form.
 *
 * @see commerce_event_ticket_validate_form()
 */
function commerce_event_ticket_validate_form_validate_submit(&$form, &$form_state) {
  $ticket = $form_state['ticket'];
  if (!commerce_event_ticket_access('mark used', $ticket)) {
    form_set_error('validate', t('Access denied'));
    return;
  }
  $result = commerce_event_ticket_validate($ticket, TRUE);
  if ($result === TRUE) {
    drupal_set_message(t('The ticket @id was validated.', array(
      '@id' => $ticket->ticket_id,
    )));
    $destination = drupal_get_destination();
    if (!$destination) {
      drupal_goto('admin/commerce/tickets/' . $ticket->ticket_id);
    }
  }
  else {
    form_set_error('validate', t('The ticket is not valid: %reason', array(
      '%reason' => $result,
    )));
  }
}
