<?php

/**
 * Check for WS2 theme
 * @return string
 */
function _webspark_featurescustom_ws2_check() {
  global $theme;
  $ws2_check = ($theme === 'elpuente') ? '_ws2' : '';
  return $ws2_check;
}
