<?php

/**
 * @file
 * Views for the default Commerce File views.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_file_views_default_views() {
  $views = array();

// -----------------------------------------------------------------------
// User licenses

  $view = new view;
  $view->name = 'commerce_user_file_licenses';
  $view->description = 'Display a list of licensed files for a user.';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_file_license';
  $view->human_name = 'User Licensed Files';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Files';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = 'filename';
  $handler->display->display_options['style_options']['group_rendered'] = 1;
  $handler->display->display_options['style_options']['columns'] = array(
    'fid' => 'fid',
    'filesize' => 'filesize',
    'fid_1' => 'fid_1',
    'filename' => 'filename',
    'granted' => 'granted',
    'status' => 'status',
    'time_remaining' => 'time_remaining',
    'address_count' => 'address_count',
    'address_limit' => 'address_limit',
    'download_count' => 'download_count',
    'download_limit' => 'download_limit',
    'download_limit_1' => 'download_limit_1',
    'address_limit_1' => 'address_limit_1',
    'edit_license' => 'edit_license',
    'delete_license' => 'edit_license',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fid' => array(
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
    'fid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'filename' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'granted' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'time_remaining' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_limit' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'download_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'download_limit' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'download_limit_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_limit_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_license' => array(
      'align' => '',
      'separator' => ' &nbsp;',
      'empty_column' => 1,
    ),
    'delete_license' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 0;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'You do not have any licensed files.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Commerce File License: Licensed file (commerce_file_license_file:fid) */
  $handler->display->display_options['relationships']['commerce_file_license_file_fid']['id'] = 'commerce_file_license_file_fid';
  $handler->display->display_options['relationships']['commerce_file_license_file_fid']['table'] = 'field_data_commerce_file_license_file';
  $handler->display->display_options['relationships']['commerce_file_license_file_fid']['field'] = 'commerce_file_license_file_fid';
  $handler->display->display_options['relationships']['commerce_file_license_file_fid']['label'] = 'file';
  $handler->display->display_options['relationships']['commerce_file_license_file_fid']['required'] = 1;
  /* Field: File: File ID */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'file_managed';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['relationship'] = 'commerce_file_license_file_fid';
  $handler->display->display_options['fields']['fid']['label'] = '';
  $handler->display->display_options['fields']['fid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['fid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['fid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['fid']['link_to_file'] = 0;
  /* Field: File: Size */
  $handler->display->display_options['fields']['filesize']['id'] = 'filesize';
  $handler->display->display_options['fields']['filesize']['table'] = 'file_managed';
  $handler->display->display_options['fields']['filesize']['field'] = 'filesize';
  $handler->display->display_options['fields']['filesize']['relationship'] = 'commerce_file_license_file_fid';
  $handler->display->display_options['fields']['filesize']['label'] = '';
  $handler->display->display_options['fields']['filesize']['exclude'] = TRUE;
  $handler->display->display_options['fields']['filesize']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['filesize']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['filesize']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['filesize']['alter']['external'] = 0;
  $handler->display->display_options['fields']['filesize']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['filesize']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['filesize']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['filesize']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['filesize']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['filesize']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['filesize']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['filesize']['alter']['html'] = 0;
  $handler->display->display_options['fields']['filesize']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['filesize']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['filesize']['hide_empty'] = 0;
  $handler->display->display_options['fields']['filesize']['empty_zero'] = 0;
  $handler->display->display_options['fields']['filesize']['hide_alter_empty'] = 1;
  /* Field: File: File ID */
  $handler->display->display_options['fields']['fid_1']['id'] = 'fid_1';
  $handler->display->display_options['fields']['fid_1']['table'] = 'file_managed';
  $handler->display->display_options['fields']['fid_1']['field'] = 'fid';
  $handler->display->display_options['fields']['fid_1']['relationship'] = 'commerce_file_license_file_fid';
  $handler->display->display_options['fields']['fid_1']['label'] = '';
  $handler->display->display_options['fields']['fid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fid_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['fid_1']['alter']['text'] = 'Download';
  $handler->display->display_options['fields']['fid_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['fid_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['fid_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['fid_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['fid_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['fid_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['fid_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['fid_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['fid_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['fid_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['fid_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['fid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fid_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['fid_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['fid_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['fid_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['fid_1']['link_to_file'] = 1;
  /* Field: File: Name */
  $handler->display->display_options['fields']['filename']['id'] = 'filename';
  $handler->display->display_options['fields']['filename']['table'] = 'file_managed';
  $handler->display->display_options['fields']['filename']['field'] = 'filename';
  $handler->display->display_options['fields']['filename']['relationship'] = 'commerce_file_license_file_fid';
  $handler->display->display_options['fields']['filename']['label'] = '';
  $handler->display->display_options['fields']['filename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['filename']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['filename']['alter']['text'] = '<h3 class="file-header">[filename] ([filesize])</h3>
  <div class="file-link">[fid_1]</div>';
  $handler->display->display_options['fields']['filename']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['external'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['filename']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['filename']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['html'] = 0;
  $handler->display->display_options['fields']['filename']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['filename']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['filename']['hide_empty'] = 0;
  $handler->display->display_options['fields']['filename']['empty_zero'] = 0;
  $handler->display->display_options['fields']['filename']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['filename']['link_to_file'] = 0;
  /* Field: Commerce File License: Granted date */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = 'Granted on';
  $handler->display->display_options['fields']['granted']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['external'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['granted']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['granted']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['html'] = 0;
  $handler->display->display_options['fields']['granted']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['granted']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['granted']['hide_empty'] = 0;
  $handler->display->display_options['fields']['granted']['empty_zero'] = 0;
  $handler->display->display_options['fields']['granted']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['granted']['date_format'] = 'medium';
  /* Field: Commerce File License: License status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  /* Field: Commerce File License: Current time remaining */
  $handler->display->display_options['fields']['time_remaining']['id'] = 'time_remaining';
  $handler->display->display_options['fields']['time_remaining']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['time_remaining']['field'] = 'time_remaining';
  $handler->display->display_options['fields']['time_remaining']['label'] = 'Time left';
  $handler->display->display_options['fields']['time_remaining']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['time_remaining']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['time_remaining']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['time_remaining']['alter']['external'] = 0;
  $handler->display->display_options['fields']['time_remaining']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['time_remaining']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['time_remaining']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['time_remaining']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['time_remaining']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['time_remaining']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['time_remaining']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['time_remaining']['alter']['html'] = 0;
  $handler->display->display_options['fields']['time_remaining']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['time_remaining']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['time_remaining']['hide_empty'] = 0;
  $handler->display->display_options['fields']['time_remaining']['empty_zero'] = 0;
  $handler->display->display_options['fields']['time_remaining']['unlimited_text'] = '';
  $handler->display->display_options['fields']['time_remaining']['granularity'] = '3';
  /* Field: Commerce File License: Current number of addresses */
  $handler->display->display_options['fields']['address_count']['id'] = 'address_count';
  $handler->display->display_options['fields']['address_count']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['address_count']['field'] = 'address_count';
  $handler->display->display_options['fields']['address_count']['label'] = '';
  $handler->display->display_options['fields']['address_count']['exclude'] = TRUE;
  $handler->display->display_options['fields']['address_count']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['address_count']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['address_count']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['address_count']['alter']['external'] = 0;
  $handler->display->display_options['fields']['address_count']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['address_count']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['address_count']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['address_count']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['address_count']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['address_count']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['address_count']['alter']['html'] = 0;
  $handler->display->display_options['fields']['address_count']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['address_count']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['address_count']['hide_empty'] = 0;
  $handler->display->display_options['fields']['address_count']['empty_zero'] = 0;
  /* Field: Commerce File License: Address limit */
  $handler->display->display_options['fields']['address_limit']['id'] = 'address_limit';
  $handler->display->display_options['fields']['address_limit']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['address_limit']['field'] = 'address_limit';
  $handler->display->display_options['fields']['address_limit']['label'] = '';
  $handler->display->display_options['fields']['address_limit']['exclude'] = TRUE;
  $handler->display->display_options['fields']['address_limit']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['address_limit']['alter']['text'] = '[address_count] / [address_limit]';
  $handler->display->display_options['fields']['address_limit']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['address_limit']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['address_limit']['alter']['external'] = 0;
  $handler->display->display_options['fields']['address_limit']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['address_limit']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['address_limit']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['address_limit']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['address_limit']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['address_limit']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['address_limit']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['address_limit']['alter']['html'] = 0;
  $handler->display->display_options['fields']['address_limit']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['address_limit']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['address_limit']['empty'] = 'No Access!';
  $handler->display->display_options['fields']['address_limit']['hide_empty'] = 0;
  $handler->display->display_options['fields']['address_limit']['empty_zero'] = 1;
  /* Field: Commerce File License: Current number of downloads */
  $handler->display->display_options['fields']['download_count']['id'] = 'download_count';
  $handler->display->display_options['fields']['download_count']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['download_count']['field'] = 'download_count';
  $handler->display->display_options['fields']['download_count']['label'] = '';
  $handler->display->display_options['fields']['download_count']['exclude'] = TRUE;
  $handler->display->display_options['fields']['download_count']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['download_count']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['download_count']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['download_count']['alter']['external'] = 0;
  $handler->display->display_options['fields']['download_count']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['download_count']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['download_count']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['download_count']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['download_count']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['download_count']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['download_count']['alter']['html'] = 0;
  $handler->display->display_options['fields']['download_count']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['download_count']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['download_count']['hide_empty'] = 0;
  $handler->display->display_options['fields']['download_count']['empty_zero'] = 0;
  /* Field: Commerce File License: Download limit */
  $handler->display->display_options['fields']['download_limit']['id'] = 'download_limit';
  $handler->display->display_options['fields']['download_limit']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['download_limit']['field'] = 'download_limit';
  $handler->display->display_options['fields']['download_limit']['label'] = '';
  $handler->display->display_options['fields']['download_limit']['exclude'] = TRUE;
  $handler->display->display_options['fields']['download_limit']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['download_limit']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['download_limit']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['download_limit']['alter']['external'] = 0;
  $handler->display->display_options['fields']['download_limit']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['download_limit']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['download_limit']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['download_limit']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['download_limit']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['download_limit']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['download_limit']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['download_limit']['alter']['html'] = 0;
  $handler->display->display_options['fields']['download_limit']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['download_limit']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['download_limit']['empty'] = 'No Access!';
  $handler->display->display_options['fields']['download_limit']['hide_empty'] = 0;
  $handler->display->display_options['fields']['download_limit']['empty_zero'] = 1;
  /* Field: Commerce File License: Download limit */
  $handler->display->display_options['fields']['download_limit_1']['id'] = 'download_limit_1';
  $handler->display->display_options['fields']['download_limit_1']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['download_limit_1']['field'] = 'download_limit';
  $handler->display->display_options['fields']['download_limit_1']['label'] = 'Downloads';
  $handler->display->display_options['fields']['download_limit_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['download_limit_1']['alter']['text'] = '[download_count] / [download_limit]';
  $handler->display->display_options['fields']['download_limit_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['download_limit_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['download_limit_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['download_limit_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['download_limit_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['download_limit_1']['empty_zero'] = 0;
  /* Field: Commerce File License: Address limit */
  $handler->display->display_options['fields']['address_limit_1']['id'] = 'address_limit_1';
  $handler->display->display_options['fields']['address_limit_1']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['address_limit_1']['field'] = 'address_limit';
  $handler->display->display_options['fields']['address_limit_1']['label'] = 'IP Addresses';
  $handler->display->display_options['fields']['address_limit_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['address_limit_1']['alter']['text'] = '[address_count] / [address_limit]';
  $handler->display->display_options['fields']['address_limit_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['address_limit_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['address_limit_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['address_limit_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['address_limit_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['address_limit_1']['empty_zero'] = 0;
  /* Field: Commerce File License: Edit link */
  $handler->display->display_options['fields']['edit_license']['id'] = 'edit_license';
  $handler->display->display_options['fields']['edit_license']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['edit_license']['field'] = 'edit_license';
  $handler->display->display_options['fields']['edit_license']['label'] = '';
  $handler->display->display_options['fields']['edit_license']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['external'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_license']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_license']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_license']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['edit_license']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_license']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_license']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_license']['text'] = 'edit';
  /* Field: Commerce File License: Delete link */
  $handler->display->display_options['fields']['delete_license']['id'] = 'delete_license';
  $handler->display->display_options['fields']['delete_license']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['delete_license']['field'] = 'delete_license';
  $handler->display->display_options['fields']['delete_license']['label'] = '';
  $handler->display->display_options['fields']['delete_license']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['external'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delete_license']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delete_license']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delete_license']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_license']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delete_license']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delete_license']['empty_zero'] = 0;
  $handler->display->display_options['fields']['delete_license']['text'] = 'delete';
  /* Sort criterion: Commerce File License: License ID */
  $handler->display->display_options['sorts']['license_id']['id'] = 'license_id';
  $handler->display->display_options['sorts']['license_id']['table'] = 'commerce_file_license';
  $handler->display->display_options['sorts']['license_id']['field'] = 'license_id';
  $handler->display->display_options['sorts']['license_id']['order'] = 'DESC';
  /* Contextual filter: Commerce File License: Owner uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'commerce_file_license';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'commerce_file_user';
  $handler->display->display_options['arguments']['uid']['validate_options']['restrict_roles'] = '1';
  $handler->display->display_options['arguments']['uid']['validate_options']['roles'] = array(
    3 => '3',
  );
  $handler->display->display_options['arguments']['uid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['uid']['not'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'user/%/licensed-files';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Files';
  $handler->display->display_options['menu']['weight'] = '10';

  $views[$view->name] = $view;



// -----------------------------------------------------------------------
// Related line items list

  $view = new view;
  $view->name = 'commerce_license_line_items_list';
  $view->description = 'A list of commerce line items related to a file license.  This is used in various admin forms to show the line item references.';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_file_license';
  $view->human_name = 'License Related Line Items';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Related Orders';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = 'order_id_1';
  $handler->display->display_options['style_options']['columns'] = array(
    'order_number' => 'order_number',
    'created' => 'created',
    'status' => 'status',
    'order_id_1' => 'order_id_1',
    'line_item_id' => 'line_item_id',
    'line_item_label' => 'line_item_label',
    'line_item_title' => 'line_item_title',
    'quantity' => 'quantity',
    'commerce_total' => 'commerce_total',
  );
  $handler->display->display_options['style_options']['default'] = 'line_item_id';
  $handler->display->display_options['style_options']['info'] = array(
    'order_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'order_id_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'line_item_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'line_item_label' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'line_item_title' => array(
      'align' => '',
      'separator' => '',
    ),
    'quantity' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'commerce_total' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 1;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no line items related to this license.';
  /* Relationship: Commerce File License: Referenced line item */
  $handler->display->display_options['relationships']['commerce_file_license_line_items_line_item_id']['id'] = 'commerce_file_license_line_items_line_item_id';
  $handler->display->display_options['relationships']['commerce_file_license_line_items_line_item_id']['table'] = 'field_data_commerce_file_license_line_items';
  $handler->display->display_options['relationships']['commerce_file_license_line_items_line_item_id']['field'] = 'commerce_file_license_line_items_line_item_id';
  $handler->display->display_options['relationships']['commerce_file_license_line_items_line_item_id']['required'] = 1;
  /* Relationship: Commerce Line Item: Order ID */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['relationship'] = 'commerce_file_license_line_items_line_item_id';
  $handler->display->display_options['relationships']['order_id']['required'] = 1;
  /* Field: Commerce Order: Order number */
  $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['order_number']['label'] = '';
  $handler->display->display_options['fields']['order_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['order_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['order_number']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['order_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['order_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['order_number']['empty_zero'] = 0;
  /* Field: Commerce Order: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Commerce Order: Order status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['status']['label'] = '';
  $handler->display->display_options['fields']['status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  /* Field: Commerce Order: Order ID */
  $handler->display->display_options['fields']['order_id_1']['id'] = 'order_id_1';
  $handler->display->display_options['fields']['order_id_1']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_id_1']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id_1']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['order_id_1']['label'] = '';
  $handler->display->display_options['fields']['order_id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['order_id_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['order_id_1']['alter']['text'] = 'Order [order_number] on [created] &nbsp;([status])
  ';
  $handler->display->display_options['fields']['order_id_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_id_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_id_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['order_id_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['order_id_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['order_id_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['order_id_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['order_id_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['order_id_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['order_id_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['order_id_1']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['order_id_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['order_id_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['order_id_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['order_id_1']['link_to_order'] = 'customer';
  /* Field: Commerce Line Item: Label */
  $handler->display->display_options['fields']['line_item_label']['id'] = 'line_item_label';
  $handler->display->display_options['fields']['line_item_label']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_label']['field'] = 'line_item_label';
  $handler->display->display_options['fields']['line_item_label']['relationship'] = 'commerce_file_license_line_items_line_item_id';
  $handler->display->display_options['fields']['line_item_label']['label'] = 'SKU';
  $handler->display->display_options['fields']['line_item_label']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_label']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_label']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_label']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['line_item_label']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_label']['hide_empty'] = 0;
  $handler->display->display_options['fields']['line_item_label']['empty_zero'] = 0;
  /* Field: Commerce Line Item: Title */
  $handler->display->display_options['fields']['line_item_title']['id'] = 'line_item_title';
  $handler->display->display_options['fields']['line_item_title']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_title']['field'] = 'line_item_title';
  $handler->display->display_options['fields']['line_item_title']['relationship'] = 'commerce_file_license_line_items_line_item_id';
  $handler->display->display_options['fields']['line_item_title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['line_item_title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['line_item_title']['empty_zero'] = 0;
  /* Field: Commerce Line Item: Quantity */
  $handler->display->display_options['fields']['quantity']['id'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['quantity']['field'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['relationship'] = 'commerce_file_license_line_items_line_item_id';
  $handler->display->display_options['fields']['quantity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['quantity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['quantity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['quantity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['quantity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['quantity']['set_precision'] = 0;
  $handler->display->display_options['fields']['quantity']['precision'] = '0';
  $handler->display->display_options['fields']['quantity']['format_plural'] = 0;
  /* Field: Commerce Line item: Total */
  $handler->display->display_options['fields']['commerce_total']['id'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['table'] = 'field_data_commerce_total';
  $handler->display->display_options['fields']['commerce_total']['field'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['relationship'] = 'commerce_file_license_line_items_line_item_id';
  $handler->display->display_options['fields']['commerce_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_total']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_total']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_total']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_total']['field_api_classes'] = 0;
  /* Contextual filter: Commerce File License: License ID */
  $handler->display->display_options['arguments']['license_id']['id'] = 'license_id';
  $handler->display->display_options['arguments']['license_id']['table'] = 'commerce_file_license';
  $handler->display->display_options['arguments']['license_id']['field'] = 'license_id';
  $handler->display->display_options['arguments']['license_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['license_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['license_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['license_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['license_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['license_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['license_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['license_id']['not'] = 0;

  $views[$view->name] = $view;



// -----------------------------------------------------------------------
// Admin Page

  $view = new view;
  $view->name = 'commerce_file_admin';
  $view->description = 'Display a list of licensed files for store admin.';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_file_license';
  $view->human_name = 'Commerce File Admin';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'File licenses';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer commerce_file_license';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'license_id' => 'license_id',
    'commerce_file_license_file' => 'commerce_file_license_file',
    'name' => 'name',
    'status' => 'status',
    'created' => 'created',
    'granted' => 'granted',
    'edit_license' => 'edit_license',
    'clone_license' => 'edit_license',
    'delete_license' => 'edit_license',
  );
  $handler->display->display_options['style_options']['default'] = 'license_id';
  $handler->display->display_options['style_options']['info'] = array(
    'license_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'commerce_file_license_file' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'granted' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'edit_license' => array(
      'align' => '',
      'separator' => ' | ',
    ),
    'clone_license' => array(
      'align' => '',
      'separator' => '',
    ),
    'delete_license' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['order'] = 'desc';
  $handler->display->display_options['style_options']['empty_table'] = 1;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No file licenses have been issued.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Commerce File License: Owner uid */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'commerce_file_license';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Field: Commerce File License: License ID */
  $handler->display->display_options['fields']['license_id']['id'] = 'license_id';
  $handler->display->display_options['fields']['license_id']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['license_id']['field'] = 'license_id';
  $handler->display->display_options['fields']['license_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['license_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['license_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['license_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['license_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['license_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['license_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['license_id']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['license_id']['link_to_entity'] = 'admin';
  /* Field: Commerce File License: Licensed file */
  $handler->display->display_options['fields']['commerce_file_license_file']['id'] = 'commerce_file_license_file';
  $handler->display->display_options['fields']['commerce_file_license_file']['table'] = 'field_data_commerce_file_license_file';
  $handler->display->display_options['fields']['commerce_file_license_file']['field'] = 'commerce_file_license_file';
  $handler->display->display_options['fields']['commerce_file_license_file']['label'] = '';
  $handler->display->display_options['fields']['commerce_file_license_file']['exclude'] = TRUE;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['text'] = '[commerce_file_license_file]<span class="element-invisible">[commerce_file_license_file-fid]</span>';
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['commerce_file_license_file']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_file_license_file']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['commerce_file_license_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['commerce_file_license_file']['field_api_classes'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Owner';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: Commerce File License: License status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = '';
  $handler->display->display_options['fields']['status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim_whitespace'] = 1;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['empty'] = 'none';
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['status']['hide_alter_empty'] = 0;
  /* Field: Commerce File License: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Commerce File License: Granted date */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = 'Granted';
  $handler->display->display_options['fields']['granted']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['external'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['granted']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['granted']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['html'] = 0;
  $handler->display->display_options['fields']['granted']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['granted']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['granted']['hide_empty'] = 0;
  $handler->display->display_options['fields']['granted']['empty_zero'] = 0;
  $handler->display->display_options['fields']['granted']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['granted']['date_format'] = 'short';
  /* Field: Commerce File License: Edit link */
  $handler->display->display_options['fields']['edit_license']['id'] = 'edit_license';
  $handler->display->display_options['fields']['edit_license']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['edit_license']['field'] = 'edit_license';
  $handler->display->display_options['fields']['edit_license']['label'] = 'Operations';
  $handler->display->display_options['fields']['edit_license']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['external'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_license']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_license']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_license']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_license']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['edit_license']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_license']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_license']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_license']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['edit_license']['text'] = 'edit';
  /* Field: Commerce File License: Clone link */
  $handler->display->display_options['fields']['clone_license']['id'] = 'clone_license';
  $handler->display->display_options['fields']['clone_license']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['clone_license']['field'] = 'clone_license';
  $handler->display->display_options['fields']['clone_license']['label'] = '';
  $handler->display->display_options['fields']['clone_license']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['clone_license']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['clone_license']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['clone_license']['alter']['external'] = 0;
  $handler->display->display_options['fields']['clone_license']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['clone_license']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['clone_license']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['clone_license']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['clone_license']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['clone_license']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['clone_license']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['clone_license']['alter']['html'] = 0;
  $handler->display->display_options['fields']['clone_license']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['clone_license']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['clone_license']['hide_empty'] = 0;
  $handler->display->display_options['fields']['clone_license']['empty_zero'] = 0;
  $handler->display->display_options['fields']['clone_license']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['clone_license']['text'] = 'clone';
  /* Field: Commerce File License: Delete link */
  $handler->display->display_options['fields']['delete_license']['id'] = 'delete_license';
  $handler->display->display_options['fields']['delete_license']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['delete_license']['field'] = 'delete_license';
  $handler->display->display_options['fields']['delete_license']['label'] = '';
  $handler->display->display_options['fields']['delete_license']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['external'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delete_license']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delete_license']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delete_license']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delete_license']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_license']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delete_license']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delete_license']['empty_zero'] = 0;
  $handler->display->display_options['fields']['delete_license']['text'] = 'delete';

  /* Display: Admin Page */
  $handler = $view->new_display('page', 'Admin Page', 'page');
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Commerce File License: License status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_file_license';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    'active' => 'active',
  );
  $handler->display->display_options['path'] = 'admin/commerce/file-licenses/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'File licenses';
  $handler->display->display_options['tab_options']['description'] = 'Manage files in the store.';
  $handler->display->display_options['tab_options']['weight'] = '5';
  $handler->display->display_options['tab_options']['name'] = 'management';


  $views[$view->name] = $view;


// -----------------------------------------------------------------------
// Order Admin Page

  $view = new view();
  $view->name = 'commerce_file_order';
  $view->description = 'Display a set of line items in a table.';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_line_item';
  $view->human_name = 'Order File Licenses';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'File Licenses';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer commerce_file_license';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'line_item_id' => 'line_item_id',
    'type' => 'type',
    'line_item_title' => 'line_item_title',
    'line_item_label' => 'line_item_title',
    'edit_product' => 'line_item_title',
    'quantity' => 'quantity',
    'commerce_file_line_item_files' => 'commerce_file_line_item_files',
    'granted' => 'granted',
    'address_count' => 'address_count',
    'download_count' => 'download_count',
    'time_remaining' => 'time_remaining',
    'download_limit' => 'download_limit',
    'address_limit' => 'address_limit',
    'duration' => 'duration',
    'status' => 'status',
    'license_issue_form' => 'license_issue_form',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'line_item_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'line_item_title' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'line_item_label' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_product' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'quantity' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'commerce_file_line_item_files' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'granted' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'download_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'time_remaining' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'download_limit' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_limit' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'duration' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'license_issue_form' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Header: Commerce Order: Issue File Licenses Form */
  $handler->display->display_options['header']['license_issue_form']['id'] = 'license_issue_form';
  $handler->display->display_options['header']['license_issue_form']['table'] = 'commerce_order';
  $handler->display->display_options['header']['license_issue_form']['field'] = 'license_issue_form';
  $handler->display->display_options['header']['license_issue_form']['label'] = 'Issue License Form';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty text';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No purchased files found.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Relationship: Commerce Line Item: Order ID */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['required'] = TRUE;
  /* Relationship: Commerce Line item: Referenced product */
  $handler->display->display_options['relationships']['commerce_product_product_id']['id'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['table'] = 'field_data_commerce_product';
  $handler->display->display_options['relationships']['commerce_product_product_id']['field'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['required'] = TRUE;
  /* Relationship: Commerce Line Item: Commerce File License using Line item references */
  $handler->display->display_options['relationships']['reverse_commerce_file_license_line_items_commerce_file_license']['id'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['relationships']['reverse_commerce_file_license_line_items_commerce_file_license']['table'] = 'commerce_line_item';
  $handler->display->display_options['relationships']['reverse_commerce_file_license_line_items_commerce_file_license']['field'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['relationships']['reverse_commerce_file_license_line_items_commerce_file_license']['label'] = 'License';
  /* Field: Commerce Line Item: Line item ID */
  $handler->display->display_options['fields']['line_item_id']['id'] = 'line_item_id';
  $handler->display->display_options['fields']['line_item_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_id']['field'] = 'line_item_id';
  $handler->display->display_options['fields']['line_item_id']['label'] = 'ID';
  $handler->display->display_options['fields']['line_item_id']['exclude'] = TRUE;
  /* Field: Commerce Line Item: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  /* Field: Commerce Line Item: Title */
  $handler->display->display_options['fields']['line_item_title']['id'] = 'line_item_title';
  $handler->display->display_options['fields']['line_item_title']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_title']['field'] = 'line_item_title';
  /* Field: Commerce Line Item: Label */
  $handler->display->display_options['fields']['line_item_label']['id'] = 'line_item_label';
  $handler->display->display_options['fields']['line_item_label']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_label']['field'] = 'line_item_label';
  $handler->display->display_options['fields']['line_item_label']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['line_item_label']['alter']['text'] = '([line_item_label])';
  /* Field: Commerce Product: Edit link */
  $handler->display->display_options['fields']['edit_product']['id'] = 'edit_product';
  $handler->display->display_options['fields']['edit_product']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['edit_product']['field'] = 'edit_product';
  $handler->display->display_options['fields']['edit_product']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['fields']['edit_product']['label'] = '';
  $handler->display->display_options['fields']['edit_product']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_product']['text'] = '[view]';
  /* Field: Commerce Line Item: Quantity */
  $handler->display->display_options['fields']['quantity']['id'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['quantity']['field'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['precision'] = '0';
  /* Field: Commerce File License: Licensed file */
  $handler->display->display_options['fields']['commerce_file_license_file']['id'] = 'commerce_file_license_file';
  $handler->display->display_options['fields']['commerce_file_license_file']['table'] = 'field_data_commerce_file_license_file';
  $handler->display->display_options['fields']['commerce_file_license_file']['field'] = 'commerce_file_license_file';
  $handler->display->display_options['fields']['commerce_file_license_file']['relationship'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['fields']['commerce_file_license_file']['label'] = 'Purchased File';
  $handler->display->display_options['fields']['commerce_file_license_file']['click_sort_column'] = 'fid';
  /* Field: Commerce File License: Granted date */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['relationship'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['fields']['granted']['label'] = 'Granted';
  $handler->display->display_options['fields']['granted']['date_format'] = 'short';
  /* Field: Commerce File License: Current number of addresses */
  $handler->display->display_options['fields']['address_count']['id'] = 'address_count';
  $handler->display->display_options['fields']['address_count']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['address_count']['field'] = 'address_count';
  $handler->display->display_options['fields']['address_count']['relationship'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['fields']['address_count']['exclude'] = TRUE;
  /* Field: Commerce File License: Current number of downloads */
  $handler->display->display_options['fields']['download_count']['id'] = 'download_count';
  $handler->display->display_options['fields']['download_count']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['download_count']['field'] = 'download_count';
  $handler->display->display_options['fields']['download_count']['relationship'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['fields']['download_count']['exclude'] = TRUE;
  /* Field: Commerce File License: Current time remaining */
  $handler->display->display_options['fields']['time_remaining']['id'] = 'time_remaining';
  $handler->display->display_options['fields']['time_remaining']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['time_remaining']['field'] = 'time_remaining';
  $handler->display->display_options['fields']['time_remaining']['relationship'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['fields']['time_remaining']['exclude'] = TRUE;
  $handler->display->display_options['fields']['time_remaining']['granularity'] = '2';
  /* Field: Commerce File License: Download limit */
  $handler->display->display_options['fields']['download_limit']['id'] = 'download_limit';
  $handler->display->display_options['fields']['download_limit']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['download_limit']['field'] = 'download_limit';
  $handler->display->display_options['fields']['download_limit']['relationship'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['fields']['download_limit']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['download_limit']['alter']['text'] = '[download_count] / [download_limit]';
  /* Field: Commerce File License: Address limit */
  $handler->display->display_options['fields']['address_limit']['id'] = 'address_limit';
  $handler->display->display_options['fields']['address_limit']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['address_limit']['field'] = 'address_limit';
  $handler->display->display_options['fields']['address_limit']['relationship'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['fields']['address_limit']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address_limit']['alter']['text'] = '[address_count] / [address_limit]';
  /* Field: Commerce File License: Duration */
  $handler->display->display_options['fields']['duration']['id'] = 'duration';
  $handler->display->display_options['fields']['duration']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['duration']['field'] = 'duration';
  $handler->display->display_options['fields']['duration']['relationship'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['fields']['duration']['granularity'] = '2';
  /* Field: Commerce File License: License status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_file_license';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['relationship'] = 'reverse_commerce_file_license_line_items_commerce_file_license';
  $handler->display->display_options['fields']['status']['link_to_entity'] = 'admin';
  /* Field: Commerce Line Item: Issue File Licenses Form */
  $handler->display->display_options['fields']['license_issue_form']['id'] = 'license_issue_form';
  $handler->display->display_options['fields']['license_issue_form']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['license_issue_form']['field'] = 'license_issue_form';
  $handler->display->display_options['fields']['license_issue_form']['label'] = 'Issue / Update';
  $handler->display->display_options['fields']['license_issue_form']['element_label_colon'] = FALSE;
  /* Sort criterion: Commerce Line Item: Line item ID */
  $handler->display->display_options['sorts']['line_item_id']['id'] = 'line_item_id';
  $handler->display->display_options['sorts']['line_item_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['sorts']['line_item_id']['field'] = 'line_item_id';
  /* Contextual filter: Commerce Order: Order ID */
  $handler->display->display_options['arguments']['order_id_1']['id'] = 'order_id_1';
  $handler->display->display_options['arguments']['order_id_1']['table'] = 'commerce_order';
  $handler->display->display_options['arguments']['order_id_1']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id_1']['relationship'] = 'order_id';
  $handler->display->display_options['arguments']['order_id_1']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['order_id_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id_1']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Commerce Line Item: Line item is of a product line item type */
  $handler->display->display_options['filters']['product_line_item_type']['id'] = 'product_line_item_type';
  $handler->display->display_options['filters']['product_line_item_type']['table'] = 'commerce_line_item';
  $handler->display->display_options['filters']['product_line_item_type']['field'] = 'product_line_item_type';
  $handler->display->display_options['filters']['product_line_item_type']['value'] = '1';
  $handler->display->display_options['filters']['product_line_item_type']['group'] = 1;
  /* Filter criterion: Commerce Product: Product is a product type with Commerce File fields */
  $handler->display->display_options['filters']['commerce_file_product_type']['id'] = 'commerce_file_product_type';
  $handler->display->display_options['filters']['commerce_file_product_type']['table'] = 'commerce_product';
  $handler->display->display_options['filters']['commerce_file_product_type']['field'] = 'commerce_file_product_type';
  $handler->display->display_options['filters']['commerce_file_product_type']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['filters']['commerce_file_product_type']['value'] = '1';
  $handler->display->display_options['filters']['commerce_file_product_type']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/commerce/orders/%/licenses';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Licenses';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  $views[$view->name] = $view;


  return $views;
}
