<?php
/**
 * @file
 * asu_directory.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function asu_directory_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'asu_directory_feed';
  $feeds_importer->config = array(
    'name' => 'ASU Directory Feed',
    'description' => 'ASU Directory Feed that pulls information from web services',
    'fetcher' => array(
      'plugin_key' => 'ASUDirectoryFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'ASUDirectoryFeedParser',
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
            'source' => 'url',
            'target' => 'url',
            'unique' => 1,
          ),
          2 => array(
            'source' => 'eid',
            'target' => 'field_asu_directory_eid',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'displayname',
            'target' => 'title',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'firstname',
            'target' => 'field_asu_directory_firstname',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'lastname',
            'target' => 'field_asu_directory_lastname',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'displayname',
            'target' => 'field_asu_directory_displayname',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'asuriteid',
            'target' => 'field_asu_directory_asuriteid',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'primaryaffiliation',
            'target' => 'field_asu_directory_prim_affili',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'affiliationdescription',
            'target' => 'field_asu_directory_affili_desc',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'company',
            'target' => 'field_asu_directory_company',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'department',
            'target' => 'field_asu_directory_department',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'departmentcode',
            'target' => 'field_asu_directory_deptcode',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'email',
            'target' => 'field_asu_directory_email',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'phone',
            'target' => 'field_asu_directory_phone',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'researchinterest',
            'target' => 'field_asu_directory_research',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'biography',
            'target' => 'body',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 't_term',
            'target' => 'field_tags',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'title',
            'target' => 'field_asu_directory_title',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'url',
            'target' => 'field_asu_directory_url:title',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'url',
            'target' => 'field_asu_directory_url:url',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'imageurl',
            'target' => 'field_asu_directory_image',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'asu_feeds',
        'authorize' => 1,
        'skip_hash_check' => 0,
        'bundle' => 'asu_directory_person',
      ),
    ),
    'content_type' => 'asu_directory_feed',
    'update' => 0,
    'import_period' => '86400',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['asu_directory_feed'] = $feeds_importer;

  return $export;
}
