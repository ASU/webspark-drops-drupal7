<?php

/**
 * @file
 * Manages validation rules administration UI
 */

/**
 * Menu callback function to show an overview of the existing validation rules, and the option to add a rule
 */
function webform_validation_manage($node) {
  $rules = webform_validation_get_webform_rules($node);
  $output = array();
  $output['webform_validation_manage_overview_form'] = drupal_get_form('webform_validation_manage_overview_form', $rules, $node);
  $output['webform_validation_manage_add_rule'] = array(
    '#theme' => 'webform_validation_manage_add_rule',
    '#nid' => $node->nid,
  );
  return $output;
}

/**
 * Get the list of rules associated with the webform
 */
function webform_validation_get_webform_rules($node) {
  if (in_array($node->type, webform_variable_get('webform_node_types'))) {
    $webform_nid = $node->nid;
    $rules = webform_validation_get_node_rules($node->nid);
  }
  return $rules;
}


/**
 * Themable function to list and re-order the rules assigned to a webform
 */
function theme_webform_validation_manage_overview_form($variables) {
  $form = $variables['form'];
  $header = array(t('Rule name'), t('Validator'), t('Components'), t('Weight'), array(
    'data' => t('Operations'),
    'colspan' => 2,
  ));

  $rows = array();
  foreach (element_children($form) as $rule) {
    $row = array();
    foreach (element_children($form[$rule]) as $item) {
      //unset the titles of the form elements, since we are displaying them in a table with a header.
      unset($form[$rule][$item]['#title']);
      //add a class to the weight field
      $form[$rule]['weight']['#attributes']['class'] = array('ruleid-weight');
      $row[] = array(
        'data' => drupal_render($form[$rule][$item]),
      );
    }
    if (count($row) > 1) {
      $rows[] = array(
        'data' => $row,
        'class' => array('draggable'),
      );
    }
    // Hide any fieldsets, since we are displaying the form in a table.
    if (isset($form[$rule]['#type']) && $form[$rule]['#type'] === 'fieldset') {
      hide($form[$rule]);
    }
  }
  $drag = TRUE;
  if (!$rows) {
    $drag = FALSE;
    $rows[][] = array(
      'data' => t('No validation rules available.'),
      'colspan' => 5,
    );
  }
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'webform-validation-overview-form')));
  $output .= drupal_render_children($form);
  if ($drag) {
    drupal_add_tabledrag('webform-validation-overview-form', 'order', 'sibling', 'ruleid-weight');
  }
  return $output;
}

/**
 * Form to list and reorder the rules assigned to a webform
 */
function webform_validation_manage_overview_form($form, &$form_state, $rules, $node) {
  $form = array();
  $form['#tree'] = TRUE;
  $validators = webform_validation_get_validators_selection();

  foreach ($rules as $rule) {
    $component_info = webform_validation_rule_components_basic($rule['components']);
    $form[$rule['ruleid']] = array(
      '#type' => 'fieldset',
    );
    $form[$rule['ruleid']]['name'] = array(
      '#type' => 'item',
      '#title' => t('Name'),
      '#markup' => check_plain($rule['rulename']),
    );
    $form[$rule['ruleid']]['validator'] = array(
      '#type' => 'item',
      '#title' => t('Validator'),
      '#markup' => $validators[$rule['validator']],
    );
    $form[$rule['ruleid']]['components'] = array(
      '#type' => 'item',
      '#title' => t('Components'),
      '#markup' => theme('item_list', array('items' => $component_info)),
    );
    $form[$rule['ruleid']]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $rule['weight'],
      '#description' => t('Optional. By changing the order of validation rules, you can use code that relies on earlier validation functions being completed.'),
    );
    $form[$rule['ruleid']]['actions'] = array('#type' => 'actions');
    $form[$rule['ruleid']]['actions']['edit'] = array(
      '#type' => 'item',
      '#markup' => l(t('Edit'), 'node/' . $node->nid . '/webform/validation/edit/' . $rule['validator'] . '/' . $rule['ruleid'], array("query" => drupal_get_destination())),
    );
    $form[$rule['ruleid']]['actions']['delete'] = array(
      '#type' => 'item',
      '#markup' => l(t('Delete'), 'node/' . $node->nid . '/webform/validation/delete/' . $rule['ruleid'], array("query" => drupal_get_destination())),
    );
  }
  if (count($rules) > 1) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save rule order'),
    );
  }

  return $form;
}

/**
 * Submit function for rule overview form.
 */
function webform_validation_manage_overview_form_submit($form, $form_state) {
  //Save the rule weights.
  foreach ($form_state['values'] as $ruleid => $value) {
    if (is_numeric($ruleid)) {
      $update = db_update('webform_validation_rule')
        ->fields(array(
          'weight' => $value['weight'],
        ))
        ->condition('ruleid', $ruleid)
        ->execute();
    }
  }
  drupal_set_message(t('The order of the validation rules has been saved.'));
}

/**
 * Callback function to add or edit a validation rule
 */
