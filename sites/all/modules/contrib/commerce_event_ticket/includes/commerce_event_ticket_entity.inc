<?php
/**
 * @file
 * Entity class for Commerce Event Ticket.
 */

class CommerceEventTicketEntity extends Entity {

  public $ticket_id;
  public $revision_id;
  public $type = 'ticket';
  public $barcode_token;
  public $order_id;
  public $line_item_id;
  public $product_id;
  public $nid;
  public $used;
  public $number;
  public $quantity;
  public $created;
  public $changed;

}
