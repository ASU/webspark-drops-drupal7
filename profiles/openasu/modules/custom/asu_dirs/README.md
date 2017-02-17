# ASU Directory Integration Reinvented Suite

A suite of modules for building local iSearch-enabled directory listings.  


## Modules Included

This suite includes the following projects:

### ASU Directory Integration Reinvented (ASU DIR)
The ASU DIR module allows creation and configuration of Solr-enabled directory people listings, which pull directly from iSearch.

Features:

* Defines a custom ASU Directory field type, and also a custom content type with field attached.
    * Configurable field options include:
        * Filtering by department, title, expertise, and employee type, among others
        * Optional interactive directory tree
        * Faceted search filters for expertise and faculty titles
        * Search functionality
* Automatic integration with ASU LID module (if enabled).
    * When ASU LID is enabled, and profiles have been imported from iSearch, the directory listings will 
    automatically link to the imported profile nodes.
    * Now includes a Solr Health Check fallback.  If Solr is down, then the directory listing will automatically
    be replaced with a Drupal View of local profile profile nodes

### ASU Local iSearch Directory (ASU LID)

Pulls iSearch profile data and stores/updates it locally. Sets up profile nodes and default listing view.

Features:

* Import profiles from iSearch according to site configs
    * Allows the display of iSearch profiles on local site
* Automatic profile updating.
    * Profiles are updated from iSearch via periodic cron tasks.
    * Periodic and load-time checking of profiles against iSearch Solr index, to ensure
    up-to-date affiliation data
* ASU LID Profile View will automatically substitute for the ASU DIR Solr listings if iSearch
Solr health check fails
 
    
### ASU Directory Panel

Creates ASU Directory Panel Pane, for ease of use with Webspark and Panopoly.

### ASU Directory Utilities

Utilities useful for gathering data from iSearch and Solr.

## Packaged with Webspark

When ASUDIRS is enabled by Webspark, 3 modules will be enabled by default:

* ASU DIR
* ASU Directory Utilities
* ASU Directory Panel


#### Standalone

When ASUDIRS is enabled as a standalone module, 2 modules are enabled by default:

* ASU DIR
* ASU Directory Utilities
