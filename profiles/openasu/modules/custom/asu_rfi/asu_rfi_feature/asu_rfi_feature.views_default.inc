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
  $view->description = 'Listing of RFI submissions sitting in various queueing statuses in this site (on their way to Salesforce).';
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
    'views_bulk_operations' => 'views_bulk_operations',
    'created' => 'created',
    'changed' => 'changed',
    'field_rfi_submission_status' => 'field_rfi_submission_status',
    'field_rfi_first_name' => 'field_rfi_first_name',
    'field_rfi_last_name' => 'field_rfi_last_name',
    'field_rfi_email' => 'field_rfi_email',
    'field_rfi_phone' => 'field_rfi_phone',
    'field_rfi_campus' => 'field_rfi_campus',
    'field_rfi_location' => 'field_rfi_location',
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
    'field_rfi_error_message' => 'field_rfi_error_message',
    'field_rfi_form_name' => 'field_rfi_form_name',
    'field_rfi_form_type' => 'field_rfi_form_type',
    'field_rfi_international' => 'field_rfi_international',
    'field_rfi_province' => 'field_rfi_province',
    'field_rfi_question' => 'field_rfi_question',
    'nid' => 'nid',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['class'] = '';
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
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
    'field_rfi_submission_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_email' => array(
      'sortable' => 1,
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
    'field_rfi_campus' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_location' => array(
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
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_country' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_state' => array(
      'sortable' => 1,
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
      'sortable' => 1,
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
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_program' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_program_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_start_term' => array(
      'sortable' => 1,
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
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rfi_international' => array(
      'sortable' => 1,
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
      'empty_column' => 1,
    ),
    'field_rfi_question' => array(
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
  /* Field: Content: Domain */
  $handler->display->display_options['fields']['field_rfi_domain']['id'] = 'field_rfi_domain';
  $handler->display->display_options['fields']['field_rfi_domain']['table'] = 'field_data_field_rfi_domain';
  $handler->display->display_options['fields']['field_rfi_domain']['field'] = 'field_rfi_domain';
  $handler->display->display_options['fields']['field_rfi_domain']['element_label_colon'] = FALSE;
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
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_rfi_campus']['id'] = 'field_rfi_campus';
  $handler->display->display_options['fields']['field_rfi_campus']['table'] = 'field_data_field_rfi_campus';
  $handler->display->display_options['fields']['field_rfi_campus']['field'] = 'field_rfi_campus';
  $handler->display->display_options['fields']['field_rfi_campus']['element_label_colon'] = FALSE;
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_rfi_location']['id'] = 'field_rfi_location';
  $handler->display->display_options['fields']['field_rfi_location']['table'] = 'field_data_field_rfi_location';
  $handler->display->display_options['fields']['field_rfi_location']['field'] = 'field_rfi_location';
  $handler->display->display_options['fields']['field_rfi_location']['element_label_colon'] = FALSE;
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
  $handler->display->display_options['filters']['field_rfi_submission_status_value']['expose']['label'] = 'Status';
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
  $handler->display->display_options['filters']['field_rfi_email_value']['expose']['label'] = 'Email';
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
  $handler->display->display_options['filters']['field_rfi_last_name_value']['expose']['label'] = 'Last name';
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
  /* Header: Global: Result summary with an additional token to change the items/page */
  $handler->display->display_options['header']['webform_result']['id'] = 'webform_result';
  $handler->display->display_options['header']['webform_result']['table'] = 'views';
  $handler->display->display_options['header']['webform_result']['field'] = 'webform_result';
  $handler->display->display_options['header']['webform_result']['content'] = 'Displaying @start - @end of @total submissions. @items_per_page_links';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::asu_rfi_bulk_submit_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::asu_rfi_bulk_delete_submissions_action' => array(
      'selected' => 1,
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
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  $handler->display->display_options['fields']['created']['date_ap_style_output'] = array(
    'use_year' => 0,
    'show_time' => 0,
    'use_dow' => 0,
  );
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last updated (here)';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'panopoly_time';
  $handler->display->display_options['fields']['changed']['date_ap_style_output'] = array(
    'use_year' => 0,
    'show_time' => 0,
    'use_dow' => 0,
  );
  /* Field: Content: Status of the submission */
  $handler->display->display_options['fields']['field_rfi_submission_status']['id'] = 'field_rfi_submission_status';
  $handler->display->display_options['fields']['field_rfi_submission_status']['table'] = 'field_data_field_rfi_submission_status';
  $handler->display->display_options['fields']['field_rfi_submission_status']['field'] = 'field_rfi_submission_status';
  $handler->display->display_options['fields']['field_rfi_submission_status']['label'] = 'Status';
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
  /* Field: Content: Form type */
  $handler->display->display_options['fields']['field_rfi_form_type']['id'] = 'field_rfi_form_type';
  $handler->display->display_options['fields']['field_rfi_form_type']['table'] = 'field_data_field_rfi_form_type';
  $handler->display->display_options['fields']['field_rfi_form_type']['field'] = 'field_rfi_form_type';
  $handler->display->display_options['fields']['field_rfi_form_type']['element_label_colon'] = FALSE;
  /* Field: Content: Error message from MW */
  $handler->display->display_options['fields']['field_rfi_error_message']['id'] = 'field_rfi_error_message';
  $handler->display->display_options['fields']['field_rfi_error_message']['table'] = 'field_data_field_rfi_error_message';
  $handler->display->display_options['fields']['field_rfi_error_message']['field'] = 'field_rfi_error_message';
  $handler->display->display_options['fields']['field_rfi_error_message']['label'] = 'Middleware response';
  $handler->display->display_options['fields']['field_rfi_error_message']['element_label_colon'] = FALSE;
  /* Field: Content: Link to content */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  /* Field: Content: Link to delete content */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  /* Field: Content: Link to edit content */
  $handler->display->display_options['fields']['edit_node_1']['id'] = 'edit_node_1';
  $handler->display->display_options['fields']['edit_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node_1']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node_1']['label'] = '';
  $handler->display->display_options['fields']['edit_node_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['edit_node_1']['element_label_colon'] = FALSE;
  /* Field: Global: Contextual Links */
  $handler->display->display_options['fields']['contextual_links']['id'] = 'contextual_links';
  $handler->display->display_options['fields']['contextual_links']['table'] = 'views';
  $handler->display->display_options['fields']['contextual_links']['field'] = 'contextual_links';
  $handler->display->display_options['fields']['contextual_links']['label'] = 'More Submission Actions';
  $handler->display->display_options['fields']['contextual_links']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['contextual_links']['alter']['text'] = '<div class="asu-rfi-contextual-links-container">[contextual_links]</div>';
  $handler->display->display_options['fields']['contextual_links']['fields'] = array(
    'view_node' => 'view_node',
    'delete_node' => 'delete_node',
    'edit_node_1' => 'edit_node_1',
  );
  $handler->display->display_options['fields']['contextual_links']['check_access'] = 0;
  /* Field: Content: Student type */
  $handler->display->display_options['fields']['field_rfi_student_type']['id'] = 'field_rfi_student_type';
  $handler->display->display_options['fields']['field_rfi_student_type']['table'] = 'field_data_field_rfi_student_type';
  $handler->display->display_options['fields']['field_rfi_student_type']['field'] = 'field_rfi_student_type';
  $handler->display->display_options['fields']['field_rfi_student_type']['element_label_colon'] = FALSE;
  /* Field: Content: Start term */
  $handler->display->display_options['fields']['field_rfi_start_term']['id'] = 'field_rfi_start_term';
  $handler->display->display_options['fields']['field_rfi_start_term']['table'] = 'field_data_field_rfi_start_term';
  $handler->display->display_options['fields']['field_rfi_start_term']['field'] = 'field_rfi_start_term';
  $handler->display->display_options['fields']['field_rfi_start_term']['element_label_colon'] = FALSE;
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
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_rfi_location']['id'] = 'field_rfi_location';
  $handler->display->display_options['fields']['field_rfi_location']['table'] = 'field_data_field_rfi_location';
  $handler->display->display_options['fields']['field_rfi_location']['field'] = 'field_rfi_location';
  $handler->display->display_options['fields']['field_rfi_location']['label'] = 'Location preference';
  $handler->display->display_options['fields']['field_rfi_location']['element_label_colon'] = FALSE;
  /* Field: Content: Campus */
  $handler->display->display_options['fields']['field_rfi_campus']['id'] = 'field_rfi_campus';
  $handler->display->display_options['fields']['field_rfi_campus']['table'] = 'field_data_field_rfi_campus';
  $handler->display->display_options['fields']['field_rfi_campus']['field'] = 'field_rfi_campus';
  $handler->display->display_options['fields']['field_rfi_campus']['element_label_colon'] = FALSE;
  /* Field: Content: Question */
  $handler->display->display_options['fields']['field_rfi_question']['id'] = 'field_rfi_question';
  $handler->display->display_options['fields']['field_rfi_question']['table'] = 'field_data_field_rfi_question';
  $handler->display->display_options['fields']['field_rfi_question']['field'] = 'field_rfi_question';
  $handler->display->display_options['fields']['field_rfi_question']['label'] = 'Additional question/comment';
  $handler->display->display_options['fields']['field_rfi_question']['element_label_colon'] = FALSE;
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
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_rfi_state']['id'] = 'field_rfi_state';
  $handler->display->display_options['fields']['field_rfi_state']['table'] = 'field_data_field_rfi_state';
  $handler->display->display_options['fields']['field_rfi_state']['field'] = 'field_rfi_state';
  $handler->display->display_options['fields']['field_rfi_state']['element_label_colon'] = FALSE;
  /* Field: Content: Province */
  $handler->display->display_options['fields']['field_rfi_province']['id'] = 'field_rfi_province';
  $handler->display->display_options['fields']['field_rfi_province']['table'] = 'field_data_field_rfi_province';
  $handler->display->display_options['fields']['field_rfi_province']['field'] = 'field_rfi_province';
  $handler->display->display_options['fields']['field_rfi_province']['element_label_colon'] = FALSE;
  /* Field: Content: Zipcode */
  $handler->display->display_options['fields']['field_rfi_zipcode']['id'] = 'field_rfi_zipcode';
  $handler->display->display_options['fields']['field_rfi_zipcode']['table'] = 'field_data_field_rfi_zipcode';
  $handler->display->display_options['fields']['field_rfi_zipcode']['field'] = 'field_rfi_zipcode';
  $handler->display->display_options['fields']['field_rfi_zipcode']['element_label_colon'] = FALSE;
  /* Field: Content: Country */
  $handler->display->display_options['fields']['field_rfi_country']['id'] = 'field_rfi_country';
  $handler->display->display_options['fields']['field_rfi_country']['table'] = 'field_data_field_rfi_country';
  $handler->display->display_options['fields']['field_rfi_country']['field'] = 'field_rfi_country';
  $handler->display->display_options['fields']['field_rfi_country']['element_label_colon'] = FALSE;
  /* Field: Content: DOB */
  $handler->display->display_options['fields']['field_rfi_dob']['id'] = 'field_rfi_dob';
  $handler->display->display_options['fields']['field_rfi_dob']['table'] = 'field_data_field_rfi_dob';
  $handler->display->display_options['fields']['field_rfi_dob']['field'] = 'field_rfi_dob';
  /* Field: Content: Veteran */
  $handler->display->display_options['fields']['field_rfi_veteran']['id'] = 'field_rfi_veteran';
  $handler->display->display_options['fields']['field_rfi_veteran']['table'] = 'field_data_field_rfi_veteran';
  $handler->display->display_options['fields']['field_rfi_veteran']['field'] = 'field_rfi_veteran';
  $handler->display->display_options['fields']['field_rfi_veteran']['element_label_colon'] = FALSE;
  /* Field: Content: International */
  $handler->display->display_options['fields']['field_rfi_international']['id'] = 'field_rfi_international';
  $handler->display->display_options['fields']['field_rfi_international']['table'] = 'field_data_field_rfi_international';
  $handler->display->display_options['fields']['field_rfi_international']['field'] = 'field_rfi_international';
  $handler->display->display_options['fields']['field_rfi_international']['element_label_colon'] = FALSE;
  /* Field: Content: Form name */
  $handler->display->display_options['fields']['field_rfi_form_name']['id'] = 'field_rfi_form_name';
  $handler->display->display_options['fields']['field_rfi_form_name']['table'] = 'field_data_field_rfi_form_name';
  $handler->display->display_options['fields']['field_rfi_form_name']['field'] = 'field_rfi_form_name';
  $handler->display->display_options['fields']['field_rfi_form_name']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
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

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area_1']['id'] = 'area_1';
  $handler->display->display_options['header']['area_1']['table'] = 'views';
  $handler->display->display_options['header']['area_1']['field'] = 'area';
  $handler->display->display_options['header']['area_1']['empty'] = TRUE;
  $handler->display->display_options['header']['area_1']['content'] = '<style type="text/css">
.view-asu-rfi-submissions-report table td { vertical-align: text-top; }
.view-asu-rfi-submissions-report .views-field-field-rfi-error-message, .view-asu-rfi-submissions-report .views-field-field-rfi-question { min-width: 16em;}
.view-asu-rfi-submissions-report .views-field-field-rfi-submission-status { min-width: 8em;}
.view-asu-rfi-submissions-report .attachment .questions,
.view-asu-rfi-submissions-report .view-header legend {
  font-weight: 300;
}
.view-asu-rfi-submissions-report .view-header {
  border: 1px solid #ddd;
  padding: 1em;
  background-color: #f7f7f7;
  margin-bottom: 1em;
}
.view-asu-rfi-submissions-report .attachment .view-header {
  padding: 0 1em;
}
.view-asu-rfi-submissions-report .view-header fieldset {
  background-color: #fff;
  text-transform: none !important;
  margin-bottom: 1em;
  padding-top: 0;
}
.view-asu-rfi-submissions-report .attachment fieldset.collapsible .fieldset-legend {
  position: relative;
}
.view-asu-rfi-submissions-report .view-header .questions {
  background: url(/misc/menu-expanded.png) 5px 65% no-repeat;
  padding-left: 1em;
}
.view-asu-rfi-submissions-report .view-header .questions.questions-collapsed {
  background-image: url(/misc/menu-collapsed.png);
  background-position: 5px 50%;
}
.view-asu-rfi-submissions-report .asu-rfi-contextual-links-container {
  position: relative;
}
</style>';
  $handler->display->display_options['header']['area_1']['format'] = 'full_html';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<h4 class="questions"><a href="/admin/reports/asu-rfi-submissions-report">Commonly asked RFI submission questions...</a></h4>
<div class="questions-container">
<fieldset class="collapsible collapsed field-group-fieldset form-wrapper fieldset-nested-even asu-rfi-intro collapse-processed"><style type="text/css">.view-asu-rfi-submissions-report table td { vertical-align: text-top; } .view-asu-rfi-submissions-report .views-field-field-rfi-error-message, .view-asu-rfi-submissions-report .views-field-field-rfi-question { min-width: 16em;}</style><legend><span class="fieldset-legend"><a class="fieldset-title" href="#"><span class="fieldset-legend-prefix element-invisible">Show</span>Q: What does the submission status tell me?</a></span></legend><div class="fieldset-wrapper">
<p>Submission statuses show where the submissions are in the process of getting the form submission from your site on their way to Salesforce (SF) via a "middleware" server that will do the rest of the work for your site. They can also tell you what action (if any) needs to be taken if there is a problem.</p>
<ul><li><strong>Ready for SF POST</strong> - A prospective/current student has successfully submitted either the single page "long" form OR the LAST page of a multistep form, but for some reason it hasn\'t been submitted to the SF middleware yet. (NOTE: You won\'t normally see this status because the data is automatically submitted to the SF middleware when the form is submitted by the end user.)</li><li><strong>Partial multiform submitted</strong> <em>(Multi-page form submissions ONLY)</em> - A prospective student has only submitted the first half of a multistep RFI form and either hasn\'t finished yet or has chosen to not complete the second half. The next cron job (an automated website process that <a href="/admin/config/system/cron">runs at periodic intervals</a>) will submit the data to the SF middleware (or you can submit it manually here).</li><li><strong>SF POST Multiform Pending</strong> <em>(Multi-page forms ONLY)</em> - Multiform submissions that have been submitted once and failed, or were not completed by the end user and the cron job changed its status from "Partial multiform submitted" - making it eligible to be submitted by a future cron job. It is waiting to be submitted to SF middleware. Similar to "Ready for SF POST".</li><li><strong>SF POST Successful</strong> - DONE. A submission has successfully posted to the middleware. No further action is required.</li><li><strong>SF POST Failed</strong> - An error occurred while trying to submit to the middleware. The site administrators need to first check the "Middleware response" field for possible explanations. Also check the submission\'s data for issues (bad characters, missing data, etc.), and if possible correct any errors found and resubmit it by either <a href="/admin/reports/status/run-cron">running cron</a> or using the "OPERATIONS" list to resubmit. <br />NOTE: If the errors are not rectified, after its expiration date (currently set at 14 days after it was submitted), this submission will be deleted automatically by a future cron job. (Submissions can also be manually deleted here, if desired.)</li><li><strong>Completed (No Salesforce)</strong> <em>(Current student forms ONLY)</em> - The submission has been received, and no Salesforce processing will occur. DONE. <br />IMPORTANT: This data should be deleted ASAP (see, "Can I store RFI form submission data on my site after it has been submitted to Salesforce?", below.)</li></ul></div></fieldset>
<fieldset class="collapsible collapsed field-group-fieldset form-wrapper fieldset-nested-even asu-rfi-intro collapse-processed"><style type="text/css">.view-asu-rfi-submissions-report table td { vertical-align: text-top; } .view-asu-rfi-submissions-report .views-field-field-rfi-error-message, .view-asu-rfi-submissions-report .views-field-field-rfi-question { min-width: 16em;}</style><legend><span class="fieldset-legend"><a class="fieldset-title" href="#"><span class="fieldset-legend-prefix element-invisible">Show</span>Q: Can I store RFI form submission data on my site after it has been submitted to Salesforce?</a></span></legend><div class="fieldset-wrapper">
<p>No. It must be deleted after it has been submitted onto the SF middleware and into Salesforce itself.</p>
<p>Storing personally identifiable information (PII) that has been submitted by end users in your site violates ASU and UTO policies regarding PII data storage and data security.</p>
</div></fieldset>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: First name */
  $handler->display->display_options['fields']['field_rfi_first_name']['id'] = 'field_rfi_first_name';
  $handler->display->display_options['fields']['field_rfi_first_name']['table'] = 'field_data_field_rfi_first_name';
  $handler->display->display_options['fields']['field_rfi_first_name']['field'] = 'field_rfi_first_name';
  $handler->display->display_options['fields']['field_rfi_first_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: First name (field_rfi_first_name) */
  $handler->display->display_options['filters']['field_rfi_first_name_value']['id'] = 'field_rfi_first_name_value';
  $handler->display->display_options['filters']['field_rfi_first_name_value']['table'] = 'field_data_field_rfi_first_name';
  $handler->display->display_options['filters']['field_rfi_first_name_value']['field'] = 'field_rfi_first_name_value';
  $handler->display->display_options['filters']['field_rfi_first_name_value']['value'] = 'Mytzlflick';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_arguments'] = FALSE;
  $translatables['asu_rfi_submissions_report'] = array(
    t('Master'),
    t('ASU RFI submissions report'),
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
    t('<p>0 Results Found</p>'),
    t('First name'),
    t('Last name'),
    t('Email'),
    t('Domain'),
    t('Phone'),
    t('Address'),
    t('City'),
    t('Country'),
    t('State'),
    t('DOB'),
    t('Zipcode'),
    t('Student type'),
    t('Veteran'),
    t('Program'),
    t('Program name'),
    t('Start term'),
    t('Start term code'),
    t('Error message from MW'),
    t('Form name'),
    t('Form type'),
    t('International'),
    t('Province'),
    t('Question'),
    t('Status of the submission'),
    t('Campus'),
    t('Location'),
    t('Status'),
    t('Page'),
    t('Displaying @start - @end of @total submissions. @items_per_page_links'),
    t('Content'),
    t('- Choose an operation -'),
    t('Submitted date'),
    t('Last updated (here)'),
    t('Middleware response'),
    t('More Submission Actions'),
    t('<div class="asu-rfi-contextual-links-container">[contextual_links]</div>'),
    t('Location preference'),
    t('Additional question/comment'),
    t('Data export'),
    t('Attachment'),
    t('<style type="text/css">
.view-asu-rfi-submissions-report table td { vertical-align: text-top; }
.view-asu-rfi-submissions-report .views-field-field-rfi-error-message, .view-asu-rfi-submissions-report .views-field-field-rfi-question { min-width: 16em;}
.view-asu-rfi-submissions-report .attachment .questions,
.view-asu-rfi-submissions-report .view-header legend {
  font-weight: 300;
}
.view-asu-rfi-submissions-report .view-header {
  border: 1px solid #ddd;
  padding: 1em;
  background-color: #f7f7f7;
  margin-bottom: 1em;
}
.view-asu-rfi-submissions-report .attachment .view-header {
  padding: 0 1em;
}
.view-asu-rfi-submissions-report .view-header fieldset {
  background-color: #fff;
  text-transform: none !important;
  margin-bottom: 1em;
}
.view-asu-rfi-submissions-report .view-header .questions {
  background: url(/misc/menu-expanded.png) 5px 65% no-repeat;
  padding-left: 1em;
}
.view-asu-rfi-submissions-report .view-header .questions.questions-collapsed {
  background-image: url(/misc/menu-collapsed.png);
  background-position: 5px 50%;
}
.view-asu-rfi-submissions-report .asu-rfi-contextual-links-container {
  position: relative;
}
</style>'),
    t('<h4 class="questions"><a href="/admin/reports/asu-rfi-submissions-report">Commonly asked RFI submission questions...</a></h4>
<div class="questions-container">
<fieldset class="collapsible collapsed field-group-fieldset form-wrapper fieldset-nested-even asu-rfi-intro collapse-processed"><style type="text/css">.view-asu-rfi-submissions-report table td { vertical-align: text-top; } .view-asu-rfi-submissions-report .views-field-field-rfi-error-message, .view-asu-rfi-submissions-report .views-field-field-rfi-question { min-width: 16em;}</style><legend><span class="fieldset-legend"><a class="fieldset-title" href="#"><span class="fieldset-legend-prefix element-invisible">Show</span>Q: What does the submission status tell me?</a></span></legend><div class="fieldset-wrapper">
<p>Submission statuses show where the submissions are in the process of getting the form submission from your site on their way to Salesforce (SF) via a "middleware" server that will do the rest of the work for your site. They can also tell you what action (if any) needs to be taken if there is a problem.</p>
<ul><li><strong>Ready for SF POST</strong> - A prospective/current student has successfully submitted either the single page "long" form OR the LAST page of a multistep form, but for some reason it hasn\'t been submitted to the SF middleware yet. (NOTE: You won\'t normally see this status because the data is automatically submitted to the SF middleware when the form is submitted by the end user.)</li><li><strong>Partial multiform submitted</strong> <em>(Multi-page form submissions ONLY)</em> - A prospective student has only submitted the first half of a multistep RFI form and either hasn\'t finished yet or has chosen to not complete the second half. The next cron job (an automated website process that <a href="/admin/config/system/cron">runs at periodic intervals</a>) will submit the data to the SF middleware (or you can submit it manually here).</li><li><strong>SF POST Multiform Pending</strong> <em>(Multi-page forms ONLY)</em> - Multiform submissions that have been submitted once and failed, or were not completed by the end user and the cron job changed its status from "Partial multiform submitted" - making it eligible to be submitted by a future cron job. It is waiting to be submitted to SF middleware. Similar to "Ready for SF POST".</li><li><strong>SF POST Successful</strong> - DONE. A submission has successfully posted to the middleware. No further action is required.</li><li><strong>SF POST Failed</strong> - An error occurred while trying to submit to the middleware. The site administrators need to first check the "Middleware response" field for possible explanations. Also check the submission\'s data for issues (bad characters, missing data, etc.), and if possible correct any errors found and resubmit it by either <a href="/admin/reports/status/run-cron">running cron</a> or using the "OPERATIONS" list to resubmit. <br />NOTE: If the errors are not rectified, after its expiration date (currently set at 14 days after it was submitted), this submission will be deleted automatically by a future cron job. (Submissions can also be manually deleted here, if desired.)</li><li><strong>Completed (No Salesforce)</strong> <em>(Current student forms ONLY)</em> - The submission has been received, and no Salesforce processing will occur. DONE. <br />IMPORTANT: This data should be deleted ASAP (see, "Can I store RFI form submission data on my site after it has been submitted to Salesforce?", below.)</li></ul></div></fieldset>
<fieldset class="collapsible collapsed field-group-fieldset form-wrapper fieldset-nested-even asu-rfi-intro collapse-processed"><style type="text/css">.view-asu-rfi-submissions-report table td { vertical-align: text-top; } .view-asu-rfi-submissions-report .views-field-field-rfi-error-message, .view-asu-rfi-submissions-report .views-field-field-rfi-question { min-width: 16em;}</style><legend><span class="fieldset-legend"><a class="fieldset-title" href="#"><span class="fieldset-legend-prefix element-invisible">Show</span>Q: Can I store RFI form submission data on my site after it has been submitted to Salesforce?</a></span></legend><div class="fieldset-wrapper">
<p>No. It must be deleted after it has been submitted onto the SF middleware and into Salesforce itself.</p>
<p>Storing personally identifiable information (PII) that has been submitted by end users in your site violates ASU and UTO policies regarding PII data storage and data security.</p>
</div></fieldset>
</div>'),
  );
  $export['asu_rfi_submissions_report'] = $view;

  return $export;
}
