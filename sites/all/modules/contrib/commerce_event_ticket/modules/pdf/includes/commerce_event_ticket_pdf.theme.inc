<?php
/**
 * @file
 * Theme functions for the Commerce Event Ticket PDF module.
 */

/**
 * Preprocess function for theming the information on an event ticket PDF.
 */
function template_preprocess_commerce_event_ticket_pdf_info(&$variables) {
  $ticket = $variables['ticket'];

  $order = commerce_order_load($ticket->order_id);
  $product = commerce_product_load($ticket->product_id);
  $owner = user_load($order->uid);
  $node = node_load($ticket->nid);

  if ($node) {
    $variables['nid'] = $node->nid;
    $variables['node_title'] = check_plain($node->title);
    $variables['node_path'] = 'node/' . $node->nid;
    $node_products_count = commerce_event_ticket_count_node_products($node);
    global $base_url;
    if ($base_url && ($domain = parse_url($base_url, PHP_URL_HOST))) {
      $variables['node_shortlink'] = $domain . base_path() . $variables['node_path'];
    }
  }

  $variables['display_product_title'] = !$node || ($node_products_count > 1 && $product->title != $node->title);
  $variables['product_title'] = check_plain($product->title);

  $variables['data'] = array(
    t('Order number') => $order->order_number,
    t('Order date') => format_date($order->created),
    t('Customer') => format_username($owner),
  );

  $unit_price = commerce_event_ticket_get_unit_price($ticket);
  if ($unit_price) {
    $variables['data'][t('Unit price')] = $unit_price;
  }
}

/**
 * Theme the information on an event ticket PDF.
 */
function theme_commerce_event_ticket_pdf_info($variables) {
  $output = array();
  $output['title'] = array(
    '#prefix' => '<h1>',
    '#suffix' => '</h1>',
    '#markup' => t('TICKET'),
  );
  if (isset($variables['nid'])) {
    $output['subtitle'] = array(
      '#prefix' => '<h2>',
      '#suffix' => '</h2>',
      '#markup' => $variables['node_title'],
    );
    if (isset($variables['node_shortlink'])) {
      $output['shortlink'] = array(
        '#prefix' => '<p>',
        '#suffix' => '</p>',
        '#markup' => l(
          $variables['node_shortlink'],
          $variables['node_path'],
          array('absolute' => TRUE, 'html' => TRUE)
        ),
      );
    }
  }
  if ($variables['display_product_title']) {
    $output['product_title'] = array(
      '#prefix' => '<p>',
      '#suffix' => '</p>',
      '#markup' => t('Product: !title', array('!title' => $variables['product_title'])),
    );
  }
  $rows = array();
  foreach ($variables['data'] as $label => $value) {
    $rows[] = array('<strong>' . $label . '</strong>', $value);
  }
  $output['table'] = array(
    '#theme' => 'table',
    '#header' => array(),
    '#rows' => $rows,
    '#attributes' => array(
      'cellpadding' => '10',
    ),
  );
  return drupal_render($output);
}
