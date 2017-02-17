Missing Modules
===============

This module lists modules that are activated in your database but missing
from your file system.

These can greatly impact the performance of your drupal 7 site.

For example: 1 missing module lead to 900 file_scan_directory() calls
resulting in a wasted 250ms every page load.


To use either view the site status report

/admin/reports/status


or from drush run

drush list-missing-modules (alias drush lmm)

INSTALL
=======

This module can be installed as any other Drupal module, or as a drush module in e.g. ~/.drush/.
