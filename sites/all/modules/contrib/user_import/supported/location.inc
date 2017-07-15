<?php

// Functionality depends on User Location.
if (module_exists('location_user')) {

  /**
   * Implementation of hook_user_import_form_field_match(). Add supported Location fields into our dropdown list.
   */
  function location_user_import_form_field_match() {
    $options             = array();
    $options['location'] = location_field_names();

    return $options;
  }

  /**
   * Implementation of hook_user_import_form_update_user().
   */
  function location_user_import_form_update_user() {
    $form['location'] = array(
      'title'       => t('Location'),
      'description' => t('Affected: fields in user Location.'),
    );

    return $form;
  }

  /**
   * Implementation of hook_user_import_data().
   */
  function location_user_import_data($settings, $update_setting, $column_settings, $module, $field_id, $data, $column_id) {
    if ($module != 'location') {
      return;
    }
    if (empty($data[$column_id])) {
      $defaults         = location_locationapi($data, 'defaults');
      $data[$column_id] = $defaults[$field_id]['default'];
    }
    switch ($field_id) {
      case 'country':
        $country = location_country_name($data[$column_id]);
        if ($country != '') {
          return trim($data[$column_id]);
        }
        else {
          $countries = location_get_iso3166_list();
          if ($country = array_search($data[$column_id], $countries)) {
            if ($country !== FALSE) {
              return $country;
            }
          }
        }

        user_import_errors(t('Invalid country'));

        return trim($data[$column_id]);

      case 'province':
        if (!empty($data['country'])) {
          if (!empty($data[$column_id])) {
            $provinces = location_get_provinces($data['country']);
            $found     = FALSE;
            $province  = strtoupper($data['province']);
            foreach ($provinces as $key => $value) {
              if ($province == strtoupper($key) || $province == strtoupper($value)) {
                $found = TRUE;
                break;
              }
            }
            if (!$found) {
              user_import_errors(t('Province not found'));
            }

            return trim($data[$column_id]);
          }
        }

        return trim($data[$column_id]);

      default:
        return trim($data[$column_id]);
    }
  }

  /**
   * Implementation of hook_user_import_after_save().
   */
  function location_user_import_after_save($settings, $account, $password, $fields, $updated, $update_setting_per_module) {
    if (!is_array($fields['location'])) {
      return;
    }
    // check if it's an existing user and if location is to be updated
    if ($updated && $update_setting_per_module['location'] == UPDATE_NONE) {
      return;
    }
    // Arrange values for location array
    $location = array();

    foreach ($fields['location'] as $column_id => $column_data) {
      $location[0][$column_id] = $column_data[0];
    }
    // Merge defaults in
    $dummy    = array();
    $defaults = location_invoke_locationapi($dummy, 'defaults');

    foreach ($defaults as $key => $value) {
      if (!isset($location[0][$key])) {
        $location[0][$key] = $value['default'];
      }
    }

    location_save_locations($location, array('uid' => $account->uid));

    return;
  }

}

