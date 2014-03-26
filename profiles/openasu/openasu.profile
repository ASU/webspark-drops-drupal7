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
  $theme = 'asu_webspark_bootstrap';

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
  $form['theme_configuration']['asu_brand_header_selector'] = array(
    '#title' => t('Header Scheme'),
    '#type' => 'radios',
    '#options' => array(
      'default' => t('Gold'),
      'default_maroon' => t('Maroon'),
      'default_white' => t('White'),
      'custom' => t('Custom'),
    ),
    '#default_value' => variable_get('asu_brand_header_selector', ASU_BRAND_HEADER_TEMPLATE_DEFAULT),
    '#ajax' => array(
      'callback' => 'openasu_header_preview',
      'wrapper' => 'openasu-header-preview',
      'method' => 'replace',
      'effect' => 'fade',
      //'progress' => array('type' => 'none'),
    ),
  );
  $form['theme_configuration']['header_preview'] = array(
    '#prefix' => "<div id='openasu-header-preview'>",
    '#markup' => t('<img src="@preview">', array(
      '@preview' => drupal_get_path('profile', 'openasu') . '/themes/' . $theme . '/thumbs/' . variable_get('asu_brand_header_selector', ASU_BRAND_HEADER_TEMPLATE_DEFAULT) . '-header.png')),
    '#suffix' => "</div>",
  );
  $form['theme_configuration']['asu_brand_header_template'] = array(
    '#title' => t('Enter Custom Template Key'),
    '#type' => 'textfield',
    '#states' => array(
     'visible' => array(
       ':input[name="asu_brand_header_selector"]' => array('value' => 'custom'),
     ),
    ),
    '#default_value' => variable_get('asu_brand_header_template', variable_get('asu_brand_header_selector')),
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
    '#ajax' => array(
      'callback' => 'openasu_menu_preview',
      'wrapper' => 'openasu-menu-preview',
      'method' => 'replace',
      'effect' => 'fade',
      //'progress' => array('type' => 'none'),
    ),
  );
  $form['theme_configuration']['menu_preview'] = array(
    '#prefix' => "<div id='openasu-menu-preview'>",
    '#markup' => t('<img src="@preview">', array(
      '@preview' => drupal_get_path('profile', 'openasu') . '/themes/' . $theme . '/thumbs/' . variable_get('asu_brand_student_color', 'black') . '-menu.png')),
    '#suffix' => "</div>",
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
  $theme = 'asu_webspark_bootstrap';
  $module = 'asu_brand';
  system_rebuild_theme_data();
  drupal_theme_rebuild();
  theme_enable(array($basetheme));
  theme_enable(array($theme));
  variable_set('theme_default', $theme);

  // Set the appropriate colors
  if ($form_state['values']['asu_brand_header_selector'] != 'custom') {
    variable_set('asu_brand_header_template', $form_state['values']['asu_brand_header_selector']);
  }
  else {
    variable_set('asu_brand_header_template', $form_state['values']['asu_brand_header_template']);
  }
  variable_set('asu_brand_is_student', $form_state['values']['asu_brand_is_student']);
  variable_set('asu_brand_student_color', $form_state['values']['asu_brand_student_color']);
  variable_set('asu_brand_header_selector', $form_state['values']['asu_brand_header_selector']);

  // Enable the Brand Header block in the right region
  $asu_brand_header_delta = 'asu_brand_header';
  $asu_brand_header_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(':delta' => $asu_brand_header_delta, ':theme' => $theme))->fetchField();
  db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(':status' => 1, ':bid' => $asu_brand_header_bid, ':theme' => $theme));
  db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(':region' => 'header', ':bid' => $asu_brand_header_bid, ':theme' => $theme));

  // Enable the Main Menu block in the right region
  $main_menu_delta = 'main-menu';
  $main_menu_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(':delta' => $main_menu_delta, ':theme' => $theme))->fetchField();
  db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(':status' => 1, ':bid' => $main_menu_bid, ':theme' => $theme));
  db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(':region' => 'menu', ':bid' => $main_menu_bid, ':theme' => $theme));
  db_query("UPDATE {block} SET weight = -100 WHERE bid = :bid AND theme = :theme", array(':bid' => $main_menu_bid, ':theme' => $theme));

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

  // Set the responsive version of the header to be default
  variable_set('asu_brand_header_version', '4.0-rsp-up.0');

  // Flush caches so things are right
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
  $form['site_information']['site_name']['#default_value'] = 'My New WebSpark Site';
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
 * Custom submission handler for Webspark install.
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

/**
 * Ajax callback that returns HTML to the setup form so that the user
 * can see a preview of the ASU Header they are selecting.
 *
 * @param $form
 *   Form
 * @param $form_state
 *   Form state
 *
 * @return
 *   Updated form state to be merged back in
 *
 */
function openasu_header_preview($form, &$form_state) {
  $header = $form_state['values']['asu_brand_header_selector'];
  if ($header === 'custom') {
    $form['theme_configuration']['header_preview']['#markup'] = t('');
  }
  else {
    $form['theme_configuration']['header_preview']['#markup'] = t('<img src="@preview">', array(
      '@preview' => drupal_get_path('profile', 'openasu') . '/themes/asu_webspark_bootstrap/thumbs/' . $header . '-header.png',
    ));
  }
  return $form['theme_configuration']['header_preview'];
}

/**
 * Ajax callback that returns HTML to the setup form so that the user
 * can see a preview of the ASU Menu they are selecting.
 *
 * @param $form
 *   Form
 * @param $form_state
 *   Form state
 *
 * @return
 *   Updated form state to be merged back in
 *
 */
function openasu_menu_preview($form, &$form_state) {
  $menu = $form_state['values']['asu_brand_student_color'];
  $form['theme_configuration']['menu_preview']['#markup'] = t('<img src="@preview">', array(
    '@preview' => drupal_get_path('profile', 'openasu') . '/themes/asu_webspark_bootstrap/thumbs/' . $menu . '-menu.png',
  ));
  return $form['theme_configuration']['menu_preview'];
}
