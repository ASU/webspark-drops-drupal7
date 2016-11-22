<?php
/**
 * @file
 * asu_isearch.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function asu_isearch_taxonomy_default_vocabularies() {
  return array(
    'isearch_departments' => array(
      'name' => 'iSearch Departments',
      'machine_name' => 'isearch_departments',
      'description' => 'Departments provided by iSearch.',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'isearch_expertise' => array(
      'name' => 'iSearch Expertise',
      'machine_name' => 'isearch_expertise',
      'description' => 'The expertise fields provided by iSearch.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'isearch_local_tags' => array(
      'name' => 'iSearch Local Tags',
      'machine_name' => 'isearch_local_tags',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'isearch_ranks' => array(
      'name' => 'iSearch Ranks',
      'machine_name' => 'isearch_ranks',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
