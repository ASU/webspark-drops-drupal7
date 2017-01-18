<?php

/*********************************************************************
 * UTILITY FUNCTIONS
 *********************************************************************/


/**
 * Clear tree and employee types from cache
 *
 * @param $test
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
  $columns = array(
    'photo' => 2,
    'name' => 4,
    'contact' => 3,
    'expertise' => 3,
  );

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
 * Helper function to get the default configuration
 * used for an ASU Directory field type.
 *
 * This will help avoid undefined warnings when new options added
 */
function asu_dir_get_default_config() {

  $depts = new stdClass();
  $depts->items = array();
  $depts->options = new stdClass();

  return array(

    "show_tree" => FALSE,
    "new_tab" => FALSE,
    "show_managers" => FALSE,
    "show_breadcrumbs" => FALSE,
    "dept_id" => "",
    "employee_types" => array('All'),
    "breadcrumb" => "",
    "use_custom_q" => 0,
    "custom_q" => array(
      "q" => "",
      "fq" => ""
    ),
    'display_type' => 'list',
    //'employee_type_exclude' => FALSE,
    'tenure_display' => 'Both',
    'show_filters' => TRUE,
    'include_subdepts' => FALSE,
    'pager_display' => 'paged',
    'pager_items_per_page' => 10,
    'expertise_areas' => '',
    'display_short_bio' => FALSE,
    'display_header' => TRUE,
    'display_photo' => TRUE,
    'display_name' => TRUE,
    'display_contact' => TRUE,
    'display_expertise' => FALSE,
    'display_building' => FALSE,
    'display_room' => FALSE,
    'default_sort_by' => 'tsort',
    'filter_title' => '',
    'show_filter_faculty_titles' => FALSE,
    'show_filter_titles' => TRUE,
    'show_filter_omni' => TRUE,
    'show_filter_expertise' => TRUE,
    'hide_filter_rank_sort' => FALSE,
    'show_az_index' => TRUE,
    //todo:  how to do this with Solr?
    //'link_building_codes' => variable_get('isearch_link_buildings', FALSE),
    'depts' => $depts,
    'top_level_ids' => array(
      'top_level_psid' => ASU_DIRECTORY_TOP_LEVEL_PS_ID,
      'top_level_nid' => ASU_DIRECTORY_TOP_LEVEL_DEPT_NID
    )
  );
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
 * Helper function for backwards compatibility when retrieving tenure display setting
 */
function asu_dir_get_tenure_config($setting) {
  if (!is_object($setting)) {
    return $setting;
  }

  $tenure_display = 'Both';

  $tenure_display_values = array();
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
  $default_feed_dept = array(
    'items' => array(),
    'options' => array(),
  );

  return variable_get('isearch_admin_feed_dept', json_encode($default_feed_dept));
}

/**
 * Helper function to test for devmode
 */
function asu_dir_devmode() {
  return (bool) variable_get('asu_dir_devmode', FALSE);
}

