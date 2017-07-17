<?php

/**
 * @file
 * Field handler for a license edit link.
 */

/**
 * Field handler to present a license edit link.
 */
class commerce_file_handler_field_license_link_clone extends commerce_file_handler_field_license_link {
  function render($values) {
    $entity_id = $this->get_value($values, 'license_id');

    if (!empty($entity_id)) {
      $entity = commerce_file_license_load($entity_id);

      if ($entity->access('create') && ($uri = $entity->uri())) {
        $text = !empty($this->options['text']) ? $this->options['text'] : t('clone');
        return l($text, $uri['path'] . '/clone', array('query' => drupal_get_destination()) + $uri);
      }
    }
  }
}
