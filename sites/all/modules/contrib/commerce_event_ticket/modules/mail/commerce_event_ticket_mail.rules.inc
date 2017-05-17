<?php
/**
 * @file
 * Rules integration for the Commerce Event Ticket Mail module.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_event_ticket_mail_rules_action_info() {
  $defaults = array(
    'group' => t('Commerce Event Ticket'),
    'module' => 'commerce_event_ticket_mail',
    'access callback' => 'commerce_event_ticket_rules_config_access',
  );
  $actions = array();
  $actions['commerce_event_ticket_mail_for_order'] = $defaults + array(
    'label' => t("Send an order's tickets by e-mail as attachments"),
    'named parameter' => TRUE,
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('The order'),
      ),
      'to' => array(
        'type' => 'text',
        'label' => t('To'),
        'description' => t("The mail's recipient address. The formatting of this string must comply with RFC 2822."),
        'default value' => '[commerce-order:mail]',
      ),
      'from_name' => array(
        'type' => 'text',
        'label' => t('Sender name'),
        'description' => t("The sender's name. Leave it empty to use the site-wide configured name."),
        'optional' => TRUE,
      ),
      'from_mail' => array(
        'type' => 'text',
        'label' => t('Sender e-mail address'),
        'description' => t("The sender's address. Leave it empty to use the site-wide configured address."),
        'optional' => TRUE,
      ),
      'subject' => array(
        'type' => 'text',
        'label' => t('Subject'),
        'description' => t("The mail's subject."),
        'translatable' => TRUE,
        'default value' => t('Your tickets for order [commerce-order:order-number]'),
      ),
      'body' => array(
        'type' => 'text_formatted',
        'label' => t('Body'),
        'description' => t("The mail's message HTML body."),
        'sanitize' => TRUE,
        'optional' => TRUE,
        'translatable' => TRUE,
      ),
      'plaintext' => array(
        'type' => 'text',
        'label' => t('Plain-text body'),
        'description' => t("The mail's message plain-text body."),
        'optional' => TRUE,
        'translatable' => TRUE,
      ),
      'send_without_tickets' => array(
        'type' => 'boolean',
        'label' => t('Send the e-mail even if the order has no tickets'),
        'description' => t("If enabled, this e-mail will be sent regardless of whether the order has tickets. This could be useful for sending a general-purpose order confirmation e-mail."),
        'optional' => TRUE,
        'default value' => FALSE,
      ),
      'subject_no_tickets' => array(
        'type' => 'text',
        'label' => t('Subject (without tickets)'),
        'description' => t("The mail's subject, if the order does not have tickets. Leave blank to use the same subject as above."),
        'optional' => TRUE,
        'translatable' => TRUE,
        'default value' => t('Your tickets for order [commerce-order:order-number]'),
      ),
      'body_no_tickets' => array(
        'type' => 'text_formatted',
        'label' => t('Body (without tickets)'),
        'description' => t("The mail's message HTML body, only if the order does not have tickets. Leave blank to use the same body as above."),
        'sanitize' => TRUE,
        'optional' => TRUE,
        'translatable' => TRUE,
      ),
      'plaintext_no_tickets' => array(
        'type' => 'text',
        'label' => t('Plain-text body (without tickets)'),
        'description' => t("The mail's message plaintext body, if the order does not have tickets. Leave blank to use the same plain-text body as above."),
        'optional' => TRUE,
        'translatable' => TRUE,
      ),
    ),
  );
  return $actions;
}

/**
 * Rules action: send an e-mail containing an order's tickets as attachments.
 *
 * First the order is examined to check whether it has any tickets in it.
 * Tickets and PDF files (for each line item) are created if necessary. An
 * e-mail is sent with the provided parameters (subject, body, to, etc.), and
 * all of the line items' PDF files are attached automatically.
 */
