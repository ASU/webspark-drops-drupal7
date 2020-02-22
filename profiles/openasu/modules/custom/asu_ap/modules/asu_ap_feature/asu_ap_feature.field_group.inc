<?php

/**
 * @file
 * asu_ap_feature.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function asu_ap_feature_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_asu_ap_grp_banner|node|asu_ap|form';
  $field_group->group_name = 'group_asu_ap_grp_banner';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_ap';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Banner & Program Flags',
    'weight' => '2',
    'children' => array(
      0 => 'field_asu_ap_acc_program',
      1 => 'field_asu_ap_conc_program',
      2 => 'field_asu_ap_new_program',
      3 => 'field_asu_banner_image',
      4 => 'field_degree_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Banner & Program Flags',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-asu-ap-grp-banner field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_asu_ap_grp_banner|node|asu_ap|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_asu_ap_grp_career|node|asu_ap|form';
  $field_group->group_name = 'group_asu_ap_grp_career';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_ap';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Career Display',
    'weight' => '7',
    'children' => array(
      0 => 'field_asu_ap_career_outlook',
      1 => 'field_asu_ap_ex_car_tf',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Career Display',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-asu-ap-grp-career field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_asu_ap_grp_career|node|asu_ap|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_asu_ap_grp_desc|node|asu_ap|form';
  $field_group->group_name = 'group_asu_ap_grp_desc';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_ap';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Program Description & Call to Action Buttons',
    'weight' => '3',
    'children' => array(
      0 => 'field_asu_ap_cta_apply',
      1 => 'field_asu_ap_cta_information',
      2 => 'field_asu_ap_cta_visit',
      3 => 'field_asu_ap_short_desc',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Program Description & Call to Action Buttons',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-asu-ap-grp-desc field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_asu_ap_grp_desc|node|asu_ap|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_asu_ap_grp_grad|node|asu_ap|form';
  $field_group->group_name = 'group_asu_ap_grp_grad';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_ap';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Custom Graduate Markup',
    'weight' => '5',
    'children' => array(
      0 => 'field_asu_ap_grad_app',
      1 => 'field_asu_ap_grad_desc_video',
      2 => 'field_asu_ap_grad_financing',
      3 => 'field_asu_ap_grad_text_area',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Custom Graduate Markup',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-asu-ap-grp-grad field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_asu_ap_grp_grad|node|asu_ap|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_asu_ap_grp_hidden|node|asu_ap|form';
  $field_group->group_name = 'group_asu_ap_grp_hidden';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_ap';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Hidden',
    'weight' => '8',
    'children' => array(
      0 => 'body',
      1 => 'field_asu_ap',
      2 => 'field_asu_ap_acad_plan',
      3 => 'field_asu_ap_acad_prog',
      4 => 'field_asu_ap_admission_req',
      5 => 'field_asu_ap_asuds_url',
      6 => 'field_asu_ap_awarded',
      7 => 'field_asu_ap_campus',
      8 => 'field_asu_ap_career_opps',
      9 => 'field_asu_ap_cert',
      10 => 'field_asu_ap_college',
      11 => 'field_asu_ap_college_j',
      12 => 'field_asu_ap_college_url',
      13 => 'field_asu_ap_college_url_j',
      14 => 'field_asu_ap_department',
      15 => 'field_asu_ap_department_code',
      16 => 'field_asu_ap_department_code_j',
      17 => 'field_asu_ap_department_j',
      18 => 'field_asu_ap_diploma_desc',
      19 => 'field_asu_ap_example_careers',
      20 => 'field_asu_ap_major_map_url',
      21 => 'field_asu_ap_major_map_year',
      22 => 'field_asu_ap_min_math',
      23 => 'field_asu_ap_prog_req',
      24 => 'field_asu_ap_program',
      25 => 'field_asu_ap_program_fee',
      26 => 'field_asu_ap_req_desc',
      27 => 'field_asu_ap_second_language',
      28 => 'field_asu_ap_subplan_title',
      29 => 'field_asu_ap_subplan_url',
      30 => 'field_asu_ap_curriculum_url',
      31 => 'field_asu_ap_grad_all_app_dates',
      32 => 'field_asu_ap_url_1',
      33 => 'field_asu_ap_url_2',
      34 => 'field_asu_ap_url_3',
      35 => 'field_asu_ap_url_4',
      36 => 'field_asu_ap_market_text',
      37 => 'field_asu_ap_math_intensity',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Hidden',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-asu-ap-grp-hidden field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_asu_ap_grp_hidden|node|asu_ap|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_asu_ap_grp_links|node|asu_ap|form';
  $field_group->group_name = 'group_asu_ap_grp_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_ap';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Program Links, Requirements & Options',
    'weight' => '4',
    'children' => array(
      0 => 'field_asu_ap_addl_req',
      1 => 'field_asu_ap_sl',
      2 => 'field_asu_ap_wue_available',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Program Links, Requirements & Options',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-asu-ap-grp-links field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_asu_ap_grp_links|node|asu_ap|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_asu_ap_grp_prog|node|asu_ap|form';
  $field_group->group_name = 'group_asu_ap_grp_prog';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_ap';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Related Programs',
    'weight' => '6',
    'children' => array(
      0 => 'field_asu_ap_related_programs',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Related Programs',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-asu-ap-grp-prog field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_asu_ap_grp_prog|node|asu_ap|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Banner & Program Flags');
  t('Career Display');
  t('Custom Graduate Markup');
  t('Hidden');
  t('Program Description & Call to Action Buttons');
  t('Program Links, Requirements & Options');
  t('Related Programs');

  return $field_groups;
}
