<?php
/**
 * @file
 * asu_isearch.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function asu_isearch_defaultconfig_features() {
  return array(
    'asu_isearch' => array(
      'field_default_fields' => 'field_default_fields',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function asu_isearch_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'fieldable_panels_pane-isearch_directory-field_isearch_config'.
  $fields['fieldable_panels_pane-isearch_directory-field_isearch_config'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_isearch_config',
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
      'bundle' => 'isearch_directory',
      'default_value' => array(
        0 => array(
          'value' => '{}',
        ),
      ),
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_isearch_config',
      'label' => 'Configuration',
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
          'maxlength_js' => '',
          'maxlength_js_enforce' => 0,
          'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
          'maxlength_js_truncate_html' => 0,
          'rows' => 5,
        ),
        'type' => 'text_textarea',
        'weight' => -2,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Configuration');

  return $fields;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function asu_isearch_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format isearch_html'.
  $permissions['use text format isearch_html'] = array(
    'name' => 'use text format isearch_html',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
