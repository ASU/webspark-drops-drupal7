<?php
/**
 * @file
 * Services hook implementations for the Commerce Event Ticket Services module.
 */

/**
 * Implements hook_services_resources().
 */
function commerce_event_ticket_services_services_resources() {
  return array(
    'event-ticket' => array(
      'operations' => array(
        'retrieve' => array(
          'help' => t('Get event ticket information.'),
          'callback' => 'commerce_event_ticket_services_retrieve_ticket',
          'file' => array(
            'type' => 'inc',
            'module' => 'commerce_event_ticket_services',
            'name' => 'commerce_event_ticket_services_resource',
          ),
          'access callback' => 'commerce_event_ticket_services_access_ticket',
          'access arguments' => array('view'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'barcode',
              'type' => 'string',
              'description' => t('The barcode token for the event ticket.'),
              'source' => array('path' => '0'),
              'optional' => FALSE,
            ),
          ),
        ),
      ),
      'targeted_actions' => array(
        'validate' => array(
          'help' => 'Validate a ticket',
          'callback' => 'commerce_event_ticket_services_validate_ticket',
          'file' => array(
            'type' => 'inc',
            'module' => 'commerce_event_ticket_services',
            'name' => 'commerce_event_ticket_services_resource',
          ),
          'access callback' => 'commerce_event_ticket_services_access_ticket',
          'access arguments' => array('mark used'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'barcode',
              'type' => 'string',
              'description' => t('The barcode token for the event ticket.'),
              'source' => array('path' => '0'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'log',
              'type' => 'string',
              'description' => t('A log message to save if the ticket is validated.'),
              'source' => array('data' => 'log'),
              'optional' => TRUE,
            ),
          ),
        ),
        'reset' => array(
          'help' => 'Reset a ticket',
          'callback' => 'commerce_event_ticket_services_reset_ticket',
          'file' => array(
            'type' => 'inc',
            'module' => 'commerce_event_ticket_services',
            'name' => 'commerce_event_ticket_services_resource',
          ),
          'access callback' => 'commerce_event_ticket_services_access_ticket',
          'access arguments' => array('mark unused'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'barcode',
              'type' => 'string',
              'description' => t('The barcode token for the event ticket.'),
              'source' => array('path' => '0'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'log',
              'type' => 'string',
              'description' => t('A log message to save if the ticket is reset.'),
              'source' => array('data' => 'log'),
              'optional' => TRUE,
            ),
          ),
        ),
      ),
      'actions' => array(
        'validate-multiple' => array(
          'help' => t('Validate multiple tickets'),
          'callback' => 'commerce_event_ticket_services_validate_multiple_tickets',
          'access callback' => 'commerce_event_ticket_services_access_validate_multiple',
          'file' => array(
            'type' => 'inc',
            'module' => 'commerce_event_ticket_services',
            'name' => 'commerce_event_ticket_services_resource',
          ),
          'args' => array(
            array(
              'name' => 'tickets',
              'type' => 'array',
              'description' => t('The barcodes of the tickets to validate'),
              'source' => array('data' => 'tickets'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'log',
              'type' => 'string',
              'description' => t('A log message to save if the ticket is validated.'),
              'source' => array('data' => 'log'),
              'optional' => TRUE,
            ),
          ),
        ),
      ),
    ),
    'event-ticket-nodes' => array(
      'operations' => array(
        'index' => array(
          'help' => t('List nodes with event tickets'),
          'callback' => 'commerce_event_ticket_services_list_event_ticket_nodes',
          'access callback' => 'commerce_event_ticket_services_access_ticket_nodes',
          'file' => array(
            'type' => 'inc',
            'module' => 'commerce_event_ticket_services',
            'name' => 'commerce_event_ticket_services_resource',
          ),
          'args' => array(
            array(
              'name' => 'offset',
              'optional' => TRUE,
              'type' => 'int',
              'description' => t('An offset from 0 for the retrieved nodes.'),
              'source' => array('param' => 'offset'),
              'default value' => 0,
            ),
            array(
              'name' => 'limit',
              'optional' => TRUE,
              'type' => 'int',
              'description' => t('A limit for the number of nodes to return. Defaults to 50.'),
              'source' => array('param' => 'limit'),
              'default value' => 50,
            ),
            array(
              'name' => 'date_filter',
              'optional' => TRUE,
              'type' => 'int',
              'description' => t('Whether to filter nodes by the event dates, if this is possible. If enabled, only nodes with a start date equal or later than today will be returned. Defaults to 1 (enabled).'),
              'source' => array('param' => 'date_filter'),
              'default value' => 1,
            ),
            array(
              'name' => 'date_sort',
              'optional' => TRUE,
              'type' => 'int',
              'description' => t('Whether to sort nodes by the event dates, if possible. Defaults to 1 (enabled).'),
              'source' => array('param' => 'date_sort'),
              'default value' => 1,
            ),
          ),
        ),
      ),
    ),
    'node' => array(
      'relationships' => array(
        'tickets' => array(
          'help' => t('Retrieve tickets associated with a product display node.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'commerce_event_ticket_services',
            'name' => 'commerce_event_ticket_services_resource',
          ),
          'access callback' => 'commerce_event_ticket_services_access_tickets_per_node',
          'access arguments' => array(),
          'access arguments append' => TRUE,
          'callback' => 'commerce_event_ticket_services_retrieve_tickets_per_node',
          'args' => array(
            array(
              'name' => 'nid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => t('The nid of the product display node.'),
            ),
            array(
              'name' => 'offset',
              'optional' => TRUE,
              'type' => 'int',
              'description' => t('An offset from 0 for the retrieved tickets.'),
              'source' => array('param' => 'offset'),
              'default value' => 0,
            ),
            array(
              'name' => 'limit',
              'optional' => TRUE,
              'type' => 'int',
              'description' => t('A limit for the number of tickets to return. Defaults to 50.'),
              'source' => array('param' => 'limit'),
              'default value' => 50,
            ),
            array(
              'name' => 'changed_since',
              'optional' => TRUE,
              'type' => 'int',
              'description' => t('A UNIX timestamp to filter results by. Only tickets that changed at or after this timestamp will be returned.'),
              'source' => array('param' => 'changed_since'),
              'default value' => 0,
            ),
          ),
        ),
      ),
    ),
  );
}
