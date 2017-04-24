<?php

/**
 * Implements hook_admin()
 * Creates a form for setting the root for the department hierarchy by department ID
 */
function asu_dir_utilities_admin($form, &$form_state) {
  $form = array();

// Environment to determine which Solr Server URL to access
// (Actual URLs supplied by WSI Settings Endpoint based on chosen environment)
  $form['asu_dir_utilities_isearch_url'] = array(
    '#type' => 'textfield',
    '#title' => 'Directory URL (iSearch)',
    '#default_value' => ASU_DIR_UTILITIES_ISEARCH_URL,
    '#description' => t('URL of iSearch directory.'),
    '#required' => TRUE,
  );

  $form['asu_dir_utilities_solr_env'] = array(
    '#type' => 'textfield',
    '#title' => 'Solr Environment',
    '#default_value' => ASU_DIR_UTILITIES_SOLR_ENV,
    '#description' => t('The Solr server you would like to pull data from.'),
    '#required' => TRUE,
  );

  $form['asu_dir_utilities_solr_schema_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => 'Solr Schema Endpoint',
    '#default_value' => ASU_DIR_UTILITIES_SOLR_SCHEMA_ENDPOINT,
    '#description' => t('The Solr schema endpoint.'),
    '#required' => TRUE,
  );

  $form['asu_dir_utilities_tree_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => 'ASU Directory Tree Endpoint',
    '#default_value' => ASU_DIR_UTILITIES_TREE_ENDPOINT,
    '#description' => t('The URL of the directory tree endpoint.'),
    '#required' => TRUE,
  );

  $form['asu_dir_utilities_feed_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => 'ASU iSearch Directory Feed Endpoint',
    '#default_value' => ASU_DIR_UTILITIES_FEED_ENDPOINT,
    '#description' => t('The URL of the iSearch directory feed endpoint.'),
    '#required' => TRUE,
  );

  $form['asu_dir_utilities_employee_types_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => 'ASU Employee Types Endpoint',
    '#default_value' => ASU_DIR_UTILITIES_EMPLOYEE_TYPES_ENDPOINT,
    '#description' => t('The URL of the employee types endpoint.'),
    '#required' => TRUE,
  );

  $form['asu_dir_utilities_faculty_titles_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => 'ASU Faculty Titles Endpoint',
    '#default_value' => ASU_DIR_UTILITIES_FACULTY_TITLES_ENDPOINT,
    '#description' => t('The URL of the faculty titles endpoint.'),
    '#required' => TRUE,
  );

  $form['asu_dir_utilities_form_clear_cache'] = array(
    '#type' => 'button',
    '#value' => 'Clear caches for this module',
// Send in part of the form_state array to know if this is initial page load or not
    '#click' => asu_dir_utilities_clear_cache($form_state['buttons']),
  );


  $form['#submit'][] = "asu_dir_utilities_admin_submit";
  return system_settings_form($form);
}


/**
 * Set configuration variables for asu_dir_utilities module
 */
function asu_dir_utilities_admin_submit($form, &$form_state) {
  /*maybe clear the cache after submitting*/
  variable_set('asu_dir_utilities_solr_endpoint', $form['asu_dir_utilities_solr_env']['#value']);
  variable_set('asu_dir_utilities_tree_endpoint', $form['asu_dir_utilities_tree_endpoint']['#value']);
  variable_set('asu_dir_utilities_feed_endpoint', $form['asu_dir_utilities_feed_endpoint']['#value']);
  variable_set('asu_dir_utilities_employee_types_endpoint', $form['asu_dir_utilities_employee_types_endpoint']['#value']);
  variable_set('asu_dir_utilities_isearch_url', $form['asu_dir_utilities_isearch_url']['#value']);
  variable_set('asu_dir_utilities_faculty_titles_endpoint', $form['asu_dir_utilities_faculty_titles_endpoint']['#value']);
  variable_set('asu_dir_utilities_solr_schema_endpoint', $form['asu_dir_utilities_solr_schema_endpoint']['#value']);

}


/****
 *  CONFIGURATION FUNCTIONs
 */


/****
 * Returns a list of endpoints mapped to cache names
 */
