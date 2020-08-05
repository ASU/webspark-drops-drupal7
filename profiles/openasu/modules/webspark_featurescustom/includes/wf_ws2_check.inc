<?php

/**
 * Check for a particular theme
 * @param string $theme_to_check - machine name of theme to check for as the current, default theme
 * @param string $suffix - Suffix to append to the CSS file name as the alternate CSS file. Defaults to _ws2
 * @return string
 */
function _webspark_featurescustom_ws2_check($theme_to_check = 'elpuente', $suffix = '_ws2') {
  global $theme;
  return ($theme === $theme_to_check) ? $suffix : '';
}
