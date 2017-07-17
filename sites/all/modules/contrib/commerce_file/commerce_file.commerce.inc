<?php

/**
 * @file
 * Implementations of Commerce Hooks
 */


/**
 * Implements hook_commerce_file_license_info().
 */
function commerce_file_commerce_file_license_info() {
  return array(
    'duration' => array(
      'name' => 'duration',
      'title' => t('Duration'),
      'base_element' => array(
        '#type' => 'commerce_file_limit_duration',
        '#title' => t('Access duration'),
      ),
      'property info' => array(
        'type' => 'duration',
        'label' => t('The license duration'),
        'description' => t('The amount time that this file is allowed to be downloaded.'),
        'default_value' => COMMERCE_FILE_FIELD_UNLIMITED,
      ),
      'callbacks' => array(
        'check_access' => '_commerce_file_license_property_duration_check_access',
        'current' => '_commerce_file_license_property_duration_current',
        'remaining' => '_commerce_file_license_property_duration_remaining',
      ),
    ),
    'download_limit' => array(
      'name' => 'download_limit',
      'title' => t('Download Limit'),
      'base_element' => array(
        '#type' => 'commerce_file_limit_integer',
        '#title' => t('# of Downloads'),
      ),
      'property info' => array(
        'type' => 'integer',
        'label' => t('The number of downloads allowed'),
        'description' => t('The number of downloads allowed for this file.'),
        'default_value' => 10,
      ),
      'callbacks' => array(
        'check_access' => '_commerce_file_license_property_downloads_check_access',
        'current' => '_commerce_file_license_property_downloads_current',
        'remaining' => '_commerce_file_license_property_downloads_remaining',
      ),
    ),
    'address_limit' => array(
      'name' => 'address_limit',
      'title' => t('IP Address Limit'),
      'base_element' => array(
        '#type' => 'commerce_file_limit_integer',
        '#title' => t('# of IP Addresses'),
      ),
      'property info' => array(
        'type' => 'integer',
        'label' => t('The number of IP addresses allowed'),
        'description' => t('The number of IP addresses allowed to be used by a single user to access this file.'),
        'default_value' => 2,
      ),
      'callbacks' => array(
        'check_access' => '_commerce_file_license_property_ip_check_access',
        'current' => '_commerce_file_license_property_ip_current',
        'remaining' => '_commerce_file_license_property_ip_remaining',
      ),
    ),
  );
}


// -----------------------------------------------------------------------
// License Duration limit handling

/**
 * Current Callback for License duration
 *
 * @param $license
 *   The Commerce File License entity
 *
 * @return
 *   The current value of the property
 */
function _commerce_file_license_property_duration_current($license) {
  if (!empty($license->granted)) {
    return REQUEST_TIME - $license->granted;
  }
}

/**
 * Remaining Callback for License duration
 *
 * @param $license
 *   The Commerce File License entity
 *
 * @return
 *   The current value of the property
 */
function _commerce_file_license_property_duration_remaining($license, $limit_value) {
  if (is_numeric($limit_value)) {
    $current = _commerce_file_license_property_duration_current($license);
    if (isset($current)) {
      return $limit_value - $current;
    }

    // default to full limit
    return $limit_value;
  }

  return 0;
}

/**
 * Check Callback for License duration
 *
 * @param $license
 *   The Commerce File License entity
 * @param $limit_value
 *   The value of the limit for this property
 *
 * @return
 *   TRUE access is allowed
 */
function _commerce_file_license_property_duration_check_access($license, $limit_value) {
  $current = _commerce_file_license_property_duration_current($license);

  if (isset($current) && is_numeric($limit_value)) {
    return $current < $limit_value;
  }

  return FALSE;
}


// -----------------------------------------------------------------------
// License Downloads limit handling

/**
 * Current Callback for License downloads
 */
function _commerce_file_license_property_downloads_current($license) {
  return count($license->logs);
}

/**
 * Remaining Callback for License downloads
 */
function _commerce_file_license_property_downloads_remaining($license, $limit_value) {
  if (is_numeric($limit_value)) {
    $current = _commerce_file_license_property_downloads_current($license);
    if (isset($current)) {
      return $limit_value - $current;
    }

    // default to full limit
    return $limit_value;
  }

  return 0;
}

/**
 * Check Callback for License downloads
 *
 * @return
 *   TRUE access is allowed
 */
function _commerce_file_license_property_downloads_check_access($license, $limit_value) {
  $current = _commerce_file_license_property_downloads_current($license);

  if (isset($current) && is_numeric($limit_value)) {
    return $current < $limit_value;
  }

  return FALSE;
}


// -----------------------------------------------------------------------
// License IP Addresses limit handling

/**
 * Current Callback for License IP Addresses
 */
function _commerce_file_license_property_ip_current($license) {
  return count($license->addresses);
}

/**
 * Remaining Callback for License IP Addresses
 */
function _commerce_file_license_property_ip_remaining($license, $limit_value) {
  if (is_numeric($limit_value)) {
    $current = _commerce_file_license_property_ip_current($license);
    if (isset($current)) {
      return $limit_value - $current;
    }

    // default to full limit
    return $limit_value;
  }

  return 0;
}

/**
 * Check Callback for License IP Addresses
 *
 * @return
 *   TRUE access is allowed
 */
function _commerce_file_license_property_ip_check_access($license, $limit_value) {
  $current = _commerce_file_license_property_ip_current($license);

  if (isset($current) && is_numeric($limit_value)) {
    $ip = ip_address();
    return $current < $limit_value || in_array($ip, $license->addresses);
  }

  return FALSE;
}
