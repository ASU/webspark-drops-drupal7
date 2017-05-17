<?php
/**
 * @file
 * A View displaying revisions for each ticket.
 */

$view = new view();
$view->name = 'commerce_event_ticket_revisions';
$view->description = '';
$view->tag = 'commerce_event_ticket';
$view->base_table = 'commerce_event_ticket_revision';
$view->human_name = 'Event ticket revisions';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Revisions';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer commerce event ticket';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '15';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'ticket_id' => 'ticket_id',
  'revision_id' => 'revision_id',
  'revision_timestamp' => 'revision_timestamp',
  'name' => 'name',
  'used' => 'used',
  'log' => 'log',
);
$handler->display->display_options['style_options']['default'] = 'revision_id';
$handler->display->display_options['style_options']['info'] = array(
  'ticket_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'revision_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'revision_timestamp' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'used' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'log' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Relationship: Event ticket revision: User */
$handler->display->display_options['relationships']['revision_uid']['id'] = 'revision_uid';
$handler->display->display_options['relationships']['revision_uid']['table'] = 'commerce_event_ticket_revision';
$handler->display->display_options['relationships']['revision_uid']['field'] = 'revision_uid';
/* Field: Event ticket revision: Ticket ID */
$handler->display->display_options['fields']['ticket_id']['id'] = 'ticket_id';
$handler->display->display_options['fields']['ticket_id']['table'] = 'commerce_event_ticket_revision';
$handler->display->display_options['fields']['ticket_id']['field'] = 'ticket_id';
$handler->display->display_options['fields']['ticket_id']['separator'] = '';
/* Field: Event ticket revision: Revision ID */
$handler->display->display_options['fields']['revision_id']['id'] = 'revision_id';
$handler->display->display_options['fields']['revision_id']['table'] = 'commerce_event_ticket_revision';
$handler->display->display_options['fields']['revision_id']['field'] = 'revision_id';
$handler->display->display_options['fields']['revision_id']['separator'] = '';
/* Field: Event ticket revision: Revision date */
$handler->display->display_options['fields']['revision_timestamp']['id'] = 'revision_timestamp';
$handler->display->display_options['fields']['revision_timestamp']['table'] = 'commerce_event_ticket_revision';
$handler->display->display_options['fields']['revision_timestamp']['field'] = 'revision_timestamp';
$handler->display->display_options['fields']['revision_timestamp']['date_format'] = 'short';
$handler->display->display_options['fields']['revision_timestamp']['second_date_format'] = 'long';
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'revision_uid';
$handler->display->display_options['fields']['name']['label'] = 'User';
/* Field: Event ticket revision: Used */
$handler->display->display_options['fields']['used']['id'] = 'used';
$handler->display->display_options['fields']['used']['table'] = 'commerce_event_ticket_revision';
$handler->display->display_options['fields']['used']['field'] = 'used';
$handler->display->display_options['fields']['used']['not'] = 0;
/* Field: Event ticket revision: Log message */
$handler->display->display_options['fields']['log']['id'] = 'log';
$handler->display->display_options['fields']['log']['table'] = 'commerce_event_ticket_revision';
$handler->display->display_options['fields']['log']['field'] = 'log';
/* Contextual filter: Event ticket revision: Ticket ID */
$handler->display->display_options['arguments']['ticket_id']['id'] = 'ticket_id';
$handler->display->display_options['arguments']['ticket_id']['table'] = 'commerce_event_ticket_revision';
$handler->display->display_options['arguments']['ticket_id']['field'] = 'ticket_id';
$handler->display->display_options['arguments']['ticket_id']['default_action'] = 'default';
$handler->display->display_options['arguments']['ticket_id']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['ticket_id']['title'] = 'Ticket %1: revisions';
$handler->display->display_options['arguments']['ticket_id']['default_argument_type'] = 'raw';
$handler->display->display_options['arguments']['ticket_id']['default_argument_options']['index'] = '0';
$handler->display->display_options['arguments']['ticket_id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['ticket_id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['ticket_id']['summary_options']['items_per_page'] = '25';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'admin/commerce/tickets/%/revisions';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Revisions';
$handler->display->display_options['menu']['weight'] = '2';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

$views[$view->name] = $view;
