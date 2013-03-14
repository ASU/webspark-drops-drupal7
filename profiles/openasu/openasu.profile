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

  // Force the SSL for installation
  if (isset($_SERVER['PANTHEON_ENVIRONMENT'])) {
    if (!isset($_SERVER['HTTP_X_SSL']) || $_SERVER['HTTP_X_SSL'] != 'ON') {
      header('HTTP/1.0 301 Moved Permanently');
      header('Location: https://' . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI']);
      exit();
    }
  }
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

  $form['theme_configuration']['asu_brand_is_student'] = array(
    '#type' => 'value',
    '#default_value' => variable_get('asu_brand_is_student', 'student'),
  );

  $form['theme_configuration']['asu_brand_header_template'] = array(
    '#title' => t('Header Color'),
    '#type' => 'radios',
    '#options' => array(
      'default' => t('Gold'),
      'default_maroon' => t('Maroon'),
      'default_white' => t('White'),
    ),
    '#default_value' => variable_get('asu_brand_header_template', ASU_BRAND_HEADER_TEMPLATE_DEFAULT),
  );

  $form['theme_configuration']['asu_brand_student_color'] = array(
    '#title' => t('Menu Color'),
    '#type' => 'radios',
    '#options' => array(
      'black' => t('Black'),
      'gold' => t('Gold'),
      'grey' => t('Grey'),
    ),
    '#default_value' => variable_get('asu_brand_student_color', 'black'),
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

  // Disable the default Bartik theme
  theme_disable(array('bartik'));

  // Enable and set the ASU theme
  $basetheme = 'kalatheme';
  $theme = 'openasu_bootstrap';
  $module = 'asu_brand';
  theme_enable(array($basetheme, $theme));
  variable_set('theme_default', $theme);

  // Set the appropriate colors
  $header_key = $form_state['values']['asu_brand_header_template'];
  variable_set('asu_brand_header_template', $header_key);

  // Enable the apporpriate blocks in the right regions
  $asu_brand_header_delta = 'asu_brand_header';
  $asu_brand_header_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(':delta' => $asu_brand_header_delta, ':theme' => $theme))->fetchField();
  db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(':status' => 1, ':bid' => $asu_brand_header_bid, ':theme' => $theme));
  db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(':region' => 'header', ':bid' => $asu_brand_header_bid, ':theme' => $theme));

  // Add in student footer if applicable 
  if ($form_state['values']['asu_brand_is_student'] == 'student') {
    $asu_brand_footer_delta = 'asu_brand_students_footer';
    variable_set('asu_brand_is_student', 'student');
    $asu_brand_footer_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(':delta' => $asu_brand_footer_delta, ':theme' => $theme))->fetchField();
    db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(':status' => 1, ':bid' => $asu_brand_footer_bid, ':theme' => $theme));
    db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(':region' => 'footer', ':bid' => $asu_brand_footer_bid, ':theme' => $theme)); 
    db_query("UPDATE {block} SET weight = -100 WHERE bid = :bid AND theme = :theme", array(':bid' => $asu_brand_footer_bid, ':theme' => $theme)); 
  }
  
  // Add in default footer regardless
  $asu_brand_footer_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(':delta' => 'asu_brand_footer', ':theme' => $theme))->fetchField();
  db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(':status' => 1, ':bid' => $asu_brand_footer_bid, ':theme' => $theme));
  db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(':region' => 'footer', ':bid' => $asu_brand_footer_bid, ':theme' => $theme));

  // Flush theme caches so things are right
  asu_brand_cache_clear();
  system_rebuild_theme_data();
  drupal_theme_rebuild();
}

/**
 * Implements hook_form_FORM_ID_alter()
 */
function openasu_form_install_configure_form_alter(&$form, $form_state) {

  // Hide some messages from various modules that are just too chatty.
  drupal_get_messages('status');
  drupal_get_messages('warning');

  // Set reasonable defaults for site configuration form
  $form['site_information']['site_name']['#default_value'] = 'My New OpenASU Site';
  $form['admin_account']['account']['name']['#default_value'] = 'admin';

  // Define a default email address if we can guess a valid one
  if (valid_email_address('admin@' . $_SERVER['HTTP_HOST'])) {
    $form['site_information']['site_mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
    $form['admin_account']['account']['mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  }
}
