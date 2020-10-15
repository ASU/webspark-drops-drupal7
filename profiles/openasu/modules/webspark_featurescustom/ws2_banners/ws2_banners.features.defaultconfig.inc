<?php

/**
 * @file
 * ws2_banners.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function ws2_banners_defaultconfig_features() {
  return array(
    'ws2_banners' => array(
      'default_fieldable_panels_pane_type' => 'default_fieldable_panels_pane_type',
      'field_default_fields' => 'field_default_fields',
      'field_group_info' => 'field_group_info',
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_default_fieldable_panels_pane_type().
 */
function ws2_banners_defaultconfig_default_fieldable_panels_pane_type() {
  $export = array();

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'banners_ws2';
  $fieldable_panels_pane_type->title = 'WS2L Banner';
  $fieldable_panels_pane_type->description = '';
  $export['banners_ws2'] = $fieldable_panels_pane_type;

  return $export;
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function ws2_banners_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'fieldable_panels_pane-banners_ws2-field_banner_body'.
  $fields['fieldable_panels_pane-banners_ws2-field_banner_body'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_banner_body',
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
      'bundle' => 'banners_ws2',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 5,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_banner_body',
      'label' => 'Banner body',
      'required' => 0,
      'settings' => array(
        'linkit' => array(
          'button_text' => 'Search',
          'enable' => 0,
          'profile' => '',
        ),
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'maxlength_js' => '',
          'maxlength_js_enforce' => 0,
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
          'maxlength_js_truncate_html' => 0,
          'rows' => 5,
        ),
        'type' => 'text_textarea',
        'weight' => 2,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-banners_ws2-field_banner_color'.
  $fields['fieldable_panels_pane-banners_ws2-field_banner_color'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_banner_color',
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
          'ws2-banner-success' => 'Success',
          'ws2-banner-warning' => 'Alert',
          'ws2-banner-info' => 'Info',
          'ws2-element-alt-gray' => 'Gray',
          'ws2-element-alt-black' => 'Black',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => 0,
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'banners_ws2',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => 'Success == green, Alert == orange, Info == blue. The gray and black will have alternate styling applied to buttons, etc.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_banner_color',
      'label' => 'Banner color',
      'required' => 1,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(
          'apply_chosen' => 0,
        ),
        'type' => 'options_select',
        'weight' => 1,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-banners_ws2-field_banner_title_int'.
  $fields['fieldable_panels_pane-banners_ws2-field_banner_title_int'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_banner_title_int',
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
      'settings' => array(
        'max_length' => 255,
      ),
      'translatable' => 0,
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'banners_ws2',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => 'Different that the FPP title. This appears to the right of the bell icon.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 4,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_banner_title_int',
      'label' => 'Banner title - internal',
      'required' => 1,
      'settings' => array(
        'linkit' => array(
          'button_text' => 'Search',
          'enable' => 0,
          'profile' => '',
        ),
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'maxlength_js' => 0,
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => 1,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-banners_ws2-field_ws2_button'.
  $fields['fieldable_panels_pane-banners_ws2-field_ws2_button'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_ws2_button',
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
      'bundle' => 'banners_ws2',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'link',
          'settings' => array(
            'custom_title' => '',
          ),
          'type' => 'link_default',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_ws2_button',
      'label' => 'WS2 Button',
      'required' => 0,
      'settings' => array(
        'absolute_url' => 0,
        'attributes' => array(
          'class' => 'btn btn-sm btn-black',
          'configurable_class' => 0,
          'configurable_title' => 0,
          'rel' => '',
          'target' => 'user',
          'title' => '',
        ),
        'display' => array(
          'url_cutoff' => 80,
        ),
        'enable_tokens' => 1,
        'linkit' => array(
          'button_text' => 'Search',
          'enable' => 1,
          'profile' => 'content_fields',
        ),
        'rel_remove' => 'default',
        'title' => 'required',
        'title_allowed_values' => '',
        'title_label_use_field_label' => 0,
        'title_maxlength' => 128,
        'title_value' => '',
        'url' => 0,
        'user_register_form' => FALSE,
        'validate_url' => 1,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_field',
        'weight' => -3,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-banners_ws2-field_ws2_button_2'.
  $fields['fieldable_panels_pane-banners_ws2-field_ws2_button_2'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_ws2_button_2',
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
      'bundle' => 'banners_ws2',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'link',
          'settings' => array(
            'custom_title' => '',
          ),
          'type' => 'link_default',
          'weight' => 3,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_ws2_button_2',
      'label' => 'WS2 Button 2',
      'required' => 0,
      'settings' => array(
        'absolute_url' => 0,
        'attributes' => array(
          'class' => 'btn btn-sm btn-black',
          'configurable_class' => 0,
          'configurable_title' => 0,
          'rel' => '',
          'target' => 'user',
          'title' => '',
        ),
        'display' => array(
          'url_cutoff' => 80,
        ),
        'enable_tokens' => 1,
        'linkit' => array(
          'button_text' => 'Search',
          'enable' => 0,
          'profile' => '',
        ),
        'rel_remove' => 'default',
        'title' => 'required',
        'title_allowed_values' => '',
        'title_label_use_field_label' => 0,
        'title_maxlength' => 128,
        'title_value' => '',
        'url' => 0,
        'user_register_form' => FALSE,
        'validate_url' => 1,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_field',
        'weight' => -2,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-fields-field_banner_title'.
  $fields['fieldable_panels_pane-fields-field_banner_title'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_banner_title',
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
      'settings' => array(
        'max_length' => 255,
      ),
      'translatable' => 0,
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'fields',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_banner_title',
      'label' => 'Banner title',
      'required' => FALSE,
      'settings' => array(
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => 1,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<ul class="help-text">
<li>Add a title banner only <strong>to the top section</strong> of your page and in a single-region row.</li>
<li>Images should be 1170 x 200 px for optimal display.</li>
<li>When adding a new image, you must refresh the page after saving to view the image.</li>
</ul>');
  t('Banner body');
  t('Banner color');
  t('Banner image');
  t('Banner title');
  t('Banner title - internal');
  t('Different that the FPP title. This appears to the right of the bell icon.');
  t('Success == green, Alert == orange, Info == blue. The gray and black will have alternate styling applied to buttons, etc.');
  t('WS2 Button');
  t('WS2 Button 2');

  return $fields;
}

/**
 * Implements hook_defaultconfig_field_group_info().
 */
function ws2_banners_defaultconfig_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_banner_text|fieldable_panels_pane|banners_ws2|default';
  $field_group->group_name = 'group_banner_text';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'banners_ws2';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '0',
    'children' => array(
      0 => 'field_banner_body',
      1 => 'field_banner_title_int',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'col-sm-12 col-lg-6 col-md-6',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_banner_text|fieldable_panels_pane|banners_ws2|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_banner_text|fieldable_panels_pane|banners_ws2|form';
  $field_group->group_name = 'group_banner_text';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'banners_ws2';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Banner text',
    'weight' => '2',
    'children' => array(
      0 => 'field_banner_body',
      1 => 'field_banner_title_int',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_banner_text|fieldable_panels_pane|banners_ws2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_buttons|fieldable_panels_pane|banners_ws2|default';
  $field_group->group_name = 'group_buttons';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'banners_ws2';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '1',
    'children' => array(
      0 => 'field_ws2_button',
      1 => 'field_ws2_button_2',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'col-sm-12 col-lg-5 col-md-5',
        'element' => 'div',
        'show_label' => '0',
        'label_element' => 'div',
        'attributes' => '',
      ),
    ),
  );
  $field_groups['group_buttons|fieldable_panels_pane|banners_ws2|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_buttons|fieldable_panels_pane|banners_ws2|form';
  $field_group->group_name = 'group_buttons';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'banners_ws2';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Buttons',
    'weight' => '3',
    'children' => array(
      0 => 'field_ws2_button',
      1 => 'field_ws2_button_2',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Buttons',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-buttons field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_buttons|fieldable_panels_pane|banners_ws2|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Banner text');
  t('Buttons');

  return $field_groups;
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function ws2_banners_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_fieldable_panels_pane__banners_ws2';
  $strongarm->value = array(
    'view_modes' => array(
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'preview' => array(
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
            'weight' => '1',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_fieldable_panels_pane__banners_ws2'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function ws2_banners_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fieldable banners_ws2'.
  $permissions['create fieldable banners_ws2'] = array(
    'name' => 'create fieldable banners_ws2',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable banners_ws2'.
  $permissions['delete fieldable banners_ws2'] = array(
    'name' => 'delete fieldable banners_ws2',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable banners_ws2'.
  $permissions['edit fieldable banners_ws2'] = array(
    'name' => 'edit fieldable banners_ws2',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  return $permissions;
}
