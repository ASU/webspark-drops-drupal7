<?php
/**
 * @file
 * Commerce Registration default views.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_registration_views_default_views() {
  $view = new view;
  $view->name = 'commerce_registration_admin_regs';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'registration';
  $view->human_name = 'Commerce Registration Admin Registrations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Completed Registrations';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'registration_id' => 'registration_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'registration_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no finalized registrations.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Registration: Commerce Order ID */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'registration';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['required'] = 0;
  /* Relationship: Registration: State entity */
  $handler->display->display_options['relationships']['state']['id'] = 'state';
  $handler->display->display_options['relationships']['state']['table'] = 'registration';
  $handler->display->display_options['relationships']['state']['field'] = 'state';
  $handler->display->display_options['relationships']['state']['required'] = 0;
  /* Field: Registration: View link */
  $handler->display->display_options['fields']['view_registration']['id'] = 'view_registration';
  $handler->display->display_options['fields']['view_registration']['table'] = 'registration';
  $handler->display->display_options['fields']['view_registration']['field'] = 'view_registration';
  $handler->display->display_options['fields']['view_registration']['label'] = '';
  $handler->display->display_options['fields']['view_registration']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['view_registration']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_registration']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_registration']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_registration']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['view_registration']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_registration']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_registration']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_registration']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['view_registration']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_registration']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_registration']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_registration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_registration']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_registration']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_registration']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_registration']['hide_alter_empty'] = 1;
  /* Field: Registration: Registration ID */
  $handler->display->display_options['fields']['registration_id']['id'] = 'registration_id';
  $handler->display->display_options['fields']['registration_id']['table'] = 'registration';
  $handler->display->display_options['fields']['registration_id']['field'] = 'registration_id';
  $handler->display->display_options['fields']['registration_id']['label'] = 'Number';
  $handler->display->display_options['fields']['registration_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['registration_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['registration_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['registration_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['registration_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['registration_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['registration_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['registration_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['registration_id']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['registration_id']['separator'] = '';
  $handler->display->display_options['fields']['registration_id']['format_plural'] = 0;
  /* Field: Registration: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'registration';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date Entered';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Registration: Attached Commerce Product */
  $handler->display->display_options['fields']['registration_attached_entity']['id'] = 'registration_attached_entity';
  $handler->display->display_options['fields']['registration_attached_entity']['table'] = 'registration';
  $handler->display->display_options['fields']['registration_attached_entity']['field'] = 'registration_attached_entity';
  $handler->display->display_options['fields']['registration_attached_entity']['label'] = 'Product';
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['registration_attached_entity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['registration_attached_entity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['registration_attached_entity']['hide_alter_empty'] = 1;
  /* Field: Commerce Order: Order number */
  $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['order_number']['label'] = 'Order';
  $handler->display->display_options['fields']['order_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['order_number']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['order_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['order_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['order_number']['empty_zero'] = 0;
  $handler->display->display_options['fields']['order_number']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['order_number']['link_to_order'] = 'admin';
  /* Field: Commerce Order: Order total */
  $handler->display->display_options['fields']['commerce_order_total']['id'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['table'] = 'field_data_commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['field'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['commerce_order_total']['label'] = 'Total';
  $handler->display->display_options['fields']['commerce_order_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_order_total']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_order_total']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_order_total']['field_api_classes'] = 0;
  /* Field: Commerce Order: Order status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['status']['label'] = 'Order Status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['status']['hide_alter_empty'] = 1;
  /* Field: Registration State: Label */
  $handler->display->display_options['fields']['label']['id'] = 'label';
  $handler->display->display_options['fields']['label']['table'] = 'registration_state';
  $handler->display->display_options['fields']['label']['field'] = 'label';
  $handler->display->display_options['fields']['label']['relationship'] = 'state';
  $handler->display->display_options['fields']['label']['label'] = 'Registration state';
  $handler->display->display_options['fields']['label']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['label']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['label']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['label']['alter']['external'] = 0;
  $handler->display->display_options['fields']['label']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['label']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['label']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['label']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['label']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['label']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['label']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['label']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['label']['alter']['html'] = 0;
  $handler->display->display_options['fields']['label']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['label']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['label']['hide_empty'] = 0;
  $handler->display->display_options['fields']['label']['empty_zero'] = 0;
  $handler->display->display_options['fields']['label']['hide_alter_empty'] = 1;
  /* Sort criterion: Registration: Date created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'registration';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Registration State: Label */
  $handler->display->display_options['filters']['label']['id'] = 'label';
  $handler->display->display_options['filters']['label']['table'] = 'registration_state';
  $handler->display->display_options['filters']['label']['field'] = 'label';
  $handler->display->display_options['filters']['label']['relationship'] = 'state';
  $handler->display->display_options['filters']['label']['value'] = 'Complete';

  /* Display: Completed Registrations with Order ID */
  $handler = $view->new_display('block', 'Completed Registrations with Order ID', 'commerce_regs_w_order');

  /* Display: All Registrations */
  $handler = $view->new_display('block', 'All Registrations', 'commerce_regs_all');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All Registrations';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Registration: Commerce Order ID */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'registration';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['required'] = 0;
  /* Relationship: Registration: State entity */
  $handler->display->display_options['relationships']['state']['id'] = 'state';
  $handler->display->display_options['relationships']['state']['table'] = 'registration';
  $handler->display->display_options['relationships']['state']['field'] = 'state';
  $handler->display->display_options['relationships']['state']['required'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;

  $views['commerce_registration_admin_registrations'] = $view;

  return $views;
}
