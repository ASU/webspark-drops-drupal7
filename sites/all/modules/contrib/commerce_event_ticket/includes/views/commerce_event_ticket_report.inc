<?php
/**
 * @file
 * Default View to display a report of tickets and their usage.
 */

$view = new view();
$view->name = 'commerce_event_ticket_report';
$view->description = 'A ticket usage report.';
$view->tag = 'commerce_event_ticket';
$view->base_table = 'commerce_event_ticket';
$view->human_name = 'Ticket usage';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Ticket usage';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'update all commerce event tickets';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['submit_button'] = 'Filter';
$handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['total_pages'] = '10';
$handler->display->display_options['pager']['options']['quantity'] = '5';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'title' => 'title',
  'used' => 'used',
  'revision_timestamp' => 'revision_timestamp',
  'ticket_id' => 'ticket_id',
  'uid' => 'uid',
  'order_id' => 'order_id',
  'line_item_id' => 'line_item_id',
  'product_id' => 'product_id',
);
$handler->display->display_options['style_options']['default'] = 'revision_timestamp';
$handler->display->display_options['style_options']['info'] = array(
  'title' => array(
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
  'revision_timestamp' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'ticket_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'uid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'order_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'line_item_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'product_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
$handler->display->display_options['style_options']['empty_table'] = TRUE;
/* No results behavior: Global: Unfiltered text */
$handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
$handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['label'] = 'There is no data to display.';
$handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
$handler->display->display_options['empty']['area_text_custom']['content'] = 'There is no data to display.';
/* Relationship: Event ticket: Node */
$handler->display->display_options['relationships']['nid']['id'] = 'nid';
$handler->display->display_options['relationships']['nid']['table'] = 'commerce_event_ticket';
$handler->display->display_options['relationships']['nid']['field'] = 'nid';
/* Relationship: Event ticket: Product */
$handler->display->display_options['relationships']['product_id']['id'] = 'product_id';
$handler->display->display_options['relationships']['product_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['relationships']['product_id']['field'] = 'product_id';
$handler->display->display_options['relationships']['product_id']['label'] = 'Product';
$handler->display->display_options['relationships']['product_id']['required'] = TRUE;
/* Relationship: Event ticket: Order */
$handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
$handler->display->display_options['relationships']['order_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'nid';
$handler->display->display_options['fields']['title']['label'] = 'Content';
/* Field: Event ticket: Used */
$handler->display->display_options['fields']['used']['id'] = 'used';
$handler->display->display_options['fields']['used']['table'] = 'commerce_event_ticket';
$handler->display->display_options['fields']['used']['field'] = 'used';
$handler->display->display_options['fields']['used']['label'] = 'Ticket status';
$handler->display->display_options['fields']['used']['type'] = 'used';
$handler->display->display_options['fields']['used']['not'] = 0;
/* Field: MAX(Event ticket revision: Revision date) */
$handler->display->display_options['fields']['revision_timestamp']['id'] = 'revision_timestamp';
$handler->display->display_options['fields']['revision_timestamp']['table'] = 'commerce_event_ticket_revision';
$handler->display->display_options['fields']['revision_timestamp']['field'] = 'revision_timestamp';
$handler->display->display_options['fields']['revision_timestamp']['group_type'] = 'max';
$handler->display->display_options['fields']['revision_timestamp']['label'] = 'Last revision';
$handler->display->display_options['fields']['revision_timestamp']['date_format'] = 'today time ago';
$handler->display->display_options['fields']['revision_timestamp']['second_date_format'] = 'short';
/* Field: COUNT(DISTINCT Event ticket: Ticket ID) */
$handler->display->display_options['fields']['ticket_id']['id'] = 'ticket_id';
$handler->display->display_options['fields']['ticket_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['fields']['ticket_id']['field'] = 'ticket_id';
$handler->display->display_options['fields']['ticket_id']['group_type'] = 'count_distinct';
$handler->display->display_options['fields']['ticket_id']['label'] = 'Tickets';
/* Field: COUNT(DISTINCT Commerce Order: Uid) */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'commerce_order';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'order_id';
$handler->display->display_options['fields']['uid']['group_type'] = 'count_distinct';
$handler->display->display_options['fields']['uid']['label'] = 'Customers';
/* Field: COUNT(DISTINCT Event ticket: Order) */
$handler->display->display_options['fields']['order_id']['id'] = 'order_id';
$handler->display->display_options['fields']['order_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['fields']['order_id']['field'] = 'order_id';
$handler->display->display_options['fields']['order_id']['group_type'] = 'count_distinct';
$handler->display->display_options['fields']['order_id']['label'] = 'Orders';
/* Field: COUNT(DISTINCT Event ticket: Line item) */
$handler->display->display_options['fields']['line_item_id']['id'] = 'line_item_id';
$handler->display->display_options['fields']['line_item_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['fields']['line_item_id']['field'] = 'line_item_id';
$handler->display->display_options['fields']['line_item_id']['group_type'] = 'count_distinct';
$handler->display->display_options['fields']['line_item_id']['label'] = 'Line items';
/* Field: COUNT(DISTINCT Event ticket: Product) */
$handler->display->display_options['fields']['product_id']['id'] = 'product_id';
$handler->display->display_options['fields']['product_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['fields']['product_id']['field'] = 'product_id';
$handler->display->display_options['fields']['product_id']['group_type'] = 'count_distinct';
$handler->display->display_options['fields']['product_id']['label'] = 'Products';
/* Filter criterion: Content: Title */
$handler->display->display_options['filters']['title_1']['id'] = 'title_1';
$handler->display->display_options['filters']['title_1']['table'] = 'node';
$handler->display->display_options['filters']['title_1']['field'] = 'title';
$handler->display->display_options['filters']['title_1']['relationship'] = 'nid';
$handler->display->display_options['filters']['title_1']['operator'] = 'allwords';
$handler->display->display_options['filters']['title_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['title_1']['expose']['operator_id'] = 'title_1_op';
$handler->display->display_options['filters']['title_1']['expose']['label'] = 'Content title';
$handler->display->display_options['filters']['title_1']['expose']['operator'] = 'title_1_op';
$handler->display->display_options['filters']['title_1']['expose']['identifier'] = 'title_1';
$handler->display->display_options['filters']['title_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'admin/commerce/tickets/report';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Usage report';
$handler->display->display_options['menu']['weight'] = '1';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

$views[$view->name] = $view;
