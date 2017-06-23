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
    'asu_dir_isearch_view' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'file' => 'theme/asu_dir.theme.inc',
    )
  );
}


/*****
 * Build the isearch people list
 */
function theme_asu_dir_isearch_view(&$vars) {
  // shortcut to content render array
  $content = array();

  // Setup variables here...
  $content['title'] = '';
  $directory = new IsearchProfileDirectory();

  // load the configuration saved for this pane
  $default_view_config = asu_dir_utilities_get_default_config('asu_isearch');
  $view_config = json_decode($vars['items'][0]['directory_config']);
  $view_config = (object) array_merge($default_view_config, (array) $view_config);

  //set the view display option if there is none
  if (!isset($view_config->view_display)) {
    $view_config->view_display = 'isearch_directory:directory_list';
  }

  list($view_name, $view_display_id) = explode(':', $view_config->view_display);

  // build out the view
  $view = views_get_view($view_name);
  $view->view_config = $view_config;
  $view->set_display($view_display_id);
  $view->init_handlers();

  $contextual_filters = asu_isearch_get_filters($view_config, $view);

  // set the contextual filters arguments
  $view_display = asu_isearch_get_rendered_view($view_config, $view);

  // end edit
  $directory->setViewConfig($view_config);

  $directory->setContextualFilters($contextual_filters);

  if ($view_config->show_az_index) {
    $content['isearch_az_index'] = array(
      '#markup' => $directory->renderIndex(),
      '#weight' => -10,
    );
  }

  $content['isearch_view'] = array(
    '#markup' => $view_display,
  );

  /*
  // display filters? - Should we display or hide the filters
  if ($view_config->show_filters) {
    // build the exposed form fields
    $form_state = array(
      'view' => $view,
      'display' => $view->display_handler->display,
      'exposed_form_plugin' => $view->display_handler->get_plugin('exposed_form'),
      'method' => 'get',
      'rerender' => TRUE,
      'no_redirect' => TRUE,
      'ajax' => TRUE
    );


    $form = drupal_build_form('views_exposed_form', $form_state);

    // Attach our custom ajax handling script, if ajax is enabled
    if ($view->use_ajax) {
      $form['#attached']['js'][] = drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch_omni.js';
    }

    $form['keys']['#weight'] = -100;
    $form['keys']['#attributes']['placeholder'] = t('Name or Keyword');


    // update search filters
    $view->set_items_per_page(0);
    $view->set_offset(0);

    if ($view_config->show_filter_titles) {
      _asu_isearch_update_view_form_filters($view, $form, $directory);
    }

    // change some values to correctly display the form
    $form['#action'] = '/' . drupal_get_path_alias(current_path());
    $form['#weight'] = -5;

    $form['field_isearch_affil_title_value']['#access'] = (bool) $view_config->show_filter_titles;
    $form['field_isearch_expertise_areas_tid']['#access'] = (bool) $view_config->show_filter_expertise;
    $form['sort_by']['#access'] = (bool) $view_config->show_filter_sort;
    $form['keys']['#access'] = (bool) $view_config->show_filter_omni;

    // set the default sort by
    $form['sort_by']['#value'] = $view_config->default_sort_by;

    // set some form defaults when submitted ...
    $params = drupal_get_query_parameters();

    if (isset($params['field_isearch_expertise_areas_tid'])) {
      $form['field_isearch_expertise_areas_tid']['#value'] = intval($params['field_isearch_expertise_areas_tid']);

      if (isset($params['sort_by'])) {
        $form['sort_by']['#default_value'] = check_url($params['sort_by']);
        $form['sort_by']['#value'] = check_url($params['sort_by']);
      }

      if (isset($params['sort_order'])) {
        // Forcing ascending sort order for now
        $form['sort_order']['#value'] = 'ASC';
      }
    }

    // Add our configs to the exposed form, so that they are resubmitted as
    // part of the ajax process
    $form['omni_configs']['#value'] = drupal_json_encode($view_config);


    //$form['submit']['#ajax_processed'] = TRUE;
    $content['isearch_view_exposed_form'] = $form;
    $form['field_isearch_affil_title_value']['#title'] = t('Title');
    $form['field_isearch_affil_title_value']['#title_display'] = 'invisible';
    $form['field_isearch_expertise_areas_tid']['#title'] = t('Expertise Areas Filter');
    $form['field_isearch_expertise_areas_tid']['#title_display'] = 'invisible';
    $form['sort_by']['#title'] = t('Sort By');
    $form['sort_by']['#title_display'] = 'invisible';
    $form['field_isearch_local_tags_tid']['#title'] = t('Local Tags');
    $form['field_isearch_local_tags_tid']['#title_display'] = 'invisible';
  }*/

  _asu_isearch_build_contextual_filter_form($content, $view, $view_config, $directory);

  $html = $content['isearch_az_index']['#markup'];
  $html .= render($content['isearch_view_exposed_form']);
  $html .= $content['isearch_view']['#markup'];

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
  $filter_people = array();
  $local_people = array();

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

  // if local tags are set, we'll pass the tagged asurite ids to the js
  if (!empty($field_configs['local_tags'])) {
    $tags = array_keys($field_configs['local_tags']);
    $tagged = asu_isearch_get_local_tag_people($tags);

    if (!empty($tagged)) {
      $field_configs['filter_asurite'] = array_keys($tagged);
    }
  }

  $alias = drupal_get_path_alias();

  $html = '';

  //pass these module constants tot he JS
  $top_level_ids = array(
    'top_level_nid' => ASU_DIR_UTILITIES_TOP_LEVEL_DEPT_NID,
    'top_level_psid' => ASU_DIR_UTILITIES_TOP_LEVEL_PS_ID
  );

  //get the dept tree, don't decode it
  $tree = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_TREE_ENDPOINT, FALSE);

  // get the faculty titles
  $faculty_titles = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_FACULTY_TITLES_ENDPOINT);

  if (module_exists('asu_isearch')) {
    $local_people = asu_isearch_get_local_profile_list();
  }

  $field_configs['faculty_titles'] = $faculty_titles;

  // setup expertise area names for ajax solr
  if (!empty($field_configs['expertise_areas'])) {

    $exp = array();

    foreach ($field_configs['expertise_areas'] as $key => $item) {
      $term = taxonomy_term_load($item);

      $exp[] = $term->name;
    }

    $field_configs['expertise_areas'] = $exp;
  }

  libraries_load('ajax_solr');
  libraries_load('jqtree');
  libraries_load('fontawesome');

  $options = array('weight' => 1000);



  //drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/plugins/jquery.tabgroups.js');

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
  drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/asu_dir_ajax_solr_field.js', $options);
  drupal_add_css(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/css/asu_dir_tree.css');
  drupal_add_css(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/css/asu_dir_people_block.css');

  // get the default photo url, if configured, and pass information
  // to the frontend
  $display_default_photo = variable_get('isearch_display_default_photo', FALSE);
  $photo_url = NULL;

  if ($display_default_photo) {
    $default_photo = asu_isearch_get_default_photo();


    if (is_object($default_photo)) {
      $photo_url = file_create_url($default_photo->uri);
    }
  }

  $default_photo = array(
    'display' => $display_default_photo,
    'url' => $photo_url
  );

  $field_configs['default_photo'] = $default_photo;


  $settings = array(
    'deptNids' => $field_items,
    'fieldConfigs' => $field_configs,
    'solrServer' => ASU_DIR_UTILITIES_SOLR_ENV,
    'admin' => $admin,
    'topLevelIds' => $top_level_ids,
    'tree' => $tree,
    'pageAlias' => $alias,
    'titleSortField' => ASU_DIR_UTILITIES_TITLESORT_FIELD,
    'fidNum' => $the_id,
    'localPeople' => $local_people,
    'isearchUrl' => ASU_DIR_UTILITIES_ISEARCH_URL
  );

  drupal_add_js(array(ASU_DIRECTORY_MODULE_NAME . $the_id => $settings), 'setting');

  if ($field_configs['show_breadcrumbs'] && $field_configs['show_tree']) {
    //todo:  uncomment this later
    drupal_add_js(drupal_get_path('module', ASU_DIRECTORY_MODULE_NAME) . '/js/asu_dir.breadcrumb.js');
  }

  // Markup for primary display block (to be altered via AJAX)
  $html .= '<div class="dir-people-wrapper" id="asu-dir-people-wrapper' . $the_id . '"><div class="col-md-12 dir-ajax-solr-people" id="asu-dir-ajax-solr-people' . $the_id . '"></div></div>';

  //Pagination Controls

  $html .= '<div class="text-center asu_directory_bottom_container"><ul id="asu-dir-ajax-solr-pager' . $the_id . '" class="pagination"></ul></div>';

  return $html;
}

/**
 * Template preprocess handler for 'asu_dir' field.
 */
function template_process_asu_dir_ajax_solr_field(&$vars) {

  //if items are saved, need to json decode them
  if (!empty($vars['items'])) {
    foreach ($vars['items'] as &$item) {
      $default_configs = asu_dir_utilities_get_default_config();
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



