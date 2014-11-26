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
    'uuid' => '0043afe3-9f4d-4b01-8b69-d7e387f96480',
    'field_file_image_alt_text' => array(),
    'field_file_image_title_text' => array(),
    'metadata' => array(
      'height' => 244,
      'width' => 366,
    ),
    'alt' => '',
    'title' => '',
    'uuid_features_file_path' => 'profiles/openasu/modules/custom/webspark_featurescustom/webspark_content_callout/images/example.jpg',
    'user_uuid' => '5d9be61c-96bb-4398-83cd-92b0a9c22924',
  );
  return $files;
}