function asu_dir_utilities_get_endpoint_list($backup = FALSE) {


  if ($backup === TRUE) {

    // return the backup json file endpoints
    $endpoints = array(
      ASU_DIR_UTILITIES_EMPLOYEE_TYPES_ENDPOINT => ASU_DIR_UTILITIES_EMPLOYEE_TYPES_BACKUP,
      ASU_DIR_UTILITIES_TREE_ENDPOINT => ASU_DIR_UTILITIES_TREE_BACKUP,
      ASU_DIR_UTILITIES_FACULTY_TITLES_ENDPOINT => ASU_DIR_UTILITIES_FACULTY_TITLES_BACKUP
    );
  }
  else {
    $endpoints = array(
      ASU_DIR_UTILITIES_EMPLOYEE_TYPES_ENDPOINT => 'asu_dir_utilities_employee_types_endpoint',
      ASU_DIR_UTILITIES_TREE_ENDPOINT => 'asu_dir_utilities_directory_tree',
      ASU_DIR_UTILITIES_FACULTY_TITLES_ENDPOINT => 'asu_dir_utilities_faculty_titles',
      ASU_DIR_UTILITIES_SOLR_SCHEMA_ENDPOINT => 'asu_dir_utilities_solr_schema'
    );
  }


  return $endpoints;
}


/***
 * Returns the cache name for a particular endpoint
 *
 * @param $endpoint
 */
function asu_dir_utilities_get_cache_name($endpoint) {

  $cache_names = asu_dir_utilities_get_endpoint_list();

  if (isset($cache_names[$endpoint])) {
    return $cache_names[$endpoint];
  }
  else {
    return NULL;
  }
}

/**
 * Helper function to get the default configuration
 * used for an ASU Directory field.
 *
 * This sets sane defaults
 */
function asu_dir_utilities_get_default_config($type = 'asu_dir') {

  $depts = array();
  $depts['items'] = array();

  // note: options needs to be an object in our model, since
  // we are using numeric 'keys' (properties) in order to store options
  // for each dept
  $depts['options'] = new stdClass();

  $tsort_field = ASU_DIR_UTILITIES_TITLESORT_FIELD;

  if ($type == 'asu_isearch') {
    $tsort_field = 'field_isearch_affil_rank_weight_value';
  }

  return array(
    "type" => 'asu_dir',
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
    'local_tags' => array(),
    'display_short_bio' => FALSE,
    'display_header' => TRUE,
    'display_photo' => TRUE,
    'display_name' => TRUE,
    'display_contact' => TRUE,
    'display_expertise' => FALSE,
    'display_building' => FALSE,
    'display_room' => FALSE,
    'default_sort_by' => $tsort_field,
    'filter_title' => '',
    'show_filter_faculty_titles' => FALSE,
    'show_filter_titles' => TRUE,
    'show_filter_omni' => TRUE,
    'show_filter_expertise' => TRUE,
    'hide_filter_rank_sort' => FALSE,
    'show_az_index' => TRUE,
    'default_rank_mode' => 'isearch',
    'depts' => $depts,
    'top_level_ids' => array(
      'top_level_psid' => ASU_DIR_UTILITIES_TOP_LEVEL_PS_ID,
      'top_level_nid' => ASU_DIR_UTILITIES_TOP_LEVEL_DEPT_NID
    ),
    'always_display_view' => FALSE,
    // asu_isearch_specific
    'show_filter_sort' => TRUE,
    'view_display' => 'isearch_directory:isearch_directory_list',
    'link_building_codes' => variable_get('isearch_link_buildings', FALSE),
  );


  /*  ASU_ISEARCH ORIGINAL CONFIGS
  return array(
    'employee_types' => array('All'),
    'employee_type_exclude' => 0,
    'tenure_display' => 0,
    'show_managers' => 0,
    'show_filters' => 1,
    'include_subdepts' => 0,

    'pager_display' => 'paged',
    'pager_items_per_page' => 10,
    'pager_offset' => 0,
    'expertise_areas' => array(),
    'local_tags' => array(),
    'display_short_bio' => TRUE,
    'display_header' => TRUE,
    'display_photo' => TRUE,
    'display_name' => TRUE,
    'display_contact' => TRUE,
    'display_expertise' => TRUE,
    'display_building' => TRUE,
    'display_room' => TRUE,
    'default_sort_by' => 'field_isearch_affil_rank_weight_value',
    'filter_title' => '',
    'show_filter_titles' => TRUE,
    'show_filter_omni' => TRUE,
    'show_filter_expertise' => TRUE,

    'show_az_index' => FALSE,

    'depts' => $depts,
  );*/
}

function asu_dir_utilites_get_view_sort($sort) {
  $sorts = array(
    'tsort' => 'field_isearch_affil_rank_weight_value',
    'lastNameSort' => 'field_isearch_lastname_value',
    'firstNameSort' => 'field_isearch_firstname_value'
  );

  return $sorts[$sort];

}
