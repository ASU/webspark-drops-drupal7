<?php
/**
 * cron implementations
 */


/**
 * Implements hook_cron().
 */
function asu_isearch_cron() {

  // if we are locked from automatic update, then return false without updating
  $lock = variable_get('isearch_local_lock', FALSE);

  if ($lock) {
    return FALSE;
  }

  // it takes too much time to do both of these actions every cron run.
  // so switch between caching depts and migrating departments.
  $last_action = variable_get('asu_isearch_cron_action', 'import_depts');

  if ($last_action == 'import_depts') {
    // Cache dept tree and employee types data
    variable_set('asu_isearch_cron_action', 'cache_depts');
    _asu_isearch_cache_dept_feed(TRUE);
  }
  else {
    // Begin profile migrations
    variable_set('asu_isearch_cron_action', 'import_depts');
    _asu_isearch_begin_migrate(FALSE);
  }

  // cleanup any profiles which are not found in Solr
  _asu_isearch_cleanup();

  // Clear cache, and cleanup profile image caches
  $last_clean = variable_get('last_profile_cleanup', NULL);

  if ($last_clean != date('ymd', time())) {

    variable_set('last_profile_cleanup', date('ymd', time()));

    // flush the image styles cache, so that updated photos show up
    $styles = array('asu_isearch_profile_list', 'asu_isearch_profile');

    foreach ($styles as $style) {
      $the_style = image_style_load($style);
      asu_isearch_image_style_flush($the_style);
    }

    // clear all cached content
    cache_clear_all();
  }
}

/**
 * Flushes cached media for a style.
 *
 * @param $style
 *   An image style array.
 */
function asu_isearch_image_style_flush($style) {
  // Delete the style directory in each registered wrapper.
  $wrappers = file_get_stream_wrappers(STREAM_WRAPPERS_WRITE_VISIBLE);
  foreach ($wrappers as $wrapper => $wrapper_data) {
    if (file_exists($directory = $wrapper . '://styles/' . $style['name'])) {
      file_unmanaged_delete_recursive($directory);
    }
  }

  // Clear image style and effect caches.
  cache_clear_all('image_styles', 'cache');
  cache_clear_all('image_effects:', 'cache', TRUE);
  drupal_static_reset('image_styles');
  drupal_static_reset('image_effects');

  // Clear field caches so that formatters may be added for this style.
  field_info_cache_clear();
  drupal_theme_rebuild();

  // Clear page caches when flushing.
  if (module_exists('block')) {
    cache_clear_all('*', 'cache_block', TRUE);
  }
  cache_clear_all('*', 'cache_page', TRUE);
}

/**
 * Implements hook_cron_queue_info().
 */
function asu_isearch_cron_queue_info() {
  $queues['isearch_fetch_profile_photo'] = array(
    'worker callback' => 'asu_isearch_fetch_profile_photo',
    'time' => 120,
  );

  $queues['isearch_fetch_department'] = array(
    'worker callback' => 'asu_isearch_fetch_departments',
    'time' => 120,
  );

  $queues['isearch_clean_profiles'] = array(
    'worker callback' => 'asu_isearch_cleanup_profile',
    'time' => 120,
  );

  return $queues;
}


/**
 * Cron queue worker callback for fetching department profiles
 */
function asu_isearch_fetch_departments($data) {
  // feed endpoint
  $source_urls = array($data['endpoint']);

  $migration = _asu_isearch_get_migration();


  $migration->setMigrateSource($source_urls);
  // begin the migration
  $update = $migration->prepareUpdate();
  $result = $migration->processImport($data);
}


/**
 * Cron queue worker callback for fetching profile photos
 */
function asu_isearch_fetch_profile_photo($data) {
  $photo_url = $data['photo_url'];
  $destination = $data['destination'];

  $entity = current(entity_load('node', array($data['entity'])));

  if (!$entity) {
    return;
  }

  // ensure the file is truly accessible
  $response = drupal_http_request($photo_url);
  if ($response->code == 200) {

    $file = FALSE;
    $photo_exists = file_exists($destination);

    // does the file already exist on the server?
    // if yes, associate it
    if ($photo_exists) {
      $file = current(entity_load('file', array(), array('uri' => $destination . '')));
    }

    if (!$photo_exists || filesize($destination) != $response->headers['content-length']) {
      $file = system_retrieve_file($photo_url, $destination, TRUE, $replace = FILE_EXISTS_REPLACE);
    }

    if ($file) {
      // Load the node so we can set
      $entity->field_isearch_photo_url[LANGUAGE_NONE][0]['fid'] = $file->fid;
      node_save($entity);
    }
  }
}

