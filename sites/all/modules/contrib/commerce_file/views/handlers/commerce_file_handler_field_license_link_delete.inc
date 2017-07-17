<?php

/**
 * @file
 * Field handler for a license delete link.
 */

/**
 * Field handler to present a license delete link.
 */
class commerce_file_handler_field_license_link_delete extends commerce_file_handler_field_license_link {
  function render($values) {
    $entity_id = $this->get_value($values, 'license_id');

    if (!empty($entity_id)) {
      $entity = commerce_file_license_load($entity_id);

      if ($entity->access('delete') && ($uri = $entity->uri())) {
        $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
        return l($text, $uri['path'] . '/delete', array('query' => drupal_get_destination()) + $uri);
      }
    }
  }
}
