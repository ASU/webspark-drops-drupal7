<?php

/**
 * @file
 * Administrative functions for DS panels.
 */

/**
 * Menu callback: settings for DS panels.
 */
function ds_panels_view_mode_settings() {
  ctools_include('common', 'panels');
  return drupal_get_form('panels_common_settings', 'panels_ds');
}

/**
 * Manage display screen with panels editor.

 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle_arg
 *   The name of the bundle.
 * @param $view_mode
 *   The name of the view mode.
 */
function ds_panels_field_ui($entity_type, $bundle, $view_mode) {

  $build = array();
  $panel_layout = '';

  // Load ds field ui.
  module_load_include('inc', 'ds', 'ds.field_ui');
  module_load_include('inc', 'ds_extras', 'ds.admin');

  // Get the ds layout. Make sure this does not break in case
  // there was a layout created with Field UI.
  $ds_layout = ds_get_layout($entity_type, $bundle, $view_mode);
  if (!empty($ds_layout) && !isset($ds_layout['settings']['ds_panels'])) {
    $ds_layout = NULL;
  }

  // Check if the layout is added as an extra argument in the URI.
  // Depending on the outcome, the selection tab will display
  // links, a form or the layout edit form.
  $layout_tab_first = FALSE;
  $menu = menu_get_item();
  if (!empty($menu['theme_arguments'])) {
    $layout_tab_first = TRUE;
    $panel_layout = array_shift($menu['theme_arguments']);
  }

  // Check the $panel_layout variable.
  if (!empty($ds_layout)) {
    $panel_layout = $ds_layout['settings']['layout'];
  }

  // If there's a ds layout and panel layout and the layout key is in the URI
  // show the layout change form of panels, else return the form
  // to select the form or update its settings.
  if (!empty($ds_layout) && !empty($panel_layout) && $layout_tab_first) {
    $display = panels_load_display($ds_layout['settings']['did']);
    $display->context = ds_get_entity_context($entity_type);
    $destination = str_replace('/' . $panel_layout, '', $_GET['q']);
    $layout = panels_edit_layout($display, t('Save'), $destination, 'ds_panels');
  }
  else {
    $layout = drupal_get_form('ds_panels_layout', $entity_type, $bundle, $view_mode, $ds_layout, $panel_layout, $layout_tab_first);
  }

  // Content tab.
  $content = ds_panels_content($entity_type, $bundle, $view_mode, $ds_layout, $panel_layout);

  // Move all this stuff into nice vertical tabs.
  $build['tabs'] = array(
    '#type' => 'vertical_tabs',
    '#theme_wrappers' => array('vertical_tabs'),
  );

  $build['tabs']['ds_panels_content'] = array(
    '#type' => 'fieldset',
    '#group' => 'tabs',
    '#title' => t('Content'),
    '#weight' => 0,
  );
  $build['tabs']['ds_panels_content']['content'] = array(
    '#markup' => drupal_render($content),
  );
  $build['tabs']['ds_panels_layout'] = array(
    '#type' => 'fieldset',
    '#group' => 'tabs',
    '#title' => t('Layout'),
    '#weight' => ($layout_tab_first || empty($ds_layout)) ? -1 : 1,
  );
  $build['tabs']['ds_panels_layout']['content'] = array(
    '#markup' => drupal_render($layout)
  );

  // Add the Custom display settings form. We're just going to copy
  // the code from Field UI, because otherwhise we need override to much.
  if ($view_mode == 'default') {
    $view_modes = drupal_get_form('ds_panels_display_settings', $entity_type, $bundle);
    if (!empty($view_modes['view_modes_custom'])) {
      $build['tabs']['view_modes'] = array(
        '#type' => 'fieldset',
        '#group' => 'tabs',
        '#title' => t('Custom display settings'),
        '#weight' => 10,
      );
      $build['tabs']['view_modes']['content'] = array(
        '#markup' => drupal_render($view_modes)
      );
    }
  }

  // Switch to Field UI.
  if (variable_get('ds_extras_editor_switch') && variable_get('ds_extras_panel_view_modes')) {
    $build['tabs']['editor_switch'] = array(
      '#type' => 'fieldset',
      '#group' => 'tabs',
      '#title' => t('Switch editor'),
      '#weight' => 10,
    );
    $query = array('switch' => 'field_ui');
    $switch_link = l(t('Switch to Field UI'), $_GET['q'], array('query' => $query));
    $content = array(
      '#markup' => '<p>' . t('Click on the link underneath to switch to Field UI') . '</p><p>' . $switch_link . '</p>',
    );
    $build['tabs']['editor_switch']['content'] = array(
      '#markup' => drupal_render($content)
    );
  }

  return $build;
}

