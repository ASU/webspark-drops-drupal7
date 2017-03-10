<?php

/**
 * Implements hook_node_delete()
 */
function asu_isearch_node_delete($node) {
  if ($node->type == 'asu_isearch_profile') {
    db_delete('migrate_map_migrateisearchprofile')
      ->condition('destid1', $node->nid)
      ->execute();
  }
}
