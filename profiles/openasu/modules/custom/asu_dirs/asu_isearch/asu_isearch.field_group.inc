<?php
/**
 * @file
 * asu_isearch.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function asu_isearch_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_advanced|node|asu_isearch_profile|form';
  $field_group->group_name = 'group_advanced';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Advanced',
    'weight' => '11',
    'children' => array(
      0 => 'field_isearch_hash',
      1 => 'field_isearch_local_tags',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-advanced field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_advanced|node|asu_isearch_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic|node|asu_isearch_profile|form';
  $field_group->group_name = 'group_basic';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Basic',
    'weight' => '2',
    'children' => array(
      0 => 'field_isearch_affiliations',
      1 => 'field_isearch_asurite_id',
      2 => 'field_isearch_campus_building',
      3 => 'field_isearch_campus_room',
      4 => 'field_isearch_displayname',
      5 => 'field_isearch_eid',
      6 => 'field_isearch_email',
      7 => 'field_isearch_employee_type',
      8 => 'field_isearch_employment_title',
      9 => 'field_isearch_fax',
      10 => 'field_isearch_firstname',
      11 => 'field_isearch_lastname',
      12 => 'field_isearch_link_building_code',
      13 => 'field_isearch_local_photo_url',
      14 => 'field_isearch_local_primary_aff',
      15 => 'field_isearch_phone',
      16 => 'field_isearch_photo_permission',
      17 => 'field_isearch_photo_preference',
      18 => 'field_isearch_photo_url',
      19 => 'field_isearch_primary_aff',
      20 => 'field_isearch_primary_campus',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-basic field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_basic|node|asu_isearch_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_biography|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_biography';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Bio',
    'weight' => '18',
    'children' => array(
      0 => 'field_isearch_bio',
      1 => 'field_isearch_cv_url',
      2 => 'field_isearch_education',
      3 => 'field_isearch_fax',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Bio',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-biography field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_biography|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_biography|node|asu_isearch_profile|isearch_profile_full';
  $field_group->group_name = 'group_biography';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'isearch_profile_full';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Bio',
    'weight' => '41',
    'children' => array(
      0 => 'field_isearch_fax',
      1 => 'field_isearch_bio',
      2 => 'field_isearch_education',
      3 => 'field_isearch_cv_url',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-biography field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_biography|node|asu_isearch_profile|isearch_profile_full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details_left|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_details_left';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Left',
    'weight' => '18',
    'children' => array(
      0 => 'field_isearch_profile_tabs',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-details-left field-group-div col-md-8',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_details_left|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details_right|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_details_right';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Right',
    'weight' => '19',
    'children' => array(
      0 => 'field_isearch_expertise_areas',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-details-right field-group-div col-md-4',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_details_right|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '1',
    'children' => array(
      0 => 'group_details_left',
      1 => 'group_details_right',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-details field-group-div row',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_details|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_expertise_area|node|asu_isearch_profile|form';
  $field_group->group_name = 'group_expertise_area';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Expertise Area',
    'weight' => '4',
    'children' => array(
      0 => 'field_isearch_expertise_areas',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Expertise Area',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-expertise-area field-group-tab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_expertise_area|node|asu_isearch_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_industry_experience|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_industry_experience';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Industry Experience',
    'weight' => '22',
    'children' => array(
      0 => 'field_consulting',
      1 => 'field_board',
      2 => 'field_pro_bono',
      3 => 'field_industry_positions',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-industry-experience field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_industry_experience|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_links|node|asu_isearch_profile|form';
  $field_group->group_name = 'group_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '3',
    'children' => array(
      0 => 'field_isearch_social_facebook',
      1 => 'field_isearch_social_googleplus',
      2 => 'field_isearch_social_linkedin',
      3 => 'field_isearch_social_personalweb',
      4 => 'field_isearch_social_twitter',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-links field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_links|node|asu_isearch_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|asu_isearch_profile|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '9',
    'children' => array(
      0 => 'field_isearch_audio',
      1 => 'field_isearch_images',
      2 => 'field_isearch_videos',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-media field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_media|node|asu_isearch_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personal|node|asu_isearch_profile|form';
  $field_group->group_name = 'group_personal';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal',
    'weight' => '5',
    'children' => array(
      0 => 'field_isearch_bio',
      1 => 'field_isearch_cv_url',
      2 => 'field_isearch_education',
      3 => 'field_isearch_short_bio',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-personal field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_personal|node|asu_isearch_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_portrait_contact|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_portrait_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_portrait_section';
  $field_group->data = array(
    'label' => 'Contact',
    'weight' => '39',
    'children' => array(
      0 => 'field_isearch_campus_building',
      1 => 'field_isearch_email',
      2 => 'field_isearch_phone',
      3 => 'group_profile_social',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Contact',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-portrait-contact field-group-div col-sm-10',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_portrait_contact|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_portrait_image|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_portrait_image';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_portrait_section';
  $field_group->data = array(
    'label' => 'Image',
    'weight' => '38',
    'children' => array(
      0 => 'field_isearch_photo_url',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Image',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-portrait-image field-group-div col-sm-2',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_portrait_image|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_portrait_section|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_portrait_section';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Portrait Section',
    'weight' => '0',
    'children' => array(
      0 => 'group_portrait_contact',
      1 => 'group_portrait_image',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Portrait Section',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-portrait-section field-group-div row',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_portrait_section|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile_social|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_profile_social';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_portrait_contact';
  $field_group->data = array(
    'label' => 'Social',
    'weight' => '49',
    'children' => array(
      0 => 'field_isearch_social_facebook',
      1 => 'field_isearch_social_googleplus',
      2 => 'field_isearch_social_linkedin',
      3 => 'field_isearch_social_personalweb',
      4 => 'field_isearch_social_twitter',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Social',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-profile-social field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_profile_social|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_public_work|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_public_work';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Public Work',
    'weight' => '21',
    'children' => array(
      0 => 'field_isearch_editorships',
      1 => 'field_isearch_graduate_faculties',
      2 => 'field_isearch_honors_awards',
      3 => 'field_isearch_prof_associations',
      4 => 'field_isearch_service',
      5 => 'field_isearch_work_history',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-public-work field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_public_work|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_public_work|node|asu_isearch_profile|form';
  $field_group->group_name = 'group_public_work';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Public Work',
    'weight' => '8',
    'children' => array(
      0 => 'field_isearch_editorships',
      1 => 'field_isearch_graduate_faculties',
      2 => 'field_isearch_honors_awards',
      3 => 'field_isearch_prof_associations',
      4 => 'field_isearch_service',
      5 => 'field_isearch_work_history',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-public-work field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_public_work|node|asu_isearch_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_public_work|node|asu_isearch_profile|isearch_profile_full';
  $field_group->group_name = 'group_public_work';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'isearch_profile_full';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Public Work',
    'weight' => '44',
    'children' => array(
      0 => 'field_isearch_honors_awards',
      1 => 'field_isearch_editorships',
      2 => 'field_isearch_prof_associations',
      3 => 'field_isearch_graduate_faculties',
      4 => 'field_isearch_work_history',
      5 => 'field_isearch_service',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-public-work field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_public_work|node|asu_isearch_profile|isearch_profile_full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_research|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_research';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Research',
    'weight' => '19',
    'children' => array(
      0 => 'field_isearch_rsrch_activity',
      1 => 'field_isearch_rsrch_group',
      2 => 'field_isearch_rsrch_interests',
      3 => 'field_isearch_rsrch_publications',
      4 => 'field_isearch_rsrch_website',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-research field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_research|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_research|node|asu_isearch_profile|form';
  $field_group->group_name = 'group_research';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Research',
    'weight' => '6',
    'children' => array(
      0 => 'field_isearch_rsrch_activity',
      1 => 'field_isearch_rsrch_group',
      2 => 'field_isearch_rsrch_interests',
      3 => 'field_isearch_rsrch_publications',
      4 => 'field_isearch_rsrch_website',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_research|node|asu_isearch_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_research|node|asu_isearch_profile|isearch_profile_full';
  $field_group->group_name = 'group_research';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'isearch_profile_full';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Research',
    'weight' => '42',
    'children' => array(
      0 => 'field_isearch_rsrch_interests',
      1 => 'field_isearch_rsrch_activity',
      2 => 'field_isearch_rsrch_group',
      3 => 'field_isearch_rsrch_publications',
      4 => 'field_isearch_rsrch_website',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-research field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_research|node|asu_isearch_profile|isearch_profile_full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tabs|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tabs',
    'weight' => '2',
    'children' => array(
      0 => 'group_biography',
      1 => 'group_public_work',
      2 => 'group_research',
      3 => 'group_teaching',
      4 => 'group_industry_experience',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-tabs field-group-htabs',
      ),
    ),
  );
  $field_groups['group_tabs|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tabs|node|asu_isearch_profile|isearch_profile_full';
  $field_group->group_name = 'group_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'isearch_profile_full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tabs',
    'weight' => '17',
    'children' => array(
      0 => 'group_biography',
      1 => 'group_research',
      2 => 'group_teaching',
      3 => 'group_public_work',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Tabs',
      'instance_settings' => array(
        'classes' => 'group-tabs field-group-htabs',
      ),
    ),
  );
  $field_groups['group_tabs|node|asu_isearch_profile|isearch_profile_full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_teaching|node|asu_isearch_profile|default';
  $field_group->group_name = 'group_teaching';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Teaching',
    'weight' => '20',
    'children' => array(
      0 => 'field_isearch_tch_presentations',
      1 => 'field_isearch_tch_website',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-teaching field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_teaching|node|asu_isearch_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_teaching|node|asu_isearch_profile|form';
  $field_group->group_name = 'group_teaching';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Teaching',
    'weight' => '7',
    'children' => array(
      0 => 'field_isearch_tch_courses',
      1 => 'field_isearch_tch_presentations',
      2 => 'field_isearch_tch_website',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-teaching field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_teaching|node|asu_isearch_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_teaching|node|asu_isearch_profile|isearch_profile_full';
  $field_group->group_name = 'group_teaching';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_isearch_profile';
  $field_group->mode = 'isearch_profile_full';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Teaching',
    'weight' => '43',
    'children' => array(
      0 => 'field_isearch_tch_website',
      1 => 'field_isearch_tch_presentations',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-teaching field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_teaching|node|asu_isearch_profile|isearch_profile_full'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Advanced');
  t('Basic');
  t('Bio');
  t('Contact');
  t('Details');
  t('Expertise Area');
  t('Image');
  t('Industry Experience');
  t('Left');
  t('Links');
  t('Media');
  t('Personal');
  t('Portrait Section');
  t('Public Work');
  t('Research');
  t('Right');
  t('Social');
  t('Tabs');
  t('Teaching');

  return $field_groups;
}