function commerce_event_ticket_mail_for_order(array $parameters) {
  $required_params = array(
    'commerce_order',
    'to',
    'subject',
  );
  $default_params = array(
    'from_name' => NULL,
    'from_mail' => NULL,
    'body' => NULL,
    'plaintext' => NULL,
    'send_without_tickets' => FALSE,
    'subject_no_tickets' => NULL,
    'body_no_tickets' => NULL,
    'plaintext_no_tickets' => NULL,
  );
  foreach ($required_params as $required_param) {
    if (empty($parameters[$required_param])) {
      throw new Exception(t('Missing required parameter @param', array('@param' => $required_param)));
    }
  }
  $parameters = array_merge($default_params, $parameters);

  $order = $parameters['commerce_order'];

  // Create the tickets for the order, if they don't already exist.
  $tickets = commerce_event_ticket_create_from_order($order);
  if (!$tickets && !$parameters['send_without_tickets']) {
    return;
  }

  // Create the PDF files for each line item, if they haven't already been
  // created, and format them as attachments for the Mime Mail module.
  $attachments = array();
  if ($tickets) {
    $tickets_by_line_item = array();
    foreach ($tickets as $ticket) {
      if (!$ticket->used && commerce_event_ticket_is_valid($ticket)) {
        $tickets_by_line_item[$ticket->line_item_id][$ticket->ticket_id] = $ticket;
      }
    }
    $line_items = commerce_line_item_load_multiple(array_keys($tickets_by_line_item));
    foreach ($tickets_by_line_item as $line_item_id => $line_item_tickets) {
      $line_item = $line_items[$line_item_id];
      $file = commerce_event_ticket_pdf_create($line_item, 'commerce_line_item', $line_item_tickets);
      if (!$file) {
        continue;
      }

      // Set up the attachment array structure.
      $attachment['filemime'] = 'application/pdf';
      $attachment['filecontent'] = file_get_contents($file->uri);

      // Create a filename based on the product title, OR the node title if the
      // node only has one product.
      $ticket = reset($line_item_tickets);
      $node = node_load($ticket->nid);
      if ($node && commerce_event_ticket_count_node_products($node) == 1) {
        $filename = $node->title;
      }
      else {
        $product = commerce_product_load($ticket->product_id);
        $filename = $product->title;
      }

      // Sanitize the filename so it can only contain letters, numbers,
      // hyphens, and underscores.
      $sanitized = preg_replace('/[^0-9a-z\-]+/i', '_', trim($filename));
      $attachment['filename'] = $sanitized . '.pdf';

      $attachments[] = $attachment;
    }
    if (empty($attachments) && !$parameters['send_without_tickets']) {
      return;
    }
  }

  // Allow different subject, body, and plaintext parameters for when the order
  // does not contain tickets.
  $subject = $parameters['subject'];
  $body = $parameters['body'];
  $plaintext = $parameters['plaintext'];
  if (empty($attachments)) {
    if (!empty($parameters['subject_no_tickets'])) {
      $subject = $parameters['subject_no_tickets'];
    }
    if (!empty($parameters['body_no_tickets'])) {
      $body = $parameters['body_no_tickets'];
    }
    if (!empty($parameters['plaintext_no_tickets'])) {
      $plaintext = $parameters['plaintext_no_tickets'];
    }
  }

  $context = array('commerce_order' => $order);
  $options = array('clear' => TRUE);

  // Format the body.
  $body['value'] = token_replace($body['value'], $context, $options);
  $body = check_markup($body['value'], $body['format']);

  // Format the subject.
  $subject = token_replace($subject, $context, $options);

  // Format the plain-text body.
  if ($plaintext) {
    $plaintext = token_replace($plaintext, $context, $options);
  }

  // Set the sender name and from address.
  if (empty($parameters['from_mail'])) {
    $from_string = NULL;
  }
  else {
    $from_string = array(
      'name' => $parameters['from_name'],
      'mail' => $parameters['from_mail'],
    );
    // Create an address string.
    module_load_include('inc', 'mimemail', 'mimemail');
    $from_string = mimemail_address($from_string);
  }

  // Set up all the other parameters for drupal_mail().
  $module = 'commerce_event_ticket_mail';
  $key = 'mail_tickets_for_order';
  $language = language_default();
  $mail_params = array(
    'subject' => $subject,
    'body' => $body,
    'plaintext' => $plaintext,
    'attachments' => $attachments,
  );

  drupal_mail($module, $key, $parameters['to'], $language, $mail_params, $from_string);
}
