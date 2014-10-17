<?php
/**
 * @file
 * webspark_extras.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function webspark_extras_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.field_featured_categories.field_featured_categories"]["DELETED"] = TRUE;
  $overrides["field_base.field_featured_status.field_featured_status"]["DELETED"] = TRUE;

  // Exported overrides for: field_instance
  $overrides["field_instance.node-panopoly_page-field_featured_categories.node-panopoly_page-field_featured_categories"]["DELETED"] = TRUE;
  $overrides["field_instance.node-panopoly_page-field_featured_image.node-panopoly_page-field_featured_image"]["DELETED"] = TRUE;
  $overrides["field_instance.node-panopoly_page-field_featured_status.node-panopoly_page-field_featured_status"]["DELETED"] = TRUE;

 return $overrides;
}
