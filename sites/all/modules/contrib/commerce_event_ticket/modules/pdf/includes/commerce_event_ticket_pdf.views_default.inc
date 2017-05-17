<?php
/**
 * @file
 * Default Views for the Commerce Event Ticket PDF module.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_event_ticket_pdf_views_default_views() {
  $views_dir = drupal_get_path('module', 'commerce_event_ticket_pdf') . '/includes/views';
  $views_files = scandir($views_dir);
  $views = array();
  foreach ($views_files as $filename) {
    if (substr($filename, -4) == '.inc') {
      include_once $views_dir . '/' . $filename;
    }
  }
  return $views;
}

/**
 * Implements hook_views_default_views_alter().
 */
function commerce_event_ticket_pdf_views_default_views_alter(&$views) {
  // Alter the default Tickets view (admin/commerce/tickets) to add a "View PDF"
  // link next to each ticket.
  if (isset($views['commerce_event_tickets'])) {
    $view = $views['commerce_event_tickets'];
    if (!isset($view->display['default'])) {
      return;
    }
    $handler = $view->display['default']->handler;
    $handler->display->display_options['style_options']['columns']['line_item_ticket_pdf'] = 'line_item_ticket_pdf';
    $handler->display->display_options['style_options']['info']['line_item_ticket_pdf'] = array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    );
    $handler->display->display_options['fields']['line_item_ticket_pdf']['id'] = 'line_item_ticket_pdf';
    $handler->display->display_options['fields']['line_item_ticket_pdf']['table'] = 'commerce_line_item';
    $handler->display->display_options['fields']['line_item_ticket_pdf']['field'] = 'line_item_ticket_pdf';
    $handler->display->display_options['fields']['line_item_ticket_pdf']['relationship'] = 'line_item_id';
    $handler->display->display_options['fields']['line_item_ticket_pdf']['label'] = 'PDF (line item)';
  }

  // Alter the default Line Items view (shown on orders) to add a "Ticket(s)
  // (PDF)" link next to each line item.
  if (isset($views['commerce_line_item_table'])) {
    $view = $views['commerce_line_item_table'];
    if (!isset($view->display['default'])) {
      return;
    }
    $handler = $view->display['default']->handler;
    $handler->display->display_options['style_options']['columns']['line_item_ticket_pdf'] = 'line_item_ticket_pdf';
    $handler->display->display_options['style_options']['info']['line_item_ticket_pdf'] = array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    );
    $handler->display->display_options['fields']['line_item_ticket_pdf']['id'] = 'line_item_ticket_pdf';
    $handler->display->display_options['fields']['line_item_ticket_pdf']['table'] = 'commerce_line_item';
    $handler->display->display_options['fields']['line_item_ticket_pdf']['field'] = 'line_item_ticket_pdf';
    $handler->display->display_options['fields']['line_item_ticket_pdf']['label'] = t('Tickets');
    $handler->display->display_options['fields']['line_item_ticket_pdf']['hide_empty'] = TRUE;
  }

  // Alter the default User Orders view (user/%/orders) to add a "Ticket(s)
  // (PDF)" link next to each order.
  if (isset($views['commerce_user_orders'])) {
    $view = $views['commerce_user_orders'];
    if (!isset($view->display['default'])) {
      return;
    }
    $handler = $view->display['default']->handler;
    $handler->display->display_options['style_options']['columns']['order_ticket_pdf'] = 'order_ticket_pdf';
    $handler->display->display_options['style_options']['info']['order_ticket_pdf'] = array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    );
    $handler->display->display_options['fields']['order_ticket_pdf']['id'] = 'order_ticket_pdf';
    $handler->display->display_options['fields']['order_ticket_pdf']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['order_ticket_pdf']['field'] = 'order_ticket_pdf';
    $handler->display->display_options['fields']['order_ticket_pdf']['label'] = 'Tickets';
    $handler->display->display_options['fields']['order_ticket_pdf']['hide_empty'] = TRUE;
  }
}
