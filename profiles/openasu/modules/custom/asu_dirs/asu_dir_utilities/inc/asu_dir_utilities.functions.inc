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
    $cache_list = asu_dir_utilities_get_endpoint_list();

    foreach ($cache_list as $cache_item) {
      cache_clear_all($cache_item, 'cache', TRUE);
    }

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

/***
 * Get iSearch data, either form cache, or from endpoint
 *
 * @param $endpoint - the endpoint of the data in isearch, see the constants at the top of asu_dir_utilities.module
 * @param $decode - whether or not to json_decode the item - useful for passing to js
 * @return mixed
 */
function asu_dir_utilities_get_isearch_data($endpoint, $decode = TRUE) {

  $item = NULL;

  $cachename = asu_dir_utilities_get_cache_name($endpoint);

  // Check for cache
  if ($cache = cache_get($cachename)) {
    $item = $cache->data;
  }
  // Create content and cache if no cache available
  else {


    $item = asu_dir_utilities_refresh_dir_item($endpoint, $cachename);
  }

  // decode if option is set
  if (!is_array($item) && $decode) {
    $item = drupal_json_decode($item);
  }

  return $item;
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
        $employee_types = $request->data;
      }

      // Cache employee types for number of hours specified
      if ($employee_types != NULL) {

        $expire_date = time() + 3600 * ASU_DIR_UTILITIES_FORM_CACHE_DURATION;
        cache_set('asu_dir_utilities_employee_types', $employee_types, 'cache', $expire_date);
      }
    }
  }

  // handle legacy config
  if (!is_array($employee_types)) {
    $employee_types = drupal_json_decode($employee_types);
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
        $faculty_titles = $request->data;
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

/****
 * Get local people from iSearch
 * todo:  performance improvement
 * @return array
 */
function asu_dir_utilities_get_local_profile_list() {
  $people_list = &drupal_static(__FUNCTION__);


  //dpm($result);
  //todo: implement caching


  if (!isset($people_list) || $people_list == "") {
    // Check for cache
    if ($cache = cache_get('asu_dir_utilities_people_list')) {
      $people_list = $cache->data;
    }
    // Create content and cache if no cache available
    else {

      /*
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
      }*/

      // pull all imported profiles, which are published
      $query = db_query('SELECT field_data_field_isearch_asurite_id.field_isearch_asurite_id_value AS asurite,  
          node.nid AS nid, 
          node.title AS title,
          tax.name AS facultytitle,
          MIN(field_rank_weight.field_isearch_affil_rank_weight_value) AS rankweight,
          alias.alias AS alias
          FROM node as node 
          LEFT JOIN field_data_field_isearch_affiliations AS field_data_field_isearch_affiliations ON node.nid = field_data_field_isearch_affiliations.entity_id AND field_data_field_isearch_affiliations.entity_type = \'node\'
          INNER JOIN field_collection_item AS affiliations ON field_data_field_isearch_affiliations.field_isearch_affiliations_value = affiliations.item_id
          LEFT JOIN field_data_field_isearch_asurite_id AS field_data_field_isearch_asurite_id ON node.nid = field_data_field_isearch_asurite_id.entity_id AND field_data_field_isearch_asurite_id.entity_type = \'node\'
          LEFT JOIN field_data_field_isearch_affil_rank AS faculty_titles ON affiliations.item_id = faculty_titles.entity_id AND faculty_titles.entity_type = \'field_collection_item\'
          LEFT JOIN field_data_field_isearch_affil_rank_weight AS field_rank_weight ON affiliations.item_id = field_rank_weight.entity_id AND field_rank_weight.entity_type = \'field_collection_item\'
          LEFT JOIN taxonomy_term_data AS tax ON faculty_titles.field_isearch_affil_rank_tid = tax.tid
          Left JOIN url_alias AS alias ON alias.source = CONCAT(\'node/\', node.nid)
          WHERE (( (node.status = \'1\') AND (node.type IN  (\'asu_isearch_profile\')) ))
          GROUP BY node.nid
          ORDER BY rankweight ASC');

      $people_list = $query->fetchAllAssoc('asurite');
      $expire_date = time() + 3600 * ASU_DIR_UTILITIES_FORM_CACHE_DURATION;
      cache_set('asu_dir_utilities_people_list', $people_list, 'cache', $expire_date);
    }
  }

  return $people_list;
}


/****
 * Returns a single Solr record, given an asuriteid
 * @params asurite:  asurite ID of person
 * @return array of Solr data for person
 */
function asu_dir_utilities_get_solr_person($asurite) {

  if ($asurite != NULL) {
    $endpoint = ASU_DIR_UTILITIES_SOLR_ENV . 'select?q=asuriteId:' . $asurite . '&wt=json';
    $request = drupal_http_request($endpoint);

    if ($request->code == 200) {
      $data = json_decode($request->data, TRUE);
      $data = $data['response']['docs'];

      if (!empty($data)) {
        return $data[0];
      }
    }
  }

  return NULL;
}


/************************
 * Tree Helper Functions
 ***********************/

/**
 * Returns the node (and all children) where (node.nid == @param nid )
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


/**
 * Cache items from endpoints in iSearch
 *
 * @param $endpoint
 * @param $cachename
 **/
function asu_dir_utilities_refresh_dir_item($endpoint) {

  //set timeout of request to 60 seconds
  $options = array(
    'timeout' => 60,
  );

  $cachename = asu_dir_utilities_get_cache_name($endpoint);

  //Refresh and cache the Tree
  $item = NULL;

  $request = drupal_http_request($endpoint, $options);

  if ($request->code == 200) {
    $item = $request->data;
  }

  // Create cache, set to hold cache for number of hours specified
  if ($item != NULL) {
    $expire_date = time() + 3600 * ASU_DIRECTORY_FORM_CACHE_DURATION;
    cache_set($cachename, $item, 'cache', $expire_date);
  }

  return $item;
}

/**
 * Check if Solr is in good health
 * -- do the Solr health check
 *
 * @boolean - is Solr healthy right now
 */
function asu_dir_utilities_solr_health_check() {
  $health_check_endpoint = ASU_DIR_UTILITIES_ISEARCH_URL . '/endpoints/solr-health-check';
  $check = drupal_http_request($health_check_endpoint);

  if (!empty($check) && $check->code == 200) {
    $data = drupal_json_decode($check->data);
    if (isset($data['lock_status'])) {

      // if it is locked, then it is not healthy
      return !$data['lock_status'];
    }
  }

  return FALSE;
}


