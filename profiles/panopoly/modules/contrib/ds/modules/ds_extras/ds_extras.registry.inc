<?php

/**
 * @file
 * Display suite Extras registry file.
 */

/**
 * Implements hook_menu_alter().
 */
function _ds_extras_menu_alter(&$items) {

  // Switch view mode.
  if (variable_get('ds_extras_switch_view_mode', FALSE)) {
    $items['node/%node']['page callback'] = 'ds_extras_node_page_view';
    $items['node/%node']['file'] = 'ds_extras.pages.inc';
    $items['node/%node']['file path'] = drupal_get_path('module', 'ds_extras');
  }

  // Revision view mode.
  if (variable_get('ds_extras_revision_view_mode', FALSE)) {

    // Do not conflict with the revisioning module.
    if (module_exists('revisioning')) {
      $items['node/%node/revisions/%vid/view']['page callback'] = 'ds_extras_revision_node_show';
      $items['node/%node/revisions/%vid/view']['file'] = 'ds_extras.pages.inc';
      $items['node/%node/revisions/%vid/view']['file path'] = drupal_get_path('module', 'ds_extras');
    }
    else {
      $items['node/%node/revisions/%/view']['page callback'] = 'ds_extras_revision_node_show';
      $items['node/%node/revisions/%/view']['file'] = 'ds_extras.pages.inc';
      $items['node/%node/revisions/%/view']['file path'] = drupal_get_path('module', 'ds_extras');
    }
  }

  // Panel view modes.
  if (variable_get('ds_extras_panel_view_modes')) {

    $ds_panels_path = drupal_get_path('module', 'ds_extras');

    if (module_exists('field_ui')) {
      // Convert all manage display screen callbacks.
      foreach (entity_get_info() as $entity_type => $entity_info) {
        if ($entity_info['fieldable']) {
          foreach ($entity_info['bundles'] as $bundle_name => $bundle_info) {
            if (isset($bundle_info['admin'])) {

              // Extract path information from the bundle.
              $path = $bundle_info['admin']['path'];

              if (isset($bundle_info['admin']['bundle argument'])) {
                $bundle_arg = $bundle_info['admin']['bundle argument'];
                $bundle_pos = (string) $bundle_arg;
              }
              else {
                $bundle_arg = $bundle_name;
                $bundle_pos = '0';
              }

              // People can select whether they're going to use Field UI
              // or the Panels editor. So, we are going to delegate
              // this to a custom function which in that case is going
              // to call the right layout callback.
              $items["$path/display"]['page callback'] = 'ds_extras_select_layout_editor';
              $items["$path/display"]['page arguments'] = array($entity_type, $bundle_arg, 'default');
              $items["$path/display"]['file'] = 'ds_extras.admin.inc';
              $items["$path/display"]['file path'] = $ds_panels_path;

              $view_modes = array('default' => array('label' => t('Default'))) + $entity_info['view modes'];
              foreach ($view_modes as $view_mode => $view_mode_info) {
                $items["$path/display/$view_mode"]['page callback'] = 'ds_extras_select_layout_editor';
                $items["$path/display/$view_mode"]['page arguments'] = array($entity_type, $bundle_arg, $view_mode);
                $items["$path/display/$view_mode"]['file'] = 'ds_extras.admin.inc';
                $items["$path/display/$view_mode"]['file path'] = $ds_panels_path;
              }
            }
          }
        }
      }
    }
  }
}

/**
 * Implements hook_entity_info().
 */
function _ds_extras_entity_info() {

  if (!variable_get('ds_extras_vd', FALSE)) {
    return;
  }

  $bundles = array();
  ctools_include('export');
  $vd_settings = ctools_export_crud_load_all('ds_vd');
  foreach ($vd_settings as $key => $vd) {
    $bundles[$vd->vd] = array(
      'label' => check_plain($vd->label),
      'admin' => array('path' => 'admin/structure/ds/vd/' . $vd->vd),
    );
  }

  // Register a views entity on behalf of Views.
  $return = array(
    'ds_views' => array(
      'label' => t('Display suite Views'),
      'bundles' => $bundles,
      'ds_display' => TRUE,
      'base table' => 'views_view',
      'entity keys' => array(
        'id' => 'vid',
        'label' => 'name',
      ),
    ),
  );

  return $return;
}

/**
 * Implements hook_entity_info_alter().
 */
