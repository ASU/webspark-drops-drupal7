<?php
/**
 * @file
 * A configuration file for Commerce Event Ticket PDF's use of TCPDF.
 *
 * This only sets the TCPDF cache directory.
 */

$cache_dir = 'temporary://commerce_event_ticket/pdf-cache';

// Set a different cache directory for CLI (Drush) usage. This helps when the
// files are not writable for both the user running Drush and the web server at
// the same time.
if (defined('STDIN')) {
  $cache_dir = 'temporary://commerce_event_ticket_cli/pdf-cache';
}

if (!file_exists($cache_dir)) {
  mkdir($cache_dir, 0755, TRUE);
  chmod(drupal_realpath($cache_dir), 0755);
}
define('K_PATH_CACHE', drupal_realpath($cache_dir));
