<?php
/**
 * @file
 * webspark_content_callout.features.uuid_file_entity.inc
 */

/**
 * Implements hook_uuid_features_default_file_entities().
 */
function webspark_content_callout_uuid_features_default_file_entities() {
  $files = array();

  $files[] = array(
    'filename' => 'example.jpg',
    'uri' => 'public://example.jpg',
    'filemime' => 'image/jpeg',
    'filesize' => 19824,
    'status' => 1,
    'type' => 'image',
    'uuid' => '688dba04-cd25-4ca5-9e9a-d785aa68d1c8',
    'field_file_image_alt_text' => array(),
    'field_file_image_title_text' => array(),
    'metadata' => array(
      'height' => 244,
      'width' => 366,
    ),
    'alt' => '',
    'title' => '',
    'uuid_features_file_path' => 'profiles/openasu/modules/custom/webspark_featurescustom/webspark_content_callout/images/example.jpg',
    'user_uuid' => 'dfa43482-1044-43a0-ba41-7b69fa34eed4',
  );
  return $files;
}
