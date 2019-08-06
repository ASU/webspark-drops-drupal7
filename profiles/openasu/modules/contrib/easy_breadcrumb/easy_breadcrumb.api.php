<?php

/**
 * @file
 * API documentation file for Easy Breadcrumb.
 */

/**
 * Allows modules to alter the path to calculate the breadcrumb.
 *
 * @param string $path
 *   The current drupal path returned by drupal_get_path_alias().
 */
function hook_easy_breadcrumb_path_alter(&$path) {
  // Replace the path to calculate the breadcrumb for.
  // The printmail page in the print module.
  $args = arg();
  if ($args[0] == 'printmail') {
    $args[] = array_shift($args);
    $path = implode('/', $args);
  }
}

/**
 * Allows modules to alter the breadcrumb displayed in the block.
 *
 * @param array $breadcrumb
 *   The breadcrumb array returned to render in the block.
 */
function hook_easy_breadcrumb_breadcrumb_alter(array &$breadcrumb) {
  // Remove the last breadcrumb element for node pages.
  $args = arg();
  if ($args[0] == 'node') {
    array_pop($breadcrumb);
  }
}
