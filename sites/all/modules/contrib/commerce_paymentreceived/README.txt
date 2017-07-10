Commerce payment received
*************************

This provides a new order state and status called 'Payment received'. It also
provides two rules, enabled by default, to move an order into that state.

Update the order state on checkout completion if fully paid:
  This updates the order state to 'Payment received' on checkout complete if the
  balance is zero or less.

Update the order state on full payment:
  This updates the order state to 'Payment received' on payment first being made
  in full if the order's not currently in checkout.

Installation
************

1. Install as usual[1].
2. The new state and status should be immediately available, and the two Rules
   are enabled by default.

Links
*****

[1] http://drupal.org/documentation/install/modules-themes/modules-7
