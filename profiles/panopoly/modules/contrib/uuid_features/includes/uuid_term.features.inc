<?php
/**
 * @file
 * Features hooks for the uuid_term features component.
 */

/**
 * Implements hook_features_export_options().
 */
function uuid_term_features_export_options() {
  $options = array();

  $query = 'SELECT t.tid, t.name, v.name AS vname, t.uuid
    FROM {taxonomy_term_data} t
    INNER JOIN {taxonomy_vocabulary} v ON t.vid = v.vid
    ORDER BY v.name ASC, t.name ASC';
  $results = db_query($query);
  foreach ($results as $term) {
    $options[$term->uuid] = $term->vname . ' - ' . $term->name;
  }

  return $options;
}

/**
 * Implements hook_features_export().
 */
function uuid_term_features_export($data, &$export, $module_name = '') {
  $pipe = array();

  $export['dependencies']['taxonomy'] = 'taxonomy';
  $export['dependencies']['uuid'] = 'uuid';
  $export['dependencies']['uuid_features'] = 'uuid_features';

  foreach ($data as $uuid) {
    $export['features']['uuid_term'][$uuid] = $uuid;

    // Get the machine name of the term's vocabulary.
    $voc_machine_name = db_query('SELECT v.machine_name FROM {taxonomy_vocabulary} v
      INNER JOIN {taxonomy_term_data} t ON t.vid = v.vid
      WHERE t.uuid = :uuid', array(':uuid' => $uuid))->fetchField();

    // Add the vocab UUID to the pipe, to be processed by uuid_vocabulary.
    $export['features']['uuid_vocabulary'][$voc_machine_name] = $voc_machine_name;

    // Get the UUID of the term's parents.
    $tid = uuid_taxonomy_term_find($uuid);
    $parents = taxonomy_get_parents($tid);
    foreach ($parents as $parent) {
      $export['features']['uuid_term'][$parent->uuid] = $parent->uuid;
    }
  }

  return $pipe;
}

/**
 * Implements hook_features_export_render().
 */
function uuid_term_features_export_render($module = 'foo', $data) {
  $translatables = $code = array();

  $code[] = '  $terms = array();';
  $code[] = '';
  foreach ($data as $uuid) {
    $tid = uuid_taxonomy_term_find($uuid);
    $term = taxonomy_term_load($tid);
    if (!$term) {
      continue;
    }

    $export = array('uuid' => $uuid);

    // Whitelist of term properties.
    $props = array('name', 'description', 'weight');
    foreach ($props as $key) {
      if (isset($term->$key)) {
        $export[$key] = $term->$key;
      }
    }

    // Get the UUID of the term's parent terms.
    $parents = taxonomy_get_parents($tid);
    foreach ($parents as $parent) {
      $export['parent'][] = $parent->uuid;
    }

    // Get the machine name of the term's vocabulary.
    /*$voc_machine_name = db_query('SELECT v.machine_name FROM {taxonomy_vocabulary} v
      INNER JOIN {taxonomy_term_data} t ON t.vid = v.vid
      WHERE t.vid = :vid', array(':vid' => $term->vid))->fetchField();*/
    $vocabularies = taxonomy_vocabulary_load_multiple(array($term->vid));

    $export['uuid_vocabulary'] = $vocabularies[$term->vid]->machine_name;

    $code[] = '  $terms[] = ' . features_var_export($export, '  ') . ';';
  }

  if (!empty($translatables)) {
    $code[] = features_translatables_export($translatables, '  ');
  }

  $code[] = '  return $terms;';
  $code = implode("\n", $code);
  return array('uuid_features_default_terms' => $code);
}

/**
 * Implements hook_features_revert().
 */
function uuid_term_features_revert($module) {
  uuid_term_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 * Rebuilds terms based on UUID from code defaults.
 */
function uuid_term_features_rebuild($module) {
  $terms = module_invoke($module, 'uuid_features_default_terms');
  if (!empty($terms)) {
    foreach ($terms as $data) {
      $existing = uuid_taxonomy_term_find($data['uuid']);

      if (!empty($existing)) {
        $data['tid'] = $existing;
      }

      $vid = db_query('SELECT vid FROM {taxonomy_vocabulary} WHERE machine_name = :machine_name', array(':machine_name' => $data['uuid_vocabulary']))->fetchField();
      if ($vid) {
        $data['vid'] = $vid;

        if (isset($data['parent']) && is_array($data['parent'])) {
          foreach ($data['parent'] as $key => $parent_uuid) {
            $data['parent'][$key] = uuid_taxonomy_term_find($parent_uuid);
          }
        }

        $ret = taxonomy_term_save($term /* TODO Term object replaces array $data */);

        // TODO: remove when http://drupal.org/node/860442 is resolved.
        uuid_set_uuid('taxonomy_term_data', 'tid', $data['tid'], $data['uuid']);
      }

    }
  }
}
