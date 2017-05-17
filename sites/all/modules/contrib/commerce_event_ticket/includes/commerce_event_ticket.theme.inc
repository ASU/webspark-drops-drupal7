<?php
/**
 * @file
 * Theme functions for the Commerce Event Ticket module.
 */

/**
 * Preprocess variables for displaying a ticket.
 */
function template_preprocess_commerce_event_ticket(&$variables) {
  $ticket = $variables['ticket'];
  $product = commerce_product_load($ticket->product_id);
  $order = commerce_order_load($ticket->order_id);
  $node = isset($ticket->nid) ? node_load($ticket->nid) : FALSE;

  if ($node) {
    $node_products_count = commerce_event_ticket_count_node_products($node);
  }

  $variables['qr'] = array(
    '#theme' => 'image',
    '#path' => 'https://chart.googleapis.com/chart?cht=qr&chl=' . $ticket->barcode_token . '&chs=150x150&chld=L|1',
    '#width' => 150,
    '#height' => 150,
    '#alt' => t('QR code: @token', array('@token' => $ticket->barcode_token)),
    '#attributes' => array(
      'class' => array('commerce-event-ticket-qr'),
    ),
  );
  $variables['valid'] = commerce_event_ticket_is_valid($ticket);
  $variables['reason'] = commerce_event_ticket_explain_validity($ticket);

  $variables['number'] = t('@number of @quantity', array(
    '@number' => $ticket->number,
    '@quantity' => $ticket->quantity,
  ));

  // Find the next and previous tickets so that they can be linked.
  if ($ticket->quantity > 1) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'commerce_event_ticket')
      ->propertyCondition('line_item_id', $ticket->line_item_id)
      ->propertyCondition('number', $ticket->number - 1, '>=')
      ->propertyCondition('number', $ticket->number, '<>')
      ->propertyCondition('number', $ticket->number + 1, '<=')
      ->propertyOrderBy('number')
      ->range(0, 2);
    $result = $query->execute();
    $admin = $variables['view_mode'] == 'administrator';
    $path_prefix = $admin ? 'admin/commerce/tickets/' : 'event-ticket/';
    if (!empty($result['commerce_event_ticket'])) {
      if ($ticket->number > 1) {
        $previous = reset($result['commerce_event_ticket']);
        $variables['previous_link'] = l(t('previous'), $path_prefix . $previous->ticket_id);
      }
      if ($ticket->number < $ticket->quantity) {
        $next = end($result['commerce_event_ticket']);
        if ($next && (!isset($previous) || $next->ticket_id != $previous->ticket_id)) {
          $variables['next_link'] = l(t('next'), $path_prefix . $next->ticket_id);
        }
      }
    }
  }

  $variables['display_product_title'] = !$node || ($node_products_count > 1 && $product->title != $node->title);
  $variables['product_title'] = check_plain($product->title);
  $variables['unit_price'] = commerce_event_ticket_get_unit_price($ticket);
  $variables['node_title'] = $node ? check_plain($node->title) : FALSE;
  $variables['nid'] = $node ? $node->nid : FALSE;
  $variables['order_number'] = intval($order->order_number);
  $variables['order_created'] = format_date($order->created);
  $variables['order_status'] = check_plain(commerce_order_status_get_title($order->status));
  $variables['customer'] = theme('username', array('account' => user_load($order->uid)));

  // Link the order number to the admin view page for admins, or the customer
  // view page for customers.
  if (commerce_order_admin_order_view_access($order)) {
    $variables['order_number'] = l($order->order_number, 'admin/commerce/orders/' . $order->order_id);
  }
  elseif (commerce_order_customer_order_view_access($order)) {
    $variables['order_number'] = l($order->order_number, 'user/' . $order->uid . '/orders/' . $order->order_id);
  }
}

/**
 * Theme function for displaying a ticket.
 */
function theme_commerce_event_ticket($variables) {
  $header = array();
  $rows = array();

  $rows[] = array(t('Valid?'), $variables['valid'] ? t('Yes') : t('No (@reason)', array(
    '@reason' => $variables['reason'],
  )));

  $number = $variables['number'];
  if (isset($variables['previous_link'])) {
    $number .= ' (' . $variables['previous_link'] . ')';
  }
  if (isset($variables['next_link'])) {
    $number .= ' (' . $variables['next_link'] . ')';
  }
  $rows[] = array(t('Number'), $number);

  if ($variables['nid']) {
    $rows[] = array(
      t('Event'),
      l($variables['node_title'], 'node/' . $variables['nid'], array(
        'html' => TRUE,
      )),
    );
  }

  if ($variables['display_product_title']) {
    $rows[] = array(t('Product'), $variables['product_title']);
  }

  if ($variables['unit_price']) {
    $rows[] = array(t('Unit price'), $variables['unit_price']);
  }

  $rows[] = array(t('Order number'), $variables['order_number']);
  $rows[] = array(t('Order date'), $variables['order_created']);
  $rows[] = array(t('Customer'), $variables['customer']);

  $table = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#attributes' => array(
      'class' => array('commerce-event-ticket-info'),
    ),
  );

  $output = array();

  if (!empty($variables['qr'])) {
    $output['qr'] = array(
      '#theme' => 'container',
      '#attributes' => array(
        'class' => array('commerce-event-ticket-qr-wrapper'),
      ),
      '#children' => drupal_render($variables['qr']),
    );
  }

  $output['#attached']['css'][] = drupal_get_path('module', 'commerce_event_ticket') . '/css/commerce_event_ticket.css';

  $output['table'] = $table;
  return drupal_render($output);
}
