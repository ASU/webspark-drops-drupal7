<?php


/**
 * Clear tree and employee types from cache
 *
 * @param $test
 * @return bool
 */
function asu_dir_utilities_clear_cache($test) {
  // $test should determine whether or not this is the initial page load
  if ($test) {
    drupal_set_message(t('Caches for this module have been cleared.'));
    cache_clear_all('asu_dir_utilities_directory_tree', 'cache', TRUE);
    cache_clear_all('asu_dir_utilities_employee_types', 'cache', TRUE);
    cache_clear_all('asu_dir_utilities_faculty_titles', 'cache', TRUE);
    cache_clear_all('asu_dir_utilities_people_list', 'cache', TRUE);
    return FALSE;
  }
}


/***
 * Get the department hierarchy tree
 */
function asu_dir_utilities_get_dept_tree() {

  $tree = &drupal_static(__FUNCTION__);

  if (!isset($tree) || $tree == "") {
    // Check for cache
    if ($cache = cache_get('asu_dir_utilities_directory_tree')) {
      $tree = $cache->data;
    }
    // Create content and cache if no cache available
    else {

      //set timeout of request to 60 seconds
      $options = array(
        'timeout' => 60,
      );

      //Get the tree and cache
      $tree_endpoint = ASU_DIR_UTILITIES_TREE_ENDPOINT;
      $request = drupal_http_request($tree_endpoint, $options);

      if ($request->code == 200) {
        $tree = $request->data;
      }

      // Create cache, set to hold cache for number of hours specified
      if ($tree != NULL) {
        $set_date = time();
        $expire_date = time() + 3600 * ASU_DIR_UTILITIES_FORM_CACHE_DURATION;
        cache_set('asu_dir_utilities_directory_tree', $tree, 'cache', $expire_date);
      }
    }
  }

  return $tree;
}

/**
 * Get the employee types from the endpoint, or from cache
 *
 * @return mixed An array of employee types
 */
function asu_dir_utilities_get_employee_types() {

  $employee_types = &drupal_static(__FUNCTION__);

  if (!isset($employee_types) || $employee_types == "") {
    // Check for cache
    if ($cache = cache_get('asu_dir_utilities_employee_types')) {
      $employee_types = $cache->data;
    }
    // Create content and cache if no cache available
    else {

      //set timeout of request to 60 seconds
      $options = array(
        'timeout' => 60,
      );

      $endpoint = ASU_DIR_UTILITIES_EMPLOYEE_TYPES_ENDPOINT;
      $request = drupal_http_request($endpoint, $options);

      if ($request->code == 200) {
        $types = $request->data;
        $employee_types = drupal_json_decode($types);
      }

      // Cache employee types for number of hours specified
      if ($employee_types != NULL) {

        $expire_date = time() + 3600 * ASU_DIR_UTILITIES_FORM_CACHE_DURATION;
        cache_set('asu_dir_utilities_employee_types', $employee_types, 'cache', $expire_date);
      }
    }
  }

  return $employee_types;
}


/**
 * Get the employee types from the endpoint, or from cache
 *
 * @return mixed An array of employee types
 */
function asu_dir_utilities_get_faculty_titles() {

  $faculty_titles = &drupal_static(__FUNCTION__);

  if (!isset($faculty_titles) || $faculty_titles == "") {
    // Check for cache
    if ($cache = cache_get('asu_dir_utilities_faculty_titles')) {
      $faculty_titles = $cache->data;
    }
    // Create content and cache if no cache available
    else {

      //set timeout of request to 60 seconds
      $options = array(
        'timeout' => 60,
      );

      $endpoint = ASU_DIR_UTILITIES_FACULTY_TITLES_ENDPOINT;
      $request = drupal_http_request($endpoint, $options);

      if ($request->code == 200) {
        $types = $request->data;
        $faculty_titles = drupal_json_decode($types);
      }

      // Cache employee types for number of hours specified
      if ($faculty_titles != NULL) {

        $expire_date = time() + 3600 * ASU_DIR_UTILITIES_FORM_CACHE_DURATION;
        cache_set('asu_dir_utilities_faculty_titles', $faculty_titles, 'cache', $expire_date);
      }
    }
  }

  return $faculty_titles;
}


/**
 * Get the SOLR schema from the endpoint, or from cache
 *
 * @return mixed An array of employee types
 */
