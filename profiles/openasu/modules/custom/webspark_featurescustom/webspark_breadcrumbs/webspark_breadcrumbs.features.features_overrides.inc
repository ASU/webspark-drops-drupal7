<?php
/**
 * @file
 * webspark_breadcrumbs.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function webspark_breadcrumbs_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: panelizer_defaults
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-0a2c7b96-5f45-4e85-8e00-88fee50f4f71|position"] = 5;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1|position"] = 2;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b|position"] = 3;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-804c8d46-cd58-4f65-8692-2b32629178b0"] = (object) array(
      'pid' => 'new-804c8d46-cd58-4f65-8692-2b32629178b0',
      'panel' => 'contentmain',
      'type' => 'block',
      'subtype' => 'easy_breadcrumb-easy_breadcrumb',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
        'override_title' => 0,
        'override_title_text' => '',
      ),
      'cache' => array(),
      'style' => array(
        'settings' => NULL,
      ),
      'css' => array(),
      'extras' => array(),
      'position' => 0,
      'locks' => array(),
      'uuid' => '804c8d46-cd58-4f65-8692-2b32629178b0',
    );
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-844c76b3-e8e1-4c55-87ad-6970f51488e9"] = (object) array(
      'pid' => 'new-844c76b3-e8e1-4c55-87ad-6970f51488e9',
      'panel' => 'contentmain',
      'type' => 'node_title',
      'subtype' => 'node_title',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
        'link' => 0,
        'markup' => 'h1',
        'id' => '',
        'class' => 'page-title',
        'context' => 'panelizer',
        'override_title' => 1,
        'override_title_text' => '',
      ),
      'cache' => array(),
      'style' => array(
        'settings' => NULL,
      ),
      'css' => array(),
      'extras' => array(),
      'position' => 1,
      'locks' => array(),
      'uuid' => '844c76b3-e8e1-4c55-87ad-6970f51488e9',
    );
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-f3bf9c22-9b22-41d2-a57e-110951093871|position"] = 4;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|layout"] = 'moscone';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panel_settings|style_settings|footer"] = NULL;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panel_settings|style_settings|header"] = NULL;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|0"] = 'new-804c8d46-cd58-4f65-8692-2b32629178b0';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|1"] = 'new-844c76b3-e8e1-4c55-87ad-6970f51488e9';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|2"] = 'new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|3"] = 'new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|4"] = 'new-f3bf9c22-9b22-41d2-a57e-110951093871';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|5"] = 'new-0a2c7b96-5f45-4e85-8e00-88fee50f4f71';
  $overrides["panelizer_defaults.node:panopoly_page:default.extra|panels_breadcrumbs_home"] = 1;
  $overrides["panelizer_defaults.node:panopoly_page:default.extra|panels_breadcrumbs_paths"] = '';
  $overrides["panelizer_defaults.node:panopoly_page:default.extra|panels_breadcrumbs_state"] = 0;
  $overrides["panelizer_defaults.node:panopoly_page:default.extra|panels_breadcrumbs_titles"] = '';
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|content|new-69232890-3572-4669-8ec0-3e3025c33b09"] = (object) array(
      'pid' => 'new-69232890-3572-4669-8ec0-3e3025c33b09',
      'panel' => 'sidebar',
      'type' => 'menu_tree',
      'subtype' => 'main-menu',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
        'menu_name' => 'main-menu',
        'parent_mlid' => 0,
        'parent' => 'main-menu:0',
        'title_link' => 0,
        'admin_title' => '',
        'level' => 2,
        'follow' => 0,
        'depth' => 0,
        'expanded' => 1,
        'sort' => 0,
        'override_title' => 1,
        'override_title_text' => '',
      ),
      'cache' => array(),
      'style' => array(
        'settings' => NULL,
      ),
      'css' => array(),
      'extras' => array(),
      'position' => 0,
      'locks' => array(),
      'uuid' => '69232890-3572-4669-8ec0-3e3025c33b09',
    );
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|content|new-74f82699-93ba-4b15-8bcf-e3bfa1894d40|position"] = 2;
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|content|new-96fb1bf5-7ac2-4566-9dae-876a363c71c9|position"] = 3;
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|content|new-ade8f2e7-1173-418b-8f94-0a2d8f4cdb9d|position"] = 4;
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|content|new-d1e53aae-d3f3-4a73-b3f9-9bdbbc5913a4"] = (object) array(
      'pid' => 'new-d1e53aae-d3f3-4a73-b3f9-9bdbbc5913a4',
      'panel' => 'contentmain',
      'type' => 'block',
      'subtype' => 'easy_breadcrumb-easy_breadcrumb',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
        'override_title' => 1,
        'override_title_text' => '<none>',
      ),
      'cache' => array(),
      'style' => array(
        'settings' => NULL,
      ),
      'css' => array(),
      'extras' => array(),
      'position' => 0,
      'locks' => array(),
      'uuid' => 'd1e53aae-d3f3-4a73-b3f9-9bdbbc5913a4',
    );
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|content|new-e0d93093-20b4-42cd-bf23-6f2f487240a6|position"] = 1;
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|layout"] = 'moscone';
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|panel_settings|style_settings|footer"] = NULL;
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|panel_settings|style_settings|header"] = NULL;
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|panels|contentmain|0"] = 'new-d1e53aae-d3f3-4a73-b3f9-9bdbbc5913a4';
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|panels|contentmain|1"] = 'new-e0d93093-20b4-42cd-bf23-6f2f487240a6';
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|panels|contentmain|2"] = 'new-74f82699-93ba-4b15-8bcf-e3bfa1894d40';
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|panels|contentmain|3"] = 'new-96fb1bf5-7ac2-4566-9dae-876a363c71c9';
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|panels|contentmain|4"] = 'new-ade8f2e7-1173-418b-8f94-0a2d8f4cdb9d';
  $overrides["panelizer_defaults.node:panopoly_page:default:default.display|panels|sidebar"] = array(
    0 => 'new-69232890-3572-4669-8ec0-3e3025c33b09',
  );

 return $overrides;
}
