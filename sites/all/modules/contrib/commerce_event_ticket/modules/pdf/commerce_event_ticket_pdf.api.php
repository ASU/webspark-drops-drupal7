<?php
/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Alter a generated PDF.
 *
 * @param TCPDF $pdf
 *   The TCPDF object. See http://www.tcpdf.org/doc/code/classTCPDF.html for API
 *   documentation.
 * @param CommerceEventTicketEntity $ticket
 *   The ticket entity.
 * @param array &$context
 *   An array of contextual information about the PDF document, including:
 *     - page_margin: The size of the page margin.
 *     - inner_padding: The padding between elements on the page.
 *     - info_x: The x coordinate for where the ticket information table should
 *               be positioned. This can be altered.
 *     - info_y: The y coordinate for the ticket information table. This can
 *               also be altered.
 */
function hook_commerce_event_ticket_pdf_alter(TCPDF $pdf, CommerceEventTicketEntity $ticket, array &$context) {
  // Do something with the PDF here.
}
