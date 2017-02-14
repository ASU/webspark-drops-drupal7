<?php
/**
 * @file
 * Theming functions for the asu_dir module.
 *
 * @author Colton Testamarck (colt@asu.edu)
 *
 *
 */


/**
 *Implements hook_theme()
 *
 *
 **/
function asu_dir_theme() {
  return array(
    // Ajax-Solr implementation
    'asu_dir_ajax_solr_field' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'template' => 'theme/asu_dir_ajax_solr_field',
      'file' => 'theme/asu_dir.theme.inc',
    ),
    'asu_dir_ajax_solr_people' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'file' => 'theme/asu_dir.theme.inc',
    ),
  );
}

/**
 * Theme implementation to build People listing with Ajax-Solr library
 *
 * About the settings passed here:
 *
 * disable_history : Disables the history stack handling
 * isearch_mode : Since the search functionality for departments in iSearch is handled by a callback, we can disable features related
 *                to this functionality, as well as facets
 *
 */
function theme_asu_dir_ajax_solr_people(&$vars) {

  $admin = $vars['settings']['admin'];
  $field_configs = $vars['items'][0]['directory_config'];
  $field_items = $vars['items'][0]['directory_items'];

  $the_id = $field_configs['pane_id'];

  //we need special configurations for iSearch, specifically, turning off the history handling, facets and search handling
  if (!isset($field_configs['isearch_flag'])) {
    $field_configs['isearch_flag'] = FALSE;
    $isearch_mode = FALSE;
  }
  else {
    $isearch_mode = $field_configs['isearch_flag'];
  }


  if (!isset($field_configs['show_breadcrumbs']) && !$isearch_mode) {
    $field_configs['show_breadcrumbs'] = TRUE;
  }
  else {
    if ($isearch_mode) {
      $field_configs['show_breadcrumbs'] = FALSE;
    }
  }

  if (!isset($field_configs['display_type'])) {
    $field_configs['display_type'] = 'list';
  }

  $alias = drupal_get_path_alias();

  $html = '';

  //pass these module constants tot he JS
  $top_level_ids = array(
    'top_level_nid' => ASU_DIR_UTILITIES_TOP_LEVEL_DEPT_NID,
    'top_level_psid' => ASU_DIR_UTILITIES_TOP_LEVEL_PS_ID
  );

  //get the dept tree
  $tree = asu_dir_utilities_get_dept_tree();
  $faculty_titles = asu_dir_utilities_get_faculty_titles();
  $local_people = asu_dir_utilities_get_local_profile_list();

  $field_configs['faculty_titles'] = $faculty_titles;

  libraries_load('ajax_solr');
  libraries_load('jqtree');
  libraries_load('fontawesome');

  //add history.js
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/jquery.history.js');
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirManager.js');
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirPagerWidget.js');
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirFacetWidget.js');
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirCurrentSearchWidget.js');

  // add the custom js and css

  //don't need these if we're in isearch mode
  if (!$isearch_mode) {
    drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirTextWidget.js');
    drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirParameterHistoryStore.js');
  }

  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asuAlphaBarWidget.js');
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirSortWidget.js');
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirResultWidget.js');
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirTreeWidget.js');
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/asu_dir_ajax_solr_field.js');
  drupal_add_css(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/css/asu_dir_tree.css');
  drupal_add_css(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/css/asu_dir_people_block.css');

  $settings = array(
    'dept_nids' => $field_items,
    'field_configs' => $field_configs,
    'solr_server' => ASU_DIR_UTILITIES_SOLR_ENV,
    'admin' => $admin,
    'top_level_ids' => $top_level_ids,
    'tree' => $tree,
    'page_alias' => $alias,
    'titlesort_field' => ASU_DIR_TITLESORT_FIELD,
    'tsort_placeholder' => ASU_DIR_TITLESORT_PHOLDER,
    'pane_id' => $the_id,
    'local_people' => $local_people,
    'isearch_url' => ASU_DIR_UTILITIES_ISEARCH_URL
  );

  drupal_add_js(array(ASU_DIRECTORY_MODULE_NAME . $the_id => $settings), 'setting');

  if ($field_configs['show_breadcrumbs']) {
    //todo:  uncomment this later
    //drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/asu_dir.breadcrumb.js');
  }

  // Markup for primary display block (to be altered via AJAX)
  $html .= '<div class="row dir-people-wrapper" id="asu-dir-people-wrapper' . $the_id . '"><div class="col-md-12 dir-ajax-solr-people" id="asu-dir-ajax-solr-people' . $the_id . '"></div></div>';

  //Pagination Controls

  $html .= '<div class="text-center asu_directory_bottom_container"><ul id="asu-dir-ajax-solr-pager' . $the_id . '" class="pagination"></ul></div>';

  return $html;
}


/**
 * Theme implementation for the dept tree
 */
/*
function theme_asu_dir_dept_tree(&$vars) {

  $standalone = FALSE;
  $whole_tree = FALSE;


  if (isset($vars['settings']['standalone_tree'])) {
    $standalone = $vars['settings']['standalone_tree'];
  }

  if (isset($vars['settings']['whole_tree'])) {
    $whole_tree = $vars['settings']['whole_tree'];
  }

  $tree = asu_dir_get_dept_tree();


  // jqTree (http://mbraak.github.com/jqTree)
  libraries_load('jqtree');
  libraries_load('fontawesome');

  // Custom
  drupal_add_css(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/css/asu_dir_tree.css');
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/asu_dir_hierarchy_block.js');

  $top_level_ids = array(
    "top_level_psid" => ASU_DIRECTORY_TOP_LEVEL_PS_ID,
    "top_level_nid" => ASU_DIRECTORY_TOP_LEVEL_DEPT_NID
  );


  //Pass our items and configs to the JS
  //will need to pass extra configs if the tree is being used without the people display (standalone)
  if ($standalone) {

    if (isset($vars['items'][0]['directory_items'])) {
      $nids = $vars['items'][0]['directory_items'];
    }
    else {
      $nids = array(ASU_DIRECTORY_TOP_LEVEL_DEPT_NID);
    }

    $settings = array(
      'tree' => $tree,
      'top_level_ids' => $top_level_ids,
      'standalone' => $standalone,
      'dept_nids' => $nids,
    );
  }
  else {
    $settings = array(
      'tree' => $tree,
      'whole_tree' => $whole_tree,
      'top_level_ids' => $top_level_ids
    );
  }

  drupal_add_js(array(ASU_DIRECTORY_MODULE_NAME => $settings), 'setting');

  $employee_select = '';
  $html = '';
  $html .= $employee_select . '<div class="asu-directory-tree-hierarchy"><div id="treediv"></div></div>';

  return $html;

}
*/

/**
 * Template preprocess handler for 'asu_dir' field.
 */
function template_process_asu_dir_ajax_solr_field(&$vars) {

  //if items are saved, need to json decode them
  if (!empty($vars['items'])) {
    foreach ($vars['items'] as &$item) {
      $default_configs = asu_dir_get_default_config();
      $field_configs = drupal_json_decode($item['directory_config']);
      $config = array_merge($default_configs, $field_configs);

      $item['directory_config'] = $config;

      $item['directory_config']['pane_id'] = $vars['id'];

      //set the breadcrumb option, if it doesn't exist, due to template needs
      if (!array_key_exists('show_breadcrumbs', $item['directory_config'])) {
        $item['directory_config']['show_breadcrumbs'] = FALSE;
      }

      $item['directory_items'] = drupal_json_decode($item['directory_items']);

      $vars['configs'] = $item['directory_config'];
      $vars['dir_classes'] = _asu_dir_get_classes($item['directory_config']);

    }
  }


  // Reference configuration variables
  $vars['settings']['solr_url'] = ASU_DIR_UTILITIES_SOLR_ENV;
}

function _asu_dir_get_classes($configs) {
  $columns = array();

  if ($configs['show_tree']) {
    $columns['search'] = 'col-md-5';
    $columns['dir_dropdown'] = 'col-md-7';
    $columns['dir_row_full'] = 'dir-row-full';
  }
  else {
    $columns['search'] = 'col-md-3';
    $columns['dir_dropdown'] = 'col-md-9';
    $columns['dir_row_full'] = '';
  }

  return $columns;

}



