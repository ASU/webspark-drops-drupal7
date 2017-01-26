<?php

/**
 * Implements hook_theme()
 */
function asu_dept_picker_theme() {
  return array(
    'asu_dept_picker' => array(
      'render element' => 'element',
      'file' => 'inc/asu_dept_picker.theme.inc',
    ),
    'asu_dept_tree' => array(
      'render' => 'element',
      'variables' => array(
        'items' => array(),
        'settings' => array(),
      ),
      'file' => 'inc/asu_dept_picker.theme.inc',
    ),
  );
}

/**
 * Loads required libraries
 */
function _asu_dept_picker_load_libraries() {
  static $_loaded = null;

  if (is_null($_loaded)) {
    libraries_load('react', module_exists('devel') ? 'source' : null);

    // jqTree (http://mbraak.github.com/jqTree)
    libraries_load('jqtree');
    libraries_load('fontawesome');

    // Load javascript and css
    drupal_add_js(drupal_get_path('module', 'asu_dept_picker') . '/asu_dept_picker.react.js');
    drupal_add_js(drupal_get_path('module', 'asu_dept_picker') . '/asu_dept_picker.js');
    drupal_add_css(drupal_get_path('module', 'asu_dept_picker') . '/asu_dept_picker.css');

    $_loaded = TRUE;
  }
}

/**
 * Themes an ASU Department Picker
 */
function theme_asu_dept_picker(&$vars) {
  // Load necessary libraries
  _asu_dept_picker_load_libraries();

  // access the form element's info
  $element = $vars['element'];

  // keep a static settings var so we can reference the instance settings in our js
  $settings = &drupal_static(__FUNCTION__, array());

  // keep track of the current instance index
  $index = '__' . count($settings);

  if (isset($element['#delta'])) {
    $index = $element['#delta'];
  }

  // see if we're passing any tree options at all
  if (!isset($element['#asu_dept_tree'])) {
    $element['#asu_dept_tree'] = array();
  }

  // if we don't load any tree json data, use our default one (most common)
  if (!isset($element['#asu_dept_tree']['tree_json_data'])) {
    $element['#asu_dept_tree']['tree_json_data'] = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_TREE_ENDPOINT, FALSE);
  }

  // detect value
  $value = !empty($element['#default_value']) ? $element['#default_value'] : '';
  $value = !empty($element['#value']) ? $element['#value'] : $value;

  $data = json_decode($value);
  if (json_last_error() == JSON_ERROR_NONE) {
    $element['#asu_dept_tree']['items']   = isset($data->items) ? $data->items : array();
    $element['#asu_dept_tree']['options'] = isset($data->options) ? $data->options : new stdClass();
    $element['#asu_dept_tree']['max_items'] = isset($element['#max_items']) ? $element['#max_items'] : 0;
  }

  // store the instance settings for use later
  $settings[$index] = $element['#asu_dept_tree'];

  // add settings to Drupal object
  drupal_add_js(array('asu_dept_picker' => $settings), 'setting');

  $element['#attributes']['data-delta'] = $index;

  // return the markup we will use to render our element in our js file
  return '<div class="asu-dept-picker-container">
      <div class="asu-dept-picker" data-delta="'.$index.'"></div>
      ' . theme('hidden', $element) . '
    </div>
  ';
}


/**
 * Themes an ASU Department Tree
 */
function theme_asu_dept_tree(&$vars) {
  // Load necessary libraries
  _asu_dept_picker_load_libraries();

  // Load all tree data
  $tree_json_data = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_TREE_ENDPOINT, FALSE);

  // Define default top level ids
  $top_level_ids = array(
    'top_level_psid' => ASU_DIR_UTILITIES_TOP_LEVEL_PS_ID, //ASU_DEPT_PICKER_TOP_LEVEL_PS_ID,
    'top_level_nid' => ASU_DIR_UTILITIES_TOP_LEVEL_DEPT_NID //ASU_DEPT_PICKER_TOP_LEVEL_DEPT_NID
  );

  $nids = array(ASU_DIR_UTILITIES_TOP_LEVEL_DEPT_NID);

  $settings = array(
    'tree_data' => $tree_json_data,
    'top_level_ids' => $top_level_ids,
    'dept_nids'     => $nids,
  );

  drupal_add_js(array('asu_dept_picker_dept_tree' => $settings), 'setting');

  return '<div class="asu-dept-tree"></div>';
}


/**
 * Implements hook_libraries_info
 *
 * Adds the JQtree library
 * Documentation for the library can be found here http://mbraak.github.io/jqTree/
 *
 * @return mixed
 *
 */
function asu_dept_picker_libraries_info() {
  // Expected to be extracted into 'sites/all/libraries/jqtree'.
  $libraries['jqtree'] = array(
    'name' => 'jQTree Library',
    'vendor url' => 'http://mbraak.github.io/jqTree/',
    'download url' => 'https://github.com/mbraak/jqTree/archive/0.22.0.zip',
    'version callback' => 'asu_dept_picker_short_circuit_version',
    'files' => array(
      'js' => array('tree.jquery.js'),
      'css' => array('jqtree.css'),
    ),
  );

  return $libraries;
}


/**
 * Short-circuit the version argument.
 */
function asu_dept_picker_short_circuit_version() {
  return TRUE;
}
