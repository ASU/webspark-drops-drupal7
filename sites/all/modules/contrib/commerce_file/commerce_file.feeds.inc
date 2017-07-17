<?php

/**
 * @file
 * Integration with the Feeds module.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 */
function commerce_file_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  $license_info = _commerce_file_collate_license_info();

  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if ($info['type'] != 'commerce_file') {
      continue;
    }

    // file import
    $targets[$name . ':file'] = array(
      'name' => check_plain($instance['label'] . ': File'),
      'callback' => 'commerce_file_set_file_target',
      'real_target' => $info['field_name'],
      'description' => t('The @label field file target.', array('@label' => $instance['label'])),
    );

    // license data info
    foreach ($license_info as $data_field => $data_info) {
      $name_label = $instance['label'] . ': Data: ' . drupal_ucfirst(str_replace('_', ' ', $data_field));
      $targets[$name . ':data:' . $data_field] = array(
        'name' => check_plain($name_label),
        'callback' => 'commerce_file_set_data_target',
        'real_target' => $info['field_name'],
        'description' => $data_info['property info']['description'],
      );
    }
  }
}


/**
 * File target callback for hook_feeds_processor_targets_alter().
 *
 * @param $source
 *   Field mapper source settings.
 * @param $entity
 *   An entity object, for instance a node object.
 * @param $target
 *   A string identifying the target on the entity.
 * @param $value
 *   The value to populate the target with.
 *
 * @see file_feeds_set_target()
 */
function commerce_file_set_file_target($source, $entity, $target, $value) {
  // extract field_name, sub_field should be 'file'
  list($target, $sub_field) = explode(':', $target, 2);

  if (empty($value)) {
    return;
  }
  module_load_include('inc', 'file', 'file.field');
  module_load_include('inc', 'commerce_file', 'includes/commerce_file.field');

  // Make sure $value is an array of objects of type FeedsEnclosure.
  if (!is_array($value)) {
    $value = array($value);
  }
  foreach ($value as $k => $v) {
    if (!($v instanceof FeedsEnclosure)) {
      if (is_string($v)) {
        $value[$k] = new FeedsEnclosure($v, 'application/octet-stream');
      }
      else {
        unset($value[$k]);
      }
    }
  }
  if (empty($value)) {
    return;
  }

  // Determine file destination.
  // @todo This needs review and debugging.
  $entity_type = $entity->feeds_item->entity_type;
  list($entity_id, $vid, $bundle_name) = entity_extract_ids($entity_type, $entity);
  $instance_info = field_info_instance($entity_type, $target, $bundle_name);
  $info = field_info_field($target);
  $singular = $info['cardinality'] == 1;

  // set default file owner to root user for security
  $file_owner_uid = 1;

  // set destination and owner uid to entity uid if not anonymous
  $token_data = array();
  if (!empty($entity->uid)) {
    $file_owner_uid = $entity->uid;
    $token_data[$entity_type] = $entity;
  }
  $destination = file_field_widget_uri($info, $instance_info, $token_data);

  // set default license data
  $data_default = array();

  // add license limits as inherited
  $license_info = _commerce_file_collate_license_info();
  if (!empty($license_info)) {
    if ($entity_type == COMMERCE_FILE_LICENSE_ENTITY_NAME) {
      // Licenses - default to instance settings, else unlimited
      $data_default_value = COMMERCE_FILE_FIELD_UNLIMITED;
      $data_default = array_fill_keys(array_keys($license_info), $data_default_value);

      // merge any other instance data
      if (!empty($instance_info['settings']['data'])) {
        $data_default = $instance_info['settings']['data'] + $data_default;
      }
    }
    else {
      // Always set non-licenses to inherit
      $data_default_value = COMMERCE_FILE_FIELD_INHERIT;
      $data_default = array_fill_keys(array_keys($license_info), $data_default_value);

      // merge any other instance data
      if (!empty($instance_info['settings']['data'])) {
        $data_default += $instance_info['settings']['data'];
      }
    }
  }



  // Populate entity.
  $i = 0;
  $field = isset($entity->$target) ? $entity->$target : array();
  $lang = LANGUAGE_NONE;
  foreach ($value as $v) {
    $file = $v->getFile($destination);
    if (empty($file) || empty($file->fid)) {
      continue;
    }

    // set file data and resave
    $save_file = FALSE;

    // set file owner
    if ($file->uid != $file_owner_uid) {
      $file->uid = $file_owner_uid;
      $save_file = TRUE;
    }

    // set proper mimetype
    $mimetype = file_get_mimetype($file->uri);
    if ($file->filemime != $mimetype) {
      $file->filemime = $mimetype;
      $save_file = TRUE;
    }

    // re-save file if anything changed
    if ($save_file) {
      file_save($file);
    }

    // ensure field array
    if (empty($field[$lang][$i])) {
      $field[$lang][$i] = array();
    }
    elseif(!is_array($field[$lang][$i])) {
      $field[$lang][$i] = array($field[$lang][$i]);
    }

    // merge file
    $field[$lang][$i] += (array)$file;

    // merge access limit defaults
    $field[$lang][$i] += array('data' => $data_default);

    // stop if only 1 item
    if ($singular) {
      break;
    }
    $i++;

  }
  $entity->{$target} = $field;
}

/**
 * Schema field target callback for hook_feeds_processor_targets_alter().
 *
 * @param $source
 *   Field mapper source settings.
 * @param $entity
 *   An entity object, for instance a node object.
 * @param $target
 *   A string identifying the target on the entity.
 * @param $value
 *   The value to populate the target with.
 */
function commerce_file_set_schema_target($source, $entity, $target, $value) {
  list($field_name, $sub_field) = explode(':', $target, 2);

  // Handle non-multiple value fields.
  if (!is_array($value)) {
    $value = array($value);
  }

  $field = isset($entity->$field_name) ? $entity->$field_name : array();
  $field_info = field_info_field($field_name);
  $singular = $field_info['cardinality'] == 1;

  $lang = LANGUAGE_NONE;
  foreach ($value as $i => $v) {
    $field[$lang][$i][$sub_field] = $v;

    if ($singular) {
      break;
    }
  }

  $entity->$field_name = $field;
}

/**
 * License data target callback for hook_feeds_processor_targets_alter().
 *
 * @param $source
 *   Field mapper source settings.
 * @param $entity
 *   An entity object, for instance a node object.
 * @param $target
 *   A string identifying the target on the entity.
 * @param $value
 *   The value to populate the target with.
 */
function commerce_file_set_data_target($source, $entity, $target, $value) {
  list($field_name, $field_data_name, $property_name) = explode(':', $target, 3);

  // Handle non-multiple value fields.
  if (!is_array($value)) {
    $value = array($value);
  }

  $field = isset($entity->$field_name) ? $entity->$field_name : array();
  $field_info = field_info_field($field_name);
  $singular = $field_info['cardinality'] == 1;

  $lang = LANGUAGE_NONE;
  foreach ($value as $i => $v) {
    $field[$lang][$i][$field_data_name][$property_name] = $v;

    if ($singular) {
      break;
    }
  }

  $entity->$field_name = $field;
}
