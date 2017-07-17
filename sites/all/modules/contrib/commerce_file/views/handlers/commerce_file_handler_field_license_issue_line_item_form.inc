<?php

/**
 * Field handler to return a line item's title.
 */
class commerce_file_handler_field_license_issue_line_item_form extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['line_item_id'] = 'line_item_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    // Load the line item and return its title.
    $line_item_id = $this->get_value($values, 'line_item_id');
    $line_item = commerce_line_item_load($line_item_id);

    if (!empty($line_item)) {
      // Include the forms file
      module_load_include('inc', 'commerce_file', 'includes/commerce_file_license.forms');

      // Build the form
      $form_id = commerce_file_license_issue_by_host_form_id('commerce_line_item', array($line_item->line_item_id));
      $form = drupal_get_form($form_id, 'commerce_line_item', $line_item);

      // clean up display
      unset($form['product_refresh']['#description']);

      // Render the form
      $rendered_form = drupal_render($form);

      if (!empty($rendered_form)) {
        return '<div class="commerce-file-handler-field-license-issue-line-item-form">' . $rendered_form . '</div>';
      }
    }

    return '';
  }
}
