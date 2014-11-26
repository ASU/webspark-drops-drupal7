<?php
/**
 * @file
 * webspark_newsevents_prereq.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function webspark_newsevents_prereq_taxonomy_default_vocabularies() {
  return array(
    'asu_news' => array(
      'name' => 'ASU News',
      'machine_name' => 'asu_news',
      'description' => 'Used in ASU News nodes',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
