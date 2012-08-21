<?php

/**
 * Implements hook_install_tasks()
 */
function panopoly_install_tasks(&$install_state) {

  // Start it off
  $tasks = array();

  // Attempt to increase the memory limit to 196M
  if (ini_get('memory_limit') != '-1' && ini_get('memory_limit') <= '196M') {    
    ini_set('memory_limit', '196M');
  }

  // Summon the power of the Apps module
  require_once(drupal_get_path('module', 'apps') . '/apps.profile.inc');

  // Set up the Panopoly Apps install task
  $panopoly_server = array(
    'machine name' => 'panopoly',
    'default apps' => array(
      'panopoly_admin',
      'panopoly_core',
      'panopoly_demo',
      'panopoly_images',
      'panopoly_magic',
      'panopoly_pages',
      'panopoly_search',
      'panopoly_theme',
      'panopoly_users',
      'panopoly_widgets',
      'panopoly_wysiwyg',
    ),
    'required apps' => array(
      'panopoly_admin',
      'panopoly_core',
      'panopoly_images',      
      'panopoly_magic',             
      'panopoly_pages',                   
      'panopoly_search',                        
      'panopoly_theme',                               
      'panopoly_users',                                     
      'panopoly_widgets',                                         
      'panopoly_wysiwyg',                                               
    ),
  );
  $tasks = $tasks + apps_profile_install_tasks($install_state, $panopoly_server);

  // Rename one of the default apps tasks. In the case of a non-interactive
  // installation, apps_profile_install_tasks() never defines this task, so we
  // need to make sure we don't accidentally create it when it doesn't exist.
  if (isset($tasks['apps_profile_apps_select_form_panopoly'])) {
    $tasks['apps_profile_apps_select_form_panopoly']['display_name'] = t('Install apps for Panopoly');
  }

  // Set up the theme selection and configuration tasks
  $tasks['panopoly_theme_form'] = array(
    'display_name' => t('Choose a theme'),
    'type' => 'form',
  );

  // Set up a finishing task to do cache clearing and various cleanup
  $tasks['panopoly_final_setup'] = array(
    'run' => '2',
  );

  return $tasks;
}

/**
 * Implements hook_install_tasks_alter()
 */
function panopoly_install_tasks_alter(&$tasks, $install_state) {

  // Magically insert an install task to add the Panopoly icon to Seven!   
  if (!array_key_exists('panopoly_add_icon', $tasks)) {
    $panopoly_add_icon = array('panopoly_add_icon', array('run' => 2));
    $tasks = array_reverse($tasks);
    $install_select_profile = array_pop($tasks);
    $install_select_locale = array_pop($tasks);
    $install_load_profile = array_pop($tasks);
    $install_verify_requirements = array_pop($tasks);
    $install_settings_form = array_pop($tasks);
    $install_system_module = array_pop($tasks);
    $install_bootstrap_full = array_pop($tasks);
    $tasks['panopoly_add_icon'] = array('run' => 2);
    $tasks['install_bootstrap_full'] = $install_bootstrap_full;
    $tasks['install_system_module'] = $install_system_module;
    $tasks['install_settings_form'] = $install_settings_form;
    $tasks['install_verify_requirements'] = $install_verify_requirements;
    $tasks['install_load_profile'] = $install_load_profile;
    $tasks['install_select_locale'] = $install_select_locale;
    $tasks['install_select_profile'] = $install_select_profile;
    $tasks = array_reverse($tasks);
  }

  // Since we only offer one language, define a callback to set this
  $tasks['install_select_locale']['function'] = 'panopoly_locale_selection';
}

/**
 * Implements hook_form_FORM_ID_alter()
 */