/**
 * Form callback: Show custom display settings.
 */
function ds_panels_display_settings($form, $form_state, $entity_type, $bundle) {

  $form['#entity_type'] = $entity_type;
  $form['#bundle'] = $bundle;

  $view_mode_admin_access = user_access('admin_view_modes');
  $view_modes = ds_panels_get_enabled_view_modes($entity_type, $bundle);
  if (!empty($view_modes)) {
    $form['view_modes_custom'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Use custom display settings for the following view modes'),
      '#options' => $view_modes['options'],
      '#default_value' => $view_modes['default'],
      '#description' => $view_mode_admin_access ? l(t('Manage view modes'), 'admin/structure/ds/view_modes') : '',
    );
    $form['modes_save'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('ds_panels_display_settings_save'),
    );
    return $form;
  }
}

/**
 * Get enabled view modes for an entity_type and bundle.

 * @param $entity_type
 *   The name of the entity.
 * @param $bundle
 *   The name of the bundle
 *
 * @return $default
 *   A collection of enabled view modes.
 */
function ds_panels_get_enabled_view_modes($entity_type, $bundle) {
  $default = $options = array();
  $entity_info = entity_get_info($entity_type);
  $view_modes = $entity_info['view modes'];
  $view_mode_settings = field_view_mode_settings($entity_type, $bundle);
  foreach ($view_modes as $view_mode_name => $view_mode_info) {
    $options[$view_mode_name] = $view_mode_info['label'];
    if (!empty($view_mode_settings[$view_mode_name]['custom_settings'])) {
      $default[] = $view_mode_name;
    }
  }
  return array(
    'options' => $options,
    'default' => $default
  );
}

/**
 * Submit callback: save custom display settings.
 */
function ds_panels_display_settings_save($form, $form_state) {

  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  module_load_include('inc', 'field_ui', 'field_ui.admin');

  // Get current bundle settings.
  $bundle_settings = field_bundle_settings($entity_type, $bundle);

  $entity_info = entity_get_info($entity_type);
  foreach ($form_state['values']['view_modes_custom'] as $view_mode_name => $value) {
    // Display a message for each view mode newly configured to use custom
    // settings.
    $view_mode_settings = field_view_mode_settings($entity_type, $bundle);
    if (!empty($value) && empty($view_mode_settings[$view_mode_name]['custom_settings'])) {
      $view_mode_label = $entity_info['view modes'][$view_mode_name]['label'];
      $path = _field_ui_bundle_admin_path($entity_type, $bundle) . "/display/$view_mode_name";
      drupal_set_message(t('The %view_mode mode now uses custom display settings. You might want to <a href="@url">configure them</a>.', array('%view_mode' => $view_mode_label, '@url' => url($path))));
      // Initialize the newly customized view mode with the display settings
      // from the default view mode.
      _field_ui_add_default_view_mode_settings($entity_type, $bundle, $view_mode_name, $bundle_settings);
    }
    $bundle_settings['view_modes'][$view_mode_name]['custom_settings'] = !empty($value);
  }

  // Save updated bundle settings.
  field_bundle_settings($entity_type, $bundle, $bundle_settings);

  drupal_set_message(t('Your settings have been saved.'));
}

/**
 * Return the Panels layout settings form.
 */
