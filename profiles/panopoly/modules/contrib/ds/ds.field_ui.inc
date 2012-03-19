<?php

/**
 * @file
 * Field UI functions for Display Suite.
 */

/**
 * Adds the Display Suite fields and layouts to the form.
 */
function ds_field_ui_fields_layouts(&$form, &$form_state) {
  global $base_root, $base_path;

  // Get the entity_type, bundle and view mode.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  $form['#export_id'] = $entity_type . '|' . $bundle . '|' . $view_mode;

  // Create vertical tabs.
  ds_field_ui_create_vertical_tabs($form);

  // Add layout fieldset.
  _ds_field_ui_table_layouts($entity_type, $bundle, $view_mode, $form, $form_state);

  // Add the fields on the table.
  if ($view_mode != 'form') {
    _ds_field_ui_fields($entity_type, $bundle, $view_mode, $form, $form_state);
  }

  // Add buttons to add fields in overlay.
  if (isset($form['#ds_layout']) && user_access('admin_fields') && $view_mode != 'form') {
    _ds_field_ui_custom_fields($entity_type, $bundle, $view_mode, $form, $form_state);
  }

  // Special validate function for field group.
  if (isset($form_state['no_field_group'])) {
    array_unshift($form['#validate'], '_ds_field_group_field_ui_fix_notices');
  }

  // Attach js.
  $form['#attached']['js'][] = drupal_get_path('module', 'ds') . '/js/ds.js';

  // Attach css.
  $form['#attached']['css'][] = drupal_get_path('module', 'ds') . '/css/ds.admin.css';

  // Add process function to add the regions.
  $form['#process'][] = 'ds_field_ui_regions';

  // Add a destination so we can get back if layout has been changed.
  $form['ds_source'] = array(
    '#type' => 'hidden',
    '#value' => $base_root . $base_path,
  );
  $form['ds_destination'] = array(
    '#type' => 'hidden',
    '#value' => drupal_get_destination(),
  );
  $form['ds_entity_type'] = array(
    '#type' => 'hidden',
    '#value' => $entity_type,
  );
  $form['ds_bundle'] = array(
    '#type' => 'hidden',
    '#value' => $bundle,
  );
  $form['ds_view_mode'] = array(
    '#type' => 'hidden',
    '#value' => $view_mode,
  );
}

/**
 * Create vertical tabs.
 */
function ds_field_ui_create_vertical_tabs(&$form) {

  // Add additional settings vertical tab.
  if (!isset($form['additional_settings'])) {
    $form['additional_settings'] = array(
      '#type' => 'vertical_tabs',
      '#theme_wrappers' => array('vertical_tabs'),
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#tree' => TRUE,
    );
    $form['#attached']['js'][] = 'misc/form.js';
    $form['#attached']['js'][] = 'misc/collapse.js';
  }

  $view_mode_admin_access = user_access('admin_view_modes');
  if (isset($form['modes'])) {
    if ($view_mode_admin_access) {
      $form['modes']['view_modes_custom']['#description'] = l(t('Manage view modes'), 'admin/structure/ds/view_modes');
    }
    $form['additional_settings']['modes'] = $form['modes'];
    $form['additional_settings']['modes']['#weight'] = -10;
    unset($form['modes']);
  }
  else {
    if ($view_mode_admin_access) {
      $form['additional_settings']['modes']['view_modes_custom']['#description'] = l(t('Manage view modes'), 'admin/structure/ds/view_modes');
    }
  }
}

/**
 * Menu callback: Revert layout and field settings form.
 */
function ds_revert_layout_field_settings_form($form, &$form_state, $id = '') {
  $layout = new stdClass();
  ctools_include('export');
  $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
  if (isset($ds_layout_settings[$id])) {
    $layout = $ds_layout_settings[$id];
  }

  if (isset($layout) && $layout->export_type == 3) {
    $form['#layout'] = $layout;
    return confirm_form($form,
      t('Are you sure you want to revert the layout for %layout?', array('%layout' => implode(', ', explode('|', $layout->id)))),
      drupal_get_destination(),
      t('This action cannot be undone.'),
      t('Revert'),
      t('Cancel')
    );
  }
  else {
    drupal_set_message(t('This operation is not possible.'));
  }
}

/**
 * Submit callback: revert layout and field settings.
 */
function ds_revert_layout_field_settings_form_submit(&$form, &$form_state) {
  $layout = $form['#layout'];

  db_delete('ds_field_settings')
    ->condition('id', $layout->id)
    ->execute();

  db_delete('ds_layout_settings')
    ->condition('id', $layout->id)
    ->execute();

  // Clear the ds_fields cache.
  cache_clear_all('ds_fields', 'cache');
  cache_clear_all('ds_field_settings', 'cache');

  // Clear entity info cache.
  cache_clear_all('entity_info', 'cache', TRUE);

  drupal_set_message(t('Layout has been reverted'));

  $form_state['redirect'] = isset($_GET['destination']) ? $_GET['destination'] : drupal_get_destination();
}

/**
 * Add Regions to 'Manage fields' or 'Manage display' screen.
 *
 * @param $form
 *   The form to add layout fieldset and extra display suite fields.
 * @param $form_state
 *   The current form state.
 */
