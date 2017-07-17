<?php

/**
 * @file
 * Implement an commerce_file field, based on the file module's file field.
 */

// -----------------------------------------------------------------------
// Constants

// field type name this module defines
define('COMMERCE_FILE_FIELD_TYPE', 'commerce_file');

// unlimited value - same as COMMERCE_FILE_LIMIT_UNLIMITED
define('COMMERCE_FILE_FIELD_UNLIMITED', 'UNLIMITED');

// inherited value - same as COMMERCE_FILE_LIMIT_INHERITED
define('COMMERCE_FILE_FIELD_INHERIT', -1);

// -----------------------------------------------------------------------

/**
 * Implements hook_field_info().
 */
function commerce_file_field_info() {
  // build base field info
  $base = array(
    'label' => t('Commerce File'),
    'description' => t('This field stores the ID of a licensed file as an integer value.'),
    'settings' => array(
      'uri_scheme' => _commerce_file_default_system_scheme(),
    ),
    'instance_settings' => array(
      'file_extensions' => 'mp4 m4v flv wmv mp3 wav jpg jpeg png pdf doc docx ppt pptx xls xlsx',
      'file_directory' => '',
      'max_filesize' => '',
    ),
    'default_widget' => 'commerce_file_generic',
    'default_formatter' => 'commerce_file_access_link',
    'property_type' => 'commerce_file',
    'property_callbacks' => array('commerce_file_field_property_info_callback'),
  );

  // set license settings default to unlimited
  $license_info = _commerce_file_collate_license_info();
  $instance_defaults = array();
  foreach ($license_info as $k => $info) {
    $instance_defaults[$k] = isset($info['property info']['default']) ? $info['property info']['default'] : COMMERCE_FILE_FIELD_UNLIMITED;
  }
  $base['instance_settings'] += array('data' => $instance_defaults);

  return array(
    COMMERCE_FILE_FIELD_TYPE => array_merge_recursive($base + array(
      'label' => t('Commerce File'),
      'description' => t('This field stores the ID of a licensed file as an integer value.'),
    )),
  );
}

/**
 * Implements hook_field_formatter_info_alter().
 * - Add field type to other supported formatters
 */
function commerce_file_field_formatter_info_alter(&$info) {
  foreach ($info as $formatter_type => &$formatter_info) {
    if (empty($formatter_info['field types'])) {
      continue;
    }

    // Add to all file formatters
    if (in_array('file', $formatter_info['field types']) && !in_array(COMMERCE_FILE_FIELD_TYPE, $formatter_info['field types'])) {
      $formatter_info['field types'][] = COMMERCE_FILE_FIELD_TYPE;
    }
  }
  unset($formatter_info);
}

/**
 * Implements hook_filefield_paths_field_type_info() on behalf of image.module.
 */
function commerce_file_filefield_paths_field_type_info() {
  return array(COMMERCE_FILE_FIELD_TYPE);
}

/**
 * Implements hook_field_settings_form().
 */
function commerce_file_field_settings_form($field, $instance, $has_data) {
  $form = array();
  $defaults = field_info_field_settings($field['type']);
  $settings = array_merge($defaults, $field['settings']);

  $scheme_options = _commerce_file_get_private_stream_wrappers_options();
  if (!empty($scheme_options)) {
    $form['uri_scheme'] = array(
      '#type' => 'radios',
      '#title' => t('Private upload destination'),
      '#options' => $scheme_options,
      '#default_value' => $settings['uri_scheme'],
      '#disabled' => $has_data,
    );
  }
  else {
    drupal_set_message(t('Commerce File requires a private file scheme. Visit <a href="!url">admin/config/media/file-system</a> to set your private file path. Optionally, a private scheme other than Drupal\'s may be implemented.', array('!url' => url('admin/config/media/file-system'))), 'error');
  }

  return $form;
}

/**
 * Implements hook_field_instance_settings_form().
 */
function commerce_file_field_instance_settings_form($field, $instance) {
  $settings = $instance['settings'];

  // Use the file field instance settings form as a basis.
  $form = file_field_instance_settings_form($field, $instance);

  // build form
  _commerce_file_field_add_license_elements($form, 'instance', $settings);

  // Remove the description option.
  unset($form['description_field']);

  return $form;
}

/**
 * Implements hook_field_load().
 */
