<?php

/**
 * Implements hook_sql_sync_sanitize().
 */
function smtp_drush_sql_sync_sanitize($site) {
  $sql = 'DELETE FROM variable WHERE name in ("smtp_username", "smtp_host", "smtp_hostbackup", "smtp_on");';

  drush_sql_register_post_sync_op('smtp', dt('Remove sensitive SMTP data'), $sql);
}