function ds_field_ui_regions($form, $form_state) {

  // Get the entity_type, bundle and view mode.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Ignore fieldgroup options.
  if (isset($form_state['no_field_group'])) {
    unset($form['fields']['_add_new_group']);
    $form['additional_settings']['field_group']['#access'] = FALSE;
  }

  // Check layout.
  $layout = isset($form['#ds_layout']) ? $form['#ds_layout'] : FALSE;

  // Change UI to add Region column if we have a layout.
  if ($layout) {

    $table = &$form['fields'];

    if ($view_mode != 'form') {
      $table['#header'] = array(
        t('Field'),
        t('Weight'),
        t('Parent'),
        t('Region'),
        t('Label'),
        array('data' => t('Format'), 'colspan' => 3),
      );
    }
    else {
      $table['#header'] = array(
        t('Label'),
        t('Weight'),
        t('Parent'),
        t('Region'),
        t('Name'),
        t('Field'),
        t('Widget'),
        array('data' => t('Operations'), 'colspan' => 2),
      );
    }

    // Remove label and format for views.
    if ($entity_type == 'ds_views') {
      $table['#header'][4] = '';
    }

    $table['#regions'] = array();
    foreach ($layout->regions as $region_key => $region_title) {
      $region_options[$region_key] = $region_title;
      $table['#regions'][$region_key] = array(
        'title' => $region_title,
        'message' => t('No fields are displayed in this region'),
      );
    }

    // Let other modules alter the regions.
    $context = array(
      'entity_type' => $entity_type,
      'bundle' => $bundle,
      'view_mode' => $view_mode
    );
    $region_info = array(
      'region_options' => &$region_options,
      'table_regions' => &$table['#regions'],
    );
    drupal_alter('ds_layout_region', $context, $region_info);

    $region_options['hidden'] = $view_mode != 'form' ? t('Disabled') : t('Hidden');
    $table['#regions']['hidden'] = array(
      'title' => $view_mode != 'form' ? t('Disabled') : t('Hidden'),
      'message' => t('No fields are hidden.')
    );

    $region = array(
      '#type' => 'select',
      '#options' => $region_options,
      '#default_value' => 'hidden',
      '#attributes' => array(
        'class' => array('ds-field-region'),
      )
    );

    $limit_items = array(
      '#type' => 'textfield',
      '#size' => 2,
      '#default_value' => '',
      '#weight' => 10,
      '#default_value' => '#',
      '#prefix' => '<div class="limit-float">',
      '#suffix' => '</div><div class="clearfix"></div>',
      '#attributes' => array(
        'alt' => t('Enter a number to limit the number of items. Leave empty to display them all.'),
        'title' => t('Enter a number to limit the number of items. Leave empty to display them all.'),
      ),
    );

    // Hide this if we formatter_settings_edit is not empty so it doesn't confuse users.
    if (!empty($form_state['formatter_settings_edit'])) {
      $limit_items['#access'] = FALSE;
    }

    // Update existing rows by changing rowHandler and adding regions.
    foreach (element_children($table) as $name) {
      $row = &$table[$name];
      $row['#js_settings'] = array('rowHandler' => 'ds');
      $row['#region_callback'] = 'ds_field_ui_row_region';

      // Remove hidden format.
      if (isset($row['format']['type']['#options']['hidden'])) {
        unset($row['format']['type']['#options']['hidden']);
      }

      // Add label class.
      $row['label']['#attributes']['class'][] = 'label-change';

      // Limit items.
      $field_info = field_info_field($name);
      if (isset($field_info['cardinality']) && $field_info['cardinality'] != 1 && $view_mode != 'form') {
        $row['format']['type']['#prefix'] = '<div class="limit-float">';
        $row['format']['type']['#suffix'] = '</div>';
        $row['format']['limit'] = $limit_items;
        $row['format']['limit']['#default_value'] = (isset($layout->settings['limit']) && isset($layout->settings['limit'][$name])) ? $layout->settings['limit'][$name] : '#';
      }

      // Disable label and format for views.
      if ($entity_type == 'ds_views') {
        $row['label']['#access'] = FALSE;
      }

      // Add region.
      $split = ($view_mode != 'form') ? 7 : 6;
      if ($row['#row_type'] == 'group' && $view_mode == 'form') {
        $split = ($view_mode != 'form') ? 8 : 7;
      }
      $second = array_splice($row, $split);
      $row['region'] = $region;
      $row['region']['#default_value'] = (isset($layout->settings['fields'][$name]) && isset($region_options[$layout->settings['fields'][$name]])) ? $layout->settings['fields'][$name] : 'hidden';
      $row = array_merge($row, $second);
    }
  }

  return $form;
}

/**
 * Returns the region to which a row in the Field UI screen belongs.
 *
 * @param $row
 *   The current row that is being rendered in the Field UI screen.
 */
function ds_field_ui_row_region($row) {
  return isset($row['region']['#value']) ? $row['region']['#value'] : 'hidden';
}

/**
 * Move the view modes so Field UI can handle them.
 */
function ds_field_ui_layouts_validate($form, &$form_state) {
  if (isset($form_state['values']['additional_settings']['modes']['view_modes_custom'])) {
    $form_state['values']['view_modes_custom'] = $form_state['values']['additional_settings']['modes']['view_modes_custom'];
  }
}

/**
 * Change a layout for a given entity.
 *
 * @param $entity_type
 *   The name of the entity.
 * @param $bundle
 *   The name of the bundle.
 * @param $view_mode
 *   The name of the view mode.
 */
function ds_field_ui_layout_change($form, $form_state, $entity_type = '', $bundle = '', $view_mode = '', $new_layout = '') {

  $old_layout = NULL;
  if (!empty($entity_type) && !empty($bundle) && !empty($view_mode)) {
    $old_layout = ds_get_layout($entity_type, $bundle, $view_mode, FALSE);
  }
  $all_layouts = ds_get_layout_info();

  if ($old_layout && isset($all_layouts[$new_layout])) {

    $new_layout_key = $new_layout;
    $new_layout = $all_layouts[$new_layout];

    $form['#entity_type'] = $entity_type;
    $form['#bundle'] = $bundle;
    $form['#view_mode'] = $view_mode;
    $form['#old_layout'] = $old_layout;
    $form['#new_layout'] = $new_layout;
    $form['#new_layout_key'] = $new_layout_key;
    $form['#export_id'] = $entity_type . '|' . $bundle . '|' . $view_mode;

    $form['info'] = array(
      '#markup' => t('You are changing from %old to %new layout for !bundle in !view_mode view mode. On this screen, you can map the old regions to the new regions.', array('%old' => $old_layout['label'], '%new' => $new_layout['label'], '!bundle' => $bundle, '!view_mode' => $view_mode)),
    );

    // Old region options.
    $regions = array();
    foreach ($old_layout['regions'] as $key => $title) {
      $regions[$key] = $title;
    }

    // Let other modules alter the regions.
    // For old regions.
    $context = array(
      'entity_type' => $entity_type,
      'bundle' => $bundle,
      'view_mode' => $view_mode,
    );
    $region_info = array(
      'region_options' => $regions,
    );
    drupal_alter('ds_layout_region', $context, $region_info);
    $regions = $region_info['region_options'];

    // For new regions.
    $region_info = array(
      'region_options' => $new_layout['regions'],
    );
    drupal_alter('ds_layout_region', $context, $region_info);
    $new_layout['regions'] = $region_info['region_options'];
    $form['#new_layout']['regions'] = $new_layout['regions'];

    // Create field selects. Use previous region as default value.
    foreach ($new_layout['regions'] as $region => $region_title) {
      $form['ds_' . $region] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#title' => $region_title,
        '#options' => $regions,
        '#default_value' => $region,
      );
    }

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['actions']['cancel'] = array(
      '#type' => 'link',
      '#title' => t('Cancel'),
      '#href' => isset($_REQUEST['destination']) ? $_REQUEST['destination'] : '',
    );
  }
  else {
    $form['nothing'] = array('#markup' => t('No valid configuration found.'));
  }

  return $form;
}

/**
 * Validate callback: make sure old regions can not be mapped more than once.
 */
function ds_field_ui_layout_change_validate($form, &$form_state) {
  $layout = $form['#old_layout'];
  $new_layout = $form['#new_layout'];

  $mappings = array();
  foreach ($new_layout['regions'] as $new_region => $region_title) {
    $values = $form_state['values']['ds_' . $new_region];
    foreach ($values as $old_region) {
      if (!isset($mappings[$old_region])) {
        $mappings[$old_region] = $old_region;
        if (!isset($mappings['new'][$new_region])) {
          $mappings['new'][$new_region] = array();
        }
        $mappings['new'][$new_region][$old_region] = $old_region;
      }
      else {
        form_set_error('ds_' . $new_region, t('You can not map old regions into multiple new regions.'));
        break;
      }
    }
  }

  // Save the mappings so we can re-use in the submit callback.
  $form_state['mappings'] = isset($mappings['new']) ? $mappings['new'] : array();
}

