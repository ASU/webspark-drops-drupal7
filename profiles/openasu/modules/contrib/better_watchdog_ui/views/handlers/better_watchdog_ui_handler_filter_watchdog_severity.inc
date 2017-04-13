<?php
/**
 * @file
 * Definition of better_watchdog_ui_handler_filter_watchdog_severity.
 */


/**
 * Provides severity filter options for the watchdog entry.
 *
 * @ingroup views_filter_handlers
 */
class better_watchdog_ui_handler_filter_watchdog_severity extends views_handler_filter_in_operator {

  /**
   * Compute severity filter options.
   */
  public function get_value_options() {

    if (!isset($this->value_options)) {

      $options = array();
      foreach (watchdog_severity_levels() as $key => $value) {
        $options[$key] = $value;
      }

      $this->value_options = $options;
    }
  }
}
