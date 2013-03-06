<?php

/**
 * @file
 * Drush commands for CAS.
 */

/**
 * Implements hook_drush_command().
 */
function cas_drush_command() {
  $items = array();
  $items['cas-user-create'] = array(
    'callback' => 'cas_drush_user_create',
    'description' => dt('Create a CAS user account with the specified CAS username.'),
    'arguments' => array(
      'cas_name' => 'The CAS username of the account to add',
    ),
    'required-arguments' => TRUE,
    'examples' => array(
      'drush cas-user-create newcasuser' => 'Create a new user with CAS username newcasuser',
    ),
  );
  return $items;
}

/**
 * Implementats hook_drush_help().
 */
function cas_drush_help($section) {
  switch ($section) {
    case 'drush:cas-user-create':
      return dt('Create a CAS user account with the specified CAS username.');
  }
}

/**
 * Creates a new CAS user account.
 */
function cas_drush_user_create($cas_name) {
  // @todo: Handle additional options for setting other user attributes.
  $account = cas_user_load_by_name($cas_name);
  if ($account === FALSE) {
    if (!drush_get_context('DRUSH_SIMULATE')) {
      $options = array('invoke_cas_user_presave' => TRUE);
      $new_user_object = cas_user_register($cas_name, $options);
      if ($new_user_object !== FALSE) {
        _drush_user_print_info($new_user_object->uid);
        // return $new_user_object->uid;
      }
      else {
        drush_set_error(dt('Could not create a new user account with CAS username @cas_name.', array('@cas_name' => $cas_name)));
      }
    }
  }
  else {
    drush_set_error(dt('There is already a user account with CAS username @cas_name.', array('@cas_name' => $cas_name)));
  }
}
