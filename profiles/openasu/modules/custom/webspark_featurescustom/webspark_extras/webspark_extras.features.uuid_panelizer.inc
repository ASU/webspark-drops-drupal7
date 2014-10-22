<?php
/**
 * @file
 * webspark_extras.features.uuid_panelizer.inc
 */

/**
 * Implements hook_uuid_features_default_panelizer().
 */
function webspark_extras_uuid_features_default_panelizer() {
  $uuid_panelizer = array();

  // Modified panelizer display for node 9244310b-87f3-42ad-a1a2-5f7498372fd9.
  $display = new panels_display();
  $display->layout = 'moscone';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'column1' => NULL,
      'column2' => NULL,
      'sidebar' => NULL,
      'contentmain' => array(
        'fullwidthbg' => '',
        'panerowpad' => array(
          'js-paddingbelow' => 'js-paddingbelow',
          'js-paddingabove' => 0,
          'js-remove2above' => 0,
          'js-remove6above' => 0,
          'js-remove2below' => 0,
          'js-remove6below' => 0,
        ),
        'panespace' => array(
          'space-top-sm' => 0,
          'space-top-md' => 0,
          'space-bot-sm' => 0,
          'space-bot-md' => 0,
        ),
      ),
      'header' => NULL,
    ),
    'header' => array(
      'style' => '0',
    ),
    'sidebar' => array(
      'style' => '0',
    ),
    'contentmain' => array(
      'style' => 'customstyles',
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '16346c80-6fcf-4cee-bf7a-9c0173fc2916';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b';
    $pane->panel = 'contentmain';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'trim_length' => '250',
      ),
      'context' => 'panelizer',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'style' => 'customstyles',
      'settings' => array(
        'fullwidthbg' => '',
        'panerowpad' => array(
          'js-paddingabove' => 'js-paddingabove',
          'js-paddingbelow' => 'js-paddingbelow',
          'js-remove2above' => 0,
          'js-remove6above' => 0,
          'js-remove2below' => 0,
          'js-remove6below' => 0,
        ),
        'panespace' => array(
          'space-top-sm' => 0,
          'space-top-md' => 0,
          'space-bot-sm' => 0,
          'space-bot-md' => 0,
        ),
      ),
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '59cafe99-f0a0-4a3a-a13f-8f108d69d18b';
    $display->content['new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b'] = $pane;
    $display->panels['contentmain'][0] = 'new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b';
    $pane = new stdClass();
    $pane->pid = 'new-28834747-387f-44a5-a921-557ce847e17d';
    $pane->panel = 'header';
    $pane->type = 'fieldable_panels_pane';
    $pane->subtype = 'fpid:66';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'Full',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '28834747-387f-44a5-a921-557ce847e17d';
    $display->content['new-28834747-387f-44a5-a921-557ce847e17d'] = $pane;
    $display->panels['header'][0] = 'new-28834747-387f-44a5-a921-557ce847e17d';
    $pane = new stdClass();
    $pane->pid = 'new-cb8be7da-60cb-402e-a22d-89edceefe82d';
    $pane->panel = 'sidebar';
    $pane->type = 'block';
    $pane->subtype = 'easy_breadcrumb-easy_breadcrumb';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'cb8be7da-60cb-402e-a22d-89edceefe82d';
    $display->content['new-cb8be7da-60cb-402e-a22d-89edceefe82d'] = $pane;
    $display->panels['sidebar'][0] = 'new-cb8be7da-60cb-402e-a22d-89edceefe82d';
    $pane = new stdClass();
    $pane->pid = 'new-97e71f6e-45a6-490e-852e-17356cc9bab0';
    $pane->panel = 'sidebar';
    $pane->type = 'menu_tree';
    $pane->subtype = 'main-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'menu_name' => 'main-menu',
      'parent_mlid' => 1281,
      'parent' => 'main-menu:1281',
      'title_link' => 0,
      'admin_title' => '',
      'level' => '1',
      'follow' => 0,
      'depth' => 0,
      'expanded' => 0,
      'sort' => 0,
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'style' => 'default',
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '97e71f6e-45a6-490e-852e-17356cc9bab0';
    $display->content['new-97e71f6e-45a6-490e-852e-17356cc9bab0'] = $pane;
    $display->panels['sidebar'][1] = 'new-97e71f6e-45a6-490e-852e-17356cc9bab0';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $uuid_panelizer[] = $display;

  return $uuid_panelizer;
}
