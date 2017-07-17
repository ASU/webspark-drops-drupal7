<?php

/**
 * @file
 * Field handler for a license duration.
 */


/**
 * Field handler for license duration.
 */
class commerce_file_handler_field_license_duration extends commerce_file_handler_field_license_property {
  function option_definition() {
    $options = parent::option_definition();

    $options['granularity'] = array('default' => 2);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['granularity'] = array(
      '#type' => 'textfield',
      '#title' => t('Granularity'),
      '#description' => t('How many different units to display in the string.'),
      '#default_value' => $this->options['granularity'],
    );
  }

  function render($values) {
    $entity = $this->_get_entity($values);
    if (!empty($entity)) {
      if (!isset($entity->{$this->real_field}) || $entity->check_limit_is_unlimited($entity->{$this->real_field})) {
        return !empty($this->options['unlimited_text']) ? $this->options['unlimited_text'] : NULL;
      }

      return format_interval($entity->{$this->real_field}, isset($this->options['granularity']) ? $this->options['granularity'] : 2);
    }
  }
}