/**
 * Submit callback: save the layout change.
 */
function ds_field_ui_layout_change_submit($form, &$form_state) {

  // Prepare some variables.
  $old_layout = $form['#old_layout'];
  $new_layout = $form['#new_layout'];
  $new_layout_key = $form['#new_layout_key'];
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];
  $mappings = $form_state['mappings'];

  // Create new record.
  $record = new stdClass();
  $record->id = $form['#export_id'];
  $record->entity_type = $entity_type;
  $record->bundle = $bundle;
  $record->view_mode = $view_mode;
  $record->layout = $new_layout_key;
  $record->settings = $old_layout['settings'];
  unset($record->settings['regions']);
  unset($record->settings['fields']);

  // Remap.
  foreach ($mappings as $new_region => $old_regions) {
    foreach ($old_regions as $region_key) {
      if (isset($old_layout['settings']['regions'][$region_key])) {
        foreach ($old_layout['settings']['regions'][$region_key] as $field_key => $field) {
          if (!isset($record->settings['regions'][$new_region])) {
            $record->settings['regions'][$new_region] = array();
          }
          $record->settings['regions'][$new_region][] = $field;
          $record->settings['fields'][$field] = $new_region;
        }
      }
    }
  }

  // Remove old record.
  db_delete('ds_layout_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  // Save new record.
  drupal_write_record('ds_layout_settings', $record);

  // Clear entity info cache.
  cache_clear_all('entity_info', 'cache', TRUE);

  // Show message.
  drupal_set_message(t('The layout change has been saved.'));
}

/**
 * Save the layout settings from the 'Manage display' screen.
 */
function ds_field_ui_layouts_save($form, &$form_state) {

  // Get some default values.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Determine layout variables.
  $layout = $form_state['values']['additional_settings']['layout'];
  $hide_empty_regions = $form_state['values']['additional_settings']['hide_empty_regions'];
  $hide_sidebars = $form_state['values']['additional_settings']['hide_sidebars'];
  $old_layout = $form_state['values']['additional_settings']['old_layout'];
  $new_layout = ($layout != $old_layout) || empty($old_layout);

  // Save layout and add regions if necessary.
  $record = new stdClass;
  $record->id = $form['#export_id'];
  $record->entity_type = $entity_type;
  $record->bundle = $bundle;
  $record->view_mode = $view_mode;
  $record->layout = $layout;
  $record->settings = array('hide_empty_regions' => $hide_empty_regions, 'hide_sidebars' => $hide_sidebars);

  // Remove old layout if necessary.
  if (($new_layout && !empty($old_layout)) || $form['#panel']) {
    db_delete('ds_layout_settings')
      ->condition('entity_type', $entity_type)
      ->condition('bundle', $bundle)
      ->condition('view_mode', $view_mode)
      ->execute();
  }

  if (($new_layout && !empty($layout)) || ($form['#panel'] && !empty($layout))) {
    // Save new layout.
    $record->settings = $record->settings;

    // Let other modules alter the layout settings.
    drupal_alter('ds_layout_settings', $record, $form_state);

    // Save the record.
    drupal_write_record('ds_layout_settings', $record);
  }
  // Update existing layout.
  elseif (!empty($layout)) {

    $fields = _ds_sort_fields($form_state['values']['fields'], 'weight');

    foreach ($fields as $key => $field) {

      // Make sure we need to save anything for this field.
      if (_ds_field_valid($key, $field, $form_state, $view_mode)) {
        continue;
      }

      if (!isset($record->settings['regions'][$field['region']])) {
        $record->settings['regions'][$field['region']] = array();
      }
      $record->settings['regions'][$field['region']][] = $key;
      $record->settings['fields'][$key] = $field['region'];

      // Save limit.
      $limit = isset($field['format']['limit']) ? trim($field['format']['limit']) : '';
      if (is_numeric($limit)) {
        $record->settings['limit'][$key] = $limit;
      }
    }

    // Save the region classes.
    $record->settings['classes'] = array();
    foreach (array_keys($form['fields']['#regions']) as $region) {

      // Ignore hidden region.
      if ($region == 'hidden') {
        continue;
      }

      // Additional classes on regions.
      if (isset($form_state['values']['additional_settings'][$region])) {
        // Do not save empty string.
        $classes = is_array($form_state['values']['additional_settings'][$region]) ? implode(' ', $form_state['values']['additional_settings'][$region]) : array();
        if (!empty($classes)) {
          $record->settings['classes'][$region] = $form_state['values']['additional_settings'][$region];
        }
      }
    }

    $record->settings = $record->settings;

    // Let other modules alter the layout settings.
    drupal_alter('ds_layout_settings', $record, $form_state);

    $l = $form['#ds_layout'];
    if ($l->export_type == 2) {
      drupal_write_record('ds_layout_settings', $record);
    }
    else {
      drupal_write_record('ds_layout_settings', $record, array('id'));
    }

    // Clear entity info cache.
    cache_clear_all('entity_info', 'cache', TRUE);
  }
}

/**
 * Save the field settings from the 'Manage display' screen.
 */
