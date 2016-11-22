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
  }
}

/***
 * Implements hook_entity_load
 *
 * Use this for updating the profile upon loading
 * todo:  set sane intervals for node updating
 *
 */
function asu_isearch_entity_load($entities, $type) {

  if ($type == 'node') {
    foreach ($entities as $key => $item) {
      if ($item->type == 'asu_isearch_profile') {

        $prev_update = NULL;
        $current_time = time();
        $interval = 60 * 60 * ASU_ISEARCH_PROFILE_ONLOAD_UPDATE_INTERVAL;

        if (isset($item->field_previous_isearch_update['und'][0]['value'])) {
          $prev_update = $item->field_previous_isearch_update['und'][0]['value'];
        }

        // if it's been longer than the update interval, then update from Solr
        // todo:  isearch fields also?
        if ($prev_update == NULL || ($current_time - $interval) > $prev_update) {

          $asurite = $item->field_isearch_asurite_id['und'][0]['value'];

          $person = asu_dir_utilities_get_solr_person($asurite);


          if ($person != NULL) {
            $photo_url = $person['photoUrl'];

            // ensure the file is truly accessible
            $response = drupal_http_request($photo_url);
            $destination = file_build_uri('asu_isearch_photos') . '/' . $person['eid'] . '.jpg';

            if ($response->code == 200) {

              $file = FALSE;
              $newfile = FALSE;

              $photo_exists = file_exists($destination);

              // does the file already exist on the server?
              // if yes, associate it
              if ($photo_exists) {
                $file = current(entity_load('file', array(), array('uri' => $destination . '')));
              }

              if (!$photo_exists || filesize($destination) != $response->headers['content-length'] || ($photo_exists && empty($file))) {
                $newfile = system_retrieve_file($photo_url, $destination, TRUE, FILE_EXISTS_REPLACE);
              }

              if ($newfile) {
                $item->field_isearch_photo_url[LANGUAGE_NONE][0]['fid'] = $newfile->fid;
              }

              //dpm($person, 'THE PERSON');
              //dpm($item, 'THE ITEM');


            }
          }

          $item->field_previous_isearch_update['und'][0]['value'] = time();
          field_attach_update('node', $item);

          //only update 1
          return FALSE;
        }
      }
    }
  }
}

