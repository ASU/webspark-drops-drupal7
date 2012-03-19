<?php

/**
 * @file
 * Administrative functions for managing custom fields for every entity.
 */

/**
 * Shows the list of custom fields.
 */
function ds_custom_fields_list() {
  $output = '';

  ctools_include('export');
  $custom_fields = ctools_export_crud_load_all('ds_fields');
  if (!empty($custom_fields)) {

    $rows = array();
    foreach ($custom_fields as $field_key => $field_value) {
      $row = array();
      $row[] = check_plain($field_value->label);
      $row[] = ds_field_human_name($field_value->field_type);
      $row[] = $field_key;
      $row[] = ucwords(str_replace('_', ' ', implode(', ', $field_value->entities)));
      $operations = l(t('Edit'), 'admin/structure/ds/fields/manage/' . $field_key, array('alias' => TRUE));

      if ($field_value->export_type == 3) {
        $operations .= ' - ' . l(t('Revert'), 'admin/structure/ds/fields/revert/' . $field_key, array('alias' => TRUE));
      }
      elseif ($field_value->export_type == 1) {
        $operations .= ' - ' . l(t('Delete'), 'admin/structure/ds/fields/delete/' . $field_key, array('alias' => TRUE));
      }
      $row[] = $operations;
      $rows[] = $row;
    }

    $table = array(
      'header' => array(
        'Label',
        'Type',
        'Machine name',
        'Entities',
        'Operations',
      ),
      'rows' => $rows,
    );

    $output = theme('table', $table);
  }
  else {
    $output = t('No custom fields have been defined.');
  }

  return $output;
}

/**
 * Return the human name of a field.
 *
 * @return $human_name
 *   The human name of a field.
 */
function ds_field_human_name($type) {

  switch ($type) {
    case DS_FIELD_TYPE_CODE:
      return t('Code field');
    case DS_FIELD_TYPE_BLOCK:
      return t('Block field');
    case DS_FIELD_TYPE_CTOOLS:
      return t('Dynamic field');
    case DS_FIELD_TYPE_PREPROCESS:
      return t('Preprocess field');
  }

  // Fallback
  return t('Unknown');
}

/**
 * Manage a field. This will redirect to the exact form.
 */
function ds_custom_manage($field_key = '') {
  $redirect = '';
  ctools_include('export');
  $custom_fields = ctools_export_crud_load_all('ds_fields');
  if (isset($custom_fields[$field_key])) {
    $field = $custom_fields[$field_key];
    switch ($field->field_type) {
      case DS_FIELD_TYPE_CODE:
        $redirect = 'admin/structure/ds/fields/manage_custom/' . $field_key;
        break;

      case DS_FIELD_TYPE_BLOCK:
        $redirect = 'admin/structure/ds/fields/manage_block/' . $field_key;
        break;

      case DS_FIELD_TYPE_CTOOLS:
        $redirect = 'admin/structure/ds/fields/manage_ctools/' . $field_key;
        break;

      case DS_FIELD_TYPE_PREPROCESS:
        $redirect = 'admin/structure/ds/fields/manage_preprocess/' . $field_key;
        break;

      default:
        drupal_set_message(t('Field not found'));
        $redirect = 'admin/structure/ds/fields';
        break;
    }
  }

  drupal_goto($redirect);
}

/**
 * Shared form for all all fields.
 */
function ds_shared_form(&$form, $field) {
  ctools_include('export');
  $custom_fields = ctools_export_crud_load_all('ds_fields');
  if (isset($custom_fields[$field])) {
    $field = $custom_fields[$field];
  }
  else {
    $field = new stdClass;
    $field->label = '';
    $field->field = '';
    $field->entities = array();
    $field->properties = array();
  }

  $form['name'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $field->label,
    '#description' => t('The human-readable label of the field.'),
    '#maxlength' => 32,
    '#required' => TRUE,
    '#size' => 30,
  );

  $form['field'] = array(
    '#type' => 'machine_name',
    '#default_value' => $field->field,
    '#maxlength' => 32,
    '#description' => t('The machine-readable name of this field. This name must contain only lowercase letters and underscores. This name must be unique.'),
    '#disabled' => !empty($field->field),
    '#machine_name' => array(
      'exists' => 'ds_field_unique',
    ),
  );

  $entity_options = array();
  $entities = entity_get_info();
  foreach ($entities as $entity_type => $entity_info) {
    if ((isset($entity_info['fieldable']) && $entity_info['fieldable']) || $entity_type == 'ds_views') {
      $entity_options[$entity_type] = drupal_ucfirst(str_replace('_', ' ', $entity_type));
    }
  }
  $form['entities'] = array(
    '#title' => t('Entities'),
    '#description' => t('Select the entities for which this field will be made available.'),
    '#type' => 'checkboxes',
    '#required' => TRUE,
    '#options' => $entity_options,
    '#default_value' => $field->entities,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );

  // Validate & submit are also the same.
  $form['#validate'][] = 'ds_shared_form_validate';
  $form['#submit'][] = 'ds_shared_form_submit';

  return $field;
}

