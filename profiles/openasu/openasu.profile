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
  // Default themes on spinup
  $basetheme = 'kalatheme';
  $theme = 'innovation';
  $ws2_theme = 'college';

  // Set install state to
  $install_state['parameters']['whichtheme'] = $theme;

  // Disable the default Bartik theme
  theme_disable(array('bartik'));

  // Enable and set the themes
  variable_set('clean_url', 1);
  system_rebuild_theme_data();
  drupal_theme_rebuild();
  theme_enable(array($basetheme));
  theme_enable(array($theme));
  theme_enable(array($ws2_theme));
  variable_set('theme_default', $theme);
  variable_set('admin_theme', 'webspark_seven');
  variable_set('node_admin_theme', 1);

  // ASU Header settings (initially select WS1.0 header/footer (4.x - stable))
  variable_set('asu_brand_header_version', 'stable');

  // Configure blocks for Web standards theme (currently Innovation)
  openasu_blockupdates_for_theme($theme);

  // Flush ASU Brand caches so updated ASU header/footer (and any other related blocks) are right
  asu_brand_cache_clear();
}

/**
 * MASTER block configuration for Webspark for themes
 * For both profile and module (webspark_featurescustom) usage
 * @param $theme - Target/new theme
 * @param array $ws_data - If alternate theme data is added, it may override default Web standards keys, data, etc.
 * @noinspection HtmlUnknownTarget
 */
function openasu_blockupdates_for_theme($theme, $ws_data = array()) {
  if (module_exists('asu_brand')) {
    module_load_include('inc', 'asu_brand', 'includes/asu_brand.theme_update');
    try {
      // Enable the Mega menu (swap out system menu and put in webspark's TB megamenu)
      if (module_exists('tb_megamenu') && module_exists('webspark_megamenu')) {
        db_merge('block')
          ->key(array(
            'module' => 'tb_megamenu',
            'delta' => 'main-menu',
            'theme' => $theme,
          ))
          ->fields(array(
              'region' => 'menu',
              'status' => '1',
              'weight' => '-100'
            )
          )->execute();
        db_merge('block')
          ->key(array(
            'module' => 'system',
            'delta' => 'main-menu',
            'theme' => $theme,
          ))
          ->fields(array(
              'region' => '-1',
              'status' => '0',
              'weight' => '0'
            )
          )->execute();
      }
      // Enable the Mega footer
      if (module_exists('mega_footer') && module_exists('mega_footer_menu')) {
        $fields = array(
          'region' => 'footer',
          'status' => 1,
        );
        $result = db_select('block', 'b')->fields('b', array('weight', 'pages'))
          ->condition('module', 'asu_brand')
          ->condition('delta', 'asu_brand_footer')
          ->condition('theme', $theme)
          ->execute()
          ->fetchObject();
        if (!empty($result)) {
          $fields['weight'] = (int)($result->weight - 1); // lighter than the asu_brand_footer
          $fields['pages'] = $result->pages;
        } else {
          drupal_set_message('Check to ensure that the Mega footer'
            . ' is in the right location (directly above the ASU global footer). If not, go'
            . ' <a href="/admin/structure/block">manually reorder</a> the mega footer block.)', 'warning');
        }
        db_merge('block')
          ->key(array(
            'module' => 'mega_footer',
            'delta' => 'mega_footer',
            'theme' => $theme,
          ))
          ->fields($fields)
          ->execute();
      }

      // Enable the Web standards global header/footer w/ASU Brand code (skip if not enabled)
      asu_brand_block_theme_update($theme, $ws_data);

    } catch (Exception $e) {
      $message = 'All Web standards blocks for %theme could not be updated or created.'
        . ' Go to <a href="/admin/structure/block/list/' . check_plain($theme) . '">' . check_plain($theme)
        . ' to place the blocks in their proper locations.';
      watchdog('asu_brand', $message, array(), WATCHDOG_ERROR);
    }
    // Adjust system help block
    _openasu_system_help_block_enable($theme);
    watchdog('openasu', 'Updating block settings for %theme theme were attempted.', array('%theme' => $theme));
  }
}

/**
 * Add System module's help block to the theme. (WEBSPARK-1551)
 * Place block in help region if it exists (defaults to content).
 * @param $theme
 */
function _openasu_system_help_block_enable($theme) {
  $help_bid = db_select('block', 'b')
    ->fields('b', array('bid'))
    ->condition('delta', 'help')
    ->condition('theme', $theme)
    ->condition('module', 'system')
    ->execute()
    ->fetchField();

  $regions = array_keys(system_region_list($theme));
  $help_region = (in_array('help', $regions)) ? 'help' : 'content';
  $help_weight = ($help_region == 'help') ? 5 : -50;
  db_update('block')
    ->fields(array(
      'region' => $help_region,
      'status' => '1',
      'weight' => $help_weight,
    ))
    ->condition('bid', $help_bid)
    ->condition('theme', $theme)
    ->execute();
}

/**
 * Implements hook_form_FORM_ID_alter()
 * @noinspection PhpDocSignatureInspection
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
 * @noinspection PhpDocSignatureInspection
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
