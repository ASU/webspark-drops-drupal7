<?php
/**
 * @file
 * asu_events.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function asu_events_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'asu_event_images';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ASU Event images';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ASU Event images';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_asuevent_image']['id'] = 'field_asuevent_image';
  $handler->display->display_options['fields']['field_asuevent_image']['table'] = 'field_data_field_asuevent_image';
  $handler->display->display_options['fields']['field_asuevent_image']['field'] = 'field_asuevent_image';
  $handler->display->display_options['fields']['field_asuevent_image']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_asuevent_image']['settings'] = array(
    'image_style' => 'asuevent_image_style',
    'image_link' => 'file',
  );
  $handler->display->display_options['fields']['field_asuevent_image']['field_api_classes'] = 0;
  /* Field: Content: Image alt */
  $handler->display->display_options['fields']['field_asuevent_img_alt']['id'] = 'field_asuevent_img_alt';
  $handler->display->display_options['fields']['field_asuevent_img_alt']['table'] = 'field_data_field_asuevent_img_alt';
  $handler->display->display_options['fields']['field_asuevent_img_alt']['field'] = 'field_asuevent_img_alt';
  $handler->display->display_options['fields']['field_asuevent_img_alt']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_img_alt']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_img_alt']['field_api_classes'] = 0;
  /* Field: PHP to display image with alt text */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'PHP to display image with alt text';
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

