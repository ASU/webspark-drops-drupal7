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
    // ASU Spotlight container
    'asu_dir' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'template' => 'theme/asu_dir',
      'file' => 'theme/asu_dir.theme.inc',
    ),
    'asu_dir_form_field' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'template' => 'theme/asu_dir_form_field',
      'file' => 'theme/asu_dir.theme.inc',
    ),
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
    // Slide container
    'asu_dir_people_list' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'file' => 'theme/asu_dir.theme.inc',
    ),
    // Slide item
    'asu_dir_dept_tree' => array(
      'variables' => array(
        'item' => array(),
        'settings' => array(),
        'caption' => ''
      ),
      'file' => 'theme/asu_dir.theme.inc',
    ),
  );
}

/**
 * Theme implementation to build People listing
 */
function theme_asu_dir_people_list(&$vars) {

  $admin = $vars['settings']['admin'];
  $field_configs = $vars['items'][0]['directory_config'];
  $field_items = $vars['items'][0]['directory_items'];

  if (!isset($field_configs['show_breadcrumbs'])) {
    $field_configs['show_breadcrumbs'] = TRUE;
  }

  $html = '';

  //pass these module constants tot he JS
  $top_level_ids = array(
    'top_level_nid' => ASU_DIRECTORY_TOP_LEVEL_DEPT_NID,
    'top_level_psid' => ASU_DIRECTORY_TOP_LEVEL_PS_ID
  );

  // add the custom js and css
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/asu_dir_ppl_block.js');
  drupal_add_css(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/css/asu_dir_people_block.css');

  $settings = array(
    'dept_nids' => $field_items,
    'field_configs' => $field_configs,
    'solr_server' => ASU_DIRECTORY_SOLR_ENV,
    'admin' => $admin,
    'top_level_ids' => $top_level_ids
  );

  drupal_add_js(array(ASU_DIRECTORY_MODULE_NAME => $settings), 'setting');

  if ($admin || $field_configs['show_breadcrumbs']) {

    drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/asu_dir.breadcrumb.js');
    $html .= '<div class="asu_directory_breadcrumb"></div>';
  }

  // Markup for primary display block (to be altered via AJAX)
  $html .= '<div class="display" id="people"></div>';

  //Bottom Pagination Controls
  $html .= '<div class="asu_directory_bottom_container">';
  $html .= '<ul id="asu_directory_people_controls_bottom" class="pagination asu_directory_people_controls">';

  $html .= '<li class="asu_directory_people_button prev first" id="asu_directory_people_prev_btn"><span class="asu_directory_people_top_switcher">< previous</span></li>';

  $html .= '<li class="asu_directory_people_button" id="asu_directory_people_first_pg_btn"><span> 1 </span></li>';
  $html .= '<li class="asu_directory_people_ellipses pager-ellipsis disabled"><span>...&nbsp;</span></li>';
  $html .= '<li class="asu_directory_people_button" id="asu_directory_people_back_2_btn"><span class="dynamic_number"> </span></li>';
  $html .= '<li class="asu_directory_people_button" id="asu_directory_people_back_1_btn"><span class="dynamic_number"> </span></li>';
  $html .= '<li class="asu_directory_people_button" id="asu_directory_people_this_pg_btn"><span class="dynamic_number"> </span></li>';
  $html .= '<li class="asu_directory_people_button" id="asu_directory_people_fwd_1_btn"><span class="dynamic_number"> </span></li>';
  $html .= '<li class="asu_directory_people_button" id="asu_directory_people_fwd_2_btn"><span class="dynamic_number"> </span></li>';
  $html .= '<li class="asu_directory_people_ellipses pager-ellipsis disabled"><span>...&nbsp;</span></li>';
  $html .= '<li class="asu_directory_people_button" id="asu_directory_people_last_pg_btn"><span class="dynamic_number"> </span></li>';

  $html .= '<li class="asu_directory_people_button next last" id="asu_directory_people_next_btn"><span class="next last asu_directory_people_top_switcher">next ></span></li>';

  $html .= '</ul>';
  $html .= '</div>';

  return $html;
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

  $alias = drupal_get_path_alias();

  $html = '';

  //pass these module constants tot he JS
  $top_level_ids = array(
    'top_level_nid' => ASU_DIRECTORY_TOP_LEVEL_DEPT_NID,
    'top_level_psid' => ASU_DIRECTORY_TOP_LEVEL_PS_ID
  );

  //get the dept tree
  $tree = asu_dir_get_dept_tree();

  libraries_load('ajax_solr');
  libraries_load('jqtree');
  libraries_load('fontawesome');

  //add history.js
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/jquery.history.js');

  // add the custom js and css

  //don't need these if we're in isearch mode
  if (!$isearch_mode) {
    drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirFacetWidget.js');
    drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirTextWidget.js');
    drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/widgets/asu_dirCurrentSearchWidget.js');
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
    'solr_server' => ASU_DIRECTORY_SOLR_ENV,
    'admin' => $admin,
    'top_level_ids' => $top_level_ids,
    'tree' => $tree,
    'page_alias' => $alias,
    'titlesort_field' => ASU_DIR_TITLESORT_FIELD,
    'tsort_placeholder' => ASU_DIR_TITLESORT_PHOLDER
  );

  drupal_add_js(array(ASU_DIRECTORY_MODULE_NAME => $settings), 'setting');

  if ($field_configs['show_breadcrumbs']) {
    drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/asu_dir.breadcrumb.js');
  }

  // Markup for primary display block (to be altered via AJAX)
  $html .= '<div class="row" id="asu-dir-people-wrapper"><div class="col-md-12" id="asu-dir-ajax-solr-people"></div></div>';

  //Pagination Controls

  $html .= '<div class="text-center asu_directory_bottom_container"><ul id="asu-dir-ajax-solr-pager" class="pagination"></ul></div>';

  return $html;
}


/**
 * Default theme implementation for flexslider_list_item
 */
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


/**
 * Template preprocess handler for 'asu_dir' theme.
 */
function template_process_asu_dir(&$vars) {

  //if items are saved, need to json decode them
  if (!empty($vars['items'])) {
    foreach ($vars['items'] as &$item) {
      $item['directory_config'] = drupal_json_decode($item['directory_config']);
      $item['directory_items'] = drupal_json_decode($item['directory_items']);
    }
  }
  // Reference configuration variables
  $vars['settings']['solr_url'] = ASU_DIRECTORY_SOLR_ENV;
}

function template_process_asu_dir_ajax_solr_field(&$vars) {
  //if items are saved, need to json decode them
  if (!empty($vars['items'])) {
    foreach ($vars['items'] as &$item) {
      $item['directory_config'] = drupal_json_decode($item['directory_config']);

      //set the breadcrumb option, if it doesn't exist, due to template needs
      if (!array_key_exists('show_breadcrumbs', $item['directory_config'])) {
        $item['directory_config']['show_breadcrumbs'] = FALSE;
      }

      $item['directory_items'] = drupal_json_decode($item['directory_items']);
    }
  }
  // Reference configuration variables
  $vars['settings']['solr_url'] = ASU_DIRECTORY_SOLR_ENV;
}


/**
 * Template preprocess handler for 'asu_dir_form_field' template.
 */
function template_process_asu_dir_form_field(&$vars) {

  //this generates the employee type display, by first grabbing the types from the endpoint
  //and then grouping them into 3 columns

  $employee_types = asu_dir_get_employee_types();
  $employee_types = $employee_types['nodes'];

  //add the "show all" option to the front of the array
  $show_all = array('node' => array('name' => 'Show All'));
  array_unshift($employee_types, $show_all);

  //calculate how many types we'll put in each column
  $num_per_col = count($employee_types) / 3 + 1;

  $count = 1;
  $col = 0;

  $vars['settings']['employee_types_col_' . $col] = array();

  foreach ($employee_types as $type) {

    if (($count % $num_per_col == 0) && ($count < count($employee_types))) {
      $col++;
      $vars['settings']['employee_types_col_' . $col] = array();
    }

    array_push($vars['settings']['employee_types_col_' . $col], $type);

    $count++;
  }
}