function ds_field_ui_fields_save($form, &$form_state) {

  // Setup some variables.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Delete previous field configuration configuration.
  db_delete('ds_field_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  $field_settings = array();

  // Save settings for each field.
  $fields = $form['#ds_fields'];
  foreach ($fields as $key => $field) {

    // Field settings.
    $field_values = $form_state['values']['fields'][$field];

    // In case the region is hidden, do not save.
    if (isset($field_values['region']) && $field_values['region'] == 'hidden') {
      continue;
    }

    // Build settings.
    $settings = array();
    $settings['weight'] = $field_values['weight'];
    $settings['label'] = $field_values['label'];
    $settings['format'] = $field_values['format']['type'];

    // Any formatter settings.
    if (isset($form_state['formatter_settings'][$field])) {
      $settings['formatter_settings'] = $form_state['formatter_settings'][$field];
    }

    $field_settings[$field] = $settings;
  }

  // Allow other modules to modify the field settings before they get saved.
  drupal_alter('ds_field_settings', $field_settings, $form, $form_state);

  // Save the record.
  if (!empty($field_settings)) {
    $record = new stdClass;
    $record->id = $form['#export_id'];
    $record->entity_type = $entity_type;
    $record->bundle = $bundle;
    $record->view_mode = $view_mode;
    $record->settings = $field_settings;
    drupal_write_record('ds_field_settings', $record);
  }

  // Clear the ds_fields cache.
  cache_clear_all('ds_fields', 'cache');
  cache_clear_all('ds_field_settings', 'cache');
}

/**
 * Clone a fields layout.
 */
function ds_field_ui_layout_clone($form, &$form_state) {

  $clone = $form_state['values']['additional_settings']['clone'];
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  ctools_include('export');
  $layout = ctools_export_crud_load('ds_layout_settings', $clone);

  // Delete previous layout settings configuration.
  db_delete('ds_layout_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  // Delete previous field configuration configuration.
  db_delete('ds_field_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  // Save new layout record for ds.
  if ($layout) {
    $settings = $layout->settings;
    $record = new stdClass();
    $record->id = $form['#export_id'];
    $record->entity_type = $entity_type;
    $record->bundle = $bundle;
    $record->view_mode = $view_mode;
    $record->layout = $layout->layout;
    $record->settings = $settings;

    // Let other modules alter the layout settings.
    drupal_alter('ds_layout_settings', $record, $form_state);

    // Save layout record.
    drupal_write_record('ds_layout_settings', $record);

    // Clear entity info cache.
    cache_clear_all('entity_info', 'cache', TRUE);

    // Show message.
    drupal_set_message(t('The layout has been cloned. Note that not all settings for all fields have been copied over, you need to check those and save this screen again.'));
  
  }
  else {
    drupal_set_message(t('No layout was cloned.'));
  }
}

/**
 * Creates a summary for the field format configuration summary.
 *
 * @param $field
 *   The configuration of the field.
 *
 * @return $summary
 *   An markup array.
 */
function ds_field_settings_summary($field) {
  $summary = module_invoke($field['module'], 'ds_field_format_summary', $field);
  return array(
    '#markup' => '<div class="field-formatter-summary">' . $summary . '</div>',
    '#cell_attributes' => array('class' => array('field-formatter-summary-cell')),
  );
}

/**
 * Creates a form for Display Suite fields.
 * .
 * @param $field
 *   The field definition.
 *
 * @return $form
 *   A form definition.
 */
function ds_field_settings_form($field) {
  return module_invoke($field['module'], 'ds_field_settings_form', $field);
}

/**
 * Implements hook_ds_field_format_summary().
 */
function ds_ds_field_format_summary($field) {
  $summary = '';
  $settings = isset($field['formatter_settings']) ? $field['formatter_settings'] : $field['properties']['default'];
  foreach ($settings as $key => $value) {
    if ($key == 'ctools') {
      $conf = unserialize($value);
      $summary .= t('Type: !type', array('!type' => check_plain(drupal_ucfirst(str_replace('_', ' ', $conf['subtype'])))));
    }
    elseif (!empty($value)) {
      $value = is_numeric($value) ? ($value ? t('Yes') : t('No')) : check_plain($value);
      $summary .= ' ' . str_replace('_', ' ', drupal_ucfirst(check_plain($key))) . ': ' . check_plain($value) . '<br />';
    }
  }
  return $summary;
}

/**
 * Implements hook_ds_field_settings_form().
 */
function ds_ds_field_settings_form($field) {
  $form = array();

  $settings = isset($field['formatter_settings']) ? $field['formatter_settings'] : $field['properties']['default'];

  foreach ($field['properties']['settings'] as $key => $value) {

    switch ($value['type']) {

      case 'textfield':
        $form[$key] = array(
          '#type' => 'textfield',
          '#title' => str_replace('_', ' ', check_plain(drupal_ucfirst($key))),
          '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
          '#size' => 40,
          '#description' => isset($value['description']) ? check_plain($value['description']) : '',
        );
        break;

      case 'select':
        $form[$key] = array(
          '#type' => 'select',
          '#title' => check_plain(drupal_ucfirst($key)),
          '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
          '#options' => $value['options'],
          '#description' => isset($value['description']) ? check_plain($value['description']) : '',
        );
        break;

      case 'checkbox':
        $form[$key] = array(
          '#type' => 'checkbox',
          '#title' => str_replace('_', ' ', check_plain(drupal_ucfirst($key))),
          '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
          '#description' => isset($value['description']) ? check_plain($value['description']) : '',
        );
        break;

      case 'ctools':
        ctools_include('modal');
        ctools_include('object-cache');
        ctools_modal_add_js();
        $form[$key] = array(
          '#type' => 'hidden',
          '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
          '#weight' => 2,
        );
        $action = 'add';
        $args = '';
        $conf = array();
        $query = array('query' => array('selection' => 1));
        $title = t('Select content');
        if (isset($settings[$key])) {
          $query = array();
          $ctools = unserialize($settings['ctools']);
          $type = $ctools['type'];
          $subtype = $ctools['subtype'];
          $args = '/' . $type . '/' . $subtype;
          $action = 'edit';
          $conf = $ctools['conf'];
          $title = t('Edit content');
        }
        $form['select'] = array(
          '#markup' => '<div class="select-content-link">' . l($title, 'admin/structure/ds/fields/manage_ctools/content/' . $action . '/' . $field['entity_type'] . '/' . $field['name'] . $args, array('attributes' => array('class' => array('ctools-use-modal'))) + $query) . '</div>',
          '#weight' => -10,
        );
        $form['load_terms'] = array(
          '#type' => 'checkbox',
          '#title' => t('Load terms'),
          '#description' => t('Toggle if you are embedding a view with term fields.'),
          '#default_value' => isset($settings['load_terms']) ? $settings['load_terms'] : '',
          '#weight' => -1,
        );
        $form['show_title']['#weight'] = 0;
        $form['title_wrapper']['#weight'] = 1;
        ctools_object_cache_set($field['name'], $field['name'], $conf);
        break;
    }
  }

  return $form;
}

/**
 * Add entity contexts.
 */
function ds_get_entity_context($entity_type) {
  ctools_include('context');
  $arguments = array(
    array(
      'keyword' => $entity_type,
      'identifier' => drupal_ucfirst($entity_type) . ' being viewed',
      'id' => 1,
      'name' => 'entity_id:' . $entity_type,
      'settings' => array(),
    ),
  );

  return ctools_context_get_placeholders_from_argument($arguments);
}

/**
 * Return the configuration settings for the CTools field.
 */
function ds_ctools_content($action = 'add', $entity_type = '', $field_name = '', $type_name = '', $subtype_name = '', $step = NULL) {

  ctools_include('modal');
  ctools_include('ajax');
  ctools_include('content');
  ctools_include('object-cache');

  $commands = array();
  $content_type = ctools_get_content_type($type_name);
  $subtype = ctools_content_get_subtype($content_type, $subtype_name);

  if ($data = ctools_object_cache_get($field_name, $field_name)) {
    $conf = $data;
  }
  else {
    $conf = ctools_content_get_defaults($content_type, $subtype);
  }

  $url = 'admin/structure/ds/fields/manage_ctools/content/' . $action . '/' . $entity_type . '/' . $field_name;
  $base_url = $url;
  if (!empty($type_name) && !empty($subtype_name)) {
    $url .= '/' . $type_name . '/' . $subtype_name . '/%step';
  }
  $form_info = array(
    'path' => $url,
    'show cancel' => TRUE,
    'next callback' => 'ds_ctools_content_next',
  );

  // Get entity context.
  $contexts = ds_get_entity_context($entity_type);

  $form_state = array(
    'contexts' => $contexts,
    'ajax' => TRUE,
    'modal' => TRUE,
    'modal return' => TRUE,
    'field_name' => $field_name,
  );

  // Call the content form.
  $output = ctools_content_form($action, $form_info, $form_state, $content_type, $subtype_name, $subtype, $conf, $step);

  if (!empty($form_state['complete']) || isset($_GET['dismiss'])) {
    $configuration = array(
      'conf' => $form_state['conf'],
      'type' => $type_name,
      'subtype' => $subtype_name,
    );
    $commands[] = ctools_modal_command_dismiss();
    $commands[] = ajax_command_invoke('input[name="fields[' . $field_name . '][settings_edit_form][settings][ctools]"]', 'dsCtoolsContentConfiguration', array(serialize($configuration)));
    $commands[] = ajax_command_invoke('.select-content-link', 'dsCtoolsContentUpdate', array(serialize($configuration)));
    ctools_object_cache_clear($field_name, $field_name);
  }
  // Content selection
  else if (!empty($form_state['cancel']) || isset($_GET['selection'])) {
    ctools_object_cache_clear($field_name, $field_name);
    $commands[] = ds_ctools_content_select($contexts, $field_name, $action, $entity_type);
  }
  // No configuration anymore.
  elseif ($output === FALSE && !isset($_GET['dismiss'])) {
    $output = t('No further configuration exists for this content type.<br/><br/><a href="!close_modal" class="use-ajax">Click here to close the modal and save the settings.</a><br/><br/><a href="!new_content" class="use-ajax">Click here to select new content</a>.', array('!new_content' => url($base_url, array('query' => array('selection' => TRUE))), '!close_modal' => url($url, array('query' => array('dismiss' => 1)))));
    $commands[] = ctools_modal_command_display(t('Edit content'), $output);
  }
  // Form render.
  else {
    $commands = ctools_modal_form_render($form_state, $output);
  }

  print ajax_render($commands);
  ajax_footer();
  exit;
}

/**
 * Handle the 'next' click on the add/edit field form wizard.
 */
function ds_ctools_content_next(&$form_state) {
  ctools_object_cache_set($form_state['field_name'], $form_state['field_name'], $form_state['conf']);
}

/**
 * Select content.
 *
 * @param $contexts
 *   A collection of contexts, usually the entity.
 * @param $field_name
 *   The name of the field.
 * @param $action
 *   The name of the action.
 * @param $entity_type
 *   The name of the entity type.
 */
function ds_ctools_content_select($contexts, $field_name, $action, $entity_type) {

  // Get content types.
  $content_types = ctools_content_get_available_types($contexts);

  $categories = $category_names = $ordered = array();

  foreach ($content_types as $type_name => $subtypes) {
    foreach ($subtypes as $subtype_name => $content_type) {
      list($category_key, $category) = ds_ctools_get_category($content_type);

      if (empty($categories[$category_key])) {
        $categories[$category_key] = array(
          'title' => $category,
          'content' => array(),
        );
        $category_names[$category_key] = $category;
      }

      $content_title = filter_xss_admin($content_type['title']);

      // Ensure content with the same title doesn't overwrite each other.
      while (isset($categories[$category_key]['content'][$content_title])) {
        $content_title .= '-';
      }

      $categories[$category_key]['content'][$content_title] = $content_type;
      $categories[$category_key]['content'][$content_title]['type_name'] = $type_name;
      $categories[$category_key]['content'][$content_title]['subtype_name'] = $subtype_name;
    }
  }

  // Now sort
  natcasesort($category_names);
  foreach ($category_names as $category => $name) {
    $ordered[$category] = $categories[$category];
  }

  $left = '';
  $right = '<div class="content">' . t('Content options are divided by category. Please select a category from the left to proceed.') . '</div>';
  foreach ($ordered as $section => $section_content) {
    // Section.
    if ($section == 'root') {
      $section_content['title'] = t('Content');
    }
    $left .= '<div class="section"><a href="" id="' . $section . '" class="section-link">' . $section_content['title'] . '</a></div>';
    // Content.
    $right .= '<div id="' . $section . '-container" class="selection-hide content">';
    $right .= '<h2>' . $section_content['title'] . '</h2>';
    foreach ($section_content['content'] as $key => $value) {
      $right .= '<div class="content-item">';
      $variables = array(
        'path' => ctools_content_admin_icon($value),
      );
      $right .= theme('image', $variables) . '&nbsp;';
      $right .= ctools_ajax_text_button($key, 'admin/structure/ds/fields/manage_ctools/content/' . $action . '/' . $entity_type . '/' . $field_name . '/' . $value['type_name'] . '/' . $value['subtype_name'], $key);
      $right .= '</div>';
    }
    $right .= '</div>';
  }

  // Create output.
  $output = '<div id="ctools-content-selection">';
  $output .= '<div id="ds-left">' . $left . '</div>';
  $output .= '<div id="ds-right">' . $right . '</div>';
  $output .= '</div>';

  return ctools_modal_command_display(t('Select content'), $output);
}

/**
 * Helper function to get the category.
 */
function ds_ctools_get_category($content_type) {
  if (isset($content_type['top level'])) {
    $category = 'root';
  }
  elseif (isset($content_type['category'])) {
    if (is_array($content_type['category'])) {
      list($category, $weight) = $content_type['category'];
    }
    else {
      $category = $content_type['category'];
    }
  }
  else {
    $category = t('Uncategorized');
  }

  return array(preg_replace('/[^a-z0-9]/', '-', drupal_strtolower($category)), $category);
}

/**
 * Handles ctools modal Add field
 *
 * @param $js
 *  Whether js is used or not.
 * @param $field_type
 *   The name of the field type.
 */
function ds_ajax_add_field($js, $field_type) {

  if (!$js) {
    // We don't support degrading this from js because we're not
    // using the server to remember the state of the table.
    drupal_goto("admin/structure/ds/fields/" . $field_type);
    return;
  }

  ctools_include('ajax');
  ctools_include('modal');

  switch ($field_type) {

    case "manage_ctools":
      $title = t('Add a dynamic field');
      $form_name = "ds_edit_ctools_field_form";
      break;

    case "manage_preprocess":
      $title = t('Add a preprocess field');
      $form_name = "ds_edit_preprocess_field_form";
      break;

    case "manage_block":
      $title = t('Add a block field');
      $form_name = "ds_edit_block_field_form";
      break;

    default:
      $title = t('Add a code field');
      $form_name = "ds_edit_custom_field_form";
      $field_type = 'manage_custom';
      break;
  }

  $form_state = array();
  $form_state['build_info']['args'] = array();
  $form_state += array(
    'title' => $title,
    'ajax' => TRUE,
    're_render' => FALSE,
  );

  $output = NULL;
  form_load_include($form_state, 'inc', 'ds', 'ds.fields');

  $output = ctools_modal_form_wrapper($form_name, $form_state);

  // Field is saved.
  if ($form_state['executed']) {

    $output = array();

    // Do not print messages on screen.
    if ($messages = theme('status_messages')) {
      $output[] = ajax_command_append('#console', $messages);
    }

    // Close the modal.
    $output[] = ctools_modal_command_dismiss();

    // Call our own javascript function which will trigger a refresh of the table.
    $output[] = ajax_command_invoke('#field-display-overview', 'dsRefreshDisplayTable');
  }

  drupal_add_http_header('Content-Type', 'application/json');
  print ajax_render($output);
  exit;
}

/**
 * Add fake field group value in.
 */
function _ds_field_group_field_ui_fix_notices($form, &$form_state) {
  $field_group = array(
    'group_name' => '',
    'label' => '',
  );
  $form_state['values']['fields']['_add_new_group'] = $field_group;
}

/**
 * Add the layouts fieldset on the Field UI screen.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle
 *   The name of the bundle
 * @param $view_mode
 *   The name of the view_mode
 * @param $form
 *   A collection of form properties.
 */
function _ds_field_ui_table_layouts($entity_type, $bundle, $view_mode, &$form, $form_state) {

  $layout_options = array();
  $ds_layouts = ds_get_layout_info();
  $layout_options = array('' => t('- None -'));
  foreach ($ds_layouts as $key => $layout) {
    $optgroup = 'Display suite';

    // Continue if view mode is form and the form property is not ok.
    if ($view_mode == 'form' && (!isset($layout['form']) || (isset($layout['form']) && !$layout['form']))) {
      continue;
    }
    elseif ($view_mode != 'form' && isset($layout['form']) && $layout['form']) {
      continue;
    }

    // Panels can not be used on Views fields.
    if (!empty($layout['module']) && $layout['module'] == 'panels' && isset($form_state['no_panels'])) {
      continue;
    }

    // Create new layout optoin group.
    if (!empty($layout['module'])) {
      $optgroup = drupal_ucfirst($layout['module']);
    }

    if (!isset($layout_options[$optgroup])) {
      $layout_options[$optgroup] = array();
    }

    // Stack the layout.
    $layout_options[$optgroup][$key] = $layout['label'];
  }

  // If there is only one $optgroup, move it to the root.
  if (count($layout_options) == 2) {
    $options = $layout_options[$optgroup];
    $layout_options = array_merge(array('' => t('- None -')), $options);
  }

  // Add layouts form.
  $form['additional_settings']['ds_layouts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout for !bundle in !view_mode', array('!bundle' => str_replace('_', ' ', $bundle), '!view_mode' => str_replace('_', ' ', $view_mode))),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#parents' => array('additional_settings'),
  );

  ctools_include('export');
  $layout = new stdClass();
  $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
  $form['#panel'] = FALSE;
  if (isset($ds_layout_settings[$form['#export_id']])) {
    $layout = $ds_layout_settings[$form['#export_id']];
    // Make sure this does not break in case there was
    // a layout created with Panel view modes.
    if (isset($layout->settings['ds_panels'])) {
      $layout = NULL;
      $form['#panel'] = TRUE;
    }
  }

  if (!empty($layout) && isset($layout->layout) && isset($ds_layouts[$layout->layout])) {
    $chosen_layout = $ds_layouts[$layout->layout];
    $layout_string = $layout->layout;
    if (empty($chosen_layout['flexible'])) {
      $selected = t('You have selected the %layout_label layout. The default template can be found in %path', array('%layout_label' => $chosen_layout['label'], '%path' => $chosen_layout['path']));
      $suggestions = 'Possible template suggestions are:<ul>';
      $suggestions .= '<li>' . $layout_string . '--' . $entity_type . '.tpl.php</li>';
      $suggestions .= '<li>' . $layout_string . '--' . $entity_type . '-' . $bundle . '.tpl.php</li>';
      if (!isset($form_state['no_view_mode_suggestions'])) {
        $suggestions .= '<li>' . $layout_string . '--' . $entity_type . '-' . $bundle . '-' . $view_mode . '.tpl.php</li></ul>';
      }
    }
    else {
      $suggestions = '';
      $selected = t('You have selected the flexible %layout_label layout.', array('%layout_label' => $chosen_layout['label'], '%path' => $chosen_layout['path']));
    }
    $layout->settings = $layout->settings;
    $layout->regions = $chosen_layout['regions'];
    $form['#ds_layout'] = $layout;
  }

  $form['additional_settings']['ds_layouts']['layout'] = array(
    '#type' => 'select',
    '#title' => t('Select a layout'),
    '#options' => $layout_options,
    '#default_value' => isset($layout->layout) ? $layout->layout : '',
    '#weight' => -1,
  );

  // Apply button.
  if (isset($layout->layout)) {
    $form['additional_settings']['ds_layouts']['ds_layout_apply'] = array(
      '#type' => 'submit',
      '#value' => t('Apply'),
      '#disabled' => TRUE,
      '#weight' => 0,
    );
  }

  if (isset($layout->export_type) && $layout->export_type == 3) {
    $form['additional_settings']['ds_layouts']['revert'] = array(
      '#markup' => l(t('This layout is overridden. Click to revert to default settings.'), 'admin/structure/ds/revert-layout/' . $form['#export_id'], array('query' => drupal_get_destination())),
      '#weight' => 1,
    );
  }

  $form['additional_settings']['ds_layouts']['hide_empty_regions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide empty regions'),
    '#default_value' => isset($layout->settings['hide_empty_regions']) ? $layout->settings['hide_empty_regions'] : FALSE,
    '#weight' => 2,
    '#access' => empty($chosen_layout['flexible']),
  );

  $form['additional_settings']['ds_layouts']['hide_sidebars'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Drupal blocks/regions'),
    '#description' => t('Check this to have the page disable all sidebar regions displayed in the theme. Note that some themes support this setting better than others. If in doubt, try with stock themes to see.'),
    '#default_value' => isset($layout->settings['hide_sidebars']) ? $layout->settings['hide_sidebars'] : FALSE,
    '#access' => $view_mode != 'form',
    '#weight' => 3,
  );

  if (!empty($layout) && isset($layout->regions)) {
    $form['additional_settings']['ds_layouts']['suggestions'] = array(
      '#markup' => '<p>' . $selected . '</p><p>' . t('!suggestions', array('!suggestions' => strtr($suggestions, '_', '-'))) . '</p>',
    );

    // Add extra classes for the regions to have more control while theming.
    $form['additional_settings']['ds_classes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Extra classes for regions'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#parents' => array('additional_settings'),
      '#access' => empty($chosen_layout['flexible']),
    );

    $styles = _ds_styles();
    if (!empty($styles)) {
      foreach (array_keys($layout->regions) as $region) {
        $form['additional_settings']['ds_classes'][$region] = array(
          '#type' => 'select',
          '#multiple' => TRUE,
          '#options' => $styles,
          '#title' => t('Class for @region', array('@region' => $region)),
          '#default_value' => isset($layout->settings['classes'], $layout->settings['classes'][$region]) ? $layout->settings['classes'][$region] : '',
        );
      }
      $form['additional_settings']['ds_classes']['info'] = array('#markup' => l(t('Manage region styles'), 'admin/structure/ds/styles', array('query' => drupal_get_destination())));
    }
    else {
      $form['additional_settings']['ds_classes']['info'] = array('#markup' => '<p>' . t('You have not defined any styles which can be used on regions.') . '</p><p>' . l(t('Manage region styles'), 'admin/structure/ds/styles', array('query' => drupal_get_destination())) . '</p>');
    }
  }
  else {

    if ($view_mode != 'form') {
      // See if we can clone from another view mode.
      $options = array();
      $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
      foreach ($ds_layout_settings as $row) {
        // Do not clone from form layouts.
        if ($row->view_mode == 'form') {
          continue;
        }
        if ($row->entity_type == $entity_type && !isset($row->settings['ds_panels'])) {
          $options[$row->id] = drupal_ucfirst($row->entity_type) . ' > ' . drupal_ucfirst($row->bundle) . ' > ' . drupal_ucfirst($row->view_mode);
        }
      }

      if (!empty($options)) {

        // Clone from another layout.
        $form['additional_settings']['ds_clone'] = array(
          '#type' => 'fieldset',
          '#title' => t('Clone layout'),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
          '#parents' => array('additional_settings'),
        );
        $form['additional_settings']['ds_clone']['clone'] = array(
          '#title' => t('Select an existing layout to clone.'),
          '#type' => 'select',
          '#options' => $options,
          '#weight' => 20,
          '#description' => t('Note that not all fields might be available.'),
        );
        $form['additional_settings']['ds_clone']['clone_submit'] = array(
          '#type' => 'submit',
          '#value' => t('Clone layout'),
          '#submit' => array('ds_field_ui_layout_clone'),
          '#weight' => 21,
        );
      }
    }
  }

  $form['additional_settings']['ds_layouts']['id'] = array(
    '#type' => 'value',
    '#value' => isset($layout->id) ? $layout->id : $form['#export_id'],
  );

  $form['additional_settings']['ds_layouts']['old_layout'] = array(
    '#type' => 'value',
    '#value' => isset($layout->layout) ? $layout->layout : 0,
  );

  // Add validate and submit handlers. Layout needs be first so
  // we can reset the type key for Field API fields.
  $form['#validate'][] = 'ds_field_ui_layouts_validate';
  $submit = $form['#submit'];
  $form['#submit'] = array('ds_field_ui_layouts_save');
  $form['#submit'] = array_merge($form['#submit'], $submit);
}

/**
 * Add the fields to the Field UI form.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle
 *   The name of the bundle
 * @param $view_mode
 *   The name of the view_mode
 * @param $form
 *   A collection of form properties.
 * @param $form_state
 *   A collection of form_state properties.
 */
function _ds_field_ui_fields($entity_type, $bundle, $view_mode, &$form, &$form_state) {

  // Do not add the fields if there is no layout.
  if (!isset($form['#ds_layout'])) {
    return;
  }

  // Get the fields and put them on the form.
  $fields = ds_get_fields($entity_type, FALSE);

  // Ultimate alter on Field UI fields, only used for edge cases.
  $context = array(
    'entity_type' => $entity_type,
    'bundle' => $bundle,
    'view_mode' => $view_mode,
  );
  // Load views file if entity type is not ds_views.
  // We need to cache the hook it's implementing.
  if ($entity_type != 'ds_views' && module_exists('ds_extras') && variable_get('ds_extras_vd', FALSE)) {
    module_load_include('inc', 'ds_extras', 'ds_extras.vd');
  }
  drupal_alter('ds_fields_ui', $fields, $context);

  // Get field settings.
  $field_settings = ds_get_field_settings($entity_type, $bundle, $view_mode, FALSE);
  $form['#field_settings'] = $field_settings;

  $table = &$form['fields'];
  $form['#ds_fields'] = array();

  $field_label_options = array(
    'above' => t('Above'),
    'inline' => t('Inline'),
    'hidden' => t('<Hidden>'),
  );
  drupal_alter('ds_label_options', $field_label_options);

  foreach ($fields as $key => $field) {

    // Check on ui_limit.
    if (isset($field['ui_limit'])) {

      $continue = TRUE;
      foreach ($field['ui_limit'] as $limitation) {
        list($limit_bundle, $limit_view_mode) = explode('|', $limitation);
        if ($limit_bundle == '*' || $limit_bundle == $bundle) {
          if ($limit_view_mode == '*' || $limit_view_mode == $view_mode) {
            $continue = FALSE;
          }
        }
      }

      if ($continue) {
        continue;
      }
    }

    $form['#ds_fields'][] = $key;

    // Check on formatter settings.
    if (isset($form_state['formatter_settings'][$key])) {
      $field['formatter_settings'] = $form_state['formatter_settings'][$key];
    }
    elseif (isset($field_settings[$key]['formatter_settings'])) {
      $field['formatter_settings'] = $field_settings[$key]['formatter_settings'];
      $form_state['formatter_settings'][$key] = $field['formatter_settings'];
    }

    $hidden = array('hidden' => t('<Hidden>'));
    $formatters = isset($field['properties']['formatters']) ? $hidden + $field['properties']['formatters'] : $hidden + array('default' => t('Default'));

    $table[$key] = array(
      '#row_type' => 'field',
      '#js_settings' => array('field'),
      '#region_callback' => 'field_ui_display_overview_row_region',
      '#attributes' => array('class' => array('draggable', 'tabledrag-leaf')),
      'human_name' => array(
        '#markup' => check_plain($field['title']),
      ),
      'weight' => array(
        '#type' => 'textfield',
        '#default_value' => isset($field_settings[$key]['weight']) ? $field_settings[$key]['weight'] : 0,
        '#size' => 3,
        '#attributes' => array('class' => array('field-weight')),
      ),
      'parent_wrapper' => array(
        'parent' => array(
          '#type' => 'select',
          '#empty_value' => '',
          '#options' => array(),
          '#attributes' => array('class' => array('field-parent')),
          '#parents' => array('fields', $key, 'parent'),
        ),
        'hidden_name' => array(
          '#type' => 'hidden',
          '#default_value' => $key,
          '#attributes' => array('class' => array('field-name')),
        ),
      ),
      'label' => array(
        '#type' => 'select',
        '#options' => $field_label_options,
        '#default_value' => isset($field_settings[$key]['label']) ? $field_settings[$key]['label'] : 'hidden',
      ),
      'format' => array(
        'type' => array(
          '#type' => 'select',
          '#options' => $formatters,
          '#default_value' => isset($field_settings[$key]['format']) ? $field_settings[$key]['format'] : 'hidden',
          '#attributes' => array('class' => array('field-formatter-type')),
        ),
      ),
      'settings_summary' => array(),
      'settings_edit' => array(),
    );

    // Not all fields have settings.
    if (!isset($field['properties']['settings'])) {
      continue;
    }

    $base_button = array(
      '#submit' => array('field_ui_display_overview_multistep_submit'),
      '#ajax' => array(
        'callback' => 'field_ui_display_overview_multistep_js',
        'wrapper' => 'field-display-overview-wrapper',
        'effect' => 'fade',
      ),
      '#field_name' => $key,
    );

    if ($form_state['formatter_settings_edit'] == $key) {
      $field['name'] = $key;
      $field['entity_type'] = $entity_type;
      $field['bundle'] = $bundle;
      $field['view_mode'] = $view_mode;
      $table[$key]['settings_edit'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('field-formatter-settings-edit-form')),
        '#parents' => array('fields', $key, 'settings_edit_form'),
        '#weight' => -5,
        'label' => array(
          '#markup' => '<h3>' . t('Field settings') . '</h3>',
        ),
        // Create a settings form where hooks can pick in.
        'settings' => ds_field_settings_form($field),
        'actions' => array(
          '#type' => 'actions',
          'save_settings' => $base_button + array(
            '#type' => 'submit',
            '#name' => $key . '_formatter_settings_update',
            '#value' => t('Update'),
            '#op' => 'update',
          ),
          'cancel_settings' => $base_button + array(
            '#type' => 'submit',
            '#name' => $key . '_formatter_settings_cancel',
            '#value' => t('Cancel'),
            '#op' => 'cancel',
            // Do not check errors for the 'Cancel' button.
            '#limit_validation_errors' => array(),
          ),
        ),
      );
      $table[$key]['#attributes']['class'][] = 'field-formatter-settings-editing';
      $table[$key]['format']['type']['#attributes']['class'] = array('element-invisible');
    }
    else {
      // After saving, the settings are updated here aswell. First we create
      // the element for the table cell.
      $table[$key]['settings_summary'] = ds_field_settings_summary($field);
      // Add the configure button.
      $table[$key]['settings_edit'] = $base_button + array(
        '#type' => 'image_button',
        '#name' => $key . '_group_settings_edit',
        '#src' => 'misc/configure.png',
        '#attributes' => array('class' => array('field-formatter-settings-edit'), 'alt' => t('Edit')),
        '#op' => 'edit',
        // Do not check errors for the 'Edit' button.
        '#limit_validation_errors' => array(),
        '#prefix' => '<div class="field-formatter-settings-edit-wrapper">',
        '#suffix' => '</div>',
      );
    }
  }

  // Add fields submit handler.
  $form['#submit'][] = 'ds_field_ui_fields_save';
}

