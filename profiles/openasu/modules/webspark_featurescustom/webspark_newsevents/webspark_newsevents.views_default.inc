<?php
/**
 * @file
 * webspark_newsevents.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function webspark_newsevents_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'asu_news_new';
  $view->description = 'Views of ASU News Feeds';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ASU News new';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'column col-md-4 col-sm-6';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: News image */
  $handler->display->display_options['fields']['field_asunews_image']['id'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['table'] = 'field_data_field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['field'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asunews_image']['settings'] = array(
    'image_style' => 'asunews_thumbnail',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Posted */
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['id'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['settings'] = array(
    'format_type' => 'panopoly_day',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
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

  /* Display: Top Story News Content pane */
  $handler = $view->new_display('panel_pane', 'Top Story News Content pane', 'panel_pane_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['display_description'] = 'Shows only Top Story';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'column col-md-12 col-sm-12';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: News image */
  $handler->display->display_options['fields']['field_asunews_image']['id'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['table'] = 'field_data_field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['field'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image']['element_wrapper_class'] = 'col-lg-8';
  $handler->display->display_options['fields']['field_asunews_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asunews_image']['settings'] = array(
    'image_style' => 'asunews_image_style',
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
  /* Field: Content: Posted */
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['id'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['settings'] = array(
    'format_type' => 'panopoly_day',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['text'] = '<h4>[title]</h4><br />
[field_asunews_post_date_iso]
[body]<br />';
  $handler->display->display_options['fields']['body']['element_class'] = 'col-lg-4';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Global: Random */
  $handler->display->display_options['sorts']['random']['id'] = 'random';
  $handler->display->display_options['sorts']['random']['table'] = 'views';
  $handler->display->display_options['sorts']['random']['field'] = 'random';
  $handler->display->display_options['sorts']['random']['expose']['label'] = 'Random';
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
    'asu_news' => 'asu_news',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Has taxonomy term */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  
  // Get tid for Top Articles and use the tid - Chizuko
  $top_article_tid = key(taxonomy_get_term_by_name("Top Articles"));
  $handler->display->display_options['filters']['tid']['value'] = array(
    //74 => '74',
    $top_article_tid => $top_article_tid, 
  );
  
  $handler->display->display_options['filters']['tid']['type'] = 'select';
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'asu_news';

  /* Display: Feature Story News Content pane */
  $handler = $view->new_display('panel_pane', 'Feature Story News Content pane', 'panel_pane_1');
  $handler->display->display_options['display_description'] = 'Shows Featured Story first, then, shows the rest in the date descending order.';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Read more news */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['ui_name'] = 'Read more news';
  $handler->display->display_options['footer']['area']['content'] = '<h5><a href=\'/news\'>Read more news</a></h5>';
  $handler->display->display_options['footer']['area']['format'] = 'panopoly_wysiwyg_text';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Global: Random */
  $handler->display->display_options['sorts']['random']['id'] = 'random';
  $handler->display->display_options['sorts']['random']['table'] = 'views';
  $handler->display->display_options['sorts']['random']['field'] = 'random';
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
    'asu_news' => 'asu_news',
  );
  /* Filter criterion: Content: Has taxonomy term */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  
  // Get tid for Feature Articles and use the tid - Chizuko
  $feature_article_tid = key(taxonomy_get_term_by_name("Feature Articles"));
  $handler->display->display_options['filters']['tid']['value'] = array(
    //75 => '75',
    $feature_article_tid => $feature_article_tid, 
  );
    
  $handler->display->display_options['filters']['tid']['type'] = 'select';
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'asu_news';

  /* Display: News Page */
  $handler = $view->new_display('page', 'News Page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'News';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_asunews_post_date_iso_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    1 => array(
      'field' => 'field_asunews_post_date_iso_2',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'column col-md-4 col-sm-6';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: News image */
  $handler->display->display_options['fields']['field_asunews_image']['id'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['table'] = 'field_data_field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['field'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asunews_image']['settings'] = array(
    'image_style' => 'asunews_thumbnail',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Posted */
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['id'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['settings'] = array(
    'format_type' => 'panopoly_day',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
  /* Field: Year - For grouping */
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['id'] = 'field_asunews_post_date_iso_1';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['ui_name'] = 'Year - For grouping';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['settings'] = array(
    'format_type' => 'year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Full month - For grouping */
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['id'] = 'field_asunews_post_date_iso_2';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['ui_name'] = 'Full month - For grouping';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['settings'] = array(
    'format_type' => 'month',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['path'] = 'news';

  /* Display: News Content pane */
  $handler = $view->new_display('panel_pane', 'News Content pane', 'panel_pane_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['display_description'] = 'Lists News by month by year';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_asunews_post_date_iso_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    1 => array(
      'field' => 'field_asunews_post_date_iso_2',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'column col-md-4 col-sm-6';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: News image */
  $handler->display->display_options['fields']['field_asunews_image']['id'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['table'] = 'field_data_field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['field'] = 'field_asunews_image';
  $handler->display->display_options['fields']['field_asunews_image']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asunews_image']['settings'] = array(
    'image_style' => 'asunews_thumbnail',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Posted */
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['id'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso']['settings'] = array(
    'format_type' => 'panopoly_day',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
  /* Field: Year - For grouping */
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['id'] = 'field_asunews_post_date_iso_1';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['ui_name'] = 'Year - For grouping';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_1']['settings'] = array(
    'format_type' => 'year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Full month - For grouping */
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['id'] = 'field_asunews_post_date_iso_2';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['table'] = 'field_data_field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['field'] = 'field_asunews_post_date_iso';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['ui_name'] = 'Full month - For grouping';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['label'] = '';
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asunews_post_date_iso_2']['settings'] = array(
    'format_type' => 'month',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $export['asu_news_new'] = $view;

  $view = new view();
  $view->name = 'events_new';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ASU Events new';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Go';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'column col-md-4 col-sm-6';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Year - For grouping */
  $handler->display->display_options['fields']['field_asuevent_very_start_date']['id'] = 'field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date']['table'] = 'field_data_field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date']['field'] = 'field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date']['ui_name'] = 'Year - For grouping';
  $handler->display->display_options['fields']['field_asuevent_very_start_date']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_very_start_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date']['settings'] = array(
    'format_type' => 'year',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Full month - For grouping */
  $handler->display->display_options['fields']['field_asuevent_very_start_date_1']['id'] = 'field_asuevent_very_start_date_1';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_1']['table'] = 'field_data_field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_1']['field'] = 'field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_1']['ui_name'] = 'Full month - For grouping';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_1']['settings'] = array(
    'format_type' => 'month',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Event date (day) */
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['id'] = 'field_asuevent_very_start_date_4';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['table'] = 'field_data_field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['field'] = 'field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['ui_name'] = 'Event date (day)';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['alter']['text'] = '<div class=\'the-event-day\'>[field_asuevent_very_start_date_4]</div>';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_4']['settings'] = array(
    'format_type' => 'event_date_day',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Event date (day and month) */
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['id'] = 'field_asuevent_very_start_date_2';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['table'] = 'field_data_field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['field'] = 'field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['ui_name'] = 'Event date (day and month)';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['alter']['text'] = '<div class=\'event-day-month\'>[field_asuevent_very_start_date_4][field_asuevent_very_start_date_2]</div>';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_2']['settings'] = array(
    'format_type' => 'event_date_month',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Event date (date) */
  $handler->display->display_options['fields']['field_asuevent_very_start_date_3']['id'] = 'field_asuevent_very_start_date_3';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_3']['table'] = 'field_data_field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_3']['field'] = 'field_asuevent_very_start_date';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_3']['ui_name'] = 'Event date (date)';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_3']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_3']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_3']['alter']['text'] = '<div class=\'event-date-wrap\'>
[field_asuevent_very_start_date_2]
<div class=\'the-event-date\'>[field_asuevent_very_start_date_3]</div>
</div>';
  $handler->display->display_options['fields']['field_asuevent_very_start_date_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_very_start_date_3']['settings'] = array(
    'format_type' => 'event_date_date_',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<div class=\'event-title\'>[title]</div>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Subtitle */
  $handler->display->display_options['fields']['field_asuevent_subtitle']['id'] = 'field_asuevent_subtitle';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['table'] = 'field_data_field_asuevent_subtitle';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['field'] = 'field_asuevent_subtitle';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['element_type'] = 'strong';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['hide_empty'] = TRUE;
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_asuevent_location']['id'] = 'field_asuevent_location';
  $handler->display->display_options['fields']['field_asuevent_location']['table'] = 'field_data_field_asuevent_location';
  $handler->display->display_options['fields']['field_asuevent_location']['field'] = 'field_asuevent_location';
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['text'] = '<span class=\'location\'>[field_asuevent_location]</span>';
  $handler->display->display_options['fields']['field_asuevent_location']['hide_empty'] = TRUE;
  /* Field: Content: Room */
  $handler->display->display_options['fields']['field_asuevent_room']['id'] = 'field_asuevent_room';
  $handler->display->display_options['fields']['field_asuevent_room']['table'] = 'field_data_field_asuevent_room';
  $handler->display->display_options['fields']['field_asuevent_room']['field'] = 'field_asuevent_room';
  $handler->display->display_options['fields']['field_asuevent_room']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['text'] = '<span class=\'room\'>[field_asuevent_room]</span>';
  $handler->display->display_options['fields']['field_asuevent_room']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_room']['hide_empty'] = TRUE;
  /* Field: Content: Display Date (Text) */
  $handler->display->display_options['fields']['field_asuevent_display_date']['id'] = 'field_asuevent_display_date';
  $handler->display->display_options['fields']['field_asuevent_display_date']['table'] = 'field_data_field_asuevent_display_date';
  $handler->display->display_options['fields']['field_asuevent_display_date']['field'] = 'field_asuevent_display_date';
  $handler->display->display_options['fields']['field_asuevent_display_date']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_display_date']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_asuevent_display_date']['element_class'] = 'display-date';
  $handler->display->display_options['fields']['field_asuevent_display_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_display_date']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_display_date']['delta_offset'] = '0';
  /* Sort criterion: Content: Very start and end date -  start date (field_asuevent_very_start_date) */
  $handler->display->display_options['sorts']['field_asuevent_very_start_date_value']['id'] = 'field_asuevent_very_start_date_value';
  $handler->display->display_options['sorts']['field_asuevent_very_start_date_value']['table'] = 'field_data_field_asuevent_very_start_date';
  $handler->display->display_options['sorts']['field_asuevent_very_start_date_value']['field'] = 'field_asuevent_very_start_date_value';
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
    'asu_event' => 'asu_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Very start and end date -  start date (field_asuevent_very_start_date) */
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value']['id'] = 'field_asuevent_very_start_date_value';
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value']['table'] = 'field_data_field_asuevent_very_start_date';
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value']['field'] = 'field_asuevent_very_start_date_value';
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value']['default_date'] = 'now';

  /* Display: Upcoming Events Content pane */
  $handler = $view->new_display('panel_pane', 'Upcoming Events Content pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming Events';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: See all events */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['ui_name'] = 'See all events';
  $handler->display->display_options['footer']['area']['content'] = '<br clear=\'all\' /><h5><a href=\'/events\'>See all events</a></h5>';
  $handler->display->display_options['footer']['area']['format'] = 'panopoly_wysiwyg_text';

  /* Display: Events Page */
  $handler = $view->new_display('page', 'Events Page', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Events';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_asuevent_very_start_date',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    1 => array(
      'field' => 'field_asuevent_very_start_date_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'column col-md-4 col-sm-6';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'events';

  /* Display: Events Content pane */
  $handler = $view->new_display('panel_pane', 'Events Content pane', 'panel_pane_2');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_asuevent_very_start_date',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    1 => array(
      'field' => 'field_asuevent_very_start_date_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'column col-md-4 col-sm-6';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['events_new'] = $view;

  return $export;
}
