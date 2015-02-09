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
  $view->description = '';
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
  /* Field: Content: Body */
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
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_offset'] = '0';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$v = count($data->_field_data[\'nid\'][\'entity\']->field_asu_degree_campus[\'und\']) - 1;
if ($data->_field_data[\'nid\'][\'entity\']->field_asu_degree_campus[\'und\'][$v][\'value\']== \'Online\') {
  echo \'Yes\';
}
else {
  echo \'No\';
}
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
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
    <!--<div class="asu-degree-field-title">Degree Type:</div> [field_asu_degree]<br>-->
    <div class="asu-degree-field-title">Available Online:</div> [php]
</div>';
  $handler->display->display_options['fields']['field_asu_degree']['element_label_colon'] = FALSE;
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
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['group'] = 1;

  /* Display: Page - Undergrad all */
  $handler = $view->new_display('page', 'Page - Undergrad all', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate All';
  $handler->display->display_options['display_description'] = 'Displays all undergraduate degrees';
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
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
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
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['value'] = 'false';
  $handler->display->display_options['path'] = 'asu_degrees/ugrad/major';

  /* Display: Page - Undergrad minors/certificates */
  $handler = $view->new_display('page', 'Page - Undergrad minors/certificates', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Undergraduate Minors/Certificates';
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
  $handler->display->display_options['filters']['field_asu_degree_program_value']['value'] = 'undergrad';
  /* Filter criterion: Content: Cert option: True or False (field_asu_degree_cert) */
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['id'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['table'] = 'field_data_field_asu_degree_cert';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['field'] = 'field_asu_degree_cert_value';
  $handler->display->display_options['filters']['field_asu_degree_cert_value']['value'] = 'true';
  $handler->display->display_options['path'] = 'asu_degrees/ugrad/minor_cert';

  /* Display: Page - Graduate */
  $handler = $view->new_display('page', 'Page - Graduate', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Graduate';
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
  /* Field: Content: Body */
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
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_asu_degree_campus']['delta_offset'] = '0';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$v = count($data->_field_data[\'nid\'][\'entity\']->field_asu_degree_campus[\'und\']) - 1;
if ($data->_field_data[\'nid\'][\'entity\']->field_asu_degree_campus[\'und\'][$v][\'value\']== \'Online\') {
  echo \'Yes\';
}
else {
  echo \'No\';
}
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
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
    <div class="asu-degree-major-title">[field_asu_degree_awarded]</div>
    [body]
    <div class="asu-degree-field-title">Location:</div> [field_asu_degree_campus]<br>
    <!--<div class="asu-degree-field-title">Degree Type:</div> [field_asu_degree]<br>-->
    <div class="asu-degree-field-title">Available Online:</div> [php]
</div>';
  $handler->display->display_options['fields']['field_asu_degree']['element_label_colon'] = FALSE;
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
  $handler->display->display_options['path'] = 'asu_degrees/grad';
  $export['asu_degrees_feature'] = $view;

  return $export;
}