/**
 * Add tab for adding new fields on the fly.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle
 *   The name of the bundle
 * @param $view_mode
 *   The name of the view_mode
 * @param $form
 *   A collection of form properties.
 * @param $form_state
 *   A collection of form_state properties.
 */
function _ds_field_ui_custom_fields($entity_type, $bundle, $view_mode, &$form, $form_state) {

  $form['additional_settings']['add_custom_fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add custom fields'),
    '#description' => t('Click on one of the buttons to create a new field.') . '<p></p>',
    '#access' => user_access('admin_fields'),
  );

  // Include the CTools tools that we need.
  ctools_include('ajax');
  ctools_include('modal');

  // Add CTools' javascript to the page.
  ctools_modal_add_js();

  $field_types = array(
    'custom_field' => t('Add a code field'),
    'manage_ctools' => t('Add a dynamic field'),
  );
  if (module_exists('block')) {
    $field_types['manage_block'] = t('Add a block field');
  }
  $field_types['manage_preprocess'] = t('Add a preprocess field');

  foreach ($field_types as $field_key => $field_title) {

    $form['ctools_add_field_' . $field_key . '_url'] = array(
      '#type' => 'hidden',
      '#attributes' => array('class' => array('ctools_add_field_' . $field_key . '-url')),
      '#value' => url('admin/structure/ds/nojs/add_field/' . $field_key),
    );

    $form['additional_settings']['add_custom_fields']['ctools_add_field_' . $field_key] = array(
      '#type' => 'button',
      '#value' => $field_title,
      '#attributes' => array('class' => array('ctools-use-modal')),
      '#id' => 'ctools_add_field_' . $field_key,
    );
  }
}

