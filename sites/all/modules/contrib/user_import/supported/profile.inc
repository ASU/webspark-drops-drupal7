<?php

/**
 * Implementation of hook_user_import_form_field_match().
 */
function profile_user_import_form_field_match() {
  module_load_include('inc', 'user_import', 'user_import.admin');
  $fields             = _user_import_profile('fid', 'title');
  $options['profile'] = $fields;

  return $options;
}

/**
 * Implementation of hook_user_import_form_update_user().
 */
function profile_user_import_form_update_user() {
  $form['profile'] = array('title' => t('Profile'), 'description' => t('Affected: Profile fields.'));

  return $form;
}

/**
 * Implementation of hook_user_import_data().
 */
function profile_user_import_data($settings, $update_setting, $column_settings, $module, $field_id, $data, $column_id) {

  if ($module != 'profile') return;

  return trim($data[$column_id]);
}

/**
 * Implementation of hook_user_import_after_save().
 */
function profile_user_import_after_save($settings, $account, $password, $fields, $updated, $update_setting_per_module) {

  // get all fields
  $profile_fields = profile_get_fields();
  $data           = $old_data = unserialize($account->data);

  foreach ($profile_fields as $field) {
    profile_user_import_save_profile($field, $account->uid, $fields['profile'][$field->fid][0], $updated, $update_setting_per_module['profile'], $data);
  }

  // data column in the user table needs to be updated
  if ($data != $old_data) {

    db_update('users')
      ->fields(array('data' => serialize($data)))
      ->condition('uid', $account->uid)
      ->execute();
  }

  return;
}


function profile_user_import_save_profile($field, $uid, $value, $updated, $update_setting, &$data) {

  // when the profile field is displayed on the registration form an empty value is automatically saved by the Profile module
  $exists = db_query_range('SELECT value FROM {profile_values} WHERE fid = :fid AND uid = :uid', 0, 1, array(':fid' => $field->fid, ':uid' => $uid))->fetchField();

  user_import_profile_date($value, $field->type);

  if ($updated) {

    switch ($update_setting) {
      case UPDATE_NONE:
        return;

      case UPDATE_ADD:
        if (empty($value) || (!empty($exists) && $exists != '')) return;

      case UPDATE_REPLACE:

        if (empty($value) && $update_setting == UPDATE_REPLACE) {

          db_query("DELETE FROM {profile_values} WHERE fid = :fid AND uid = :uid", array(':fid' => $field->fid, ':uid' => $uid));
          unset($data[$field->name]);

          return;
        }

        if ((empty($exists) && $exists != '') || $exists === FALSE) {

          $id = db_insert('profile_values')
            ->fields(array(
            'fid'   => $field->fid,
            'uid'   => $uid,
            'value' => $value,
          ))
            ->execute();
        }
        else {

          $id = db_update('profile_values')
            ->fields(array(
            'value' => $value,
          ))
            ->condition('fid', $field->fid)
            ->condition('uid', $uid)
            ->execute();
        }

        $data[$field->name] = $value;

        return;
    }

  }
  else {

    if (empty($value)) return;

    if ((empty($exists) && $exists != '') || $exists === FALSE) {

      $id = db_insert('profile_values')
        ->fields(array('fid' => $field->fid, 'uid' => $uid, 'value' => $value))
        ->execute();

    }
    else {

      db_update('profile_values')
        ->fields(array('value' => $value))
        ->condition('fid', $field->fid)
        ->condition('uid', $uid)
        ->limit(1)
        ->execute();

      $data[$field->name] = $value;
    }
  }

  return;
}


/**
 *
 */
function profile_get_fields() {

  static $fields = array();

  // Avoid making more than one database call for profile info.
  if (empty($fields)) {
    $results = db_query('SELECT * FROM {profile_field}');

    foreach ($results as $row) {
      $fields[] = $row;
    }
  }

  return $fields;
}

/**
 * Convert date into format that Profile module expects:
 * a:3:{s:5:"month";s:1:"1";s:3:"day";s:1:"1";s:4:"year";s:4:"1976";}
 */
function user_import_profile_date(&$value, $field_type) {

  if ($field_type != "date" || empty($value)) {
    return;
  }

  $date = explode('/', $value);

  if (!is_array($date)) {
    return;
  }

  // Get seleceted format.
  $date_format = variable_get('user_import_profile_date_format', 'MM/DD/YYYY');

  if ($date_format == 'MM/DD/YYYY') {
    list($month, $day, $year) = explode('/', $value);
  }
  else {
    if ($date_format == 'DD/MM/YYYY') {
      list($day, $month, $year) = explode('/', $value);
    }
    else {
      if ($date_format == 'YYYY/MM/DD') {
        list($year, $month, $day) = explode('/', $value);
      }
      else {
        if ($date_format == 'YYYY/DD/MM') {
          list($year, $day, $month) = explode('/', $value);
        }
      }
    }
  }

  // Leading zeros cause a problem so remove them.
  if (substr($day, 0, 1) == '0') {
    $day = substr($day, 1, 1);
  }
  if (substr($month, 0, 1) == '0') {
    $month = substr($month, 1, 1);
  }

  $value = serialize(array('month' => $month, 'day' => $day, 'year' => $year));
}
