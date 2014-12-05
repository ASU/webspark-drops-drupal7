<?php
/**
 * @file
 * asu_rfi_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function asu_rfi_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'asu_rfi_submissions_report';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ASU RFI submissions report';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ASU RFI submissions report';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
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
      'empty_column' => 0,
    ),
  );
  /* Field: Content: First name */
  $handler->display->display_options['fields']['field_rfi_first_name']['id'] = 'field_rfi_first_name';
  $handler->display->display_options['fields']['field_rfi_first_name']['table'] = 'field_data_field_rfi_first_name';
  $handler->display->display_options['fields']['field_rfi_first_name']['field'] = 'field_rfi_first_name';
  $handler->display->display_options['fields']['field_rfi_first_name']['element_label_colon'] = FALSE;
  /* Field: Content: Last name */
  $handler->display->display_options['fields']['field_rfi_last_name']['id'] = 'field_rfi_last_name';
  $handler->display->display_options['fields']['field_rfi_last_name']['table'] = 'field_data_field_rfi_last_name';
  $handler->display->display_options['fields']['field_rfi_last_name']['field'] = 'field_rfi_last_name';
  $handler->display->display_options['fields']['field_rfi_last_name']['element_label_colon'] = FALSE;
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_rfi_email']['id'] = 'field_rfi_email';
  $handler->display->display_options['fields']['field_rfi_email']['table'] = 'field_data_field_rfi_email';
  $handler->display->display_options['fields']['field_rfi_email']['field'] = 'field_rfi_email';
  $handler->display->display_options['fields']['field_rfi_email']['element_label_colon'] = FALSE;
  /* Field: Content: Phone */
  $handler->display->display_options['fields']['field_rfi_phone']['id'] = 'field_rfi_phone';
  $handler->display->display_options['fields']['field_rfi_phone']['table'] = 'field_data_field_rfi_phone';
  $handler->display->display_options['fields']['field_rfi_phone']['field'] = 'field_rfi_phone';
  $handler->display->display_options['fields']['field_rfi_phone']['element_label_colon'] = FALSE;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_rfi_address']['id'] = 'field_rfi_address';
  $handler->display->display_options['fields']['field_rfi_address']['table'] = 'field_data_field_rfi_address';
  $handler->display->display_options['fields']['field_rfi_address']['field'] = 'field_rfi_address';
  $handler->display->display_options['fields']['field_rfi_address']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_rfi_city']['id'] = 'field_rfi_city';
  $handler->display->display_options['fields']['field_rfi_city']['table'] = 'field_data_field_rfi_city';
  $handler->display->display_options['fields']['field_rfi_city']['field'] = 'field_rfi_city';
  $handler->display->display_options['fields']['field_rfi_city']['element_label_colon'] = FALSE;
  /* Field: Content: Country */
  $handler->display->display_options['fields']['field_rfi_country']['id'] = 'field_rfi_country';
  $handler->display->display_options['fields']['field_rfi_country']['table'] = 'field_data_field_rfi_country';
  $handler->display->display_options['fields']['field_rfi_country']['field'] = 'field_rfi_country';
  $handler->display->display_options['fields']['field_rfi_country']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_rfi_state']['id'] = 'field_rfi_state';
  $handler->display->display_options['fields']['field_rfi_state']['table'] = 'field_data_field_rfi_state';
  $handler->display->display_options['fields']['field_rfi_state']['field'] = 'field_rfi_state';
  $handler->display->display_options['fields']['field_rfi_state']['element_label_colon'] = FALSE;
  /* Field: Content: DOB */
  $handler->display->display_options['fields']['field_rfi_dob']['id'] = 'field_rfi_dob';
  $handler->display->display_options['fields']['field_rfi_dob']['table'] = 'field_data_field_rfi_dob';
  $handler->display->display_options['fields']['field_rfi_dob']['field'] = 'field_rfi_dob';
  /* Field: Content: Zipcode */
  $handler->display->display_options['fields']['field_rfi_zipcode']['id'] = 'field_rfi_zipcode';
  $handler->display->display_options['fields']['field_rfi_zipcode']['table'] = 'field_data_field_rfi_zipcode';
  $handler->display->display_options['fields']['field_rfi_zipcode']['field'] = 'field_rfi_zipcode';
  $handler->display->display_options['fields']['field_rfi_zipcode']['element_label_colon'] = FALSE;
  /* Field: Content: Student type */
  $handler->display->display_options['fields']['field_rfi_student_type']['id'] = 'field_rfi_student_type';
  $handler->display->display_options['fields']['field_rfi_student_type']['table'] = 'field_data_field_rfi_student_type';
  $handler->display->display_options['fields']['field_rfi_student_type']['field'] = 'field_rfi_student_type';
  $handler->display->display_options['fields']['field_rfi_student_type']['element_label_colon'] = FALSE;
  /* Field: Content: Veteran */
  $handler->display->display_options['fields']['field_rfi_veteran']['id'] = 'field_rfi_veteran';
  $handler->display->display_options['fields']['field_rfi_veteran']['table'] = 'field_data_field_rfi_veteran';
  $handler->display->display_options['fields']['field_rfi_veteran']['field'] = 'field_rfi_veteran';
  $handler->display->display_options['fields']['field_rfi_veteran']['element_label_colon'] = FALSE;
  /* Field: Content: Program */
  $handler->display->display_options['fields']['field_rfi_program']['id'] = 'field_rfi_program';
  $handler->display->display_options['fields']['field_rfi_program']['table'] = 'field_data_field_rfi_program';
  $handler->display->display_options['fields']['field_rfi_program']['field'] = 'field_rfi_program';
  $handler->display->display_options['fields']['field_rfi_program']['element_label_colon'] = FALSE;
  /* Field: Content: Program name */
  $handler->display->display_options['fields']['field_rfi_program_name']['id'] = 'field_rfi_program_name';
  $handler->display->display_options['fields']['field_rfi_program_name']['table'] = 'field_data_field_rfi_program_name';
  $handler->display->display_options['fields']['field_rfi_program_name']['field'] = 'field_rfi_program_name';
  $handler->display->display_options['fields']['field_rfi_program_name']['element_label_colon'] = FALSE;
  /* Field: Content: Start term */
  $handler->display->display_options['fields']['field_rfi_start_term']['id'] = 'field_rfi_start_term';
  $handler->display->display_options['fields']['field_rfi_start_term']['table'] = 'field_data_field_rfi_start_term';
  $handler->display->display_options['fields']['field_rfi_start_term']['field'] = 'field_rfi_start_term';
  $handler->display->display_options['fields']['field_rfi_start_term']['element_label_colon'] = FALSE;
  /* Field: Content: Error message from MW */
  $handler->display->display_options['fields']['field_rfi_error_message']['id'] = 'field_rfi_error_message';
  $handler->display->display_options['fields']['field_rfi_error_message']['table'] = 'field_data_field_rfi_error_message';
  $handler->display->display_options['fields']['field_rfi_error_message']['field'] = 'field_rfi_error_message';
  $handler->display->display_options['fields']['field_rfi_error_message']['element_label_colon'] = FALSE;
  /* Field: Content: Form name */
  $handler->display->display_options['fields']['field_rfi_form_name']['id'] = 'field_rfi_form_name';
  $handler->display->display_options['fields']['field_rfi_form_name']['table'] = 'field_data_field_rfi_form_name';
  $handler->display->display_options['fields']['field_rfi_form_name']['field'] = 'field_rfi_form_name';
  $handler->display->display_options['fields']['field_rfi_form_name']['element_label_colon'] = FALSE;
  /* Field: Content: Form type */
  $handler->display->display_options['fields']['field_rfi_form_type']['id'] = 'field_rfi_form_type';
  $handler->display->display_options['fields']['field_rfi_form_type']['table'] = 'field_data_field_rfi_form_type';
  $handler->display->display_options['fields']['field_rfi_form_type']['field'] = 'field_rfi_form_type';
  $handler->display->display_options['fields']['field_rfi_form_type']['element_label_colon'] = FALSE;
  /* Field: Content: International */
  $handler->display->display_options['fields']['field_rfi_international']['id'] = 'field_rfi_international';
  $handler->display->display_options['fields']['field_rfi_international']['table'] = 'field_data_field_rfi_international';
  $handler->display->display_options['fields']['field_rfi_international']['field'] = 'field_rfi_international';
  $handler->display->display_options['fields']['field_rfi_international']['element_label_colon'] = FALSE;
  /* Field: Content: Province */
  $handler->display->display_options['fields']['field_rfi_province']['id'] = 'field_rfi_province';
  $handler->display->display_options['fields']['field_rfi_province']['table'] = 'field_data_field_rfi_province';
  $handler->display->display_options['fields']['field_rfi_province']['field'] = 'field_rfi_province';
  $handler->display->display_options['fields']['field_rfi_province']['element_label_colon'] = FALSE;
  /* Field: Content: Question */
  $handler->display->display_options['fields']['field_rfi_question']['id'] = 'field_rfi_question';
  $handler->display->display_options['fields']['field_rfi_question']['table'] = 'field_data_field_rfi_question';
  $handler->display->display_options['fields']['field_rfi_question']['field'] = 'field_rfi_question';
  $handler->display->display_options['fields']['field_rfi_question']['element_label_colon'] = FALSE;
  /* Field: Content: Status of the submission */
  $handler->display->display_options['fields']['field_rfi_submission_status']['id'] = 'field_rfi_submission_status';
  $handler->display->display_options['fields']['field_rfi_submission_status']['table'] = 'field_data_field_rfi_submission_status';
  $handler->display->display_options['fields']['field_rfi_submission_status']['field'] = 'field_rfi_submission_status';
  $handler->display->display_options['fields']['field_rfi_submission_status']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'asu_rfi' => 'asu_rfi',
  );
  /* Filter criterion: Content: Status of the submission (field_rfi_submission_status) */
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['id'] = 'field_rfi_submission_status_value';
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['table'] = 'field_data_field_rfi_submission_status';
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['field'] = 'field_rfi_submission_status_value';
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['expose']['operator_id'] = 'field_rfi_submission_status_value_op';
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['expose']['label'] = 'Status of the form submissions';
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['expose']['operator'] = 'field_rfi_submission_status_value_op';
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['expose']['identifier'] = 'field_rfi_submission_status_value';
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Form type (field_rfi_form_type) */
  $handler->display->display_options['filters']['field_rfi_form_type_value']['id'] = 'field_rfi_form_type_value';
  $handler->display->display_options['filters']['field_rfi_form_type_value']['table'] = 'field_data_field_rfi_form_type';
  $handler->display->display_options['filters']['field_rfi_form_type_value']['field'] = 'field_rfi_form_type_value';
  $handler->display->display_options['filters']['field_rfi_form_type_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_rfi_form_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_rfi_form_type_value']['expose']['operator_id'] = 'field_rfi_form_type_value_op';
  $handler->display->display_options['filters']['field_rfi_form_type_value']['expose']['label'] = 'Form type';
  $handler->display->display_options['filters']['field_rfi_form_type_value']['expose']['operator'] = 'field_rfi_form_type_value_op';
  $handler->display->display_options['filters']['field_rfi_form_type_value']['expose']['identifier'] = 'field_rfi_form_type_value';
  $handler->display->display_options['filters']['field_rfi_form_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'asu-rfi-submissions-report';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['path'] = 'asu_rfi_download';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $export['asu_rfi_submissions_report'] = $view;

  return $export;
}