function panopoly_form_install_configure_form_alter(&$form, $form_state) {

  // Hide some messages from various modules that are just too chatty!
  drupal_get_messages('status');
  drupal_get_messages('warning');

  // Set reasonable defaults for site configuration form
  $form['site_information']['site_name']['#default_value'] = 'Panopoly';
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['server_settings']['site_default_country']['#default_value'] = 'US';
  $form['server_settings']['date_default_timezone']['#default_value'] = 'America/Los_Angeles'; // West coast, best coast

  // Define a default email address if we can guess a valid one
  if (valid_email_address('admin@' . $_SERVER['HTTP_HOST'])) {
    $form['site_information']['site_mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
    $form['admin_account']['account']['mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  }
}

/**
 * Implements hook_form_FORM_ID_alter()
 */
function panopoly_form_apps_profile_apps_select_form_alter(&$form, $form_state) {

  // For some things there are no need
  $form['apps_message']['#access'] = FALSE;
  $form['apps_fieldset']['apps']['#title'] = NULL;

  // Improve style of apps selection form
  if (isset($form['apps_fieldset'])) {
    $options = array();
    $manifest = apps_manifest(apps_servers('panopoly'));
    foreach ($manifest['apps'] as $name => $app) {
      if ($name != '#theme') {
        $options[$name] = '<strong>' . $app['name'] . '</strong><p><div class="admin-options"><div class="form-item">' . theme('image', array('path' => $app['logo']['path'], 'height' => '32', 'width' => '32')) . '</div>' . $app['description'] . '</div></p>';
      }
    }
    ksort($options);
    $form['apps_fieldset']['apps']['#options'] = $options;
  }

  // Remove the demo content selection option since this is
  // handled through the Panopoly demo module.
  $form['default_content_fieldset']['#access'] = FALSE;

  // Remove the "skip this step" option since why would we want that?
  $form['actions']['skip']['#access'] = FALSE;
}

/**
 * Task handler to set the language to English since that is the only one
 * we have at the moment.
 */
function panopoly_locale_selection(&$install_state) {
  $install_state['parameters']['locale'] = 'en';
}

/**
 * Task handler to set the icon of the maintaince theme to the Panopoly icon since
 * that icon is awesome and the Drupal alien (while also awesome) is scarey to new ppl
 */
function panopoly_add_icon(&$install_state) {
  $theme_data = _system_rebuild_theme_data();
  $seven_data = $theme_data['seven']->info['settings'];
  $seven_data['default_logo'] = 0;
  $seven_data['logo_path'] = 'profiles/panopoly/images/panopoly_icon_install.png';  
  variable_set('theme_seven_settings', $seven_data);
}

/**
 * Implements hook_appstore_stores_info()
 */
function panopoly_apps_servers_info() {
  $profile = variable_get('install_profile', 'panopoly');
  $info =  drupal_parse_info_file(drupal_get_path('profile', $profile) . '/' . $profile . '.info');
  return array(
    'panopoly' => array(
      'title' => 'Panopoly',
      'description' => 'Apps for Panopoly',
      'manifest' => (empty($info['version']) || $info['version'] == '7.x-1.x-dev') ? 'http://apps.getpantheon.com/panopoly-dev' : 'http://apps.getpantheon.com/panopoly',
    ),
  );
}

/**
 * Form to choose the starting theme from list of available options
 */
function panopoly_theme_form($form, &$form_state) {

  // Set the page title
  drupal_set_title(t('Choose a theme'));

  // Create list of theme options, minus admin + testing + starter themes
  $themes = array();
  foreach (system_rebuild_theme_data() as $theme) {
    if (!in_array($theme->name, array('test_theme', 'update_test_basetheme', 'update_test_subtheme', 'block_test_theme', 'stark', 'seven', 'adaptivetheme_admin', 'adaptivetheme', 'adaptivetheme_subtheme'))) {
      $themes[$theme->name] = theme('image', array('path' => $theme->info['screenshot'])) . '<strong>' . $theme->info['name'] . '</strong><br><p><em>' . $theme->info['description'] . '</em></p><p class="clearfix"></p>';
    }
  }

  $form['theme_wrapper'] = array(
    '#title' => t('Starting Theme'),
    '#type' => 'fieldset',
  );

  $form['theme_wrapper']['theme'] = array(
    '#type' => 'radios',
    '#options' => $themes,
    '#default_value' => 'bartik',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Choose theme',
  );

  return $form;
}

/**
 * Form submit handler to select the theme
 */
function panopoly_theme_form_submit($form, &$form_state) {
  
  // Enable and set the theme of choice
  $theme = $form_state['input']['theme'];
  theme_enable(array($theme));
  variable_set('theme_default', $theme);

  // Set the Bartik or Garland logo to be Panopoly's logo
  if ($theme == 'bartik' || $theme == 'garland' || $theme == 'responsive_bartik') {
    $theme_data = _system_rebuild_theme_data();
    $theme_data[$theme]->info['settings']['default_logo'] = 0;
    $theme_data[$theme]->info['settings']['logo_path'] = 'profiles/panopoly/images/panopoly_icon_theme.png';
    variable_set('theme_' . $theme . '_settings', $theme_data[$theme]->info['settings']);
  }

  // Flush theme caches so things are right
  system_rebuild_theme_data();
  drupal_theme_rebuild();
}

/**
 * Handler callback to do additional setup reqired for the site to be awesome
 */
function panopoly_final_setup(&$install_state) {

  // Allow anonymous and authenticated users to see and search content
  user_role_grant_permissions(DRUPAL_ANONYMOUS_RID, array('access content'));
  user_role_grant_permissions(DRUPAL_AUTHENTICATED_RID, array('access content'));
  user_role_grant_permissions(DRUPAL_ANONYMOUS_RID, array('search content'));
  user_role_grant_permissions(DRUPAL_AUTHENTICATED_RID, array('search content'));

  // Add login link for users to log in
  $item = array(
    'link_path' => 'user/login',
    'link_title' => 'Log in',
    'menu_name' => 'user-menu',
  );
  menu_link_save($item);
}
