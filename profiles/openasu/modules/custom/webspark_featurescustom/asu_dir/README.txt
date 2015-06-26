DESCRIPTION
--------------------------
Module with custom ASU Directory field type, and an ASU Directory content type with an instance of the field.


INSTALLATION
--------------------------
Install as usual, see http://drupal.org/node/70151 for further information.

See libraries required under DEPENDENCIES, below. Install libraries in

sites/all/libraries/jqtree


DEPENDENCIES
--------------------------

Libraries
 - jqTree (current supported verion of jqTree is 0.22.0)
 - Bootstrap (3.0 and up)
 - Fontawesome

Modules
 - ctools
 - features
 - fontawesome
 - libraries
 - list
 - options
 - jquery_update
 
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

