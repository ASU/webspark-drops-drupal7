<?php
/**
 * @file
 * webspark_content_callout.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function webspark_content_callout_defaultconfig_features() {
  return array(
    'webspark_content_callout' => array(
      'field_default_fields' => 'field_default_fields',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function webspark_content_callout_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'node-content_callout-field_callout_body'.
  $fields['node-content_callout-field_callout_body'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_callout_body',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(),
      'translatable' => 0,
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'content_callout',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 1,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_callout_body',
      'label' => 'Callout body',
      'required' => 1,
      'settings' => array(
        'linkit' => array(
          'enable' => 0,
          'insert_plugin' => '',
        ),
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'maxlength_js' => 300,
          'maxlength_js_enforce' => 0,
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
          'maxlength_js_truncate_html' => 0,
          'rows' => 3,
        ),
        'type' => 'text_textarea',
        'weight' => 2,
      ),
    ),
  );

  // Exported field: 'node-content_callout-field_callout_button'.
  $fields['node-content_callout-field_callout_button'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_callout_button',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => 0,
      'module' => 'link',
      'settings' => array(
        'attributes' => array(
          'class' => '',
          'rel' => '',
          'target' => 'default',
        ),
        'display' => array(
          'url_cutoff' => 80,
        ),
        'enable_tokens' => 1,
        'title' => 'optional',
        'title_maxlength' => 128,
        'title_value' => '',
        'url' => 0,
      ),
      'translatable' => 0,
      'type' => 'link_field',
    ),
    'field_instance' => array(
      'bundle' => 'content_callout',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'link',
          'settings' => array(),
          'type' => 'link_default',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_callout_button',
      'label' => 'Callout button',
      'required' => 0,
      'settings' => array(
        'attributes' => array(
          'class' => 'btn btn-primary',
          'configurable_title' => 0,
          'rel' => '',
          'target' => 'default',
          'title' => '',
        ),
        'display' => array(
          'url_cutoff' => 80,
        ),
        'enable_tokens' => 1,
        'linkit' => array(
          'enable' => 0,
          'insert_plugin' => '',
        ),
        'rel_remove' => 'default',
        'title' => 'required',
        'title_maxlength' => 128,
        'title_value' => '',
        'url' => 0,
        'user_register_form' => FALSE,
        'validate_url' => 1,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'link',
        'settings' => array(
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        ),
        'type' => 'link_field',
        'weight' => 3,
      ),
    ),
  );

  // Exported field: 'node-content_callout-field_callout_image'.
  $fields['node-content_callout-field_callout_image'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_callout_image',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'image',
      'settings' => array(
        'default_image' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'image',
    ),
    'field_instance' => array(
      'bundle' => 'content_callout',
      'deleted' => 0,
      'description' => 'Images should be about 370x250 px.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'image',
          'settings' => array(
            'image_link' => '',
            'image_style' => '',
          ),
          'type' => 'image',
          'weight' => 3,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_callout_image',
      'label' => 'Callout image',
      'required' => 0,
      'settings' => array(
        'alt_field' => 0,
        'default_image' => 0,
        'file_directory' => '',
        'file_extensions' => 'png gif jpg jpeg',
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'image',
        'settings' => array(
          'manualcrop_crop_info' => 1,
          'manualcrop_default_crop_area' => 1,
          'manualcrop_enable' => 0,
          'manualcrop_inline_crop' => 0,
          'manualcrop_instant_crop' => 0,
          'manualcrop_instant_preview' => 1,
          'manualcrop_keyboard' => 1,
          'manualcrop_maximize_default_crop_area' => 0,
          'manualcrop_require_cropping' => array(),
          'manualcrop_styles_list' => array(),
          'manualcrop_styles_mode' => 'include',
          'manualcrop_thumblist' => 0,
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
          'preview_image_style' => 'thumbnail',
          'progress_indicator' => 'throbber',
        ),
        'type' => 'image_image',
        'weight' => 5,
      ),
    ),
  );

  // Exported field: 'node-content_callout-field_callout_video'.
  $fields['node-content_callout-field_callout_video'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_callout_video',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => 0,
      'module' => 'video_embed_field',
      'settings' => array(),
      'translatable' => 0,
      'type' => 'video_embed_field',
    ),
    'field_instance' => array(
      'bundle' => 'content_callout',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'video_embed_field',
          'settings' => array(
            'description' => 1,
            'description_position' => 'bottom',
            'video_style' => 'normal',
          ),
          'type' => 'video_embed_field',
          'weight' => 4,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_callout_video',
      'label' => 'Callout video',
      'required' => 0,
      'settings' => array(
        'description_field' => 0,
        'description_length' => 128,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'video_embed_field',
        'settings' => array(
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        ),
        'type' => 'video_embed_field_video',
        'weight' => 6,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Callout body');
  t('Callout button');
  t('Callout image');
  t('Callout video');
  t('Images should be about 370x250 px.');

  return $fields;
}
