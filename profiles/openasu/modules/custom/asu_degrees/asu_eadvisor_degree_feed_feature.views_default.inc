<?php
/**
 * @file
 * asu_eadvisor_degree_feed_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function asu_eadvisor_degree_feed_feature_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'asu_eadvisor_degree';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ASU eAdvisor Degree';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Undergraduate Majors';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_degree_major']['id'] = 'field_asu_degree_major';
  $handler->display->display_options['fields']['field_asu_degree_major']['table'] = 'field_data_field_asu_degree_major';
  $handler->display->display_options['fields']['field_asu_degree_major']['field'] = 'field_asu_degree_major';
  $handler->display->display_options['fields']['field_asu_degree_major']['label'] = 'Major';
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['text'] = '<a href="/node/[nid]">[field_asu_degree_major]</a>';
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['field_api_classes'] = 0;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_degree_degree']['id'] = 'field_asu_degree_degree';
  $handler->display->display_options['fields']['field_asu_degree_degree']['table'] = 'field_data_field_asu_degree_degree';
  $handler->display->display_options['fields']['field_asu_degree_degree']['field'] = 'field_asu_degree_degree';
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_degree']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['field_api_classes'] = 0;
  /* Field: Content: Major map URL */
  $handler->display->display_options['fields']['field_asu_degree_major_map']['id'] = 'field_asu_degree_major_map';
  $handler->display->display_options['fields']['field_asu_degree_major_map']['table'] = 'field_data_field_asu_degree_major_map';
  $handler->display->display_options['fields']['field_asu_degree_major_map']['field'] = 'field_asu_degree_major_map';
  $handler->display->display_options['fields']['field_asu_degree_major_map']['label'] = 'Major map';
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['text'] = '<a href="[field_asu_degree_major_map-url]">Major map</a>';
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major_map']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_asu_degree_major_map']['field_api_classes'] = 0;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus']['id'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['field_api_classes'] = 0;
  /* Field: Content: Department */
  $handler->display->display_options['fields']['field_asu_degree_dept']['id'] = 'field_asu_degree_dept';
  $handler->display->display_options['fields']['field_asu_degree_dept']['table'] = 'field_data_field_asu_degree_dept';
  $handler->display->display_options['fields']['field_asu_degree_dept']['field'] = 'field_asu_degree_dept';
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['field_api_classes'] = 0;
  /* Field: Content: Department code */
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['id'] = 'field_asu_degree_dept_code';
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['table'] = 'field_data_field_asu_degree_dept_code';
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['field'] = 'field_asu_degree_dept_code';
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['field_api_classes'] = 0;
  /* Sort criterion: Content: Department code (field_asu_degree_dept_code) */
  $handler->display->display_options['sorts']['field_asu_degree_dept_code_value']['id'] = 'field_asu_degree_dept_code_value';
  $handler->display->display_options['sorts']['field_asu_degree_dept_code_value']['table'] = 'field_data_field_asu_degree_dept_code';
  $handler->display->display_options['sorts']['field_asu_degree_dept_code_value']['field'] = 'field_asu_degree_dept_code_value';
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
    'asu_eadvisor_degree' => 'asu_eadvisor_degree',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';

  /* Display: Page - Undergrad all */
  $handler = $view->new_display('page', 'Page - Undergrad all', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate All';
  $handler->display->display_options['display_description'] = 'Displays all undergraduate degrees';
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
    'asu_eadvisor_degree' => 'asu_eadvisor_degree',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  $handler->display->display_options['path'] = 'eadvisor_degree/ugrad/all';

  /* Display: Page - Undergrad majors */
  $handler = $view->new_display('page', 'Page - Undergrad majors', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Majors';
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
    'asu_eadvisor_degree' => 'asu_eadvisor_degree',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['value'] = 'false';
  $handler->display->display_options['path'] = 'eadvisor_degree/ugrad/major';

  /* Display: Page - Undergrad minors/certificates */
  $handler = $view->new_display('page', 'Page - Undergrad minors/certificates', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Minors/Certificates';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_degree_major']['id'] = 'field_asu_degree_major';
  $handler->display->display_options['fields']['field_asu_degree_major']['table'] = 'field_data_field_asu_degree_major';
  $handler->display->display_options['fields']['field_asu_degree_major']['field'] = 'field_asu_degree_major';
  $handler->display->display_options['fields']['field_asu_degree_major']['label'] = 'Major';
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['text'] = '<a href="/node/[nid]">[field_asu_degree_major]</a>';
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['field_api_classes'] = 0;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_degree_degree']['id'] = 'field_asu_degree_degree';
  $handler->display->display_options['fields']['field_asu_degree_degree']['table'] = 'field_data_field_asu_degree_degree';
  $handler->display->display_options['fields']['field_asu_degree_degree']['field'] = 'field_asu_degree_degree';
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_degree']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['field_api_classes'] = 0;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus']['id'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['field_api_classes'] = 0;
  /* Field: Content: Department */
  $handler->display->display_options['fields']['field_asu_degree_dept']['id'] = 'field_asu_degree_dept';
  $handler->display->display_options['fields']['field_asu_degree_dept']['table'] = 'field_data_field_asu_degree_dept';
  $handler->display->display_options['fields']['field_asu_degree_dept']['field'] = 'field_asu_degree_dept';
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['field_api_classes'] = 0;
  /* Field: Content: Department code */
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['id'] = 'field_asu_degree_dept_code';
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['table'] = 'field_data_field_asu_degree_dept_code';
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['field'] = 'field_asu_degree_dept_code';
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['field_api_classes'] = 0;
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
    'asu_eadvisor_degree' => 'asu_eadvisor_degree',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['value'] = 'true';
  $handler->display->display_options['path'] = 'eadvisor_degree/ugrad/minor_cert';

  /* Display: Page - Graduate */
  $handler = $view->new_display('page', 'Page - Graduate', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Graduate';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Degree awarded */
  $handler->display->display_options['fields']['field_asu_degree_major']['id'] = 'field_asu_degree_major';
  $handler->display->display_options['fields']['field_asu_degree_major']['table'] = 'field_data_field_asu_degree_major';
  $handler->display->display_options['fields']['field_asu_degree_major']['field'] = 'field_asu_degree_major';
  $handler->display->display_options['fields']['field_asu_degree_major']['label'] = 'Major';
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['text'] = '<a href="/node/[nid]">[field_asu_degree_major]</a>';
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_major']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_major']['field_api_classes'] = 0;
  /* Field: Content: Degree */
  $handler->display->display_options['fields']['field_asu_degree_degree']['id'] = 'field_asu_degree_degree';
  $handler->display->display_options['fields']['field_asu_degree_degree']['table'] = 'field_data_field_asu_degree_degree';
  $handler->display->display_options['fields']['field_asu_degree_degree']['field'] = 'field_asu_degree_degree';
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_degree']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_degree']['field_api_classes'] = 0;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_asu_degree_campus']['id'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['table'] = 'field_data_field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['field'] = 'field_asu_degree_campus';
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_campus']['field_api_classes'] = 0;
  /* Field: Content: Department */
  $handler->display->display_options['fields']['field_asu_degree_dept']['id'] = 'field_asu_degree_dept';
  $handler->display->display_options['fields']['field_asu_degree_dept']['table'] = 'field_data_field_asu_degree_dept';
  $handler->display->display_options['fields']['field_asu_degree_dept']['field'] = 'field_asu_degree_dept';
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept']['field_api_classes'] = 0;
  /* Field: Content: Department code */
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['id'] = 'field_asu_degree_dept_code';
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['table'] = 'field_data_field_asu_degree_dept_code';
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['field'] = 'field_asu_degree_dept_code';
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asu_degree_dept_code']['field_api_classes'] = 0;
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
    'asu_eadvisor_degree' => 'asu_eadvisor_degree',
  );
  /* Filter criterion: Content: Program: Undergrad or Graduate (field_asu_degree_program) */
  $handler->display->display_options['filters']['field_asu_degree_program_value']['id'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['table'] = 'field_data_field_asu_degree_program';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['field'] = 'field_asu_degree_program_value';
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'graduate';
  $handler->display->display_options['path'] = 'eadvisor_degree/grad';
  $export['asu_eadvisor_degree'] = $view;

  return $export;
}