function commerce_file_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  file_field_load($entity_type, $entities, $field, $instances, $langcode, $items, $age);

  foreach ($entities as $id => $entity) {
    foreach ($items[$id] as $delta => $item) {
      if (isset($item) && !empty($item['fid'])) {
        // Unserialize the data array if necessary.
        if (empty($item['data'])) {
          $items[$id][$delta]['data'] = array();
        }
        elseif (!is_array($item['data'])) {
          $items[$id][$delta]['data'] = unserialize($item['data']);
        }
      }
    }
  }
}

/**
 * Implements hook_field_storage_pre_insert().
 */
function commerce_file_field_storage_pre_insert($entity_type, $entity) {
  _commerce_file_field_serialize_data($entity_type, $entity);
}

/**
 * Implements hook_field_storage_pre_update().
 */
function commerce_file_field_storage_pre_update($entity_type, $entity) {
  _commerce_file_field_serialize_data($entity_type, $entity);
}

/**
 * Implements hook_field_attach_insert().
 *
 * This hook is used to unserialize the commerce_file field's data array after it has
 * been inserted, because the data array is serialized before it is saved and
 * must be unserialized for compatibility with API requests performed during the
 * same request after the insert occurs.
 */
function commerce_file_field_attach_insert($entity_type, $entity) {
  _commerce_file_field_unserialize_data($entity_type, $entity);
}

/**
 * Implements hook_field_attach_update().
 *
 * This hook is used to unserialize the commerce_file field's data array after it has
 * been updated, because the data array is serialized before it is saved and
 * must be unserialized for compatibility with API requests performed during the
 * same request after the update occurs.
 */
function commerce_file_field_attach_update($entity_type, $entity) {
  _commerce_file_field_unserialize_data($entity_type, $entity);
}

/**
 * Converts commerce_file field data to a serialized array.
 *
 * @param $entity_type
 *   The entity type variable passed through hook_field_storage_pre_*().
 * @param $entity
 *   The entity variable passed through hook_field_storage_pre_*().
 */
function _commerce_file_field_serialize_data($entity_type, $entity) {
  // Loop over all the commerce_file fields attached to this entity.
  foreach (_commerce_file_get_commerce_file_fields($entity_type, $entity) as $field_name) {
    // Iterate over the items arrays for each language.
    foreach (array_keys($entity->{$field_name}) as $langcode) {
      $items = isset($entity->{$field_name}[$langcode]) ? $entity->{$field_name}[$langcode] : array();

      // Serialize data arrays before saving.
      foreach ($items as $delta => $item) {
        // Serialize an existing data array.
        if (!empty($item['data']) && is_array($item['data'])) {
          $entity->{$field_name}[$langcode][$delta]['data'] = serialize($item['data']);
        }
      }
     }
   }
}

/**
 * Converts saved commerce_file field data columns back to arrays for use in the rest of
 * the current page request execution.
 *
 * @param $entity_type
 *   The entity type variable passed through hook_field_attach_*().
 * @param $entity
 *   The entity variable passed through hook_field_attach_*().
 */
function _commerce_file_field_unserialize_data($entity_type, $entity) {
  // Loop over all the commerce_file fields attached to this entity.
  foreach (_commerce_file_get_commerce_file_fields($entity_type, $entity) as $field_name) {
    // Iterate over the items arrays for each language.
    foreach (array_keys($entity->{$field_name}) as $langcode) {
      $items = isset($entity->{$field_name}[$langcode]) ? $entity->{$field_name}[$langcode] : array();

      // For each item in the array, unserialize or initialize its data array.
      foreach ($items as $delta => $item) {
        // If we have a non-array $item['data'], unserialize it.
        if (!empty($item['data']) && !is_array($item['data'])) {
          $entity->{$field_name}[$langcode][$delta]['data'] = unserialize($item['data']);
        }
        // If we have no data element (or an existing empty), create an empty
        // array.
        elseif (empty($item['data'])) {
          $entity->{$field_name}[$langcode][$delta]['data'] = array();
        }
      }
    }
  }
}

/**
 * Returns an array of commerce_file field names from a specific entity.
 *
 * @param $entity_type
 *   The entity type variable passed through hook_field_storage_pre_*() or
 *   hook_field_attach_*().
 * @param $entity
 *   The entity variable passed through hook_field_storage_pre_*() or
 *   hook_field_attach_*().
 *
 * @return array
 *   An array of commerce_file field names or an empty array if none are found.
 */
