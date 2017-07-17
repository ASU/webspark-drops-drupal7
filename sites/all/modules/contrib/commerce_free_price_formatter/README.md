CONTENTS OF THIS FILE
---------------------
   
* Introduction
* Requirements
* Installation
* Configuration
* Maintainers
 
INTRODUCTION
------------
The Commerce Free Price Formatter module allows in Drupal Commerce to
display prices of 0,0 as a text (by default "Free!").

This allows to have more attractive prices for our customers.

If the price is greater than zero, an existing user-defined field formatter
will be used.

This module was developed for the online store [Abejitas](http://abejitas.org).

REQUIREMENTS
------------
This module requires the following modules:
* commerce_price (https://drupal.org/project/commerce)
 
INSTALLATION
------------
* Install as you would normally install a contributed Drupal module. See:
  https://www.drupal.org/documentation/install/modules-themes/modules-7
  for further information.
   
CONFIGURATION
-------------
For the default product type created by Drupal Commerce, the configuration will
be on admin/commerce/products/types/product/display.

On the price field, select "Free formatter" and click on the configuration
button to define its options.
   
MAINTAINERS
-----------
Current maintainers:
 * Mario Galan (mariogalan) - (https://www.drupal.org/u/mariogalan)
