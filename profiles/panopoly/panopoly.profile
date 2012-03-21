<?php

/**
 * Implements hook_install_tasks()
 */
function panopoly_install_tasks($install_state) {

  // Kick off the tasks
  $tasks = array();

  // Summon the power of the Apps module
  require_once(drupal_get_path('module', 'apps') . '/apps.profile.inc');

  // Setup a task to verify capability to run apps
  $tasks['panopoly_apps_check'] = array(
    'display_name' => t('Enable apps support'),
    'type' => 'form',
  );

  // Setup the Panopoly Apps install task
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
      'panopoly_widgets',
      'panopoly_wysiwyg',
    ),
    'required apps' => array(
      'panopoly_core',
    ),
  );
  $tasks = $tasks + apps_profile_install_tasks($install_state, $panopoly_server);
  $tasks['apps_profile_apps_select_form_panopoly']['display_name'] = t('Install apps for Panopoly');

  // Setup the theme selection and configuration tasks
  $tasks['panopoly_theme_form'] = array(
    'display_name' => t('Choose a theme'),
    'type' => 'form',
  );
  $tasks['panopoly_theme_configure_form'] = array(
    'display_name' => t('Configure theme settings'),
    'type' => 'form',
  );

  // Setup the prepare task to close it out
  $tasks['panopoly_prepare'] = array(
    'display_name' => t('Prepare site'),
    'type' => 'form',
  );

  return $tasks;
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
  $form['site_information']['site_mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST']; 
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
  $form['server_settings']['site_default_country']['#default_value'] = 'US';
  $form['server_settings']['date_default_timezone']['#default_value'] = 'America/Los_Angeles'; // West coast, best coast
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
    foreach($_SESSION['apps_manifest'] as $name => $app) {
      if ($name != '#theme') {
        $options[$name] = '<strong>' . $app['name'] . '</strong><p><div class="admin-options"><div class="form-item">' . theme('image', array('path' => $app['logo']['path'], 'height' => '32', 'width' => '32')) . '</div>' . $app['description'] . '</div></p>';
      }
    }
    ksort($options);
    $form['apps_fieldset']['apps']['#options'] = $options;
  }
}

/**
 * Implements hook_install_tasks_alter()
 */
function panopoly_install_tasks_alter(&$tasks, $install_state) {

  // Since we only offer one language, define a callback to set this
  $tasks['install_select_locale']['function'] = 'panopoly_locale_selection';

  // Create a more fun finished page with our Open Academy Saurus
  $tasks['install_finished']['function'] = 'panopoly_finished_yah';
  $tasks['install_finished']['display_name'] = t('Finished!');
  $tasks['install_finished']['type'] = 'form';
}

/**
 * Task handler to set the language to English since that is the only one
 * we have at the moment.
 */
function panopoly_locale_selection(&$install_state) {
  $install_state['parameters']['locale'] = 'en';
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
      'manifest' => 'http://apps.getpantheon.com/panopoly',
      'profile' => $profile,
      'profile_version' => isset($info['version']) ? $info['version'] : '7.x-1.x',
      'server_name' => $_SERVER['SERVER_NAME'],
      'server_ip' => $_SERVER['SERVER_ADDR'],
    ),
  );
}

/**
 * Apps installer default content callback.
 *
 * Adapted from openenterprise_default_content()
 */
function panopoly_default_content(&$modules) {
  $files = system_rebuild_module_data();
  foreach($modules as $module) {
    // This assumes a pattern MYMODULE_democontent which is probably not always true. Might be 
    // better to check $_SESSION['apps_manifest'] and check to see if this exists:
    // function_exists($_SESSION['module']['configure form'])
    if (isset($files[$module . '_democontent'])) {
      $modules[] = $module . '_democontent';
    }
  }
}

/**
 * Form to check to see if Apps support is possible
 */