function ds_panels_layout($form, $form_state, $entity_type, $bundle, $view_mode, $ds_layout, $panel_layout, $layout_tab_first) {

  $form['#entity_type'] = $entity_type;
  $form['#bundle'] = $bundle;
  $form['#view_mode'] = $view_mode;
  $form['#export_id'] = $entity_type . '|' . $bundle . '|' . $view_mode;
  $form['#ds_panels_update'] = !empty($ds_layout) ? TRUE : FALSE;

  // Include panel functions.
  ctools_include('plugins', 'panels');
  ctools_include('common', 'panels');

  // Add css
  $form['#attached']['css'][] = drupal_get_path('module', 'ds_extras') . '/ds_extras.panels.admin.css';

  // When panel_layout is empty, render the layout selector with links.
  if (empty($ds_layout) && empty($panel_layout)) {
    $layout_tab_first = TRUE;
    $layouts = panels_common_get_allowed_layouts('ds_panels');
    // We don't allow the flexible builder from here directly.
    unset($layouts['flexible']);
    $form['layout'] = array(
      '#markup' => '<p>' . t('Select a layout to use for !entity_type > !bundle > !view_mode.<br />You can use flexible layouts, but you need to create them first at !flexible.', array('!entity_type' => $entity_type, '!bundle' => $bundle, '!view_mode' => $view_mode, '!flexible' => url('admin/structure/panels/layouts'))) . '</p>' . panels_common_print_layout_links($layouts, $_GET['q'], array('query' => $_GET))
    );

    // See if we can clone from another view mode.
    $options = array();
    $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
    foreach ($ds_layout_settings as $row) {
      if ($row->entity_type == $entity_type && isset($row->settings['ds_panels'])) {
        $options[$row->id] = drupal_ucfirst($row->entity_type) . ' > ' . drupal_ucfirst($row->bundle) . ' > ' . drupal_ucfirst($row->view_mode);
      }
    }

    if (!empty($options)) {
      $form['clone'] = array(
        '#title' => t('Clone layout from existing view mode'),
        '#type' => 'select',
        '#options' => $options,
      );
      $form['clone_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Clone layout'),
        '#submit' => array('ds_panels_layout_clone'),
      );
    }

    return $form;
  }

  $form['ds_panels_layout']['info'] = array(
    '#markup' => '<p>' . t('Configure settings for the %layout layout.', array('%layout' => $panel_layout)) . '</p>',
  );

  // First time creation of a layout.
  if (!isset($ds_layout['settings']['did'])) {

    // Get the first region of the chosen layout.
    $chosen_layout = panels_get_layout($panel_layout);

    if (isset($chosen_layout['regions'])) {
      $form['ds_panels_layout']['add_default_fields'] = array(
        '#type' => 'checkbox',
        '#title' => t('Add default fields'),
        '#default_value' => TRUE,
      );

      $form['ds_panels_layout']['fields'] = array(
        '#type' => 'fieldset',
        '#title' => t('Default fields'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#attributes' => array('class' => array('default-fallback')),
        '#states' => array(
          'visible' => array(
            'input[name="add_default_fields"]' => array('checked' => TRUE),
          ),
        ),
      );

      // Use prefix and suffixes to create a table here.
      $form['ds_panels_layout']['fields']['configure'] = array(
        '#prefix' => '<table id="ds-panels-layout-table"><th>' . t('Field') . '</th><th>' . t('Pane title') . '</th><th>' . t('Region') . '</th>',
        '#suffix' => '</table>',
      );

      $region_options = $chosen_layout['regions'];
      $region_keys = array_keys($chosen_layout['regions']);

      $i = 1;
      module_load_include('inc', 'field_ui', 'field_ui.admin');
      $fields = module_invoke_all('ds_panels_default_fields', $entity_type, $bundle, $view_mode);
      foreach ($fields as $field_name => $field) {
        $class = ($i % 2) ? 'odd' : 'even';
        $form['ds_panels_layout']['fields']['configure'][$field_name . '_enable'] = array(
          '#type' => 'checkbox',
          '#title' => $field['label'],
          '#default_value' => TRUE,
          '#prefix' => '<tr class=' . $class . '><td>',
        );
        $form['ds_panels_layout']['fields']['configure'][$field_name . '_hide_title'] = array(
          '#type' => 'checkbox',
          '#title' => t('Hide'),
          '#default_value' => TRUE,
          '#prefix' => '</td><td>',
        );
        $form['ds_panels_layout']['fields']['configure'][$field_name . '_region'] = array(
          '#type' => 'select',
          '#options' => $region_options,
          '#default_value' => $region_keys[array_rand($region_keys)],
          '#prefix' => '</td><td>',
          '#suffix' => '</td></tr>'
        );
        $i++;
      }
    }
  }

  $form['ds_panels_layout']['layout'] = array(
    '#type' => 'value',
    '#value' => $panel_layout,
  );

  // Page title functionality, currently only works on nodes.
  if ($form['#entity_type'] == 'node' && ($form['#view_mode'] == 'full' || $form['#view_mode'] == 'revision' || variable_get('ds_extras_switch_view_mode', FALSE)) &&  variable_get('ds_extras_hide_page_title', FALSE)) {
    $form['ds_panels_layout']['ds_layouts']['ds_page_title_options'] = _ds_extras_page_title_options($ds_layout['settings'], $entity_type);
  }

  $form['ds_panels_layout']['css_id'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS ID'),
    '#size' => 30,
    '#description' => t('An ID that can be used by CSS to style the panel.'),
    '#default_value' => isset($ds_layout['settings']['css_id']) ? $ds_layout['settings']['css_id'] : '',
  );

  $form['ds_panels_layout']['class'] = array(
    '#type' => 'textfield',
    '#title' => t('Classes'),
    '#size' => 30,
    '#description' => t('Add classes to the layout. Note that this will only work if the template has a $class variable.'),
    '#default_value' => isset($ds_layout['settings']['class']) ? $ds_layout['settings']['class'] : '',
  );

  if ($entity_type == 'node') {
    $form['ds_panels_layout']['sticky'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add sticky class'),
      '#description' => t('Add a "sticky" class if a node is marked sticky. Only works if the template has a $class variable.'),
      '#default_value' => isset($ds_layout['settings']['sticky']) ? $ds_layout['settings']['sticky'] : '',
    );
  }
  else {
    $form['ds_panels_layout']['sticky'] = array('#type' => 'value', '#value' => FALSE);
  }

  $form['ds_panels_layout']['hide_sidebars'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Drupal blocks/regions'),
    '#description' => t('Check this to have the page disable all sidebar regions displayed in the theme. Note that some themes support this setting better than others. If in doubt, try with stock themes to see.'),
    '#default_value' => isset($ds_layout['settings']['hide_sidebars']) ? $ds_layout['settings']['hide_sidebars'] : FALSE,
  );

  $form['ds_panels_layout']['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save layout'),
    '#submit' => array('ds_panels_layout_save'),
  );

  if (isset($ds_layout['settings']['did'])) {
    $form['#did'] = $ds_layout['settings']['did'];
    $form['ds_panels_layout']['actions']['layout_change'] = array(
      '#type' => 'submit',
      '#value' => t('Change layout'),
      '#submit' => array('ds_panels_layout_change'),
    );
    $form['ds_panels_layout']['actions']['layout_remove'] = array(
      '#type' => 'submit',
      '#value' => t('Remove layout'),
      '#submit' => array('ds_panels_layout_remove'),
    );
  }

  // Check if we need to strip out the panel layout key.
  $form['#strip_off_layout_from_url'] = $layout_tab_first;

  // Add javascript.
  $form['#attached']['js'][] = drupal_get_path('module', 'ds_extras') . '/ds_extras.panels.admin.js';

  return $form;
}

