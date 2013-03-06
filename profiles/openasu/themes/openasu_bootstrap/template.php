<?php
/**
 * @file
 * OpenASU Bootstrap's primary theme functions and alterations.
 */

/**
 * Load Kalatheme dependencies.
 *
 * Implements template_preprocess_html().
 */
function openasu_bootstrap_preprocess_html(&$variables) {
  // Set the header color
  if (module_exists('asu_brand')) {
    drupal_add_css(drupal_get_path('theme', 'openasu_bootstrap') . '/css/header/' .
      variable_get('asu_brand_header_template', ASU_BRAND_HEADER_TEMPLATE_DEFAULT) .  '.css');
  }
  // Load student CSS if this is a student template
  if (variable_get('asu_brand_is_student', 'default') == 'student') {
    drupal_add_css(drupal_get_path('theme', 'openasu_bootstrap') . '/css/student/' .
      variable_get('asu_brand_is_student', 'default') .  '.css', array(
      'group' => CSS_THEME,
      'media' => 'screen',
      'weight' => '100',
      )
    );
    // Load menu CSS for student header
    if (variable_get('asu_brand_student_color', 'black') != 'black') {
      drupal_add_css(drupal_get_path('theme', 'openasu_bootstrap') . '/css/student/menu/' .
        variable_get('asu_brand_student_color', 'black') .  '.css', array(
        'group' => CSS_THEME,
        'media' => 'screen',
        'weight' => '200',
        )
      );
    }
  }
}

/**
 * Implements hook_preprocess_PANELS_LAYOUT().
 */
function openasu_bootstrap_preprocess_asu_student_a(&$variables) {
  _openasu_bootstrap_theme_student_menu($variables);
}

/**
 * Implements hook_preprocess_PANELS_LAYOUT().
 */
function openasu_bootstrap_preprocess_asu_student_b(&$variables) {
  _openasu_bootstrap_theme_student_menu($variables);
}

/**
 * Helper function to get a themed menu for the panels layouts.
 */
function _openasu_bootstrap_theme_student_menu(&$variables) {
  $main_menu_tree = array();
  $main_menu_tree = menu_tree_all_data('main-menu', NULL, 2);
  // Add the rendered output to the $main_menu_expanded variable.
  $main_menu_expanded = menu_tree_output($main_menu_tree);
  $variables['content']['menu'] = theme('links__system_main_menu', array(
    'links' => $main_menu_expanded,
    'attributes' => array(
      'class' => array('nav pull-left'),
    ),
    'heading' => array(
      'text' => t('Main menu'),
      'level' => 'h2',
      'class' => array('element-invisible'),
    ),
  )
  );
}

/**
 * Implements hook_ctools_plugin_post_alter()
 */
function openasu_bootstrap_ctools_plugin_post_alter(&$plugin, &$info) {
  if ($info['type'] == 'styles') {
    if ($plugin['name'] == 'kalacustomize') {
      $plugin['title'] = 'Arizona State University';
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function openasu_bootstrap_form_panels_edit_style_settings_form_alter(&$form, &$form_state) {
  // Add some ASU styles if style panes are on
  if (isset($form['general_settings']['settings']['pane_style'])) {
    $form['general_settings']['settings']['pane_style']['#options'] += array(
      'black-pane' => 'ASU BLACK',
      'yellow-pane' => 'ASU GOLD',
      'grey-pane' => 'ASU GREY',
    );
  }

  // Add some extra ASU styles if extra styles are on
  if (isset($form['general_settings']['settings']['title'])) {
    $styles = array('title', 'content');
    foreach ($styles as $style) {
      $form['general_settings']['settings'][$style]['attributes']['#options'] += array(
        'featured-text' => 'ASU FEATURED TEXT',
      );
    }
  }
}
