<?php

/**
 * Defines an area handler that displays a "View order" form allowing the user
 * to enter an order number and redirect to that order's view page.
 */
class commerce_file_handler_area_license_issue_order_form extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();

    // Undefine the empty option.
    unset($options['empty']);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Don't display a form element for the undefined empty option.
    unset($form['empty']);
  }

  function render($empty = FALSE) {
    if (!$empty) {
      // First look for an order_id argument.
      foreach ($this->view->argument as $name => $argument) {
        if ($argument instanceof commerce_order_handler_argument_order_order_id) {
          // If it is single value...
          if (count($argument->value) == 1) {
            // Load the order.
            $order = commerce_order_load(reset($argument->value));
            if (!empty($order)) {
              // Include the forms file
              module_load_include('inc', 'commerce_file', 'includes/commerce_file_license.forms');

              // Build the form
              $form_id = commerce_file_license_issue_by_host_form_id('commerce_order', array($order->order_id));
              $form = drupal_get_form($form_id, 'commerce_order', $order);

              // Render the form
              $rendered_form = drupal_render($form);

              if (!empty($rendered_form)) {
                // wrap the form in a fieldset
                $display = array(
                  '#type' => 'fieldset',
                  '#title' => t('License Order Operations'),
                  '#description' => t('Update all licenses associated with this order.'),
                  '#collapsible' => TRUE,
                  '#collapsed' => FALSE,
                  '#attached' => array(
                    'js' => array(
                      'misc/form.js',
                      'misc/collapse.js',
                    ),
                  ),
                  '#attributes' => array(
                    'class' => array('collapsible'),
                  ),
                  'rendered_form' => array('#markup' => $rendered_form),
                );

                return '<div class="commerce-file-handler-area-license-issue-order-form">' . drupal_render($display) . '</div>';
              }
            }
          }
        }
      }
    }

    return '';
  }
}
