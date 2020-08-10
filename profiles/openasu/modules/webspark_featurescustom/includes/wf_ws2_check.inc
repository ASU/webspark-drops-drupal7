<?php

/**
 * Check for a particular theme
 * @param bool $need_admin - Need to check against the admin theme (not the default theme). Defaults to FALSE. (Useful
 * when needing to check if Web Standards 2.0 is enabled but do not want it applied or assumed in an admin theme managed area.
 * @param string $theme_to_check - machine name of theme to check for as the current, default theme
 * @param string $suffix - Suffix to append to the CSS file name as the alternate CSS file. Defaults to _ws2
 * @return string
 */
function _webspark_featurescustom_ws2_check($need_admin = FALSE, $theme_to_check = 'elpuente', $suffix = '_ws2') {
  global $theme;
  // Return the default theme if the admin theme isn't the same
  if ($need_admin) {
    if ($theme !== variable_get('theme_default')) {
      $theme = variable_get('theme_default');
    }
  }
  return ($theme === $theme_to_check) ? $suffix : '';
}
