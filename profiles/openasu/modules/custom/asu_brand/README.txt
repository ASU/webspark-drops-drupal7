ASU Brand module installation instructions.

1. Install and enable the ASU Brand module just like any other module.
2. Go to the Structure -> Blocks and move the ASU Brand header and ASU Brand
   footer blocks into the header and footer regions respectively. The available
   regions will be determined by the theme that you are using.
3. The header and footer are cached locally and will refresh every 48 hours. If
   you need to manually refresh them, go to Configuration -> Performace and
   clear the site's cache.
     

FAQ
--------------------------
Q: Does the module support the 'Special menu items' module?
A: Yes. <nolink> menu items will link to current page ('#')
   and <separator> menu items will not be rendered in the
   injected mobile menu.



HOOKS
--------------------------

/**
 * Implements hook_asu_brand_sitemenu_alter().
 * Modify site menu before injection into ASU Header
 */
function MODULENAME_asu_brand_sitemenu_alter(&$menu_array) {
  // you can modify the $menu_array here
}


/**
 * Implements hook_asu_brand_sitename_alter().
 * Modify site name before injection into ASU Header
 */
function MODULENAME_asu_brand_sitename_alter(&$site_name) {
  // you can modify the $site_name here
}