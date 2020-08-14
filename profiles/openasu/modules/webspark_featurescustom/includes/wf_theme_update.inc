<?php

/**
 * @file
 * Update settings/configs related to ASU Web Standards when the theme is changed.
 */

/**
 * Implementation of hook_libraries_info_alter()
 *
 * + If a subtheme has been created before Kalatheme 1.4, then connect
 *   it to the default Innovation library.
 * + Ensure the user doesn't have a Bootstrap library already
 *   set up for their subtheme.
 * + El Puente will use the default Innovation bootstrap library.
 */
function webspark_featurescustom_libraries_info_alter(&$libraries) {
  global $theme_info;
  if (isset($theme_info->name) && isset($theme_info->base_theme)) {
    $library_path = DRUPAL_ROOT . '/sites/all/libraries/' . $theme_info->name . '_bootstrap/css/bootstrap.css';
    if ($theme_info->name !== 'innovation' && $theme_info->base_theme === 'innovation' && !file_exists($library_path)) {
      $libraries[$theme_info->name . '_bootstrap']['machine name'] = 'innovation_bootstrap';
    }
  }
}

/**
 * Implements hook_menu_alter()
 */
function webspark_featurescustom_menu_alter(&$items) {
  // builds on existing menu callback for theme selection function to include
  // our own functionality
  $items['admin/appearance/default']['page callback'] = '_webspark_featurescustom_appearance_theme_update';
}

/**
 * Is the current theme ASU Web standards theme (innovation, elpuente)?
 *
 * @TODO - Put in check to see if certain settings are already in place before module_load_include...s
 */
function _webspark_featurescustom_appearance_theme_update() {
  // Checking if the selected theme is our theme & calling function to active modules/configuration
  module_load_include('inc', 'system', 'system.admin.inc');
  $new_theme = check_plain($_REQUEST['theme']);

  // WEBSPARK-610 - What settings to apply, based on the theme
  $theme_test_result = _webspark_featurescustom_web_standards_theme_check($new_theme);
  _webspark_featurescustom_act($new_theme, $theme_test_result);
}

/**
 * Get WS2.0 suffix to append to files/assets if the default/active theme is an ASU Web standars 2.0 theme
 * @param string $theme_to_check - machine name of theme to check for as the current, default theme. Defaults to El Puente theme.
 * @param string $suffix - Suffix to append to the CSS file name as the alternate CSS file. Defaults to _ws2
 * @return string - Returns the suffix passed in IF $theme === checked theme.
 */
function _webspark_featurescustom_get_ws2_suffix($use_adm_theme = FALSE, $theme_to_check = 'elpuente', $suffix = '_ws2') {
  $theme = &drupal_static(__FUNCTION__);
  if (!isset($theme)) {
    $theme = _webspark_featurescustom_web_standards_theme_check($theme, 2, $use_adm_theme);
  }
  return ($theme === $theme_to_check) ? $suffix : '';
}

/**
 * Is $theme an ASU web standards theme (or have an ASU WS base theme)?
 * @param string $theme - New theme selected
 * @param int $ws_version - Which version of Web standards is desired? Defaults to all WS themes (0).
 * @param bool $use_adm_theme - Use the admin theme name (not the default theme).
 * Default: FALSE - Users want to check if Web Standards 2.0 is enabled in the site but the check is being
 * done from an admin theme managed URL/form.
 * Set to TRUE if the theme of the current URL (of the form) needs to be returned - not the default theme.
 * @return mixed - Theme name if true, 0 if false.
 */
function _webspark_featurescustom_web_standards_theme_check($theme = '', $ws_version = 0, $use_adm_theme = FALSE) {
  // Get current theme if not checking a particular theme (default)
  if (empty($theme)) {
    global $theme;
  }
  // Use the default theme (not the current page's theme) if the admin theme is NOT the theme you want to check.)
  if ($use_adm_theme === FALSE) {
    if ($theme !== variable_get('theme_default')) {
      $theme = variable_get('theme_default');
    }
  }
  // Now check if theme or base theme (WS2.0 only). If base theme, get that theme's name instead.
  dpm($ws_version, __FUNCTION__ . ' - ws_version');
  // Check #1 - Is $theme an existing web standards theme?
  if ($theme === 'innovation') {
    if ($ws_version !== 2) { // Exclude WS2.x option (can be 1 or 0/all)
      dpm('TRUE - ' . $theme);
      return $theme; // TRUE
    } else {
      dpm('FALSE - ' . $theme . ' is a WS theme, but it is not WS2 as requested.');
      return 0;
    }
  } elseif ($theme === 'elpuente') {
    if ($ws_version !== 1) { // Exclude WS1.0 option
      dpm('TRUE - ' . $theme);
      return $theme; // TRUE
    } else {
      dpm("FALSE - " . $theme . ' is a WS theme, but it is not WS1 as requested.');
      return 0;
    }
  }
  else { // Check #2 - Is $theme a subtheme of a Web standards theme?
    $all_themes = list_themes(TRUE);
    // remove themes with no base_theme.
    foreach ($all_themes as $name => $value) {
      if (!isset($value->base_theme)) {
        unset($all_themes[$name]);
      }
    }
    // Get WS themes to check against.
    $ws_base_theme_options = array();
    switch ($ws_version) {
      case 2:
        $ws_base_theme_options[] = 'elpuente';
        break;
      case 1:
        $ws_base_theme_options[] = 'innovation';
        break;
      default: // 0
        $ws_base_theme_options = array('innovation', 'elpuente');
    }
    $theme_base_themes = (array_key_exists($theme, $all_themes))
      ? drupal_find_base_themes($all_themes, $theme)
      : array();

    if (!empty($theme_base_themes)) {
      dpm($theme . ' theme has base theme(s):');
      dpm($theme_base_themes);
      foreach ($ws_base_theme_options as $option) {
        $option_array = (array)$option;
        if (in_array($ws_base_theme_options, array_keys($theme_base_themes))) {
          if ($option_array[0] === $theme) {
            dpm('TRUE - ' . $theme . ' is === '. $option_array[0] . ' - Is a WS subtheme.');
            return $theme;
          } else {
            dpm('TRUE - ' . $theme . ' - theme HAS a WS subthemes');
            return $option_array[0];
          }
        }
        unset($option_array);
      }
      // not matched -- return 0
      dpm('FALSE - ' . $theme . ' (and its subthemes) are not WS');
      return 0;
    } else {
      dpm('FALSE - ' . $theme . ' has no subthemes at all.');
      return 0;
    }
  }
}

