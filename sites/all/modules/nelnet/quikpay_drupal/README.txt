DESCRIPTION
--------------------------
This module allows you to configure a NelNet QuikPAY payment method in Drupal's
Commerce suite of modules. (A Drupal 6 version compatible Ubercrt is also
available.) Due to licensing restrictions, this module is only available by
special request. Email webconsulting@asu.edu with details about your project.


INSTALLATION
--------------------------
Install the module as usual, see http://drupal.org/node/70151 for further
information.

Quikpay requires the Commerce suite of eCommerce modules from 
https://www.drupal.org/project/commerce. Prior to enabling Quikpay, you'll
want to install and turn on the Commerce, Cart, Payment, Payment UI, Checkout,
Line Item, Line Item UI, Order, Order UI, Price, Product modules from the 
Commerce suite. There's a Getting Started guide for Commerce at
https://drupalcommerce.org/getting-started .

Once you've installed the Quikpay module, configure it within the Commerce
store configuration menus:
Administration > Store > Configuration > Payment Methods > Quikpay

Choose a redirect method:
RTPN Mode
When a customer clicks on the "proceed to payment" link, Quikpay opens in a
separate window. Once payment is complete, the customer must close that window.
Quikpay will asyncronously notify your Drupal site that a payment has been made,
by sending a request to your RTPN page (/quikpay/rtpn). This request is subject
to authentication via the keys setup in the payment method configuration, and
obtained via ASU Financial Services' Nelnet liaison (more on this below).
When the payment completes, the checkout pane will still be open on the Drupal
site, but the cart should be cleared. This is a limitation imposed by the 
QuikPay RTPN interface.

Redirect URL mode
With this mode enabled, when you proceed to the Quikpay payment site, it does
not open in a new window, and when payment completes, you are redirected back
to your Drupal site. 

To determine which modes are available to you and to obtain the proper testing
and production servers, please speak with the ASU Financial Services Nelnet 
liaison.

Real Time Payment Notifications (RTPN) will need to hit 
http://yourdomain/quikpay/rtpn (or if you are using SSL, 
https://yourdomain/quikpay/rtpn) in order to notify your site that a payment 
has completed. Keep in mind, if using SSL, that self-signed, expired and 
mis-configured SSL certificates will result in RTPN notifications failing to 
complete.

In the case of Redirect URL payments, you'll want to ask Financial Services to
configure the redirectUrl parameter to be the same path you'd have used as the
RTPN, namely https://yourdomain/quikpay/rtpn .

The "proceed to checkout" link includes a time-sensitive hash. This means the 
link will time out. Quikpay only honors hashes with times within 5 minutes of
the Quikpay server. This means:
- You want to make sure your server's time is relatively close to your
  timezone as reported at http://tycho.usno.navy.mil/
- The "proceed to checkout" link times out for users after 5 minutes, give or
  take. When the user clicks the expired link, QuikPAY will report an error. 
  The user can close that window/tab and return to the original page with the 
  link and refresh the page to get a valid link.

Once your test site is working, request that the production Quikpay payment
processing site be set up and get the keys for it from the ASU Financial 
Services' Nelnet liaison. Please allow 10 days for processing of the final 
production setup. Enter the production keys and production Quikpay url into
the Quikpay payment method settings, and switch to production mode.

PERMISSIONS
--------------------------
Inherited from Commerce. Anonymous will need "access checkout" permission
in order to access the RTPN page.

MODULES
--------------------------
Ships with just the Quikpay module.

See .info file for dependencies.

PAGES
--------------------------
Admin UI for Configuring Payment Method, accessed through Store Settings.
/admin/commerce/config/payment-methods/manage/commerce_payment_quikpay/

Page used by Quikpay to report payments.
/quikpay/rtpn 

TABLES
--------------------------
Managed by Commerce.

BLOCKS
--------------------------
None.

HOOKS
--------------------------
Alter hash parameters (shouldn't need this in most cases).
hook_quikpay_hash_param_alter(&$variables, &$param, $order)

CREDITS
--------------------------
The Quikpay module was created by 
Michael Samuelson <mlsamuel@asu.edu> / <mlsamuelson@gmail.com> (http://mlsamuelson.com).
Zohair Zaidi <zohair.zaidi@asu.edu / zohair.zaidi@gmail.com> 

