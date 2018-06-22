<?php
/**
 * File to create asu news listing page
 */

/**
 * Implements hook_default_page_manager_pages
 */
function asu_news_default_page_manager_pages() {
  $page = new stdClass();
$page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
$page->api_version = 1;
$page->name = 'asu_news_listing';
$page->task = 'page';
$page->admin_title = 'ASU News Listing';
$page->admin_description = '';
$page->path = 'news';
$page->access = array();
$page->menu = array();
$page->arguments = array();
$page->conf = array(
  'admin_paths' => FALSE,
);
$page->default_handlers = array();
$handler = new stdClass();
$handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
$handler->api_version = 1;
$handler->name = 'page_asu_news_listing_panel_context';
$handler->task = 'page';
$handler->subtask = 'asu_news_listing';
$handler->handler = 'panel_context';
$handler->weight = 0;
$handler->conf = array(
  'title' => 'Panel',
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
$display->title = '';
$display->uuid = 'addae9b2-9a8c-4735-8832-bb5b6562d86b';
$display->content = array();
$display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-300e394b-2078-4374-8330-7a0d4dcbebb0';
  $pane->panel = 'contentmain';
  $pane->type = 'fieldable_panels_pane';
  $pane->subtype = 'fpid:334';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_mode' => 'Full',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '300e394b-2078-4374-8330-7a0d4dcbebb0';
  $display->content['new-300e394b-2078-4374-8330-7a0d4dcbebb0'] = $pane;
  $display->panels['contentmain'][0] = 'new-300e394b-2078-4374-8330-7a0d4dcbebb0';
  $pane = new stdClass();
  $pane->pid = 'new-72f53892-8cb1-4e2e-9fdb-37fb1d92f9f7';
  $pane->panel = 'contentmain';
  $pane->type = 'asu_news_listing';
  $pane->subtype = 'asu_news_listing';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'asu_news_listing_display_type' => 'Compact',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '72f53892-8cb1-4e2e-9fdb-37fb1d92f9f7';
  $display->content['new-72f53892-8cb1-4e2e-9fdb-37fb1d92f9f7'] = $pane;
  $display->panels['contentmain'][1] = 'new-72f53892-8cb1-4e2e-9fdb-37fb1d92f9f7';
$display->hide_title = PANELS_TITLE_NONE;
$display->title_pane = 'new-300e394b-2078-4374-8330-7a0d4dcbebb0';
$handler->conf['display'] = $display;
$page->default_handlers[$handler->name] = $handler;

  $pages = array();
  $pages[$page->name] = $page;
  return $pages;
}
