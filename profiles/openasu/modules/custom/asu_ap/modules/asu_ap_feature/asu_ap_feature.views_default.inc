<?php

/**
 * @file
 * asu_ap_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function asu_ap_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'asu_ap_view';
  $view->description = 'Displays ASU Academic Programs nodes in various configurations and groups.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ASU Academic Programs';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Undergraduate Majors';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '24';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_grid_plugin_style';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['separator'] = '<br>';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/programs/undergraduate/all"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/programs/undergraduate/all/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No academic programs imported';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No academic programs have been imported. Please check back later.';
  $handler->display->display_options['empty']['area']['format'] = 'panopoly_wysiwyg_text';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Degree image */
  $handler->display->display_options['fields']['field_degree_image']['id'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['table'] = 'field_data_field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['field'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['label'] = '';
  $handler->display->display_options['fields']['field_degree_image']['element_label_colon'] = FALSE;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_ap_awarded']['id'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['table'] = 'field_data_field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['field'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_ap_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Program description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['body']['alter']['more_link'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['more_link_text'] = 'read more';
  $handler->display->display_options['fields']['body']['alter']['more_link_path'] = '/node/[nid]';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['preserve_tags'] = '<p> <br> <i> <li> <ul> <ol> <div> <hr> <span> <title> <u>';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus']['id'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_ap_campus']['exclude'] = TRUE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['id'] = 'field_asu_ap_campus_1';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['label'] = 'Available Online';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['delta_offset'] = '0';
  /* Field: Content: Department code */
  $handler->display->display_options['fields']['field_asu_ap_department_code']['id'] = 'field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['table'] = 'field_data_field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['field'] = 'field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_department_code']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_ap']['id'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['field'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap']['alter']['text'] = '<div class="asu-ap-rewritten-fields">
    <div class="asu-ap-major-title">[field_asu_ap_awarded] ([field_asu_ap])</div>
    [body]
    <div class="asu-ap-field-title">Location:</div> [field_asu_ap_campus]<br>
