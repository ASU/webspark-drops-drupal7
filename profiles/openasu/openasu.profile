<?php

/**
 * Implements hook_install_tasks()
 */
function openasu_install_tasks() {
  $tasks['openasu_theme_innovation_setup'] = array(
    'display' => FALSE,
    'type' => 'normal',
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

  // Pick a theme - REMOVED

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
 * Form submit handler selecting the theme
 *
 * Implements hook_form_submit()
 */

function openasu_theme_innovation_setup(&$install_state) {
  // Set install state to
  $install_state['parameters']['whichtheme'] = 'innovation';

  // Disable the default Bartik theme
  theme_disable(array('bartik'));

  // Enable and set the themes
  $basetheme = 'kalatheme';
  $theme = 'innovation';
  system_rebuild_theme_data();
  drupal_theme_rebuild();
  theme_enable(array($basetheme));
  theme_enable(array($theme));
  variable_set('theme_default', $theme);
  variable_set('admin_theme', 'webspark_seven');

  // ASU Header settings
  variable_set('asu_brand_header_version', '4.3');
  variable_set('asu_brand_header_template', 'default');
  variable_set('asu_brand_header_selector', 'default');

  // Enable the Brand Header block in the right region
  $asu_brand_header_delta = 'asu_brand_header';
  $asu_brand_header_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(
    ':delta' => $asu_brand_header_delta,
    ':theme' => $theme
  ))->fetchField();
  db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(
    ':status' => 1,
    ':bid' => $asu_brand_header_bid,
    ':theme' => $theme
  ));
  db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(
    ':region' => 'header',
    ':bid' => $asu_brand_header_bid,
    ':theme' => $theme
  ));

  // Add back in default footer regardless - readded after WEBSPARK-357 removed it from megafooter module
  $asu_brand_footer_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(
    ':delta' => 'asu_brand_footer',
    ':theme' => $theme
  ))->fetchField();
  db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(
    ':status' => 1,
    ':bid' => $asu_brand_footer_bid,
    ':theme' => $theme
  ));
  db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(
    ':region' => 'footer',
    ':bid' => $asu_brand_footer_bid,
    ':theme' => $theme
  ));
  // With tb_megamenu enabled and the block created by webspark_megamenu feature,
  // enable the TB Main Menu block in the right region.
  if (module_exists('tb_megamenu') && module_exists('webspark_megamenu')) {
    $main_menu_bid = db_query("SELECT bid FROM {block} WHERE delta = 'main-menu' AND theme = 'innovation' AND module = 'tb_megamenu'")->fetchField();
    db_query("UPDATE {block} SET status = 1 WHERE bid = :bid AND theme = 'innovation'", array(':bid' => $main_menu_bid));
    db_query("UPDATE {block} SET region = 'menu' WHERE bid = :bid AND theme = 'innovation'", array(':bid' => $main_menu_bid));
    db_query("UPDATE {block} SET weight = -100 WHERE bid = :bid AND theme = 'innovation'", array(':bid' => $main_menu_bid));
  }

  // Flush ASU Brand caches so ASU headers are right
  asu_brand_cache_clear();
}

/**
 * Implements hook_form_FORM_ID_alter()
 */
function openasu_form_install_configure_form_alter(&$form, $form_state) {

  // Hide some messages from various modules that are just too chatty.
  drupal_get_messages('status');
  drupal_get_messages('warning');

  // Set reasonable defaults for site configuration form
  $form['site_information']['site_name']['#default_value'] = 'My New ASU Webspark Site';
  $form['admin_account']['account']['name']['#default_value'] = 'admin';

  // Define a default email address if we can guess a valid one
  if (valid_email_address('admin@' . $_SERVER['HTTP_HOST'])) {
    $form['site_information']['site_mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
    $form['admin_account']['account']['mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  }

  // Set the location to be in Arizona
  $form['server_settings']['site_default_country']['#default_value'] = 'US';
  $form['server_settings']['date_default_timezone']['#default_value'] = 'America/Phoenix';
  $form['server_settings']['date_default_timezone']['#attributes']['class'] = array();

  $form['admin_account']['openasu_admin_asurite'] = array(
    '#title' => 'ASURITE User ID',
    '#description' => st('Associate admin account with ASURITE User'),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#weight' => 20,
  );

  // Add an additional submit handler to process the form
  $form['#submit'][] = 'openasu_admin_save_asurite';
}

/**
 * Custom submission handler for ASURITE IDs during Webspark install.
 */
function openasu_admin_save_asurite($form_id, &$form_state) {
  $asurite = $form_state['values']['openasu_admin_asurite'];
  if (!empty($asurite)) {
    variable_set('openasu_admin_asurite', $asurite);
    db_merge('cas_user')
      ->key(array('cas_name' => $asurite))
      ->fields(array('uid' => 1))
      ->execute();
  }
}