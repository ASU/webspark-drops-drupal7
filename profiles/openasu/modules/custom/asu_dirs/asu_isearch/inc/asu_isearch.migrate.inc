<?php
/**
 * migrate module implementations
 */


/**
 * Implements hook_migrate_api().
 */
function asu_isearch_migrate_api() {

  $disable_hooks = array(
    'entity_insert' => array(
      'metatag',
      'og',
      'registration',
    ),
    'entity_update' => array(
      'metatag',
      'og',
      'registration',
    ),
    'node_insert' => array(
      'commons_activity_streams',
      'commons_follow_group',
      'commons_follow_node',
      'commons_groups',
      'commons_notify',
      'commons_radioactivity_groups',
      'kwresearch',
      'xmlsitemap_node',
      'expire',
    ),
    'node_update' => array(
      'commons_activity_streams',
      'commons_follow_group',
      'commons_follow_node',
      'commons_groups',
      'commons_radioactivity_groups',
      'kwresearch',
      'xmlsitemap_node',
      'expire',
    ),
    'node_prepare' => array(
      'og_menu',
    ),
    'taxonomy_term_insert' => array(
      'metatag',
      'shs',
      'taxonomy_menu',
    ),
    'taxonomy_term_update' => array(
      'shs',
      'taxonomy_menu',
    ),
  );

  return array(
    'api' => 2,
    'groups' => array(
      'asu_isearch' => array(
        'title' => t('iSearch Migration'),
        'disable_hooks' => $disable_hooks,
      ),
    ),
    'migrations' => array(
      'MigrateIsearchProfile' => array(
        'class_name' => 'MigrateIsearchProfileMigration',
        'group_name' => 'asu_isearch',
      ),
    ),
  );
}

/**
 * Instantiates the migration object
 */
function _asu_isearch_get_migration() {
  try {
    $migration = Migration::getInstance('MigrateIsearchProfile');
  } catch (MigrateException $e) {
    MigrationBase::registerMigration('MigrateIsearchProfileMigration', 'MigrateIsearchProfile', array(
      'group_name' => 'asu_isearch',
      'default_uid' => 1
    ));
    $migration = Migration::getInstance('MigrateIsearchProfile');
  }

  return $migration;
}


/**
 * Begins the iSearch profile migration
 */
function _asu_isearch_begin_migrate($force_update = FALSE) {

  $migrate_config = variable_get('isearch_admin_feed_dept', NULL);

  if (is_null($migrate_config)) {
    return FALSE;
  }

  $data = array(
    'endpoint' => ASU_ISEARCH_MASTER_FILE_ENDPOINT,
    'force' => $force_update,
    //'limit' => $limit,
    //'queue' => TRUE,
  );

  // feed endpoint
  $source_urls = array(ASU_ISEARCH_MASTER_FILE_ENDPOINT);
  $migration = _asu_isearch_get_migration();

  try {

    $migration->setMigrateSource($source_urls);
    // begin the migration
    $update = $migration->prepareUpdate();
    $result = $migration->processImport($data);

    //watchdog log the result
    variable_set('isearch_last_import', time());

  } catch (Exception $e) {

    // end and reset the migration, if another is stuck
    $migration->endProcess();
    $migration->resetStatus();
  }
}


function _asu_isearch_begin_batch($force_update = FALSE) {
  $limit = variable_get('isearch_import_limit', NULL);

  if (is_null($limit) || is_numeric($limit)) {

    $value = 50;

    if (is_numeric($limit)) {
      $value = $limit;
    }

    $limit = array(
      'value' => $value,
      'unit' => 'items',
    );
  }

  $migration = _asu_isearch_get_migration();
  $migration->prepareUpdate();

  $operations[] = array(
    'migrate_ui_batch',
    array('import', 'MigrateIsearchProfile', $limit, $force_update)
  );

  $batch = array(
    'operations' => $operations,
    'title' => t('iSearch Profile processing'),
    'file' => drupal_get_path('module', 'migrate_ui') . '/migrate_ui.pages.inc',
    'init_message' => t('Starting iSearch profile migration process'),
    'progress_message' => t(''),
    'error_message' => t('An error occurred. Some or all of the migrate processing has failed.'),
    'finished' => 'migrate_ui_batch_finish',
  );

  batch_set($batch);
}

/*****************************************************************************
 * MIGRATION HELPER FUNCTIONS
 *****************************************************************************/


/***
 * Cache the dept feed data, and build the source file for migration
 *
 * @param bool|FALSE $build_source - will append data to the master source file
 */
function _asu_isearch_cache_dept_feed($build_source = FALSE) {

  if (!file_exists(ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT)) {
    mkdir(ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT, 0644, TRUE);
  }

  // limit for how many departments will be cached on each cron run.
  // this is a needed because of the slow nature of the isearch endpoint
  $limit = ASU_ISEARCH_DEPT_CACHING_LIMIT;

  // retrieve list of configured isearch dept urls for import
  $source_urls = asu_isearch_get_migrate_source_urls(FALSE);
  $track_urls = asu_isearch_get_dept_tracker();
  $count = 0;

  foreach ($track_urls as $key => $url) {

    if ($count > $limit) {
      return FALSE;
    }

    $data = _asu_isearch_cache_dept($source_urls[$key]);

    //build the source master
    if ($build_source) {
      if (_asu_isearch_append_to_source($data)) {

        asu_isearch_remove_from_tracker($key);
        watchdog('asu_isearch', "Cached Dept'[@id]'", array('@id' => $key));
      }
      else {

        // stopped because the source was too large
        return FALSE;
      }
    }

    $count++;
  }

  // return true if we've cached everything on the list
  return TRUE;
}

