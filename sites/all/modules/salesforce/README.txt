
ABOUT
-----
  This module suite implements a mapping functionality between Salesforce
  objects and Drupal entities. In other words, for each of your supported Drupal
  entities (e.g. node, user, or entities supported by extensions), you can 
  assign Salesforce objects that will be created / updated when the entity is
  saved. For each such assignment, you choose which Drupal and Salesforce fields
  should be mapped to one another.

  This suite also includes an API architecture which allows for additional
  modules to be easily plugged in (e.g. for webforms, contact form submits,
  etc).
  
  For a more detailed description of each component module, see below.


REQUIREMENTS
------------
  1) You need a Salesforce account. Developers can register here:
  http://www.developerforce.com/events/regular/registration.php

  2) You will need to create a remote application/connected app for
  authorization. In Salesforce go to Your Name > Setup > Create > Apps then
  create a new Connected App. Set the callback URL to:
  https://<your site>/salesforce/oauth_callback  (must use SSL)

  Select at least 'Perform requests on your behalf at any time' for OAuth Scope
  as well as the appropriate other scopes for your application.

  Additional information:
  https://help.salesforce.com/help/doc/en/remoteaccess_about.htm

  3) Your site needs to be SSL enabled to authorize the remote application using
  OAUTH.

  4) If using the SOAP API, PHP to have been compiled with SOAP web services and
  OpenSSL support, as per:
  
  http://php.net/soap
  http://php.net/openssl

  5) Required modules
     Entity API - http://drupal.org/project/entity
     Libraries, only for SOAP API - http://drupal.org/project/libraries


MODULES:
--------

  Salesforce (salesforce):
    OAUTH2 authorization and wrapper around the Salesforce REST API.

  Salesforce Mapping (salesforce_mapping)
    Map Drupal entities to Salesforce fields, including field level mapping.

  Salesforce Push (salesforce_push):
    Push Drupal entity updates into Salesforce.

  Salesforce Pull (salesforce_pull):
    Pull Salesforce object updates into Drupal.

  Salesforce Soap (salesforce_soap):
    Lightweight wrapper around the SOAP API, using the OAUTH access token, to
    fill in functional gaps missing in the REST API. Requires the Salesforce PHP
    Toolkit.

NOTES:

  Addressfield Options
    Salesforce provides a formatting plugin for addressfield which converts the
    "Thoroughfare" field to a text area. Enabling this option will make it much
    easier to sync addressfield data to Salesforce multi-line addressfields.

  Dates
    For Drupal date fields with start and end dates, salesforce_pull will fail
    unless you are using a version of Date that includes commit 7faeea3.

    To avoid potential timezone conversion errors, try setting your date field
    to "No timezone conversion".
