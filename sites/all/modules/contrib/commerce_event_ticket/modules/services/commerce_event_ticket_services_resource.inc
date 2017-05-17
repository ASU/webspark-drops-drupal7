<?php
/**
 * @file
 * Resource callbacks for the Commerce Event Ticket Services module.
 */

/**
 * Retrieve a list of nodes that have event tickets.
 *
 * @param int $offset
 * @param int $limit
 * @param bool $date_filter
 * @param bool $date_sort
 */
function commerce_event_ticket_services_list_event_ticket_nodes($offset = 0, $limit = 50, $date_filter = TRUE, $date_sort = TRUE) {
  drupal_add_http_header('Access-Control-Allow-Origin', '*');

  $access_for_own_nodes = user_access('mark used commerce event tickets given node update access');
  $access_all = user_access('mark used any commerce event tickets')
    || user_access('update all commerce event tickets')
    || ($access_for_own_nodes && user_access('bypass_node_access'));

  if (!$access_all && !$access_for_own_nodes) {
    // This should not happen because of the check in
    // commerce_event_ticket_services_access_ticket_nodes().
    return services_error(t('Access denied'), 403);
  }

  if ($limit > 100) {
    $limit = 100;
  }

  // EntityFieldQuery should be used here instead of db_select(), but
  // unfortunately it doesn't support joins, so there would be no way to check
  // in the same query that the nodes "have tickets".
  $query = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->distinct();
  $query->addTag('node_access');
  $query->join('commerce_event_ticket', 'cet', 'cet.nid = n.nid');
  $query->range($offset, $limit);

  // Get configured event date field(s), if any.
  $date_field_names = variable_get('commerce_event_ticket_date_fields', array());

  // Filter or sort the nodes based on the date, if enabled.
  if ($date_field_names && ($date_filter || $date_sort)) {
    foreach ($date_field_names as $field_name) {
      // Join to the field's table.
      $query->join('field_data_' . $field_name, 'dates', 'dates.entity_id = n.nid');
      $column = 'dates.' . $field_name . '_value';
      // Order events by date.
      if ($date_sort) {
        $query->orderBy($column);
      }
      if ($date_filter) {
        // Filter the nodes to those whose dates are today or later.
        $comparison_timestamp = strtotime('today');
        // Date fields can be stored in one of three different types.
        $field_info = field_info_field($field_name);
        switch ($field_info['type']) {
          case 'date':
            $query->condition($column, date('Y-m-d', $comparison_timestamp), '>=');
            break;

          case 'datetime':
            $query->condition($column, date('Y-m-d H:i:s', $comparison_timestamp), '>');
            break;

          case 'datestamp':
            $query->condition($column, $comparison_timestamp, '>');
            break;
        }
      }
      break;
    }
  }

  $query->orderBy('n.title');

  $nids = $query->execute()->fetchCol();
  if (!$nids) {
    return array();
  }

  $nodes = node_load_multiple($nids);

  // Build an array of simplified node information.
  $output = array();
  foreach ($nodes as $nid => $node) {
    // Filter out nodes that the user doesn't have access to update.
    if (!$access_all && !node_access('update', $node)) {
      continue;
    }
    // Add the node ID and node title.
    $output[$nid] = array('nid' => $nid, 'title' => $node->title);
    // Add the event start and end dates, if possible.
    $date = commerce_event_ticket_get_date($node);
    if ($date) {
      $output[$nid]['start_date'] = date('c', $date['start']);
      if ($date['start'] != $date['end']) {
        $output[$nid]['end_date'] = date('c', $date['end']);
      }
    }
  }
  return $output;
}

/**
 * Retrieve a list of tickets for a product display node.
 *
 * @see commerce_event_ticket_services_access_tickets_per_node()
 */
