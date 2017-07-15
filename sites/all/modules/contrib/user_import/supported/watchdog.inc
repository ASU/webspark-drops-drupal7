<?php

/**
 * @todo add option to not record watchdog messages for each user created
 * on large imports user import could add a lot of rows to the watchdog table
 */

/**
 * Implementation of hook_user_import_after_save().
 */
function watchdog_user_import_after_save($settings, $account, $password, $fields, $updated) {

  if (empty($updated)) {
    watchdog('user', 'New user: %name %email.', array('%name' => $account->name, '%email' => '<' . $account->mail . '>'), WATCHDOG_NOTICE, l(t('edit'), 'user/' . $account->uid . '/edit'));
  }

  return;
}
