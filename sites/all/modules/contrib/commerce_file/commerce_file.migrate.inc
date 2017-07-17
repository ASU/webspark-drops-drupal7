<?php

/**
 * @file
 * Integration with the Migrate module.
 */

/*
 * Implements hook_migrate_api().
 */
function commerce_file_migrate_api() {
  $api = array(
    'api' => 2,
    'field handlers' => array(
      'MigrateCommerceFileFieldHandler',
    ),
  );
  return $api;
}
