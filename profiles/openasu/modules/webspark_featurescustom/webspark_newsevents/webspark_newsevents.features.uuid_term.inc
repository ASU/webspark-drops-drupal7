<?php
/**
 * @file
 * webspark_newsevents.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function webspark_newsevents_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Technology',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'd0879723-e8aa-4d6e-aa66-64fc467c89a3',
    'vocabulary_machine_name' => 'asu_events_category',
  );
  return $terms;
}
