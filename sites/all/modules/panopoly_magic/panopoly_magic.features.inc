<?php
/**
 * @file
 * panopoly_magic.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function panopoly_magic_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