/**
 * Return the panels content manager.
 */
function ds_panels_content($entity_type, $bundle, $view_mode, $ds_layout) {

  if (empty($ds_layout)) {
    return array('#markup' => '<p>' . t('Select a layout first.') . '</p>');
  }

  $did = $ds_layout['settings']['did'];
  ctools_include('common', 'panels');
  $display = panels_load_display($did);
  $display->context = ds_get_entity_context($entity_type);
  $content_types = panels_common_get_allowed_types('panels_ds', $display->context);
  $panel_display = panels_edit($display, $_GET['q'], $content_types);

  // Remove the preview and render the panels content form.
  $panel_display['preview']['#access'] = FALSE;
  return $panel_display;
}

/**
 * Submit callback: Save a layout.
 */
function ds_panels_layout_save($form, &$form_state, $clone = FALSE) {

  // Setup some variables.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Prepare settings.
  $settings = array(
    'css_id' => $form_state['values']['css_id'],
    'class' => $form_state['values']['class'],
    'sticky' => $form_state['values']['sticky'],
    'layout' => $form_state['values']['layout'],
    'hide_sidebars' => $form_state['values']['hide_sidebars'],
    'pipeline' => 'standard',
    'hide_empty_regions' => FALSE,
    'ds_panels' => TRUE,
  );

  // Common panels functions.
  ctools_include('common', 'panels');

  // Create Panels display if this is the first
  // time we're saving the layout. We'll also add
  // common fields as panes to the layout.
  if (!$form['#ds_panels_update']) {

    // Content and context plugins.
    ctools_include('content');
    ctools_include('context');

    $id = 1;

    // Create new display.
    $display = panels_new_display();
    $display->layout = $settings['layout'];
    $display->context = ds_get_entity_context($entity_type);

    // Add default fields if requested.
    if (isset($form_state['values']['add_default_fields']) && $form_state['values']['add_default_fields']) {

      // Get fields to be added on the new display.
      $fields = module_invoke_all('ds_panels_default_fields', $entity_type, $bundle, $view_mode);
      foreach ($fields as $field_name => $field) {

        if (!$form_state['values'][$field_name . '_enable']) {
          continue;
        }

        // Get a random region.
        $region = $form_state['values'][$field_name . '_region'];

        // build pane_id.
        $pane_id = 'new-' . $id;

        // Create new pane.
        $type = (isset($field['field_name'])) ? 'entity_field' : $field['type'];
        $subtype = (isset($field['field_name'])) ? $entity_type . ':' . $field_name : $field['subtype'];
        $pane = panels_new_pane($type, $subtype, TRUE);
        $pane->pid = $pane_id;
        $pane->panel = $region;
        $pane->shown = TRUE;

        // Add configuration.
        $pane->configuration['context'] = 'argument_entity_id:' . $entity_type . '_1';
        if ($form_state['values'][$field_name . '_hide_title']) {
          $pane->configuration['override_title'] = TRUE;
          $pane->configuration['override_title_text'] = '';
        }
        if (isset($field['field_name'])) {
          $field_display = field_get_display($field, $view_mode, array());
          $pane->configuration['formatter'] = $field_display['type'];
        }
        // Add pane to content and panels key of display.
        $display->content[$pane_id] = $pane;
        $display->panels[$region][] = $pane_id;

        $id++;
      }
    }

    // Save display.
    panels_save_display($display);
    $did = $display->did;

    // Add the display id to the layout settings for DS.
    $settings['did'] = $did;
  }
  else {
    $settings['did'] = $form['#did'];
  }

  // Determine the theme function / template for this display.
  $panel_layout = panels_get_layout($form_state['values']['layout']);
  $settings['theme'] = $panel_layout['theme'];

  // Remove old record.
  db_delete('ds_layout_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  // Save new record.
  $record = new stdClass();
  $record->id = $form['#export_id'];
  $record->entity_type = $entity_type;
  $record->bundle = $bundle;
  $record->view_mode = $view_mode;
  $record->layout = $form_state['values']['layout'];
  $record->settings = $settings;

  // Let other modules alter the layout settings.
  drupal_alter('ds_layout_settings', $record, $form_state);

  // Save layout record.
  drupal_write_record('ds_layout_settings', $record);

  // Clear entity info cache.
  cache_clear_all('entity_info', 'cache', TRUE);

  // Show message.
  drupal_set_message(t('The layout has been saved.'));

  // Strip off layout.
  if ($form['#strip_off_layout_from_url']) {
    $form_state['redirect'] = str_replace('/' . $settings['layout'], '', $_GET['q']);
  }
}

/**
 * Submit callback: clone an existing layout.
 */
function ds_panels_layout_clone($form, &$form_state) {
  ctools_include('export');

  $clone = $form_state['values']['clone'];
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

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

  if ($layout) {
    $did = $layout->settings['did'];
    $original = panels_load_display($did);
    $export = panels_export_display($original);
    ob_start();
    eval($export);
    ob_end_clean();

    // Remove fields which are not on the bundle in case
    // it is different. The entity type is ok since, it's
    // not possible to clone from another entity type.
    $original = explode('|', $clone);
    if ($original[1] != $bundle) {
      $orig_bundle_fields = field_info_instances($original[0], $original[1]);
      $new_bundle_fields = field_info_instances($entity_type, $bundle);
      $remove = array_diff(array_keys($orig_bundle_fields), array_keys($new_bundle_fields));
      if (!empty($remove)) {
        foreach ($display->content as $key => $field) {
          if ($field->type == 'entity_field') {
            $compare = str_replace($entity_type . ':', '', $field->subtype);
            if (in_array($compare, $remove)) {
              // Remove from content.
              unset($display->content[$key]);
              // Remove from panels.
              $region = $field->panel;
              $region_key = array_search($key, $display->panels[$region]);
              unset($display->panels[$region][$region_key]);
            }
          }
        }
      }
    }

    // Save the display.
    panels_save_display($display);

    // Save new layout record for ds.
    $settings = $layout->settings;
    $settings['did'] = $display->did;
    $record = new stdClass();
    $record->id = $form['#export_id'];
    $record->entity_type = $entity_type;
    $record->bundle = $bundle;
    $record->view_mode = $view_mode;
    $record->layout = $settings['layout'];
    $record->settings = $settings;

    // Let other modules alter the layout settings.
    drupal_alter('ds_layout_settings', $record, $form_state);

    // Save layout record.
    drupal_write_record('ds_layout_settings', $record);

    // Clear entity info cache.
    cache_clear_all('entity_info', 'cache', TRUE);

    // Show message.
    drupal_set_message(t('The layout has been cloned.'));
  }
  else {
    drupal_set_message(t('No layout was cloned.'));
  }
}

/**
 * Submit callback: Redirect to change the layout.
 */
function ds_panels_layout_change($form, &$form_state) {

  $destination = array();

  // In case there's a redirect, kill it and append it to the redirect.
  if (isset($_GET['destination']) && !empty($_GET['destination'])) {
    $destination = array('query' => array('destination' => $_GET['destination']));
    unset($_GET['destination']);
  }
  $form_state['redirect'] = array($_GET['q'] . '/' . $form_state['values']['layout'], $destination);
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ds_extras_form_panels_change_layout_alter(&$form, $form_state) {
  $form['submit']['#submit'][] = 'ds_panels_layout_change_submit';
  $form['back']['#value'] = t('Cancel');
  $form['back']['#submit'] = array('ds_panels_layout_change_cancel');
}

/**
 * Submit callback: cancel the layout change.
 */
function ds_panels_layout_change_cancel($form, &$form_state) {
  $form_state['redirect'] = $form_state['destination'];
}

/**
 * Submit callback: update the layout.
 */
function ds_panels_layout_change_submit($form, $form_state) {

  $menu = menu_get_item();
  $entity_type = $menu['page_arguments'][0];
  $bundle = field_extract_bundle($entity_type, $menu['page_arguments'][1]);
  $view_mode = $menu['page_arguments'][2];

  ctools_include('export');
  $args = array(
    'entity_type' => $entity_type,
    'bundle' => $bundle,
    'view_mode' => $view_mode,
  );

  $record = ctools_export_load_object('ds_layout_settings', 'conditions', $args);
  if ($record) {

    $lid = $entity_type . '|' . $bundle . '|' . $view_mode;
    $record = $record[$lid];
    $layout = $form_state['layout'];

    // Determine the theme function / template for this display.
    $panel_layout = panels_get_layout($layout);

    // Update record object.
    $record->layout = $layout;
    $record->settings['layout'] = $layout;
    $record->settings['theme'] = $panel_layout['theme'];
    $record->settings['layout'] = $layout;

    // Let other modules alter the layout settings.
    drupal_alter('ds_layout_settings', $record, $form_state);

    // Update record in database.
    drupal_write_record('ds_layout_settings', $record, array('id'));

    // Clear entity info cache.
    cache_clear_all('entity_info', 'cache', TRUE);
  }
}

/**
 * Submit callback: remove a layout.
 */
function ds_panels_layout_remove($form, $form_state) {

  // Setup some variables.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Delete panels display.
  panels_delete_display($form['#did']);

  // Remove old record.
  db_delete('ds_layout_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  // Clear entity info cache.
  cache_clear_all('entity_info', 'cache', TRUE);

  // Show message.
  drupal_set_message(t('The layout has been removed.'));
}
