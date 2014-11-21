<?php
/**
 * @file
 * webspark_jumbohero.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function webspark_jumbohero_defaultconfig_features() {
  return array(
    'webspark_jumbohero' => array(
      'field_default_fields' => 'field_default_fields',
      'field_group_info' => 'field_group_info',
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function webspark_jumbohero_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'fieldable_panels_pane-jumbohero-field_webspark_hero_gradbtn'.
  $fields['fieldable_panels_pane-jumbohero-field_webspark_hero_gradbtn'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_webspark_hero_gradbtn',
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
      'bundle' => 'jumbohero',
      'default_value' => array(
        0 => array(
          'title' => 'Graduate Programs',
          'url' => 'https://webapp4.asu.edu/programs/t5/graduate/false',
        ),
      ),
      'deleted' => 0,
      'description' => 'It is recommended to add a button to explore graduate programs.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'link',
          'settings' => array(),
          'type' => 'link_default',
          'weight' => 4,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_webspark_hero_gradbtn',
      'label' => 'Explore graduate programs button (recommended)',
      'required' => 0,
      'settings' => array(
        'attributes' => array(
          'class' => 'btn btn-blue btn-block',
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
        'weight' => 7,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-jumbohero-field_webspark_hero_primarybtn'.
  $fields['fieldable_panels_pane-jumbohero-field_webspark_hero_primarybtn'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_webspark_hero_primarybtn',
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
      'bundle' => 'jumbohero',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '<strong>Only add this button if you did not add the explore degree buttons.</strong>   This single call-to-action button should support the single most important item of the hero message and drive the user.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'link',
          'settings' => array(),
          'type' => 'link_default',
          'weight' => 5,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_webspark_hero_primarybtn',
      'label' => 'Other call to action button (alternative)',
      'required' => 0,
      'settings' => array(
        'attributes' => array(
          'class' => 'btn btn-primary btn-col-4',
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
        'weight' => 8,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-jumbohero-field_webspark_hero_ugradbtn'.
  $fields['fieldable_panels_pane-jumbohero-field_webspark_hero_ugradbtn'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_webspark_hero_ugradbtn',
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
      'bundle' => 'jumbohero',
      'default_value' => array(
        0 => array(
          'title' => 'Undergraduate Programs',
          'url' => 'https://webapp4.asu.edu/programs/t5/undergrad',
        ),
      ),
      'deleted' => 0,
      'description' => 'It is recommended to add a button to explore undergraduate programs.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'link',
          'settings' => array(),
          'type' => 'link_default',
          'weight' => 3,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_webspark_hero_ugradbtn',
      'label' => 'Explore undergraduate programs button (recommended)',
      'required' => 0,
      'settings' => array(
        'attributes' => array(
          'class' => 'btn btn-blue btn-block',
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
        'weight' => 6,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-jumbohero-field_webspark_jumbo_position'.
  $fields['fieldable_panels_pane-jumbohero-field_webspark_jumbo_position'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_webspark_jumbo_position',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => 0,
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          'top-left' => 'top-left',
          'top-center' => 'top-center',
          'top-right' => 'top-right',
          'bottom-left' => 'bottom-left',
          'bottom-center' => 'bottom-center',
          'bottom-right' => 'bottom-right',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => 0,
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'jumbohero',
      'default_value' => array(
        0 => array(
          'value' => 'top-left',
        ),
      ),
      'deleted' => 0,
      'description' => 'Choose a position for the content (title, text and/or buttons) on the hero.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => 6,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_webspark_jumbo_position',
      'label' => 'Position',
      'required' => 1,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(
          'apply_chosen' => 0,
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        ),
        'type' => 'options_select',
        'weight' => 4,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-jumbohero-field_webspark_jumbohero_bgimg'.
  $fields['fieldable_panels_pane-jumbohero-field_webspark_jumbohero_bgimg'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_webspark_jumbohero_bgimg',
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
      'bundle' => 'jumbohero',
      'deleted' => 0,
      'description' => '<h4>Tips & Instructions</h4>

<p>Heroes should be added <strong>only to the top region</strong> of your page.</p>

<p>Images should be 1170 x 700 px. Smaller images will be scaled up; larger ones will be cropped.</p>

<p>When adding a new image, <strong>refresh the page</strong> after saving to view the image (it displays as a CSS background image).</p>',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'backgroundfield',
          'settings' => array(),
          'type' => 'backgroundfield_formatter',
          'weight' => 1,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_webspark_jumbohero_bgimg',
      'label' => 'Hero image',
      'required' => 0,
      'settings' => array(
        'alt_field' => '',
        'css_attachment' => 'scroll',
        'css_h_position' => 'center',
        'css_important' => 0,
        'css_repeat' => 'no-repeat',
        'css_selector' => '.pane-bundle-jumbohero',
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
        'weight' => 1,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-jumbohero-field_webspark_jumbohero_blurb'.
  $fields['fieldable_panels_pane-jumbohero-field_webspark_jumbohero_blurb'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_webspark_jumbohero_blurb',
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
      'bundle' => 'jumbohero',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_webspark_jumbohero_blurb',
      'label' => 'Blurb',
      'required' => 0,
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
          'maxlength_js' => 170,
          'maxlength_js_enforce' => 0,
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
          'maxlength_js_truncate_html' => 0,
          'rows' => 2,
        ),
        'type' => 'text_textarea',
        'weight' => 2,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<h4>Tips & Instructions</h4>

<p>Heroes should be added <strong>only to the top region</strong> of your page.</p>

<p>Images should be 1170 x 700 px. Smaller images will be scaled up; larger ones will be cropped.</p>

<p>When adding a new image, <strong>refresh the page</strong> after saving to view the image (it displays as a CSS background image).</p>');
  t('<strong>Only add this button if you did not add the explore degree buttons.</strong>   This single call-to-action button should support the single most important item of the hero message and drive the user.');
  t('Blurb');
  t('Choose a position for the content (title, text and/or buttons) on the hero.');
  t('Explore graduate programs button (recommended)');
  t('Explore undergraduate programs button (recommended)');
  t('Hero image');
  t('It is recommended to add a button to explore graduate programs.');
  t('It is recommended to add a button to explore undergraduate programs.');
  t('Other call to action button (alternative)');
  t('Position');

  return $fields;
}

/**
 * Implements hook_defaultconfig_field_group_info().
 */
function webspark_jumbohero_defaultconfig_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_webspark_jumbohero_buttons|fieldable_panels_pane|jumbohero|form';
  $field_group->group_name = 'group_webspark_jumbohero_buttons';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'jumbohero';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Recommended buttons',
    'weight' => '3',
    'children' => array(
      0 => 'field_webspark_hero_ugradbtn',
      1 => 'field_webspark_hero_gradbtn',
      2 => 'field_webspark_hero_primarybtn',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Recommended buttons',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-webspark-jumbohero-buttons field-group-fieldset',
        'description' => '<strong>Recommended:</strong>   Add exploring undergraduate and graduate degree program buttons as the Calls to Action.<br><br>
<strong>Alternative:</strong>  In place of degree buttons, a single call to action can be use to support the content, driving the user the single most important item of the message.',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_webspark_jumbohero_buttons|fieldable_panels_pane|jumbohero|form'] = $field_group;

  return $export;
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function webspark_jumbohero_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_fieldable_panels_pane__jumbohero';
  $strongarm->value = array(
    'view_modes' => array(
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
      ),
      'display' => array(
        'title' => array(
          'default' => array(
            'weight' => '0',
            'visible' => TRUE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_fieldable_panels_pane__jumbohero'] = $strongarm;

  return $export;
}
