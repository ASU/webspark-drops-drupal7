<?php

/**
 * Get WS2.0 suffix to append to files/assets if the default/active theme is an ASU Web standars 2.0 theme
 * @param bool $need_admin - Need to check against the admin theme (not the default theme). Defaults to FALSE. (Useful
 * when needing to check if Web Standards 2.0 is enabled but do not want it applied or assumed in an admin theme managed area.
 * @param string $theme_to_check - machine name of theme to check for as the current, default theme. Defaults to El Puente theme.
 * @param string $suffix - Suffix to append to the CSS file name as the alternate CSS file. Defaults to _ws2
 * @return string - Returns the suffix passed in IF $theme === checked theme.
 */
function _webspark_featurescustom_ws2_check($need_admin = FALSE, $theme_to_check = 'elpuente', $suffix = '_ws2') {
  $theme = &drupal_static(__FUNCTION__);
  if (!isset($theme)) {
    global $theme;
    if ($need_admin) {
      // Return the default theme if the admin theme isn't the same
      if ($theme !== variable_get('theme_default')) {
        $theme = variable_get('theme_default');
      }
    }
    // Now check if theme or base theme (WS2.0 only). If base theme, get that theme's name instead.
    $theme = _webspark_featurescustom_ws_theme_check($theme, 2);
  }
  return ($theme === $theme_to_check) ? $suffix : '';
}