</div>';
  $handler->display->display_options['fields']['field_asu_ap']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Degree awarded (field_asu_ap_awarded) */
  $handler->display->display_options['sorts']['field_asu_ap_awarded_value']['id'] = 'field_asu_ap_awarded_value';
  $handler->display->display_options['sorts']['field_asu_ap_awarded_value']['table'] = 'field_data_field_asu_ap_awarded';
  $handler->display->display_options['sorts']['field_asu_ap_awarded_value']['field'] = 'field_asu_ap_awarded_value';
  /* Filter criterion: Content: Published status */
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
    'asu_ap' => 'asu_ap',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_ap_program) */
  $handler->display->display_options['filters']['field_asu_ap_program_value']['id'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['table'] = 'field_data_field_asu_ap_program';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['field'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['value'] = 'undergrad';
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value']['id'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['operator'] = 'not empty';
  /* Filter criterion: Content: Campus (field_asu_ap_campus) */
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['id'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['field'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator_id'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['label'] = 'Campus (field_asu_ap_campus)';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Downtown Phoenix campus',
      'operator' => '=',
      'value' => 'Downtown',
    ),
    2 => array(
      'title' => 'Polytechnic campus',
      'operator' => '=',
      'value' => 'Polytechnic',
    ),
    3 => array(
      'title' => 'Tempe campus',
      'operator' => '=',
      'value' => 'Tempe',
    ),
    4 => array(
      'title' => 'West campus',
      'operator' => '=',
      'value' => 'West',
    ),
    5 => array(
      'title' => 'Lake Havasu City',
      'operator' => '=',
      'value' => 'Havasu',
    ),
    6 => array(
      'title' => 'ASU@TheGilaValley',
      'operator' => '=',
      'value' => 'The Gila Valley',
    ),
    7 => array(
      'title' => 'ASU@Pinal',
      'operator' => '=',
      'value' => 'Pinal',
    ),
    8 => array(
      'title' => 'ASU@Yuma',
      'operator' => '=',
      'value' => 'Yuma',
    ),
    9 => array(
      'title' => 'Online',
      'operator' => '=',
      'value' => 'Online',
    ),
    10 => array(
      'title' => 'ASU@Northeastern Arizona',
      'operator' => '=',
      'value' => 'Northeastern Arizona',
    ),
    11 => array(
      'title' => 'ASU@Los Angeles',
      'operator' => '=',
      'value' => 'Los Angeles',
    ),
  );
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value_1']['id'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator_id'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['label'] = 'Degree (field_asu_ap)';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['label'] = 'Program Type';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'BFA',
      'operator' => '=',
      'value' => 'BFA',
    ),
    2 => array(
      'title' => 'BGM',
      'operator' => '=',
      'value' => 'BGM',
    ),
    3 => array(
      'title' => 'BMUS',
      'operator' => '=',
      'value' => 'BMUS',
    ),
    4 => array(
      'title' => 'BS',
      'operator' => '=',
      'value' => 'BS',
    ),
    5 => array(
      'title' => 'BSD',
      'operator' => '=',
      'value' => 'BSD',
    ),
    6 => array(
      'title' => 'BSE',
      'operator' => '=',
      'value' => 'BSE',
    ),
    7 => array(
      'title' => 'BSLA',
      'operator' => '=',
      'value' => 'BSLA',
    ),
    8 => array(
      'title' => 'BSN',
      'operator' => '=',
      'value' => 'BSN',
    ),
    9 => array(
      'title' => 'BSP',
      'operator' => '=',
      'value' => 'BSP',
    ),
    10 => array(
      'title' => 'BSW',
      'operator' => '=',
      'value' => 'BSW',
    ),
    11 => array(
      'title' => 'Minor',
      'operator' => '=',
      'value' => 'Minor',
    ),
    12 => array(
      'title' => 'Certificate',
      'operator' => '=',
      'value' => 'Certificate',
    ),
    13 => array(
      'title' => 'BA',
      'operator' => '=',
      'value' => 'BA',
    ),
    14 => array(
      'title' => 'BAE',
      'operator' => '=',
      'value' => 'BAE',
    ),
    15 => array(
      'title' => 'BAS',
      'operator' => '=',
      'value' => 'BAS',
    ),
  );

  /* Display: Page - UG all */
  $handler = $view->new_display('page', 'Page - UG all', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All Undergraduate Programs';
  $handler->display->display_options['display_description'] = 'Displays all undergraduate degrees';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_grid_plugin_style';
  $handler->display->display_options['style_options']['columns_horizontal'] = '4';
  $handler->display->display_options['style_options']['columns_vertical'] = '4';
  $handler->display->display_options['style_options']['columns_xs'] = '12';
  $handler->display->display_options['style_options']['columns_sm'] = '6';
  $handler->display->display_options['style_options']['columns_md'] = '3';
  $handler->display->display_options['style_options']['columns_lg'] = '3';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['separator'] = '<br>';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/programs/undergraduate"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/programs/undergraduate/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Degree image */
  $handler->display->display_options['fields']['field_degree_image']['id'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['table'] = 'field_data_field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['field'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['label'] = '';
  $handler->display->display_options['fields']['field_degree_image']['element_label_colon'] = FALSE;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_ap_awarded']['id'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['table'] = 'field_data_field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['field'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_ap_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Program description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['body']['alter']['more_link'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['more_link_text'] = 'read more';
  $handler->display->display_options['fields']['body']['alter']['more_link_path'] = '/node/[nid]';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['preserve_tags'] = '<p> <br> <i> <li> <ul> <ol> <div> <hr> <span> <title> <u>';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus']['id'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_ap_campus']['exclude'] = TRUE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['id'] = 'field_asu_ap_campus_1';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['label'] = 'Available Online';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['delta_offset'] = '0';
  /* Field: Content: Department code */
  $handler->display->display_options['fields']['field_asu_ap_department_code']['id'] = 'field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['table'] = 'field_data_field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['field'] = 'field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_department_code']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_ap']['id'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['field'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap']['alter']['text'] = '<div class="asu-ap-rewritten-fields">
    <div class="asu-ap-major-title">[field_asu_ap_awarded], [field_asu_ap]</div>[body]<div class="asu-ap-field-location"><div class="asu-ap-field-title">Location:</div>[field_asu_ap_campus]</div>
</div>';
  $handler->display->display_options['fields']['field_asu_ap']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'programs/undergraduate';
  $handler->display->display_options['menu']['title'] = 'ASU Degrees';
  $handler->display->display_options['menu']['weight'] = '50';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Page - UG majors */
  $handler = $view->new_display('page', 'Page - UG majors', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Majors';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_grid_plugin_style';
  $handler->display->display_options['style_options']['columns_horizontal'] = '4';
  $handler->display->display_options['style_options']['columns_vertical'] = '4';
  $handler->display->display_options['style_options']['columns_xs'] = '12';
  $handler->display->display_options['style_options']['columns_sm'] = '6';
  $handler->display->display_options['style_options']['columns_md'] = '3';
  $handler->display->display_options['style_options']['columns_lg'] = '3';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['separator'] = '<br>';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/programs/undergraduate/majors"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/programs/undergraduate/majors/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Degree image */
  $handler->display->display_options['fields']['field_degree_image']['id'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['table'] = 'field_data_field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['field'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['label'] = '';
  $handler->display->display_options['fields']['field_degree_image']['element_label_colon'] = FALSE;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_ap_awarded']['id'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['table'] = 'field_data_field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['field'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_ap_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Program description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['body']['alter']['more_link'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['more_link_text'] = 'read more';
  $handler->display->display_options['fields']['body']['alter']['more_link_path'] = '/node/[nid]';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['preserve_tags'] = '<p> <br> <i> <li> <ul> <ol> <div> <hr> <span> <title> <u>';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus']['id'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_ap_campus']['exclude'] = TRUE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['id'] = 'field_asu_ap_campus_1';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['label'] = 'Available Online';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['delta_offset'] = '0';
  /* Field: Content: Department code */
  $handler->display->display_options['fields']['field_asu_ap_department_code']['id'] = 'field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['table'] = 'field_data_field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['field'] = 'field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_department_code']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_ap']['id'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['field'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap']['alter']['text'] = '<div class="asu-ap-rewritten-fields">
    <div class="asu-ap-major-title">[field_asu_ap_awarded], [field_asu_ap]</div>
    [body]
    <div class="asu-ap-field-title">Location:</div> [field_asu_ap_campus]<br>
</div>';
  $handler->display->display_options['fields']['field_asu_ap']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
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
    'asu_ap' => 'asu_ap',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_ap_program) */
  $handler->display->display_options['filters']['field_asu_ap_program_value']['id'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['table'] = 'field_data_field_asu_ap_program';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['field'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['value'] = 'undergrad';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['group'] = 1;
  /* Filter criterion: Content: Cert option: True or False (field_asu_ap_cert) */
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['id'] = 'field_asu_ap_cert_value';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['table'] = 'field_data_field_asu_ap_cert';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['field'] = 'field_asu_ap_cert_value';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['value'] = 'false';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['group'] = 1;
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value']['id'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_asu_ap_value']['group'] = 1;
  /* Filter criterion: Content: Campus (field_asu_ap_campus) */
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['id'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['field'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator_id'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['label'] = 'Campus (field_asu_ap_campus)';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Downtown Phoenix campus',
      'operator' => '=',
      'value' => 'Downtown',
    ),
    2 => array(
      'title' => 'Polytechnic campus',
      'operator' => '=',
      'value' => 'Polytechnic',
    ),
    3 => array(
      'title' => 'Tempe campus',
      'operator' => '=',
      'value' => 'Tempe',
    ),
    4 => array(
      'title' => 'West campus',
      'operator' => '=',
      'value' => 'West',
    ),
    5 => array(
      'title' => 'Lake Havasu City',
      'operator' => '=',
      'value' => 'Havasu',
    ),
    6 => array(
      'title' => 'ASU@TheGilaValley',
      'operator' => '=',
      'value' => 'The Gila Valley',
    ),
    7 => array(
      'title' => 'ASU@Pinal',
      'operator' => '=',
      'value' => 'Pinal',
    ),
    8 => array(
      'title' => 'ASU@Yuma',
      'operator' => '=',
      'value' => 'Yuma',
    ),
    9 => array(
      'title' => 'Online',
      'operator' => '=',
      'value' => 'Online',
    ),
    10 => array(
      'title' => 'ASU@Northeastern Arizona',
      'operator' => '=',
      'value' => 'Northeastern Arizona',
    ),
    11 => array(
      'title' => 'ASU@Los Angeles',
      'operator' => '=',
      'value' => 'Los Angeles',
    ),
  );
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value_1']['id'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator_id'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['label'] = 'Degree (field_asu_ap)';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['label'] = 'Program Type';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'BSN',
      'operator' => '=',
      'value' => 'BSN',
    ),
    2 => array(
      'title' => 'BSLA',
      'operator' => '=',
      'value' => 'BSLA',
    ),
    4 => array(
      'title' => 'BSP',
      'operator' => '=',
      'value' => 'BSP',
    ),
    5 => array(
      'title' => 'BSW',
      'operator' => '=',
      'value' => 'BSW',
    ),
    6 => array(
      'title' => 'BA',
      'operator' => '=',
      'value' => 'BA',
    ),
    7 => array(
      'title' => 'BAE',
      'operator' => '=',
      'value' => 'BAE',
    ),
    8 => array(
      'title' => 'BAS',
      'operator' => '=',
      'value' => 'BAS',
    ),
    9 => array(
      'title' => 'BFA',
      'operator' => '=',
      'value' => 'BFA',
    ),
    10 => array(
      'title' => 'BGM',
      'operator' => '=',
      'value' => 'BGM',
    ),
    11 => array(
      'title' => 'BMUS',
      'operator' => '=',
      'value' => 'BMUS',
    ),
    12 => array(
      'title' => 'BS',
      'operator' => '=',
      'value' => 'BS',
    ),
    13 => array(
      'title' => 'BSD',
      'operator' => '=',
      'value' => 'BSD',
    ),
    14 => array(
      'title' => 'BSE',
      'operator' => '=',
      'value' => 'BSE',
    ),
  );
  $handler->display->display_options['path'] = 'programs/undergraduate/majors';

  /* Display: Page - UG minors/certs */
  $handler = $view->new_display('page', 'Page - UG minors/certs', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Minors & Certificates';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_grid_plugin_style';
  $handler->display->display_options['style_options']['columns_horizontal'] = '4';
  $handler->display->display_options['style_options']['columns_vertical'] = '4';
  $handler->display->display_options['style_options']['columns_xs'] = '12';
  $handler->display->display_options['style_options']['columns_sm'] = '6';
  $handler->display->display_options['style_options']['columns_md'] = '3';
  $handler->display->display_options['style_options']['columns_lg'] = '3';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['separator'] = '<br>';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/programs/undergraduate/minors-certs"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/programs/undergraduate/minors-certs/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
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
    'asu_ap' => 'asu_ap',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_ap_program) */
  $handler->display->display_options['filters']['field_asu_ap_program_value']['id'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['table'] = 'field_data_field_asu_ap_program';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['field'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['value'] = 'undergrad';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['group'] = 1;
  /* Filter criterion: Content: Cert option: True or False (field_asu_ap_cert) */
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['id'] = 'field_asu_ap_cert_value';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['table'] = 'field_data_field_asu_ap_cert';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['field'] = 'field_asu_ap_cert_value';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['value'] = 'true';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['group'] = 1;
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value']['id'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_asu_ap_value']['group'] = 1;
  /* Filter criterion: Content: Campus (field_asu_ap_campus) */
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['id'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['field'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator_id'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['label'] = 'Campus (field_asu_ap_campus)';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Downtown Phoenix campus',
      'operator' => '=',
      'value' => 'Downtown',
    ),
    2 => array(
      'title' => 'Polytechnic campus',
      'operator' => '=',
      'value' => 'Polytechnic',
    ),
    3 => array(
      'title' => 'Tempe campus',
      'operator' => '=',
      'value' => 'Tempe',
    ),
    4 => array(
      'title' => 'West campus',
      'operator' => '=',
      'value' => 'West',
    ),
    5 => array(
      'title' => 'Lake Havasu City',
      'operator' => '=',
      'value' => 'Havasu',
    ),
    6 => array(
      'title' => 'ASU@TheGilaValley',
      'operator' => '=',
      'value' => 'The Gila Valley',
    ),
    7 => array(
      'title' => 'ASU@Pinal',
      'operator' => '=',
      'value' => 'Pinal',
    ),
    8 => array(
      'title' => 'ASU@Yuma',
      'operator' => '=',
      'value' => 'Yuma',
    ),
    9 => array(
      'title' => 'Online',
      'operator' => '=',
      'value' => 'Online',
    ),
    10 => array(
      'title' => 'ASU@Northeastern Arizona',
      'operator' => '=',
      'value' => 'Northeastern Arizona',
    ),
    11 => array(
      'title' => 'ASU@Los Angeles',
      'operator' => '=',
      'value' => 'Los Angeles',
    ),
  );
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value_1']['id'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator_id'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['label'] = 'Degree (field_asu_ap)';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['label'] = 'Program Type';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'BFA',
      'operator' => '=',
      'value' => 'BFA',
    ),
    2 => array(
      'title' => 'BGM',
      'operator' => '=',
      'value' => 'BGM',
    ),
    3 => array(
      'title' => 'BMUS',
      'operator' => '=',
      'value' => 'BMUS',
    ),
    4 => array(
      'title' => 'BS',
      'operator' => '=',
      'value' => 'BS',
    ),
    5 => array(
      'title' => 'BSD',
      'operator' => '=',
      'value' => 'BSD',
    ),
    6 => array(
      'title' => 'BSE',
      'operator' => '=',
      'value' => 'BSE',
    ),
    7 => array(
      'title' => 'BSLA',
      'operator' => '=',
      'value' => 'BSLA',
    ),
    8 => array(
      'title' => 'BSN',
      'operator' => '=',
      'value' => 'BSN',
    ),
    9 => array(
      'title' => 'BSP',
      'operator' => '=',
      'value' => 'BSP',
    ),
    10 => array(
      'title' => 'BSW',
      'operator' => '=',
      'value' => 'BSW',
    ),
    11 => array(
      'title' => 'Minor',
      'operator' => '=',
      'value' => 'Minor',
    ),
    12 => array(
      'title' => 'Certificate',
      'operator' => '=',
      'value' => 'Certificate',
    ),
    13 => array(
      'title' => 'BA',
      'operator' => '=',
      'value' => 'BA',
    ),
    14 => array(
      'title' => 'BAE',
      'operator' => '=',
      'value' => 'BAE',
    ),
    15 => array(
      'title' => 'BAS',
      'operator' => '=',
      'value' => 'BAS',
    ),
  );
  $handler->display->display_options['path'] = 'programs/undergraduate/minors-certs';

  /* Display: Page - UG all (list) */
  $handler = $view->new_display('page', 'Page - UG all (list)', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All Undergraduate Programs';
  $handler->display->display_options['display_description'] = 'Displays all undergraduate degrees';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_table_plugin_style';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'field_asu_degree_awarded' => 'field_asu_degree_awarded',
    'field_asu_degree' => 'field_asu_degree',
    'field_asu_degree_campus' => 'field_asu_degree_campus',
    'field_asu_degree_campus_1' => 'field_asu_degree_campus_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree_awarded' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_asu_degree_campus' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree_campus_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['bootstrap_styles'] = array(
    'striped' => 'striped',
    'bordered' => 0,
    'hover' => 0,
    'condensed' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/programs/undergraduate/all"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/programs/undergraduate/all/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_ap_awarded']['id'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['table'] = 'field_data_field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['field'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['label'] = 'Program';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_ap_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_ap']['id'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['field'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['element_label_colon'] = FALSE;
  /* Field: Content: Major map URL */
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['id'] = 'field_asu_ap_major_map_url';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['table'] = 'field_data_field_asu_ap_major_map_url';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['field'] = 'field_asu_ap_major_map_url';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['label'] = 'Course Plan';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['alter']['text'] = '<a href="[field_asu_ap_major_map_url]">Major Map</a>';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['type'] = 'link_plain';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus']['id'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_ap_campus']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'programs/undergraduate/list';
  $handler->display->display_options['menu']['title'] = 'ASU Degrees';
  $handler->display->display_options['menu']['weight'] = '50';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Page - UG majors (list) */
  $handler = $view->new_display('page', 'Page - UG majors (list)', 'page_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Majors';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_table_plugin_style';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_asu_degree_awarded' => 'field_asu_degree_awarded',
    'field_asu_degree' => 'field_asu_degree',
    'field_asu_degree_major_map_url' => 'field_asu_degree_major_map_url',
    'field_asu_degree_campus' => 'field_asu_degree_campus',
    'field_asu_degree_campus_1' => 'field_asu_degree_campus_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_asu_degree_awarded' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_asu_degree_major_map_url' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree_campus' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree_campus_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['bootstrap_styles'] = array(
    'striped' => 'striped',
    'bordered' => 0,
    'hover' => 0,
    'condensed' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/programs/undergraduate/majors"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/programs/undergraduate/majors/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_ap_awarded']['id'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['table'] = 'field_data_field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['field'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['label'] = 'Program';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_ap_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_ap']['id'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['field'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['element_label_colon'] = FALSE;
  /* Field: Content: Major map URL */
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['id'] = 'field_asu_ap_major_map_url';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['table'] = 'field_data_field_asu_ap_major_map_url';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['field'] = 'field_asu_ap_major_map_url';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['label'] = 'Course Plan';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['alter']['text'] = '<a href="[field_asu_ap_major_map_url]">Major Map</a>';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_asu_ap_major_map_url']['type'] = 'link_plain';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus']['id'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_ap_campus']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
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
    'asu_ap' => 'asu_ap',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_ap_program) */
  $handler->display->display_options['filters']['field_asu_ap_program_value']['id'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['table'] = 'field_data_field_asu_ap_program';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['field'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['value'] = 'undergrad';
  /* Filter criterion: Content: Cert option: True or False (field_asu_ap_cert) */
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['id'] = 'field_asu_ap_cert_value';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['table'] = 'field_data_field_asu_ap_cert';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['field'] = 'field_asu_ap_cert_value';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['value'] = 'false';
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value']['id'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['operator'] = 'not empty';
  /* Filter criterion: Content: Campus (field_asu_ap_campus) */
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['id'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['field'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator_id'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['label'] = 'Campus (field_asu_ap_campus)';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Downtown Phoenix campus',
      'operator' => '=',
      'value' => 'Downtown',
    ),
    2 => array(
      'title' => 'Polytechnic campus',
      'operator' => '=',
      'value' => 'Polytechnic',
    ),
    3 => array(
      'title' => 'Tempe campus',
      'operator' => '=',
      'value' => 'Tempe',
    ),
    4 => array(
      'title' => 'West campus',
      'operator' => '=',
      'value' => 'West',
    ),
    5 => array(
      'title' => 'Lake Havasu City',
      'operator' => '=',
      'value' => 'Havasu',
    ),
    6 => array(
      'title' => 'ASU@TheGilaValley',
      'operator' => '=',
      'value' => 'The Gila Valley',
    ),
    7 => array(
      'title' => 'ASU@Pinal',
      'operator' => '=',
      'value' => 'Pinal',
    ),
    8 => array(
      'title' => 'ASU@Yuma',
      'operator' => '=',
      'value' => 'Yuma',
    ),
    9 => array(
      'title' => 'Online',
      'operator' => '=',
      'value' => 'Online',
    ),
    10 => array(
      'title' => 'ASU@Northeastern Arizona',
      'operator' => '=',
      'value' => 'Northeastern Arizona',
    ),
    11 => array(
      'title' => 'ASU@Los Angeles',
      'operator' => '=',
      'value' => 'Los Angeles',
    ),
  );
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value_1']['id'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator_id'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['label'] = 'Degree (field_asu_ap)';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['label'] = 'Degree Type';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'BSN',
      'operator' => '=',
      'value' => 'BSN',
    ),
    2 => array(
      'title' => 'BSLA',
      'operator' => '=',
      'value' => 'BSLA',
    ),
    6 => array(
      'title' => 'BSP',
      'operator' => '=',
      'value' => 'BSP',
    ),
    7 => array(
      'title' => 'BSW',
      'operator' => '=',
      'value' => 'BSW',
    ),
    8 => array(
      'title' => 'BA',
      'operator' => '=',
      'value' => 'BA',
    ),
    9 => array(
      'title' => 'BAE',
      'operator' => '=',
      'value' => 'BAE',
    ),
    10 => array(
      'title' => 'BAS',
      'operator' => '=',
      'value' => 'BAS',
    ),
    11 => array(
      'title' => 'BFA',
      'operator' => '=',
      'value' => 'BFA',
    ),
    12 => array(
      'title' => 'BGM',
      'operator' => '=',
      'value' => 'BGM',
    ),
    13 => array(
      'title' => 'BMUS',
      'operator' => '=',
      'value' => 'BMUS',
    ),
    14 => array(
      'title' => 'BS',
      'operator' => '=',
      'value' => 'BS',
    ),
    15 => array(
      'title' => 'BSD',
      'operator' => '=',
      'value' => 'BSD',
    ),
    16 => array(
      'title' => 'BSE',
      'operator' => '=',
      'value' => 'BSE',
    ),
  );
  $handler->display->display_options['path'] = 'programs/undergraduate/majors/list';

  /* Display: Page - UG minors/certs (list) */
  $handler = $view->new_display('page', 'Page - UG minors/certs (list)', 'page_6');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Minors & Certificates';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_table_plugin_style';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_asu_degree_awarded' => 'field_asu_degree_awarded',
    'field_asu_degree' => 'field_asu_degree',
    'field_asu_degree_campus' => 'field_asu_degree_campus',
    'field_asu_degree_campus_1' => 'field_asu_degree_campus_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_asu_degree_awarded' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_asu_degree_campus' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree_campus_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['bootstrap_styles'] = array(
    'striped' => 'striped',
    'bordered' => 0,
    'hover' => 0,
    'condensed' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/programs/undergraduate/minors-certs"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/programs/undergraduate/minors-certs/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_ap_awarded']['id'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['table'] = 'field_data_field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['field'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['label'] = 'Program';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_ap_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_ap']['id'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['field'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['element_label_colon'] = FALSE;
  /* Field: Content: URL for program at ASU Degree Search */
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['id'] = 'field_asu_ap_asuds_url';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['table'] = 'field_data_field_asu_ap_asuds_url';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['field'] = 'field_asu_ap_asuds_url';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['label'] = 'Course Plan';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['alter']['text'] = '<a href="[field_asu_ap_asuds_url]">Plan of Study</a>';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['type'] = 'link_plain';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus']['id'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_ap_campus']['delta_offset'] = '0';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
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
    'asu_ap' => 'asu_ap',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_ap_program) */
  $handler->display->display_options['filters']['field_asu_ap_program_value']['id'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['table'] = 'field_data_field_asu_ap_program';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['field'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['value'] = 'undergrad';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['group'] = 1;
  /* Filter criterion: Content: Cert option: True or False (field_asu_ap_cert) */
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['id'] = 'field_asu_ap_cert_value';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['table'] = 'field_data_field_asu_ap_cert';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['field'] = 'field_asu_ap_cert_value';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['value'] = 'true';
  $handler->display->display_options['filters']['field_asu_ap_cert_value']['group'] = 1;
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value']['id'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_asu_ap_value']['group'] = 1;
  /* Filter criterion: Content: Campus (field_asu_ap_campus) */
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['id'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['field'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['value'] = 'undergrad';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator_id'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['label'] = 'Campus (field_asu_ap_campus)';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Downtown Phoenix campus',
      'operator' => '=',
      'value' => 'Downtown',
    ),
    2 => array(
      'title' => 'Polytechnic campus',
      'operator' => '=',
      'value' => 'Polytechnic',
    ),
    3 => array(
      'title' => 'Tempe campus',
      'operator' => '=',
      'value' => 'Tempe',
    ),
    4 => array(
      'title' => 'West campus',
      'operator' => '=',
      'value' => 'West',
    ),
    5 => array(
      'title' => 'Lake Havasu City',
      'operator' => '=',
      'value' => 'Havasu',
    ),
    6 => array(
      'title' => 'ASU@TheGilaValley',
      'operator' => '=',
      'value' => 'The Gila Valley',
    ),
    7 => array(
      'title' => 'ASU@Pinal',
      'operator' => '=',
      'value' => 'Pinal',
    ),
    8 => array(
      'title' => 'ASU@Yuma',
      'operator' => '=',
      'value' => 'Yuma',
    ),
    9 => array(
      'title' => 'Online',
      'operator' => '=',
      'value' => 'Online',
    ),
    10 => array(
      'title' => 'ASU@Northeastern Arizona',
      'operator' => '=',
      'value' => 'Northeastern Arizona',
    ),
    11 => array(
      'title' => 'ASU@Los Angeles',
      'operator' => '=',
      'value' => 'Los Angeles',
    ),
  );
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value_1']['id'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator_id'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['label'] = 'Degree (field_asu_ap)';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['label'] = 'Degree Type';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Minor',
      'operator' => '=',
      'value' => 'Minor',
    ),
    2 => array(
      'title' => 'Certificate',
      'operator' => '=',
      'value' => 'Certificate',
    ),
  );
  $handler->display->display_options['path'] = 'programs/undergraduate/minors-certs/list';

  /* Display: Page - Grad */
  $handler = $view->new_display('page', 'Page - Grad', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All Graduate Programs';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_grid_plugin_style';
  $handler->display->display_options['style_options']['columns_horizontal'] = '4';
  $handler->display->display_options['style_options']['columns_vertical'] = '4';
  $handler->display->display_options['style_options']['columns_xs'] = '12';
  $handler->display->display_options['style_options']['columns_sm'] = '6';
  $handler->display->display_options['style_options']['columns_md'] = '3';
  $handler->display->display_options['style_options']['columns_lg'] = '3';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['separator'] = '<br>';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/programs/graduate"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/programs/graduate/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Degree image */
  $handler->display->display_options['fields']['field_degree_image']['id'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['table'] = 'field_data_field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['field'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['label'] = '';
  $handler->display->display_options['fields']['field_degree_image']['element_label_colon'] = FALSE;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_ap_awarded']['id'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['table'] = 'field_data_field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['field'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_ap_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Program description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['body']['alter']['more_link'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['more_link_text'] = 'read more';
  $handler->display->display_options['fields']['body']['alter']['more_link_path'] = '/node/[nid]';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['preserve_tags'] = '<p> <br> <i> <li> <ul> <ol> <div> <hr> <span> <title> <u>';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus']['id'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_ap_campus']['exclude'] = TRUE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['id'] = 'field_asu_ap_campus_1';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['label'] = 'Available Online';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_ap_campus_1']['delta_offset'] = '0';
  /* Field: Content: Department code */
  $handler->display->display_options['fields']['field_asu_ap_department_code']['id'] = 'field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['table'] = 'field_data_field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['field'] = 'field_asu_ap_department_code';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap_department_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_department_code']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_ap']['id'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['field'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['label'] = '';
  $handler->display->display_options['fields']['field_asu_ap']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap']['alter']['text'] = '<div class="asu-ap-rewritten-fields">
    <div class="asu-ap-major-title">[field_asu_ap_awarded]</div>
    [body]
    <div class="asu-ap-field-title">Location:</div> [field_asu_ap_campus]
</div>';
  $handler->display->display_options['fields']['field_asu_ap']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
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
    'asu_ap' => 'asu_ap',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_ap_program) */
  $handler->display->display_options['filters']['field_asu_ap_program_value']['id'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['table'] = 'field_data_field_asu_ap_program';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['field'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['value'] = 'graduate';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['group'] = 1;
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value']['id'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_asu_ap_value']['group'] = 1;
  /* Filter criterion: Content: Campus (field_asu_ap_campus) */
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['id'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['field'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator_id'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['label'] = 'Campus (field_asu_ap_campus)';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Downtown Phoenix campus',
      'operator' => '=',
      'value' => 'Downtown',
    ),
    2 => array(
      'title' => 'Polytechnic campus',
      'operator' => '=',
      'value' => 'Polytechnic',
    ),
    3 => array(
      'title' => 'Tempe campus',
      'operator' => '=',
      'value' => 'Tempe',
    ),
    4 => array(
      'title' => 'West campus',
      'operator' => '=',
      'value' => 'West',
    ),
    5 => array(
      'title' => 'Thunderbird campus',
      'operator' => '=',
      'value' => 'Thunderbird',
    ),
    6 => array(
      'title' => 'Tucson',
      'operator' => '=',
      'value' => 'Tucson',
    ),
  );
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value_1']['id'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator_id'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['label'] = 'Degree (field_asu_ap)';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['label'] = 'Degree Level';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Masters',
      'operator' => 'word',
      'value' => 'EMPA EMSL LL.M. MA MAcc MALM MArch MAS MBA MC MCS MCSt MEd MEng MFA MGM MHI MIA MID MIHC MLA MLS MLSt MM MMC MNLM MNS MPA MPE MPP MPSLA MREDev MS',
    ),
    2 => array(
      'title' => 'Doctorate',
      'operator' => 'word',
      'value' => 'AUD DBA DBH DMA DNP EdD JD PHD',
    ),
    3 => array(
      'title' => 'Certificate',
      'operator' => '=',
      'value' => 'Certificate',
    ),
  );
  $handler->display->display_options['path'] = 'programs/graduate';

  /* Display: Page - Grad (list) */
  $handler = $view->new_display('page', 'Page - Grad (list)', 'page_7');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All Graduate Programs';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_table_plugin_style';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_asu_degree_awarded' => 'field_asu_degree_awarded',
    'field_asu_degree' => 'field_asu_degree',
    'field_asu_degree_campus' => 'field_asu_degree_campus',
    'field_asu_degree_campus_1' => 'field_asu_degree_campus_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_asu_degree_awarded' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_asu_degree_campus' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_degree_campus_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['bootstrap_styles'] = array(
    'striped' => 'striped',
    'bordered' => 0,
    'hover' => 0,
    'condensed' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/programs/graduate"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/programs/graduate/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_ap_awarded']['id'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['table'] = 'field_data_field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['field'] = 'field_asu_ap_awarded';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['label'] = 'Program';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_ap_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_ap_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_ap']['id'] = 'field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['fields']['field_asu_ap']['field'] = 'field_asu_ap';
  /* Field: Content: URL for program at ASU Degree Search */
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['id'] = 'field_asu_ap_asuds_url';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['table'] = 'field_data_field_asu_ap_asuds_url';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['field'] = 'field_asu_ap_asuds_url';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['label'] = 'Course Plan';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['alter']['text'] = '<a href="[field_asu_ap_asuds_url]">Plan of Study</a>';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_asu_ap_asuds_url']['type'] = 'link_plain';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_ap_campus']['id'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['field'] = 'field_asu_ap_campus';
  $handler->display->display_options['fields']['field_asu_ap_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_ap_campus']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
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
    'asu_ap' => 'asu_ap',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_ap_program) */
  $handler->display->display_options['filters']['field_asu_ap_program_value']['id'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['table'] = 'field_data_field_asu_ap_program';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['field'] = 'field_asu_ap_program_value';
  $handler->display->display_options['filters']['field_asu_ap_program_value']['value'] = 'graduate';
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value']['id'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value']['operator'] = 'not empty';
  /* Filter criterion: Content: Campus (field_asu_ap_campus) */
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['id'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['table'] = 'field_data_field_asu_ap_campus';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['field'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator_id'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['label'] = 'Campus (field_asu_ap_campus)';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['operator'] = 'field_asu_ap_campus_value_op';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['expose']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['identifier'] = 'field_asu_ap_campus_value';
  $handler->display->display_options['filters']['field_asu_ap_campus_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Downtown Phoenix campus',
      'operator' => '=',
      'value' => 'Downtown',
    ),
    2 => array(
      'title' => 'Polytechnic campus',
      'operator' => '=',
      'value' => 'Polytechnic',
    ),
    3 => array(
      'title' => 'Tempe campus',
      'operator' => '=',
      'value' => 'Tempe',
    ),
    4 => array(
      'title' => 'West campus',
      'operator' => '=',
      'value' => 'West',
    ),
    5 => array(
      'title' => 'Thunderbird campus',
      'operator' => '=',
      'value' => 'Thunderbird',
    ),
    6 => array(
      'title' => 'Tucson',
      'operator' => '=',
      'value' => 'Tucson',
    ),
  );
  /* Filter criterion: Content: Degree (field_asu_ap) */
  $handler->display->display_options['filters']['field_asu_ap_value_1']['id'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['table'] = 'field_data_field_asu_ap';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['field'] = 'field_asu_ap_value';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator_id'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['label'] = 'Degree (field_asu_ap)';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['operator'] = 'field_asu_ap_value_1_op';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['expose']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['label'] = 'Degree Level';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['identifier'] = 'field_asu_ap_value_1';
  $handler->display->display_options['filters']['field_asu_ap_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Masters',
      'operator' => 'word',
      'value' => 'EMSL LL.M. MA MAcc MArch MAS MBA MC MCS MCSt MEd MEng MFA MGM MHI MIA MID MLA MLS MLSt MM MMC MNS MPA MPE MPP MPSLA MREDev MS MS',
    ),
    2 => array(
      'title' => 'Doctorate',
      'operator' => 'word',
      'value' => 'AUD DBA DBH DMA DNP EdD PHD',
    ),
    3 => array(
      'title' => 'Certificate',
      'operator' => '=',
      'value' => 'Certificate',
    ),
  );
  $handler->display->display_options['path'] = 'programs/graduate/list';
  $export['asu_ap_view'] = $view;

  return $export;
}
