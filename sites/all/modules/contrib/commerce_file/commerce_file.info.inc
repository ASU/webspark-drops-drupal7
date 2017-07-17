<?php

/**
 * @file
 * Provides metadata for the commerce file license entity.
 */

/**
 * Implements hook_entity_property_info_alter()
 *  - entity module already adds fields from database schema
 */
function commerce_file_entity_property_info_alter(&$info) {
  // License Entity ------------------------------------------------//
  $properties = &$info['commerce_file_license']['properties'];

  // Add setters for db fields
  $table_setters = _commerce_file_entity_property_info_table_setters();
  foreach ($table_setters['commerce_file_license'] as $table_field => $table_setter) {
    if (isset($properties[$table_field])) {
      $properties[$table_field] += $table_setter;
    }
  }

  // Set database properties required for creation
  $properties['type']['required'] = TRUE;
  $properties['status']['required'] = TRUE;

  // Alter existing database fields
  $properties['status']['options list'] = 'commerce_file_license_status_options_list';
  $properties['uid']['clear'] = array('owner');

  // Add non-database fields
  $properties['state'] = array(
    'label' => t('State'),
    'description' => t('The state of the license derived from its status.'),
    'type' => 'token',
    'getter callback' => 'commerce_file_license_property_getter',
    'options list' => 'commerce_file_license_state_options_list',
    'computed' => TRUE,
  );
  $properties['owner'] = array(
    'label' => t("Owner"),
    'type' => 'user',
    'description' => t("The owner of the license."),
    'getter callback' => 'commerce_file_license_property_getter',
    'setter callback' => 'commerce_file_license_property_setter',
    'setter permission' => COMMERCE_FILE_ADMIN_PERM,
    'clear' => array('uid'),
    'required' => TRUE,
    'computed' => TRUE,
  );
  $properties['limits'] = array(
    'label' => t("License limits"),
    'type' => 'struct',
    'description' => t("A list of associated license limits."),
    'getter callback' => 'entity_property_verbatim_get',
    'property info' => _commerce_file_license_data_property_info(),
    'computed' => TRUE,
  );
  $properties['data_unlimited_value'] = array(
    'label' => t("License limit unlimited value"),
    'type' => 'integer',
    'description' => t("The unlimited value for a limit. Use this to determine if a limit has been set to unlimited."),
    'getter callback' => 'commerce_file_license_property_getter',
    'computed' => TRUE,
  );

  $properties['request_time'] = array(
    'label' => t("REQUEST TIME"),
    'type' => 'integer',
    'description' => t("The current request timestamp."),
    'getter callback' => 'commerce_file_license_property_getter',
    'computed' => TRUE,
  );
  $properties['expiration'] = array(
    'label' => t("Expiration"),
    'type' => 'integer',
    'description' => t("The expiration timestamp."),
    'getter callback' => 'commerce_file_license_property_getter',
    'computed' => TRUE,
  );
  $properties['time_remaining'] = array(
    'label' => t("Time left"),
    'type' => 'integer',
    'description' => t("The time until expiration."),
    'getter callback' => 'commerce_file_license_property_getter',
    'computed' => TRUE,
  );
  $properties['logs'] = array(
    'label' => t("Access logs"),
    'type' => 'list<commerce_file_license_log>',
    'description' => t("A list of access logs for this license."),
    'getter callback' => 'commerce_file_license_property_getter',
    'computed' => TRUE,
  );
  $properties['download_count'] = array(
    'label' => t("Download count"),
    'type' => 'integer',
    'description' => t("The current number of downloads for this license."),
    'getter callback' => 'commerce_file_license_property_getter',
    'computed' => TRUE,
  );
  $properties['address_count'] = array(
    'label' => t("Address count"),
    'type' => 'integer',
    'description' => t("The current number of different IP addresses that have been used to access this license."),
    'getter callback' => 'commerce_file_license_property_getter',
    'computed' => TRUE,
  );
  $properties['addresses'] = array(
    'label' => t("Owner's Addresses"),
    'type' => 'list<text>',
    'description' => t("A list of unique IP addresses that have been used to access this license."),
    'getter callback' => 'commerce_file_license_property_getter',
    'computed' => TRUE,
  );

  // Transfer bundle properties to entity base properties
  if (isset($info['commerce_file_license']['bundles'])) {
    $bundle_properties = array();
    foreach ($info['commerce_file_license']['bundles'] as $bundle => $bundle_info) {
      $bundle_info += array('properties' => array());
      $bundle_properties += $bundle_info['properties'];
    }

    // Move the file field properties to the license by default; as they are
    // required default fields, this makes dealing with them more convenient.
    $file_field_name = _commerce_file_get_field_names('license_file');
    if (isset($bundle_properties[$file_field_name])) {
      $properties[$file_field_name] = $bundle_properties[$file_field_name];
    }
  }


  // License Log Entity ------------------------------------------------//
  $log_properties = &$info['commerce_file_license_log']['properties'];

  $log_properties['license'] = array(
    'label' => t("File License"),
    'type' => 'commerce_file_license',
    'description' => t("The license related to the log."),
    'getter callback' => 'commerce_file_license_property_getter',
    'computed' => TRUE,
  );


  // Line Item ----------------------------------------------------------//
  if (isset($info['commerce_line_item']) && isset($info['commerce_line_item']['bundles'])) {
    // Move the line item field properties to the line item by default;
    // this makes dealing with them more convenient.
    $line_properties = array();

    foreach ($info['commerce_line_item']['bundles'] as $bundle => $bundle_info) {
      $bundle_info += array('properties' => array());
      $line_properties += $bundle_info['properties'];
    }

    $field_name = _commerce_file_get_field_names('line_item_files');
    if (isset($line_properties[$field_name])) {
      $info['commerce_line_item']['properties'][$field_name] = $line_properties[$field_name];
    }
  }
}

/**
 * Returns an array of database fields that can be set
 */
function _commerce_file_entity_property_info_table_setters() {
  return array(
    'commerce_file_license' => array(
      'type' => array(
        'setter callback' => 'entity_property_verbatim_set',
      ),
      'status' => array(
        'setter callback' => 'entity_property_verbatim_set',
        'setter permission' => COMMERCE_FILE_ADMIN_PERM,
      ),
      'created' => array(
        'setter callback' => 'entity_property_verbatim_set',
        'setter permission' => COMMERCE_FILE_ADMIN_PERM,
      ),
      'changed' => array(
        'setter callback' => 'entity_property_verbatim_set',
        'setter permission' => COMMERCE_FILE_ADMIN_PERM,
      ),
      'granted' => array(
        'setter callback' => 'entity_property_verbatim_set',
        'setter permission' => COMMERCE_FILE_ADMIN_PERM,
      )
    ),
  );
}
