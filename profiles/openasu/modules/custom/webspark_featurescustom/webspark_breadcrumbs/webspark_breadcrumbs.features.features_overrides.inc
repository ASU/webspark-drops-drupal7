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
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-0a2c7b96-5f45-4e85-8e00-88fee50f4f71"]["DELETED"] = TRUE;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-2ded7768-2190-469f-8a69-7a043da98ddf"] = (object) array(
      'pid' => 'new-2ded7768-2190-469f-8a69-7a043da98ddf',
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
      'uuid' => '2ded7768-2190-469f-8a69-7a043da98ddf',
    );
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1"]["DELETED"] = TRUE;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b|position"] = 2;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-c755a7a9-2c4c-4f7e-a0f7-fc3a3c87ddd1|configuration|parent"] = 'main-menu:0';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-c755a7a9-2c4c-4f7e-a0f7-fc3a3c87ddd1|configuration|parent_mlid"] = 0;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-f3bf9c22-9b22-41d2-a57e-110951093871|position"] = 3;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|content|new-f72b7324-ddf3-47be-85a1-a6b4899ab36b"] = (object) array(
      'pid' => 'new-f72b7324-ddf3-47be-85a1-a6b4899ab36b',
      'panel' => 'contentmain',
      'type' => 'block',
      'subtype' => 'easy_breadcrumb-easy_breadcrumb',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
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
      'uuid' => 'f72b7324-ddf3-47be-85a1-a6b4899ab36b',
    );
  $overrides["panelizer_defaults.node:panopoly_page:default.display|hide_title"] = 1;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|layout"] = 'moscone';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panel_settings|style_settings|footer"] = NULL;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panel_settings|style_settings|header"] = NULL;
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|0"] = 'new-f72b7324-ddf3-47be-85a1-a6b4899ab36b';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|1"] = 'new-2ded7768-2190-469f-8a69-7a043da98ddf';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|2"] = 'new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|panels|contentmain|3"] = 'new-f3bf9c22-9b22-41d2-a57e-110951093871';
  $overrides["panelizer_defaults.node:panopoly_page:default.display|title_pane"] = 0;

 return $overrides;
}
