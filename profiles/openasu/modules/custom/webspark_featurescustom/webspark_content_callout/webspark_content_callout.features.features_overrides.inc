<?php
/**
 * @file
 * webspark_content_callout.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function webspark_content_callout_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.uuid_features_file_mode.value"] = 'local';

 return $overrides;
}