// Getting file path to the image
unset($path);
if(isset($data->field_field_asuevent_image[0][\'rendered\'][\'#path\'][\'path\'])) {
  $path = $data->field_field_asuevent_image[0][\'rendered\'][\'#path\'][\'path\'];
}

if(isset($path) ) {
  // Getting alt text
  if(isset($data->field_field_asuevent_img_alt[0][\'rendered\'][\'#markup\'])) {
    $alt = $data->field_field_asuevent_img_alt[0][\'rendered\'][\'#markup\'];
  }
  if(!(isset($alt))) {
    $alt = "";
  }

  // Loading image
  print theme(\'image\', array(\'path\' => $path, \'alt\' => $alt));
}
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Content: Image caption */
  $handler->display->display_options['fields']['field_asuevent_img_caption']['id'] = 'field_asuevent_img_caption';
  $handler->display->display_options['fields']['field_asuevent_img_caption']['table'] = 'field_data_field_asuevent_img_caption';
  $handler->display->display_options['fields']['field_asuevent_img_caption']['field'] = 'field_asuevent_img_caption';
  $handler->display->display_options['fields']['field_asuevent_img_caption']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_img_caption']['field_api_classes'] = 0;
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
  $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['nid']['not'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'test-asu-event-images';

  /* Display: Block - ASU Event images */
  $handler = $view->new_display('block', 'Block - ASU Event images', 'block_1');
  $handler->display->display_options['block_description'] = 'ASU Event images view block';

  /* Display: Block - ASU Event email */
  $handler = $view->new_display('block', 'Block - ASU Event email', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'ASU Event email';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_asuevent_email']['id'] = 'field_asuevent_email';
  $handler->display->display_options['fields']['field_asuevent_email']['table'] = 'field_data_field_asuevent_email';
  $handler->display->display_options['fields']['field_asuevent_email']['field'] = 'field_asuevent_email';
  $handler->display->display_options['fields']['field_asuevent_email']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['text'] = '<a href=\'[field_asuevent_email]\'>[field_asuevent_email]</a>';
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_email']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_email']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_email']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_email']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_email']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $export['asu_event_images'] = $view;

  $view = new view;
  $view->name = 'calendar';
  $view->description = '';
  $view->tag = 'Calendar';
  $view->base_table = 'node';
  $view->human_name = 'Calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['link_display'] = 'page_1';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
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
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Date (ISO format) */
  $handler->display->display_options['fields']['field_asuevent_date']['id'] = 'field_asuevent_date';
  $handler->display->display_options['fields']['field_asuevent_date']['table'] = 'field_data_field_asuevent_date';
  $handler->display->display_options['fields']['field_asuevent_date']['field'] = 'field_asuevent_date';
  $handler->display->display_options['fields']['field_asuevent_date']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['settings'] = array(
    'format_type' => 'time',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_asuevent_date']['group_rows'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_asuevent_date']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['field_api_classes'] = 0;
  /* Sort criterion: Content: Date (ISO format) -  start date (field_asuevent_date) */
  $handler->display->display_options['sorts']['field_asuevent_date_value']['id'] = 'field_asuevent_date_value';
  $handler->display->display_options['sorts']['field_asuevent_date_value']['table'] = 'field_data_field_asuevent_date';
  $handler->display->display_options['sorts']['field_asuevent_date_value']['field'] = 'field_asuevent_date_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Month */
  $handler = $view->new_display('page', 'Month', 'page_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['colors']['legend'] = 'type';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_asuevent_date.field_asuevent_date_value' => 'field_data_field_asuevent_date.field_asuevent_date_value',
  );
  $handler->display->display_options['path'] = 'calendar/month';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Month';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Calendar';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Week */
  $handler = $view->new_display('page', 'Week', 'page_2');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'week';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'week';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'week';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_asuevent_date.field_asuevent_date_value' => 'field_data_field_asuevent_date.field_asuevent_date_value',
  );
  $handler->display->display_options['path'] = 'calendar/week';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Week';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Day */
  $handler = $view->new_display('page', 'Day', 'page_3');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'day';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'day';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'day';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_asuevent_date.field_asuevent_date_value' => 'field_data_field_asuevent_date.field_asuevent_date_value',
  );
  $handler->display->display_options['path'] = 'calendar/day';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Day';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Year */
  $handler = $view->new_display('page', 'Year', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'year';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'year';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Date (ISO format) */
  $handler->display->display_options['fields']['field_asuevent_date']['id'] = 'field_asuevent_date';
  $handler->display->display_options['fields']['field_asuevent_date']['table'] = 'field_data_field_asuevent_date';
  $handler->display->display_options['fields']['field_asuevent_date']['field'] = 'field_asuevent_date';
  $handler->display->display_options['fields']['field_asuevent_date']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields']['field_asuevent_date']['group_rows'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_asuevent_date']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_asuevent_date']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'year';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_asuevent_date.field_asuevent_date_value' => 'field_data_field_asuevent_date.field_asuevent_date_value',
  );
  $handler->display->display_options['path'] = 'calendar/year';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Year';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '-1';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'mini';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '1';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_asuevent_date.field_asuevent_date_value' => 'field_data_field_asuevent_date.field_asuevent_date_value',
  );

  /* Display: Upcoming */
  $handler = $view->new_display('block', 'Upcoming', 'block_2');
  $handler->display->display_options['display_description'] = 'Upcoming events block';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['add_delta'] = 'yes';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_asuevent_date.field_asuevent_date_value' => 'field_data_field_asuevent_date.field_asuevent_date_value',
  );
  $export['calendar'] = $view;

  $view = new view;
  $view->name = 'events';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Events';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Go';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_news_events_thumb_img' => 'field_news_events_thumb_img',
    'title' => 'title',
    'field_asuevent_subtitle' => 'title',
    'field_asuevent_display_date' => 'title',
    'field_asuevent_location' => 'title',
    'field_asuevent_room' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_news_events_thumb_img' => array(
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
    'field_asuevent_subtitle' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asuevent_display_date' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asuevent_location' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_asuevent_room' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: Content: Thumb image (Used in Highlights) */
  $handler->display->display_options['fields']['field_news_events_thumb_img']['id'] = 'field_news_events_thumb_img';
  $handler->display->display_options['fields']['field_news_events_thumb_img']['table'] = 'field_data_field_news_events_thumb_img';
  $handler->display->display_options['fields']['field_news_events_thumb_img']['field'] = 'field_news_events_thumb_img';
  $handler->display->display_options['fields']['field_news_events_thumb_img']['label'] = '';
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_news_events_thumb_img']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_news_events_thumb_img']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_news_events_thumb_img']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<div class=\'event-title\'>[title]</div>';
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
  /* Field: Content: Subtitle */
  $handler->display->display_options['fields']['field_asuevent_subtitle']['id'] = 'field_asuevent_subtitle';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['table'] = 'field_data_field_asuevent_subtitle';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['field'] = 'field_asuevent_subtitle';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['element_type'] = 'strong';
  $handler->display->display_options['fields']['field_asuevent_subtitle']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_subtitle']['field_api_classes'] = 0;
  /* Field: Content: Display Date (Text) */
  $handler->display->display_options['fields']['field_asuevent_display_date']['id'] = 'field_asuevent_display_date';
  $handler->display->display_options['fields']['field_asuevent_display_date']['table'] = 'field_data_field_asuevent_display_date';
  $handler->display->display_options['fields']['field_asuevent_display_date']['field'] = 'field_asuevent_display_date';
  $handler->display->display_options['fields']['field_asuevent_display_date']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_asuevent_display_date']['element_class'] = 'display-date';
  $handler->display->display_options['fields']['field_asuevent_display_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_display_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_display_date']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_display_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_display_date']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_asuevent_display_date']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_asuevent_display_date']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_asuevent_display_date']['field_api_classes'] = 0;
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_asuevent_location']['id'] = 'field_asuevent_location';
  $handler->display->display_options['fields']['field_asuevent_location']['table'] = 'field_data_field_asuevent_location';
  $handler->display->display_options['fields']['field_asuevent_location']['field'] = 'field_asuevent_location';
  $handler->display->display_options['fields']['field_asuevent_location']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['text'] = '<span class=\'location\'>[field_asuevent_location]</span>';
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_location']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_location']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_location']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_location']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_location']['field_api_classes'] = 0;
  /* Field: Content: Room */
  $handler->display->display_options['fields']['field_asuevent_room']['id'] = 'field_asuevent_room';
  $handler->display->display_options['fields']['field_asuevent_room']['table'] = 'field_data_field_asuevent_room';
  $handler->display->display_options['fields']['field_asuevent_room']['field'] = 'field_asuevent_room';
  $handler->display->display_options['fields']['field_asuevent_room']['label'] = '';
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['text'] = '<span class=\'room\'>[field_asuevent_room]</span>';
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asuevent_room']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_asuevent_room']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_room']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_asuevent_room']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_asuevent_room']['field_api_classes'] = 0;
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
  /* Filter criterion: Content: Very start and end date - end date (field_asuevent_very_start_date:value2) */
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value2']['id'] = 'field_asuevent_very_start_date_value2';
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value2']['table'] = 'field_data_field_asuevent_very_start_date';
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value2']['field'] = 'field_asuevent_very_start_date_value2';
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_asuevent_very_start_date_value2']['default_date'] = 'now';
  /* Filter criterion: Content: Taxonomy: ASU Events Category (field_asuevent_tax_category) */
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['id'] = 'field_asuevent_tax_category_tid';
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['table'] = 'field_data_field_asuevent_tax_category';
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['field'] = 'field_asuevent_tax_category_tid';
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['expose']['operator_id'] = 'field_asuevent_tax_category_tid_op';
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['expose']['label'] = 'Category';
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['expose']['operator'] = 'field_asuevent_tax_category_tid_op';
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['expose']['identifier'] = 'field_asuevent_tax_category_tid';
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['vocabulary'] = 'asu_events_category';
  $handler->display->display_options['filters']['field_asuevent_tax_category_tid']['error_message'] = 1;
  /* Filter criterion: Content: Taxonomy: ASU Events Type (field_asuevent_tax_type) */
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['id'] = 'field_asuevent_tax_type_tid';
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['table'] = 'field_data_field_asuevent_tax_type';
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['field'] = 'field_asuevent_tax_type_tid';
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['expose']['operator_id'] = 'field_asuevent_tax_type_tid_op';
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['expose']['operator'] = 'field_asuevent_tax_type_tid_op';
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['expose']['identifier'] = 'field_asuevent_tax_type_tid';
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['vocabulary'] = 'asu_events_type';
  $handler->display->display_options['filters']['field_asuevent_tax_type_tid']['error_message'] = 1;
  /* Filter criterion: Content: Taxonomy: ASU Events Audience (field_asuevent_tax_audience) */
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['id'] = 'field_asuevent_tax_audience_tid';
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['table'] = 'field_data_field_asuevent_tax_audience';
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['field'] = 'field_asuevent_tax_audience_tid';
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['expose']['operator_id'] = 'field_asuevent_tax_audience_tid_op';
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['expose']['label'] = 'Audience';
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['expose']['operator'] = 'field_asuevent_tax_audience_tid_op';
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['expose']['identifier'] = 'field_asuevent_tax_audience_tid';
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['vocabulary'] = 'asu_events_audience';
  $handler->display->display_options['filters']['field_asuevent_tax_audience_tid']['error_message'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'events';
  $export['events'] = $view;

  return $export;
}
