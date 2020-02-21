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
            'language' => 'und',
          ),
          1 => array(
            'source' => 'AcadPlan',
            'target' => 'field_asu_ap_acad_plan',
            'unique' => FALSE,
            'language' => 'und',
          ),
          2 => array(
            'source' => 'AcadProg',
            'target' => 'field_asu_ap_acad_prog',
            'unique' => FALSE,
            'language' => 'und',
          ),
          3 => array(
            'source' => 'accelerateDegrees',
            'target' => 'field_asu_ap_acc_program',
            'unique' => FALSE,
            'language' => 'und',
          ),
          4 => array(
            'source' => 'AsuProgramFee',
            'target' => 'field_asu_ap_program_fee',
            'unique' => FALSE,
            'language' => 'und',
          ),
          5 => array(
            'source' => 'AdmissionsDegRequirements',
            'target' => 'field_asu_ap_admission_req',
            'unique' => FALSE,
            'language' => 'und',
          ),
          6 => array(
            'source' => 'degreeSearchURL',
            'target' => 'field_asu_ap_asuds_url:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          7 => array(
            'source' => 'degreeSearchURL',
            'target' => 'field_asu_ap_asuds_url:title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          8 => array(
            'source' => 'CampusStringArray',
            'target' => 'field_asu_ap_campus',
            'unique' => FALSE,
            'language' => 'und',
          ),
          9 => array(
            'source' => 'AsuCareerOpp',
            'target' => 'field_asu_ap_career_opps',
            'unique' => FALSE,
            'language' => 'und',
          ),
          10 => array(
            'source' => 'cert',
            'target' => 'field_asu_ap_cert',
            'unique' => FALSE,
            'language' => 'und',
          ),
          11 => array(
            'source' => 'CollegeDescr100',
            'target' => 'field_asu_ap_college',
            'unique' => FALSE,
            'language' => 'und',
          ),
          12 => array(
            'source' => 'CollegeDescr100Joint',
            'target' => 'field_asu_ap_college_j',
            'unique' => FALSE,
            'language' => 'und',
          ),
          13 => array(
            'source' => 'CollegeUrl',
            'target' => 'field_asu_ap_college_url:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          14 => array(
            'source' => 'CollegeUrl',
            'target' => 'field_asu_ap_college_url:title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          15 => array(
            'source' => 'CollegeUrlJoint',
            'target' => 'field_asu_ap_college_url_j:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          16 => array(
            'source' => 'CollegeUrlJoint',
            'target' => 'field_asu_ap_college_url_j:title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          17 => array(
            'source' => 'concurrentDegrees',
            'target' => 'field_asu_ap_conc_program',
            'unique' => FALSE,
            'language' => 'und',
          ),
          18 => array(
            'source' => 'CurriculumUrl',
            'target' => 'field_asu_ap_curriculum_url:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          19 => array(
            'source' => 'Degree',
            'target' => 'field_asu_ap',
            'unique' => FALSE,
            'language' => 'und',
          ),
          20 => array(
            'source' => 'DescrlongExtns',
            'target' => 'body',
            'unique' => FALSE,
            'language' => 'und',
          ),
          21 => array(
            'source' => 'Descr100',
            'target' => 'title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          22 => array(
            'source' => 'Descr100',
            'target' => 'field_asu_ap_awarded',
            'unique' => FALSE,
            'language' => 'und',
          ),
          23 => array(
            'source' => 'DepartmentCode',
            'target' => 'field_asu_ap_department_code',
            'unique' => FALSE,
            'language' => 'und',
          ),
          24 => array(
            'source' => 'DepartmentCodeJoint',
            'target' => 'field_asu_ap_department_code_j',
            'unique' => FALSE,
            'language' => 'und',
          ),
          25 => array(
            'source' => 'DepartmentName',
            'target' => 'field_asu_ap_department',
            'unique' => FALSE,
            'language' => 'und',
          ),
          26 => array(
            'source' => 'DepartmentNameJoint',
            'target' => 'field_asu_ap_department_j',
            'unique' => FALSE,
            'language' => 'und',
          ),
          27 => array(
            'source' => 'DiplomaDescr',
            'target' => 'field_asu_ap_diploma_desc',
            'unique' => FALSE,
            'language' => 'und',
          ),
          28 => array(
            'source' => 'careerData',
            'target' => 'field_asu_ap_example_careers',
            'unique' => FALSE,
            'language' => 'und',
          ),
          29 => array(
            'source' => 'graduateAllApplyDates',
            'target' => 'field_asu_ap_grad_all_app_dates',
            'unique' => FALSE,
            'language' => 'und',
          ),
          30 => array(
            'source' => 'AsuCritTrackUrl',
            'target' => 'field_asu_ap_major_map_url:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          31 => array(
            'source' => 'AsuCritTrackUrl',
            'target' => 'field_asu_ap_major_map_url:title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          32 => array(
            'source' => 'marketText',
            'target' => 'field_asu_ap_market_text',
            'unique' => FALSE,
            'language' => 'und',
          ),
          33 => array(
            'source' => 'MinMathReq',
            'target' => 'field_asu_ap_min_math',
            'unique' => FALSE,
            'language' => 'und',
          ),
          34 => array(
            'source' => 'DegreeNew',
            'target' => 'field_asu_ap_new_program',
            'unique' => FALSE,
            'language' => 'und',
          ),
          35 => array(
            'source' => 'degreeMajorMap',
            'target' => 'field_asu_ap_prog_req',
            'unique' => FALSE,
            'language' => 'und',
          ),
          36 => array(
            'source' => 'program',
            'target' => 'field_asu_ap_program',
            'unique' => FALSE,
            'language' => 'und',
          ),
          37 => array(
            'source' => 'Reqdescr',
            'target' => 'field_asu_ap_req_desc',
            'unique' => FALSE,
            'language' => 'und',
          ),
          38 => array(
            'source' => 'AsuLangReqFlag',
            'target' => 'field_asu_ap_second_language',
            'unique' => FALSE,
            'language' => 'und',
          ),
          39 => array(
            'source' => 'subPlnMajorMaps.SubPlnMajorMapUrl',
            'target' => 'field_asu_ap_subplan_url:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          40 => array(
            'source' => 'subPlnMajorMaps.SubplnMajorMapSubplanName',
            'target' => 'field_asu_ap_subplan_url:title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          41 => array(
            'source' => 'Url1',
            'target' => 'field_asu_ap_url_1:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          42 => array(
            'source' => 'Url2',
            'target' => 'field_asu_ap_url_2:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          43 => array(
            'source' => 'Url3',
            'target' => 'field_asu_ap_url_3:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          44 => array(
            'source' => 'Url4',
            'target' => 'field_asu_ap_url_4:video_url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          45 => array(
            'source' => 'wueCampusConfirmed',
            'target' => 'field_asu_ap_wue_available',
            'unique' => FALSE,
            'language' => 'und',
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'asu_feeds_text_format',
        'skip_hash_check' => 0,
        'bundle' => 'asu_ap',
        'insert_new' => 1,
        'update_non_existent' => 'skip',
        'language' => 'und',
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
