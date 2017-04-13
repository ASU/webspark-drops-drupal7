<?php
/**
 * @file
 * Default Views for the Commerce Event Ticket module.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_event_ticket_views_default_views() {
  $views_dir = drupal_get_path('module', 'commerce_event_ticket') . '/includes/views';
  $views_files = scandir($views_dir);
  $views = array();
  foreach ($views_files as $filename) {
    if (substr($filename, -4) == '.inc') {
      include_once $views_dir . '/' . $filename;
    }
  }
  return $views;
}
