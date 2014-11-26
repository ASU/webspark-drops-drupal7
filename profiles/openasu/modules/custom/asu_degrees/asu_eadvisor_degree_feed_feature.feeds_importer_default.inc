<?php
/**
 * @file
 * asu_eadvisor_degree_feed_feature.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function asu_eadvisor_degree_feed_feature_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'asu_eadvisor_degree_feed';
  $feeds_importer->config = array(
    'name' => 'ASU eAdvisor Degree Feed',
    'description' => 'ASU eAdvisor Degree Feed that pulls degrees from web services',
    'fetcher' => array(
      'plugin_key' => 'IXRFetcher',
      'config' => array(),
    ),
    'parser' => array(
      'plugin_key' => 'ASUeAdvisorTransferFeedParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'asu_eadvisor_degree',
        'expire' => '-1',
        'author' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'AcadPlan',
            'target' => 'field_asu_degree_plan',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'AcadProg',
            'target' => 'field_asu_degree_prog',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'CampusStringArray',
            'target' => 'field_asu_degree_campus',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'AsuCareerOpp',
            'target' => 'field_asu_degree_career_ops',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'CollegeDescr100',
            'target' => 'field_asu_degree_college_name',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'CollegeUrl',
            'target' => 'field_asu_degree_college_url:url',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'CollegeUrl',
            'target' => 'field_asu_degree_college_url:title',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'Descr100',
            'target' => 'field_asu_degree_major',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'DescrlongExtns',
            'target' => 'body',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'DiplomaDescr',
            'target' => 'field_asu_degree_diploma_descr',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'DepartmentName',
            'target' => 'field_asu_degree_dept',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'DepartmentCode',
            'target' => 'field_asu_degree_dept_code',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'degreeSearchURL',
            'target' => 'field_asu_degree_asuds_url:url',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'degreeSearchURL',
            'target' => 'field_asu_degree_asuds_url:title',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'program',
            'target' => 'field_asu_degree_program',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'cert',
            'target' => 'field_asu_degree_cert',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'Reqdescr',
            'target' => 'field_asu_degree_req_desc',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'AdmissionsDegRequirements',
            'target' => 'field_asu_degree_admission_req',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'AsuProgramFee',
            'target' => 'field_asu_degree_prog_fee',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'AsuLangReqFlag',
            'target' => 'field_asu_degree_secound_lang',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'MinMathReq',
            'target' => 'field_asu_degree_min_math',
            'unique' => FALSE,
          ),
          22 => array(
            'source' => 'AsuCritTrackUrl',
            'target' => 'field_asu_degree_major_map:url',
            'unique' => FALSE,
          ),
          23 => array(
            'source' => 'AsuCritTrackUrl',
            'target' => 'field_asu_degree_major_map:title',
            'unique' => FALSE,
          ),
          24 => array(
            'source' => 'AcadPlan',
            'target' => 'title',
            'unique' => FALSE,
          ),
          25 => array(
            'source' => 'Degree',
            'target' => 'field_asu_degree_degree',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'asu_feeds_text_format',
      ),
    ),
    'content_type' => 'asu_eadvisor_degree_feed',
    'update' => 0,
    'import_period' => '86400',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['asu_eadvisor_degree_feed'] = $feeds_importer;

  return $export;
}