function webform_validation_manage_rule($form, $form_state, $node, $action = 'add', $validator, $rule = NULL) {
  $form = array();
  $rule_validator = webform_validation_get_validator_info($validator);

  $form['rule'] = array(
    '#type' => 'fieldset',
    '#title' => ($action == 'edit') ? t('Edit rule') : t('Add rule'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['rule']['validator'] = array(
    '#type' => 'hidden',
    '#value' => $validator,
  );

  $form['rule']['action'] = array(
    '#type' => 'hidden',
    '#value' => $action,
  );

  if ($action == 'edit' && $rule) {
    $form['rule']['ruleid'] = array(
      '#type' => 'hidden',
      '#value' => $rule['ruleid'],
    );

    $form['rule']['nid'] = array(
      '#type' => 'hidden',
      '#value' => $rule['nid'],
    );
  }
  else {
    $form['rule']['nid'] = array(
      '#type' => 'hidden',
      '#value' => $node->nid,
    );
  }

  $form['rule']['rulename'] = array(
    '#type' => 'textfield',
    '#title' => t('Rule name'),
    '#default_value' => (isset($rule['rulename'])) ? $rule['rulename'] : '',
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 255,
    '#weight' => 1,
  );

  $form['rule']['rule_components'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Components'),
    '#weight' => 3,
    '#description' => t('Select the components to be validated by this validation rule'),
    '#options' => webform_validation_get_webform_components($node, $validator),
    '#default_value' => (isset($rule['components'])) ? array_keys($rule['components']) : array(),
  );

  if (!empty($rule_validator['custom_data']) && is_array($rule_validator['custom_data'])) {
    $required = isset($rule_validator['custom_data']['required']) ? $rule_validator['custom_data']['required'] : TRUE;
    $form['rule']['data'] = array(
      '#type' => 'textfield',
      '#title' => $rule_validator['custom_data']['label'],
      '#description' => $rule_validator['custom_data']['description'],
      '#required' => (bool) $required,
      '#size' => 60,
      '#maxlength' => NULL,
      '#default_value' => $rule['data'],
      '#weight' => 4,
    );
  }

  if (!empty($rule_validator['negatable'])) {
    $form['rule']['negate'] = array(
      '#type' => 'checkbox',
      '#title' => t('Negate rule'),
      '#description' => t('Validate the inverse of the rule.'),
      '#default_value' => $rule['negate'],
      '#weight' => 5,
    );
  }

  if (!empty($rule_validator['custom_error'])) {
    $form['rule']['error_message'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom error message'),
      '#description' => t("Specify an error message that should be displayed when user input doesn't pass validation"),
      '#required' => TRUE,
      '#size' => 60,
      '#maxlength' => 2048,
      '#default_value' => $rule['error_message'],
      '#weight' => 5,
    );
  }

  $form['rule']['submit'] = array(
    '#type' => 'submit',
    '#value' => (isset($rule['ruleid'])) ? t('Save rule') : t('Add rule'),
    '#weight' => 25,
  );

  $destination = drupal_get_destination();
  $form['rule']['cancel'] = array(
    '#markup' => l(t('Cancel'), $destination['destination']),
    '#weight' => 26,
  );

  return $form;
}

/**
 * Validation handler to add / edit a rule
 */
function webform_validation_manage_rule_validate($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['action'] == 'edit') {
    if (!is_numeric($values['ruleid']) || $values['ruleid'] == 0) {
      form_set_error(NULL, t('A problem occurred while editing this rule. Please try again.'));
    }
  }

  $rule_validator = webform_validation_get_validator_info($values['validator']);
  $selected_components = count(array_filter($values['rule_components']));
  // Check validator min_components and min_components property when they are equal.
  if (isset($rule_validator['min_components']) && isset($rule_validator['max_components']) && $rule_validator['min_components'] === $rule_validator['max_components'] && $selected_components !== $rule_validator['min_components']) {
      form_set_error('rule_components', format_plural($rule_validator['min_components'], 'You need to select exactly @count component', 'You need to select exactly @count components'));
  }
  // check validator min_components property
  elseif (isset($rule_validator['min_components']) && $selected_components < $rule_validator['min_components']) {
      form_set_error('rule_components', format_plural($rule_validator['min_components'], 'You need to select at least @count component', 'You need to select at least @count components'));
  }
  // check validator max_components property
  elseif (isset($rule_validator['max_components']) && $selected_components > $rule_validator['max_components']) {
      form_set_error('rule_components', format_plural($rule_validator['max_components'], 'You can select @count component at most', 'You can select @count components at most'));
  }
}


/**
 * Submit handler to add / edit a rule
 */
function webform_validation_manage_rule_submit($form, &$form_state) {
  $values = $form_state['values'];
  webform_validation_rule_save($values);
}

/**
 * Get a list of components for a specific webform, filtered by the validator settings
 */
function webform_validation_get_webform_components($node, $validator) {
  $ret = array();
  $components = $node->webform['components'];
  if ($components) {
    $valid_components = webform_validation_valid_component_types($validator);
    $component_names = webform_component_list($node, NULL, 'path');
    foreach ($components as $cid => $component) {
      if (in_array($component['type'], $valid_components)) {
        $ret[$cid] = $component_names[$cid];
      }
    }
  }
  return $ret;
}

/**
 * Confirmation form to delete a rule
 */
function webform_validation_delete_rule($form, &$form_state, $rule) {
  if (isset($rule['ruleid'])) {
    $form['ruleid'] = array(
      '#type' => 'value',
      '#value' => $rule['ruleid'],
    );
  }

  return confirm_form($form,
    t('Are you sure you want to delete the rule %name?', array('%name' => $rule['rulename'])),
    isset($_GET['destination']) ? $_GET['destination'] : $_GET['q'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler to delete a rule
 */
function webform_validation_delete_rule_submit($form, &$form_state) {
  $ruleid = $form_state['values']['ruleid'];
  module_invoke_all('webform_validation', 'rule', 'delete', $ruleid);
  webform_dynamic_delete_rule($ruleid);
}
