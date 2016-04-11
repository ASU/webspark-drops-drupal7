<?php

/**
 * @file
 * Update settings/configs related to ASU Web Standards when the theme is changed.
 */

/**
 * Implements hook_menu_alter()
 */
function webspark_featurescustom_menu_alter(&$items) {
  // builds on existing menu callback for theme selection function to include
  // our own functionality
  $items['admin/appearance/default']['page callback'] = '_webspark_featurescustom_theme_check';
}

/**
 * @param has_base_theme - (boolean) - Is innovation the theme
 *
 * @TODO - Put in check to see if certain settings are already in place before module_load_include...s
 */
function _webspark_featurescustom_theme_check() {
  // Checking if the selected theme is our theme & calling function to active modules/configuration
  module_load_include('inc', 'system', 'system.admin.inc');
  $new_theme = check_plain($_REQUEST['theme']);

  // WEBSPARK-610 - What settings to apply, based on the theme
  $theme_test_result = _webspark_featurescustom_get_base_theme($new_theme);
  _webspark_featurescustom_act($new_theme, $theme_test_result);
}

/**
 * Is new theme an ASU theme or have an ASU base theme?
 * @param $theme - New theme selected
 * @returns TRUE or FALSE
 */
function _webspark_featurescustom_get_base_theme($theme) {
  $all_themes = list_themes(TRUE);
  // remove themes with no base_theme.
  foreach ($all_themes as $name => $value) {
    if (!isset($value->base_theme)) {
      unset($all_themes[$name]);
    }
  }
  $base_themes = (array_key_exists($theme, $all_themes)) ? drupal_find_base_themes($all_themes, $theme) : array();
  return ($theme === 'innovation' || in_array('innovation', array_keys($base_themes))) ? 1 : 0;
}

/**
 * Enable ASU Web Standards elements or not?
 *
 * @param $theme_test_result - Boolean - Is innovation the theme or base_theme of
 * the new theme?
 */
function _webspark_featurescustom_act($new_theme, $theme_test_result) {
  if ($theme_test_result === 1) { // innovation is involved
    _webspark_featurescustom_webstandards_theme_config($new_theme);
  }
  else { // or not
    if ($new_theme !== 'asu_webspark_bootstrap') {
      _webspark_featurescustom_alt_theme_config($new_theme);
    }
    else { // no changes
      drupal_set_message('No changes for asu_webspark_bootstrap theme');
    }
  }
  system_theme_default(); // reset themes
}

/**
 * Theme update callback - On theme change from any theme to Innovation theme
 * @TODO - Centralize the ASU header information
 */
