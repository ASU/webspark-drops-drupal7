<?php
/**
 * @file
 * Views integration for the Commerce Event Ticket module.
 */

/**
 * Implements hook_views_data().
 */
function commerce_event_ticket_views_data() {
  $data = array();

  $data['commerce_event_ticket']['valid'] = array(
    'title' => t('Validity'),
    'help' => t('Whether the ticket is currently valid.'),
    'field' => array(
      'handler' => 'commerce_event_ticket_views_handler_field_valid',
      'click sortable' => FALSE,
    ),
    'real field' => 'ticket_id',
  );

  $data['commerce_event_ticket']['revision_id'] = array(
    'title' => t('Revision ID'),
    'help' => t('The current revision ID for the event ticket.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
  );

  $data['commerce_event_ticket_revision']['revision_id'] = array(
    'title' => t('Revision ID'),
    'help' => t('The unique ID of the revision.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_event_ticket',
      'base field' => 'revision_id',
      'title' => t('Event ticket'),
      'label' => t('Latest ticket revision'),
      'help' => t('The latest (or current) revision for the event ticket.'),
    ),
  );

  $data['commerce_event_ticket_revision']['revision_timestamp'] = array(
    'title' => t('Revision date'),
    'help' => t('The date the ticket revision was made.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['commerce_event_ticket_revision']['log'] = array(
    'title' => t('Log message'),
    'help' => t('The log message entered when the revision was created.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['commerce_event_ticket_revision']['revision_uid'] = array(
    'title' => t('User'),
    'help' => t('Relate a ticket revision to the user who created the revision.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'field' => 'revision_uid',
      'field_name' => 'revision_uid',
      'label' => t('Revision user'),
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 *
 * @todo Find out why this has to be done at the _alter stage. At the moment it
 * seems that doing this in hook_views_data() causes duplicated definitions that
 * end up as arrays (this could be a bug in Entity API or in Views).
 */
function commerce_event_ticket_views_data_alter(&$data) {
  $data['commerce_event_ticket_revision']['table']['group']  = t('Event ticket');

  $data['commerce_event_ticket']['table']['base'] = array(
    'field' => 'ticket_id',
    'title' => t('Commerce Event Ticket'),
    'help' => t('Tickets for events.'),
  );
  $data['commerce_event_ticket']['table']['entity type'] = 'commerce_event_ticket';

  $data['commerce_event_ticket']['used']['field']['output formats'] = array(
    'used' => array(t('Used'), t('Unused')),
  );
  $data['commerce_event_ticket']['used']['filter']['title'] = t('Used');
  $data['commerce_event_ticket']['used']['filter']['type'] = 'yes-no';

  $data['commerce_event_ticket']['table']['default_relationship'] = array(
    'commerce_event_ticket_revision' => array(
      'table' => 'commerce_event_ticket_revision',
      'field' => 'revision_id',
    ),
  );
  $data['commerce_event_ticket_revision']['table']['group']  = t('Event ticket revision');
  $data['commerce_event_ticket_revision']['table']['base'] = array(
    'field' => 'revision_id',
    'title' => t('Event ticket revision'),
    'help' => t('A history of changes to event tickets.'),
    'defaults' => array(
      'field' => 'revision_timestamp',
    ),
  );
}
