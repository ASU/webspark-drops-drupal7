<?php
/**
 * @file
 * asu_directory.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_dir_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return ["version" => "1"];
  }
}

/**
 * Implements hook_node_info().
 */
function asu_dir_node_info() {
  $items = [
    'asu_directory' => [
      'name' => t('ASU Directory'),
      'base' => 'node_content',
      'description' => t('A node to display an ASU directory from a specified root department. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('Complete the specified fields to customize the directory listing.'),
    ],
  ];

  drupal_alter('node_info', $items);
  return $items;
}