/**
 * Return whether a field machine name is unique.
 */
function ds_field_unique($name) {
  ctools_include('export');
  $custom_fields = ctools_export_crud_load_all('ds_fields');
  $value = strtr($name, array('-' => '_'));
  return isset($custom_fields[$value]) ? TRUE : FALSE;
}

/**
 * Shared field form validation.
 */
function ds_shared_form_validate($form, &$form_state) {
  $field = new stdClass;
  $field->properties = array();
  $field->field = $form_state['values']['field'];
  $field->label = $form_state['values']['name'];

  $entities = $form_state['values']['entities'];
  foreach ($entities as $key => $value) {
    if ($key !== $value) {
      unset($entities[$key]);
    }
  }
  $field->entities = $entities;
  $form_state['field'] = $field;
}

/**
 * Save any field.
 */
function ds_shared_form_submit($form, &$form_state) {
  $field = $form_state['field'];

  // Delete previous field configuration.
  db_delete('ds_fields')
    ->condition('field', $field->field)
    ->execute();

  // Save field and clear ds_fields.
  drupal_write_record('ds_fields', $field);
  cache_clear_all('ds_fields', 'cache');

  // Redirect.
  $form_state['redirect'] = 'admin/structure/ds/fields';
  drupal_set_message(t('The field %field has been saved', array('%field' => $field->label)));
}

/**
 * Manage a custom field.
 */
