<?php
/**
 * @file
 * webspark_breadcrumbs.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function webspark_breadcrumbs_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_panelizer_defaults_override_alter().
 */
function webspark_breadcrumbs_panelizer_defaults_override_alter(&$data) {
  if (isset($data['node:panopoly_page:default'])) {
    $data['node:panopoly_page:default']->display->content['new-2ded7768-2190-469f-8a69-7a043da98ddf'] = (object) array(
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
        ); /* WAS: '' */
    $data['node:panopoly_page:default']->display->content['new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b']->position = 2; /* WAS: 1 */
    $data['node:panopoly_page:default']->display->content['new-c755a7a9-2c4c-4f7e-a0f7-fc3a3c87ddd1']->configuration['parent'] = 'main-menu:0'; /* WAS: '' */
    $data['node:panopoly_page:default']->display->content['new-c755a7a9-2c4c-4f7e-a0f7-fc3a3c87ddd1']->configuration['parent_mlid'] = 0; /* WAS: 'main-menu:0' */
    $data['node:panopoly_page:default']->display->content['new-f3bf9c22-9b22-41d2-a57e-110951093871']->position = 3; /* WAS: 2 */
    $data['node:panopoly_page:default']->display->content['new-f72b7324-ddf3-47be-85a1-a6b4899ab36b'] = (object) array(
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
        ); /* WAS: '' */
    $data['node:panopoly_page:default']->display->hide_title = 1; /* WAS: 0 */
    $data['node:panopoly_page:default']->display->layout = 'moscone'; /* WAS: 'bryant' */
    $data['node:panopoly_page:default']->display->panel_settings['style_settings']['footer'] = NULL; /* WAS: '' */
    $data['node:panopoly_page:default']->display->panel_settings['style_settings']['header'] = NULL; /* WAS: '' */
    $data['node:panopoly_page:default']->display->panels['contentmain'][0] = 'new-f72b7324-ddf3-47be-85a1-a6b4899ab36b'; /* WAS: 'new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1' */
    $data['node:panopoly_page:default']->display->panels['contentmain'][1] = 'new-2ded7768-2190-469f-8a69-7a043da98ddf'; /* WAS: 'new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b' */
    $data['node:panopoly_page:default']->display->panels['contentmain'][2] = 'new-59cafe99-f0a0-4a3a-a13f-8f108d69d18b'; /* WAS: 'new-f3bf9c22-9b22-41d2-a57e-110951093871' */
    $data['node:panopoly_page:default']->display->panels['contentmain'][3] = 'new-f3bf9c22-9b22-41d2-a57e-110951093871'; /* WAS: 'new-0a2c7b96-5f45-4e85-8e00-88fee50f4f71' */
    $data['node:panopoly_page:default']->display->title_pane = 0; /* WAS: 'new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1' */
    unset($data['node:panopoly_page:default']->display->content['new-0a2c7b96-5f45-4e85-8e00-88fee50f4f71']);
    unset($data['node:panopoly_page:default']->display->content['new-34b4f35e-bc4b-4819-905c-6b6bf84bffe1']);
  }
}
