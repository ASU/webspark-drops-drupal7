<?php
/**
 * @file
 * webspark_newsevents.features.uuid_panelizer.inc
 */

/**
 * Implements hook_uuid_features_default_panelizer().
 */
function webspark_newsevents_uuid_features_default_panelizer() {
  $uuid_panelizer = array();

  // Modified panelizer display for node 9dd25b93-d935-4bea-b3da-dbe56e8304bd.
  $display = new panels_display();
  $display->layout = 'beast';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'column1' => NULL,
      'column2' => NULL,
      'sidebar' => NULL,
      'contentmain' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '16346c80-6fcf-4cee-bf7a-9c0173fc2916';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-b65f7f61-aa6c-4d06-bf82-df9d03c5ccda';
    $pane->panel = 'bottomrow1';
    $pane->type = 'views_panes';
    $pane->subtype = 'events_new-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_settings' => 'fields',
      'header_type' => 'none',
      'view_mode' => 'teaser',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'b65f7f61-aa6c-4d06-bf82-df9d03c5ccda';
    $display->content['new-b65f7f61-aa6c-4d06-bf82-df9d03c5ccda'] = $pane;
    $display->panels['bottomrow1'][0] = 'new-b65f7f61-aa6c-4d06-bf82-df9d03c5ccda';
    $pane = new stdClass();
    $pane->pid = 'new-7d5c4a86-ad04-4e49-bf1e-acb61f32f9f1';
    $pane->panel = 'middlerow1';
    $pane->type = 'views_panes';
    $pane->subtype = 'asu_news_new-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_settings' => 'fields',
      'header_type' => 'none',
      'view_mode' => 'teaser',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '7d5c4a86-ad04-4e49-bf1e-acb61f32f9f1';
    $display->content['new-7d5c4a86-ad04-4e49-bf1e-acb61f32f9f1'] = $pane;
    $display->panels['middlerow1'][0] = 'new-7d5c4a86-ad04-4e49-bf1e-acb61f32f9f1';
    $pane = new stdClass();
    $pane->pid = 'new-844c76b3-e8e1-4c55-87ad-6970f51488e9';
    $pane->panel = 'postheaderrow1';
    $pane->type = 'node_title';
    $pane->subtype = 'node_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'link' => 0,
      'markup' => 'h1',
      'id' => '',
      'class' => 'page-title',
      'context' => 'panelizer',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '844c76b3-e8e1-4c55-87ad-6970f51488e9';
    $display->content['new-844c76b3-e8e1-4c55-87ad-6970f51488e9'] = $pane;
    $display->panels['postheaderrow1'][0] = 'new-844c76b3-e8e1-4c55-87ad-6970f51488e9';
    $pane = new stdClass();
    $pane->pid = 'new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1';
    $pane->panel = 'postheaderrow1';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_featured_image';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'image',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'image_link' => 'content',
        'image_style' => 'panopoly_image_half',
      ),
      'context' => 'panelizer',
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
    $pane->uuid = '34b4f35e-bc4b-4819-905c-6b6bf84bffe1';
    $display->content['new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1'] = $pane;
    $display->panels['postheaderrow1'][1] = 'new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1';
    $pane = new stdClass();
    $pane->pid = 'new-f3bf9c22-9b22-41d2-a57e-110951093871';
    $pane->panel = 'postheaderrow1';
    $pane->type = 'node_links';
    $pane->subtype = 'node_links';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => FALSE,
      'override_title_text' => '',
      'build_mode' => 'featured',
      'identifier' => '',
      'link' => TRUE,
      'context' => 'panelizer',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_class' => 'link-wrapper',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'f3bf9c22-9b22-41d2-a57e-110951093871';
    $display->content['new-f3bf9c22-9b22-41d2-a57e-110951093871'] = $pane;
    $display->panels['postheaderrow1'][2] = 'new-f3bf9c22-9b22-41d2-a57e-110951093871';
    $pane = new stdClass();
    $pane->pid = 'new-0a2c7b96-5f45-4e85-8e00-88fee50f4f71';
    $pane->panel = 'postheaderrow1';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_featured_categories';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
      'formatter' => 'taxonomy_term_reference_link',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'panelizer',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '0a2c7b96-5f45-4e85-8e00-88fee50f4f71';
    $display->content['new-0a2c7b96-5f45-4e85-8e00-88fee50f4f71'] = $pane;
    $display->panels['postheaderrow1'][3] = 'new-0a2c7b96-5f45-4e85-8e00-88fee50f4f71';
    $pane = new stdClass();
    $pane->pid = 'new-c755a7a9-2c4c-4f7e-a0f7-fc3a3c87ddd1';
    $pane->panel = 'postheaderrow1';
    $pane->type = 'menu_tree';
    $pane->subtype = 'main-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'menu_name' => 'main-menu',
      'parent_mlid' => 'main-menu:0',
      'title_link' => 0,
      'admin_title' => '',
      'level' => '2',
      'follow' => 0,
      'depth' => 0,
      'expanded' => 1,
      'sort' => 0,
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'c755a7a9-2c4c-4f7e-a0f7-fc3a3c87ddd1';
    $display->content['new-c755a7a9-2c4c-4f7e-a0f7-fc3a3c87ddd1'] = $pane;
    $display->panels['postheaderrow1'][4] = 'new-c755a7a9-2c4c-4f7e-a0f7-fc3a3c87ddd1';
    $pane = new stdClass();
    $pane->pid = 'new-1934fe03-def3-4988-af30-53b5a0ee8c33';
    $pane->panel = 'toprow1';
    $pane->type = 'views_panes';
    $pane->subtype = 'asu_news_new-panel_pane_3';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_settings' => 'fields',
      'header_type' => 'none',
      'view_mode' => 'teaser',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '1934fe03-def3-4988-af30-53b5a0ee8c33';
    $display->content['new-1934fe03-def3-4988-af30-53b5a0ee8c33'] = $pane;
    $display->panels['toprow1'][0] = 'new-1934fe03-def3-4988-af30-53b5a0ee8c33';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1';
  $uuid_panelizer[] = $display;

  return $uuid_panelizer;
}
