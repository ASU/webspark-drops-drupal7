<?php
/**
 * @file
 * Contains form definitions for removing missing modules.
 */

/**
 * Menu callback: Confirm disabling module.
 */
function missing_module_disable_confirm($form, &$form_state, $module_name = FALSE) {
  $form_state['missing_modules']['modules'] = missing_module_find_missing();

  if (array_key_exists($module_name, $form_state['missing_modules']['modules'])) {
    $form = confirm_form(array(),
                  t('This action disables the @module_name module.', array('@module_name' => $module_name)),
                  'admin/reports/status',
                  t('Are you sure you want to disable the @module_name module?', array('@module_name' => $module_name)),
                   t('Disable module'),
                   t('Cancel'));
  }
  else {
    drupal_set_message(t('%module_name is not a missing module and cannot be disabled.', array('%module_name' => $module_name)), 'error');
    // This will exit out of the function.
    drupal_goto('admin/reports/status');
  }

  return $form;
}

/**
 * Handler for module disable confirmation.
 */
function missing_module_disable_confirm_submit($form, &$form_state) {

  $module_name = $form_state['build_info']['args'][0];

  if (array_key_exists($module_name, $form_state['missing_modules']['modules'])) {
    db_update('system')
           ->fields(array('status' => 0))
           ->condition('type', 'module')
           ->condition('name', $module_name)
           ->execute();
  }
  else {
    drupal_set_message(t('%module_name is not a missing module and cannot be disabled.', array('%module_name' => $module_name)), 'error');
  }

  $form_state['redirect'] = 'admin/reports/status';
}

/**
 * Menu callback: Confirm remove module.
 */
function missing_module_remove_confirm($form, &$form_state, $module_name = FALSE) {
  $form_state['missing_modules']['modules'] = missing_module_find_missing();

  if (array_key_exists($module_name, $form_state['missing_modules']['modules'])) {
    $form = confirm_form(array(),
                  t('This action removes the @module_name module.', array('@module_name' => $module_name)),
                  'admin/reports/status',
                  t('Are you sure you want to remove the @module_name module from the system tabel?', array('@module_name' => $module_name)),
                   t('Remove module'),
                   t('Cancel'));
  }
  else {
    drupal_set_message(t('%module_name is not a missing module and cannot be disabled.', array('%module_name' => $module_name)), 'error');
    // This will exit out of the function.
    drupal_goto('admin/reports/status');
  }

  return $form;
}

/**
 * Handler for module remove confirmation.
 */
function missing_module_remove_confirm_submit($form, &$form_state) {

  $module_name = $form_state['build_info']['args'][0];

  if (array_key_exists($module_name, $form_state['missing_modules']['modules'])) {
    db_delete('system')
           ->condition('name', $module_name)
           ->execute();
  }
  else {
    drupal_set_message(t('%module_name is not a missing module and cannot be removed.', array('%module_name' => $module_name)), 'error');
  }

  $form_state['redirect'] = 'admin/reports/status';
}