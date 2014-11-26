<?php
/**
 * @file
 * webspark_banner.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function webspark_banner_defaultconfig_features() {
  return array(
    'webspark_banner' => array(
      'field_default_fields' => 'field_default_fields',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function webspark_banner_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'fieldable_panels_pane-banner-field_banner_image'.
  $fields['fieldable_panels_pane-banner-field_banner_image'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_banner_image',
      'foreign keys' => array(
        'file_managed' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(),
      'locked' => 0,
      'module' => 'backgroundfield',
      'settings' => array(
        'default_image' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'backgroundfield',
    ),
    'field_instance' => array(
      'bundle' => 'banner',
      'deleted' => 0,
      'description' => '<ul class="help-text">
<li>Add a title banner only <strong>to the top section</strong> of your page and in a single-region row.</li>
<li>Images should be 1220 x 200 px. Smaller images will be scaled up; larger ones will be cropped.</li>
<li>When adding a new image, you must refresh the page after saving to view the image.</li>
</ul>',
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
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<ul class="help-text">
<li>Add a title banner only <strong>to the top section</strong> of your page and in a single-region row.</li>
<li>Images should be 1220 x 200 px. Smaller images will be scaled up; larger ones will be cropped.</li>
<li>When adding a new image, you must refresh the page after saving to view the image.</li>
</ul>');
  t('Banner image');

  return $fields;
}