function commerce_event_ticket_services_retrieve_tickets_per_node($nid, $offset = 0, $limit = 50, $changed_since = 0) {
  drupal_add_http_header('Access-Control-Allow-Origin', '*');

  if ($limit > 100) {
    $limit = 100;
  }

  // Find the ticket IDs.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'commerce_event_ticket')
    ->propertyCondition('nid', $nid)
    ->propertyCondition('changed', $changed_since, '>=')
    ->propertyOrderBy('ticket_id')
    ->range($offset, $limit);
  $result = $query->execute();
  if (!$result || empty($result['commerce_event_ticket'])) {
    return array();
  }

  $tickets = commerce_event_ticket_load_multiple(array_keys($result['commerce_event_ticket']));

  $info = array();
  foreach ($tickets as $ticket) {
    $validity = commerce_event_ticket_explain_validity($ticket);
    $info[$ticket->ticket_id] = array(
      'valid' => $validity === TRUE,
      'reason' => $validity === TRUE ? NULL : $validity,
      'barcode_token' => $ticket->barcode_token,
      'ticket_id' => $ticket->ticket_id,
      'used' => (bool) $ticket->used,
      'position' => t('@number of @count', array(
        '@number' => $ticket->number,
        '@count' => $ticket->quantity,
      )),
      'created' => date('c', $ticket->created),
      'changed' => date('c', $ticket->changed),
    );
  }

  return $info;
}

/**
 * Validate callback to mark a ticket as used.
 */
function commerce_event_ticket_services_validate_ticket($barcode, $log = NULL) {
  $ticket = commerce_event_ticket_load_by_barcode($barcode);
  if (!$ticket) {
    return services_error(t('Ticket not found'), 404);
  }
  $output = array();
  $log = empty($log) ? t('Validated via service.') : $log;
  $result = commerce_event_ticket_validate($ticket, TRUE, TRUE, $log);
  if ($result === TRUE) {
    $output['validated'] = TRUE;
  }
  else {
    drupal_add_http_header('Status', '400 ' . t('Ticket not validated'));
    $output['validated'] = FALSE;
    $output['reason'] = $result;
  }
  return $output;
}

/**
 * Validate callback to mark multiple tickets as used.
 */
function commerce_event_ticket_services_validate_multiple_tickets($barcodes, $log = NULL) {
  drupal_add_http_header('Access-Control-Allow-Origin', '*');
  if (count($barcodes) > 100) {
    return services_error(t('Maximum number of tickets exceeded'), 400);
  }
  elseif (count($barcodes) == 0) {
    return services_error(t('No tickets specified'), 400);
  }
  $ticket_ids = db_query('SELECT barcode_token, ticket_id FROM {commerce_event_ticket} WHERE barcode_token IN (:barcodes)', array(
    ':barcodes' => $barcodes,
  ))->fetchAllKeyed();
  $tickets = commerce_event_ticket_load_multiple($ticket_ids);
  $output = array();
  $log = empty($log) ? t('Validated via service.') : $log;
  foreach ($barcodes as $barcode) {
    $output[$barcode] = array();
    if (!isset($ticket_ids[$barcode]) || !isset($tickets[$ticket_ids[$barcode]])) {
      $output[$barcode]['found'] = FALSE;
      $output[$barcode]['validated'] = FALSE;
      continue;
    }
    $ticket = $tickets[$ticket_ids[$barcode]];
    $output[$barcode]['found'] = TRUE;
    $result = commerce_event_ticket_validate($ticket, TRUE, TRUE, $log);
    if ($result === TRUE) {
      $output[$barcode]['validated'] = TRUE;
    }
    else {
      $output[$barcode]['validated'] = FALSE;
      $output[$barcode]['reason'] = $result;
    }
  }
  return $output;
}

/**
 * Reset callback to mark a ticket as unused.
 */
