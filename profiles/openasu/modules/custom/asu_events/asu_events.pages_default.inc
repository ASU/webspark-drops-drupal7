<?php
/**
 * File to create asu news listing page
 */

function asu_events_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'asu_events_listing';
  $page->task = 'page';
  $page->admin_title = 'ASU Events';
  $page->admin_description = '';
  $page->path = 'events';
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
  $handler->name = 'page_asu_events_listing_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'asu_events_listing';
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
  $display->uuid = 'b41974e3-865f-4124-8c5b-321e10a32a47';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0f727978-8387-4bc7-aa27-170b20838147';
    $pane->panel = 'contentmain';
    $pane->type = 'fieldable_panels_pane';
    $pane->subtype = 'fpid:335';
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
    $pane->uuid = '0f727978-8387-4bc7-aa27-170b20838147';
    $display->content['new-0f727978-8387-4bc7-aa27-170b20838147'] = $pane;
    $display->panels['contentmain'][0] = 'new-0f727978-8387-4bc7-aa27-170b20838147';
    $pane = new stdClass();
    $pane->pid = 'new-8e7f7b99-cd90-4070-91aa-7f44f84155d0';
    $pane->panel = 'contentmain';
    $pane->type = 'asu_events_listing';
    $pane->subtype = 'asu_events_listing';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'asu_events_listing_display_type' => 'full',
      'asu_events_listing_featured' => '',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '8e7f7b99-cd90-4070-91aa-7f44f84155d0';
    $display->content['new-8e7f7b99-cd90-4070-91aa-7f44f84155d0'] = $pane;
    $display->panels['contentmain'][1] = 'new-8e7f7b99-cd90-4070-91aa-7f44f84155d0';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;

  $pages = array();
  $pages[$page->name] = $page;
  return $pages;
}
