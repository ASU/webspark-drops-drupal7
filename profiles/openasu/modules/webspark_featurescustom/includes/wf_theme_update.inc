<?php /** @noinspection PhpUnusedParameterInspection */
/** @noinspection PhpDocSignatureInspection */

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
 * Is the current theme ASU Web standards theme (innovation, college)?
 *
 * @noinspection PhpUnused
 */
function _webspark_featurescustom_appearance_theme_update() {
  // Checking if the selected theme is our theme & calling function to active modules/configuration
  module_load_include('inc', 'system', 'system.admin.inc');
  $new_theme = check_plain($_REQUEST['theme']);
  if (!empty($new_theme)) {
    // Get what settings to apply, based on what the theme is (a Web standards check)
    $ws_theme_test_result = _webspark_featurescustom_web_standards_theme_check($new_theme);
    _webspark_featurescustom_act($new_theme, $ws_theme_test_result);
  }
}

/**
 * Get WS2.0 suffix to append to files/assets if the default/active theme is an ASU Web standars 2.0 theme
 * @param bool $use_current_theme - @see _webspark_featurescustom_web_standards_theme_check()
 * @param string $theme_to_check - machine name of theme to check for as the current, default theme. Defaults to El Puente theme.
 * @param string $suffix - Suffix to append to the CSS file name as the alternate CSS file. Defaults to _ws2
 * @return string - Returns the suffix passed in IF $theme === checked theme.
 */
function _webspark_featurescustom_get_ws2_suffix($use_current_theme = FALSE, $theme_to_check = 'college', $suffix = '_ws2') {
  $theme = &drupal_static(__FUNCTION__);
  if (!isset($theme)) {
    $theme = _webspark_featurescustom_web_standards_theme_check($theme, 2, $use_current_theme);
  }
  return ($theme === $theme_to_check) ? $suffix : '';
}

/**
 * Is $theme an ASU web standards theme (or have an ASU WS base theme)?
 * @param string $theme - New theme selected
 * @param int $ws_version - Which version of Web standards is desired? Checks for ANY WS theme by default (=== 0).
 * @param bool $use_current_theme - Use the admin theme name (not the default theme).
 * Default: FALSE - Users want to check if Web Standards 2.0 is enabled in the site but the check is being
 * done from an admin theme managed URL/form.
 * Set to TRUE if the theme of the current URL (of the form) needs to be returned - not the default theme.
 * @return mixed - Theme name if true, 0 if false.
 */
function _webspark_featurescustom_web_standards_theme_check($theme = '', $ws_version = 0, $use_current_theme = FALSE) {
  // Get current theme if not checking a particular theme (default)
  if (empty($theme)) {
    global $theme;
  }
  // Use the default theme (not the current page's theme) if the admin theme is NOT the theme
  // you want to check.)
  if ($use_current_theme === FALSE) {
    if (isset($_REQUEST['theme'])) { // Theme change is happening; Use that theme.
      $theme = check_plain($_REQUEST['theme']);
    } elseif ($theme !== variable_get('theme_default')) {
      $theme = variable_get('theme_default'); // Gets current theme (no theme change is taking place
    }
  }
  // Check #1 - Is $theme an existing web standards theme?
  if ($theme === 'innovation') {
    if ($ws_version !== 2) { // Exclude WS2.x option;
      return $theme; // TRUE is a WS1 theme
    } else {
      return 0; // FALSE is a WS theme, but it is not WS1 as requested.
    }
  } elseif ($theme === 'college') {
    if ($ws_version !== 1) { // Exclude WS1.0 option
      return $theme; // TRUE
    } else { // is a WS theme, but it is not WS2 as requested.
      return 0;
    }
  } else {
    // Check #2 - Is $theme a subtheme of a Web standards theme? If so, return the base theme's name instead.
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
        $ws_base_theme_options[] = 'college';
        break;
      case 1:
        $ws_base_theme_options[] = 'innovation';
        break;
      default: // 0
        $ws_base_theme_options = array('innovation', 'college');
    }
    $theme_base_themes = (array_key_exists($theme, $all_themes))
      ? drupal_find_base_themes($all_themes, $theme)
      : array();

    if (!empty($theme_base_themes)) {
      foreach ($ws_base_theme_options as $option) {
        $option_array = (array)$option;
        if (in_array($option_array[0], array_keys($theme_base_themes))) {
          if ($option_array[0] === $theme) { // Is a WS subtheme
            return $theme;
          } else { // New/current theme HAS a WS subtheme
            return $option_array[0];
          }
        }
        unset($option_array);
      }
      // $theme (and its subthemes) are both not WS
      return 0;
    } else { // $theme has no subthemes, so it's not WS.
      return 0;
    }
  }
}

