<?php
/**
 * @file
 * asu_isearch.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function asu_isearch_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'isearch_admin';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'iSearch Admin';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'path' => 'path',
    'field_isearch_photo_url' => 'field_isearch_photo_url',
    'field_isearch_short_bio' => 'field_isearch_short_bio',
    'title' => 'title',
    'field_isearch_phone' => 'field_isearch_phone',
    'field_isearch_campus_building' => 'field_isearch_campus_building',
    'field_isearch_email' => 'field_isearch_email',
    'field_isearch_expertise_areas' => 'field_isearch_expertise_areas',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_isearch_photo_url' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_isearch_short_bio' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_isearch_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_isearch_campus_building' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_isearch_email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_isearch_expertise_areas' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No employees found.';
  $handler->display->display_options['empty']['area']['format'] = 'panopoly_wysiwyg_text';
  /* Relationship: Affiliation */
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['id'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['table'] = 'field_data_field_isearch_affiliations';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['field'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['ui_name'] = 'Affiliation';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['label'] = 'Affiliation';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['delta'] = '-1';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Expertise';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'isearch_expertise' => 'isearch_expertise',
    'panopoly_categories' => 0,
    'isearch_departments' => 0,
    'isearch_ranks' => 0,
  );
  /* Relationship: Field collection item: Rank (field_isearch_affil_rank) */
  $handler->display->display_options['relationships']['field_isearch_affil_rank_tid']['id'] = 'field_isearch_affil_rank_tid';
  $handler->display->display_options['relationships']['field_isearch_affil_rank_tid']['table'] = 'field_data_field_isearch_affil_rank';
  $handler->display->display_options['relationships']['field_isearch_affil_rank_tid']['field'] = 'field_isearch_affil_rank_tid';
  $handler->display->display_options['relationships']['field_isearch_affil_rank_tid']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['relationships']['field_isearch_affil_rank_tid']['label'] = 'Affiliation Rank';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  /* Field: Content: Profile Picture */
  $handler->display->display_options['fields']['field_isearch_photo_url']['id'] = 'field_isearch_photo_url';
  $handler->display->display_options['fields']['field_isearch_photo_url']['table'] = 'field_data_field_isearch_photo_url';
  $handler->display->display_options['fields']['field_isearch_photo_url']['field'] = 'field_isearch_photo_url';
  $handler->display->display_options['fields']['field_isearch_photo_url']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_photo_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_photo_url']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_isearch_photo_url']['element_wrapper_class'] = 'col-md-2';
  $handler->display->display_options['fields']['field_isearch_photo_url']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_isearch_photo_url']['settings'] = array(
    'image_style' => 'asu_isearch_profile_list',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'col-md-4';
  /* Field: Content: Phone */
  $handler->display->display_options['fields']['field_isearch_phone']['id'] = 'field_isearch_phone';
  $handler->display->display_options['fields']['field_isearch_phone']['table'] = 'field_data_field_isearch_phone';
  $handler->display->display_options['fields']['field_isearch_phone']['field'] = 'field_isearch_phone';
  $handler->display->display_options['fields']['field_isearch_phone']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_phone']['element_label_colon'] = FALSE;
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_isearch_email']['id'] = 'field_isearch_email';
  $handler->display->display_options['fields']['field_isearch_email']['table'] = 'field_data_field_isearch_email';
  $handler->display->display_options['fields']['field_isearch_email']['field'] = 'field_isearch_email';
  $handler->display->display_options['fields']['field_isearch_email']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_email']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['id'] = 'field_isearch_lastname_value';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['field'] = 'field_isearch_lastname_value';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['expose']['label'] = 'Last Name';
  /* Sort criterion: Content: First Name (field_isearch_firstname) */
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['id'] = 'field_isearch_firstname_value';
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['table'] = 'field_data_field_isearch_firstname';
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['field'] = 'field_isearch_firstname_value';
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['expose']['label'] = 'First Name';
  /* Contextual filter: Employee Type */
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['id'] = 'field_isearch_affil_empl_type_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['table'] = 'field_data_field_isearch_affil_empl_type';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['field'] = 'field_isearch_affil_empl_type_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['ui_name'] = 'Employee Type';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_type_value']['break_phrase'] = TRUE;
  /* Contextual filter: Department ID */
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['id'] = 'field_isearch_affil_dept_id_value_1';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['table'] = 'field_data_field_isearch_affil_dept_id';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['field'] = 'field_isearch_affil_dept_id_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['ui_name'] = 'Department ID';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['break_phrase'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'asu_isearch_profile' => 'asu_isearch_profile',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Admin - List Profiles */
  $handler = $view->new_display('page', 'Admin - List Profiles', 'admin_list');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'List Profiles';
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['path'] = 'admin/content/isearch/profiles';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['description'] = 'Manage profiles imported from iSearch';
  $handler->display->display_options['menu']['weight'] = '1000';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'iSearch';
  $handler->display->display_options['tab_options']['weight'] = '1000';
  $export['isearch_admin'] = $view;

  $view = new view();
  $view->name = 'isearch_affiliations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'iSearch Affiliations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_accordion_plugin_style';
  $handler->display->display_options['style_options']['title_field'] = 'field_isearch_affil_dept_name';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Field collection item: Entity with the Affiliations (field_isearch_affiliations) */
  $handler->display->display_options['relationships']['field_isearch_affiliations_node']['id'] = 'field_isearch_affiliations_node';
  $handler->display->display_options['relationships']['field_isearch_affiliations_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_isearch_affiliations_node']['field'] = 'field_isearch_affiliations_node';
  $handler->display->display_options['relationships']['field_isearch_affiliations_node']['required'] = TRUE;
  /* Field: Field collection item: Title */
  $handler->display->display_options['fields']['field_isearch_affil_title']['id'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['field'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_affil_title']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Dept */
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['id'] = 'field_isearch_affil_dept_name';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['table'] = 'field_data_field_isearch_affil_dept_name';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['field'] = 'field_isearch_affil_dept_name';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Employee Type */
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['id'] = 'field_isearch_affil_empl_type';
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['table'] = 'field_data_field_isearch_affil_empl_type';
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['field'] = 'field_isearch_affil_empl_type';
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_isearch_affil_campus']['id'] = 'field_isearch_affil_campus';
  $handler->display->display_options['fields']['field_isearch_affil_campus']['table'] = 'field_data_field_isearch_affil_campus';
  $handler->display->display_options['fields']['field_isearch_affil_campus']['field'] = 'field_isearch_affil_campus';
  /* Field: Field collection item: Mailcode */
  $handler->display->display_options['fields']['field_isearch_affil_mailcode']['id'] = 'field_isearch_affil_mailcode';
  $handler->display->display_options['fields']['field_isearch_affil_mailcode']['table'] = 'field_data_field_isearch_affil_mailcode';
  $handler->display->display_options['fields']['field_isearch_affil_mailcode']['field'] = 'field_isearch_affil_mailcode';
  /* Sort criterion: Field collection item: Primary Affiliation (field_isearch_affil_primary) */
  $handler->display->display_options['sorts']['field_isearch_affil_primary_value']['id'] = 'field_isearch_affil_primary_value';
  $handler->display->display_options['sorts']['field_isearch_affil_primary_value']['table'] = 'field_data_field_isearch_affil_primary';
  $handler->display->display_options['sorts']['field_isearch_affil_primary_value']['field'] = 'field_isearch_affil_primary_value';
  $handler->display->display_options['sorts']['field_isearch_affil_primary_value']['order'] = 'DESC';
  /* Sort criterion: Field collection item: Affiliation Weight (field_isearch_affil_weight) */
  $handler->display->display_options['sorts']['field_isearch_affil_weight_value']['id'] = 'field_isearch_affil_weight_value';
  $handler->display->display_options['sorts']['field_isearch_affil_weight_value']['table'] = 'field_data_field_isearch_affil_weight';
  $handler->display->display_options['sorts']['field_isearch_affil_weight_value']['field'] = 'field_isearch_affil_weight_value';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_isearch_affiliations_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'asu_isearch_profile' => 'asu_isearch_profile',
  );
  /* Contextual filter: Field collection item: Field collection item ID */
  $handler->display->display_options['arguments']['item_id']['id'] = 'item_id';
  $handler->display->display_options['arguments']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['arguments']['item_id']['field'] = 'item_id';
  $handler->display->display_options['arguments']['item_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['item_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['item_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['item_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['item_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['item_id']['validate']['type'] = 'numeric';
  $handler->display->display_options['arguments']['item_id']['break_phrase'] = TRUE;
  /* Filter criterion: Field collection item: Hide Affiliation (field_isearch_affil_hide) */
  $handler->display->display_options['filters']['field_isearch_affil_hide_value']['id'] = 'field_isearch_affil_hide_value';
  $handler->display->display_options['filters']['field_isearch_affil_hide_value']['table'] = 'field_data_field_isearch_affil_hide';
  $handler->display->display_options['filters']['field_isearch_affil_hide_value']['field'] = 'field_isearch_affil_hide_value';
  $handler->display->display_options['filters']['field_isearch_affil_hide_value']['value'] = array(
    0 => '0',
  );

  /* Display: iSearch Profile Affiliations */
  $handler = $view->new_display('panel_pane', 'iSearch Profile Affiliations', 'panel_pane_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field collection item: Dept */
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['id'] = 'field_isearch_affil_dept_name';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['table'] = 'field_data_field_isearch_affil_dept_name';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['field'] = 'field_isearch_affil_dept_name';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Title */
  $handler->display->display_options['fields']['field_isearch_affil_title']['id'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['field'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_affil_title']['type'] = 'text_plain';
  /* Field: Field collection item: Employee Type */
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['id'] = 'field_isearch_affil_empl_type';
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['table'] = 'field_data_field_isearch_affil_empl_type';
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['field'] = 'field_isearch_affil_empl_type';
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_empl_type']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_isearch_affil_campus']['id'] = 'field_isearch_affil_campus';
  $handler->display->display_options['fields']['field_isearch_affil_campus']['table'] = 'field_data_field_isearch_affil_campus';
  $handler->display->display_options['fields']['field_isearch_affil_campus']['field'] = 'field_isearch_affil_campus';
  $handler->display->display_options['fields']['field_isearch_affil_campus']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_campus']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_affil_campus']['alter']['text'] = '[field_isearch_affil_campus] Campus';
  $handler->display->display_options['fields']['field_isearch_affil_campus']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Mailcode */
  $handler->display->display_options['fields']['field_isearch_affil_mailcode']['id'] = 'field_isearch_affil_mailcode';
  $handler->display->display_options['fields']['field_isearch_affil_mailcode']['table'] = 'field_data_field_isearch_affil_mailcode';
  $handler->display->display_options['fields']['field_isearch_affil_mailcode']['field'] = 'field_isearch_affil_mailcode';
  $handler->display->display_options['fields']['field_isearch_affil_mailcode']['element_label_colon'] = FALSE;

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_isearch_affil_title' => 'field_isearch_affil_title',
    'field_isearch_affil_dept_name' => 0,
    'field_isearch_affil_empl_type' => 0,
    'field_isearch_affil_campus' => 0,
    'field_isearch_affil_mailcode' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field collection item: Title */
  $handler->display->display_options['fields']['field_isearch_affil_title']['id'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['field'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_affil_title']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Dept */
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['id'] = 'field_isearch_affil_dept_name';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['table'] = 'field_data_field_isearch_affil_dept_name';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['field'] = 'field_isearch_affil_dept_name';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['alter']['text'] = '[field_isearch_affil_dept_name-value] <em>([field_isearch_affil_title])</em>';
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_affil_dept_name']['type'] = 'text_plain';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_isearch_affiliations_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'asu_isearch_profile' => 'asu_isearch_profile',
  );
  $export['isearch_affiliations'] = $view;

  $view = new view();
  $view->name = 'isearch_directory';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'iSearch Directory';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'isearch-directory-list';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_tags'] = array(
    0 => 'asu_isearch_list',
  );
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '1';
  $handler->display->display_options['pager']['options']['quantity'] = '6';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'row';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['content'] = '<div class="views-row views-row-1 views-row-odd views-row-first row">
    <div class="views-field views-field-field-isearch-photo-url col-md-2 user-photo"></div>
    <div class="views-field views-field-nothing-1 col-md-4 user-name">
      <span class="field-content"><div class="name">Name</div></span>
    </div>
    <div class="views-field views-field-nothing col-md-3 user-contact">
      <span class="field-content"><div class="email">Contact</div></span>
    </div>
    <div class="views-field views-field-field-isearch-expertise-areas col-md-3 user-expertise">
      <span class="field-content"><div class="email">Expertise</div></span>
    </div>
</div>
';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No employees found.';
  $handler->display->display_options['empty']['area']['format'] = 'panopoly_wysiwyg_text';
  /* Relationship: Content: Affiliations (field_isearch_affiliations) */
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['id'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['table'] = 'field_data_field_isearch_affiliations';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['field'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['label'] = 'Affiliation';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['delta'] = '-1';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Expertise';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'isearch_expertise' => 'isearch_expertise',
    'asu_events_audience' => 0,
    'asu_events_category' => 0,
    'asu_events_type' => 0,
    'asu_news' => 0,
    'panopoly_categories' => 0,
    'isearch_departments' => 0,
    'isearch_ranks' => 0,
  );
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  /* Field: Content: Profile Picture */
  $handler->display->display_options['fields']['field_isearch_photo_url']['id'] = 'field_isearch_photo_url';
  $handler->display->display_options['fields']['field_isearch_photo_url']['table'] = 'field_data_field_isearch_photo_url';
  $handler->display->display_options['fields']['field_isearch_photo_url']['field'] = 'field_isearch_photo_url';
  $handler->display->display_options['fields']['field_isearch_photo_url']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_photo_url']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_photo_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_photo_url']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_isearch_photo_url']['element_wrapper_class'] = 'col-md-2 user-photo';
  $handler->display->display_options['fields']['field_isearch_photo_url']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_isearch_photo_url']['settings'] = array(
    'image_style' => 'asu_isearch_profile_list',
    'image_link' => 'content',
  );
  /* Field: Content: Local Profile Picture */
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['id'] = 'field_isearch_local_photo_url';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['table'] = 'field_data_field_isearch_local_photo_url';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['field'] = 'field_isearch_local_photo_url';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['alter']['text'] = '[field_isearch_photo_url]';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['element_wrapper_class'] = 'user-photo';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['empty'] = '[field_isearch_photo_url]';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['settings'] = array(
    'image_style' => 'asu_isearch_profile_list',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'col-md-4';
  /* Field: Field collection item: Title */
  $handler->display->display_options['fields']['field_isearch_affil_title']['id'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['field'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['fields']['field_isearch_affil_title']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_affil_title']['element_label_colon'] = FALSE;
  /* Field: Content: Short Bio */
  $handler->display->display_options['fields']['field_isearch_short_bio']['id'] = 'field_isearch_short_bio';
  $handler->display->display_options['fields']['field_isearch_short_bio']['table'] = 'field_data_field_isearch_short_bio';
  $handler->display->display_options['fields']['field_isearch_short_bio']['field'] = 'field_isearch_short_bio';
  $handler->display->display_options['fields']['field_isearch_short_bio']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_short_bio']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_short_bio']['element_label_colon'] = FALSE;
  /* Field: Name / Titles */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Name / Titles';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<div class="name">[title]</div>
<div class="title">[field_isearch_affil_title]</div>
<div class="shortbio">[field_isearch_short_bio]</div>';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_1']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['nothing_1']['element_wrapper_class'] = 'user-name';
  /* Field: Content: Phone */
  $handler->display->display_options['fields']['field_isearch_phone']['id'] = 'field_isearch_phone';
  $handler->display->display_options['fields']['field_isearch_phone']['table'] = 'field_data_field_isearch_phone';
  $handler->display->display_options['fields']['field_isearch_phone']['field'] = 'field_isearch_phone';
  $handler->display->display_options['fields']['field_isearch_phone']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_phone']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_phone']['element_label_colon'] = FALSE;
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_isearch_email']['id'] = 'field_isearch_email';
  $handler->display->display_options['fields']['field_isearch_email']['table'] = 'field_data_field_isearch_email';
  $handler->display->display_options['fields']['field_isearch_email']['field'] = 'field_isearch_email';
  $handler->display->display_options['fields']['field_isearch_email']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_email']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_email']['element_label_colon'] = FALSE;
  /* Field: Content: Campus Building */
  $handler->display->display_options['fields']['field_isearch_campus_building']['id'] = 'field_isearch_campus_building';
  $handler->display->display_options['fields']['field_isearch_campus_building']['table'] = 'field_data_field_isearch_campus_building';
  $handler->display->display_options['fields']['field_isearch_campus_building']['field'] = 'field_isearch_campus_building';
  $handler->display->display_options['fields']['field_isearch_campus_building']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_campus_building']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_campus_building']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_campus_building']['alter']['text'] = '[field_isearch_campus_building] ';
  $handler->display->display_options['fields']['field_isearch_campus_building']['element_label_colon'] = FALSE;
  /* Field: Content: Campus Room */
  $handler->display->display_options['fields']['field_isearch_campus_room']['id'] = 'field_isearch_campus_room';
  $handler->display->display_options['fields']['field_isearch_campus_room']['table'] = 'field_data_field_isearch_campus_room';
  $handler->display->display_options['fields']['field_isearch_campus_room']['field'] = 'field_isearch_campus_room';
  $handler->display->display_options['fields']['field_isearch_campus_room']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_campus_room']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_campus_room']['element_label_colon'] = FALSE;
  /* Field: Contact Info */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Contact Info';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="email">[field_isearch_email]</div>
<div class="phone">[field_isearch_phone]</div>
<div class="location"><span class="building">[field_isearch_campus_building]</span><span class="room">[field_isearch_campus_room]</span></div>
';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['nothing']['element_wrapper_class'] = 'user-contact';
  /* Field: Content: Expertise Areas */
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['id'] = 'field_isearch_expertise_areas';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['table'] = 'field_data_field_isearch_expertise_areas';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['field'] = 'field_isearch_expertise_areas';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['element_wrapper_class'] = 'user-expertise';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['delta_offset'] = '0';
  /* Field: Field collection item: Rank Local Weight */
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['id'] = 'field_isearch_affil_local_weight';
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['table'] = 'field_data_field_isearch_affil_local_weight';
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['field'] = 'field_isearch_affil_local_weight';
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['relationship'] = 'field_isearch_affiliations_value';
  /* Field: Field collection item: Rank Tenure */
  $handler->display->display_options['fields']['field_isearch_affil_rank_tenure']['id'] = 'field_isearch_affil_rank_tenure';
  $handler->display->display_options['fields']['field_isearch_affil_rank_tenure']['table'] = 'field_data_field_isearch_affil_rank_tenure';
  $handler->display->display_options['fields']['field_isearch_affil_rank_tenure']['field'] = 'field_isearch_affil_rank_tenure';
  $handler->display->display_options['fields']['field_isearch_affil_rank_tenure']['relationship'] = 'field_isearch_affiliations_value';
  /* Field: Field collection item: Rank Weight */
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['id'] = 'field_isearch_affil_rank_weight';
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['table'] = 'field_data_field_isearch_affil_rank_weight';
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['field'] = 'field_isearch_affil_rank_weight';
  /* Sort criterion: Field collection item: Rank Weight (field_isearch_affil_rank_weight) */
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['id'] = 'field_isearch_affil_rank_weight_value';
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['table'] = 'field_data_field_isearch_affil_rank_weight';
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['field'] = 'field_isearch_affil_rank_weight_value';
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['expose']['label'] = 'Rank';
  /* Sort criterion: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['id'] = 'field_isearch_lastname_value';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['field'] = 'field_isearch_lastname_value';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['expose']['label'] = 'Last Name';
  /* Sort criterion: Content: First Name (field_isearch_firstname) */
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['id'] = 'field_isearch_firstname_value';
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['table'] = 'field_data_field_isearch_firstname';
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['field'] = 'field_isearch_firstname_value';
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['expose']['label'] = 'First Name';
  /* Sort criterion: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['sorts']['field_isearch_lastname_value_1']['id'] = 'field_isearch_lastname_value_1';
  $handler->display->display_options['sorts']['field_isearch_lastname_value_1']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['sorts']['field_isearch_lastname_value_1']['field'] = 'field_isearch_lastname_value';
  /* Contextual filter: Employee Type */
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['id'] = 'field_isearch_affil_empl_key_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['table'] = 'field_data_field_isearch_affil_empl_key';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['field'] = 'field_isearch_affil_empl_key_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['ui_name'] = 'Employee Type';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['break_phrase'] = TRUE;
  /* Contextual filter: Department ID */
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['id'] = 'field_isearch_affil_dept_id_value_1';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['table'] = 'field_data_field_isearch_affil_dept_id';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['field'] = 'field_isearch_affil_dept_id_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['ui_name'] = 'Department ID';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['break_phrase'] = TRUE;
  /* Contextual filter: Field collection item: Rank Tenure (field_isearch_affil_rank_tenure) */
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['id'] = 'field_isearch_affil_rank_tenure_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['table'] = 'field_data_field_isearch_affil_rank_tenure';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['field'] = 'field_isearch_affil_rank_tenure_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Has Expertise Areas */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['ui_name'] = 'Has Expertise Areas';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'isearch_expertise' => 'isearch_expertise',
  );
  $handler->display->display_options['arguments']['tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = TRUE;
  /* Contextual filter: Has Local Tags */
  $handler->display->display_options['arguments']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['arguments']['tid_1']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid_1']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid_1']['ui_name'] = 'Has Local Tags';
  $handler->display->display_options['arguments']['tid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid_1']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid_1']['validate_options']['vocabularies'] = array(
    'isearch_local_tags' => 'isearch_local_tags',
  );
  $handler->display->display_options['arguments']['tid_1']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['tid_1']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['tid_1']['reduce_duplicates'] = TRUE;
  /* Contextual filter: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['id'] = 'field_isearch_lastname_value';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['field'] = 'field_isearch_lastname_value';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'asu_isearch_profile' => 'asu_isearch_profile',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Expertise Areas (field_isearch_expertise_areas) */
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['id'] = 'field_isearch_expertise_areas_tid';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['table'] = 'field_data_field_isearch_expertise_areas';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['field'] = 'field_isearch_expertise_areas_tid';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['operator_id'] = 'field_isearch_expertise_areas_tid_op';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['label'] = 'Expertise Area';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['operator'] = 'field_isearch_expertise_areas_tid_op';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['identifier'] = 'field_isearch_expertise_areas_tid';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['vocabulary'] = 'isearch_expertise';
  /* Filter criterion: Field collection item: Title (field_isearch_affil_title) */
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['id'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['field'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group'] = 1;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['operator_id'] = 'field_isearch_affil_title_value_op';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['label'] = 'Select Title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['operator'] = 'field_isearch_affil_title_value_op';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['identifier'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    8 => 0,
    6 => 0,
    7 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_field'] = 'field_isearch_affil_title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_raw_dropdown'] = 0;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_dependent'] = 0;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group_info']['label'] = 'Title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group_info']['identifier'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group_info']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Any',
      'operator' => 'contains',
      'value' => 'Any',
    ),
    2 => array(
      'title' => '',
      'operator' => 'contains',
      'value' => '',
    ),
    3 => array(
      'title' => '',
      'operator' => 'contains',
      'value' => '',
    ),
  );
  /* Filter criterion: Field collection item: Title (field_isearch_affil_title) */
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['id'] = 'field_isearch_affil_title_value_1';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['field'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['operator'] = 'regular_expression';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['value'] = '.*';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['group'] = 1;
  /* Filter criterion: Content: Local Tags (field_isearch_local_tags) */
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['id'] = 'field_isearch_local_tags_tid';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['table'] = 'field_data_field_isearch_local_tags';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['field'] = 'field_isearch_local_tags_tid';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['value'] = '';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['operator_id'] = 'field_isearch_local_tags_tid_op';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['label'] = 'Local Tags (field_isearch_local_tags)';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['operator'] = 'field_isearch_local_tags_tid_op';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['identifier'] = 'field_isearch_local_tags_tid';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    8 => 0,
    6 => 0,
    7 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['vocabulary'] = 'isearch_local_tags';
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Combine fields filter';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';

  /* Display: Directory - List */
  $handler = $view->new_display('panel_pane', 'Directory - List', 'isearch_directory_list');
  $handler->display->display_options['display_description'] = 'Displays a directory in list format';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Affiliations (field_isearch_affiliations) */
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['id'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['table'] = 'field_data_field_isearch_affiliations';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['field'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['label'] = 'Affiliation';
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_isearch_affiliations_value']['delta'] = '-1';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Expertise';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'isearch_expertise' => 'isearch_expertise',
    'asu_events_audience' => 0,
    'asu_events_category' => 0,
    'asu_events_type' => 0,
    'asu_news' => 0,
    'panopoly_categories' => 0,
    'isearch_departments' => 0,
    'isearch_ranks' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  /* Field: Content: Profile Picture */
  $handler->display->display_options['fields']['field_isearch_photo_url']['id'] = 'field_isearch_photo_url';
  $handler->display->display_options['fields']['field_isearch_photo_url']['table'] = 'field_data_field_isearch_photo_url';
  $handler->display->display_options['fields']['field_isearch_photo_url']['field'] = 'field_isearch_photo_url';
  $handler->display->display_options['fields']['field_isearch_photo_url']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_photo_url']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_photo_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_photo_url']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_isearch_photo_url']['element_wrapper_class'] = 'col-md-2 user-photo';
  $handler->display->display_options['fields']['field_isearch_photo_url']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_isearch_photo_url']['settings'] = array(
    'image_style' => 'asu_isearch_profile_list',
    'image_link' => 'content',
  );
  /* Field: Content: Local Profile Picture */
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['id'] = 'field_isearch_local_photo_url';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['table'] = 'field_data_field_isearch_local_photo_url';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['field'] = 'field_isearch_local_photo_url';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['alter']['text'] = '[field_isearch_photo_url]';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['element_wrapper_class'] = 'user-photo';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['empty'] = '[field_isearch_photo_url]';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_isearch_local_photo_url']['settings'] = array(
    'image_style' => 'asu_isearch_profile_list',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'col-md-4';
  /* Field: Field collection item: Title */
  $handler->display->display_options['fields']['field_isearch_affil_title']['id'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['field'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['fields']['field_isearch_affil_title']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_affil_title']['element_label_colon'] = FALSE;
  /* Field: Content: Short Bio */
  $handler->display->display_options['fields']['field_isearch_short_bio']['id'] = 'field_isearch_short_bio';
  $handler->display->display_options['fields']['field_isearch_short_bio']['table'] = 'field_data_field_isearch_short_bio';
  $handler->display->display_options['fields']['field_isearch_short_bio']['field'] = 'field_isearch_short_bio';
  $handler->display->display_options['fields']['field_isearch_short_bio']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_short_bio']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_short_bio']['element_label_colon'] = FALSE;
  /* Field: Name / Titles */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Name / Titles';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<div class="name">[title]</div>
<div class="title">[field_isearch_affil_title]</div>
<div class="shortbio">[field_isearch_short_bio]</div>';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_1']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['nothing_1']['element_wrapper_class'] = 'user-name';
  /* Field: Content: Phone */
  $handler->display->display_options['fields']['field_isearch_phone']['id'] = 'field_isearch_phone';
  $handler->display->display_options['fields']['field_isearch_phone']['table'] = 'field_data_field_isearch_phone';
  $handler->display->display_options['fields']['field_isearch_phone']['field'] = 'field_isearch_phone';
  $handler->display->display_options['fields']['field_isearch_phone']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_phone']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_phone']['element_label_colon'] = FALSE;
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_isearch_email']['id'] = 'field_isearch_email';
  $handler->display->display_options['fields']['field_isearch_email']['table'] = 'field_data_field_isearch_email';
  $handler->display->display_options['fields']['field_isearch_email']['field'] = 'field_isearch_email';
  $handler->display->display_options['fields']['field_isearch_email']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_email']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_email']['element_label_colon'] = FALSE;
  /* Field: Content: Campus Building */
  $handler->display->display_options['fields']['field_isearch_campus_building']['id'] = 'field_isearch_campus_building';
  $handler->display->display_options['fields']['field_isearch_campus_building']['table'] = 'field_data_field_isearch_campus_building';
  $handler->display->display_options['fields']['field_isearch_campus_building']['field'] = 'field_isearch_campus_building';
  $handler->display->display_options['fields']['field_isearch_campus_building']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_campus_building']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_campus_building']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_campus_building']['alter']['text'] = '[field_isearch_campus_building] ';
  $handler->display->display_options['fields']['field_isearch_campus_building']['element_label_colon'] = FALSE;
  /* Field: Content: Campus Room */
  $handler->display->display_options['fields']['field_isearch_campus_room']['id'] = 'field_isearch_campus_room';
  $handler->display->display_options['fields']['field_isearch_campus_room']['table'] = 'field_data_field_isearch_campus_room';
  $handler->display->display_options['fields']['field_isearch_campus_room']['field'] = 'field_isearch_campus_room';
  $handler->display->display_options['fields']['field_isearch_campus_room']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_campus_room']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_campus_room']['element_label_colon'] = FALSE;
  /* Field: Contact Info */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Contact Info';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="email">[field_isearch_email]</div>
