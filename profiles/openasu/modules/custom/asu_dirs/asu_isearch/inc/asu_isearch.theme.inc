<?php
/**
 * @file
 * Theming functions for the asu_isearch module.
 *
 * @author Sebastian Nievas (snievas@asu.edu)
 *
 */

/**
 *Implements hook_theme()
 */
function asu_isearch_theme() {
  return array(
    // iSearch Directory Panel Pane
    'fieldable_panels_pane__isearch_directory' => array(
      'template' => 'theme/fieldable-panels-pane--isearch-directory',
      'render element' => 'elements',
      'file' => 'inc/asu_isearch.theme.inc',
      'type' => 'module'
    ),
    // ASU Spotlight container
    'asu_isearch_dept_picker' => array(
      'variables' => array(
        'items' => array(),
        'settings' => array(),
        'label' => 'Select Department'
      ),
      'template' => 'theme/asu_isearch.dept_picker',
      'file' => 'inc/asu_isearch.theme.inc',
    ),
    // iSearch Department Tree
    'asu_isearch_dept_tree' => array(
      'variables' => array(
        'item' => array(),
        'settings' => array(),
        'caption' => ''
      ),
      'file' => 'inc/asu_isearch.theme.inc',
    ),
  );
}

/**
 * Default theme implementation for iSearch department tree
 */
function theme_asu_isearch_dept_tree(&$vars) {
  $standalone = FALSE;
  $whole_tree = FALSE;
  $config_target = FALSE;

  if (isset($vars['settings']['standalone_tree'])) {
    $standalone = $vars['settings']['standalone_tree'];
  }

  if (isset($vars['settings']['whole_tree'])) {
    $whole_tree = $vars['settings']['whole_tree'];
  }

  if (isset($vars['settings']['config_target'])) {
    $config_target = $vars['settings']['config_target'];
  }

  $tree = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_TREE_ENDPOINT, FALSE); //asu_dir_utilities_get_dept_tree();

  // jqTree (http://mbraak.github.com/jqTree)
  libraries_load('jqtree');
  libraries_load('fontawesome');

  // Custom
  drupal_add_css(drupal_get_path('module', 'asu_isearch') . '/css/asu_isearch.dept_tree.css');
  drupal_add_js(drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch.dept_tree.js');

  $top_level_ids = array(
    "top_level_psid" => ASU_ISEARCH_DIRECTORY_TOP_LEVEL_PS_ID,
    "top_level_nid" => ASU_ISEARCH_DIRECTORY_TOP_LEVEL_DEPT_NID
  );

  // Pass our items and configs to the JS
  // will need to pass extra configs if the tree is being used without the people display (standalone)
  if ($standalone) {
    if (isset($vars['items'][0]['directory_items'])) {
      $nids = $vars['items'][0]['directory_items'];
    }
    else {
      $nids = array(ASU_ISEARCH_DIRECTORY_TOP_LEVEL_DEPT_NID);
    }

    $settings = array(
      'tree' => $tree,
      'top_level_ids' => $top_level_ids,
      'standalone' => $standalone,
      'dept_nids' => $nids,
    );
  }
  else {
    $settings = array(
      'tree' => $tree,
      'whole_tree' => $whole_tree,
      'top_level_ids' => $top_level_ids
    );
  }

  $settings['config_target'] = $config_target;

  drupal_add_js(array('asu_isearch_dept_tree' => $settings), 'setting');


  $form = array();
  $form['include_subdepts'] = array(
    '#type' => 'checkbox',
    '#title' => 'Include sub-departments?',
    '#attributes' => array(
      'id' => 'asu-isearch-dept-include-subdept',
      'name' => 'include_subdepts',
    ),
    '#description' => t('This will include all sub-departments beneath the selected department.'),
  );

  $form['dialog_submit'] = array(
    '#type' => 'button',
    '#value' => 'Select',
    '#attributes' => array(
      'id' => 'asu-isearch-dept-picker-select',
      'type' => 'button',
    ),
  );

  $form['dialog_cancel'] = array(
    '#type' => 'button',
    '#value' => 'Cancel',
    '#attributes' => array(
      'id' => 'asu-isearch-dept-picker-cancel',
      'type' => 'button',
    ),
  );

  return '<div class="asu-directory-tree-hierarchy">
    <div class="dialog-title">
      Choose a department
      <div class="close-dialog"><span class="fa fa-close"></span></div>
    </div>
    <div class="tree-wrapper">
      <div id="treediv"></div>
    </div>
    <div class="actions">
      ' . drupal_render($form) . '
    </div>
  </div>';

}