<?php

/**
 * @file
 * Display Suite Extras administrative functions.
 */

/**
 * Menu callback: Display Suite extras settings.
 */
function ds_extras_settings($form) {

  $form['additional_settings'] = array(
    '#type' => 'vertical_tabs',
    '#theme_wrappers' => array('vertical_tabs'),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  $form['additional_settings']['fs1'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field Templates'),
  );

  $form['additional_settings']['fs1']['ds_extras_field_template'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Field Templates'),
    '#description' => t('Customize the labels and the HTML output of your fields.'),
    '#default_value' => variable_get('ds_extras_field_template', FALSE),
  );

  $theme_functions = module_invoke_all('ds_field_theme_functions_info');
  unset($theme_functions['theme_ds_field_expert']);
  $form['additional_settings']['fs1']['ft-default'] = array(
    '#type' => 'select',
    '#title' => t('Default Field Template'),
    '#options' => $theme_functions,
    '#default_value' => variable_get('ft-default', 'theme_field'),
    '#description' => t('Default will output the field as defined in Drupal Core.<br />Reset will strip all HTML.<br />Minimal adds a simple wrapper around the field.<br/>There is also an Expert Field Template that gives full control over the HTML, but can only be set per field.<br /><br />You can override this setting per field on the "Manage display" screens or when creating fields on the instance level.<br /><br /><strong>Template suggestions</strong><br />You can create .tpl files as well for these field theme functions, e.g. field--reset.tpl.php, field--minimal.tpl.php<br /><br /><label>Styles</label>You can add custom styles on the <a href="!url">styles form</a>. These styles can be added to fields using the Default Field Template.<br /><br /><label>Advanced</label>You can create your own custom field templates which need to be defined with hook_ds_field_theme_functions_info(). See ds.api.php for an example.', array('!url' => url('admin/structure/ds/styles'))),
    '#states' => array(
      'visible' => array(
        'input[name="additional_settings[fs1][ds_extras_field_template]"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['additional_settings']['fs1']['ft-kill-colon'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide colon'),
    '#default_value' => variable_get('ft-kill-colon', FALSE),
    '#description' => t('Hide the colon on the reset field template.'),
    '#states' => array(
      'visible' => array(
        'select[name="additional_settings[fs1][ft-default]"]' => array('value' => 'theme_ds_field_reset'),
        'input[name="additional_settings[fs1][ds_extras_field_template]"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['additional_settings']['fs2'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra fields'),
  );

  $form['additional_settings']['fs2']['ds_extras_fields_extra'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable extra fields'),
    '#description' => t('Make fields from other modules available on the "Manage display" screens.'),
    '#default_value' => variable_get('ds_extras_fields_extra', FALSE),
  );

  $form['additional_settings']['fs2']['ds_extras_fields_extra_list'] = array(
    '#type' => 'textarea',
    '#description' => t('Enter fields line by line, where each line is a combination of entity type, bundle and field name. E.g. node|article|tweetbutton. It might be possible that the actual content of the field depends on configuration of that field/module.'),
    '#default_value' => variable_get('ds_extras_fields_extra_list', FALSE),
    '#states' => array(
      'visible' => array(
        'input[name="additional_settings[fs2][ds_extras_fields_extra]"]' => array('checked' => TRUE),
      ),
    ),
  );

  if (module_exists('panels')) {
    $form['additional_settings']['fs3'] = array(
      '#type' => 'fieldset',
      '#title' => t('Panel view modes'),
    );

    $form['additional_settings']['fs3']['ds_extras_panel_view_modes'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use the Panels editor on the \'Manage Display\' screen'),
      '#description' => t('Use the Panels editor instead of Field UI to manage your layout.'),
      '#default_value' => variable_get('ds_extras_panel_view_modes', FALSE),
    );
    $form['additional_settings']['fs3']['ds_extras_editor_switch'] = array(
      '#type' => 'checkbox',
      '#title' => t('Switch layout editor'),
      '#description' => t('Keep the option to switch between Field UI or Panels. Note: any layout configured already with Field UI will be kept.'),
      '#default_value' => variable_get('ds_extras_editor_switch', FALSE),
      '#states' => array(
        'visible' => array(
          'input[name="additional_settings[fs3][ds_extras_panel_view_modes]"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  $form['additional_settings']['fs4'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other'),
  );

  $form['additional_settings']['fs4']['ds_extras_switch_view_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('View mode per node'),
    '#description' => t('Change view modes for individual nodes. A new tab \'Display settings\' will appear on the content create form.<br />You can also pass the name of a view mode through the URL, eg node/x?v=full.'),
    '#default_value' => variable_get('ds_extras_switch_view_mode', FALSE),
  );

  $form['additional_settings']['fs4']['ds_extras_switch_field'] = array(
    '#type' => 'checkbox',
    '#title' => t('View mode switcher'),
    '#description' => t('Adds a field with links to switch view modes inline with Ajax. Only works for nodes at this time.'),
    '#default_value' => variable_get('ds_extras_switch_field', FALSE),
  );

  $form['additional_settings']['fs4']['ds_extras_revision_view_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Revision view mode'),
    '#description' => t('Make new view mode "Revision" available which can be used to style the revision of a node.'),
    '#default_value' => variable_get('ds_extras_revision_view_mode', FALSE),
  );

  if (module_exists('contextual') && module_exists('field_ui')) {
    $form['additional_settings']['fs4']['ds_extras_contextual'] = array(
      '#type' => 'checkbox',
      '#title' => t('Contextual links'),
      '#description' => t('Add contextual links (if possible) to manage the layout.'),
      '#default_value' => variable_get('ds_extras_contextual', FALSE),
    );
  }

  $form['additional_settings']['fs4']['ds_extras_hide_page_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Page title options'),
    '#description' => t('Hide or manually set the page title of the "Full content" view mode.'),
    '#default_value' => variable_get('ds_extras_hide_page_title', FALSE),
  );

  if (module_exists('block')) {
    $form['additional_settings']['fs4']['ds_extras_region_to_block'] = array(
      '#type' => 'checkbox',
      '#title' => t('Region to block'),
      '#description' => t('Create additional regions exposed as block. Note: this will not work on the default view mode.'),
      '#default_value' => variable_get('ds_extras_region_to_block', FALSE),
    );
  }

  if (module_exists('views')) {
    $form['additional_settings']['fs4']['ds_extras_vd'] = array(
      '#type' => 'checkbox',
      '#title' => t('Views displays'),
      '#description' => t('Manage the layout of your Views layout with Field UI at !url.', array('!url' => l(url('admin/structure/ds/vd', array('absolute' => TRUE)), 'admin/structure/ds/vd'))),
      '#default_value' => variable_get('ds_extras_vd', FALSE),
    );
  }

  $form['#attached']['js'][] = drupal_get_path('module', 'ds_extras') . '/ds_extras.admin.js';

  $form = system_settings_form($form);
  $form['#submit'][] = 'ds_extras_settings_submit';
  return $form;
}

/**
 * Validate callback: Extras settings screen.
 */
function ds_extras_settings_validate($form, &$form_state) {
  foreach ($form_state['values']['additional_settings'] as $tab => $value) {
    if (is_array($value)) {
      foreach ($value as $variable => $val) {
        $form_state['values'][$variable] = $val;
      }
    }
    unset($form_state['values']['additional_settings'][$tab]);
  }
  unset($form_state['values']['additional_settings']);
}

/**
 * Select the editor depending on layout.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle_arg
 *   The position of the bundle argument
 * @param $view_mode
 *   The name of the view mode.
 */
function ds_extras_select_layout_editor($entity_type, $bundle_arg, $view_mode) {

  // Extra the bundle name.
  $bundle = field_extract_bundle($entity_type, $bundle_arg);

  // Check layout.
  $layout = ds_get_layout($entity_type, $bundle, $view_mode);

  // Check switch.
  $panels_editor = TRUE;
  if (variable_get('ds_extras_editor_switch')) {
    if ($layout && !isset($layout['settings']['ds_panels'])) {
      $panels_editor = FALSE;
    }
    if (isset($_GET['switch']) && $_GET['switch'] == 'field_ui') {
      $panels_editor = FALSE;
    }
    if (isset($_GET['switch']) && $_GET['switch'] == 'panels') {
      $panels_editor = TRUE;
    }
  }

  // Select the layout editor.
  if ($panels_editor) {
    module_load_include('inc', 'ds_extras', 'ds_extras.panels');
    return ds_panels_field_ui($entity_type, $bundle, $view_mode);
  }
  else {
    // Use drupal_build_form instead of drupal_get_form.
    $form_state = array();
    $arguments = array($entity_type, $bundle, $view_mode);
    $form_state['build_info']['args'] = $arguments;
    form_load_include($form_state, 'inc', 'field_ui', 'field_ui.admin');
    return drupal_build_form('field_ui_display_overview_form', $form_state);
  }
}

/**
 * Submit callback: Extras settings screen.
 */
function ds_extras_settings_submit($form, &$form_state) {
  cache_clear_all('ds_fields', 'cache');
  cache_clear_all('entity_info:', 'cache', TRUE);
  cache_clear_all('theme_registry:', 'cache', TRUE);
  cache_clear_all('module_implements', 'cache_bootstrap');
  cache_clear_all('field_info_fields', 'cache_field');
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * Alter Manage display screen.
 */
function ds_extras_field_ui_alter(&$form, &$form_state) {

  // Field Template.
  if (variable_get('ds_extras_field_template', FALSE) && isset($form['#ds_layout'])) {

    $field_settings = $form['#field_settings'];
    $field_styles = _ds_styles('ds_styles_fields');
    $functions = module_invoke_all('ds_field_theme_functions_info');
    $default_field_function = variable_get('ft-default', 'theme_field');

    $i = 1;
    foreach (element_children($form['fields']) as $key) {

      // Check if the label is overridden - add the original too.
      if (isset($form['fields'][$key]['human_name'])) {
        $form['fields'][$key]['human_name']['#prefix'] = '<div class="field-label-row"><input type="hidden" class="original-label" value="' . $form['fields'][$key]['human_name']['#markup'] . '">';
        $form['fields'][$key]['human_name']['#suffix'] = '</div>';
        if (isset($field_settings[$key]['ft']['lb'])) {
          $form['fields'][$key]['human_name']['#markup'] = t('@label (Original: @original)', array('@label' => $field_settings[$key]['ft']['lb'], '@original' => $form['fields'][$key]['human_name']['#markup']));
        }
      }

      // Skip those settings for DS views.
      if ($form['#entity_type'] == 'ds_views') {
        continue;
      }

      // Link to open settings.
      $form['fields'][$key]['format']['ft'] = array(
        '#prefix' => '<a href="" class="ft-link">' . t('Field display') . '</a><div class="field-template" id="ft-' . $i . '">',
        '#suffix' => '</div>',
        '#weight' => 50,
      );
      $i++;

      $field_function = isset($field_settings[$key]['ft']['func']) ? $field_settings[$key]['ft']['func'] : $default_field_function;

      // Functions.
      $form['fields'][$key]['format']['ft']['function'] = array(
        '#title' => t('Choose a Field Template'),
        '#type' => 'select',
        '#options' => $functions,
        '#default_value' => $field_function,
        '#attributes' => array(
          'class' => array('ds-extras-field-template'),
        ),
      );

      // Field styles.
      if (!empty($field_styles)) {
        $field_styles_select = array(
          '#type' => 'select',
          '#multiple' => TRUE,
          '#options' => $field_styles,
          '#title' => t('Choose a field style'),
          '#default_value' => isset($field_settings[$key]['ft']['styles']) ? explode(' ', $field_settings[$key]['ft']['styles']) : array(),
          '#prefix' => '<div class="field-styles">',
          '#suffix' => '</div>',
        );
        $form['fields'][$key]['format']['ft']['styles'] = $field_styles_select;
      }
      else {
        $form['fields'][$key]['format']['ft']['styles'] = array(
          '#type' => 'value',
          '#value' => array(''),
        );
      }

      // Wrappers and label.
      $wrappers = array(
        'lb' => array(
          'title' => t('Label'),
        ),
        'ow' => array('title' => t('Outer wrapper')),
        'fis' => array('title' => t('Field items')),
        'fi' => array('title' => t('Field item')),
      );

      $colon_checkbox = FALSE;
      foreach ($wrappers as $wrapper_key => $value) {

        // Hide colon.
        if (!$colon_checkbox) {
          $form['fields'][$key]['format']['ft']['lb-col'] = array(
            '#type' => 'checkbox',
            '#title' => t('Hide colon'),
            '#default_value' => isset($field_settings[$key]['ft']['lb-col']) ? $field_settings[$key]['ft']['lb-col'] : FALSE,
            '#attributes' => array(
              'class' => array('colon-checkbox'),
            ),
          );
          $colon_checkbox = TRUE;
        }

        $form['fields'][$key]['format']['ft'][$wrapper_key] = array(
          '#type' => 'checkbox',
          '#title' => $value['title'],
          '#prefix' => '<div class="ft-group ' . $wrapper_key . '">',
          '#default_value' => isset($field_settings[$key]['ft'][$wrapper_key]) ? TRUE : FALSE,
        );
        $form['fields'][$key]['format']['ft'][$wrapper_key . '-el'] = array(
          '#type' => 'textfield',
          '#title' => t('Element'),
          '#size' => '10',
          '#description' => t('E.g. div, span, h2 etc.'),
          '#default_value' => isset($field_settings[$key]['ft'][$wrapper_key . '-el']) ? $field_settings[$key]['ft'][$wrapper_key . '-el'] : '',
        );
        $classes = array(
          'field-name-' . strtr($key, '_', '-'),
        );
        $form['fields'][$key]['format']['ft'][$wrapper_key . '-cl'] = array(
          '#type' => 'textfield',
          '#title' => t('Classes'),
          '#size' => '10',
          '#suffix' => '</div><div class="clearfix"></div>',
          '#default_value' => isset($field_settings[$key]['ft'][$wrapper_key . '-cl']) ? $field_settings[$key]['ft'][$wrapper_key . '-cl'] : '',
          '#description' => t('Classes: !classes', array('!classes' => implode(', ', $classes))),
        );
      }

      $form['fields'][$key]['format']['ft']['update'] = array(
        '#type' => 'button',
        '#value' => t('Update'),
        '#attributes' => array(
          'class' => array('ft-update'),
        ),
      );

      // Another label needs some other stuff.
      unset($form['fields'][$key]['format']['ft']['lb']['#description']);
      $form['fields'][$key]['format']['ft']['lb']['#type'] = 'textfield';
      $form['fields'][$key]['format']['ft']['lb']['#size'] = '10';
      $form['fields'][$key]['format']['ft']['lb']['#attributes'] = array('class' => array('label-change'));
      $form['fields'][$key]['format']['ft']['lb']['#default_value'] = isset($field_settings[$key]['ft']['lb']) ? $field_settings[$key]['ft']['lb'] : '';
    }
  }

  // Views displays.
  if ($form['#entity_type'] == 'ds_views') {
    // Add an additional submit callback so we can ditch the extra title
    // which is added by ds_extras_field_extra_fields().
    $form['#submit'] = array_merge(array('ds_extras_vd_field_ui_submit'), $form['#submit']);
  }

  // Page title functionality, currently only works on nodes, users and taxonomy terms.
  if (variable_get('ds_extras_hide_page_title', FALSE) && isset($form['#ds_layout']) && in_array($form['#entity_type'], array('node', 'user', 'taxonomy_term')) && ($form['#view_mode'] == 'full' || $form['#view_mode'] == 'revision' || (variable_get('ds_extras_switch_view_mode', FALSE) && $form['#entity_type'] == 'node'))) {
    $form['additional_settings']['ds_layouts']['ds_page_title_options'] = _ds_extras_page_title_options($form['#ds_layout']->settings, $form['#entity_type']);
  }

  // Region to block only fires if there is a layout and we're working on the
  // a view mode which is not equal to default.
  if (isset($form['#ds_layout']) && $form['#view_mode'] != 'default' && variable_get('ds_extras_region_to_block', FALSE)) {

    $layout = $form['#ds_layout'];

    // Get the entity_type, bundle and view mode.
    $entity_type = $form['#entity_type'];
    $bundle = $form['#bundle'];
    $view_mode = $form['#view_mode'];

    $region_blocks_options = array();
    $region_blocks = variable_get('ds_extras_region_blocks', array());
    foreach ($region_blocks as $key => $block) {
      if ($block['info'] == "{$entity_type}_{$bundle}_{$view_mode}") {
        $region_blocks_options[$key] = t('Remove') . ' ' . $block['title'];
      }
    }

    $form['additional_settings']['region_to_block'] = array(
      '#type' => 'fieldset',
      '#title' => t('Block regions'),
      '#description' => t('Create additional regions in this layout which will be exposed as blocks.')
    );

    $form['additional_settings']['region_to_block']['new_block_region'] = array(
      '#type' => 'textfield',
      '#title' => t('Region name'),
      '#description' => t('Enter a name to create a new region.'),
    );
    $form['additional_settings']['region_to_block']['new_block_region_key'] = array(
      '#title' => t('Machine name'),
      '#type' => 'machine_name',
      '#default_value' => '',
      '#maxlength' => 32,
      '#required' => FALSE,
      '#description' => t('The machine-readable name of this block region. This name must contain only lowercase letters and underscores. This name must be unique.'),
      '#disabled' => FALSE,
      '#machine_name' => array(
        'exists' => 'ds_extras_region_to_block_unique',
        'source' => array('additional_settings', 'region_to_block', 'new_block_region'),
      ),
    );

    if (!empty($region_blocks_options)) {
      $form['additional_settings']['region_to_block']['remove_block_region'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Existing block regions'),
        '#options' => $region_blocks_options,
        '#description' => t('Check the regions you want to remove.'),
      );
    }

    $form['#submit'][] = 'ds_extras_block_submit';
  }

  // Editor switch.
  if (variable_get('ds_extras_editor_switch') && variable_get('ds_extras_panel_view_modes')) {

    // Get the entity_type, bundle and view mode.
    $entity_type = $form['#entity_type'];
    $bundle = $form['#bundle'];
    $view_mode = $form['#view_mode'];

    $form['additional_settings']['editor_switch'] = array(
      '#type' => 'fieldset',
      '#group' => 'tabs',
      '#title' => t('Switch editor'),
      '#weight' => 10,
    );
    $query = array('switch' => 'panels');
    $switch_link = l(t('Switch to Panels'), $_GET['q'], array('query' => $query));
    $content = array(
      '#markup' => '<p>' . t('Click on the link underneath to switch to Panels') . '</p><p>' . $switch_link . '</p>',
    );
    $form['additional_settings']['editor_switch']['content'] = array(
      '#markup' => drupal_render($content)
    );
  }
}

/**
 * Implements hook_ds_field_format_summary().
 */
function ds_extras_ds_field_format_summary($field) {
  if (isset($field['formatter_settings'])) {
    foreach ($field['formatter_settings'] as $key => $value) {
      if (!empty($value)) {
        return t('Configured');
        break;
      }
    }
  }
  return t('Not configured');
}

/**
 * Implements hook_ds_field_settings_form().
 */
function ds_extras_ds_field_settings_form($field) {
  $form = array();

  $entity_type = $field['entity_type'];
  $bundle = $field['bundle'];
  $view_mode = $field['view_mode'];
  $settings = isset($field['formatter_settings']) ? $field['formatter_settings'] : array();
  $view_modes = ds_entity_view_modes($entity_type);

  $form['info'] = array(
    '#markup' => t('Enter a label for the link for the view modes you want to switch to.<br />Leave empty to hide link. They will be localized.'),
  );

  foreach ($view_modes as $key => $value) {

    $view_mode_settings = field_view_mode_settings($entity_type, $bundle);
    $visible = !empty($view_mode_settings[$key]['custom_settings']);

    if ($visible) {
      $form[$key] = array(
        '#type' => 'textfield',
        '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
        '#size' => 20,
        '#title' => check_plain($value['label']),
      );
    }
  }

  return $form;
}

/**
 * Implements hook_ds_field_settings_alter().
 */
function ds_extras_ds_field_settings_alter(&$field_settings, $form, &$form_state) {

  $fields = $form_state['values']['fields'];
  $default_field_function = variable_get('ft-default', 'theme_field');

  $wrappers = array(
    'ow' => t('Wrapper'),
    'fis' => t('Field items'),
    'fi' => t('Field item')
  );

  foreach ($fields as $key => $field) {

    // Make sure we need to save anything for this field.
    if (_ds_field_valid($key, $field, $form_state)) {
      continue;
    }

    // Get the values.
    $values = isset($fields[$key]['format']['ft']) ? $fields[$key]['format']['ft'] : array();
    if (empty($values)) {
      continue;
    }

    // Theme output function.
    $function = $values['function'];
    if ($function != $default_field_function) {
      $field_settings[$key]['ft']['func'] = $function;
    }

    // Field styles.
    if ($function != 'theme_ds_field_expert' && $function != 'theme_ds_field_reset') {
      $classes = implode(' ', $values['styles']);
      if (!empty($classes)) {
        $field_settings[$key]['ft']['styles'] = $classes;
      }
    }

    // Label.
    if (isset($fields[$key]['label']) && $fields[$key]['label'] != 'hidden') {
      if (!empty($values['lb'])) {
        $field_settings[$key]['ft']['lb'] = $values['lb'];
      }
      if (!(empty($values['lb-el'])) && $function == 'theme_ds_field_expert') {
        $field_settings[$key]['ft']['lb-el'] = check_plain($values['lb-el']);
      }
      if (!(empty($values['lb-cl'])) && $function == 'theme_ds_field_expert') {
        $field_settings[$key]['ft']['lb-cl'] = check_plain($values['lb-cl']);
      }
      if (!(empty($values['lb-col']))) {
        $field_settings[$key]['ft']['lb-col'] = TRUE;
      }
    }

    // Custom field configuration.
    if ($function == 'theme_ds_field_expert') {
      foreach ($wrappers as $wrapper_key => $title) {
        if ($values[$wrapper_key]) {
          // Enable.
          $field_settings[$key]['ft'][$wrapper_key] = TRUE;
          // Element.
          $field_settings[$key]['ft'][$wrapper_key . '-el'] = !(empty($values[$wrapper_key . '-el'])) ? check_plain($values[$wrapper_key . '-el']) : 'div';
          // Classess.
          $field_settings[$key]['ft'][$wrapper_key . '-cl'] = !(empty($values[$wrapper_key . '-cl'])) ? check_plain($values[$wrapper_key . '-cl']) : '';
        }
      }
    }
  }
}

/**
 * Submit callback after Field UI submission of a views display.
 */
function ds_extras_vd_field_ui_submit($form, &$form_state) {
  // Add the 'type' key to the extra title key so we can ditch the notice.
  $form_state['values']['fields']['title']['type'] = 'hidden';
}

/**
 * Submit callback: manage block regions.
 */
function ds_extras_block_submit($form, &$form_state) {

  // Create new region.
  if (!empty($form_state['values']['additional_settings']['region_to_block']['new_block_region'])) {

    // Get the entity_type, bundle and view mode.
    $entity_type = $form['#entity_type'];
    $bundle = $form['#bundle'];
    $view_mode = $form['#view_mode'];

    $block = array(
      'title' => $form_state['values']['additional_settings']['region_to_block']['new_block_region'],
      'info' => "{$entity_type}_{$bundle}_{$view_mode}",
    );

    $block_key = $form_state['values']['additional_settings']['region_to_block']['new_block_region_key'];
    $region_blocks = variable_get('ds_extras_region_blocks', array());
    $region_blocks[$block_key] = $block;
    variable_set('ds_extras_region_blocks', $region_blocks);
  }

  // Remove a region.
  if (isset($form_state['values']['additional_settings']['region_to_block']['remove_block_region'])) {
    $variable_set = FALSE;
    $region_blocks = variable_get('ds_extras_region_blocks', array());
    $remove = $form_state['values']['additional_settings']['region_to_block']['remove_block_region'];
    foreach ($remove as $key => $value) {
      if ($key === $value) {
        $variable_set = TRUE;
        db_delete('block')
          ->condition('delta', $key)
          ->condition('module', 'ds_extras')
          ->execute();
        unset($region_blocks[$key]);
      }
    }

    if ($variable_set) {
      variable_set('ds_extras_region_blocks', $region_blocks);
    }
  }
}

/**
 * Return unique region to block.
 */
function ds_extras_region_to_block_unique($name) {
  $region_blocks = variable_get('ds_extras_region_blocks', array());
  $value = strtr($name, array('-' => '_'));
  return isset($region_blocks[$value]) ? TRUE : FALSE;
}

/**
 * Helper function to show the page title options. Used in Field UI and Panels editor.
 */
function _ds_extras_page_title_options($settings, $entity_type) {

  $return['page_option_type'] = array(
    '#type' => 'select',
    '#title' => t('Page title'),
    '#options' => array(
      '0' => t('Show'),
      '1' => t('Hide'),
      '2' => t('Manually set'),
    ),
    '#default_value' => isset($settings['hide_page_title']) ? $settings['hide_page_title'] : FALSE,
    '#weight' => 100,
  );

  $contexts = ds_get_entity_context($entity_type);
  $rows = array();
  foreach ($contexts as $context) {
    foreach (ctools_context_get_converters('%' . check_plain($context->keyword) . ':', $context) as $keyword => $title) {
      $rows[] = array(
        check_plain($keyword),
        t('@identifier: @title', array('@title' => $title, '@identifier' => $context->identifier)),
      );
    }
  }

  $return['page_option_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($settings['page_option_title']) ? $settings['page_option_title'] : '',
    '#description' => t('The title, you may use substitutions in this title.'),
    '#weight' => 101,
    '#states' => array(
      'visible' => array(
        ':input[name="page_option_type"]' => array('value' => '2'),
        ':input[name="additional_settings[ds_page_title_options][page_option_type]"]' => array('value' => '2'),
      ),
    ),
  );

  $header = array(t('Keyword'), t('Value'));
  $return['page_option_contexts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Substitutions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#value' => theme('table', array('header' => $header, 'rows' => $rows)),
    '#weight' => 102,
    '#states' => array(
      'visible' => array(
        ':input[name="page_option_type"]' => array('value' => '2'),
        ':input[name="additional_settings[ds_page_title_options][page_option_type]"]' => array('value' => '2'),
      ),
    ),
  );

  return $return;
}
