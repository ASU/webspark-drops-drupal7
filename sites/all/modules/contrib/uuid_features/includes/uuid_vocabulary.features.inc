<?php
/**
 * @file
 * Features hooks for the uuid_vocabulary features component.
 */

/**
 * Implements hook_features_export_options().
 */
function uuid_vocabulary_features_export_options() {
  $options = array();

  $vocabularies = taxonomy_get_vocabularies();
  foreach ($vocabularies as $vocab) {
    $options[$vocab->machine_name] = $vocab->name;
  }

  return $options;
}

/**
 * Implements hook_features_export().
 */
function uuid_vocabulary_features_export($data, &$export, $module_name = '') {
  $pipe = array();

  $export['dependencies']['taxonomy'] = 'taxonomy';
  $export['dependencies']['uuid'] = 'uuid';
  $export['dependencies']['uuid_features'] = 'uuid_features';

  foreach ($data as $uuid) {
    $export['features']['uuid_vocabulary'][$uuid] = $uuid;
  }

  return $pipe;
}

/**
 * Implements hook_features_export_render().
 */
function uuid_vocabulary_features_export_render($module = 'foo', $data) {
  $translatables = $code = array();

  $code[] = '  $vocabularies = array();';
  $code[] = '';
  foreach ($data as $uuid) {
    $vocab = taxonomy_vocabulary_machine_name_load($uuid);

    if (!$vocab) {
      continue;
    }

    $export = array('uuid' => $uuid);

    // Whitelist of vocabulary properties.
    $props = array(
      'name',
      'description',
      'help',
      'relations',
      'heirarchy',
      'multiple',
      'required',
      'tags',
      'module',
      'weight',
      'nodes',
    );
    foreach ($props as $key) {
      if (isset($vocab->$key)) {
        $export[$key] = $vocab->$key;
      }
    }

    $code[] = '  $vocabularies[] = ' . features_var_export($export, '  ') . ';';
  }

  if (!empty($translatables)) {
    $code[] = features_translatables_export($translatables, '  ');
  }

  $code[] = '  return $vocabularies;';
  $code = implode("\n", $code);
  return array('uuid_features_default_vocabularies' => $code);
}

/**
 * Implements hook_features_revert().
 */
function uuid_vocabulary_features_revert($module) {
  uuid_vocabulary_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 * Rebuilds nodes based on UUID from code defaults.
 */
function uuid_vocabulary_features_rebuild($module) {
  $vocabs = module_invoke($module, 'uuid_features_default_vocabularies');
  if (!empty($vocabs)) {
    foreach ($vocabs as $vocab) {
      $vocabulary = taxonomy_vocabulary_machine_name_load($vocab->machine_name);

      if (!empty($vocabulary)) {
        $vocab->vid = $vocabulary->vid;
      }

      taxonomy_vocabulary_save($vocab);
    }
  }
}
