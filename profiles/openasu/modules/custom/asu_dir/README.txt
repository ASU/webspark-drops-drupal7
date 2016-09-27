DESCRIPTION
--------------------------
Module with custom ASU Directory field type, and an ASU Directory content type with an instance of the field.


INSTALLATION
--------------------------
Install as usual, see http://drupal.org/node/70151 for further information.

See libraries required under DEPENDENCIES, below. Install any missing libraries in sites/all/libraries. (NOTE:
All of the libraries below are included already in Webspark 1.13.8+ and do not need to be installed.)


DEPENDENCIES
--------------------------

Libraries
 - jqTree (0.22.0 and up)
 - Bootstrap (3.0 and up)
 - Fontawesome
 - Ajax Solr library
 - React

Modules
 - ctools
 - features
 - fontawesome
 - libraries
 - list
 - options
 - jquery_update
 - asu_dept-picker
 - react


USAGE
--------------------------
See https://webspark.asu.edu/asu_directory for how to use this module.
 
PERMISSIONS
--------------------------
  - admin/people/permissions#module-asu_dir

CONFIGURATION
--------------------------
  - admin/config/search/asu_dir

API
--------------------------
  - Pulls from isearch.asu.edu endpoints:
  	+ endpoints/settings/json
  	+ endpoints/dept_list/json
  	+ endpoints/dept_tree/json
  	+ endpoints/employee-types

