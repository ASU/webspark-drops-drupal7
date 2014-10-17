<?php
/**
 * @file
 * webspark_banner.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function webspark_banner_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'fieldable_panels_pane-banner-field_banner_image'
  $field_instances['fieldable_panels_pane-banner-field_banner_image'] = array(
    'bundle' => 'banner',
    'deleted' => 0,
    'description' => 'Images should be 1220 x 200 px. Smaller images will be scaled up; larger ones will be cropped.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'backgroundfield',
        'settings' => array(),
        'type' => 'backgroundfield_formatter',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_banner_image',
    'label' => 'Banner image',
    'required' => 0,
    'settings' => array(
      'alt_field' => '',
      'css_attachment' => 'scroll',
      'css_h_position' => 'center',
      'css_important' => 0,
      'css_repeat' => 'no-repeat',
      'css_selector' => '.title-banner',
      'css_v_position' => 'center',
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'image_style' => 'no_style',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'backgroundfield',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => '',
      ),
      'type' => 'backgroundfield_widget',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Banner image');
  t('Images should be 1220 x 200 px. Smaller images will be scaled up; larger ones will be cropped.');

  return $field_instances;
}
