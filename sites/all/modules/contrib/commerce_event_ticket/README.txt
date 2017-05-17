Commerce Event Ticket
=====================
This module automatically creates 'ticket' entities when customers purchase
products (one per unit). Each ticket is identified by a secure barcode.

Submodules
----------
### commerce_event_ticket_pdf
This allows PDFs to be created (optionally containing 1D or 2D barcodes). It
depends on the TCPDF module. You will also need to set up your file system
with valid paths for private files and temporary files.

### commerce_event_ticket_mail
This allows the PDF tickets to be e-mailed as attachments, via Rules. It depends
on Mime Mail (mimemail).

### commerce_event_ticket_services
This provides web service resources for validating tickets. It depends on
Services. The web services can be used by barcode scanners (with custom
software) or mobile phone apps for admission to events.

Credits
-------
Developed by Patrick Dawkins at UCLU, the students' union for University College
London.

Patrick Dawkins (drupal.org username: pjcdawkins)

UCLU
25 Gordon St, London WC1H 0AY
http://uclu.org/
