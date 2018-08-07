UPDATED: Do not use or enable this module because it will be deleted in the next release sometime
in mid-to-late 2018.

If you are already using this module and want to keep using it, then:

1) copy this module's entire directory to your /sites/all/modules directory, and 
2) run "drush rr" from the CLI (or go to your site's Modules page (/admin/modules) 
   and re-save the list of modules.

========================

This module was created to separate the Academic links out from the core Webspark build.

Enabling this feature creates the four academic menu items in the Drupal "Main Menu":

- About
- Admissions
- Degree Programs
- Student Life

Configuring these links isn't done yet, however. The four links will initially point at
https://webspark.asu.edu because the actual four Drupal pages haven't been created by this
module. Those four pages need to be manually built first, just like any other Drupal page.

(Note: When creating the page, do not create a menu item. This step should be skipped or
a 2nd similar menu item will appear, creating some confusion.)

After each page has been built, go to
/admin/structure/menu/manage/main-menu and manually update each link to point at the
newly created page.
