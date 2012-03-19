<?php

/**
 * @file
 * Display suite Extras page functions.
 */

/**
 * Menu callback: show an individual node with the Switch field.
 */
function ds_extras_node_page_view($node) {

  // If there is a menu link to this node, the link becomes the last part
  // of the active trail, and the link name becomes the page title.
  // Thus, we must explicitly set the page title to be the node title.
  drupal_set_title($node->title);
  $uri = entity_uri('node', $node);
  // Set the node path as the canonical URL to prevent duplicate content.
  drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);

  // Update the history table, stating that this user viewed this node.
  node_tag_new($node);

  // For markup consistency with other pages, use node_view_multiple() rather than node_view().
  $view_mode = (!empty($node->ds_switch)) ? $node->ds_switch : 'full';

  // It's also possible to use $_GET['v'] to switch view modes.
  if (isset($_GET['v']) && !empty($_GET['v'])) {
    $view_mode = $_GET['v'];
  }
  drupal_static('ds_extras_view_mode', $view_mode);
  return node_view_multiple(array($node->nid => $node), $view_mode);
}

/**
 * Menu callback: show an individual revision node using the revision view mode.
 */
function ds_extras_revision_node_show($node, $message = NULL) {

  drupal_set_title(t('Revision of %title from %date', array('%title' => $node->title, '%date' => format_date($node->revision_timestamp))), PASS_THROUGH);

  // Update the history table, stating that this user viewed this node.
  node_tag_new($node);

  // Determine view mode.
  $layout = ds_get_layout('node', $node->type, 'revision', FALSE);
  $view_mode = ($layout) ? 'revision' : 'full';
  drupal_static('ds_extras_view_mode', $view_mode);

  // For markup consistency with other pages, use node_view_multiple() rather than node_view().
  return node_view_multiple(array($node->nid => $node), $view_mode);
}

/**
 * Menu callback: switches to another view mode inline.
 */
function ds_switch_view_mode_inline() {

  $content = '';
  $status = TRUE;
  $error = FALSE;

  $id = $_REQUEST['id'];
  $view_mode = $_REQUEST['view_mode'];
  $entity_type = $_REQUEST['entity_type'];
  $entity = entity_load($entity_type, array($id));

  if (!isset($entity[$id])) {
    $status = FALSE;
    $error = t('Content was not found.');
  }
  else {
    if (node_access('view', $entity[$id])) {
      $element = node_view($entity[$id], $view_mode);
      $content = drupal_render($element);
    }
    else {
      $error = t('Access denied');
    }
  }

  drupal_add_http_header('Content-Type', 'text/javascript; charset=utf-8');
  print drupal_json_encode(array(
    'status' => $status,
    'content' => $content,
    'errorMessage' => $error,
  ));
  exit();
}

/**
 * Menu callback: redirect to manage display.
 */
function ds_extras_contextual_page_tab($object, $entity_type) {

  switch ($entity_type) {
    case 'node':
      $bundle = $object->type;
      $view_mode = (!empty($object->ds_switch)) ? $object->ds_switch : 'full';

      // Let's always go back to the node page.
      $destination = 'node/' . $object->nid;
      break;
    case 'user':
      $bundle = 'user';
      $view_mode = 'full';
      $destination = 'user/' . $object->uid;
      break;
    case 'taxonomy_term':
      $bundle = $object->vocabulary_machine_name;
      $view_mode = 'full';
      $destination = 'taxonomy/term/' . $object->tid;
      break;
  }

  // Check if we have a configured layout. Do not fallback to default.
  $layout = ds_get_layout($entity_type, $bundle, $view_mode, FALSE);

  // Get the manage display URI.
  $admin_path = _field_ui_bundle_admin_path($entity_type, $bundle);

  // Check view mode settings.
  $view_mode_settings = field_view_mode_settings($entity_type, $bundle);
  $overriden = (!empty($view_mode_settings[$view_mode]['custom_settings']) ? TRUE : FALSE);

  if (empty($layout) && !$overriden) {
    $admin_path .= '/display';
  }
  else {
    $admin_path .= '/display/' . $view_mode;
  }

  drupal_goto($admin_path, array('query' => array('destination' => $destination)));
}
