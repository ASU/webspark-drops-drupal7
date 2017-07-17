<?php

/**
 * Provides views integration for files.
 */

/**
 * Implements hook_views_data().
 */
function commerce_file_views_data() {
  $data['commerce_license']['download_limit'] = array(
    'title' => t('Download limit'),
    'help' => t('Displays the download limit for a file.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_download_limit',
      'click sortable' => FALSE,
    ),
  );

  return $data;
}
