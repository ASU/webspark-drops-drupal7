<?php

function _user_import_process($settings) {
  // Load supported modules
  user_import_load_supported();

  $remaining_data            = FALSE;
  $line_max                  = variable_get('user_import_line_max', 1000);
  $import_max                = variable_get('user_import_max', 250);
  $field_match               = _user_import_unconcatenate_field_match($settings['field_match']);
  $update_setting            = _user_import_update_user_check($settings['options']['update_user']);
  $update_setting_per_module = $settings['options']['update_user'];
  $username_data             = array();
  $username_order            = array();
  $username_abbreviate       = array();
  $first_line_skip           = 0;
  $delimiter                 = isset($settings['delimiter']) && !empty($settings['delimiter']) ? $settings['delimiter'] : ',';

  ini_set('auto_detect_line_endings', TRUE);
  $handle = @fopen($settings['filepath'], "r");

  // move pointer to where test/import last finished
  if ($settings['pointer'] != 0) fseek($handle, $settings['pointer']);

  // start count of imports on this cron run
  $processed_counter = 0;

  while ($data = fgetcsv($handle, $line_max, $delimiter)) {

    $errors = user_import_errors(FALSE, TRUE);

    // if importing, check we are not over max number of imports per cron
    if ($settings['setting'] == 'import' && $processed_counter >= $import_max) {
      $remaining_data = TRUE;
      break;
    }

    // don't process empty lines
    $line_filled = (count($data) == 1 && drupal_strlen($data[0]) == 0) ? FALSE : TRUE;

    if ($line_filled) {

      // check if this is first line - if so should we skip?
      if (!empty($settings['first_line_skip']) && $settings['processed'] == 0) {
        // reset to false on second process
        $first_line_skip = ($first_line_skip === 0) ? TRUE : FALSE;
      }

      if (!$first_line_skip) {

        unset($errors, $fields);
        reset($field_match);
        $password = '';

        // Process data cell.
        foreach ($field_match as $column_id => $column_settings) {

          $type     = $column_settings['type'];
          $field_id = $column_settings['field_id'];

          // Skip if this is a field used as part of a username but
          // not otherwise mapped for import.
          if ($type != 'username_part') {
            $fields[$type][$field_id] = module_invoke_all('user_import_data', $settings, $update_setting, $column_settings, $type, $field_id, $data, $column_id);
          }
          // Read in data if present for concatenating a user name.
          if ($column_settings['username'] > 0) {

            $username_data[$column_id]       = $data[$column_id];
            $username_order[$column_id]      = $column_settings['username'];
            $username_abbreviate[$column_id] = $column_settings['abbreviate'];
          }
        }

        $errors           = user_import_errors();
        $account          = array();
        $existing_account = FALSE;
        $updated          = FALSE;

        // if we update existing users matched by email (and therefore passed validation even if this email already exists)
        // look for and use an existing account.
        if ($update_setting && !empty($fields['user']['email'][0])) {
          $existing_account = user_load_by_mail($fields['user']['email'][0]);
          if ($existing_account) $account = (array)$existing_account;
        }

        // if $account['uid'] is not empty then we can assume the account is being updated
        $account_additions = module_invoke_all('user_import_pre_save', $settings, $account, $fields, $errors, $update_setting_per_module);

        foreach ($account_additions as $field_name => $value) {
          $account[$field_name] = $value;
        }

        if (empty($errors)) {

          if ($settings['setting'] == 'import') {

            if ($existing_account) {
              $account = user_save($existing_account, $account);
              $updated = TRUE;
            }
            else {
              // Only set a user name if we are not updating an existing record.
              $account['name'] = _user_import_create_username($username_order, $username_data, $username_abbreviate, $settings['username_space']);
              $password        = $account['pass'];
              $account         = user_save('', $account);
            }

            module_invoke_all('user_import_after_save', $settings, $account, $password, $fields, $updated, $update_setting_per_module);
            $processed_counter++;
          }

          $settings['valid']++;
        }

        // If first line is skipped it doesn't count as processed.
        $settings['processed']++;
      }

      $settings['pointer'] = ftell($handle);

      // save lines that have fatal errors
      if (!empty($errors)) {
        $account_email = isset($account['email']) ? $account['email'] : '';
        _user_import_errors_display_save($settings['import_id'], $fields, $account_email, $errors);
      }
    }

    $settings['setting'] = _user_import_save_progress($settings['setting'], $remaining_data, $settings['pointer'], $settings['processed'], $settings['valid'], $settings['import_id']);
  }

  // Save progress.
  $settings['setting'] = _user_import_save_progress($settings['setting'], $remaining_data, $settings['pointer'], $settings['processed'], $settings['valid'], $settings['import_id'], TRUE);

  if ($settings['setting'] == 'imported') {
    module_invoke_all('user_import_imported', $settings['import_id'], $settings);
  }

  fclose($handle);

  return $settings;
}

// errors for user being imported
function user_import_errors($error = FALSE, $clear = FALSE) {

  static $errors = array();
  if ($clear) $errors = array();
  if ($error) $errors[] = $error;

  return $errors;
}

