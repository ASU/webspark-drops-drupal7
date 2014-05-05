<?php
/**
 * @file
 * openasu_demo.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function openasu_demo_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'contact_demo_page';
  $page->task = 'page';
  $page->admin_title = 'Contact Demo Page';
  $page->admin_description = '';
  $page->path = 'contact';
  $page->access = array();
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Contact',
    'name' => 'main-menu',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_contact_demo_page_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'contact_demo_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel Contaact Demo page',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'boxton';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'contentmain' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Contact';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1';
    $pane->panel = 'contentmain';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<h3>Contact</h3><p>Have questions on how ASU webspark can work for you? Or are you a current user of ASU webspark? Please check out&nbsp;<a href="drupal.asu.edu">drupal.asu.edu</a>&nbsp;for further information.</p><p>&nbsp;</p><blockquote><p><strong>Step 1:&nbsp;</strong>Turn on the Webform module by going to Modules and then typing "webform" in the search box. &nbsp;This will pull up the Webform module on the page. &nbsp;Check the box next to it and click Save Configuration.</p></blockquote><blockquote><p><strong>Step 2:&nbsp;</strong>Site administrators can also add custom contact forms to their site. &nbsp;To add a custom form go to Content -&gt; Add Content -&gt; Webform. &nbsp;This creates a page where your form will be displayed.</p></blockquote><blockquote><p><strong>Step 3:&nbsp;</strong>Give the page a title and some descriptive text.</p></blockquote><blockquote><p><strong>Step 4:&nbsp;</strong>Now to add fields to the form click on Webform at the top of the page (next to Edit). &nbsp;Here you can add the desired webform fields. &nbsp;</p></blockquote><blockquote><p><strong>Step 5:&nbsp;</strong>For more information on creating custom WebForms see&nbsp;http://www.youtube.com/watch?v=fgIL8jEMd4s and&nbsp;http://www.ostraining.com/blog/drupal/webform-module/</p></blockquote><p><img src="/sites/all/modules/openasu_demo/images/contact_form_example.jpg"></p>',
      'format' => 'panopoly_wysiwyg_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-1'] = $pane;
    $display->panels['contentmain'][0] = 'new-1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['contact_demo_page'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'openasu_demo_panel';
  $page->task = 'page';
  $page->admin_title = 'Home';
  $page->admin_description = 'This is a demo panel for Panopoly so folks can see the magic';
  $page->path = 'demo';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Home',
    'name' => 'main-menu',
    'weight' => '-50',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_openasu_demo_panel_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'openasu_demo_panel';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Demo Panel',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'mccoppin';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'contentmain' => NULL,
      'footer' => NULL,
      'column1' => NULL,
      'header' => NULL,
    ),
    'sidebar' => array(
      'style' => '-1',
    ),
    'header' => array(
      'style' => '0',
    ),
    'column1' => array(
      'style' => '0',
    ),
    'footer' => array(
      'style' => '0',
    ),
  );
  $display->cache = array();
  $display->title = 'Home';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-2';
    $pane->panel = 'column1';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => 'What is ASU webspark?',
      'body' => '<p>Web<strong>spark</strong> lets you create a feature-rich website without in-depth technical knowledge. Learn more:</p><h4><a href="/content/about">Learn More About web<strong>spark</strong></a><br><br><a href="/content/how-start-site">How To Get Started</a><br><br><a href="/contact">Request More Information</a><br><br><br><br></h4><p>&nbsp;</p><p><a href="http://commguide.asu.edu/"><img src="https://dev-openasu-demo.ws.asu.edu/sites/default/files/asucommguide.jpg" data-file_info="%7B%22fid%22:%2261%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></a></p><p>The Comm Guide is the source for all ASU branding and standards information, including logo downloads, photography resources and social media tools.<br><br><a href="http://commguide.asu.edu/">Visit ASU Comm Guide site</a><br><br></p>',
      'format' => 'panopoly_wysiwyg_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-2'] = $pane;
    $display->panels['column1'][0] = 'new-2';
    $pane = new stdClass();
    $pane->pid = 'new-3';
    $pane->panel = 'column2';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => 'Highlights',
      'body' => '<ul><li>Flexible content placement options</li><li>Multiple style variations available</li><li>New site created within 15 minutes</li><li>Easy to use editor</li><li>Use analytics for site tracking</li></ul><p><a href="/content/features">view full list of features</a></p>',
      'format' => 'panopoly_wysiwyg_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-3'] = $pane;
    $display->panels['column2'][0] = 'new-3';
    $pane = new stdClass();
    $pane->pid = 'new-4';
    $pane->panel = 'column2';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => 'Connect',
      'body' => '<p>Include any social media connection or link to ASU’s social media channels to engage with your audience.</p>',
      'format' => 'panopoly_wysiwyg_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $display->content['new-4'] = $pane;
    $display->panels['column2'][1] = 'new-4';
    $pane = new stdClass();
    $pane->pid = 'new-5';
    $pane->panel = 'column2';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<p><img src="sites/all/modules/openasu_demo/images/social_buttons_home_page.png"></p>',
      'format' => 'panopoly_wysiwyg_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $display->content['new-5'] = $pane;
    $display->panels['column2'][2] = 'new-5';
    $pane = new stdClass();
    $pane->pid = 'new-6';
    $pane->panel = 'column3';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => 'ASU Feeds',
      'body' => '<p>Easily include ASU feeds on any page within the site. Learn more about individual feed options:</p><p><a href="/content/asu-events">ASU Events</a><br><a href="/content/asu-news">ASU News</a></p>',
      'format' => 'panopoly_wysiwyg_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-6'] = $pane;
    $display->panels['column3'][0] = 'new-6';
    $pane = new stdClass();
    $pane->pid = 'new-7';
    $pane->panel = 'column3';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<p><a href="/content/maps"><img src="/sites/all/modules/openasu_demo/images/map_feature_home_page.png"></a></p>',
      'format' => 'panopoly_wysiwyg_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $display->content['new-7'] = $pane;
    $display->panels['column3'][1] = 'new-7';
    $pane = new stdClass();
    $pane->pid = 'new-8';
    $pane->panel = 'column3';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<p><a href="/content/mobile-formatted"><img src="sites/all/modules/openasu_demo/images/mobile_home_page.png"></a></p>',
      'format' => 'panopoly_wysiwyg_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $display->content['new-8'] = $pane;
    $display->panels['column3'][2] = 'new-8';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['openasu_demo_panel'] = $page;

  return $pages;

}