function ds_edit_custom_field_form($form, &$form_state, $custom_field = '') {
  $custom_field = ds_shared_form($form, $custom_field);

  $form['code'] = array(
    '#type' => 'text_format',
    '#title' => t('Field code'),
    '#default_value' => isset($custom_field->properties['code']['value']) ? $custom_field->properties['code']['value'] : '',
    '#format' => isset($custom_field->properties['code']['format']) ? $custom_field->properties['code']['format'] : 'ds_code',
    '#base_type' => 'textarea',
    '#required' => TRUE,
  );

  $form['use_token'] = array(
    '#type' => 'checkbox',
    '#title' => t('Token'),
    '#description' => t('Toggle this checkbox if you are using tokens in this field.'),
    '#default_value' => isset($custom_field->properties['use_token']) ? $custom_field->properties['use_token'] : '',
  );

  // Token support.
  if (module_exists('token')) {

    $form['tokens'] = array(
      '#title' => t('Tokens'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['tokens']['help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => 'all',
      '#global_types' => FALSE,
    );
  }
  else {
    $form['use_token']['#description'] = t('Toggle this checkbox if you are using tokens in this field. If the token module is installed, you get a nice list of all tokens available in your site.');
  }

  $form['#validate'][] = 'ds_custom_field_form_validate';

  return $form;
}

/**
 * Custom field form validation.
 */
function ds_custom_field_form_validate($form, &$form_state) {
  $form_state['field']->field_type = DS_FIELD_TYPE_CODE;
  $form_state['field']->properties['code'] = $form_state['values']['code'];
  $form_state['field']->properties['use_token'] = $form_state['values']['use_token'];
}

/**
 * Manage a CTools field.
 */
function ds_edit_ctools_field_form($form, &$form_state, $ctools_field = '') {
  $custom_field = ds_shared_form($form, $ctools_field);
  $form['info'] = array(
    '#markup' => t('The content of this field is configurable on the "Manage display" screens.'),
    '#weight' => -10,
  );
  $form['#validate'][] = 'ds_ctools_field_form_validate';
  return $form;
}

/**
 * CTools field form validation.
 */
function ds_ctools_field_form_validate($form, &$form_state) {
  $form_state['field']->field_type = DS_FIELD_TYPE_CTOOLS;
  $form_state['field']->properties['default'] = array();
  $form_state['field']->properties['settings'] = array('show_title' => array('type' => 'checkbox'), 'title_wrapper' => array('type' => 'textfield', 'description' => t('Eg: h1, h2, p')), 'ctools' => array('type' => 'ctools'));
}

/**
 * Manage a Preprocess field.
 */
function ds_edit_preprocess_field_form($form, &$form_state, $ctools_field = '') {
  $custom_field = ds_shared_form($form, $ctools_field);
  $form['info'] = array(
    '#markup' => t('The machine name of this field must reflect the key in the variables, e.g. "submitted". So in most cases, it is very likely you will have to manually edit the machine name as well, which can not be changed anymore after saving.'),
    '#weight' => -10,
  );
  $form['#validate'][] = 'ds_preprocess_field_form_validate';
  return $form;
}

/**
 * CTools field form validation.
 */
function ds_preprocess_field_form_validate($form, &$form_state) {
  $form_state['field']->field_type = DS_FIELD_TYPE_PREPROCESS;
}

/**
 * Manage a custom block.
 */
function ds_edit_block_field_form($form, &$form_state, $custom_block = '') {
  $custom_block = ds_shared_form($form, $custom_block);

  $blocks = array();
  foreach (module_implements('block_info') as $module) {
    $module_blocks = module_invoke($module, 'block_info');
    if ($module_blocks) {
      foreach ($module_blocks as $module_key => $info) {
        $blocks[drupal_ucfirst($module)][$module . '|' . $module_key] = $info['info'];
      }
    }
  }
  ksort($blocks);

  $form['block_identity']['block'] = array(
    '#type' => 'select',
    '#options' => $blocks,
    '#title' => t('Block'),
    '#required' => TRUE,
    '#default_value' => isset($custom_block->properties['block']) ? $custom_block->properties['block'] : '',
  );
  $form['block_identity']['block_render'] = array(
    '#type' => 'select',
    '#options' => array(
      DS_BLOCK_TEMPLATE => t('Default'),
      DS_BLOCK_TITLE_CONTENT => t('Show block title + content'),
      DS_BLOCK_CONTENT => t('Show only block content'),
    ),
    '#title' => t('Layout'),
    '#required' => TRUE,
    '#default_value' => isset($custom_block->properties['block_render']) ? $custom_block->properties['block_render'] : '',
  );

  $form['#validate'][] = 'ds_block_field_form_validate';

  return $form;
}

/**
 * Custom field form validation.
 */
function ds_block_field_form_validate($form, &$form_state) {
  $form_state['field']->field_type = DS_FIELD_TYPE_BLOCK;
  $form_state['field']->properties = array();
  $form_state['field']->properties['block'] = $form_state['values']['block'];
  $form_state['field']->properties['block_render'] = $form_state['values']['block_render'];
}

/**
 * Menu callback: Confirmation custom field delete form.
 */
function ds_delete_field_confirm($form, &$form_state, $field = '') {
  return ds_remove_fields_form($form, $form_state, $field, 'delete');
}

/**
 * Menu callback: Confirmation custom field delete form.
 */
function ds_revert_field_confirm($form, &$form_state, $field = '') {
  return ds_remove_fields_form($form, $form_state, $field, 'revert');
}

/**
 * Confirmation delete or revert form.
 */
function ds_remove_fields_form($form, &$form_state, $field = '', $action = 'delete') {
  ctools_include('export');
  $custom_fields = ctools_export_crud_load_all('ds_fields');
  if (isset($custom_fields[$field])) {
    $field = $custom_fields[$field];
    $form['#ds_field'] = $field;
    return confirm_form($form,
      t('Are you sure you want to ' . $action . ' %field?', array('%field' => $field->label)),
      'admin/structure/ds/fields',
      t('This action cannot be undone.'),
      t(drupal_ucfirst($action)),
      t('Cancel')
    );
  }
  else {
    drupal_set_message(t('Unknown field'));
    drupal_goto('admin/structure/ds/fields');
  }
}

/**
 * Submit callback: confirmed delete submit.
 */
function ds_delete_field_confirm_submit($form, &$form_state) {
  ds_remove_field_confirm_submit($form, $form_state, 'deleted');
}

/**
 * Submit callback: confirmed revert submit.
 */
function ds_revert_field_confirm_submit($form, &$form_state) {
  ds_remove_field_confirm_submit($form, $form_state, 'reverted');
}

/**
 * Confirmed field delete or revert submit callback.
 */
function ds_remove_field_confirm_submit($form, &$form_state, $action = 'deleted') {

  $field = $form['#ds_field'];

  // Remove field.
  db_delete('ds_fields')
    ->condition('field', $field->field)
    ->execute();

  // Clear cache.
  cache_clear_all('ds_fields', 'cache');

  // Redirect.
  $form_state['redirect'] = 'admin/structure/ds/fields';
  drupal_set_message(t('The field %field has been ' . $action, array('%field' => $field->label)));
}