function panopoly_apps_check($form, &$form_state) {
  $form = array();

  $form['opening'] = array(
    '#markup' => '<h1>' . t('Enable Support for Apps') . '</h1>',
  );

  $form['openingtext'] = array(
    '#markup' => '<p>' . t('Apps uses the same mechanism for installing modules as the update module in core. This depends on certain php extensions to be installed on your server. Below is the documentation for the various methods of installing.') . '</p>',
  );

  $form['pantheon'] = array(
    '#title' => t('Pantheon'),
    '#type' => 'fieldset',
    '#description' => theme('image', array('path' => drupal_get_path('profile', 'panopoly') . '/images/enable-apps-pantheon.png')) . t('If you are installing Panopoly on Pantheon, you need to enable "On Server Development" to use apps.<br /><br />After you install your apps, you will need to use the "Commit" button to add them to the version control system.'),
  );

  $form['ftp'] = array(
    '#title' => t('FTP'),
    '#type' => 'fieldset',
    '#description' => 'In order to install via ftp, you must have the ftp php extension enabled. Most apache2/php installs have this by default which is by it probably shows up on most installs. <br /><br />You may run into a server that doesn\'t have ftp so then you will need to install it or use an alternative method. See <a href="http://us2.php.net/manual/en/book.ftp.php">http://us2.php.net/manual/en/book.ftp.php</a> for how to install the ftp php extension. You will also need an ftp username and password that has rights to write to your site directory on your server. Be aware that FTP is not an encrypted protocol and your credentials will be transmitted in the clear.',
  );

  $form['ssh'] = array(
    '#title' => t('SSH'),
    '#type' => 'fieldset',
    '#description' => 'In order to install via ssh, you must have the ssh2 php extension installed and enabled. This does not come by default with many apache2/php installs so it commonly needs to be added. <br /><br />See <a href="http://us2.php.net/manual/en/book.ssh2.php">http://us2.php.net/manual/en/book.ssh2.php</a> for how to install the ssh2 php extension. You will also need a username and password of a user that can ssh into the server and has write permissions to your site directory on your server.',
  );

  $form['webserver'] = array(
    '#title' => 'Webserver Direct Install',
    '#type' => 'fieldset',
    '#description' => 'In order to install directly to the sites/all/modules directory it needs to be writable. In order to do this go to the root of your drupal install and type <strong>sudo chmod -R 777 sites/all/modules</strong>. Be aware that there are security issues with leaving your site in this state.',
  );

  $form['continue'] = array(
    '#type' => 'submit',
    '#value' => 'Continue',
  );

  return $form;
}
                
/**
 * Form to choose the starting theme from list of available options
 */
function panopoly_theme_form($form, &$form_state) {

  // Create list of theme options, minus admin + testing + starter themes
  $themes = array();
  foreach(system_rebuild_theme_data() as $theme) {
    if (!in_array($theme->name, array('test_theme', 'update_test_basetheme', 'update_test_subtheme', 'block_test_theme', 'stark', 'seven'))) {
      $themes[$theme->name] = theme('image', array('path' => $theme->info['screenshot'])) . '<strong>' . $theme->info['name'] . '</strong><br><p><em>' . $theme->info['description'] . '</em></p><p class="clearfix"></p>';
    }
  }

  $form['theme'] = array(
    '#title' => t('Starting Theme'),
    '#type' => 'radios',
    '#options' => $themes,
    '#default_value' => 'panopoly_default',
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
 
  // Flush theme caches so things are right
  system_rebuild_theme_data();
  drupal_theme_rebuild();
}

/**
 * Form to choose the starting theme
 */
function panopoly_theme_configure_form($form, &$form_state) {
  $theme = variable_get('theme_default');
  ctools_include('system.admin', 'system', '');
  $form = system_theme_settings($form, $form_state, $theme); 
  return $form;
}

/**
 * Form to talk about preparing the site for prime time
 */
function panopoly_prepare($form, &$form_state) {
  $form = array();

  $form['opening'] = array(
    '#markup' => '<h1>' . t('Prepare Site'),
  );

  $form['openingtext'] = array(
    '#markup' => '<h2>' . t('Panopoly now needs to do a bit more Drupal magic to get everything setup.') . '</h2>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Prepare your site',
  );

  return $form;
}

/**
 * Submit form to prepare site for prime time
 */
function panopoly_prepare_submit($form, &$form_state) {
  // Flush all caches to ensure that any full bootstraps during the installer
  // do not leave stale cached data, and that any content types or other items
  // registered by the install profile are registered correctly.
  drupal_flush_all_caches();

  // Remember the profile which was used.
  variable_set('install_profile', drupal_get_profile());

  // Install profiles are always loaded last
  db_update('system')
    ->fields(array('weight' => 1000))
    ->condition('type', 'module')
    ->condition('name', drupal_get_profile())
    ->execute();

  // Cache a fully-built schema.
  drupal_get_schema(NULL, TRUE);

  // Run cron to populate update status tables (if available) so that users
  // will be warned if they've installed an out of date Drupal version.
  // Will also trigger indexing of profile-supplied content or feeds.
  drupal_cron_run();
}

/**
 * Form to finish it all out and send us on our way
 */
function panopoly_finished_yah($form, &$form_state) {
  $form = array();

  $form['opening'] = array(
    '#markup' => '<h1>' . t('Finished!') . '</h1>',
  );

  $form['openingtext'] = array(
    '#markup' => '<h2>' . t('Congratulations, you just installed Panopoly!') . '</h2>',
  );
  
  $form['panopoly_icon'] = array(
    '#markup' => theme('image', array('path' => drupal_get_path('profile', 'panopoly') . '/images/panopoly_icon.png')),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Visit your new site!',
  );

  return $form;
}

/**
 * Submit form to finish it out and send us on our way!
 */
function panopoly_finished_yah_submit($form, &$form_state) {

  // Once more for good measure
  drupal_flush_all_caches();

  // And away we go
  drupal_goto('<front>');
}
