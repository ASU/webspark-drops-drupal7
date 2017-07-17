<?php

/**
 * @file
 * Argument plugin for a valid user.
 */

/**
 * Validate whether an argument is a valid user.
 *
 * This supports either numeric arguments (UID) or strings (username) and
 * converts either one into the user's UID.  This validator also sets the
 * argument's title to the username.
 */
class commerce_file_plugin_argument_validate_user extends views_plugin_argument_validate_user {
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['restrict_roles']['#title'] = t('If the current user does not match the argument, validate the argument for users with specific roles.');

    $form['roles'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Grant access for the selected roles'),
      '#description' => t('If no roles are selected, additional access will not be granted.'),
      '#options' => array_map('check_plain', user_roles(TRUE)),
      '#default_value' => $this->options['roles'],
      '#process' => array('form_process_checkboxes', 'ctools_dependent_process'),
      '#dependency' => array(
        'edit-options-validate-options-commerce-file-user-restrict-roles' => array(1),
      ),
      '#prefix' => '<div id="edit-options-validate-options-commerce-file-user-restrict-roles-wrapper">',
      '#suffix' => '</div>',
    );
  }

  function validate_argument($argument) {
    global $user;
    $type = $this->options['type'];
    // is_numeric() can return false positives, so we ensure it's an integer.
    // However, is_integer() will always fail, since $argument is a string.
    if (is_numeric($argument) && $argument == intval($argument)) {
      if ($type == 'uid' || $type == 'either') {
        if ($argument == $GLOBALS['user']->uid) {
          // If you assign an object to a variable in PHP, the variable
          // automatically acts as a reference, not a copy, so we use
          // clone to ensure that we don't actually mess with the
          // real global $user object.
          $account = clone $GLOBALS['user'];
        }
        $where = 'uid = :argument';
      }
    }
    else {
      if ($type == 'name' || $type == 'either') {
        if ($argument == $GLOBALS['user']->name) {
          $account = clone $GLOBALS['user'];
        }
        $where = "name = :argument";
      }
    }

    // If we don't have a WHERE clause, the argument is invalid.
    if (empty($where)) {
      return FALSE;
    }

    if (!isset($account)) {
      $query = 'SELECT uid, name FROM {users} WHERE ' . $where;
      $account = db_query($query, array(':argument' => $argument))->fetchObject();
    }
    if (empty($account)) {
      // User not found.
      return FALSE;
    }

    // access checks
    $owner_access = $user->uid == $account->uid;
    $admin_access = user_access('access any ' . COMMERCE_FILE_LICENSE_ENTITY_NAME, $user) || user_access(COMMERCE_FILE_ADMIN_PERM, $user);

    // Validate user access
    if ($owner_access || $admin_access) {
      // ALLOW access if owner or admin access
      $this->_set_allowed_argument($account);
      return TRUE;
    }

    // See if we're filtering users based on roles.
    if (!empty($this->options['restrict_roles']) && !empty($this->options['roles'])) {
      // Look for matching roles on the current user.
      $matching_roles = array_intersect(array_keys($user->roles), $this->options['roles']);
      if (!empty($matching_roles)) {
        // ALLOW if the user does not match any of the roles.
        $this->_set_allowed_argument($account);
        return TRUE;
      }
    }

    // DENY by default
    return FALSE;
  }

  /**
   * Sets argument properties for an allowed argument
   */
  private function _set_allowed_argument($account) {
    $this->argument->argument = $account->uid;
    $this->argument->validated_title = check_plain($account->name);
  }
}