/***
 * Build the sourc efile
 *
 * @param bool|FALSE $build_source
 */
function _asu_isearch_build_migrate_master($sources) {

  if (!file_exists(ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT)) {
    mkdir(ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT, 0644, TRUE);
  }

  // retrieve list of configured isearch dept urls for import
  foreach ($sources as $key => $url) {
    $data = asu_isearch_get_department($url, $key);

    // if the source gets too large, then stop appending
    // and break out of for loop
    if (_asu_isearch_append_to_source($data)) {
      asu_isearch_remove_from_tracker($key);
    }
    else {
      break;
    }
  }
}


/***
 * Cache a single department, and return the decoded data
 *
 * @param $url - the URL of the dept endpoint to cache
 * @return mixed - a PHP array of data which was cached
 */
function _asu_isearch_cache_dept($url) {

  // set timeout of request to 60 seconds
  $options = array(
    'timeout' => 60,
  );

  $decoded = NULL;
  $data = NULL;

  $request = drupal_http_request($url, $options);

  if ($request->code == 200) {
    $data = $request->data;
  }

  if (!is_null($data)) {

    $decoded = drupal_json_decode($data);
    $info = pathinfo($url);
    $dept_nid = $info['filename'];
    file_save_data($data, ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT . $dept_nid, FILE_EXISTS_REPLACE);
  }

  return $decoded;
}

/*****
 * Returns a department given an endpoint
 */
function asu_isearch_get_department($url, $deptnid) {

  // if we're not grabbing from cache, we might as well cache what we find at the
  // isearch endpoint
  $from_cache = ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT . $deptnid;

  //cache dept if it is not already
  if ($url != $from_cache) {
    $decoded = _asu_isearch_cache_dept($url);
    return $decoded;
  }

  $ctx = stream_context_create(array(
    'http' =>
      array(
        'timeout' => 30,  //30 second timeout
      )
  ));

  //
  $dept = file_get_contents($url, FALSE, $ctx);

  if ($decoded = drupal_json_decode($dept)) {
    return $decoded;
  }
  else {
    return array();
  }
}


/**
 * Append to the migrate source
 *
 * @param $data
 */
function _asu_isearch_append_to_source($data) {

  $master_list = asu_isearch_get_master_source();

  if (is_array($master_list) && count($master_list) < ASU_ISEARCH_MASTER_SOURCE_LIMIT) {

    if (is_array($data)) {
      $master_list = array_merge($master_list, $data);
    }

    $master_list = drupal_json_encode($master_list);

    //replace the source
    file_save_data($master_list, ASU_ISEARCH_MASTER_FILE_ENDPOINT, FILE_EXISTS_REPLACE);

    return TRUE;
  }
  else {
    return FALSE;
  }
}

/***
 * Refreshes the source json file
 *
 * @param $data
 */
function _asu_isearch_refresh_source($data) {
  $data = json_encode($data);
  file_save_data($data, ASU_ISEARCH_MASTER_FILE_ENDPOINT, FILE_EXISTS_REPLACE);
}


/***
 * Returns a department tracker array, which is an array of departments which have not yet been added to the source
 *
 * @return array|mixed
 */
function asu_isearch_get_dept_tracker() {
  $source_urls = asu_isearch_get_migrate_source_urls(TRUE);

  $tracker = variable_get('asu_isearch_dept_tracker', '[]');
  $tracker = json_decode($tracker, TRUE);

  //watchdog('thetracker','<pre>'.print_r($tracker,TRUE).'</pre>');

  if (!$tracker || empty($tracker)) {
    variable_set('asu_isearch_dept_tracker', json_encode($source_urls));
    $tracker = $source_urls;
  }
  else {
    // set to proper source urls, since we may have cached some depts since
    // getting the tracker last
    foreach ($tracker as $key => $track) {
      $tracker[$key] = $source_urls[$key];
    }
  }

  return $tracker;
}

/*****
 * Removes an item from the department tracker
 */
function asu_isearch_remove_from_tracker($dept_nid) {
  if (variable_get('asu_isearch_dept_tracker', NULL) != NULL) {
    $tracker = json_decode(variable_get('asu_isearch_dept_tracker', NULL), TRUE);

    foreach ($tracker as $key => $track) {
      if ($key == $dept_nid) {
        unset($tracker[$key]);
      }
    }

    variable_set('asu_isearch_dept_tracker', json_encode($tracker));
  }
}


function asu_isearch_get_master_source() {

  $master_list = array();

  //todo:  check for master list
  if (file_exists(ASU_ISEARCH_MASTER_FILE_ENDPOINT)) {
    $master_data = file_get_contents(ASU_ISEARCH_MASTER_FILE_ENDPOINT);

    $master_data = json_decode($master_data, TRUE);

    if ($master_data != NULL) {
      $master_list = $master_data;
    }
  }

  return $master_list;
}

/***
 * Reset the migration sources, if the source depts are changed
 */
function _asu_isearch_reset_migration_sources() {
  // reset, and then reload the tracker with the new dept sources
  variable_set('asu_isearch_dept_tracker', '[]');
  $newtracker = asu_isearch_get_dept_tracker();
  $newlist = array();
  $counter = 0;

  foreach ($newtracker as $key => $item) {
    // we're likely to timeout if we're doing a ton of requests to the
    // endpoint, so we need to cap this at a reasonable number
    if ($counter > 24) {
      break;
    }
    else {
      $newdept = asu_isearch_get_department($item, $key);

      if ($newdept) {
        $newlist = array_merge($newlist, $newdept);
        asu_isearch_remove_from_tracker($key);
      }
    }

    $counter++;
  }

  _asu_isearch_refresh_source($newlist);

}
