<?php
/**
 * @file
 * Default View to display a list of tickets.
 */

$view = new view();
$view->name = 'commerce_event_tickets';
$view->description = 'A list of tickets.';
$view->tag = 'commerce_event_ticket';
$view->base_table = 'commerce_event_ticket';
$view->human_name = 'Tickets';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Tickets';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view all commerce event tickets';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['submit_button'] = 'Filter';
$handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['total_pages'] = '15';
$handler->display->display_options['pager']['options']['quantity'] = '5';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'views_bulk_operations' => 'views_bulk_operations',
  'ticket_id' => 'ticket_id',
  'valid' => 'valid',
  'used' => 'used',
  'created' => 'created',
  'order_number' => 'order_number',
  'title' => 'title',
  'commerce_unit_price' => 'commerce_unit_price',
  'name' => 'name',
);
$handler->display->display_options['style_options']['default'] = 'order_number';
$handler->display->display_options['style_options']['info'] = array(
  'views_bulk_operations' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'ticket_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'valid' => array(
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
  'created' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'order_number' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
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
  'commerce_unit_price' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
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
);
$handler->display->display_options['style_options']['empty_table'] = TRUE;
/* No results behavior: Global: Unfiltered text */
$handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
$handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['label'] = 'There are no tickets to display.';
$handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
$handler->display->display_options['empty']['area_text_custom']['content'] = 'There are no tickets to display.';
/* Relationship: Event ticket: Order */
$handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
$handler->display->display_options['relationships']['order_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
$handler->display->display_options['relationships']['order_id']['required'] = TRUE;
/* Relationship: Commerce Order: Owner */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'commerce_order';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
$handler->display->display_options['relationships']['uid']['relationship'] = 'order_id';
$handler->display->display_options['relationships']['uid']['required'] = TRUE;
/* Relationship: Event ticket: Product */
$handler->display->display_options['relationships']['product_id']['id'] = 'product_id';
$handler->display->display_options['relationships']['product_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['relationships']['product_id']['field'] = 'product_id';
$handler->display->display_options['relationships']['product_id']['required'] = TRUE;
/* Relationship: Event ticket: Line item */
$handler->display->display_options['relationships']['line_item_id']['id'] = 'line_item_id';
$handler->display->display_options['relationships']['line_item_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['relationships']['line_item_id']['field'] = 'line_item_id';
$handler->display->display_options['relationships']['line_item_id']['required'] = TRUE;
/* Relationship: Event ticket: Node */
$handler->display->display_options['relationships']['nid']['id'] = 'nid';
$handler->display->display_options['relationships']['nid']['table'] = 'commerce_event_ticket';
$handler->display->display_options['relationships']['nid']['field'] = 'nid';
/* Field: Bulk operations: Event ticket */
$handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['table'] = 'commerce_event_ticket';
$handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
$handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
  'action::views_bulk_operations_delete_item' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'postpone_processing' => 0,
  ),
  'action::system_message_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'postpone_processing' => 0,
  ),
  'action::views_bulk_operations_script_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'postpone_processing' => 0,
  ),
  'action::views_bulk_operations_modify_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'settings' => array(
      'show_all_tokens' => 1,
      'display_values' => array(
        '_all_' => '_all_',
      ),
    ),
    'postpone_processing' => 0,
  ),
  'action::views_bulk_operations_argument_selector_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'settings' => array(
      'url' => '',
    ),
  ),
  'action::system_goto_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'postpone_processing' => 0,
  ),
  'action::system_send_email_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'postpone_processing' => 0,
  ),
  'action::commerce_event_ticket_validate_action' => array(
    'selected' => 1,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => 'Validate ticket(s)',
    'postpone_processing' => 0,
  ),
);
/* Field: Event ticket: Ticket ID */
$handler->display->display_options['fields']['ticket_id']['id'] = 'ticket_id';
$handler->display->display_options['fields']['ticket_id']['table'] = 'commerce_event_ticket';
$handler->display->display_options['fields']['ticket_id']['field'] = 'ticket_id';
$handler->display->display_options['fields']['ticket_id']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['ticket_id']['alter']['path'] = 'admin/commerce/tickets/[ticket_id]';
$handler->display->display_options['fields']['ticket_id']['separator'] = '';
/* Field: Event ticket: Validity */
$handler->display->display_options['fields']['valid']['id'] = 'valid';
$handler->display->display_options['fields']['valid']['table'] = 'commerce_event_ticket';
$handler->display->display_options['fields']['valid']['field'] = 'valid';
$handler->display->display_options['fields']['valid']['label'] = 'Valid?';
$handler->display->display_options['fields']['valid']['type'] = 'unicode-yes-no';
$handler->display->display_options['fields']['valid']['not'] = 0;
/* Field: Event ticket: Used */
$handler->display->display_options['fields']['used']['id'] = 'used';
$handler->display->display_options['fields']['used']['table'] = 'commerce_event_ticket';
$handler->display->display_options['fields']['used']['field'] = 'used';
$handler->display->display_options['fields']['used']['label'] = 'Used?';
$handler->display->display_options['fields']['used']['not'] = 0;
/* Field: Commerce Order: Created date */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'commerce_order';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['relationship'] = 'order_id';
$handler->display->display_options['fields']['created']['label'] = 'Order date';
$handler->display->display_options['fields']['created']['date_format'] = 'short';
$handler->display->display_options['fields']['created']['second_date_format'] = 'long';
/* Field: Commerce Order: Order number */
$handler->display->display_options['fields']['order_number']['id'] = 'order_number';
$handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
$handler->display->display_options['fields']['order_number']['field'] = 'order_number';
$handler->display->display_options['fields']['order_number']['relationship'] = 'order_id';
$handler->display->display_options['fields']['order_number']['link_to_order'] = 'admin';
/* Field: Commerce Product: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'commerce_product';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'product_id';
$handler->display->display_options['fields']['title']['label'] = 'Product';
$handler->display->display_options['fields']['title']['link_to_product'] = 1;
/* Field: Commerce Line item: Unit price */
$handler->display->display_options['fields']['commerce_unit_price']['id'] = 'commerce_unit_price';
$handler->display->display_options['fields']['commerce_unit_price']['table'] = 'field_data_commerce_unit_price';
$handler->display->display_options['fields']['commerce_unit_price']['field'] = 'commerce_unit_price';
$handler->display->display_options['fields']['commerce_unit_price']['relationship'] = 'line_item_id';
$handler->display->display_options['fields']['commerce_unit_price']['click_sort_column'] = 'amount';
$handler->display->display_options['fields']['commerce_unit_price']['settings'] = array(
  'calculation' => FALSE,
);
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'User';
/* Filter criterion: Event ticket: Barcode token */
$handler->display->display_options['filters']['barcode_token']['id'] = 'barcode_token';
$handler->display->display_options['filters']['barcode_token']['table'] = 'commerce_event_ticket';
$handler->display->display_options['filters']['barcode_token']['field'] = 'barcode_token';
$handler->display->display_options['filters']['barcode_token']['group'] = 1;
$handler->display->display_options['filters']['barcode_token']['exposed'] = TRUE;
$handler->display->display_options['filters']['barcode_token']['expose']['operator_id'] = 'barcode_token_op';
$handler->display->display_options['filters']['barcode_token']['expose']['label'] = 'Barcode';
$handler->display->display_options['filters']['barcode_token']['expose']['operator'] = 'barcode_token_op';
$handler->display->display_options['filters']['barcode_token']['expose']['identifier'] = 'barcode_token';
$handler->display->display_options['filters']['barcode_token']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
);
/* Filter criterion: Commerce Order: Order number */
$handler->display->display_options['filters']['order_number']['id'] = 'order_number';
$handler->display->display_options['filters']['order_number']['table'] = 'commerce_order';
$handler->display->display_options['filters']['order_number']['field'] = 'order_number';
$handler->display->display_options['filters']['order_number']['relationship'] = 'order_id';
$handler->display->display_options['filters']['order_number']['group'] = 1;
$handler->display->display_options['filters']['order_number']['exposed'] = TRUE;
$handler->display->display_options['filters']['order_number']['expose']['operator_id'] = 'order_number_op';
$handler->display->display_options['filters']['order_number']['expose']['label'] = 'Order number';
$handler->display->display_options['filters']['order_number']['expose']['operator'] = 'order_number_op';
$handler->display->display_options['filters']['order_number']['expose']['identifier'] = 'order_number';
$handler->display->display_options['filters']['order_number']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
);
/* Filter criterion: User: E-mail */
$handler->display->display_options['filters']['mail']['id'] = 'mail';
$handler->display->display_options['filters']['mail']['table'] = 'users';
$handler->display->display_options['filters']['mail']['field'] = 'mail';
$handler->display->display_options['filters']['mail']['relationship'] = 'uid';
$handler->display->display_options['filters']['mail']['operator'] = 'contains';
$handler->display->display_options['filters']['mail']['group'] = 1;
$handler->display->display_options['filters']['mail']['exposed'] = TRUE;
$handler->display->display_options['filters']['mail']['expose']['operator_id'] = 'mail_op';
$handler->display->display_options['filters']['mail']['expose']['label'] = 'E-mail';
$handler->display->display_options['filters']['mail']['expose']['operator'] = 'mail_op';
$handler->display->display_options['filters']['mail']['expose']['identifier'] = 'mail';
$handler->display->display_options['filters']['mail']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
);
/* Filter criterion: Content: Title */
$handler->display->display_options['filters']['title_1']['id'] = 'title_1';
$handler->display->display_options['filters']['title_1']['table'] = 'node';
$handler->display->display_options['filters']['title_1']['field'] = 'title';
$handler->display->display_options['filters']['title_1']['relationship'] = 'nid';
$handler->display->display_options['filters']['title_1']['operator'] = 'allwords';
$handler->display->display_options['filters']['title_1']['group'] = 1;
$handler->display->display_options['filters']['title_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['title_1']['expose']['operator_id'] = 'title_1_op';
$handler->display->display_options['filters']['title_1']['expose']['label'] = 'Content title';
$handler->display->display_options['filters']['title_1']['expose']['operator'] = 'title_1_op';
$handler->display->display_options['filters']['title_1']['expose']['identifier'] = 'title_1';
$handler->display->display_options['filters']['title_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
);
/* Filter criterion: Commerce Product: Title */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'commerce_product';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['relationship'] = 'product_id';
$handler->display->display_options['filters']['title']['operator'] = 'allwords';
$handler->display->display_options['filters']['title']['group'] = 1;
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Product title';
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
);
/* Filter criterion: Event ticket: Used */
$handler->display->display_options['filters']['used']['id'] = 'used';
$handler->display->display_options['filters']['used']['table'] = 'commerce_event_ticket';
$handler->display->display_options['filters']['used']['field'] = 'used';
$handler->display->display_options['filters']['used']['value'] = 'All';
$handler->display->display_options['filters']['used']['group'] = 1;
$handler->display->display_options['filters']['used']['exposed'] = TRUE;
$handler->display->display_options['filters']['used']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['used']['expose']['label'] = 'Used';
$handler->display->display_options['filters']['used']['expose']['operator'] = 'used_op';
$handler->display->display_options['filters']['used']['expose']['identifier'] = 'used';
$handler->display->display_options['filters']['used']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'admin/commerce/tickets/list';
$handler->display->display_options['menu']['type'] = 'default tab';
$handler->display->display_options['menu']['title'] = 'List';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$handler->display->display_options['tab_options']['type'] = 'normal';
$handler->display->display_options['tab_options']['title'] = 'Tickets';
$handler->display->display_options['tab_options']['description'] = 'Manage event tickets.';
$handler->display->display_options['tab_options']['weight'] = '0';
$handler->display->display_options['tab_options']['name'] = 'management';

$views[$view->name] = $view;
