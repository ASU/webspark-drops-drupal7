<?php
/**
 * @file
 * panopoly_demo.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function panopoly_demo_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'panopoly_demo_panel';
  $page->task = 'page';
  $page->admin_title = 'Homepage Demo';
  $page->admin_description = 'This is a demo panel for Panopoly so folks can see the magic';
  $page->path = 'demo';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Homepage Demo',
    'name' => 'main-menu',
    'weight' => '-10',
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
  $handler->name = 'page_panopoly_demo_panel_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'panopoly_demo_panel';
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
  $display->layout = 'radix_burr_flipped';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'header' => NULL,
      'contentmain' => NULL,
      'footer' => NULL,
    ),
    'sidebar' => array(
      'style' => '-1',
    ),
  );
  $display->cache = array();
  $display->title = 'Homepage Demo';
  $display->uuid = 'b7a6867e-81e2-4492-b887-5ef5422d53cf';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-31a76efc-0294-4d4c-91e5-dd436aa0f9d9';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'panopoly_demo-individual_demo_item';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'fields_override' => array(
      'field_featured_image' => 1,
      'title' => 1,
      'created' => 1,
      'name' => 1,
      'body' => 1,
    ),
    'exposed' => array(
      'title' => 'Content Demo',
    ),
    'view_mode' => 'featured',
    'widget_title' => NULL,
    'items_per_page' => NULL,
    'view_settings' => 'nodes',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '31a76efc-0294-4d4c-91e5-dd436aa0f9d9';
  $display->content['new-31a76efc-0294-4d4c-91e5-dd436aa0f9d9'] = $pane;
  $display->panels['contentmain'][0] = 'new-31a76efc-0294-4d4c-91e5-dd436aa0f9d9';
  $pane = new stdClass();
  $pane->pid = 'new-15cead82-ce21-4f28-8d06-c9efb4c73e22';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'panopoly_demo-demo_listing';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'fields_override' => array(
      'field_featured_image' => 1,
      'title' => 1,
      'created' => 1,
      'name' => 1,
      'body' => 1,
    ),
    'exposed' => array(
      'sort_by' => 'created',
      'sort_order' => 'ASC',
      'widget_title' => '',
      'items_per_page' => '3',
    ),
    'view_mode' => 'teaser',
    'widget_title' => '',
    'items_per_page' => '3',
    'view_settings' => 'nodes',
    'override_title' => '',
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '15cead82-ce21-4f28-8d06-c9efb4c73e22';
  $display->content['new-15cead82-ce21-4f28-8d06-c9efb4c73e22'] = $pane;
  $display->panels['contentmain'][1] = 'new-15cead82-ce21-4f28-8d06-c9efb4c73e22';
  $pane = new stdClass();
  $pane->pid = 'new-34874601-6af8-4ec0-bb86-649b1966544c';
  $pane->panel = 'sidebar';
  $pane->type = 'search_box';
  $pane->subtype = 'search_box';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'type' => 'node',
    'form' => 'simple',
    'path_type' => 'default',
    'path' => '',
    'override_prompt' => 0,
    'prompt' => '',
    'override_title' => 0,
    'override_title_text' => 'Search the Site',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '34874601-6af8-4ec0-bb86-649b1966544c';
  $display->content['new-34874601-6af8-4ec0-bb86-649b1966544c'] = $pane;
  $display->panels['sidebar'][0] = 'new-34874601-6af8-4ec0-bb86-649b1966544c';
  $pane = new stdClass();
  $pane->pid = 'new-b573b3a8-9a6d-4fbf-921e-89d3fed18c89';
  $pane->panel = 'sidebar';
  $pane->type = 'views_panes';
  $pane->subtype = 'panopoly_demo-demo_listing';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'fields_override' => array(
      'field_featured_image' => 1,
      'title' => 1,
      'created' => 1,
      'name' => 0,
      'body' => 0,
    ),
    'exposed' => array(
      'widget_title' => 'Demo Items',
    ),
    'view_mode' => 'teaser',
    'widget_title' => 'Demo Items',
    'items_per_page' => '3',
    'view_settings' => 'fields',
    'override_title' => '',
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'b573b3a8-9a6d-4fbf-921e-89d3fed18c89';
  $display->content['new-b573b3a8-9a6d-4fbf-921e-89d3fed18c89'] = $pane;
  $display->panels['sidebar'][1] = 'new-b573b3a8-9a6d-4fbf-921e-89d3fed18c89';
  $pane = new stdClass();
  $pane->pid = 'new-0a7200da-fe1f-4fd7-a6b9-b6cc71ca9a1c';
  $pane->panel = 'sidebar';
  $pane->type = 'views_panes';
  $pane->subtype = 'panopoly_demo-list_featured_demo_items';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'fields_override' => array(
      'field_featured_image' => 1,
      'title' => 1,
      'created' => 0,
      'name' => 1,
      'body' => 1,
    ),
    'exposed' => array(
      'widget_title' => 'Featured Demo Items',
    ),
    'view_mode' => 'teaser',
    'widget_title' => 'Featured Demo Items',
    'items_per_page' => '0',
    'view_settings' => 'fields',
    'override_title' => '',
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '0a7200da-fe1f-4fd7-a6b9-b6cc71ca9a1c';
  $display->content['new-0a7200da-fe1f-4fd7-a6b9-b6cc71ca9a1c'] = $pane;
  $display->panels['sidebar'][2] = 'new-0a7200da-fe1f-4fd7-a6b9-b6cc71ca9a1c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['panopoly_demo_panel'] = $page;

  return $pages;

}
