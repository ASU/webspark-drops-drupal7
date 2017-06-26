<?php
/**
 * @file
 * asu_isearch.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function asu_isearch_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = TRUE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'isearch_directory';
  $page->task = 'page';
  $page->admin_title = 'iSearch Directory';
  $page->admin_description = '';
  $page->path = 'isearch-directory';
  $page->access = array();
  $page->menu = array(
    'type' => 'normal',
    'title' => 'iSearch Directory',
    'weight' => 0,
    'name' => 'main-menu',
    'parent' => 'main-menu:0',
  );
  $page->arguments = array();
  $page->conf = array();
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_isearch_directory_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'isearch_directory';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Landing page',
    'no_blocks' => FALSE,
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
  $display->panel_settings = array();
  $display->cache = array();
  $display->title = 'iSearch Directory';
  $display->uuid = '0365ffd6-5183-4d33-b195-2e60fa3d6c2f';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-cc484a7f-b9fc-480e-9a60-b2077747b22a';
  $pane->panel = 'contentmain';
  $pane->type = 'fieldable_panels_pane';
  $pane->subtype = 'fpid:34';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_mode' => 'Full',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'cc484a7f-b9fc-480e-9a60-b2077747b22a';
  $display->content['new-cc484a7f-b9fc-480e-9a60-b2077747b22a'] = $pane;
  $display->panels['contentmain'][0] = 'new-cc484a7f-b9fc-480e-9a60-b2077747b22a';
  $pane = new stdClass();
  $pane->pid = 'new-e979fe35-e01c-4e5b-8076-158925a06e7d';
  $pane->panel = 'contentmain';
  $pane->type = 'fieldable_panels_pane';
  $pane->subtype = 'fpid:31';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_mode' => 'Full',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'e979fe35-e01c-4e5b-8076-158925a06e7d';
  $display->content['new-e979fe35-e01c-4e5b-8076-158925a06e7d'] = $pane;
  $display->panels['contentmain'][1] = 'new-e979fe35-e01c-4e5b-8076-158925a06e7d';
  $pane = new stdClass();
  $pane->pid = 'new-2d1e19e1-66ce-4ff7-b491-32256aa9b833';
  $pane->panel = 'contentmain';
  $pane->type = 'fieldable_panels_pane';
  $pane->subtype = 'fpid:28';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_mode' => 'Full',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '2d1e19e1-66ce-4ff7-b491-32256aa9b833';
  $display->content['new-2d1e19e1-66ce-4ff7-b491-32256aa9b833'] = $pane;
  $display->panels['contentmain'][2] = 'new-2d1e19e1-66ce-4ff7-b491-32256aa9b833';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['isearch_directory'] = $page;

  return $pages;

}
