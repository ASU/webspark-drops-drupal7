<?php
/**
 * @file
 * asu_degrees_feature.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function asu_degrees_feature_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'asu_degrees_feed';
  $feeds_importer->config = array(
    'name' => 'ASU Degrees Feed',
    'description' => 'ASU Degrees Feed that pulls degrees from web services',
    'fetcher' => array(
      'plugin_key' => 'ASUeAdvisorFeedsFetcher',
      'config' => array(),
    ),
    'parser' => array(
      'plugin_key' => 'ASUeAdvisorTransferFeedParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
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
            'target' => 'field_asu_academic_plan',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'AcadProg',
            'target' => 'field_asu_academic_program',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'CampusStringArray',
            'target' => 'field_asu_degree_campus',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'AsuCareerOpp',
            'target' => 'field_asu_degree_career_opps',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'CollegeDescr100',
            'target' => 'field_asu_college',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'CollegeUrl',
            'target' => 'field_asu_college_url:url',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'CollegeUrl',
            'target' => 'field_asu_college_url:title',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'Descr100',
            'target' => 'field_asu_degree_awarded',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'DescrlongExtns',
            'target' => 'body',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'DiplomaDescr',
            'target' => 'field_asu_diploma_description',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'DepartmentName',
            'target' => 'field_asu_degree_department',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'DepartmentCode',
            'target' => 'field_asu_degree_department_code',
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
            'target' => 'field_asu_degree_program_fee',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'AsuLangReqFlag',
            'target' => 'field_asu_degree_second_language',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'MinMathReq',
            'target' => 'field_asu_degree_min_math',
            'unique' => FALSE,
          ),
          22 => array(
            'source' => 'AsuCritTrackUrl',
            'target' => 'field_asu_degree_major_map_url:url',
            'unique' => FALSE,
          ),
          23 => array(
            'source' => 'AsuCritTrackUrl',
            'target' => 'field_asu_degree_major_map_url:title',
            'unique' => FALSE,
          ),
          24 => array(
            'source' => 'Degree',
            'target' => 'field_asu_degree',
            'unique' => FALSE,
          ),
          25 => array(
            'source' => 'Descr100',
            'target' => 'title',
            'unique' => FALSE,
          ),
          26 => array(
            'source' => 'careerData',
            'target' => 'field_asu_degree_example_careers',
            'unique' => FALSE,
          ),
          27 => array(
            'source' => 'subPlnMajorMaps.SubPlnMajorMapUrl',
            'target' => 'field_asu_degree_subplan_url:url',
            'unique' => FALSE,
          ),
          28 => array(
            'source' => 'subPlnMajorMaps.SubplnMajorMapSubplanCode',
            'target' => 'field_asu_degree_subplan_url:title',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'asu_feeds_text_format',
        'authorize' => 1,
        'skip_hash_check' => 0,
        'bundle' => 'asu_degree',
      ),
    ),
    'content_type' => 'asu_degree_feed',
    'update' => 0,
    'import_period' => '86400',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['asu_degrees_feed'] = $feeds_importer;

  return $export;
}
