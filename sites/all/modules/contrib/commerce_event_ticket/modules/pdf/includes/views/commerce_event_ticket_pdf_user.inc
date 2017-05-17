<?php
/**
 * @file
 * Default View to display a list of the current user's own tickets.
 */

$view = new view();
$view->name = 'commerce_event_ticket_pdf_user';
$view->description = 'A list of the user\'s own tickets.';
$view->tag = 'commerce_event_ticket';
$view->base_table = 'commerce_line_item';
$view->human_name = 'My tickets';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = TRUE;

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'My tickets';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view own commerce event tickets';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '5';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'order_number' => 'order_number',
  'created' => 'created',
  'status' => 'status',
  'title' => 'title',
  'quantity' => 'quantity',
  'line_item_ticket_pdf' => 'line_item_ticket_pdf',
);
$handler->display->display_options['style_options']['default'] = 'order_number';
$handler->display->display_options['style_options']['info'] = array(
  'order_number' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'created' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'status' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'title' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'quantity' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'line_item_ticket_pdf' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* No results behavior: Global: Unfiltered text */
$handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
$handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['label'] = 'There are no (currently valid) tickets to display.';
$handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
$handler->display->display_options['empty']['area_text_custom']['content'] = '<p>There are no (currently valid) tickets to display.</p>';
/* Relationship: Commerce Line Item: Order ID */
$handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
$handler->display->display_options['relationships']['order_id']['table'] = 'commerce_line_item';
$handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
$handler->display->display_options['relationships']['order_id']['required'] = TRUE;
/* Relationship: Commerce Line item: Referenced products */
$handler->display->display_options['relationships']['commerce_product_product_id']['id'] = 'commerce_product_product_id';
$handler->display->display_options['relationships']['commerce_product_product_id']['table'] = 'field_data_commerce_product';
$handler->display->display_options['relationships']['commerce_product_product_id']['field'] = 'commerce_product_product_id';
$handler->display->display_options['relationships']['commerce_product_product_id']['required'] = TRUE;
/* Relationship: Commerce Line Item: Event ticket */
$handler->display->display_options['relationships']['commerce_event_ticket']['id'] = 'commerce_event_ticket';
$handler->display->display_options['relationships']['commerce_event_ticket']['table'] = 'commerce_line_item';
$handler->display->display_options['relationships']['commerce_event_ticket']['field'] = 'commerce_event_ticket';
$handler->display->display_options['relationships']['commerce_event_ticket']['required'] = TRUE;
/* Field: Commerce Order: Order number */
$handler->display->display_options['fields']['order_number']['id'] = 'order_number';
$handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
$handler->display->display_options['fields']['order_number']['field'] = 'order_number';
$handler->display->display_options['fields']['order_number']['relationship'] = 'order_id';
$handler->display->display_options['fields']['order_number']['link_to_order'] = 'customer';
/* Field: Commerce Order: Created date */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'commerce_order';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['relationship'] = 'order_id';
$handler->display->display_options['fields']['created']['label'] = 'Date';
$handler->display->display_options['fields']['created']['date_format'] = 'short';
$handler->display->display_options['fields']['created']['second_date_format'] = 'long';
/* Field: Commerce Order: Order status */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'commerce_order';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['relationship'] = 'order_id';
$handler->display->display_options['fields']['status']['label'] = 'Status';
/* Field: Commerce Product: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'commerce_product';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'commerce_product_product_id';
$handler->display->display_options['fields']['title']['label'] = 'Product';
$handler->display->display_options['fields']['title']['link_to_product'] = 0;
/* Field: Commerce Line Item: Quantity */
$handler->display->display_options['fields']['quantity']['id'] = 'quantity';
$handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
$handler->display->display_options['fields']['quantity']['field'] = 'quantity';
$handler->display->display_options['fields']['quantity']['precision'] = '0';
/* Field: Commerce Line Item: Tickets PDF link */
$handler->display->display_options['fields']['line_item_ticket_pdf']['id'] = 'line_item_ticket_pdf';
$handler->display->display_options['fields']['line_item_ticket_pdf']['table'] = 'commerce_line_item';
$handler->display->display_options['fields']['line_item_ticket_pdf']['field'] = 'line_item_ticket_pdf';
$handler->display->display_options['fields']['line_item_ticket_pdf']['label'] = 'Tickets';
/* Contextual filter: Commerce Order: Uid */
$handler->display->display_options['arguments']['uid']['id'] = 'uid';
$handler->display->display_options['arguments']['uid']['table'] = 'commerce_order';
$handler->display->display_options['arguments']['uid']['field'] = 'uid';
$handler->display->display_options['arguments']['uid']['relationship'] = 'order_id';
$handler->display->display_options['arguments']['uid']['default_action'] = 'default';
$handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
$handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
$handler->display->display_options['arguments']['uid']['validate']['type'] = 'current_user_or_role';
$handler->display->display_options['arguments']['uid']['validate_options']['restrict_roles'] = TRUE;
$handler->display->display_options['arguments']['uid']['validate_options']['roles'] = array(
  3 => '3',
);
/* Filter criterion: Commerce Line Item: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'commerce_line_item';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'product' => 'product',
);
/* Filter criterion: Commerce Product: Enable tickets (cet_enable) */
$handler->display->display_options['filters']['cet_enable_value']['id'] = 'cet_enable_value';
$handler->display->display_options['filters']['cet_enable_value']['table'] = 'field_data_cet_enable';
$handler->display->display_options['filters']['cet_enable_value']['field'] = 'cet_enable_value';
$handler->display->display_options['filters']['cet_enable_value']['relationship'] = 'commerce_product_product_id';
$handler->display->display_options['filters']['cet_enable_value']['value'] = array(
  1 => '1',
);
/* Filter criterion: Commerce Order: Order state */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'commerce_order';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['relationship'] = 'order_id';
$handler->display->display_options['filters']['state']['value'] = array(
  'completed' => 'completed',
);
/* Filter criterion: Event ticket: Used */
$handler->display->display_options['filters']['used']['id'] = 'used';
$handler->display->display_options['filters']['used']['table'] = 'commerce_event_ticket';
$handler->display->display_options['filters']['used']['field'] = 'used';
$handler->display->display_options['filters']['used']['relationship'] = 'commerce_event_ticket';
$handler->display->display_options['filters']['used']['value'] = '0';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'user/%/event-tickets';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Tickets';
$handler->display->display_options['menu']['weight'] = '16';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

$views[$view->name] = $view;
