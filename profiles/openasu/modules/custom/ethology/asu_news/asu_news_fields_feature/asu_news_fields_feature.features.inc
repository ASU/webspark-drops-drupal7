<?php
/**
 * @file
 * asu_news_fields_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_news_fields_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
