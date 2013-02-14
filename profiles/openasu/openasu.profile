<?php

/**
 * Implements hook_install_tasks()
 */
function openasu_install_tasks() {
  $tasks['openasu_theme_configure_form'] = array(
    'display_name' => t('Configure theme'),
    'type' => 'form',
  );
  return $tasks;
}

/**
 * Implements hook_install_tasks_alter()
 */
function openasu_install_tasks_alter(&$tasks, $install_state) {

  // Magically go one level deeper in solving years of dependency problems
  require_once(drupal_get_path('module', 'panopoly_core') . '/panopoly_core.profile.inc');
  $tasks['install_load_profile']['function'] = 'panopoly_core_install_load_profile';
}

/**
 * Form to configure the theme
 */
function openasu_theme_configure_form($form, &$form_state) {

  // Set the page title
  drupal_set_title(t('Configure theme'));

  // Build the form
  $form = array();

  $form['theme_configuration'] = array(
    '#title' => t('OpenASU Theme Settings'),
    '#type' => 'fieldset',
  );

  $form['theme_configuration']['asu_brand_header_template'] = array(
    '#title' => t('Color Scheme'),
    '#type' => 'radios',
    '#options' => array(
      'default' => t('Gold'),
      'default_maroon' => t('Maroon'),
      'default_white' => t('White'),
    ),
    '#default_value' => variable_get('asu_brand_header_template', ASU_BRAND_HEADER_TEMPLATE_DEFAULT),
  );

  $form['theme_configuration']['asu_brand_is_student'] = array(
    '#title' => t('Footer Type'),
    '#type' => 'select',
    '#options' => array(
      'default' => t('Default Footer'),
      'student' => t('Student Footer'),
    ),
    '#default_value' => 'default',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Configure theme',
  );

  return $form;
}

/**
 * Form submit handler to configure the theme
 */
function openasu_theme_configure_form_submit($form, &$form_state) {
  
  // Enable and set the ASU theme
  $theme = 'openasu_bootstrap';
  $module = 'asu_brand';
  theme_enable(array($theme));
  variable_set('theme_default', $theme);

  // Set the appropriate colors
  $header_key = $form_state['values']['asu_brand_header_template'];
  variable_set('asu_brand_header_template', $header_key);

  // Enable the apporpriate blocks in the right regions
  $asu_brand_header_delta = 'asu_brand_header';
  $asu_brand_header_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(':delta' => $asu_brand_header_delta, ':theme' => $theme))->fetchField();
  db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(':status' => 1, ':bid' => $asu_brand_header_bid, ':theme' => $theme));
  db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(':region' => 'header', ':bid' => $asu_brand_header_bid, ':theme' => $theme));
  $asu_brand_footer_delta = ($form_state['values']['asu_brand_is_student'] == 'default') ? 'asu_brand_footer' : 'asu_brand_students_footer';
  $asu_brand_footer_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(':delta' => $asu_brand_footer_delta, ':theme' => $theme))->fetchField();
  db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(':status' => 1, ':bid' => $asu_brand_footer_bid, ':theme' => $theme));
  db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(':region' => 'footer', ':bid' => $asu_brand_footer_bid, ':theme' => $theme));

  // Flush theme caches so things are right
  asu_brand_cache_clear();
  system_rebuild_theme_data();
  drupal_theme_rebuild();
}
