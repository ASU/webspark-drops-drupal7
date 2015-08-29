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
  $handler->display->display_options['access']['perm'] = 'asu access lead export tool';
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
    'created' => 'created',
    'changed' => 'changed',
    'views_bulk_operations' => 'views_bulk_operations',
    'field_rfi_first_name' => 'field_rfi_first_name',
    'field_rfi_last_name' => 'field_rfi_last_name',
    'field_rfi_email' => 'field_rfi_email',
    'field_rfi_phone' => 'field_rfi_phone',
    'field_rfi_address' => 'field_rfi_address',
    'field_rfi_city' => 'field_rfi_city',
    'field_rfi_country' => 'field_rfi_country',
    'field_rfi_state' => 'field_rfi_state',
    'field_rfi_dob' => 'field_rfi_dob',
    'field_rfi_zipcode' => 'field_rfi_zipcode',
    'field_rfi_student_type' => 'field_rfi_student_type',
    'field_rfi_veteran' => 'field_rfi_veteran',
    'field_rfi_program' => 'field_rfi_program',
    'field_rfi_program_name' => 'field_rfi_program_name',
    'field_rfi_start_term' => 'field_rfi_start_term',
    'field_rfi_start_term_code' => 'field_rfi_start_term_code',
    'field_rfi_error_message' => 'field_rfi_error_message',
    'field_rfi_form_name' => 'field_rfi_form_name',
    'field_rfi_form_type' => 'field_rfi_form_type',
    'field_rfi_international' => 'field_rfi_international',
    'field_rfi_province' => 'field_rfi_province',
    'field_rfi_question' => 'field_rfi_question',
    'field_rfi_submission_status' => 'field_rfi_submission_status',
    'nid' => 'nid',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_address' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_city' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_country' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_state' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_dob' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_zipcode' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_student_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_veteran' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_program' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_program_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_start_term' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_start_term_code' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_error_message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_form_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_form_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_international' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_province' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_question' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_submission_status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p>0 Results Found</p>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
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
  /* Field: Content: Start term code */
  $handler->display->display_options['fields']['field_rfi_start_term_code']['id'] = 'field_rfi_start_term_code';
  $handler->display->display_options['fields']['field_rfi_start_term_code']['table'] = 'field_data_field_rfi_start_term_code';
  $handler->display->display_options['fields']['field_rfi_start_term_code']['field'] = 'field_rfi_start_term_code';
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
  /* Filter criterion: Content: Email (field_rfi_email) */
  $handler->display->display_options['filters']['field_rfi_email_value']['id'] = 'field_rfi_email_value';
  $handler->display->display_options['filters']['field_rfi_email_value']['table'] = 'field_data_field_rfi_email';
  $handler->display->display_options['filters']['field_rfi_email_value']['field'] = 'field_rfi_email_value';
  $handler->display->display_options['filters']['field_rfi_email_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_rfi_email_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['operator_id'] = 'field_rfi_email_value_op';
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['label'] = 'Search by student\'s email';
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['operator'] = 'field_rfi_email_value_op';
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['identifier'] = 'field_rfi_email_value';
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['autocomplete_field'] = 'field_rfi_email';
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Content: Last name (field_rfi_last_name) */
  $handler->display->display_options['filters']['field_rfi_last_name_value']['id'] = 'field_rfi_last_name_value';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['table'] = 'field_data_field_rfi_last_name';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['field'] = 'field_rfi_last_name_value';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['operator_id'] = 'field_rfi_last_name_value_op';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['label'] = 'Search by Last name';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['operator'] = 'field_rfi_last_name_value_op';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['identifier'] = 'field_rfi_last_name_value';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['autocomplete_field'] = 'field_rfi_last_name';
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['autocomplete_dependent'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h4>RFI Submissions Statuses:</h4>
<p><strong>Complete: </strong>Student completed the multi step form or the long form. Response from middleware has not been received.</p>

<p><strong>Incomplete:</strong> Student submitted just the first part of the multistep form. If the student doesn’t complete the second part of the form, it will be submitted to middleware/HTTP POST when cron runs in the site.</p>

<p><strong>SF_Complete:</strong> After a submission is posted to the middleware, middleware responds to the site with the status of the submission. If the submission went through successfully, the status of the submission changes to SF_Complete.</p>
 
<p><strong>Pending:</strong> If any error occurs with the submission to the middleware, the submission status changes to Pending.</p>

<p><strong>Action required:</strong> If any error occurs after trying to submit to the middleware, the submission status will change to "Action required" and the site administrators should correct the submission and post it back to middleware using Bulk operation below.</p>
';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::panelizer_set_status_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::asu_rfi_bulk_submit_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Submitted date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'long';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Status of the submission */
  $handler->display->display_options['fields']['field_rfi_submission_status']['id'] = 'field_rfi_submission_status';
  $handler->display->display_options['fields']['field_rfi_submission_status']['table'] = 'field_data_field_rfi_submission_status';
  $handler->display->display_options['fields']['field_rfi_submission_status']['field'] = 'field_rfi_submission_status';
  $handler->display->display_options['fields']['field_rfi_submission_status']['element_label_colon'] = FALSE;
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
  /* Field: Content: Start term code */
  $handler->display->display_options['fields']['field_rfi_start_term_code']['id'] = 'field_rfi_start_term_code';
  $handler->display->display_options['fields']['field_rfi_start_term_code']['table'] = 'field_data_field_rfi_start_term_code';
  $handler->display->display_options['fields']['field_rfi_start_term_code']['field'] = 'field_rfi_start_term_code';
  /* Field: Content: Error message from MW */
  $handler->display->display_options['fields']['field_rfi_error_message']['id'] = 'field_rfi_error_message';
  $handler->display->display_options['fields']['field_rfi_error_message']['table'] = 'field_data_field_rfi_error_message';
  $handler->display->display_options['fields']['field_rfi_error_message']['field'] = 'field_rfi_error_message';
  $handler->display->display_options['fields']['field_rfi_error_message']['label'] = 'Message from MW/SF';
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
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'admin/reports/asu-rfi-submissions-report';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'RFI lead submissions';
  $handler->display->display_options['menu']['description'] = 'RFI lead submissions report, with option to export to CSV or run operations on leads to resubmit to middleware.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

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
  $handler->display->display_options['path'] = 'admin/reports/asu_rfi_download';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '100';
  $export['asu_rfi_submissions_report'] = $view;

  return $export;
}
