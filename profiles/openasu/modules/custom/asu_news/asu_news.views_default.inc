<?php
/**
 * @file
 * asu_news.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function asu_news_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'asu_news';
  $view->description = 'Views of ASU News Feeds';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ASU News';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent News';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['empty'] = FALSE;
  /* Field: Content: News image */
  $handler->display->display_options['fields']['field_asunews_image']['id'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['table'] = 'field_data_field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['field'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asunews_image']['settings'] = array(
    'image_style' => 'asunews_thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_asunews_image']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Posted */
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['id'] = 'field_asunews_post_date_iso_3';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['settings'] = array(
    'format_type' => 'asu_news_date_format_very_short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['field_api_classes'] = 0;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['body']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: Content: Posted */
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['id'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['field'] = 'field_asunews_post_date_iso';
  /* Sort criterion: Content: Posted (field_asunews_post_date_iso) */
  $handler->display->display_options['sorts']['field_asunews_post_date_iso_value']['id'] = 'field_asunews_post_date_iso_value';
  $handler->display->display_options['sorts']['field_asunews_post_date_iso_value']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['sorts']['field_asunews_post_date_iso_value']['field'] = 'field_asunews_post_date_iso_value';
  $handler->display->display_options['sorts']['field_asunews_post_date_iso_value']['order'] = 'DESC';
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
    'asu_news' => 'asu_news',
  );

  /* Display: Page - Recent News */
  $handler = $view->new_display('page', 'Page - Recent News', 'page');
  $handler->display->display_options['display_description'] = 'Teasers of recent ASU News feed items';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_asunews_post_date_iso_2',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['empty'] = FALSE;
  $handler->display->display_options['header']['php']['php_output'] = '<?php

/* Display header */

$view = views_get_current_view();

$year = $view->args[0];

echo "<h1 class=\'title\'>News " . $year . "</h1>";





/* Display months at the top of the page */



$uri = $_SERVER[\'REQUEST_URI\'];



echo "<a href=\'" . $uri . "#January\'>Jan</a> | <a href=\'" . $uri . "#February\'>Feb</a> | <a href=\'" . $uri . "#March\'>Mar</a> | <a href=\'" . $uri . "#April\'>Apr</a> | <a href=\'" . $uri . "#May\'>May</a> | <a href=\'" . $uri . "#June\'>Jun</a> | <a href=\'" . $uri . "#July\'>Jul</a> | <a href=\'" . $uri . "#August\'>Aug</a> | <a href=\'" . $uri . "#September\'>Sep</a> | <a href=\'" . $uri . "#October\'>Oct</a> | <a href=\'" . $uri . "#November\'>Nov</a> | <a href=\'" . $uri . "#December\'>Dec</a>";



?>';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Posted - year */
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['id'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['ui_name'] = 'Posted - year';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['settings'] = array(
    'format_type' => 'year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['field_api_classes'] = 0;
  /* Field: Posted - month */
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['id'] = 'field_asunews_post_date_iso_1';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['ui_name'] = 'Posted - month';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['strip_tags'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['settings'] = array(
    'format_type' => 'month',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['field_api_classes'] = 0;
  /* Field: Posted - month (Used for grouping) */
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['id'] = 'field_asunews_post_date_iso_2';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['ui_name'] = 'Posted - month (Used for grouping)';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['text'] = '<a name=\'[field_asunews_post_date_iso_1]\'>[field_asunews_post_date_iso_1]</a>';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['settings'] = array(
    'format_type' => 'month',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['field_api_classes'] = 0;
  /* Field: Content: News image */
  $handler->display->display_options['fields']['field_asunews_image']['id'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['table'] = 'field_data_field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['field'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asunews_image']['settings'] = array(
    'image_style' => 'asunews_thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_asunews_image']['field_api_classes'] = 0;
  /* Field: Content: Posted */
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['id'] = 'field_asunews_post_date_iso_3';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['settings'] = array(
    'format_type' => 'very_short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_asunews_post_date_iso_3']['field_api_classes'] = 0;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['body']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: text: back to top */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'text: back to top';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href=\'#\'>(back to top)</a>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Posted (field_asunews_post_date_iso) */
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['id'] = 'field_asunews_post_date_iso_value';
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['field'] = 'field_asunews_post_date_iso_value';
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_asunews_post_date_iso_value']['granularity'] = 'year';
  $handler->display->display_options['path'] = 'asunews';
  $export['asu_news'] = $view;

  $view = new view;
  $view->name = 'asu_news_images';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ASU News Images';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ASU News Images';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_asunews_image_by' => 'field_asunews_image_by',
  );
  $handler->display->display_options['row_options']['hide_empty'] = 1;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  /* Field: Content: News image */
  $handler->display->display_options['fields']['field_asunews_image']['id'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['table'] = 'field_data_field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['field'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asunews_image']['settings'] = array(
    'image_style' => 'asunews_image_style',
    'image_link' => 'file',
  );
  $handler->display->display_options['fields']['field_asunews_image']['field_api_classes'] = 0;
  /* Field: Content: News image alt text */
  $handler->display->display_options['fields']['field_asunews_image_alt']['id'] = 'field_asunews_image_alt';
  $handler->display->display_options['fields']['field_asunews_image_alt']['table'] = 'field_data_field_asunews_image_alt';
  $handler->display->display_options['fields']['field_asunews_image_alt']['field'] = 'field_asunews_image_alt';
  $handler->display->display_options['fields']['field_asunews_image_alt']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image_alt']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image_alt']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_alt']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_alt']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_alt']['field_api_classes'] = 0;
  /* Field: Content: News image title */
  $handler->display->display_options['fields']['field_asunews_image_title']['id'] = 'field_asunews_image_title';
  $handler->display->display_options['fields']['field_asunews_image_title']['table'] = 'field_data_field_asunews_image_title';
  $handler->display->display_options['fields']['field_asunews_image_title']['field'] = 'field_asunews_image_title';
  $handler->display->display_options['fields']['field_asunews_image_title']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image_title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image_title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_title']['field_api_classes'] = 0;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['php']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['php']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['php']['alter']['external'] = 0;
  $handler->display->display_options['fields']['php']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['php']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['php']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['php']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['php']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['php']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['php']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['php']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['php']['alter']['html'] = 0;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['php']['hide_empty'] = 1;
  $handler->display->display_options['fields']['php']['empty_zero'] = 0;
  $handler->display->display_options['fields']['php']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
//print_r($data);
/**
 * Loading image with alt text and image title text
 */

// Getting file path to the image
if(isset($path)){
  unset($path);
}

if(isset($data->field_field_asunews_image[0][\'rendered\'][\'#item\'][\'uri\'])) {
  $path = $data->field_field_asunews_image[0][\'rendered\'][\'#item\'][\'uri\'];
}

if(isset($path) ) {
  // Getting alt text
  if(isset($data->field_field_asunews_image_alt[0][\'rendered\'][\'#markup\'])) {
    $alt = $data->field_field_asunews_image_alt[0][\'rendered\'][\'#markup\'];
  }

  // Getting image title text
  if(isset($data->field_field_asunews_image_title[0][\'rendered\'][\'#markup\'])) {
    $image_title = trim($data->field_field_asunews_image_title[0][\'rendered\'][\'#markup\']);
  }

  if(!(isset($alt))) {
    $alt = "";
  }
  if(!(isset($image_title))) {
    $image_title = "";
  }
  
  $style_name = "asunews_image_style";

  // Loading image
  print theme(\'image_style\', array(\'style_name\' => $style_name, \'path\' => $path, \'alt\' => $alt, \'title\' => $image_title));
 }
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Content: News image description */
  $handler->display->display_options['fields']['field_asunews_image_desc']['id'] = 'field_asunews_image_desc';
  $handler->display->display_options['fields']['field_asunews_image_desc']['table'] = 'field_data_field_asunews_image_desc';
  $handler->display->display_options['fields']['field_asunews_image_desc']['field'] = 'field_asunews_image_desc';
  $handler->display->display_options['fields']['field_asunews_image_desc']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image_desc']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_desc']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_desc']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_desc']['field_api_classes'] = 0;
  /* Field: Content: News image by */
  $handler->display->display_options['fields']['field_asunews_image_by']['id'] = 'field_asunews_image_by';
  $handler->display->display_options['fields']['field_asunews_image_by']['table'] = 'field_data_field_asunews_image_by';
  $handler->display->display_options['fields']['field_asunews_image_by']['field'] = 'field_asunews_image_by';
  $handler->display->display_options['fields']['field_asunews_image_by']['label'] = 'Photo by';
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_by']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_by']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asunews_image_by']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asunews_image_by']['field_api_classes'] = 0;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['nid']['validate']['fail'] = 'empty';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['nid']['not'] = 0;
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
    'asu_news' => 'asu_news',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'test-asu-news-images';
  $export['asu_news_images'] = $view;

  return $export;
}