/**
 * Utility function to check if we need to save anything for this field.
 */
function _ds_field_valid($key, $field, &$form_state, $view_mode = 'default') {
  $continue = FALSE;

  // Ignore the Field group module and the region to block plugin.
  if ($key == '_add_new_group' || $key == '_add_new_field' || $key == '_add_new_block_region') {
    $continue = TRUE;
  }

  // If the field is in hidden region, do not save. Check if the
  // field has a type key which means it's from Field API and
  // we need to reset that type to 'hidden' so it doesn't get
  // fired by Field API in the frontend.
  if (isset($field['region']) && $field['region'] == 'hidden') {
    if (isset($field['type']) && $view_mode != 'form') {
      $form_state['values']['fields'][$key]['type'] = 'hidden';
    }

    // In case of a form, fields will be set with #access to FALSE.
    if ($view_mode != 'form') {
      $continue = TRUE;
    }
  }

  return $continue;
}

/**
 * Utility function to return styles.
 */
function _ds_styles($name = 'ds_styles_regions') {
  static $styles = array();

  if (!isset($styles[$name])) {
    $styles[$name] = array();
    $custom_styles = trim(variable_get($name, ''));
    if (!empty($custom_styles)) {
      $styles[$name][''] = t('None');
      $custom_styles = explode("\n", $custom_styles);
      foreach ($custom_styles as $key => $value) {
        $classes = explode("|", $value);
        $key = trim($classes[0]);
        $friendly_name = isset($classes[1]) ? trim($classes[1]) : $key;
        $styles[$name][check_plain($key)] = $friendly_name;
      }
    }
  }

  return $styles[$name];
}

/**
 * Utility function to sort a multidimensional array by a value in a sub-array.
 *
 * @param $a
 *   The array to sort.
 * @param $subkey
 *   The subkey to sort by.
 */
function _ds_sort_fields($a, $subkey) {
  foreach ($a as $k => $v) {
    if (isset($v[$subkey])) {
      $b[$k] = $v[$subkey];
    }
  }
  asort($b);
  foreach ($b as $key => $val) {
    $c[$key] = $a[$key];
  }
  return $c;
}

