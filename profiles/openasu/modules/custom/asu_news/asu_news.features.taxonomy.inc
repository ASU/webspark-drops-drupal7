<?php
/**
 * @file
 * asu_news.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function asu_news_taxonomy_default_vocabularies() {
  return array(
    'asu_news' => array(
      'name' => 'ASU News',
      'machine_name' => 'asu_news',
      'description' => 'Used in ASU News nodes',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
