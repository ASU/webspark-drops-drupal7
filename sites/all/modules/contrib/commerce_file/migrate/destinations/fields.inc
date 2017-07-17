<?php

/**
 * @file
 * Support for processing commerce file fields
 */

/**
 * Handle for commerce_file fields;
 */
class MigrateCommerceFileFieldHandler extends MigrateFileFieldBaseHandler {
  public function __construct() {
    $this->registerTypes(array('commerce_file'));
  }

  /**
   * Implementation of MigrateFieldHandler::fields().
   *
   * @param $type
   *  The file field type - 'file' or 'image'
   * @param $instance
   *  Instance info for the field.
   * @param Migration $migration
   *  The migration context for the parent field. We can look at the mappings
   *  and determine which subfields are relevant.
   * @return array
   */
  public function fields($type, $instance, $migration = NULL) {
    $fields = parent::fields($type, $instance, $migration);

    // remove file field sub fields
    unset($fields['description'], $fields['display']);

    // add limit data
    $data_fields = array();
    $license_info = _commerce_file_collate_license_info();
    foreach ($license_info as $data_key => $data_info) {
      $fields[$data_key] = t('Subfield: Access limit for @title', array(
        '@title' => isset($data_info['title']) ? $data_info['title'] : $data_key,
      ));
    }

    return $fields;
  }

  /**
   * Implementation of MigrateFieldHandler::prepare().
   *
   * Prepare file data for saving as a Field API file field.
   *
   * @return array
   *  Field API array suitable for inserting in the destination object.
   */
  public function prepare($entity, array $field_info, array $instance, array $values) {
    // store the instance info for use in buildFieldArray()
    $this->_field_instance = $instance;

    // call file field's prepare
    $return = parent::prepare($entity, $field_info, $instance, $values);

    return $return;
  }

  /**
   * Implementation of MigrateFileFieldBaseHandler::buildFieldArray().
   */
  protected function buildFieldArray($field_array, $arguments, $delta) {
    $field_instance = !empty($this->_field_instance) ? $this->_field_instance : array();

    $data_defaults = $this->_field_data_defaults($field_instance);
    foreach ($data_defaults as $data_key => $data_default) {
      if (isset($arguments[$data_key])) {
        if (is_array($arguments[$data_key])) {
          $field_array['data'][$data_key] = $arguments[$data_key][$delta];
        }
        else {
          $field_array['data'][$data_key] = $arguments[$data_key];
        }
      }

      if (!isset($field_array['data'][$data_key])) {
        $field_array['data'][$data_key] = $data_default;
      }
    }

    return $field_array;
  }

  /**
   * Returns the data array defaults for a Commerce File field
   *
   * @return array
   */
  private function _field_data_defaults(array $instance) {
    $defaults = array();

    // get license info
    $license_info = _commerce_file_collate_license_info();
    $entity_type = !empty($instance['entity_type']) ? $instance['entity_type'] : '';

    if (!empty($license_info)) {
      if ($entity_type == COMMERCE_FILE_LICENSE_ENTITY_NAME) {
        // Licenses - default to instance settings, else unlimited
        $data_default_value = COMMERCE_FILE_FIELD_UNLIMITED;
        $defaults = array_fill_keys(array_keys($license_info), $data_default_value);

        // merge any other instance data
        if (!empty($instance_info['settings']['data'])) {
          $defaults = $instance_info['settings']['data'] + $defaults;
        }
      }
      else {
        // Always set non-licenses to inherit
        $data_default_value = COMMERCE_FILE_FIELD_INHERIT;
        $defaults = array_fill_keys(array_keys($license_info), $data_default_value);

        // merge any other instance data
        if (!empty($instance_info['settings']['data'])) {
          $defaults += $instance_info['settings']['data'];
        }
      }
    }

    return $defaults;
  }
}
