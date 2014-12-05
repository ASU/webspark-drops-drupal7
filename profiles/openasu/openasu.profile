<?php

/**
 * Implements hook_install_tasks()
 */
function openasu_install_tasks() {
  $tasks['openasu_select_theme_form'] = array(
    'display_name' => t('Select theme'),
    'type' => 'form',
  );
  $tasks['openasu_theme_configure_form'] = array(
    'display_name' => t('Configure theme'),
    'type' => 'form',
  );
  $tasks['openasu_innovation_extra_setup'] = array(
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

    // Skip Webspark theme settings task if Innovation theme is selected
  if (!empty($install_state['parameters']['whichtheme']) && $install_state['parameters']['whichtheme'] == 'innovation') {
    $tasks['openasu_theme_configure_form']['run'] = INSTALL_TASK_SKIP;
  }

  // Skip Innovation extra setup task if Webspark theme is selected
  if (!empty($install_state['parameters']['whichtheme']) && $install_state['parameters']['whichtheme'] == 'asu_webspark_bootstrap') {
    $tasks['openasu_innovation_extra_setup']['run'] = INSTALL_TASK_SKIP;
  }
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
 * Implements hook_form()
 *
 * Form to select Drupal theme
 * Choices:
 * -- Webspark
 * -- Innovation
 */
function openasu_select_theme_form($form, &$form_state) {
  $form = array();
  $theme = 'innovation';
  global $base_url;
  global $base_path;
  $form['theme_selection'] = array(
    '#title' => t('Select a theme'),
    '#type' => 'fieldset',
  );
  $form['theme_selection']['whichtheme'] = array(
    '#title' => t(''),
    '#type' => 'radios',
    '#options' => array(
      'innovation' => t('Innovation (BETA) - ASU Web Standards compliant theme. Currently in development and not ready for production.'),
      'asu_webspark_bootstrap' => t('Webspark (Stable) - ASU branded responsive (mobile friendly) theme.'),
    ),
    '#default_value' => 'innovation',
    '#ajax' => array(
      'callback' => 'openasu_selection_preview',
      'wrapper' => 'openasu-selection-preview',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#required' => FALSE,
  );
  $form['theme_selection']['selection_preview'] = array(
    '#prefix' => "<div id='openasu-selection-preview'>",
    '#markup' => t('<p><img src="@preview"></p>', array(
      '@preview' => $base_url . $base_path . '/profiles/openasu/themes/' . $theme . '/screenshot.png'
    )),
    '#suffix' => "</div>",
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Select theme',
  );
  return $form;
}

/**
 * Form submit handler selecting the theme
 *
 * Implements hook_form_submit()
 */

function openasu_select_theme_form_submit($form, &$form_state) {
  global $install_state;

  // Innovation theme selected
  if ($form_state['values']['whichtheme'] == 'innovation') {
    // Set install state to 
    $install_state['parameters']['whichtheme'] = 'innovation';

    // Disable the default Bartik theme
    theme_disable(array('bartik'));
    // Enable and set the theme
    $basetheme = 'kalatheme';
    $theme = 'innovation';
    $module = 'asu_brand';
    system_rebuild_theme_data();
    drupal_theme_rebuild();
    theme_enable(array($basetheme));
    theme_enable(array($theme));
    variable_set('theme_default', $theme);

    // Set the appropriate colors
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

    // Set the responsive version of the header to be default
    variable_set('asu_brand_header_version', '4.3');
  }
}

/**
 * Form to configure the Webspark Classic theme (if selected)
 */
function openasu_theme_configure_form($form, &$form_state) {

  // Set the page title
  drupal_set_title(t('Configure theme'));
  $theme = 'asu_webspark_bootstrap';

  // Build the form
  $form = array();
  $form['theme_configuration'] = array(
    '#title' => t('ASU Webspark Theme Settings'),
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
      '@preview' => drupal_get_path('profile', 'openasu') . '/themes/' . $theme . '/thumbs/' . variable_get('asu_brand_header_selector', ASU_BRAND_HEADER_TEMPLATE_DEFAULT) . '-header.png'
    )),
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
      '@preview' => drupal_get_path('profile', 'openasu') . '/themes/' . $theme . '/thumbs/' . variable_get('asu_brand_student_color', 'black') . '-menu.png'
    )),
    '#suffix' => "</div>",
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Configure theme',
  );

  return $form;
}

/**
 * Form submit handler to configure the Webspark Classic theme
 *
 * Implements hook_form_submit()
 */
