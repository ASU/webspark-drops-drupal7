<?php
/**
 * @file
 * asu_directory.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function asu_directory_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'asu_directory_people';
  $view->description = 'View to display ASU Directory Person nodes';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'asu_directory_people';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ASU Directory Feeds';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_asu_directory_image' => 'field_asu_directory_image',
    'title' => 'title',
    'field_asu_directory_title' => 'title',
    'field_asu_directory_department' => 'title',
    'field_asu_directory_affili_desc' => 'title',
    'field_asu_directory_email' => 'title',
    'field_asu_directory_phone' => 'title',
    'body' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_asu_directory_image' => array(
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
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'field_asu_directory_title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_directory_department' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_directory_affili_desc' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_directory_email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_directory_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'body' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: URL to profile image */
  $handler->display->display_options['fields']['field_asu_directory_image']['id'] = 'field_asu_directory_image';
  $handler->display->display_options['fields']['field_asu_directory_image']['table'] = 'field_data_field_asu_directory_image';
  $handler->display->display_options['fields']['field_asu_directory_image']['field'] = 'field_asu_directory_image';
  $handler->display->display_options['fields']['field_asu_directory_image']['label'] = '';
  $handler->display->display_options['fields']['field_asu_directory_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asu_directory_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asu_directory_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asu_directory_image']['settings'] = array(
    'image_style' => 'directory_table_profile__web_standard_',
    'image_link' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_empty'] = TRUE;
  /* Field: Content: Department */
  $handler->display->display_options['fields']['field_asu_directory_department']['id'] = 'field_asu_directory_department';
  $handler->display->display_options['fields']['field_asu_directory_department']['table'] = 'field_data_field_asu_directory_department';
  $handler->display->display_options['fields']['field_asu_directory_department']['field'] = 'field_asu_directory_department';
  $handler->display->display_options['fields']['field_asu_directory_department']['hide_empty'] = TRUE;
  /* Field: Content: Job title */
  $handler->display->display_options['fields']['field_asu_directory_title']['id'] = 'field_asu_directory_title';
  $handler->display->display_options['fields']['field_asu_directory_title']['table'] = 'field_data_field_asu_directory_title';
  $handler->display->display_options['fields']['field_asu_directory_title']['field'] = 'field_asu_directory_title';
  $handler->display->display_options['fields']['field_asu_directory_title']['hide_empty'] = TRUE;
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_asu_directory_email']['id'] = 'field_asu_directory_email';
  $handler->display->display_options['fields']['field_asu_directory_email']['table'] = 'field_data_field_asu_directory_email';
  $handler->display->display_options['fields']['field_asu_directory_email']['field'] = 'field_asu_directory_email';
  $handler->display->display_options['fields']['field_asu_directory_email']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_asu_directory_email']['alter']['path'] = 'mailto:[field_asu_directory_email-value]';
  $handler->display->display_options['fields']['field_asu_directory_email']['hide_empty'] = TRUE;
  /* Field: Content: Phone */
  $handler->display->display_options['fields']['field_asu_directory_phone']['id'] = 'field_asu_directory_phone';
  $handler->display->display_options['fields']['field_asu_directory_phone']['table'] = 'field_data_field_asu_directory_phone';
  $handler->display->display_options['fields']['field_asu_directory_phone']['field'] = 'field_asu_directory_phone';
  $handler->display->display_options['fields']['field_asu_directory_phone']['hide_empty'] = TRUE;
  /* Sort criterion: Content: Last name (field_asu_directory_lastname) */
  $handler->display->display_options['sorts']['field_asu_directory_lastname_value']['id'] = 'field_asu_directory_lastname_value';
  $handler->display->display_options['sorts']['field_asu_directory_lastname_value']['table'] = 'field_data_field_asu_directory_lastname';
  $handler->display->display_options['sorts']['field_asu_directory_lastname_value']['field'] = 'field_asu_directory_lastname_value';
  /* Sort criterion: Content: First name (field_asu_directory_firstname) */
  $handler->display->display_options['sorts']['field_asu_directory_firstname_value']['id'] = 'field_asu_directory_firstname_value';
  $handler->display->display_options['sorts']['field_asu_directory_firstname_value']['table'] = 'field_data_field_asu_directory_firstname';
  $handler->display->display_options['sorts']['field_asu_directory_firstname_value']['field'] = 'field_asu_directory_firstname_value';
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
    'asu_directory_person' => 'asu_directory_person',
  );

  /* Display: Page - ASU Directory Feeds */
  $handler = $view->new_display('page', 'Page - ASU Directory Feeds', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'directory-listing-table';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_asu_directory_image' => 'field_asu_directory_image',
    'title' => 'title',
    'field_asu_directory_title' => 'title',
    'field_asu_directory_department' => 'title',
    'field_asu_directory_email' => 'field_asu_directory_email',
    'field_asu_directory_phone' => 'field_asu_directory_email',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'field_asu_directory_image' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'field_asu_directory_title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_directory_department' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asu_directory_email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'field_asu_directory_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h3>People Directory</h3>';
  $handler->display->display_options['header']['area']['format'] = 'panopoly_wysiwyg_text';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: URL to profile image */
  $handler->display->display_options['fields']['field_asu_directory_image']['id'] = 'field_asu_directory_image';
  $handler->display->display_options['fields']['field_asu_directory_image']['table'] = 'field_data_field_asu_directory_image';
  $handler->display->display_options['fields']['field_asu_directory_image']['field'] = 'field_asu_directory_image';
  $handler->display->display_options['fields']['field_asu_directory_image']['label'] = '';
  $handler->display->display_options['fields']['field_asu_directory_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asu_directory_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asu_directory_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asu_directory_image']['settings'] = array(
    'image_style' => 'asu_directory_table_profile',
    'image_link' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_class'] = 'directory-sort';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_empty'] = TRUE;
  /* Field: Content: Job title */
  $handler->display->display_options['fields']['field_asu_directory_title']['id'] = 'field_asu_directory_title';
  $handler->display->display_options['fields']['field_asu_directory_title']['table'] = 'field_data_field_asu_directory_title';
  $handler->display->display_options['fields']['field_asu_directory_title']['field'] = 'field_asu_directory_title';
  $handler->display->display_options['fields']['field_asu_directory_title']['hide_empty'] = TRUE;
  /* Field: Content: Department */
  $handler->display->display_options['fields']['field_asu_directory_department']['id'] = 'field_asu_directory_department';
  $handler->display->display_options['fields']['field_asu_directory_department']['table'] = 'field_data_field_asu_directory_department';
  $handler->display->display_options['fields']['field_asu_directory_department']['field'] = 'field_asu_directory_department';
  $handler->display->display_options['fields']['field_asu_directory_department']['hide_empty'] = TRUE;
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_asu_directory_email']['id'] = 'field_asu_directory_email';
  $handler->display->display_options['fields']['field_asu_directory_email']['table'] = 'field_data_field_asu_directory_email';
  $handler->display->display_options['fields']['field_asu_directory_email']['field'] = 'field_asu_directory_email';
  $handler->display->display_options['fields']['field_asu_directory_email']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_asu_directory_email']['alter']['path'] = 'mailto:[field_asu_directory_email-value]';
  $handler->display->display_options['fields']['field_asu_directory_email']['hide_empty'] = TRUE;
  /* Field: Content: Phone */
  $handler->display->display_options['fields']['field_asu_directory_phone']['id'] = 'field_asu_directory_phone';
  $handler->display->display_options['fields']['field_asu_directory_phone']['table'] = 'field_data_field_asu_directory_phone';
  $handler->display->display_options['fields']['field_asu_directory_phone']['field'] = 'field_asu_directory_phone';
  $handler->display->display_options['fields']['field_asu_directory_phone']['hide_empty'] = TRUE;
  $handler->display->display_options['path'] = 'people';

  /* Display: Attachment - Glossary for ASU Directory */
  $handler = $view->new_display('attachment', 'Attachment - Glossary for ASU Directory', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Last name (field_asu_directory_lastname) */
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['id'] = 'field_asu_directory_lastname_value';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['table'] = 'field_data_field_asu_directory_lastname';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['field'] = 'field_asu_directory_lastname_value';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['default_action'] = 'summary';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['summary']['format'] = 'unformatted_summary';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['summary_options']['inline'] = TRUE;
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['summary_options']['separator'] = '|';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['glossary'] = TRUE;
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['limit'] = '1';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['case'] = 'upper';
  $handler->display->display_options['arguments']['field_asu_directory_lastname_value']['path_case'] = 'lower';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'page' => 0,
    'page_1' => 0,
    'block_1' => 0,
    'block_2' => 0,
  );
  $handler->display->display_options['inherit_arguments'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: URL to profile image */
  $handler->display->display_options['fields']['field_asu_directory_image']['id'] = 'field_asu_directory_image';
  $handler->display->display_options['fields']['field_asu_directory_image']['table'] = 'field_data_field_asu_directory_image';
  $handler->display->display_options['fields']['field_asu_directory_image']['field'] = 'field_asu_directory_image';
  $handler->display->display_options['fields']['field_asu_directory_image']['label'] = '';
  $handler->display->display_options['fields']['field_asu_directory_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asu_directory_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asu_directory_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asu_directory_image']['settings'] = array(
    'image_style' => 'asu_directory_profile_image',
    'image_link' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Job title */
  $handler->display->display_options['fields']['field_asu_directory_title']['id'] = 'field_asu_directory_title';
  $handler->display->display_options['fields']['field_asu_directory_title']['table'] = 'field_data_field_asu_directory_title';
  $handler->display->display_options['fields']['field_asu_directory_title']['field'] = 'field_asu_directory_title';
  $handler->display->display_options['fields']['field_asu_directory_title']['hide_empty'] = TRUE;
  /* Field: Content: Department */
  $handler->display->display_options['fields']['field_asu_directory_department']['id'] = 'field_asu_directory_department';
  $handler->display->display_options['fields']['field_asu_directory_department']['table'] = 'field_data_field_asu_directory_department';
  $handler->display->display_options['fields']['field_asu_directory_department']['field'] = 'field_asu_directory_department';
  $handler->display->display_options['fields']['field_asu_directory_department']['hide_empty'] = TRUE;
  /* Field: Content: Affiliation description */
  $handler->display->display_options['fields']['field_asu_directory_affili_desc']['id'] = 'field_asu_directory_affili_desc';
  $handler->display->display_options['fields']['field_asu_directory_affili_desc']['table'] = 'field_data_field_asu_directory_affili_desc';
  $handler->display->display_options['fields']['field_asu_directory_affili_desc']['field'] = 'field_asu_directory_affili_desc';
  $handler->display->display_options['fields']['field_asu_directory_affili_desc']['label'] = '';
  $handler->display->display_options['fields']['field_asu_directory_affili_desc']['element_label_colon'] = FALSE;
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_asu_directory_email']['id'] = 'field_asu_directory_email';
  $handler->display->display_options['fields']['field_asu_directory_email']['table'] = 'field_data_field_asu_directory_email';
  $handler->display->display_options['fields']['field_asu_directory_email']['field'] = 'field_asu_directory_email';
  $handler->display->display_options['fields']['field_asu_directory_email']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_asu_directory_email']['alter']['path'] = 'mailto:[field_asu_directory_email-value]';
  $handler->display->display_options['fields']['field_asu_directory_email']['hide_empty'] = TRUE;
  /* Field: Content: Phone */
  $handler->display->display_options['fields']['field_asu_directory_phone']['id'] = 'field_asu_directory_phone';
  $handler->display->display_options['fields']['field_asu_directory_phone']['table'] = 'field_data_field_asu_directory_phone';
  $handler->display->display_options['fields']['field_asu_directory_phone']['field'] = 'field_asu_directory_phone';
  $handler->display->display_options['fields']['field_asu_directory_phone']['hide_empty'] = TRUE;
  /* Field: Content: Bio */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: EID (field_asu_directory_eid) */
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['id'] = 'field_asu_directory_eid_value';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['table'] = 'field_data_field_asu_directory_eid';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['field'] = 'field_asu_directory_eid_value';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'person/%';

  /* Display: Attachment 2 */
  $handler = $view->new_display('attachment', 'Attachment 2', 'attachment_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Bio */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: EID (field_asu_directory_eid) */
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['id'] = 'field_asu_directory_eid_value';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['table'] = 'field_data_field_asu_directory_eid';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['field'] = 'field_asu_directory_eid_value';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_asu_directory_eid_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'default' => 0,
    'page' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Attachment 3 */
  $handler = $view->new_display('attachment', 'Attachment 3', 'attachment_3');
  $handler->display->display_options['pager']['type'] = 'some';

  /* Display: Bio */
  $handler = $view->new_display('block', 'Bio', 'block_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Bio */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Research Interests */
  $handler = $view->new_display('block', 'Research Interests', 'block_2');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Research interest */
  $handler->display->display_options['fields']['field_asu_directory_research']['id'] = 'field_asu_directory_research';
  $handler->display->display_options['fields']['field_asu_directory_research']['table'] = 'field_data_field_asu_directory_research';
  $handler->display->display_options['fields']['field_asu_directory_research']['field'] = 'field_asu_directory_research';
  $handler->display->display_options['fields']['field_asu_directory_research']['label'] = '';
  $handler->display->display_options['fields']['field_asu_directory_research']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $export['asu_directory_people'] = $view;

  return $export;
}
