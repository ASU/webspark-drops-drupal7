<?php

/**
 * Implements hook_entity_view()
 */
function asu_isearch_entity_view($entity, $type, $view_mode, $langcode) {
  if ($type == 'node' && $entity->type == 'asu_isearch_profile') {
    // Suppress title
    drupal_set_title(FALSE);
  }
}

/**
 * Implements hook_entity_presave()
 */
function asu_isearch_entity_presave($entity, $type) {
  if ($type == 'field_collection_item' && $entity->field_name == 'field_isearch_affiliations') {

    $affiliation = entity_metadata_wrapper($type, $entity);

    $affiliation_rank_weight = NULL;

    $is_faculty_ranked = (!empty($entity->field_isearch_affil_rank[LANGUAGE_NONE]) && !is_null($entity->field_isearch_affil_rank[LANGUAGE_NONE][0]['tid']));
    if ($is_faculty_ranked) {
      $affiliation_rank_weight = $affiliation->field_isearch_affil_rank->field_isearch_rank_weight->value();
    }

    $has_local_weight = (!empty($entity->field_isearch_affil_local_weight[LANGUAGE_NONE]));

    if ($has_local_weight) {
      $affiliation_rank_weight = $affiliation->field_isearch_affil_local_weight->value();
    }

    // set the rank weight
    if ($affiliation_rank_weight != NULL) {
      $entity->field_isearch_affil_rank_weight[LANGUAGE_NONE][0]['value'] = $affiliation_rank_weight;
    }

    // set this field for proper filtering
    if (empty($entity->field_isearch_affil_hide)) {
      $entity->field_isearch_affil_hide[LANGUAGE_NONE][0]['value'] = 0;
    }
  }
}





