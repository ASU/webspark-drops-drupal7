<?php

/**
 * @file
 * Field handler for a license limit.
 */


/**
 * Field handler for license expiration.
 */
class commerce_file_handler_field_license_limit extends commerce_file_handler_field_license_property {
  function render($values) {
    $entity = $this->_get_entity($values);
    if (!empty($entity)) {
      $limits = $entity->limits;
      if (!empty($limits)) {
        if (!isset($limits[$this->real_field]) || $entity->check_limit_is_unlimited($limits[$this->real_field])) {
          $value = !empty($this->options['unlimited_text']) ? $this->options['unlimited_text'] : NULL;
        }
        else {
          $value = $limits[$this->real_field];
        }

        return $this->sanitize_value($value);
      }
    }
  }
}