function _user_import_create_username($order, $data, $abbreviate, $username_space) {

  $username = '';

  if (is_array($order)) {

    asort($order);
    //reset($order);


    //while (list ($file_column, $sequence) = each ($order)) {
    foreach ($order as $file_column => $sequence) {

      if (!empty($username) && !empty($username_space)) {
        $username .= ' ';
      }

      if ($abbreviate[$file_column] == 1) {
        //$username .= trim(drupal_strtoupper(chr(ord($data[$file_column]))));
        $first_character = trim($data[$file_column]);
        $first_character = drupal_substr($first_character, 0, 1);
        $username .= drupal_strtoupper($first_character);
      }
      else {
        $username .= trim($data[$file_column]);
      }

    }
  }

  if (empty($username)) $username = _user_import_random_username();

  $username = _user_import_sanitise_username($username);
  $username = _user_import_unique_username($username, TRUE);

  return $username;
}

/**
 *  conform to Drupal username rules
 */
function _user_import_sanitise_username($username) {

  // username cannot contain an illegal character
  $username = preg_replace('/[^\x80-\xF7 [:alnum:]@_.-]/', '', $username);
  $username = preg_replace(
    '/[\x{80}-\x{A0}' . // Non-printable ISO-8859-1 + NBSP
      '\x{AD}' . // Soft-hyphen
      '\x{2000}-\x{200F}' . // Various space characters
      '\x{2028}-\x{202F}' . // Bidirectional text overrides
      '\x{205F}-\x{206F}' . // Various text hinting characters
      '\x{FEFF}' . // Byte order mark
      '\x{FF01}-\x{FF60}' . // Full-width latin
      '\x{FFF9}-\x{FFFD}' . // Replacement characters
      '\x{0}]/u',
    '', $username);

  // username cannot contain multiple spaces in a row
  $username = preg_replace('/[ ]+/', ' ', $username);

  // username must be less than 56 characters
  $username = substr($username, 0, 56);

  // username cannot begin or end with a space
  $username = trim($username);

  return $username;
}

/**
 *  deal with duplicate usernames
 */
function _user_import_unique_username($username, $start = FALSE) {

  static $suffix = 1;
  if ($start) $suffix = 1;

  if ($suffix < 2) {
    $duplicate = db_query_range('SELECT uid from {users} where name = :name', 0, 1, array(':name' => $username))->fetchField();
  }
  else {
    $duplicate = db_query_range('SELECT uid from {users} where name = :name', 0, 1, array(':name' => "$username $suffix"))->fetchField();
  }

  // loop until name is valid
  if (!empty($duplicate)) {
    $suffix++;

    // If we loop to many times PHP will kill the script,
    // for large user bases that might be a problem with popular names.
    if ($suffix > 10) {
      $suffix = $suffix * mt_rand(10, 99);
    }

    _user_import_unique_username($username);
  }

  // add number at end of username if it already exists
  $username = ($suffix < 2) ? $username : "$username $suffix";

  return $username;
}

// Update settings for existing import
function _user_import_settings_update($pointer, $processed, $valid, $setting, $import_id) {

  if (empty($import_id)) return;

  db_update('user_import')
    ->fields(array(
    'pointer'   => $pointer,
    'processed' => $processed,
    'valid'     => $valid,
    'setting'   => $setting
  ))
    ->condition('import_id', $import_id)
    ->execute();
}

function _user_import_random_username() {
  $username   = '';
  $vowels     = 'aoueiy';
  $consonants = 'bcdfghjklmnpqrstvwxz';
  $length     = 8;

  mt_srand((double)microtime() * 10000000);
  $next_vowel = 0;

  for ($count = 0; $count <= $length; $count++) {

    if ($next_vowel) {
      $rand = mt_rand(0, 5);
      $username .= $vowels{$rand};
      $next_vowel = 0;

    }
    else {
      $rand = mt_rand(0, 19);
      $username .= $consonants{$rand};
      $next_vowel = 1;
    }
  }

  return $username;
}

// check if any updates are to be made
function _user_import_update_user_check($settings) {

  foreach ($settings as $setting) {
    if ($setting != UPDATE_NONE) return TRUE;
  }

  return FALSE;
}

function _user_import_errors_display_save($import_id, $data, $email, $errors) {

  $data['email'] = $email;

  $id = db_insert('user_import_errors')
    ->fields(array(
    'import_id' => $import_id,
    'data'      => serialize($data),
    'errors'    => serialize($errors),
  ))
    ->execute();

  return;
}

/**
 *  Save progress status and counter of the import.
 */
function _user_import_save_progress($status, $remaining_data, $pointer, $processed, $valid, $import_id, $status_check = FALSE) {

  if ($status_check) {
    if ($status == 'import' && !$remaining_data) $status = 'imported';
    if ($status == 'test') $status = 'tested';
  }

  _user_import_settings_update($pointer, $processed, $valid, $status, $import_id);

  return $status;
}

