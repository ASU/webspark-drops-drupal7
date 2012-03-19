<?php

/**
 * @file
 * Registry file for Display Suite.
 */

/**
 * Implements hook_theme().
 */
function _ds_theme() {
  $theme_functions = array();

  // Layouts
  $layouts = ds_get_layout_info();
  foreach ($layouts as $key => $layout) {

    // We don't need panel layouts to be registered.
    if (isset($layout['module']) && $layout['module'] == 'panels') {
      continue;
    }

    $theme_functions[$key] = array(
      'render element' => 'elements',
      'template' => strtr($key, '_', '-'),
      'path' => $layout['path'],
    );
  }

  return $theme_functions;
}

/**
 * Implements hook_features_api().
 */
function _ds_features_api() {
  static $api = FALSE;

  if (!$api) {
    module_load_include('inc', 'features', 'includes/features.ctools');
    $api = ctools_component_features_api('ds');
    foreach ($api as $key => $value) {
      switch ($key) {
        case 'ds_field_settings':
          $api[$key]['name'] = 'Display suite field settings';
          break;
        case 'ds_layout_settings':
          $api[$key]['name'] = 'Display suite layout settings';
          break;
        case 'ds_view_modes':
          $api[$key]['name'] = 'Display suite view modes';
          break;
        case 'ds_fields':
          $api[$key]['name'] = 'Display suite fields';
          break;
      }
    }
  }

  return $api;
}

/**
 * Remove or rename layout & field settings on entity machine name update.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $info
 *   The entity info.
 * @param $action
 *   The action, either update or delete.
 */
function _ds_entity_type_update($entity_type, $info, $action) {

  // Delete settings.
  if ($action == 'delete') {
    db_delete('ds_layout_settings')
      ->condition('entity_type', $entity_type)
      ->condition('bundle', $info->type)
      ->execute();
    db_delete('ds_field_settings')
      ->condition('entity_type', $entity_type)
      ->condition('bundle', $info->type)
      ->execute();
  }

  // Update settings.
  if ($action == 'update') {
    $records = db_query('SELECT * FROM {ds_layout_settings} WHERE entity_type = :entity_type AND bundle = :bundle', array(':entity_type' => $entity_type, ':bundle' => $info->old_type));
    foreach ($records as $record) {
      $old_id = $entity_type . '|' . $info->old_type . '|' . $record->view_mode;
      $new_id = $entity_type . '|' . $info->type . '|' . $record->view_mode;
      db_update('ds_layout_settings')
        ->fields(array(
          'id' => $new_id,
          'bundle' => $info->type)
        )
        ->condition('id', $old_id)
        ->execute();
    }
    $records = db_query('SELECT * FROM {ds_field_settings} WHERE entity_type = :entity_type AND bundle = :bundle', array(':entity_type' => $entity_type, ':bundle' => $info->old_type));
    foreach ($records as $record) {
      $old_id = $entity_type . '|' . $info->old_type . '|' . $record->view_mode;
      $new_id = $entity_type . '|' . $info->type . '|' . $record->view_mode;
      db_update('ds_field_settings')
        ->fields(array(
          'id' => $new_id,
          'bundle' => $info->type)
        )
        ->condition('id', $old_id)
        ->execute();
    }
  }

  // Clear cache.
  cache_clear_all('ds_fields', 'cache');
  cache_clear_all('ds_field_settings', 'cache');
  field_info_cache_clear();
}

/**
 * Implements hook_theme_registry_alter().
 */
function _ds_theme_registry_alter(&$theme_registry) {

  // Inject ds_entity_variables in all entity theming functions.
  $entity_info = entity_get_info();
  foreach ($entity_info as $entity => $info) {
    if (isset($entity_info[$entity]['fieldable']) && $entity_info[$entity]['fieldable']) {

      // User uses user_profile for theming.
      if ($entity == 'user') $entity = 'user_profile';

      // Only add preprocess functions if entity exposes theme function.
      if (isset($theme_registry[$entity])) {
        $theme_registry[$entity]['preprocess functions'][] = 'ds_entity_variables';
      }
    }
  }

  // Support for File Entity.
  if (isset($theme_registry['file_entity'])) {
    $theme_registry['file_entity']['preprocess functions'][] = 'ds_entity_variables';
  }

  // Support for Entity API.
  if (isset($theme_registry['entity'])) {
    $theme_registry['entity']['preprocess functions'][] = 'ds_entity_variables';
  }
}

/**
 * Implements hook_entity_info_alter().
 */
function _ds_entity_info_alter(&$entity_info) {

  // Make sure ds_view_modes table exists.
  if (!db_table_exists('ds_view_modes')) {
    return;
  }

  ctools_include('export');

  // Add custom view modes to entities.
  $custom_view_modes = ctools_export_crud_load_all('ds_view_modes');
  foreach ($custom_view_modes as $view_mode_key => $view_mode_value) {
    $view_mode = array(
      'label' => check_plain($view_mode_value->label),
      'custom settings' => FALSE,
    );
    foreach ($view_mode_value->entities as $entity_type) {
      if (isset($entity_info[$entity_type])) {
        $entity_info[$entity_type]['view modes'][$view_mode_key] = $view_mode;
      }
    }
  }

  // Add layout if applicable.
  $ds_layouts = ds_get_layout_info();
  $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
  foreach ($ds_layout_settings as $row) {

    // Don't store any configurations with layouts that don't exist anymore.
    if (!isset($ds_layouts[$row->layout]) && !isset($row->settings['ds_panels'])) {
      continue;
    }

    if (!isset($entity_info[$row->entity_type])) {
      continue;
    }

    if (!isset($entity_info[$row->entity_type]['bundles'][$row->bundle])) {
      continue;
    }

    $layout = array();
    if (!isset($row->settings['ds_panels'])) {
      $layout = $ds_layouts[$row->layout];
    }
    $layout['layout'] = $row->layout;
    $layout['settings'] = $row->settings;
    $entity_info[$row->entity_type]['bundles'][$row->bundle]['layouts'][$row->view_mode] = $layout;
  }
}

