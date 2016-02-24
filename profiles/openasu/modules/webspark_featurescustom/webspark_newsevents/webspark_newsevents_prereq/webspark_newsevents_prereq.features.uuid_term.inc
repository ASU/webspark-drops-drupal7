<?php
/**
 * @file
 * webspark_newsevents_prereq.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function webspark_newsevents_prereq_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Feature Articles',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '7d16a7f7-63d9-4c37-afd6-19c4d38b4ccf',
    'vocabulary_machine_name' => 'asu_news',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-news/feature-articles',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Top Articles',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'cf9e5588-be92-4a36-8405-ceb7996f437b',
    'vocabulary_machine_name' => 'asu_news',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-news/top-articles',
        'language' => 'und',
      ),
    ),
  );
  return $terms;
}
