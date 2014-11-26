<?php
/**
 * @file
 * webspark_content_callout.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function webspark_content_callout_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function webspark_content_callout_node_info() {
  $items = array(
    'content_callout' => array(
      'name' => t('Content Callout Box'),
      'base' => 'node_content',
      'description' => t('Call attention to special content or reinforce branding. Don\'t place these directly under a Hero Image block, directly over the footer, and don\'t stack these on top of each other.'),
      'has_title' => '1',
      'title_label' => t('Callout Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