function _ds_extras_entity_info_alter(&$entity_info) {
  $revision = array(
    'label' => 'Revision',
    'custom settings' => FALSE,
  );
  $entity_info['node']['view modes']['revision'] = $revision;
}

/**
 * Implements hook_theme_registry_alter().
 */
function _ds_extras_theme_registry_alter(&$theme_registry) {

  // Add views preprocess layout.
  if (variable_get('ds_extras_vd', FALSE)) {
    $theme_registry['views_view']['preprocess functions'][] = 'ds_extras_preprocess_view_layout';
  }

  // Add process page function.
  if (variable_get('ds_extras_hide_page_title', FALSE)) {
    $theme_registry['page']['process functions'][] = 'ds_extras_process_page_title';
  }

  // Check on field templates.
  if (!variable_get('ds_extras_field_template', FALSE)) {
    $key = array_search('ds_preprocess_field', $theme_registry['field']['preprocess functions']);
    unset($theme_registry['field']['preprocess functions'][$key]);
  }

  // Inject ds_extras_render_panel_layout in all entity theming functions.
  if (variable_get('ds_extras_panel_view_modes')) {
    $entity_info = entity_get_info();

    foreach ($entity_info as $entity => $info) {
      if (isset($entity_info[$entity]['fieldable']) && $entity_info[$entity]['fieldable']) {

        // User uses user_profile for theming.
        if ($entity == 'user') $entity = 'user_profile';

        // Only add preprocess functions if entity exposes theme function.
        if (isset($theme_registry[$entity])) {
          $theme_registry[$entity]['preprocess functions'][] = 'ds_extras_render_panel_layout';
        }
      }
    }

    // Support for Entity API.
    if (isset($theme_registry['entity'])) {
      $theme_registry['entity']['preprocess functions'][] = 'ds_extras_render_panel_layout';
    }
  }
}

/**
 * Implements hook_module_implements_alter().
 */
function _ds_extras_module_implements_alter(&$implementations, $hook) {

  // Because it's possible to turn on/off features for DS extras,
  // we'll unset hooks here if necessary which otherwhise do nothing at all.

  // Field template
  $ft_hooks = array(
    'ds_field_settings_alter',
    'form_ds_styles_form_alter',
    'form_field_ui_field_edit_form_alter',
    'theme',
  );
  if (!variable_get('ds_extras_field_template', FALSE) && in_array($hook, $ft_hooks)) {
    unset($implementations['ds_extras']);
  }

  // Contextual
  $con_hooks = array(
    'contextual_links_view_alter',
    'admin_paths',
  );
  if ((!variable_get('ds_extras_contextual', FALSE) && in_array($hook, $con_hooks)) || !module_exists('field_ui')) {
    unset($implementations['ds_extras']);
  }

  // Region to block
  $region_hooks = array(
    'ds_layout_region_alter',
    'field_attach_view_alter',
    'block_info',
    'block_view'
  );
  if (!variable_get('ds_extras_region_to_block', FALSE) && in_array($hook, $region_hooks)) {
    unset($implementations['ds_extras']);
  }

  // Switch view mode
  $switch_hooks = array(
    'permission',
    'form_node_form_alter',
  );
  if (!variable_get('ds_extras_switch_view_mode', FALSE) && in_array($hook, $switch_hooks)) {
    unset($implementations['ds_extras']);
  }

  // Revision view mode.
  $revision_hooks = array(
    'entity_info_alter',
  );
  if (!variable_get('ds_extras_revision_view_mode', FALSE) && in_array($hook, $revision_hooks)) {
    unset($implementations['ds_extras']);
  }

  // Views displays
  $vd_hooks = array(
    'entity_info',
    'ctools_plugin_api',
    'ds_fields_ui_alter',
  );
  if (!variable_get('ds_extras_vd', FALSE) && in_array($hook, $vd_hooks)) {
    unset($implementations['ds_extras']);
  }

  // Panel view modes.
  $pvm_hooks = array(
    'flush_caches',
    'panels_dashboard_blocks',
    'ds_panels_default_fields',
    'entity_update',
    'entity_delete',
    'ctools_plugin_directory',
    'ctools_plugin_type',
  );
  if (!variable_get('ds_extras_panel_view_modes', FALSE) && in_array($hook, $pvm_hooks)) {
    unset($implementations['ds_extras']);
  }
}