<div class="phone">[field_isearch_phone]</div>
<div class="location"><span class="building">[field_isearch_campus_building]</span><span class="room">[field_isearch_campus_room]</span></div>
';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['nothing']['element_wrapper_class'] = 'user-contact';
  /* Field: Content: Expertise Areas */
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['id'] = 'field_isearch_expertise_areas';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['table'] = 'field_data_field_isearch_expertise_areas';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['field'] = 'field_isearch_expertise_areas';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['element_wrapper_class'] = 'user-expertise';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['delta_offset'] = '0';
  /* Field: Field collection item: Rank Weight */
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['id'] = 'field_isearch_affil_rank_weight';
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['table'] = 'field_data_field_isearch_affil_rank_weight';
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['field'] = 'field_isearch_affil_rank_weight';
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_affil_rank_weight']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Field collection item: Rank Local Weight */
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['id'] = 'field_isearch_affil_local_weight';
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['table'] = 'field_data_field_isearch_affil_local_weight';
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['field'] = 'field_isearch_affil_local_weight';
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_affil_local_weight']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Field collection item: Rank Weight (field_isearch_affil_rank_weight) */
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['id'] = 'field_isearch_affil_rank_weight_value';
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['table'] = 'field_data_field_isearch_affil_rank_weight';
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['field'] = 'field_isearch_affil_rank_weight_value';
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_isearch_affil_rank_weight_value']['expose']['label'] = 'Rank';
  /* Sort criterion: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['id'] = 'field_isearch_lastname_value';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['field'] = 'field_isearch_lastname_value';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['expose']['label'] = 'Last Name';
  /* Sort criterion: Content: First Name (field_isearch_firstname) */
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['id'] = 'field_isearch_firstname_value';
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['table'] = 'field_data_field_isearch_firstname';
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['field'] = 'field_isearch_firstname_value';
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_isearch_firstname_value']['expose']['label'] = 'First Name';
  /* Sort criterion: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['sorts']['field_isearch_lastname_value_1']['id'] = 'field_isearch_lastname_value_1';
  $handler->display->display_options['sorts']['field_isearch_lastname_value_1']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['sorts']['field_isearch_lastname_value_1']['field'] = 'field_isearch_lastname_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['id'] = 'field_isearch_lastname_value';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['field'] = 'field_isearch_lastname_value';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['limit'] = '0';
  /* Contextual filter: Employee Type */
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['id'] = 'field_isearch_affil_empl_key_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['table'] = 'field_data_field_isearch_affil_empl_key';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['field'] = 'field_isearch_affil_empl_key_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['ui_name'] = 'Employee Type';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['break_phrase'] = TRUE;
  /* Contextual filter: Department ID */
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['id'] = 'field_isearch_affil_dept_id_value_1';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['table'] = 'field_data_field_isearch_affil_dept_id';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['field'] = 'field_isearch_affil_dept_id_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['ui_name'] = 'Department ID';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['break_phrase'] = TRUE;
  /* Contextual filter: Field collection item: Rank Tenure (field_isearch_affil_rank_tenure) */
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['id'] = 'field_isearch_affil_rank_tenure_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['table'] = 'field_data_field_isearch_affil_rank_tenure';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['field'] = 'field_isearch_affil_rank_tenure_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Has Expertise Areas */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['ui_name'] = 'Has Expertise Areas';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'isearch_expertise' => 'isearch_expertise',
  );
  $handler->display->display_options['arguments']['tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = TRUE;
  /* Contextual filter: Has Local Tags */
  $handler->display->display_options['arguments']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['arguments']['tid_1']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid_1']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid_1']['ui_name'] = 'Has Local Tags';
  $handler->display->display_options['arguments']['tid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid_1']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid_1']['validate_options']['vocabularies'] = array(
    'isearch_local_tags' => 'isearch_local_tags',
  );
  $handler->display->display_options['arguments']['tid_1']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['tid_1']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['tid_1']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'asu_isearch_profile' => 'asu_isearch_profile',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Expertise Areas (field_isearch_expertise_areas) */
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['id'] = 'field_isearch_expertise_areas_tid';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['table'] = 'field_data_field_isearch_expertise_areas';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['field'] = 'field_isearch_expertise_areas_tid';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['operator_id'] = 'field_isearch_expertise_areas_tid_op';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['label'] = 'Expertise Area';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['operator'] = 'field_isearch_expertise_areas_tid_op';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['identifier'] = 'field_isearch_expertise_areas_tid';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_isearch_expertise_areas_tid']['vocabulary'] = 'isearch_expertise';
  /* Filter criterion: Field collection item: Title (field_isearch_affil_title) */
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['id'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['field'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group'] = 1;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['operator_id'] = 'field_isearch_affil_title_value_op';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['label'] = 'Select Title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['operator'] = 'field_isearch_affil_title_value_op';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['identifier'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_field'] = 'field_isearch_affil_title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_raw_dropdown'] = 0;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['expose']['autocomplete_dependent'] = 0;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group_info']['label'] = 'Title (field_isearch_affil_title)';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group_info']['identifier'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Field collection item: Title (field_isearch_affil_title) */
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['id'] = 'field_isearch_affil_title_value_1';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['field'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['operator'] = 'regular_expression';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['value'] = '.*';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['group'] = 1;
  /* Filter criterion: Content: Local Tags (field_isearch_local_tags) */
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['id'] = 'field_isearch_local_tags_tid';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['table'] = 'field_data_field_isearch_local_tags';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['field'] = 'field_isearch_local_tags_tid';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['value'] = '';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['operator_id'] = 'field_isearch_local_tags_tid_op';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['label'] = 'Local Tags (field_isearch_local_tags)';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['operator'] = 'field_isearch_local_tags_tid_op';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['identifier'] = 'field_isearch_local_tags_tid';
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    8 => 0,
    6 => 0,
    7 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_isearch_local_tags_tid']['vocabulary'] = 'isearch_local_tags';
  /* Filter criterion: Search: Search Terms */
  $handler->display->display_options['filters']['keys']['id'] = 'keys';
  $handler->display->display_options['filters']['keys']['table'] = 'search_index';
  $handler->display->display_options['filters']['keys']['field'] = 'keys';
  $handler->display->display_options['filters']['keys']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keys']['expose']['operator_id'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['keys']['expose']['operator'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['identifier'] = 'keys';
  $handler->display->display_options['filters']['keys']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 'offset';
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 'exposed_form';
  $handler->display->display_options['allow']['fields_override'] = 0;

  /* Display: Directory - Titles */
  $handler = $view->new_display('panel_pane', 'Directory - Titles', 'isearch_directory_titles');
  $handler->display->display_options['display_description'] = 'Used to populate titles filter';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'row';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field collection item: Title */
  $handler->display->display_options['fields']['field_isearch_affil_title']['id'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['field'] = 'field_isearch_affil_title';
  $handler->display->display_options['fields']['field_isearch_affil_title']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['fields']['field_isearch_affil_title']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_affil_title']['element_type'] = '0';
  $handler->display->display_options['fields']['field_isearch_affil_title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_isearch_affil_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_affil_title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_affil_title']['type'] = 'text_plain';
  /* Field: Content: Expertise Areas */
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['id'] = 'field_isearch_expertise_areas';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['table'] = 'field_data_field_isearch_expertise_areas';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['field'] = 'field_isearch_expertise_areas';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_isearch_expertise_areas']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Field collection item: Title (field_isearch_affil_title) */
  $handler->display->display_options['sorts']['field_isearch_affil_title_value']['id'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['sorts']['field_isearch_affil_title_value']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['sorts']['field_isearch_affil_title_value']['field'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['sorts']['field_isearch_affil_title_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['id'] = 'field_isearch_lastname_value';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['field'] = 'field_isearch_lastname_value';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['summary']['format'] = 'default_summary';
  /* Contextual filter: Employee Type */
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['id'] = 'field_isearch_affil_empl_key_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['table'] = 'field_data_field_isearch_affil_empl_key';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['field'] = 'field_isearch_affil_empl_key_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['ui_name'] = 'Employee Type';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['break_phrase'] = TRUE;
  /* Contextual filter: Department ID */
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['id'] = 'field_isearch_affil_dept_id_value_1';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['table'] = 'field_data_field_isearch_affil_dept_id';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['field'] = 'field_isearch_affil_dept_id_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['ui_name'] = 'Department ID';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['break_phrase'] = TRUE;
  /* Contextual filter: Field collection item: Rank Tenure (field_isearch_affil_rank_tenure) */
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['id'] = 'field_isearch_affil_rank_tenure_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['table'] = 'field_data_field_isearch_affil_rank_tenure';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['field'] = 'field_isearch_affil_rank_tenure_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Has Expertise Areas */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['ui_name'] = 'Has Expertise Areas';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'isearch_expertise' => 'isearch_expertise',
  );
  $handler->display->display_options['arguments']['tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = TRUE;
  /* Contextual filter: Has Local Tags */
  $handler->display->display_options['arguments']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['arguments']['tid_1']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid_1']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid_1']['ui_name'] = 'Has Local Tags';
  $handler->display->display_options['arguments']['tid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid_1']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid_1']['validate_options']['vocabularies'] = array(
    'isearch_local_tags' => 'isearch_local_tags',
  );
  $handler->display->display_options['arguments']['tid_1']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['tid_1']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['tid_1']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'asu_isearch_profile' => 'asu_isearch_profile',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Field collection item: Title (field_isearch_affil_title) */
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['id'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['field'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['operator'] = 'regular_expression';
  $handler->display->display_options['filters']['field_isearch_affil_title_value']['value'] = '.*';
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 'offset';
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 'exposed_form';
  $handler->display->display_options['allow']['fields_override'] = 0;

  /* Display: A-Z Index */
  $handler = $view->new_display('panel_pane', 'A-Z Index', 'isearch_a_z');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'isearch-a-z';
  $handler->display->display_options['display_description'] = 'Displays an A-Z index';
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Last Name */
  $handler->display->display_options['fields']['field_isearch_lastname']['id'] = 'field_isearch_lastname';
  $handler->display->display_options['fields']['field_isearch_lastname']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['fields']['field_isearch_lastname']['field'] = 'field_isearch_lastname';
  $handler->display->display_options['fields']['field_isearch_lastname']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_lastname']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['id'] = 'field_isearch_lastname_value';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['field'] = 'field_isearch_lastname_value';
  $handler->display->display_options['sorts']['field_isearch_lastname_value']['expose']['label'] = 'Last Name';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Last Name (field_isearch_lastname) */
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['id'] = 'field_isearch_lastname_value';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['table'] = 'field_data_field_isearch_lastname';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['field'] = 'field_isearch_lastname_value';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_lastname_value']['summary']['format'] = 'default_summary';
  /* Contextual filter: Employee Type */
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['id'] = 'field_isearch_affil_empl_key_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['table'] = 'field_data_field_isearch_affil_empl_key';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['field'] = 'field_isearch_affil_empl_key_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['ui_name'] = 'Employee Type';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_empl_key_value']['break_phrase'] = TRUE;
  /* Contextual filter: Department ID */
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['id'] = 'field_isearch_affil_dept_id_value_1';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['table'] = 'field_data_field_isearch_affil_dept_id';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['field'] = 'field_isearch_affil_dept_id_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['ui_name'] = 'Department ID';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['limit'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_dept_id_value_1']['break_phrase'] = TRUE;
  /* Contextual filter: Field collection item: Rank Tenure (field_isearch_affil_rank_tenure) */
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['id'] = 'field_isearch_affil_rank_tenure_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['table'] = 'field_data_field_isearch_affil_rank_tenure';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['field'] = 'field_isearch_affil_rank_tenure_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_isearch_affil_rank_tenure_value']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Has Expertise Areas */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['ui_name'] = 'Has Expertise Areas';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'isearch_expertise' => 'isearch_expertise',
  );
  $handler->display->display_options['arguments']['tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = TRUE;
  /* Contextual filter: Has Local Tags */
  $handler->display->display_options['arguments']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['arguments']['tid_1']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid_1']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid_1']['ui_name'] = 'Has Local Tags';
  $handler->display->display_options['arguments']['tid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid_1']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid_1']['validate_options']['vocabularies'] = array(
    'isearch_local_tags' => 'isearch_local_tags',
  );
  $handler->display->display_options['arguments']['tid_1']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['tid_1']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['tid_1']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'asu_isearch_profile' => 'asu_isearch_profile',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Field collection item: Title (field_isearch_affil_title) */
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['id'] = 'field_isearch_affil_title_value_1';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['table'] = 'field_data_field_isearch_affil_title';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['field'] = 'field_isearch_affil_title_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['relationship'] = 'field_isearch_affiliations_value';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['operator'] = 'regular_expression';
  $handler->display->display_options['filters']['field_isearch_affil_title_value_1']['group'] = 1;
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 'offset';
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 'exposed_form';
  $handler->display->display_options['allow']['fields_override'] = 0;
  $export['isearch_directory'] = $view;

  $view = new view();
  $view->name = 'isearch_expertise_people';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'iSearch Expertise People';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'isearch-expertise-people';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_isearch_displayname' => 'field_isearch_displayname',
  );
  $handler->display->display_options['row_options']['separator'] = ',';
  /* Relationship: Taxonomy term: Content with term */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'taxonomy_index';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['required'] = TRUE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['relationship'] = 'nid';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  /* Field: Content: Display Name */
  $handler->display->display_options['fields']['field_isearch_displayname']['id'] = 'field_isearch_displayname';
  $handler->display->display_options['fields']['field_isearch_displayname']['table'] = 'field_data_field_isearch_displayname';
  $handler->display->display_options['fields']['field_isearch_displayname']['field'] = 'field_isearch_displayname';
  $handler->display->display_options['fields']['field_isearch_displayname']['relationship'] = 'nid';
  $handler->display->display_options['fields']['field_isearch_displayname']['label'] = '';
  $handler->display->display_options['fields']['field_isearch_displayname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_displayname']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['field_isearch_displayname']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_isearch_displayname']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_isearch_displayname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_isearch_displayname']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_isearch_displayname']['element_default_classes'] = FALSE;
  /* Contextual filter: Taxonomy term: Term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'isearch_expertise' => 'isearch_expertise',
  );
  $handler->display->display_options['arguments']['tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = TRUE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'isearch_expertise' => 'isearch_expertise',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'nid';
  $handler->display->display_options['filters']['type']['value'] = array(
    'asu_isearch_profile' => 'asu_isearch_profile',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['argument_input'] = array(
    'tid' => array(
      'type' => 'user',
      'context' => 'entity:field_collection_item.uuid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Taxonomy term: Term ID',
    ),
  );
  $export['isearch_expertise_people'] = $view;

  return $export;
}