function commerce_event_ticket_services_reset_ticket($barcode, $log = NULL) {
  $ticket = commerce_event_ticket_load_by_barcode($barcode);
  if (!$ticket) {
    return services_error(t('Ticket not found'), 404);
  }
  $output = array(
    'reset' => FALSE,
    'used' => FALSE,
  );
  if ($ticket->used) {
    $log = empty($log) ? t('Reset via service.') : $log;
    commerce_event_ticket_reset($ticket, TRUE, $log);
    $output['reset'] = !$ticket->used;
    $output['used'] = (bool) $ticket->used;
  }
  return $output;
}

/**
 * Retrieve callback to get ticket information based on a barcode.
 */
function commerce_event_ticket_services_retrieve_ticket($barcode) {
  $ticket = commerce_event_ticket_load_by_barcode($barcode);
  if (!$ticket) {
    return services_error(t('Ticket not found'), 404);
  }
  $valid = commerce_event_ticket_is_valid($ticket);
  if ($valid) {
    $reason = NULL;
  }
  else {
    $reason = commerce_event_ticket_explain_validity($ticket);
  }
  $output = array(
    'valid' => commerce_event_ticket_is_valid($ticket),
    'reason' => $reason,
    'barcode_token' => $ticket->barcode_token,
    'ticket_id' => $ticket->ticket_id,
    'used' => (bool) $ticket->used,
    'position' => t('@number of @count', array(
      '@number' => $ticket->number,
      '@count' => $ticket->quantity,
    )),
    'created' => date('c', $ticket->created),
    'changed' => date('c', $ticket->changed),
  );
  $access_all_info = user_access('view all info for a commerce event ticket');
  $order = commerce_order_load($ticket->order_id);
  if ($order && ($access_all_info || commerce_order_access('view', $order))) {
    $output['order'] = array(
      'order_id' => $order->order_id,
      'order_number' => $order->order_number,
      'status' => $order->status,
      'status_title' => commerce_order_status_get_title($order->status),
      'created' => date('c', $order->created),
      'changed' => date('c', $order->changed),
    );
    $owner = user_load($order->uid);
    if ($owner && ($access_all_info || user_view_access($owner))) {
      $output['order']['owner'] = array(
        'uid' => $order->uid,
        'name' => $owner->name,
        'mail' => $owner->mail,
        'username' => format_username($owner),
        'status' => $owner->status,
      );
    }
  }
  $line_item = commerce_line_item_load($ticket->line_item_id);
  if ($line_item && ($access_all_info || commerce_line_item_access('view', $line_item))) {
    $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
    $total_price = commerce_line_items_total(array($line_item_wrapper));
    $output['line_item'] = array(
      'line_item_id' => $line_item->line_item_id,
      'type' => $line_item->type,
      'quantity' => $line_item->quantity,
      'unit_price' => commerce_event_ticket_get_unit_price($ticket, $line_item_wrapper),
      'total_price' => commerce_currency_format($total_price['amount'], $total_price['currency_code']),
      'created' => date('c', $line_item->created),
      'changed' => date('c', $line_item->changed),
    );
  }
  $product = commerce_product_load($ticket->product_id);
  if ($product && ($access_all_info || commerce_product_access('view', $product))) {
    $output['product'] = array(
      'product_id' => $ticket->product_id,
      'title' => $product->title,
      'type' => $product->type,
      'status' => $product->status,
      'revision_id' => $product->revision_id,
      'created' => date('c', $product->created),
      'changed' => date('c', $product->changed),
    );
  }
  if ($ticket->nid) {
    $node = node_load($ticket->nid);
  }
  if (!empty($node) && ($access_all_info || node_access('view', $node))) {
    $uri = node_uri($node);
    $path = $uri['path'];
    $output['node'] = array(
      'nid' => $node->nid,
      'title' => $node->title,
      'type' => $node->type,
      'status' => $node->status,
      'vid' => $node->vid,
      'created' => date('c', $node->created),
      'changed' => date('c', $node->changed),
      'path_raw' => $GLOBALS['base_path'] . $path,
      'path' => url($path),
    );
  }
  return $output;
}