function asu_dir_utilities_get_solr_schema() {

  $solr_schema = &drupal_static(__FUNCTION__);

  if (!isset($solr_schema) || $solr_schema == "") {
    // Check for cache
    if ($cache = cache_get('asu_dir_utilities_solr_schema')) {
      $solr_schema = $cache->data;
    }
    // Create content and cache if no cache available
    else {

      //set timeout of request to 60 seconds
      $options = array(
        'timeout' => 60,
      );

      $endpoint = ASU_DIR_UTILITIES_SOLR_SCHEMA_ENDPOINT;
      $request = drupal_http_request($endpoint, $options);

      if ($request->code == 200) {
        $types = $request->data;
        $solr_schema = drupal_json_decode($types);
      }

      // Cache employee types for number of hours specified
      if ($solr_schema != NULL) {

        $expire_date = time() + 3600 * ASU_DIR_UTILITIES_FORM_CACHE_DURATION;
        cache_set('asu_dir_utilities_solr_schema', $solr_schema, 'cache', $expire_date);
      }
    }
  }

  return $solr_schema;
}

function asu_dir_utilities_get_local_profile_list() {
  $people_list = &drupal_static(__FUNCTION__);

  if (!isset($people_list) || $people_list == "") {
    // Check for cache
    if ($cache = cache_get('asu_dir_utilities_people_list')) {
      $people_list = $cache->data;
    }
    // Create content and cache if no cache available
    else {

      //set timeout of request to 60 seconds
      $options = array(
        'timeout' => 60,
      );

      $nodes = node_load_multiple(array(), array('type' => 'asu_isearch_profile'));

      $people_list = array();

      foreach($nodes as $node) {
       if (isset($node->field_isearch_asurite_id['und'][0]['value'])) {
         $asurite = $node->field_isearch_asurite_id['und'][0]['value'];
         $people_list[$asurite] = drupal_get_path_alias('node/' .$node->nid);

       }
      }

      // Cache employee types for number of hours specified
     if (!empty($people_list)) {

        $expire_date = time() + 3600 * ASU_DIR_UTILITIES_FORM_CACHE_DURATION;
        cache_set('asu_dir_utilities_people_list', $people_list, 'cache', $expire_date);
      }
    }
  }

  return $people_list;
}


/****
 * Returns a single Solr record
 * @params asurite:  asurite ID of person
 * @return array of Solr data for person
 */
function asu_dir_utilities_get_solr_person($asurite) {
    $endpoint = ASU_DIR_UTILITIES_SOLR_ENV;


}


/************************
 * Tree Helper Functions
 ***********************/

/**
 * Returns the node (and all children) where (node.tid == @param tid )
 * @param {Object} data
 *  Nested JSON object with department data
 * @param {integer} dept_id
 *  ID of the department that should be the root of the hierarchy
 */
function asu_dir_utilities_dept_find_root($data, $dept_id, $lookup = 'dept_nid') {
  $success = array();

  for ($i = 0; $i < count($data); $i++) {
    if (count($success) == 0 && $data[$i] != NULL) {
      if ($data[$i]->$lookup == $dept_id) {
        return $data[$i];
      }
      else {
        if (isset($data[$i]->children)) {
          $success = asu_dir_utilities_dept_find_root($data[$i]->children, $dept_id, $lookup);
        }
      }
    }
    else {
      break;
    }
  }
  return $success;
}

/**
 * Saves the ids of all departments under currently selected tree on #people's data object
 * @param {object}
 *  Nested JSON object with department data
 */
function asu_dir_utilities_dept_get_tree_data($tree, $tree_ids = array()) {

  $newItem = new stdClass();
  $newItem->name = $tree->name;
  $newItem->dept_nid = $tree->dept_nid;

  $tree_ids[] = $newItem;

  for ($i = 0; $i < count($tree->children); $i++) {
    $tree_ids = asu_dir_utilities_dept_get_tree_data($tree->children[$i], $tree_ids);
  }

  return $tree_ids;
}


/**
 * Returns an array of department nids, given the department tree
 *
 * @param $tree
 * @param array $tree_ids
 * @return array
 */
function asu_dir_utilities_dept_get_tree_nids($tree, $tree_ids = array()) {


  if (isset($tree->dept_nid)) {
    $newItem = $tree->dept_nid;

    $tree_ids[] = $newItem;
  }

  if (isset($tree->children)) {
    for ($i = 0; $i < count($tree->children); $i++) {
      $tree_ids = asu_dir_utilities_dept_get_tree_data($tree->children[$i], $tree_ids);
    }
  }

  return $tree_ids;
}
