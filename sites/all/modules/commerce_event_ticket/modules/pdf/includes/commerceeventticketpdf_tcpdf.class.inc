<?php
/**
 * @file
 * Class extending TCPDF.
 */

class CommerceEventTicketPDF_TCPDF extends TCPDF {

  public $cet_ticket;
  public $cet_elements;

  /**
   * Overrides TCPDF::Footer().
   */
  public function Footer() {
    $footer_font_size = 10;
    $footer_height = 8;
    $footer_y = -18;

    // Add ticket metadata at the bottom left of the page (optionally).
    if (!empty($this->cet_elements['metadata'])) {
      $ticket = $this->cet_ticket;
      $this->setFont('Helvetica', NULL, $footer_font_size);
      $this->SetY($footer_y);
      $metadata = t('Ticket @id (@number of @count)', array(
        '@number' => $ticket->number,
        '@count' => $ticket->quantity,
        '@id' => $ticket->ticket_id,
      ));
      $this->Cell(0, $footer_height, $metadata, 0, 0, 'L');
    }

    // Add page numbering at the bottom left of the page (optionally).
    if (!empty($this->cet_elements['page_numbering'])) {
      $this->setFont('Helvetica', NULL, $footer_font_size);
      if (!empty($this->cet_elements['metadata'])) {
        $this->SetY($footer_y - $footer_height);
      }
      else {
        $this->SetY($footer_y);
      }
      $number = t('Page @number of @count', array(
        '@number' => $this->getPageNumGroupAlias(),
        '@count' => $this->getPageGroupAlias(),
      ));
      $this->Cell(0, $footer_height, $number, 0, 0, 'L');
    }
  }

}