function openasu_theme_configure_form_submit($form, &$form_state) {
  // Set install_task setting to Webspark
  $install_state['parameters']['whichtheme'] = 'asu_webspark_bootstrap';

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

  // Enable the Main Menu block in the right region
  $main_menu_delta = 'main-menu';
  $main_menu_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(
      ':delta' => $main_menu_delta,
      ':theme' => $theme
    ))->fetchField();
  db_query("UPDATE {block} SET status = :status WHERE bid = :bid AND theme = :theme", array(
      ':status' => 1,
      ':bid' => $main_menu_bid,
      ':theme' => $theme
    ));
  db_query("UPDATE {block} SET region = :region WHERE bid = :bid AND theme = :theme", array(
      ':region' => 'menu',
      ':bid' => $main_menu_bid,
      ':theme' => $theme
    ));
  db_query("UPDATE {block} SET weight = -100 WHERE bid = :bid AND theme = :theme", array(
      ':bid' => $main_menu_bid,
      ':theme' => $theme
    ));

  // Add in student footer if applicable
  if ($form_state['values']['asu_brand_is_student'] == 'student') {
    $asu_brand_footer_delta = 'asu_brand_students_footer';
    variable_set('asu_brand_is_student', 'student');
    $asu_brand_footer_bid = db_query("SELECT bid FROM {block} WHERE delta = :delta AND theme = :theme", array(
        ':delta' => $asu_brand_footer_delta,
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
    db_query("UPDATE {block} SET weight = -100 WHERE bid = :bid AND theme = :theme", array(
        ':bid' => $asu_brand_footer_bid,
        ':theme' => $theme
      ));
  }

  // Add in Brand Footer block footer regardless of student footer
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

  // Set the responsive version of the header to be default
  variable_set('asu_brand_header_version', '4.0-rsp-up.0');
  // Now disable Innovation-specific modules that were enabled on spinup
  $modules = array();
  // Contrib module dependencies for features
  $modules[] = 'backgroundfield';
  $modules[] = 'chosen';
  $modules[] = 'easy_breadcrumb';
  $modules[] = 'entity_view_mode';
  $modules[] = 'flexslider';
  $modules[] = 'fontawesome';
  $modules[] = 'google_appliance';
  $modules[] = 'maxlength';
  $modules[] = 'panels_tabs';
  $modules[] = 'uuid_features';
  $modules[] = 'video_embed_field';
  $modules[] = 'wysiwyg_template';
  $modules[] = 'asu_spotlight';
  $modules[] = 'mega_footer';
  // OpenASU custom modules, features
  $modules[] = 'asu_gsa';
  $modules[] = 'webspark_featurescustom';
  $modules[] = 'webspark_wysiwyg';
  $modules[] = 'webspark_panels_styles';
  $modules[] = 'webspark_banner';
  $modules[] = 'webspark_breadcrumbs';
  $modules[] = 'webspark_content_callout';
  $modules[] = 'webspark_hero';
  $modules[] = 'webspark_megamenu';
  $modules[] = 'mega_footer_menu';
  $modules[] = 'webspark_extras';

  module_disable($modules);

  // Enable Webspark Demo module
  $modules_enable = array('openasu_demo');
  module_enable($modules_enable);

  // Flush caches so things are right
  asu_brand_cache_clear();
}

/**
 * More Innovation theme setup, after initial module enabling, etc.
 */
function openasu_innovation_extra_setup(&$install_state) {
  if (isset($install_state['parameters']['whichtheme']) &&
    $install_state['parameters']['whichtheme'] == 'innovation'
  ) {
    // With tb_megamenu enabled and the block created by webspark_megamenu feature, 
    // enable the TB Main Menu block in the right region.
    if (module_exists('tb_megamenu') && module_exists('webspark_megamenu')) {
      $main_menu_bid = db_query("SELECT bid FROM {block} WHERE delta = 'main-menu' AND theme = 'innovation' AND module = 'tb_megamenu'")->fetchField();
      db_query("UPDATE {block} SET status = 1 WHERE bid = :bid AND theme = 'innovation'", array(':bid' => $main_menu_bid));
      db_query("UPDATE {block} SET region = 'menu' WHERE bid = :bid AND theme = 'innovation'", array(':bid' => $main_menu_bid));
      db_query("UPDATE {block} SET weight = -100 WHERE bid = :bid AND theme = 'innovation'", array(':bid' => $main_menu_bid));
    }
  }
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

/**
 * Theme selection Ajax callbacks that returns HTML to the setup form so that the user
 * can see a preview of the theme.
 *
 * @function openasu_selection_preview - select a theme preview (Innovation only)
 * @function openasu_header_preview - select a header (Webspark only)
 * @function openasu_menu_preview - select a menu color (Webspark only)
 * @param $form
 * @param $form_state
 * @return - Updated form state to be merged back in
 *
 */
function openasu_selection_preview($form, &$form_state) {
  $theme = $form_state['values']['whichtheme'];
  $form['theme_selection']['selection_preview']['#markup'] = t('<p><img src="@preview"></p>', array(
    '@preview' => $base_url . $base_path . '/profiles/openasu/themes/' . $theme . '/screenshot.png',
  ));
  return $form['theme_selection']['selection_preview'];
}

function openasu_header_preview($form, &$form_state) {
  $header = $form_state['values']['asu_brand_header_selector'];
  if ($header === 'custom') {
    $form['theme_configuration']['header_preview']['#markup'] = t('');
  }
  else {
    $form['theme_configuration']['header_preview']['#markup'] = t('<img src="@preview">', array(
      '@preview' => $base_url . $base_path . '/profiles/openasu/themes/asu_webspark_bootstrap/thumbs/' . $header . '-header.png',
    ));
  }
  return $form['theme_configuration']['header_preview'];
}

function openasu_menu_preview($form, &$form_state) {
  $menu = $form_state['values']['asu_brand_student_color'];
  $form['theme_configuration']['menu_preview']['#markup'] = t('<img src="@preview">', array(
    '@preview' => $base_url . $base_path . '/profiles/openasu/themes/asu_webspark_bootstrap/thumbs/' . $menu . '-menu.png',
  ));
  return $form['theme_configuration']['menu_preview'];
}
