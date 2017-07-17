<?php

/**
 * @file
 * Field handler for a license link.
 */

/**
 * Field handler to present a link to an order.
 */
class commerce_file_handler_field_license_link extends views_handler_field {
  function construct() {
    parent::construct();

    // retrieve bare minimum to do access check
    $this->additional_fields['license_id'] = 'license_id';
    $this->additional_fields['uid'] = 'uid';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $entity_id = $this->get_value($values, 'license_id');

    if (!empty($entity_id)) {
      $entity = commerce_file_license_load($entity_id);

      if ($entity->access('view') && ($uri = $entity->uri())) {
        $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
        return l($text, $uri['path'], array('query' => drupal_get_destination()) + $uri);
      }
    }
  }
}
