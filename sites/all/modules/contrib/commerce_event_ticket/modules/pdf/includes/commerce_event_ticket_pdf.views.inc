<?php
/**
 * @file
 * Views integration for the Commerce Event Ticket PDF module.
 */

/**
 * Implements hook_views_data_alter().
 */
function commerce_event_ticket_pdf_views_data_alter(&$data) {
  $data['commerce_event_ticket']['pdf'] = array(
    'title' => t('PDF download link'),
    'help' => t('A link to download a PDF file for this ticket.'),
    'field' => array(
      'handler' => 'commerce_event_ticket_pdf_views_handler_field_link',
      'click sortable' => FALSE,
    ),
    'real field' => 'ticket_id',
  );
  $data['commerce_order']['order_ticket_pdf'] = array(
    'title' => t('Tickets PDF link'),
    'help' => t('A link to download a PDF file containing all the tickets for this order.'),
    'field' => array(
      'handler' => 'commerce_event_ticket_pdf_views_handler_field_link',
      'entity type' => 'commerce_order',
      'click sortable' => FALSE,
    ),
    'real field' => 'order_id',
  );
  $data['commerce_line_item']['line_item_ticket_pdf'] = array(
    'title' => t('Tickets PDF link'),
    'help' => t('A link to download a PDF file containing all the tickets for this line item.'),
    'field' => array(
      'handler' => 'commerce_event_ticket_pdf_views_handler_field_link',
      'entity type' => 'commerce_line_item',
      'click sortable' => FALSE,
    ),
    'real field' => 'line_item_id',
  );
}
