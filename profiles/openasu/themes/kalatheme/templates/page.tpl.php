<?php

/**
 * @file
 * Kalatheme's implementation to display a single Drupal page.
 *
 * The doctype, html, head, and body tags are not in this template. Instead
 * they can be found in the html.tpl.php template normally located in the
 * core/modules/system directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $hide_site_name: TRUE if the site name has been toggled off on the theme
 *   settings page. If hidden, the "element-invisible" class is added to make
 *   the site name visually hidden, but still accessible.
 * - $hide_site_slogan: TRUE if the site slogan has been toggled off on the
 *   theme settings page. If hidden, the "element-invisible" class is added to
 *   make the site slogan visually hidden, but still accessible.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $main_menu_expanded (array): An array containing 2 depths of the Main
 *   menu links
 *   for the site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on
 *   the menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node entity, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Kalatheme:
 * - $no_panels: A boolean that is true if the current page is not a panels page
 * - $always_show_page_title: A boolean that is true if we're to always print
 *   the page title, even on panelized pages.
 *
 * Regions:
 * - $page['content']: The main content of the current page.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see bartik_process_page()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<div id="page-wrapper"><div id="page">

   <!-- Page Header -->
  <header class="navbar navbar-default <?php if ($hide_site_name && $hide_site_slogan && !$logo && !$main_menu && !$secondary_menu) { print ' element-invisible'; } ?>">
    <div class="container">
      <div class="navbar-header">
        <button class="navbar-toggle" type="button" data-toggle="collapse" data-target=".navbar-collapse">
          <span class="sr-only">Toggle navigation</span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
        </button>
        <?php if ($logo): ?>
          <div class='brand navbar-brand'>
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </a>
          </div>
        <?php endif; ?>

        <?php if ($site_name || $site_slogan): ?>
          <div id="site-name-slogan" class="brand navbar-brand <?php if ($hide_site_name && $hide_site_slogan) { print ' element-invisible'; } ?>">

            <?php if ($site_name): ?>
              <h1 id="site-name"<?php if ($hide_site_name) { print ' class="element-invisible"'; } ?>>
                <strong>
                  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
                </strong>
              </h1>
            <?php endif; ?>

            <?php if ($site_slogan): ?>
              <div id="site-slogan" <?php if ($hide_site_slogan) { print 'class="element-invisible"'; } ?>>
                <?php print $site_slogan; ?>
              </div>
            <?php endif; ?>

          </div> <!-- /#name-and-slogan -->
        <?php endif; ?>
      </div><!-- /.navbar-header -->

      <nav class="collapse navbar-collapse <?php if (!$main_menu && !$secondary_menu) { print 'element-invisible'; } ?>" role="navigation">
        <?php
          $pri_attributes = array(
            'class' => array(
              'nav',
              'navbar-nav',
              'links',
              'clearfix',
            ),
          );
          if (!$main_menu) {
            $pri_attributes['class'][] = 'element-invisible';
          }
        ?>
        <?php print theme('links__system_main_menu', array(
          'links' => $main_menu_expanded,
          'attributes' => $pri_attributes,
          'heading' => array(
            'text' => t('Main menu'),
            'level' => 'h2',
            'class' => array('element-invisible'),
          ),
        )); ?>

        <?php
          $sec_attributes = array(
            'id' => 'secondary-menu-links',
            'class' => array('nav', 'navbar-nav', 'secondary-links'),
          );
          if (!$secondary_menu) {
            $sec_attributes['class'][] = 'element-invisible';
          }
        ?>

        <?php print theme('links__system_secondary_menu', array(
          'links' => $secondary_menu,
          'attributes' => $sec_attributes,
          'heading' => array(
            'text' => t('Secondary menu'),
            'level' => 'h2',
            'class' => array('element-invisible'),
          ),
        )); ?>
      </nav>

    </div>
  </header>

  <!-- Page Main -->
  <div id="main-wrapper" class="clearfix"><div id="main" class="clearfix">
    <div id="top-content" class="column container">
      <a id="main-content"></a>
      <?php if (($no_panels || $always_show_page_title) && $title): ?>
        <h1 id="page-title" class="title">
          <?php print $title; ?>
        </h1>
      <?php endif; ?>

      <?php if ($messages): ?>
        <div id="messages">
          <?php print $messages; ?>
        </div>
      <?php endif; ?>

      <?php if ($tabs): ?>
        <div id="tabs">
          <?php print render($tabs); ?>
        </div>
      <?php endif; ?>

      <?php if ($action_links): ?>
        <div id="action-links">
          <?php print render($action_links); ?>
        </div>
      <?php endif; ?>
    </div> <!-- /.section, /#top-content -->

    <div id="content" class="column <?php $no_panels ? print 'container' : ''; ?>">
      <?php print render($page['content']); ?>
    </div> <!-- /.section, /#content -->

  </div></div> <!-- /#main, /#main-wrapper -->

</div></div> <!-- /#page, /#page-wrapper -->
