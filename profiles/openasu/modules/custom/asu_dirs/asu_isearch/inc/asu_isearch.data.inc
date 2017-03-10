<?php

/**
 * Returns an associative array of rank titles
 */
function asu_isearch_get_rank_titles() {
  // @FIXME: Add caching
  $result = db_select('field_data_field_isearch_affil_title', 't')
    ->fields('t', array('field_isearch_affil_title_value'))
    ->orderBy('field_isearch_affil_title_value')
    ->distinct(TRUE)
    ->execute();


  $ranks = array_keys($result->fetchAllAssoc('field_isearch_affil_title_value'));
  $ranks = drupal_map_assoc($ranks);

  return $ranks;
}
