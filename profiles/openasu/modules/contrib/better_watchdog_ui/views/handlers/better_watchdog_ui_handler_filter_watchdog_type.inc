<?php
/**
 * @file
 * Definition of better_watchdog_ui_handler_filter_watchdog_type.
 */


/**
 * Provides type filter options for the watchdog entry.
 *
 * @ingroup views_filter_handlers
 */
class better_watchdog_ui_handler_filter_watchdog_type extends views_handler_filter_in_operator {

  /**
   * Compute type filter options.
   */
  public function get_value_options() {

    if (!isset($this->value_options)) {

      $options = array();
      foreach (_dblog_get_message_types() as $value) {
        $options[$value] = $value;
      }

      $this->value_options = $options;
    }
  }
}
