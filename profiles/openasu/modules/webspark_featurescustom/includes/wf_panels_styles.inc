<?php

/**
 * @file - Customizes/overrides Panels settings set earlier by Panopoly
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function webspark_featurescustom_form_panopoly_page_node_form_alter(&$form, &$form_state, $form_id) {
  // Content Page node form
  // + Remove feature fields from panopoly content page
  $form['field_featured_image']['#access'] = FALSE;
  $form['field_featured_categories']['#access'] = FALSE;
  $form['field_featured_status']['#access'] = FALSE;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function webspark_featurescustom_form_panels_edit_style_settings_form_alter(&$form, &$form_state, $form_id) {
  // Panels styles accordion settings form
  // + Set default configuration settings
  $form['settings']['autoHeight']['#default_value'] = 0;
  $form['settings']['clearStyle']['#default_value'] = 1;
  $form['settings']['collapsible']['#default_value'] = 1;
  $form['settings']['fillSpace']['#default_value'] = 1;
}

/**
 * Implementation of hook_entity_info_alter()
 */
function webspark_featurescustom_entity_info_alter(&$entity_info) {
  // Changing name of Basic Image widget for clarity
  $entity_info['fieldable_panels_pane']['bundles']['image'] = array(
    'label' => t('Add responsive image'),
    'description' => t('Add 100%-wide responsive image'),
    'pane category' => t('Custom'),
    'pane top level' => TRUE,
    'pane icon' => drupal_get_path('module', 'panopoly_widgets') . '/images/icon_image.png',
    'admin' => array(
      'path' => 'admin/structure/fieldable-panels-panes/manage/%fieldable_panels_panes_type',
      'bundle argument' => 4,
      'real path' => 'admin/structure/fieldable-panels-panes/manage/image',
      'access arguments' => array('administer fieldable panels panes'),
    ),
  );

  // Changing description of Basic text for clarity
  $entity_info['fieldable_panels_pane']['bundles']['text'] = array(
    'label' => t('Add text'),
    'description' => t('Add text and media'),
    'pane category' => t('Custom'),
    'pane top level' => TRUE,
    'pane icon' => drupal_get_path('module', 'panopoly_widgets') . '/images/icon_text.png',
    'admin' => array(
      'path' => 'admin/structure/fieldable-panels-panes/manage/%fieldable_panels_panes_type',
      'bundle argument' => 4,
      'real path' => 'admin/structure/fieldable-panels-panes/manage/text',
      'access arguments' => array('administer fieldable panels panes'),
    ),
  );

  /* WEBSPARK-1123 - Obscuring Panopoly Widgets-generated spotlight in IPE UI */
  $entity_info['fieldable_panels_pane']['bundles']['map']['pane category'] = t('DEPRECATED by Webspark');
  $entity_info['fieldable_panels_pane']['bundles']['map']['pane icon'] = drupal_get_path('module', 'webspark_panels_styles') . '/images/icon_map_DEP.png';
  $entity_info['fieldable_panels_pane']['bundles']['spotlight']['pane category'] = t('DEPRECATED by Webspark');
  $entity_info['fieldable_panels_pane']['bundles']['spotlight']['pane icon'] = drupal_get_path('module', 'webspark_panels_styles') . '/images/icon_spotlight_DEP.png';
}