/**
 * Enable ASU Web Standards elements or not?
 *
 * @param string $new_theme - Theme to be changed to.
 * @param mixed $theme_test_result - Is an ASU Web standards theme (ex. innovation, elpuente).
 * Theme machine name if true; 0 if false.
 * the theme or base_theme of the new theme?
 */
function _webspark_featurescustom_act($new_theme, $theme_test_result) {
  if ($theme_test_result !== 0) { // ASU Web standards theme is involved
    _webspark_featurescustom_web_standards_theme_config($new_theme);
  }
  else { // Not an ASU Web standards theme
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
 */
function _webspark_featurescustom_web_standards_theme_config($theme) {
  // Enabling WS theme-related modules if they are not enabled
  $modules = array();
  $modules_to_enable = array();
  // Contrib module dependencies for features
  $modules[] = 'backgroundfield';
  $modules[] = 'chosen';
  $modules[] = 'easy_breadcrumb';
  $modules[] = 'entity_view_mode';
  $modules[] = 'flexslider';
  $modules[] = 'fontawesome';
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
      watchdog('theme update', 'Web standards-based modules enabled for %theme theme - ' . implode(', ', $modules_to_enable), array('%theme' => $theme));
    }
    catch (Exception $e) {
      watchdog('theme update', 'Web standards-based module dependency enabling failed: ' . $e->getMessage(), WATCHDOG_ERROR);
      drupal_set_message('The enabling of Innovation theme-specific modules may have failed. Check your <a href="/admin/reports/dblog">recent log messages</a> for details.', 'error');
    }
  }
  else {
    watchdog('theme update', 'All modules already enabled for %theme theme, so no module_enable action taken.', array('%theme' => $theme), WATCHDOG_NOTICE);
  }

  // Reset ASU Header settings
  if (module_exists('asu_brand')) {
    variable_set('asu_brand_header_version', ASU_BRAND_HEADER_VERSION_DEFAULT);
    variable_set('asu_brand_header_template', ASU_BRAND_HEADER_TEMPLATE_DEFAULT);
    variable_set('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT);
    watchdog('theme update', 'Updated ASU Header values for %theme theme based on ASU Brand module settings', array('%theme' => $theme), WATCHDOG_NOTICE);
  }

  dpm($theme, __FUNCTION__ . ' - which theme?');

  // Re-apply original block configs to ensure their proper location to match spinup settings.
  // function openasu_blockupdates_for_theme() in openasu.profile
  if (function_exists('openasu_blockupdates_for_theme')) {
    openasu_blockupdates_for_theme($theme);
  }

  // Upsert Mega Footer block
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
      $fields['weight'] = (int) ($result->weight - 1); // lighter than the asu_brand_footer
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

  // WEBSPARK-509 - Swap out system main-menu with TB Mega Menu main-menu on
  // theme update. (#610 - updated queries to Database API)
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
      )
      ->execute();
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
      )
      ->execute();
  }
  // Disable deprecated ASU Students block for all themes except asu_webspark_bootstrap
  db_merge('block')
    ->key(array(
      'module' => 'asu_brand',
      'delta' => 'asu_brand_students_footer',
      'theme' => $theme,
    ))
    ->fields(array(
        'region' => '-1',
        'status' => '0',
        'weight' => '0'
      )
    )
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
function _webspark_featurescustom_alt_theme_config($theme = NULL) {
  dpm($theme, __FUNCTION__);
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

  // WEBSPARK-1551 - Move System Help block to help region if it exists (defaults to content)
  $regions = array_keys(system_region_list($theme));
  $help_region = (in_array('help', $regions)) ? 'help' : 'content';
  dpm($help_region, __FUNCTION__ . ' - help_region');
  $help_weight = ($help_region === 'help') ? 5 : -50;
  db_merge('block')
    ->key(array(
      'module' => 'system',
      'delta' => 'help',
      'theme' => $theme,
    ))
    ->fields(array(
      'region' => $help_region,
      'status' => '1',
      'weight' => $help_weight,
    ))
    ->execute();

  // Log changes
  drupal_set_message('Disabled Innovation-themed blocks for <em>' . t($theme) .
    '</em> theme. Go to the <a href="">blocks configuration</a> page to re-enable these blocks if desired.');
  watchdog('theme update', 'Disabled Web Standards-themed blocks for %theme theme.', array('%theme' => $theme));
}

/**
 * Implements hook_form_alter().
 *
 * Adds the theme checking to the admin theme selection form (/admin/appearance).
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
  $theme = $form_state['values']['admin_theme']; // new admin theme
  $theme_test_result = _webspark_featurescustom_web_standards_theme_check($theme, 0, TRUE);
  _webspark_featurescustom_act($theme, $theme_test_result);
}
