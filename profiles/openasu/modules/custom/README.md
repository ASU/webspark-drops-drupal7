# asu-drupal-modules

## List of modules

* asu_ajax_solr - Adds AJAX Solr library.
* asu_ap - (Feature) Pulls degree programs from webapp4 (utilizing the Degree Search API) via Feeds;
  includes necessary modules ASU Feeds 2 (asu_feeds2) and ASU IXR (asu_ixr), which were previously not bundled;
  includes theming for nodes and views.
* asu_brand - Contains ASU Brand header and footer blocks for usage in Drupal;
* asu_cas - (Feature) CAS settings for integrating ASU SSO and CAS into Drupal.
* asu_degrees [DEPRECATED] - (Feature) Pulls in degrees from Degree Search via Feeds; Includes theming for layout.
* asu_dir - AJAX-powered, rudimentary ASU directory; Pulls data from a Solr instance (which gets its data from iSearch).
* asu_feeds [DEPRECATED] - (Feature) Provides settings and theming for old asu_directory module.
* asu_rfi - Extends asu_degrees to include Request for Info (RFI) forms, which collect and transmit data to Salesforce
  via middleware.
* asu_userpicker - Provides a custom user field widget for picking users in Drupal and ASU LDAP, and creating those not
  yet in Drupal.
* ixr [DEPRECATED] - This module provides several wrapper methods for using the IXR - The Inutio XML-RPC Library,
  a PHP-based library for performing remote XML-RPC transactions. It is simply an API and doesn't directly provide any
  functionality on its own.