/**
 * Implements hook_ds_layout_info().
 */
function _ds_ds_layout_info() {
  $path = drupal_get_path('module', 'ds');
  $layouts = array(
    'ds_1col' => array(
      'label' => t('One column'),
      'path' => $path . '/layouts/ds_1col',
      'regions' => array(
        'ds_content' => t('Content'),
      ),
    ),
    'ds_2col' => array(
      'label' => t('Two column'),
      'path' => $path . '/layouts/ds_2col',
      'regions' => array(
        'left' => t('Left'),
        'right' => t('Right')
      ),
      'css' => TRUE,
    ),
    'ds_2col_stacked' => array(
      'label' => t('Two column stacked'),
      'path' => $path . '/layouts/ds_2col_stacked',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_2col_stacked_fluid' => array(
      'label' => t('Fluid two column stacked'),
      'path' => $path . '/layouts/ds_2col_stacked_fluid',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_3col' => array(
      'label' => t('Three column - 25/50/25'),
      'path' => $path . '/layouts/ds_3col',
      'regions' => array(
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
      ),
      'css' => TRUE,
    ),
    'ds_3col_equal_width' => array(
      'label' => t('Three column - equal width'),
      'path' => $path . '/layouts/ds_3col_equal_width',
      'regions' => array(
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
      ),
      'css' => TRUE,
    ),
    'ds_3col_stacked' => array(
      'label' => t('Three column stacked - 25/50/25'),
      'path' => $path . '/layouts/ds_3col_stacked',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_3col_stacked_fluid' => array(
      'label' => t('Fluid three column stacked - 25/50/25'),
      'path' => $path . '/layouts/ds_3col_stacked_fluid',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_3col_stacked_equal_width' => array(
      'label' => t('Three column stacked - equal width'),
      'path' => $path . '/layouts/ds_3col_stacked_equal_width',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_3col_stacked_html5' => array(
      'label' => t('Three column stacked - 25/50/25 (HTML5)'),
      'path' => $path . '/layouts/ds_3col_stacked_html5',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_4col' => array(
      'label' => t('Four column - equal width'),
      'path' => $path . '/layouts/ds_4col',
      'regions' => array(
        'first' => t('First'),
        'second' => t('Second'),
        'third' => t('Third'),
        'fourth' => t('Fourth'),
      ),
       'css' => TRUE,
    ),
  );

  // Support for panels.
  if (module_exists('panels')) {
    ctools_include('plugins', 'panels');
    $panel_layouts = panels_get_layouts();
    foreach ($panel_layouts as $key => $layout) {
      // The easy ones.
      if (isset($layout['regions'])) {
        $layouts['panels-' . $key] = array(
          'label' => $layout['title'],
          'path' => $layout['path'],
          'module' => 'panels',
          // We need the Panels plugin info array to correctly include the
          // layout and its CSS files later on.
          'panels' => $layout,
          'flexible' => FALSE,
          'regions' => $layout['regions'],
        );
        if (!empty($layout['css'])) {
          $layouts['panels-' . $key]['css'] = TRUE;
        }
      }
      // Flexible panel layouts, ignore the default flexible.
      else {
        if ($layout['name'] != 'flexible') {
          $regions = panels_flexible_panels(array(), array(), $layout);
          $layouts['panels-' . $key] = array(
            'label' => $layout['title'],
            'path' => $layout['path'],
            'module' => 'panels',
            'panels' => $layout,
            'flexible' => TRUE,
            'regions' => $regions,
          );
        }
      }
    }
  }

  // Get layouts defined in the default theme and base theme (if applicable).
  $theme = variable_get('theme_default');
  $themes = list_themes();

  $base_theme = array();
  $ancestor = $theme;
  while ($ancestor && isset($themes[$ancestor]->base_theme)) {
    $ancestor = $themes[$ancestor]->base_theme;
    $base_theme[] = $themes[$ancestor];
  }

  foreach (array_reverse($base_theme) as $base) {
    _ds_layouts_scan_theme($base->name, $layouts);
  }
  _ds_layouts_scan_theme($theme, $layouts);

  return $layouts;
}

function _ds_layouts_scan_theme($theme, &$layouts) {
  $theme_layouts = file_scan_directory(drupal_get_path('theme', $theme) . '/ds_layouts', '/inc$/');
  foreach ($theme_layouts as $file => $values) {
    include_once(DRUPAL_ROOT . '/' . $file);
    $function = 'ds_' . $values->name;
    $layouts[$values->name] = $function();
    $layouts[$values->name]['path'] = str_replace('/' . $values->filename, '', $file);
  }
}
