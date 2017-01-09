<?php

/**
 * Helper function to get the header column widths
 * used on the iSearch directory list view.
 */
function asu_isearch_get_view_column_widths(stdClass $display_options) {
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
 * Helper function to determine if the passed view is an isearch configured view
 *
 * This will help clarify code and add checks to keep undefines from happening
 */
function asu_isearch_is_isearch_view($view) {
  return $view->current_display == 'isearch_a_z' || (isset($view->display_handler->view->display['default']->display_options['css_class']) && $view->display_handler->view->display['default']->display_options['css_class'] == 'isearch-directory-list');
}


/**
 * Helper function to check for valid building codes
 */
function asu_isearch_fetch_asu_building_code($code) {
  $building_code = check_plain(trim($code));

  if (in_array(strtoupper($building_code), array('FULTON CENTER', 'FULTON'))) {
    $building_code = 'FULTN';
  }

  if ($has_building_code = preg_match('/^[0-9A-Z]{2,5}$/', strtoupper($building_code))) {

    return $building_code;
  }

  return FALSE;
}


/**
 * Helper function to load react library locally if module isn't present
 */
function asu_isearch_load_js() {
  if (!module_exists('react')) {
    drupal_add_js(drupal_get_path('module', 'asu_isearch') . '/vendor/react/build/react.js');
    drupal_add_js(drupal_get_path('module', 'asu_isearch') . '/vendor/react/build/react-dom.js');
  }
}

/**
 * Helper function for backwards compatibility when retrieving tenure display setting
 */
function asu_isearch_get_tenure_config($setting) {
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
 * Returns the global dept configuration
 */
function asu_isearch_get_dept_config() {
  $default_feed_dept = array(
    'items' => array(),
    'options' => new stdClass(),
  );

  //todo:  make sure this still works for all cases (asu_isearch legacy and new)
  $configs = variable_get('isearch_admin_feed_dept', json_encode($default_feed_dept));
  $tree = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_TREE_ENDPOINT, TRUE);
  $decoded = drupal_json_decode($configs);


  // pull the subdepts dynamically, instead of using the saved copy
  foreach($decoded['items'] as $key => $item) {
    $nid = $item['dept_nid'];

    $subtree = asu_dir_utilities_dept_find_root($tree, $nid);
    $dept_nids = asu_dir_utilities_dept_get_tree_nids($subtree);

    if (!empty($dept_nids)) {
      $decoded['items'][$key]['tree_nids'] = $dept_nids;
    }
  }

  // use regular json_encode, to encode back into an
  $new_configs = json_encode($decoded);

  return $new_configs;
}

/**
 * Retrieves an array of source urls
 */
function asu_isearch_get_migrate_source_urls($from_cache = FALSE) {

  $source_urls = array();

  // Check and see if we have configured our migration
  $migrate_config = variable_get('isearch_admin_feed_dept', NULL);

  if (!is_null($migrate_config)) {
    $migrate_config = json_decode($migrate_config);

    foreach ($migrate_config->items as $migrate_item) {
      // determine which endpoint to use
      $dept_id = $migrate_item->dept_id;

      if ($migrate_config->options->$dept_id->subdepts) {
        foreach ($migrate_item->tree_nids as $department_nid) {

          if ($from_cache && file_exists(ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT . $department_nid)) {
            $endpoint = ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT;
          }
          else {
            $endpoint = ASU_DIR_UTILITIES_FEED_ENDPOINT;
          }

          $source_urls[$department_nid] = $endpoint . $department_nid;
        }
      }
      else {
        // determine which endpoint to use
        if ($from_cache && file_exists(ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT . $migrate_item->dept_nid)) {
          $endpoint = ASU_ISEARCH_DIRECTORY_FEED_CACHE_ENDPOINT;
        }
        else {
          $endpoint = ASU_DIR_UTILITIES_FEED_ENDPOINT;
        }

        $source_urls[$migrate_item->dept_nid] = $endpoint . $migrate_item->dept_nid;
      }
    }
  }

  return $source_urls;
}


/**
 * Helper function to test for devmode
 */
function asu_isearch_devmode() {
  return (bool) variable_get('asu_isearch_devmode', FALSE);
}

/**
 * Returns the node (and all children) where (node.tid == @param tid )
 * @param {Object} data
 *  Nested JSON object with department data
 * @param {integer} dept_id
 *  ID of the department that should be the root of the hierarchy
 */
function asu_isearch_dept_find_root($data, $dept_id, $lookup = 'dept_nid') {
  $success = array();

  for ($i = 0; $i < count($data); $i++) {
    if (count($success) == 0 && $data[$i] != NULL) {
      if ($data[$i]->$lookup == $dept_id) {
        return $data[$i];
      }
      else {
        if (isset($data[$i]->children)) {
          $success = asu_isearch_dept_find_root($data[$i]->children, $dept_id, $lookup);
        }
      }
    }
    else {
      break;
    }
  }
  return $success;
}

/****
 * Function to update profile from Solr
 *
 */
function asu_isearch_solr_update_profile() {

}

function asu_isearch_get_field_solr_mappings() {

  $map = array(
    'status' => 'status',
    'field_isearch_displayname' => 'displayName',
    'field_isearch_firstname' => 'firstName',
    'field_isearch_lastname' => 'lastName',
    'field_isearch_employment_title' => 'primaryTitle',
    'field_isearch_eid' => 'eid',
    'field_isearch_asurite_id' => 'asuriteId',
    'field_isearch_email' => 'emailAddress',
    'field_isearch_phone' => 'phone',
    'field_isearch_fax' => 'fax',
    'field_isearch_campus_building' => 'addressLine1',
    'field_isearch_campus_room' => 'addressLine2',
    'field_isearch_primary_campus' => 'primaryJobCampus',
    'field_isearch_photo_preference' => 'photoPreference',
    'field_isearch_photo_permission' => 'photoPermission',
    'field_isearch_social_twitter' => 'twitterLink',
    'field_isearch_social_facebook' => 'facebook',
    'field_isearch_social_linkedin' => 'linkedin',
    'field_isearch_social_googleplus' => 'googlePlus',
    'field_isearch_social_personalweb' => 'website',
    'field_isearch_short_bio' => 'shortBio',
    'field_isearch_bio' => 'bio',
    'field_isearch_education' => 'education',
    'field_isearch_cv_url' => 'cvUrl',
    'field_isearch_rsrch_website' => 'researchWebsite',
    'field_isearch_rsrch_interests' => 'researchInterests',
    'field_isearch_rsrch_group' => 'researchGroup',
    'field_isearch_rsrch_activity' => 'researchActivity',
    'field_isearch_rsrch_publications' => 'publications',
    'field_isearch_tch_website' => 'teachingWebsite',
    'field_isearch_tch_courses' => 'courses',
    'field_isearch_tch_presentations' => 'presentations',
    'field_isearch_honors_awards' => 'honorsAwards',
    'field_isearch_editorships' => 'editorships',
    'field_isearch_prof_associations' => 'professionalAssociations',
    'field_isearch_graduate_faculties' => 'graduateFaculties',
    'field_isearch_work_history' => 'workHistory',
    'field_isearch_service' => 'service',
  );

  return $map;

}
