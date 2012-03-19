<?php
/**
 * @file
 * Implements Views integration.
 */

/**
 * Implementation of hook_views_handlers().
 */
function office_hours_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'office_hours') . '/includes',
    ),
    'handlers' => array(
      'office_hours_handler_filter_hours' => array(
        'parent' => 'views_handler_filter_numeric',
      ),
      'office_hours_handler_filter_day' => array(
        'parent' => 'content_handler_filter_many_to_one',
      ),
    ),
  );
}