/**
 * Enable ASU Web Standards elements or not?
 *
 * @param string $new_theme - Theme to be changed to.
 * @param mixed $ws_theme_test_result - Machine name of ASU Web standards theme or subtheme
 * (ex. innovation, college). Theme machine name if true; 0 if false.
 */
function _webspark_featurescustom_act($new_theme, $ws_theme_test_result) {
  if (module_exists('asu_brand')) {
    module_load_include('inc', 'asu_brand', 'includes/asu_brand.theme_update');
    $ws_data = asu_brand_get_ws_data($ws_theme_test_result);
    switch ($ws_theme_test_result) {
      case 'college':
      case 'innovation':
        variable_set('asu_brand_header_version', $ws_data['curr_version']);
        _webspark_featurescustom_web_standards_theme_config($new_theme, $ws_data);
        break;
      default:
        variable_set('asu_brand_header_version', ASU_BRAND_HEADER_VERSION_DEFAULT);
        if ($new_theme !== 'asu_webspark_bootstrap') {
          _webspark_featurescustom_alt_theme_config($new_theme);
        } else { // no changes
          drupal_set_message('No changes for asu_webspark_bootstrap theme.');
        }
        break;
    }
    system_theme_default(); // reset themes
  }
}

/**
 * Theme update callback - On theme change to Web standards based theme (regardless of old theme)
 * @param string $new_theme - name of Web standards theme
 * @param array $ws_data - Web standards data (header version, asset suffix)
 */
function _webspark_featurescustom_web_standards_theme_config($new_theme, $ws_data) {
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
      drupal_set_message('Modules enabled for <em>' . t($new_theme) . '</em> - ' . implode(', ', $modules_to_enable));
      watchdog('theme update', 'Web standards-based modules enabled for %theme theme - ' . implode(', ', $modules_to_enable), array('%theme' => $new_theme));
    }
    catch (Exception $e) {
      watchdog('theme update', 'Web standards-based module dependency enabling failed: ' . $e->getMessage(), WATCHDOG_ERROR);
      /** @noinspection HtmlUnknownTarget */
      drupal_set_message('The enabling of Web standards specific modules may have failed. Check your <a href="/admin/reports/dblog">recent log messages</a> for details.', 'error');
    }
  } else {
    watchdog('theme update', 'All modules already enabled for %theme theme, so no module_enable action taken.', array('%theme' => $new_theme), WATCHDOG_NOTICE);
  }

  // Apply original block configs from Webspark install profile (openasu.profile) to ensure their proper
  // location to match spinup settings.
  openasu_blockupdates_for_theme($new_theme, $ws_data);
  _webspark_featurescustom_wysiwyg_css($new_theme);

  // Flush ASU Brand caches so ASU header/footer/megamenu/mega_footer are right.
  asu_brand_cache_clear();
  // and log changes.
  drupal_set_message('Enabled Web Standards-themed blocks for <em>' . t($new_theme) . '</em> theme');
  watchdog('theme update', 'Enabled Web Standards-themed blocks for %theme theme', array('%theme' => $new_theme));
}

/**
 * Alternate callback for when a desired Web standards theme has NOT been selected - disable
 * Innovation-specific blocks.
 * @param null $theme - Name of theme. If 0,
 */
