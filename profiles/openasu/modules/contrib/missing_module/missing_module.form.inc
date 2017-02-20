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
      t('Disable missing module <strong><em>@module_name</em></strong>', array('@module_name' => $module_name)),
      'admin/reports/status',
      t('This does not remove the missing module\'s superfluous record from the system ' .
        'table, and it does not remove any lingering tables and/or data generated ' .
        'from the database. <br><br>Are you sure you want to disable the ' .
        'missing @module_name module?', array('@module_name' => $module_name)),
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
    drupal_set_message(t('The %module_name module has been set to disabled.',
      array('%module_name' => $module_name)), 'status');
  }
  else {
    drupal_set_message(t('%module_name is not a missing module and cannot be disabled.',
      array('%module_name' => $module_name)), 'error');
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
      t('Remove the <strong><em>@module_name</em></strong>', array('@module_name' => $module_name)),
      'admin/reports/status',
      t('NOTE: This only removes the @module_name module\'s superfluous record ' .
        'from the system table. If the module had an .install file, it is likely ' .
        'that there are lingering database tables and/or data created by the ' .
        'module that need to be deleted by properly uninstalling it at ' .
        '/admin/modules/uninstall after redownloading the module code. <br><br>' .
        'Are you sure you want to continue and remove the @module_name2 module ' .
        'from the system table?', array(
          '@module_name' => $module_name,
          '@module_name2' => $module_name
        )
      ),
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
    drupal_set_message(t('The record for %module_name in the system table has ' .
      'been removed.', array('%module_name' => $module_name)), 'status');
  }
  else {
    drupal_set_message(t('%module_name is not a missing module and cannot be removed.',
      array('%module_name' => $module_name)), 'error');
  }

  $form_state['redirect'] = 'admin/reports/status';
}