function _commerce_file_get_commerce_file_fields($entity_type, $entity) {
  $commerce_file_fields = array();

  // Determine the list of instances to iterate on.
  list(, , $bundle) = entity_extract_ids($entity_type, $entity);
  $instances = field_info_instances($entity_type, $bundle);
  $fields = field_info_fields();

  // Iterate through the instances and collect results.
  foreach ($instances as $instance) {
    $field_name = $instance['field_name'];

    // If the instance is a commerce_file field with data...
    if ($fields[$field_name]['type'] == COMMERCE_FILE_FIELD_TYPE && isset($entity->{$field_name})) {
      $commerce_file_fields[] = $field_name;
    }
  }

  return $commerce_file_fields;
}

/**
 * Implements hook_field_presave().
 */
function commerce_file_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  file_field_presave($entity_type, $entity, $field, $instance, $langcode, $items);

  foreach ($items as $delta => $item) {
    // Serialize an existing data array.
    if (isset($item['data']) && is_array($item['data'])) {
      $items[$delta]['data'] = serialize($item['data']);
    }
  }
}

/**
 * Implements hook_field_insert().
 */
function commerce_file_field_insert($entity_type, $entity, $field, $instance, $langcode, &$items) {
  file_field_insert($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_field_update().
 */
function commerce_file_field_update($entity_type, $entity, $field, $instance, $langcode, &$items) {
  file_field_update($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_field_delete().
 */
function commerce_file_field_delete($entity_type, $entity, $field, $instance, $langcode, &$items) {
  file_field_delete($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_field_delete_revision().
 */
function commerce_file_field_delete_revision($entity_type, $entity, $field, $instance, $langcode, &$items) {
  file_field_delete_revision($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_field_is_empty().
 */
function commerce_file_field_is_empty($item, $field) {
  return file_field_is_empty($item, $field);
}

/**
 * Implements hook_field_widget_info().
 */
function commerce_file_field_widget_info() {
  $base = array(
    'field types' => array('commerce_file'),
    'settings' => array(
      'progress_indicator' => 'throbber',
    ),
    'behaviors' => array(
      'multiple values' => FIELD_BEHAVIOR_CUSTOM,
      'default value' => FIELD_BEHAVIOR_NONE,
    ),
  );

  // set license settings default to inherited
  $license_info = _commerce_file_collate_license_info();
  $base['settings'] += array('data' => array_fill_keys(array_keys($license_info), COMMERCE_FILE_FIELD_INHERIT));

  // return widgets
  return  array(
    'commerce_file_generic' => array_merge_recursive($base, array(
      'label' => t('Commerce File'),
    )),
  );
}

/**
 * Implements hook_filefield_sources_widgets().
 *
 * This returns a list of widgets that are compatible with FileField Sources.
 */
function commerce_file_filefield_sources_widgets() {
  // Add any widgets that your module supports here.
  return array('commerce_file_generic');
}

/**
 * Implements hook_field_widget_settings_form().
 */
function commerce_file_field_widget_settings_form($field, $instance) {
  $widget = $instance['widget'];
  $settings = $widget['settings'];

  // Use the file widget settings form.
  $form = file_field_widget_settings_form($field, $instance);

  return $form;
}

/**
 * Implements hook_field_widget_form().
 */
function commerce_file_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  // Add display_field setting to field because file_field_widget_form() assumes it is set.
  $field['settings']['display_field'] = 0;

  // ensure uri scheme on license file field if no items
  $controlled_field_names = _commerce_file_get_field_names();
  if (empty($items) && empty($field['settings']['uri_scheme']) && $instance['field_name'] == $controlled_field_names['license_file']) {
    $available_scheme_options = _commerce_file_get_private_stream_wrappers_options();

    // set uri_scheme to first available
    $field['settings']['uri_scheme'] = key($available_scheme_options);
  }

  // build elements with file_field
  $elements = file_field_widget_form($form, $form_state, $field, $instance, $langcode, $items, $delta, $element);

  // add properties to each element for widget process
  foreach (element_children($elements) as $delta) {
    $elements[$delta]['#entity_type'] = $instance['entity_type'];
    $elements[$delta]['#value_callback'] = '_commerce_file_field_widget_value';
    $elements[$delta]['#process'][] = '_commerce_file_field_widget_process';

    if ($instance['entity_type'] == COMMERCE_FILE_LICENSE_ENTITY_NAME) {
      $elements[$delta]['#inheritable'] = FALSE;
    }

    // add license limit settings
    $element_settings = isset($elements[$delta]['#default_value']) ? $elements[$delta]['#default_value'] : array();
    _commerce_file_field_add_license_elements($elements[$delta], 'widget', $element_settings, $instance['settings']);
  }

  return $elements;
}

/**
 * An element #process callback for the commerce_file_commerce_file field type.
 * - add file widget styles
 * - determine if there is a default file scheme available
 */
function _commerce_file_field_widget_process($element, &$form_state, $form) {
  $item = $element['#value'];
  $item['fid'] = $element['fid']['#value'];
  $field = field_widget_field($element, $form_state);
  $instance = field_widget_instance($element, $form_state);

  // add styles for file widget
  $element['#theme'] = 'file_widget';
  $element['#attached']['css'][] = drupal_get_path('module', 'commerce_file') . '/css/commerce_file.forms.css';

  if (isset($element['#attributes']['class'])) {
    $element['#attributes']['class'] = array_merge($element['#attributes']['class'], array('file-commerce-file'));
  }
  else {
    $element['#attributes']['class'] = array('file-commerce-file');
  }

  // only check scheme if not any field generated on install
  if (!in_array($instance['field_name'], _commerce_file_get_field_names())) {
    // get scheme options
    $available_scheme_options = _commerce_file_get_private_stream_wrappers_options();
    $scheme_options = _commerce_file_get_private_stream_wrappers_options(array($field['settings']['uri_scheme']));

    // Warn if there is no scheme selected for this field
    $default_scheme = NULL;
    if (empty($item['fid']) && empty($scheme_options)) {
      $element['#disabled'] = TRUE;
      $error_msg = t('You cannot upload a file. Commerce File requires a private file scheme. Visit <a href="!url">admin/config/media/file-system</a> to set your private file path. Optionally, a private scheme other than Drupal\'s may be implemented.', array('!url' => url('admin/config/media/file-system')));
      if (!empty($available_scheme_options)) {
        $error_msg .= t('<br />There are private file schemes available on your system. Visit the field settings to select a private scheme allowed for this field.');
      }

      form_error($element, $error_msg);
    }
  }

  return $element;
}

/**
 * The #value_callback for the commerce_file_generic field element.
 */
function _commerce_file_field_widget_value($element, $input = FALSE, $form_state) {
  // call file field's value callback to perform managed_file operations
  return file_field_widget_value($element, $input, $form_state);
}


// -----------------------------------------------------------------------
// Form element functions

/**
 * License settings element generator
 */
function _commerce_file_field_add_license_elements(&$parent, $level = 'field', $settings = array(), $inherited_settings = array()) {
  $base = array();
  $defaults = array();
  $license_info = _commerce_file_collate_license_info();

  // allow parent element to suggest inheritable
  $parent_inheritable = isset($parent['#inheritable']) ? $parent['#inheritable'] : TRUE;
  $have_inherited_settings = !empty($inherited_settings);

  switch ($level) {
    case 'widget':
      $defaults = field_info_instance_settings(COMMERCE_FILE_FIELD_TYPE);
      break;
    case 'instance':
      $defaults = field_info_instance_settings(COMMERCE_FILE_FIELD_TYPE);
      break;
    default:
      $defaults = field_info_field_settings(COMMERCE_FILE_FIELD_TYPE);
      break;
  }

  // Initialize license base elements
  foreach ($license_info as $k => &$info) {
    // initialize base element if not defined
    if (!isset($info['base_element'])) {
      $info['base_element'] = array();
    }

    // set base element #inheritable property
    if ($have_inherited_settings) {
      // allow setting definition to override if explicitly set to NOT inherit
      // else set to parent's inheritable
      if (!isset($info['property info']['inheritable']) || $info['property info']['inheritable']) {
        $info['base_element']['#inheritable'] = $parent_inheritable;
      }
    }
    else {
      // force to not inheritable if not inherited settings given
      $info['base_element']['#inheritable'] = FALSE;
    }
  }
  unset($info);

  // build inherited settings for license settings
  $inherited = array('descriptions' => array(), 'values' => array());
  if ($have_inherited_settings) {
    $inherited_tokens = array();

    // alter license info array
    foreach ($license_info as $k => &$info) {
      // skip if non-inheritable
      if (empty($info['base_element']['#inheritable'])) {
        continue;
      }

      // retrieve inherited value
      $inherited['values'][$k] = $inherited_value_k = _commerce_file_license_resolve_setting_value(NULL, $inherited_settings['data'][$k]);
      if (!isset($inherited_value_k)) {
        continue;
      }

      // if no setting value then set to inherit by default
      if (!isset($settings['data'][$k])) {
        $settings['data'][$k] = COMMERCE_FILE_FIELD_INHERIT;
      }
    }
    unset($info);
  }
  else {
    $inherited_settings = array();
  }

  // merge all defaults
  $values = array_merge($defaults, $inherited_settings, $settings);

  // build form elements
  $elements = array();
  foreach ($license_info as $k => $info) {
    if (!isset($values['data'][$k])) {
      continue;
    }

    // set default value to inherited value if defined
    $default_value = $values['data'][$k];
    $inherited_value = isset($inherited['values'][$k]) ? $inherited['values'][$k] : NULL;

    // initialize element with default value, inherited value, and base element
    $elements[$k] = array(
      '#default_value' => $default_value,
      '#limit_inherited_value' => $inherited_value,
    ) + $info['base_element'];
  }

  // update parent with settings elements
  if (!empty($elements)) {
    $element_container = array(
      '#type' => 'fieldset',
      '#title' => t('Access Limits'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 150,
      '#attributes' => array('class' => array('clearfix')),
      '#access' => !empty($elements),
    );

    // merge settings into parent element
    $parent = array_merge($parent, array('data' => ($element_container + $elements)));
  }
}


/**
 * Resolves license settings values with inheritance of instance settings
 */
function _commerce_file_license_resolve_setting_value($value, $inherited_value) {
  if (!isset($value) || _commerce_file_field_setting_is_inherited($value)) {
    // check if inherited value is set to unlimited - blank textfields are unlimited
    if (!empty($inherited_value) || $inherited_value === '0') {
      return $inherited_value;
    }

    // default to unlimited
    return COMMERCE_FILE_FIELD_UNLIMITED;
  }

  return $value;
}

/**
 * Check if field limit setting value is set to Unlimited
 */
function _commerce_file_field_setting_is_unlimited($value) {
  return strcmp($value, COMMERCE_FILE_FIELD_UNLIMITED) === 0;
}

/**
 * Check if field limit setting value is set to Unlimited
 */
function _commerce_file_field_setting_is_inherited($value) {
  return strcmp($value, COMMERCE_FILE_FIELD_INHERIT) === 0;
}


// -----------------------------------------------------------------------
// Field property info

/**
 * Callback to alter the property info of price fields.
 *
 * @see commerce_file_field_info().
 */
function commerce_file_field_property_info_callback(&$info, $entity_type, $field, $instance, $field_type) {
  $name = $field['field_name'];
  $property = &$info[$entity_type]['bundles'][$instance['bundle']]['properties'][$name];

  $property['type'] = ($field['cardinality'] != 1) ? 'list<commerce_file>' : 'commerce_file';
  $property['getter callback'] = 'entity_metadata_field_verbatim_get';
  $property['setter callback'] = 'entity_metadata_field_verbatim_set';
  $property['validation callback'] = 'commerce_file_field_entity_metadata_validate_item';

  $property['auto creation'] = 'commerce_file_field_data_auto_creation';

  $property['property info'] = commerce_file_field_data_property_info($name);

  unset($property['query callback']);
}

/**
 * Returns the default array structure for a field for use when creating
 *   new data arrays through an entity metadata wrapper.
 */
function commerce_file_field_data_auto_creation() {
  return array('fid' => NULL, 'data' => array());
}

/**
 * Callback for validating commerce_file field $items.
 *
 * - Requires 'fid' to be a valid file
 * - Allows 'data' to be optional
 *
 * @see entity_metadata_field_file_validate_item()
 */
function commerce_file_field_entity_metadata_validate_item($items, $context) {
  // Allow NULL values.
  if (!isset($items)) {
    return TRUE;
  }

  // Stream-line $items for multiple vs non-multiple fields.
  $items = !entity_property_list_extract_type($context['type']) ? array($items) : (array) $items;

  foreach ($items as $item) {
    // File-field items require a valid file.
    if (!isset($item['fid']) || !file_load($item['fid'])) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
 * Defines info for the properties of the Price field data structure.
 */
function commerce_file_field_data_property_info($name = NULL) {
  return array(
    'file' => array(
      'label' => t('File'),
      'description' => !empty($name) ? t('The file of field %name', array('%name' => $name)) : '',
      'type' => 'file',
      'getter callback' => 'entity_metadata_field_file_get',
      'setter callback' => 'entity_metadata_field_file_set',
      'required' => TRUE,
    ),
    'data' => array(
      'label' => t('Data'),
      'description' => !empty($name) ? t('License data array of field %name', array('%name' => $name)) : '',
      'type' => 'struct',
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'property info' => _commerce_file_license_data_property_info(),
    ),
  );
}



// -----------------------------------------------------------------------
// Field item operations

/**
 * Resolve all settings for a given field item
 */
function _commerce_file_license_resolve_settings($field_item, $instance) {
  if (empty($field_item['data']) || empty($instance['settings']['data'])) {
    return $field_item;
  }

  // get license setting info
  $license_info = _commerce_file_collate_license_info();

  // resolve only settings defined in license info
  foreach ($field_item['data'] as $setting_key => &$setting_value) {
    if (isset($license_info[$setting_key]) && isset($instance['settings']['data'][$setting_key])) {
      $setting_value = _commerce_file_license_resolve_setting_value($setting_value, $instance['settings']['data'][$setting_key]);
    }
  }
  unset($setting_value);

  return $field_item;
}

/**
 * Aggregate one or more field items' settings into the first field item
 *  - assumes all settings have been resolved for all items
 */
function _commerce_file_field_aggregate_field_items($field_item1/*, $field_item2, ... */) {
  $args = func_get_args();
  $trunk = array_shift($args);

  if (empty($args)) {
    return $trunk;
  }

  foreach ($args as $field_item) {
    if (!isset($field_item['data'])) {
      continue;
    }

    if (!isset($trunk['data'])) {
      $trunk['data'] = $field_item['data'];
    }
    else {
      $trunk['data'] = _commerce_file_license_property_merge($trunk['data'], $field_item['data']);
    }
  }

  return $trunk;
}


// -----------------------------------------------------------------------
// Entity field items

/**
 * Return all commerce_file fields for a given entity, indexed by fid
 */
function _commerce_file_field_aggregate_files($entity, $entity_type = NULL) {
  $aggregated = array();
  $field_type = COMMERCE_FILE_FIELD_TYPE;

  if (empty($entity_type)) {
    $entity_type = _commerce_file_get_entity_type($entity);
    if (empty($entity_type)) {
      return $aggregated;
    }
  }

  // get some entity info
  $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);
  $entity_id = $entity_wrapper->getIdentifier();
  $entity_bundle = $entity_wrapper->getBundle();

  // get field instances for type and bundle
  $instances = _commerce_file_field_info_instances($entity_type, $entity_bundle, $field_type);
  if (empty($instances)) {
    return $aggregated;
  }

  $file_items = array();
  foreach ($instances as $field_name => $instance) {
    $items = $entity_wrapper->{$field_name}->value();
    if (empty($items)) {
      continue;
    }

    // make an array for single value
    if (isset($items['fid'])) {
      $items = array($items);
    }

    // index items on fid
    foreach ($items as $item) {
      if (isset($item['fid'])) {
        $file_items[$item['fid']][] = _commerce_file_license_resolve_settings($item, $instance);
      }
    }
  }

  // aggregate per file
  foreach ($file_items as $fid => $items) {
    $aggregated[$fid] = call_user_func_array('_commerce_file_field_aggregate_field_items', $items);
  }

  return $aggregated;
}

/**
 * Return all commerce_file field type instances
 */
function _commerce_file_field_info_instances($entity_type, $entity_bundle, $field_type = COMMERCE_FILE_FIELD_TYPE) {
  $cache = &drupal_static(__FUNCTION__);

  $field_type = !empty($field_type) ? $field_type : COMMERCE_FILE_FIELD_TYPE;
  $cid = "{$entity_type}::{$entity_bundle}::{$field_type}";

  if (!isset($cache[$cid])) {
    $cache[$cid] = array();

    // find all fields instances
    $instances = field_info_instances($entity_type, $entity_bundle);
    if (!empty($instances)) {
      // find all instances for field type
      foreach ($instances as $field_name => $instance) {
        $field_info = field_info_field($field_name);
        if ($field_info['type'] == $field_type) {
           $cache[$cid][$field_name] = $instance;
        }
      }
    }
  }

  return $cache[$cid];
}