function _webspark_featurescustom_alt_theme_config($theme = NULL) {
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
        ->condition('delta', 'asu_brand_foote%', 'LIKE')
      )
      ->condition(db_and()
        ->condition('module', 'asu_brand')
        ->condition('delta', 'asu_brand_heade%', 'LIKE')
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

  // Add System module's help block to the theme
  if (function_exists('_openasu_system_help_block_enable')) {
    _openasu_system_help_block_enable($theme);
  }
  // Set WYSIWYG profile (WYSIWYG) CSS to the theme's default.
  _webspark_featurescustom_wysiwyg_css($theme, $alt_theme = FALSE);

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
function _webspark_featurescustom_admin_theme($form, $form_state) {
  $theme = $form_state['values']['admin_theme']; // new admin theme
  $theme_test_result = _webspark_featurescustom_web_standards_theme_check($theme, 0, TRUE);
  _webspark_featurescustom_act($theme, $theme_test_result);
}

/**
 * Sets the CSS file paths to the new theme's defaults so the WYSIWYG can apply that styling.
 * @param string $new_theme - New theme machine name
 * @param bool $alt_theme - Is an alternate theme (not Web standards?). Defaults to FALSE.
 */
function _webspark_featurescustom_wysiwyg_css($new_theme, $alt_theme = FALSE) {
  if (module_exists('wysiwyg')) {
    $innovation_css_path = '%bprofiles/openasu/libraries/innovation_bootstrap/css/bootstrap.min.css,%bprofiles/openasu/themes/innovation/css/innovation-main.css,%bprofiles/openasu/themes/innovation/css/buttons.css,%bprofiles/openasu/themes/innovation/css/forms.css,%bprofiles/openasu/themes/innovation/css/nav.css,%bprofiles/openasu/themes/innovation/fonts/roboto/css/roboto.css,%bprofiles/openasu/modules/webspark_featurescustom/webspark_wysiwyg/css/webspark-wysiwyg.css';
    $college_css_path = '%bprofiles/openasu/themes/college/css/college.core-bootstrap.css,%bprofiles/openasu/themes/college/css/admin.css,%bprofiles/openasu/themes/college/css/maintenance-pages.css,%bprofiles/openasu/themes/college/css/nav.css,%bprofiles/openasu/themes/college/css/college.custom.css,%bprofiles/openasu/themes/college/css/college.media-rules.css';
    $alt_theme_css_path = '';
    $settings = db_select('wysiwyg', 'w')
      ->fields('w', array('settings'))
      ->condition('format', 'panopoly_wysiwyg_text')
      ->condition('editor', 'tinymce')
      ->execute()
      ->fetchField();
    if (!empty($settings)) {
      $settings = unserialize($settings);
      if ($settings !== FALSE) {
        if ($alt_theme === TRUE) { // Use the active theme's CSS for alternate themes
          $settings['css_path'] = $alt_theme_css_path;
          $settings['css_setting'] = 'theme';
          $settings['css_theme'] = ''; // Active theme
        } else {
          $settings['css_path'] = ($new_theme === 'college') ? $college_css_path : $innovation_css_path;
        }
        $settings = serialize($settings);
        db_update('wysiwyg')
          ->fields(array('settings' => $settings))
          ->condition('format', 'panopoly_wysiwyg_text')
          ->condition('editor', 'tinymce')
          ->execute();
        flogger('theme_update', 'The CSS styling for @theme has been applied to the WYSIWYG'
          . ' editor.',
          array('@theme' => $new_theme),
          WATCHDOG_INFO, TRUE);
      } else {
        // Data wasn't a well-formed, serialized array. Manual CSS paths need to be set.
        flogger('theme_update', 'The WYSIWYG module\'s CSS path setting could not'
          . ' be updated for the @theme theme, so styling within the WYSIWYG window may not match the theme.'
          . ' Please check the CSS Path field vales at @url to see if your theme\'s CSS files are listed properly.',
          array('@theme' => $new_theme,
            '@url' => l('WYSIWYG settings', '/admin/config/content/wysiwyg/profile/panopoly_wysiwyg_text')),
          WATCHDOG_WARNING, TRUE);
      }
    } else {
      flogger('theme_update', 'The WYSIWYG profile data (called "WYSIWYG") could not be found.',
        array(), WATCHDOG_NOTICE);
    }
  }
}
