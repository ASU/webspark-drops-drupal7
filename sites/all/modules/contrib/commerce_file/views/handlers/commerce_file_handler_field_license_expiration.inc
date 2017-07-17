<?php

/**
 * @file
 * Field handler for a license expiration.
 */

/**
 * Field handler for license expiration.
 */
class commerce_file_handler_field_license_expiration extends views_handler_field_date {
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
      '#title' => t('Text to display for unlimited duration'),
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
      if (!isset($entity->{$this->real_field})) {
        // unlimited duration if no expiration is defined
        return !empty($this->options['unlimited_text']) ? $this->options['unlimited_text'] : NULL;
      }

      // set value and render as date
      $values->{$this->field_alias} = $entity->{$this->real_field};
      return parent::render($values);
    }
  }

  function _get_entity($values) {
    $entity_id = $this->get_value($values, 'license_id');

    if (!empty($entity_id)) {
      return commerce_file_license_load($entity_id);
    }
  }
}