function _webspark_featurescustom_webstandards_theme_config($theme) {
  // Enabling Innovation-related modules if they are not enabled
  $modules = array();
  $modules_to_enable = array();
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
  // OpenASU custom modules, features - keep this up with openasu.info
  // TODO - automate this process by reading in .info file
  $modules[] = 'webspark_featurescustom';
  $modules[] = 'asu_gsa';
  $modules[] = 'asu_maps_enhanced';
  $modules[] = 'asu_spotlight';
  $modules[] = 'uto_carousel';
  $modules[] = 'asu_securityscanfixes';
  $modules[] = 'webspark_wysiwyg';
  $modules[] = 'webspark_panels_styles';
  $modules[] = 'webspark_banner';
  $modules[] = 'webspark_breadcrumbs';
  $modules[] = 'webspark_content_callout';
  $modules[] = 'webspark_easyadmin';
  $modules[] = 'webspark_hero';
  $modules[] = 'webspark_jumbohero';
  $modules[] = 'webspark_megamenu';
  $modules[] = 'mega_footer';
  $modules[] = 'mega_footer_menu';
  $modules[] = 'webspark_wysiwyg';
  $modules[] = 'webspark_extras';

  // Enable disabled modules
  foreach($modules as $module) {
    if (!module_exists($module)) {
      $modules_to_enable[] = $module;
    }
  }

  if (count($modules_to_enable) > 0) {
    try {
      module_enable($modules_to_enable);
      drupal_set_message('Modules enabled for <em>' . t($theme) . '</em> - ' . implode(', ', $modules_to_enable));
      watchdog('theme update', 'Modules enabled for %theme theme - ' . implode(', ', $modules_to_enable), array('%theme' => $theme));
    }
    catch (Exception $e) {
      watchdog('theme update', 'Innovation module dependency enabling failed: ' . $e->getMessage(), WATCHDOG_ERROR);
      drupal_set_message('The enabling of Innovation theme-specific modules may have failed. Check your <a href="/admin/reports/dblog">recent log messages</a> for details.', 'error');
    }
  }
  else {
    watchdog('theme update', 'All modules already enabled for %theme theme, so no module_enable action taken.', array('%theme' => $theme));
  }

  // WEBSPARK-448, 509
  // Reset ASU Header settings
  if (module_exists('asu_brand')) {
    variable_set('asu_brand_header_version', ASU_BRAND_HEADER_VERSION_DEFAULT);
    variable_set('asu_brand_header_template', ASU_BRAND_HEADER_TEMPLATE_DEFAULT);
    variable_set('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT);
    watchdog('theme update', 'Updated ASU Header values for %theme theme based on ASU Brand module settings', array('%theme' => $theme));
  }

  // WEBSPARK-610 - Re-apply original block configs to ensure their proper location
  // to match spinup settings.
  // function openasu_blockupdates_for_theme() in openasu.profile
  if (function_exists('openasu_blockupdates_for_theme')) {
    openasu_blockupdates_for_theme($theme);
  }

  // Now Mega Footer block
  if (module_exists('mega_footer') && module_exists('mega_footer_menu')) {
    db_update('block')
      ->fields(array(
          'region' => 'footer',
          'status' => '1',
          'weight' => '-10'
        )
      )
      ->condition('module', 'mega_footer')
      ->condition('delta', 'mega_footer')
      ->execute();
  }

  // WEBSPARK-509 - Swap out system main-menu with TB Mega Menu main-menu on
  // theme update. (#610 - updated queries to Database API)
  if (module_exists('tb_megamenu') && module_exists('webspark_megamenu')) {
    db_update('block')
      ->fields(array(
          'region' => 'menu',
          'status' => '1',
          'weight' => '-100'
        )
      )
      ->condition('module', 'tb_megamenu')
      ->condition('delta', 'main-menu')
      ->execute();
    db_update('block')
      ->fields(array(
          'region' => '-1',
          'status' => '0',
          'weight' => '0'
        )
      )
      ->condition('module', 'system')
      ->condition('delta', 'main-menu')
      ->execute();
  }
  // Disable deprecated ASU Students block for all themes except asu_webspark_bootstrap
  db_update('block')
    ->fields(array(
        'region' => '-1',
        'status' => '0',
        'weight' => '0'
      )
    )
    ->condition('module', 'asu_brand')
    ->condition('delta', 'asu_brand_students_footer')
    ->execute();

  // Flush ASU Brand caches so ASU headers are right...
  asu_brand_cache_clear();
  // and log changes.
  drupal_set_message('Enabled Web Standards-themed blocks for <em>' . t($theme) . '</em> theme');
  watchdog('theme update', 'Enabled Web Standards-themed blocks for %theme theme', array('%theme' => $theme));
}

/**
 * Alternate callback for when Innovation is NOT selected - disable
 * Innovation-specific blocks.
 */
function _webspark_featurescustom_alt_theme_config($theme = NULL){
  if (is_null($theme)) { // callback from admin theme form
    $theme = variable_get('admin_theme');
    drupal_set_message($theme . ' selected as admininstrator theme');
    watchdog('theme update', '%theme selected as administrator theme', array('%theme' => $theme));
  }
  // Hide blocks for $theme
  db_update('block')
    ->fields(array(
        'region' => '-1',
        'status' => '0',
        'weight' => '0'
      )
    )
    ->condition('theme', $theme)
    ->condition(db_or()
      ->condition(db_and()
        ->condition('module', 'asu_brand')
        ->condition('delta', 'asu_brand_footer')
      )
      ->condition(db_and()
        ->condition('module', 'asu_brand')
        ->condition('delta', 'asu_brand_header')
      )
      ->condition(db_and()
        ->condition('module', 'tb_megamenu')
        ->condition('delta', 'main-menu')
      )
      ->condition(db_and()
        ->condition('module', 'mega_footer')
        ->condition('delta', 'mega_footer')
      )
    )
    ->execute();
  // Log changes
  drupal_set_message('Disabled Innovation-themed blocks for <em>' . t($theme) .
    '</em> theme. Go to the <a href="">blocks configuration</a> page to re-enable these blocks if desired.');
  watchdog('theme update', 'Disabled Web Standards-themed blocks for %theme theme.', array('%theme' => $theme));
}

/**
 * Implements hook_form_alter().
 *
 * Admin theme selection form
 */
function webspark_featurescustom_form_system_themes_admin_form_alter(&$form, &$form_state, $form_id) {
  // + Add additional submission handler to end after manually running D7 core form submit
  $form['admin_theme']['actions']['submit']['#submit'][] = 'system_themes_admin_form_submit';
  $form['admin_theme']['actions']['submit']['#submit'][] = '_webspark_featurescustom_admin_theme';
}

/**
 * Implements hook_form_submit()
 *
 * Custom submission handler for admin theme form.
 */
function _webspark_featurescustom_admin_theme($form, &$form_state) {
  $admin_theme = $form_state['values']['admin_theme']; // new admin theme
  $theme_test_result = _webspark_featurescustom_get_base_theme($admin_theme);
  _webspark_featurescustom_act($admin_theme, $theme_test_result);
}
