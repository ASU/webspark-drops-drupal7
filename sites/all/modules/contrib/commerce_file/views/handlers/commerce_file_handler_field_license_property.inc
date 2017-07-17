<?php

/**
 * @file
 * Contains the license entity property field handler.
 */

/**
 * Field handler to provide access to non database entity properties.
 */
class commerce_file_handler_field_license_property extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['license_id'] = 'license_id';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['unlimited_text'] = array('default' => 'Unlimited', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['unlimited_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display for unlimited value'),
      '#default_value' => $this->options['unlimited_text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $entity = $this->_get_entity($values);
    if (!empty($entity)) {
      if (isset($entity->{$this->real_field})) {
        $value = $entity->{$this->real_field};
        if ($entity->check_limit_is_unlimited($value)) {
          // unlimited duration
          $value = !empty($this->options['unlimited_text']) ? $this->options['unlimited_text'] : NULL;
          return $this->sanitize_value($value);
        }

        // set value and render
        $values->{$this->field_alias} = $value;
        return parent::render($values);
      }
    }
  }

  function _get_entity($values) {
    $entity_id = $this->get_value($values, 'license_id');

    if (!empty($entity_id)) {
      return commerce_file_license_load($entity_id);
    }
  }
}