/**
 * Iterate over a number of profiles to check whether to unpublish or not
 *
 */
function _asu_isearch_cleanup() {

  // get the cleanup list, remove some items for pros, reset list,
  // and queue those to be checked
  $clean_list = _asu_isearch_get_cleanup_list();
  $to_process = array_slice($clean_list, 0, ASU_ISEARCH_PROFILE_CLEANUP_LIMIT);
  $clean_list = array_slice($clean_list, ASU_ISEARCH_PROFILE_CLEANUP_LIMIT);
  variable_set('asu_isearch_cleanup_list', json_encode($clean_list));

  $nodes = node_load_multiple($to_process, array('type' => 'asu_isearch_profile'));

  $queue = DrupalQueue::get("isearch_clean_profiles");

  foreach ($nodes as $key => $profile) {
    //we only cleanup profiles which have been imported from iSearch
    if ($profile->field_isearch_eid['und'][0]['value'] != -1) {
      $queue->createItem($profile);
    }
  }
}

/**
 * @param $profile
 *
 * Worker callback for cleaning up dept profiles
 */
function asu_isearch_cleanup_profile($profile) {

  $asurite = $profile->field_isearch_asurite_id['und'][0]['value'];
  $health = asu_dir_utilities_solr_health_check();
  $configs = asu_isearch_get_dept_config();

  //check Solr department
  if ($health && $profile != NULL) {
    $pfound = FALSE;
    $person = asu_dir_utilities_get_solr_person($asurite);

    // if the above function returns exactly NULL, then something went wrong and
    // we should not unpublish
    if ($person === NULL) {
      return FALSE;
    }

    // check the person's dept affiliations in Solr against those imported on the local
    // site. if a valid affil is found, set the pfound flag to true
    if (!empty($person)) {
      foreach ($configs['items'] as $item) {
        if (isset($person['deptids']) && in_array($item['dept_nid'], $person['deptids'])) {
          $pfound = TRUE;
        }

        if (!$pfound && isset($item['options']) && $item['options']['subdepts']) {

          foreach ($item['tree_nids'] as $tree_item) {

            if (isset($person['deptids']) && in_array($tree_item, $person['deptids'])) {
              $pfound = TRUE;
            }
          }
        }
      }
    }

    //if the profile wasn't found, then unpublish
    if ($pfound == FALSE) {
      $title = $profile->title;

      watchdog('asu_isearch', "Profile'[@id]'unpublishedviacroncleanup", array('@id' => $title));
      $profile->status = 0;
      node_save($profile);
      return TRUE;
      //if node was unpublished, but was found on iSearch, republish the node
    }
    // re-publish the profile if it was previously unpublished but has valid affiliations
    else {
      if ($pfound == TRUE && $profile->status == 0) {
        $profile->status = 1;
        $title = $profile->title;
        watchdog('asu_isearch', "Profile'[@id]'REpublishedviacroncleanup", array('@id' => $title));
        node_save($profile);
      }
    }
  }

  return FALSE;
}

/***
 * Keep track of which nids need to be checked
 *
 * @return array|mixed
 */
function _asu_isearch_get_cleanup_list() {
  $nid_list = drupal_json_decode(variable_get('asu_isearch_cleanup_list', '[]'));

  if (empty($nid_list)) {
    $node_type = "asu_isearch_profile";

    // only check published nodes
    $result = db_query("SELECT nid FROM node WHERE type = :nodeType AND status = 1", array(':nodeType' => $node_type));
    foreach ($result as $obj) {
      $nid_list[] = $obj->nid;
    }

    variable_set('asu_isearch_cleanup_list', drupal_json_encode($nid_list));
  }

  return $nid_list;
}

