<?php
/**
 * @file
 * asu_ap_feature.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function asu_ap_feature_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'asu_ap_feed';
  $feeds_importer->config = array(
    'name' => 'ASU Academic Programs Feed',
    'description' => 'ASU Academic Programs Feed that pulls degree programs from web services',
    'fetcher' => array(
      'plugin_key' => 'ASUeAdvisorFeedFetcher',
      'config' => array(),
    ),
    'parser' => array(
      'plugin_key' => 'ASUeAdvisorFeedParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'AcadPlan',
            'target' => 'field_asu_ap_acad_plan',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'AcadProg',
            'target' => 'field_asu_ap_acad_prog',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'acceleratedDegree',
            'target' => 'field_asu_ap_acc_program',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'AsuProgramFee',
            'target' => 'field_asu_ap_program_fee',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'AdmissionsDegRequirements',
            'target' => 'field_asu_ap_admission_req',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'degreeSearchURL',
            'target' => 'field_asu_ap_asuds_url:url',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'degreeSearchURL',
            'target' => 'field_asu_ap_asuds_url:title',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'CampusStringArray',
            'target' => 'field_asu_ap_campus',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'AsuCareerOpp',
            'target' => 'field_asu_ap_career_opps',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'cert',
            'target' => 'field_asu_ap_cert',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'CollegeDescr100',
            'target' => 'field_asu_ap_college',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'CollegeUrl',
            'target' => 'field_asu_ap_college_url:url',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'CollegeUrl',
            'target' => 'field_asu_ap_college_url:title',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'concurrentDegree',
            'target' => 'field_asu_ap_conc_program',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'Degree',
            'target' => 'field_asu_ap',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'DescrlongExtns',
            'target' => 'body',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'Descr100',
            'target' => 'title',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'Descr100',
            'target' => 'field_asu_ap_awarded',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'DepartmentCode',
            'target' => 'field_asu_ap_department_code',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'DepartmentName',
            'target' => 'field_asu_ap_department',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'DiplomaDescr',
            'target' => 'field_asu_ap_diploma_desc',
            'unique' => FALSE,
          ),
          22 => array(
            'source' => 'careerData',
            'target' => 'field_asu_ap_example_careers',
            'unique' => FALSE,
          ),
          23 => array(
            'source' => 'AsuCritTrackUrl',
            'target' => 'field_asu_ap_major_map_url:url',
            'unique' => FALSE,
          ),
          24 => array(
            'source' => 'AsuCritTrackUrl',
            'target' => 'field_asu_ap_major_map_url:title',
            'unique' => FALSE,
          ),
          25 => array(
            'source' => 'MinMathReq',
            'target' => 'field_asu_ap_min_math',
            'unique' => FALSE,
          ),
          26 => array(
            'source' => 'newDegree',
            'target' => 'field_asu_ap_new_program',
            'unique' => FALSE,
          ),
          27 => array(
            'source' => 'degreeMajorMap',
            'target' => 'field_asu_ap_prog_req',
            'unique' => FALSE,
          ),
          28 => array(
            'source' => 'program',
            'target' => 'field_asu_ap_program',
            'unique' => FALSE,
          ),
          29 => array(
            'source' => 'Reqdescr',
            'target' => 'field_asu_ap_req_desc',
            'unique' => FALSE,
          ),
          30 => array(
            'source' => 'AsuLangReqFlag',
            'target' => 'field_asu_ap_second_language',
            'unique' => FALSE,
          ),
          31 => array(
            'source' => 'subPlnMajorMaps.SubPlnMajorMapUrl',
            'target' => 'field_asu_ap_subplan_url:url',
            'unique' => FALSE,
          ),
          32 => array(
            'source' => 'subPlnMajorMaps.SubplnMajorMapSubplanName',
            'target' => 'field_asu_ap_subplan_url:title',
            'unique' => FALSE,
          ),
          33 => array(
            'source' => 'wueCampusConfirmed',
            'target' => 'field_asu_ap_wue_available',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'asu_feeds_text_format',
        'skip_hash_check' => 0,
        'bundle' => 'asu_ap',
      ),
    ),
    'content_type' => 'asu_ap_feed',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['asu_ap_feed'] = $feeds_importer;

  return $export;
}
