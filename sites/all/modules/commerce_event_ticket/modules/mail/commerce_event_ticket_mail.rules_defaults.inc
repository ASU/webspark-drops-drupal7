<?php
/**
 * @file
 * Default Rules for the Commerce Event Ticket module.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_event_ticket_mail_default_rules_configuration() {
  $items = array();

  $items['commerce_event_ticket_mail'] = entity_import('rules_config', '{ "commerce_event_ticket_mail" : {
      "LABEL" : "Send tickets to the customer",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "commerce_event_ticket" ],
      "WEIGHT": 3,
      "REQUIRES" : [
        "commerce_event_ticket",
        "rules",
        "commerce_event_ticket_mail",
        "commerce_checkout"
      ],
      "ON" : { "commerce_checkout_complete" : [] },
      "IF" : [
        { "commerce_event_ticket_order_should_have_tickets" : { "commerce_order" : [ "commerce_order" ] } }
      ],
      "DO" : [
        { "commerce_event_ticket_mail_for_order" : {
            "commerce_order" : [ "commerce_order" ],
            "to" : "[commerce-order:mail]",
            "subject" : "Your tickets for order [commerce-order:order-number]",
            "body" : { "value" : {
                "value" : "\u003Cp\u003EThank you for your order (number [commerce-order:order-number]) at [site:name] ([site:url])\u003C\/p\u003E\r\n\r\n\u003Cp\u003EYour ticket(s) are attached to this e-mail. Please print them out and take them with you, or display them on your smartphone. Each ticket only admits one person.\u003C\/p\u003E\r\n\r\n\u003Ch2\u003EOrder summary\u003C\/h2\u003E\r\n\r\n\u003Cp\u003E\r\n  \u003Cstrong\u003EOrder number: \u003C\/strong\u003E[commerce-order:order-number]\u003Cbr \/\u003E\r\n  \u003Cstrong\u003EDate: \u003C\/strong\u003E[commerce-order:created:medium]\u003Cbr \/\u003E\r\n  \u003Cstrong\u003EStatus:\u003C\/strong\u003E [commerce-order:status-title]\u200b\u003Cbr \/\u003E\r\n  \u003Cstrong\u003ECustomer:\u003C\/strong\u003E [commerce-order:owner:name]\u003Cbr \/\u003E\r\n  \u003Cstrong\u003EDetails:\u003C\/strong\u003E [site:url]\/user\/[commerce-order:uid]\/orders\/[commerce-order:order-id]\r\n\u003C\/p\u003E\r\n",
                "format" : "filtered_html"
              }
            },
            "plaintext" : "[site:name]\r\n[site:url]\r\n\r\nThank you for your order (number  [commerce-order:order-number]).\r\n\r\nYour ticket(s) are attached to this e-mail.\r\n\r\nPlease print them out and take them with you, or display them on your\r\nsmartphone. Each ticket only admits one person.\r\n\r\nOrder summary\r\n===========\r\n\r\nOrder number: [commerce-order:order-number]\r\nDate: [commerce-order:created:medium]\r\nStatus: [commerce-order:status-title]\u200b\r\nCustomer: [commerce-order:owner:name]\r\nDetails:\r\n[site:url]\/user\/[commerce-order:uid]\/orders\/[commerce-order:order-id]\r\n"
          }
        }
      ]
    }
  }');

  return $items;
}
