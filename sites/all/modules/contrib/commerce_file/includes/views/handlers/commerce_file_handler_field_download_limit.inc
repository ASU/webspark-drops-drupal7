<?php

/**
 * @file
 * Contains commerce_file_handler_field_download_limit.
 */

/**
 * Displays the download limit for a file
 */
class commerce_file_handler_field_download_limit extends views_handler_field {

  public function query() {}

  /**
   * Hide the column if downloads are not limited.
   */
  public function access() {
    return variable_get('commerce_file_enable_download_limit', FALSE);
  }

  function pre_render(&$values) {
    $data = array();
    // Note: this assumes the view has license_id and commerce_file fields.
    foreach ($values as $index => $value) {
      if (isset($value->license_id) && isset($value->field_commerce_file)) {
        $data[$value->license_id][$index] = $value->field_commerce_file[0]['raw']['fid'];
      }
    }
    // No data found, stop here.
    if (empty($data)) {
      return;
    }

    $license_ids = array_keys($data);
    $licenses = entity_load('commerce_license', $license_ids);
    // Get the counts and add them to $values for render() to use.
    foreach ($data as $license_id => $fids) {
      $license = $licenses[$license_id];
      $counts = commerce_file_download_log_get_counts($license, $fids);
      foreach ($fids as $index => $fid) {
        $values[$index]->commerce_file_download_count = $counts[$fid];
      }
    }
  }

  function render($values) {
    if (isset($values->commerce_file_download_count)) {
      $download_limit = variable_get('commerce_file_download_limit', 100);
      return $values->commerce_file_download_count . ' / ' . $download_limit;
    }
  }

}
