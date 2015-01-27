<?php

/**
 * @file
 * Definition of better_watchdog_ui_handler_field_watchdog_severity.
 */


/**
 * Provides severity display options for the watchdog entry.
 *
 * @ingroup views_field_handlers
 */
class better_watchdog_ui_handler_field_watchdog_severity extends views_handler_field {

  /**
   * Render the field - convert numerical value to text.
   */
  public function render($values) {

    $severity_levels = watchdog_severity_levels();
    $value = $this->get_value($values);
    return $this->sanitize_value($severity_levels[$value]);
  }

}
