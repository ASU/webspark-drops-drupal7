<?php

/*********************************************************************
 * UTILITY FUNCTIONS
 *********************************************************************/


/**
 * Clear tree and employee types from cache
 *
 * @param $test
 *
 * @return bool
 */
function asu_dir_clear_cache($test) {
  // $test should determine whether or not this is the initial page load
  if ($test) {
    drupal_set_message(t('Caches for this module have been cleared.'));
    cache_clear_all('asu_directory_tree', 'cache', TRUE);
    return FALSE;
  }
}


/**
 * Helper function to get the header column widths
 * used on the iSearch directory list view.
 */
function asu_dir_get_view_column_widths(stdClass $display_options) {
  $columns = [
    'photo' => 2,
    'name' => 4,
    'contact' => 3,
    'expertise' => 3,
  ];

  if (!$display_options->display_photo) {
    $columns['name'] += $columns['photo'];
    $columns['photo'] = 0;
  }

  if (!$display_options->display_expertise) {
    $columns['name'] += ($columns['expertise'] - 1);
    $columns['contact'] += 1;
    $columns['expertise'] = 0;
  }

  if (!$display_options->display_name) {
    $columns['contact'] += $columns['name'];
    $columns['name'] = 0;
  }

  if (!$display_options->display_contact) {
    $columns['name'] += ($columns['contact'] - 1);
    $columns['expertise'] += 1;
  }

  return $columns;
}


/**
 * Helper function to check for valid building codes
 */
/*
function asu_dir_fetch_asu_building_code($code) {
  $building_code = check_plain(trim($code));

  if (in_array(strtoupper($building_code), array('FULTON CENTER', 'FULTON'))) {
    $building_code = 'FULTN';
  }

  if ($has_building_code = preg_match('/^[0-9A-Z]{2,5}$/', strtoupper($building_code))) {

    return $building_code;
  }

  return FALSE;
}
*/

/**
 * Helper function to load react library locally if module isn't present
 */
/*
function asu_dir_load_js() {
  if (!module_exists('react')) {
    drupal_add_js(drupal_get_path('module', 'asu_dir') . '/vendor/react/build/react.js');
    drupal_add_js(drupal_get_path('module', 'asu_dir') . '/vendor/react/build/react-dom.js');
  }
}*/

/**
 * Helper function for backwards compatibility when retrieving tenure display
 * setting
 */
function asu_dir_get_tenure_config($setting) {
  if (!is_object($setting)) {
    return $setting;
  }

  $tenure_display = 'Both';

  $tenure_display_values = [];
  foreach ($setting as $key => $value) {
    if ($value == 1) {
      $tenure_display_values[] = $key;
    }
  }

  if (count($tenure_display_values) == 1) {
    $tenure_display = $tenure_display_values[0];
  }

  return $tenure_display;
}


/**
 * Returns the
 */
function asu_dir_get_dept_config() {
  $default_feed_dept = [
    'items' => [],
    'options' => [],
  ];

  return variable_get('isearch_admin_feed_dept', json_encode($default_feed_dept));
}

