<?php

/**
 * @file - Customizes/overrides Panels settings set earlier by Panopoly
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function webspark_featurescustom_form_panopoly_page_node_form_alter(&$form, &$form_state, $form_id) {
  // panopoly_page_node_form
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

  $entity_info['fieldable_panels_pane']['bundles']['text'] = array(
    'label' => t('Add text'),
    'description' => t('Add new, separate body of text.'),
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

  // Changing descriptions of Panopoly's FPP-based content widgets for clarity
  $entity_info['fieldable_panels_pane']['bundles']['quick_links']['description'] = t('Creates bullet list of added URLs/links.'); // Add Links
  $entity_info['fieldable_panels_pane']['bundles']['basic_file']['description'] = t('Upload a file and display a link to it.
    Optional description text is displayed above the file link.'); // Add file
  $entity_info['fieldable_panels_pane']['bundles']['image']['description'] = t('Add 100%-wide responsive image'); // Add Responsive image
  $entity_info['fieldable_panels_pane']['bundles']['text']['description'] = t('Add new, separate body of text/content.'); // Add text
  $entity_info['fieldable_panels_pane']['bundles']['map']['description'] = t('Add a Google map based on a street address.
    IMPORTANT: Use the more detailed Enhanced ASU map when pointing at ASU-related locations.'); // Add map
  $entity_info['fieldable_panels_pane']['bundles']['table']['description'] = t('Adds an HTML formatted data table.
    Customizable number of rows and columns.'); // Add table
  $entity_info['fieldable_panels_pane']['bundles']['video']['description'] = t('Adds a URL for videos from online video from Youtube or Vimeo
    (other video sites are not supported).'); // Add video
  $entity_info['fieldable_panels_pane']['bundles']['spotlight']['description'] = t('DEPRECATED - Use ASU Spotlight instead.'); // Add Spotlight
}
