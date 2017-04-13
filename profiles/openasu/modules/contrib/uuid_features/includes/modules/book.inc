<?php
/**
 * @file
 * uuid_node hooks on behalf of the book module.
 */

/**
 * Implements hook_uuid_node_features_export_render_alter().
 *
 * For root book pages - set bid to new. For child pages set a parent_uuid
 * to use on rebuild. Clear all other book properties.
 */
function book_uuid_node_features_export_render_alter(&$export, $node, $module) {
  if (isset($node->book) && isset($node->book['bid']) && isset($node->book['nid'])) {
    $node_book_export = array();
    // $export->book = array();
    if ($node->book['bid'] == $node->book['nid']) {
      $node_book_export['bid'] = 'new';
    }
    elseif (isset($node->book['plid'])) {
      $parent_menu_link = book_link_load($node->book['plid']);
      $parent_node = node_load($parent_menu_link['nid']);
      if (!empty($parent_node)) {
        $node_book_export['parent_uuid'] = $parent_node->uuid;
        $node_book_export['weight'] = $node->book['weight'];
      }
    }

    $export->book = $node_book_export;
  }
}

/**
 * Implements hook_uuid_node_features_rebuild_alter().
 *
 * Replace book parent uuid's with the valid book parameters. As there is no way
 * to guarantee the correct top-down hierarchical order - collect orphan
 * book nodes for post node rebuild processing.
 */
function book_uuid_node_features_rebuild_alter($node, $module) {
  if (isset($node->book)) {
    if (isset($node->book['parent_uuid'])) {
      $parent_node = entity_uuid_load('node', array($node->book['parent_uuid']));
      $parent_node = reset($parent_node);

      if ($parent_node && isset($parent_node->book['mlid'])) {
        // Set up node as for add child page.
        $node->book['bid'] = $parent_node->book['bid'];
        $node->book['plid'] = $parent_node->book['mlid'];
        $node->book['menu_name'] = $parent_node->book['menu_name'];
        $node->book['weight'] = $node->book['weight'];
      }
      else {
        // Add to pending.
        _book_uuid_node_features_pending($node);
      }
    }
  }
  $existing = entity_uuid_load('node', array($node->uuid));
  $existing = reset($existing);
  if (!empty($existing->book['mlid'])) {
    $node->book['mlid'] = $existing->book['mlid'];
  }
}

/**
 * Implements hook_uuid_entity_features_rebuild_complete().
 *
 * Ensure complete book structure has been set up.
 */
function book_uuid_entity_features_rebuild_complete($entity_type, $entities, $module) {
  if ($entity_type == 'node') {
    // Reset the node cache.
    node_load(FALSE, NULL, TRUE);

    $pending = _book_uuid_node_features_pending();
    if (!empty($pending)) {
      // Sort so that parent nodes come before child nodes.
      $pending = _book_uuid_node_features_pending_sort($pending);
    }

    foreach ($pending as $uuid => $book) {
      $book_page_node = entity_uuid_load('node', array($uuid));
      $book_page_node = reset($book_page_node);

      $parent_node = entity_uuid_load('node', array($book['parent_uuid']));
      $parent_node = reset($parent_node);

      // Set up node as for add child page.
      $book_page_node->book['bid'] = $parent_node->book['bid'];
      $book_page_node->book['plid'] = $parent_node->book['mlid'];
      $book_page_node->book['menu_name'] = $parent_node->book['menu_name'];
      $book_page_node->book['weight'] = $book['weight'];

      node_save($book_page_node);
      node_load($book_page_node->nid, NULL, TRUE);
    }
  }
}

/**
 * Any pages with no parent page are put here to be processed later.
 */
function _book_uuid_node_features_pending($node = NULL) {
  static $pending = array();

  if (!is_null($node)) {
    $pending[$node->uuid] = $node->book;
  }
  else {
    return $pending;
  }
}

/**
 * Sort callback to put parents before children.
 */
function _book_uuid_node_features_pending_sort($pending) {
  $pending_by_parent = array();

  // Group by parent.
  foreach ($pending as $uuid => $book) {
    $parent_uuid = $book['parent_uuid'];
    if (empty($pending_by_parent)) {
      $pending_by_parent[$parent_uuid] = array();
    }

    $pending_by_parent[$parent_uuid][$uuid] = $book;
  }

  $sorted_pending = array();

  // Find top-level parents and get all ancestors in order.
  foreach ($pending_by_parent as $parent_uuid => $books) {
    if (empty($pending[$parent_uuid])) {
      // This is a top-level pending - recurse from here.
      $sorted_pending = array_merge($sorted_pending, _book_uuid_node_features_pending_get_ancestors($parent_uuid, $pending_by_parent));
    }
  }

  return $sorted_pending;
}

/**
 * Recursively collect ancestor nodes in top-down order.
 */
function _book_uuid_node_features_pending_get_ancestors($parent_uuid, $pending_by_parent) {
  $sorted_pending = array();

  if (!empty($pending_by_parent[$parent_uuid])) {
    foreach ($pending_by_parent[$parent_uuid] as $uuid => $book) {
      $sorted_pending[$uuid] = $book;
      $sorted_pending = array_merge($sorted_pending, _book_uuid_node_features_pending_get_ancestors($uuid, $pending_by_parent));
    }
  }

  return $sorted_pending;
}
