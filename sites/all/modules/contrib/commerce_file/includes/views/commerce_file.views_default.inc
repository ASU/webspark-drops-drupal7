<?php

/**
 * @file
 * Provides default file views.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_file_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'commerce_license_my_files';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_license';
  $view->human_name = 'Licensed files';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Files';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view own licenses';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'commerce_file' => 'commerce_file',
    'filesize' => 'filesize',
    'expires' => 'expires',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'commerce_file' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'filesize' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'expires' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You do not have any licensed files.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Commerce License: Product product_id */
  $handler->display->display_options['relationships']['product']['id'] = 'product';
  $handler->display->display_options['relationships']['product']['table'] = 'commerce_license';
  $handler->display->display_options['relationships']['product']['field'] = 'product';
  $handler->display->display_options['relationships']['product']['required'] = TRUE;
  /* Relationship: Commerce Product: Files (commerce_file:fid) */
  $handler->display->display_options['relationships']['commerce_file_fid']['id'] = 'commerce_file_fid';
  $handler->display->display_options['relationships']['commerce_file_fid']['table'] = 'field_data_commerce_file';
  $handler->display->display_options['relationships']['commerce_file_fid']['field'] = 'commerce_file_fid';
  $handler->display->display_options['relationships']['commerce_file_fid']['relationship'] = 'product';
  $handler->display->display_options['relationships']['commerce_file_fid']['required'] = TRUE;
  /* Field: Commerce License: License ID */
  $handler->display->display_options['fields']['license_id']['id'] = 'license_id';
  $handler->display->display_options['fields']['license_id']['table'] = 'commerce_license';
  $handler->display->display_options['fields']['license_id']['field'] = 'license_id';
  $handler->display->display_options['fields']['license_id']['label'] = '';
  $handler->display->display_options['fields']['license_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['license_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['license_id']['separator'] = '';
  /* Field: Commerce Product: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'product';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_product'] = 0;
  /* Field: Commerce Product: Files */
  $handler->display->display_options['fields']['commerce_file']['id'] = 'commerce_file';
  $handler->display->display_options['fields']['commerce_file']['table'] = 'field_data_commerce_file';
  $handler->display->display_options['fields']['commerce_file']['field'] = 'commerce_file';
  $handler->display->display_options['fields']['commerce_file']['relationship'] = 'product';
  $handler->display->display_options['fields']['commerce_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['commerce_file']['type'] = 'commerce_file';
  $handler->display->display_options['fields']['commerce_file']['settings'] = array(
    'show_icon' => 0,
  );
  $handler->display->display_options['fields']['commerce_file']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['commerce_file']['delta_offset'] = '0';
  /* Field: File: Size */
  $handler->display->display_options['fields']['filesize']['id'] = 'filesize';
  $handler->display->display_options['fields']['filesize']['table'] = 'file_managed';
  $handler->display->display_options['fields']['filesize']['field'] = 'filesize';
  $handler->display->display_options['fields']['filesize']['relationship'] = 'commerce_file_fid';
  /* Field: Commerce License: Download limit */
  $handler->display->display_options['fields']['download_limit']['id'] = 'download_limit';
  $handler->display->display_options['fields']['download_limit']['table'] = 'commerce_license';
  $handler->display->display_options['fields']['download_limit']['field'] = 'download_limit';
  $handler->display->display_options['fields']['download_limit']['label'] = 'Downloads';
  $handler->display->display_options['fields']['download_limit']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['download_limit']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['download_limit']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['download_limit']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['download_limit']['hide_alter_empty'] = FALSE;
  /* Field: Commerce License: Expires */
  $handler->display->display_options['fields']['expires']['id'] = 'expires';
  $handler->display->display_options['fields']['expires']['table'] = 'commerce_license';
  $handler->display->display_options['fields']['expires']['field'] = 'expires';
  $handler->display->display_options['fields']['expires']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['expires']['date_format'] = 'medium';
  /* Contextual filter: Commerce License: Owner uid */
  $handler->display->display_options['arguments']['owner']['id'] = 'owner';
  $handler->display->display_options['arguments']['owner']['table'] = 'commerce_license';
  $handler->display->display_options['arguments']['owner']['field'] = 'owner';
  $handler->display->display_options['arguments']['owner']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['owner']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['owner']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['owner']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['owner']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['owner']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['owner']['validate']['type'] = 'current_user_or_role';
  $handler->display->display_options['arguments']['owner']['validate_options']['restrict_roles'] = TRUE;
  $handler->display->display_options['arguments']['owner']['validate_options']['roles'] = array(
    3 => '3',
  );
  /* Filter criterion: Commerce License: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'commerce_license';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'file' => 'file',
  );
  /* Filter criterion: Commerce License: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_license';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    2 => '2',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'user/%/my-files';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Files';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['commerce_license_my_files'] = array(
    t('Master'),
    t('Files'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('You do not have any licensed files.'),
    t('Commerce Product'),
    t('file from commerce_file'),
    t('.'),
    t('Size'),
    t('Downloads'),
    t('Expires'),
    t('All'),
    t('Page'),
  );
  $views[$view->name] = $view;

  return $views;
}
