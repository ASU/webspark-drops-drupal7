<?php

/**
 * @file
 * Filter handler for a license status.
 */

/**
 * Filter by license status
 */
class commerce_file_handler_filter_license_status extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Status');
      $this->value_options = commerce_file_license_status_options_list();
    }
  }
}
