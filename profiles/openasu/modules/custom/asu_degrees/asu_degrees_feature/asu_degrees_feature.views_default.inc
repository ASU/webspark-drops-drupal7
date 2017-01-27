<?php
/**
 * @file
 * asu_degrees_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function asu_degrees_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'asu_degrees_feature';
  $view->description = 'Displays ASU Degree pages in various configurations and groups.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ASU Degrees';
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
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_grid_plugin_style';
  $handler->display->display_options['style_options']['columns'] = '2';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['separator'] = '<br>';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/asu_degrees/ugrad/all"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/asu_degrees/ugrad/all/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No Degrees imported';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No Degrees have been imported.  Please check back later.';
  $handler->display->display_options['empty']['area']['format'] = 'panopoly_wysiwyg_text';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Degree Image */
  $handler->display->display_options['fields']['field_degree_image']['id'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['table'] = 'field_data_field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['field'] = 'field_degree_image';
  $handler->display->display_options['fields']['field_degree_image']['label'] = '';
  $handler->display->display_options['fields']['field_degree_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_degree_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_degree_image']['settings'] = array(
    'image_style' => 'asu_degree_image',
    'image_link' => '',
  );
  /* Field: Content: Degree Awarded */
  $handler->display->display_options['fields']['field_asu_degree_awarded']['id'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['table'] = 'field_data_field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['field'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['label'] = '';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_degree_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Degree Description (long) */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '125';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus']['id'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_degree_campus']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_limit'] = '7';
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_offset'] = '0';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['id'] = 'field_asu_degree_campus_1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['label'] = 'Available Online';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_offset'] = '0';
  /* Field: Content: Department Code */
  $handler->display->display_options['fields']['field_asu_degree_department_code']['id'] = 'field_asu_degree_department_code';
  $handler->display->display_options['fields']['field_asu_degree_department_code']['table'] = 'field_data_field_asu_degree_department_code';
  $handler->display->display_options['fields']['field_asu_degree_department_code']['field'] = 'field_asu_degree_department_code';
  $handler->display->display_options['fields']['field_asu_degree_department_code']['label'] = '';
  $handler->display->display_options['fields']['field_asu_degree_department_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_department_code']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_degree']['id'] = 'field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['field'] = 'field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['label'] = '';
  $handler->display->display_options['fields']['field_asu_degree']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree']['alter']['text'] = '<div class="asu-degree-rewritten-fields">
    <div class="asu-degree-major-title">[field_asu_degree_awarded] ([field_asu_degree])</div>
    [body]
    <div class="asu-degree-field-title">Location:</div> [field_asu_degree_campus]<br>
    <div class="asu-degree-field-title">Degree Type:</div> [field_asu_degree]<br>
    <div class="asu-degree-field-title">Available Online:</div> [field_asu_degree_campus_1]
</div>';
  $handler->display->display_options['fields']['field_asu_degree']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Degree Awarded (field_asu_degree_awarded) */
  $handler->display->display_options['sorts']['field_asu_degree_awarded_value']['id'] = 'field_asu_degree_awarded_value';
  $handler->display->display_options['sorts']['field_asu_degree_awarded_value']['table'] = 'field_data_field_asu_degree_awarded';
  $handler->display->display_options['sorts']['field_asu_degree_awarded_value']['field'] = 'field_asu_degree_awarded_value';
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
    'asu_degree' => 'asu_degree',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['group'] = 1;
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value']['id'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['operator'] = 'not empty';
  /* Filter criterion: Content: Campus (field_asu_degree_campus) */
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['id'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['field'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator_id'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['label'] = 'Campus (field_asu_degree_campus)';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['group_items'] = array(
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
  );
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value_1']['id'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator_id'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['label'] = 'Degree (field_asu_degree)';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['label'] = 'Degree Type';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'BA',
      'operator' => '=',
      'value' => 'BA',
    ),
    2 => array(
      'title' => 'BAE',
      'operator' => '=',
      'value' => 'BAE',
    ),
    3 => array(
      'title' => 'BAS',
      'operator' => '=',
      'value' => 'BAS',
    ),
    4 => array(
      'title' => 'BFA',
      'operator' => '=',
      'value' => 'BFA',
    ),
    5 => array(
      'title' => 'BGM',
      'operator' => '=',
      'value' => 'BGM',
    ),
    6 => array(
      'title' => 'BMUS',
      'operator' => '=',
      'value' => 'BMUS',
    ),
    7 => array(
      'title' => 'BS',
      'operator' => '=',
      'value' => 'BS',
    ),
    8 => array(
      'title' => 'BSD',
      'operator' => '=',
      'value' => 'BSD',
    ),
    9 => array(
      'title' => 'BSE',
      'operator' => '=',
      'value' => 'BSE',
    ),
    10 => array(
      'title' => 'BSLA',
      'operator' => '=',
      'value' => 'BSLA',
    ),
    11 => array(
      'title' => 'BSN',
      'operator' => '=',
      'value' => 'BSN',
    ),
    12 => array(
      'title' => 'BSP',
      'operator' => '=',
      'value' => 'BSP',
    ),
    13 => array(
      'title' => 'BSW',
      'operator' => '=',
      'value' => 'BSW',
    ),
    14 => array(
      'title' => 'Minor',
      'operator' => '=',
      'value' => 'Minor',
    ),
    15 => array(
      'title' => 'Certificate',
      'operator' => '=',
      'value' => 'Certificate',
    ),
  );

  /* Display: Page - Undergrad all */
  $handler = $view->new_display('page', 'Page - Undergrad all', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate All';
  $handler->display->display_options['display_description'] = 'Displays all undergraduate degrees';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_grid_plugin_style';
  $handler->display->display_options['style_options']['columns'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['separator'] = '<br>';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'asu_degrees/ugrad/all';
  $handler->display->display_options['menu']['title'] = 'ASU Degrees';
  $handler->display->display_options['menu']['weight'] = '50';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Page - Undergrad majors */
  $handler = $view->new_display('page', 'Page - Undergrad majors', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Majors';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/asu_degrees/ugrad/major"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/asu_degrees/ugrad/major/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
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
    'asu_degree' => 'asu_degree',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['group'] = 1;
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['value'] = 'false';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['group'] = 1;
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value']['id'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_asu_degree_value']['group'] = 1;
  /* Filter criterion: Content: Campus (field_asu_degree_campus) */
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['id'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['field'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator_id'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['label'] = 'Campus (field_asu_degree_campus)';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['group_items'] = array(
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
  );
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value_1']['id'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator_id'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['label'] = 'Degree (field_asu_degree)';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['label'] = 'Degree Type';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'BSP',
      'operator' => '=',
      'value' => 'BSP',
    ),
    2 => array(
      'title' => 'BSW',
      'operator' => '=',
      'value' => 'BSW',
    ),
    5 => array(
      'title' => 'BA',
      'operator' => '=',
      'value' => 'BA',
    ),
    6 => array(
      'title' => 'BAE',
      'operator' => '=',
      'value' => 'BAE',
    ),
    7 => array(
      'title' => 'BAS',
      'operator' => '=',
      'value' => 'BAS',
    ),
    8 => array(
      'title' => 'BFA',
      'operator' => '=',
      'value' => 'BFA',
    ),
    9 => array(
      'title' => 'BGM',
      'operator' => '=',
      'value' => 'BGM',
    ),
    10 => array(
      'title' => 'BMUS',
      'operator' => '=',
      'value' => 'BMUS',
    ),
    11 => array(
      'title' => 'BS',
      'operator' => '=',
      'value' => 'BS',
    ),
    12 => array(
      'title' => 'BSD',
      'operator' => '=',
      'value' => 'BSD',
    ),
    13 => array(
      'title' => 'BSE',
      'operator' => '=',
      'value' => 'BSE',
    ),
    14 => array(
      'title' => 'BSLA',
      'operator' => '=',
      'value' => 'BSLA',
    ),
    15 => array(
      'title' => 'BSN',
      'operator' => '=',
      'value' => 'BSN',
    ),
  );
  $handler->display->display_options['path'] = 'asu_degrees/ugrad/major';

  /* Display: Page - Undergrad minors/certificates */
  $handler = $view->new_display('page', 'Page - Undergrad minors/certificates', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Minors/Certificates';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/asu_degrees/ugrad/minor_cert"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/asu_degrees/ugrad/minor_cert/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
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
    'asu_degree' => 'asu_degree',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['group'] = 1;
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['value'] = 'true';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['group'] = 1;
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value']['id'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_asu_degree_value']['group'] = 1;
  /* Filter criterion: Content: Campus (field_asu_degree_campus) */
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['id'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['field'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator_id'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['label'] = 'Campus (field_asu_degree_campus)';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['group_items'] = array(
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
  );
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value_1']['id'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator_id'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['label'] = 'Degree (field_asu_degree)';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['label'] = 'Degree Type';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['group_items'] = array(
    3 => array(
      'title' => 'Minor',
      'operator' => '=',
      'value' => 'Minor',
    ),
    4 => array(
      'title' => 'Certificate',
      'operator' => '=',
      'value' => 'Certificate',
    ),
  );
  $handler->display->display_options['path'] = 'asu_degrees/ugrad/minor_cert';

  /* Display: Page - Graduate */
  $handler = $view->new_display('page', 'Page - Graduate', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Graduate';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="pull-right btn-group">
<a class="btn btn-default" href="/asu_degrees/grad"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/asu_degrees/grad/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'asu_degree' => 'asu_degree',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'graduate';
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value']['id'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['operator'] = 'not empty';
  /* Filter criterion: Content: Campus (field_asu_degree_campus) */
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['id'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['field'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator_id'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['label'] = 'Campus (field_asu_degree_campus)';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['group_items'] = array(
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
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value_1']['id'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator_id'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['label'] = 'Degree (field_asu_degree)';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['label'] = 'Degree Level';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Masters',
      'operator' => 'word',
      'value' => 'EMSL LL.M. MA MAcc MArch MAS MBA MC MCS MCSt MEd MEng MFA MGM MHI MIA MID MIHC MLA MLS MLSt MM MMC MNLM MNS MPA MPE MPP MPSLA MR',
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
  $handler->display->display_options['path'] = 'asu_degrees/grad';

  /* Display: Page - Undergrad all (list) */
  $handler = $view->new_display('page', 'Page - Undergrad all (list)', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate All';
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
<a class="btn btn-default" href="/asu_degrees/ugrad/all"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/asu_degrees/ugrad/all/list"><i class="fa fa-th-list fa-lg"></i> List</a>
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
  /* Field: Content: Degree Awarded */
  $handler->display->display_options['fields']['field_asu_degree_awarded']['id'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['table'] = 'field_data_field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['field'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['label'] = 'Program';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_degree_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_degree']['id'] = 'field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['field'] = 'field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['element_label_colon'] = FALSE;
  /* Field: Content: Major Map URL */
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['id'] = 'field_asu_degree_major_map_url';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['table'] = 'field_data_field_asu_degree_major_map_url';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['field'] = 'field_asu_degree_major_map_url';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['label'] = 'Course Plan';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['alter']['text'] = '<a href="[field_asu_degree_major_map_url]">Major Map</a>';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['type'] = 'link_plain';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus']['id'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_limit'] = '7';
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_offset'] = '0';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['id'] = 'field_asu_degree_campus_1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['label'] = 'Available Online';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'asu_degrees/ugrad/all/list';
  $handler->display->display_options['menu']['title'] = 'ASU Degrees';
  $handler->display->display_options['menu']['weight'] = '50';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Page - Undergrad majors (list) */
  $handler = $view->new_display('page', 'Page - Undergrad majors (list)', 'page_5');
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
<a class="btn btn-default" href="/asu_degrees/ugrad/major"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/asu_degrees/ugrad/major/list"><i class="fa fa-th-list fa-lg"></i> List</a>
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
  /* Field: Content: Degree Awarded */
  $handler->display->display_options['fields']['field_asu_degree_awarded']['id'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['table'] = 'field_data_field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['field'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['label'] = 'Program';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_degree_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_degree']['id'] = 'field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['field'] = 'field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['element_label_colon'] = FALSE;
  /* Field: Content: Major Map URL */
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['id'] = 'field_asu_degree_major_map_url';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['table'] = 'field_data_field_asu_degree_major_map_url';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['field'] = 'field_asu_degree_major_map_url';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['label'] = 'Course Plan';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['alter']['text'] = '<a href="[field_asu_degree_major_map_url]">Major Map</a>';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_asu_degree_major_map_url']['type'] = 'link_plain';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus']['id'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_limit'] = '7';
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_offset'] = '0';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['id'] = 'field_asu_degree_campus_1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['label'] = 'Available Online';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_offset'] = '0';
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
    'asu_degree' => 'asu_degree',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['group'] = 1;
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['value'] = 'false';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['group'] = 1;
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value']['id'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_asu_degree_value']['group'] = 1;
  /* Filter criterion: Content: Campus (field_asu_degree_campus) */
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['id'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['field'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator_id'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['label'] = 'Campus (field_asu_degree_campus)';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['group_items'] = array(
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
  );
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value_1']['id'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator_id'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['label'] = 'Degree (field_asu_degree)';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['label'] = 'Degree Type';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'BSP',
      'operator' => '=',
      'value' => 'BSP',
    ),
    2 => array(
      'title' => 'BSW',
      'operator' => '=',
      'value' => 'BSW',
    ),
    5 => array(
      'title' => 'BA',
      'operator' => '=',
      'value' => 'BA',
    ),
    6 => array(
      'title' => 'BAE',
      'operator' => '=',
      'value' => 'BAE',
    ),
    7 => array(
      'title' => 'BAS',
      'operator' => '=',
      'value' => 'BAS',
    ),
    8 => array(
      'title' => 'BFA',
      'operator' => '=',
      'value' => 'BFA',
    ),
    9 => array(
      'title' => 'BGM',
      'operator' => '=',
      'value' => 'BGM',
    ),
    10 => array(
      'title' => 'BMUS',
      'operator' => '=',
      'value' => 'BMUS',
    ),
    11 => array(
      'title' => 'BS',
      'operator' => '=',
      'value' => 'BS',
    ),
    12 => array(
      'title' => 'BSD',
      'operator' => '=',
      'value' => 'BSD',
    ),
    13 => array(
      'title' => 'BSE',
      'operator' => '=',
      'value' => 'BSE',
    ),
    14 => array(
      'title' => 'BSLA',
      'operator' => '=',
      'value' => 'BSLA',
    ),
    15 => array(
      'title' => 'BSN',
      'operator' => '=',
      'value' => 'BSN',
    ),
  );
  $handler->display->display_options['path'] = 'asu_degrees/ugrad/major/list';

  /* Display: Page - Undergrad minors/certificates (list) */
  $handler = $view->new_display('page', 'Page - Undergrad minors/certificates (list)', 'page_6');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Minors/Certificates';
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
<a class="btn btn-default" href="/asu_degrees/ugrad/minor_cert"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/asu_degrees/ugrad/minor_cert/list"><i class="fa fa-th-list fa-lg"></i> List</a>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Degree Awarded */
  $handler->display->display_options['fields']['field_asu_degree_awarded']['id'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['table'] = 'field_data_field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['field'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['label'] = 'Program';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_degree_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_degree']['id'] = 'field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['field'] = 'field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['element_label_colon'] = FALSE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus']['id'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_limit'] = '7';
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_offset'] = '0';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['id'] = 'field_asu_degree_campus_1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['label'] = 'Available Online';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_offset'] = '0';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
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
    'asu_degree' => 'asu_degree',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['group'] = 1;
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['value'] = 'true';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['group'] = 1;
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value']['id'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_asu_degree_value']['group'] = 1;
  /* Filter criterion: Content: Campus (field_asu_degree_campus) */
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['id'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['field'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator_id'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['label'] = 'Campus (field_asu_degree_campus)';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['group_items'] = array(
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
  );
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value_1']['id'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group'] = 1;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator_id'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['label'] = 'Degree (field_asu_degree)';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['label'] = 'Degree Type';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['group_items'] = array(
    3 => array(
      'title' => 'Minor',
      'operator' => '=',
      'value' => 'Minor',
    ),
    4 => array(
      'title' => 'Certificate',
      'operator' => '=',
      'value' => 'Certificate',
    ),
  );
  $handler->display->display_options['path'] = 'asu_degrees/ugrad/minor_cert/list';

  /* Display: Page - Graduate (list) */
  $handler = $view->new_display('page', 'Page - Graduate (list)', 'page_7');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Graduate';
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
<a class="btn btn-default" href="/asu_degrees/grad"><i class="fa fa-th-large fa-lg"></i> Grid</a><a class="btn btn-default" href="/asu_degrees/grad/list"><i class="fa fa-th-list fa-lg"></i> List</a>
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
  /* Field: Content: Degree Awarded */
  $handler->display->display_options['fields']['field_asu_degree_awarded']['id'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['table'] = 'field_data_field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['field'] = 'field_asu_degree_awarded';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['label'] = 'Program';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asu_degree_awarded']['alter']['text'] = '<a href="/node/[nid]">[field_asu_degree_awarded]</a>';
  $handler->display->display_options['fields']['field_asu_degree_awarded']['element_label_colon'] = FALSE;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_degree']['id'] = 'field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['fields']['field_asu_degree']['field'] = 'field_asu_degree';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus']['id'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['label'] = 'Location';
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_limit'] = '7';
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_offset'] = '0';
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['id'] = 'field_asu_degree_campus_1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['label'] = 'Available Online';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_degree_campus_1']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'asu_degree' => 'asu_degree',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'graduate';
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value']['id'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value']['operator'] = 'not empty';
  /* Filter criterion: Content: Campus (field_asu_degree_campus) */
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['id'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['field'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator_id'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['label'] = 'Campus (field_asu_degree_campus)';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['operator'] = 'field_asu_degree_campus_value_op';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['expose']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['label'] = 'Location';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['identifier'] = 'field_asu_degree_campus_value';
  $handler->display->display_options['filters']['field_asu_degree_campus_value']['group_info']['group_items'] = array(
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
  /* Filter criterion: Content: Degree (field_asu_degree) */
  $handler->display->display_options['filters']['field_asu_degree_value_1']['id'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['table'] = 'field_data_field_asu_degree';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['field'] = 'field_asu_degree_value';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator_id'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['label'] = 'Degree (field_asu_degree)';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['operator'] = 'field_asu_degree_value_1_op';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['expose']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['label'] = 'Degree Level';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['identifier'] = 'field_asu_degree_value_1';
  $handler->display->display_options['filters']['field_asu_degree_value_1']['group_info']['group_items'] = array(
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
  $handler->display->display_options['path'] = 'asu_degrees/grad/list';
  $export['asu_degrees_feature'] = $view;

  return $export;
}
