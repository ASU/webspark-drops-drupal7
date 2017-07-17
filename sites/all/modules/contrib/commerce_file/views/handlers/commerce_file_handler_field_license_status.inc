<?php

/**
 * @file
 * Field handler for a license status.
 */

/**
 * Field handler to translate a license status into its readable form.
 */
class commerce_file_handler_field_license_status extends commerce_file_handler_field_license {
  function render($values) {
    $name = $this->get_value($values);
    $title = commerce_file_license_status_get_title($name);

    // Only attempt to render a valid license status.
    if (!empty($title) && !is_array($title)) {
      return $this->render_link($this->sanitize_value($title), $values);
    }
  }
}
