<?php
/**
 *  Helper functions for asu_news module
 **/

/**
 * Helper function to get events
 * @param  int     $max_range max number of items to retrieve
 * @param  array   $fields    field names, column id, value, and op to filter by
 * @param  string  $order_by  field name to sort by
 * @param  boolean $pager     to have or not a pager returned with results
 * @return array              event nodes in an array format
 */
function _asu_events_get_asuevents_items($max_range, $fields = NULL, $order_by = NULL, $pager = FALSE, $number = 10, $unique = false) {
  $event_items = array();
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'asu_event')
    ->propertyCondition('status', NODE_PUBLISHED);

  if (!empty($fields)) {
    foreach ($fields as $field) {
      if ($field['name'] == 'field_asuevent_tax_type') {
        $unique = true;
      }
      $query->fieldCondition($field['name'], $field['id'], $field['value'], $field['op']);
    }
  }
  else {
    $query->fieldCondition('field_asuevent_very_start_date', 'value', date("Y-m-d"), '>=');
  }

  if (!empty($order_by)){
    $query->fieldOrderBy('field_photo', 'fid', 'DESC');
  }
  else {
    $query->fieldOrderBy('field_asuevent_very_start_date', 'value', 'ASC');
  }

  $query->range(0, 30);

  if ($pager) {
    $query->pager($number);
  }

  $result = $query->execute();

  if (isset($result['node'])) {
    $event_items_nids = array_keys($result['node']);
    $event_items = entity_load('node', $event_items_nids);
  }

  if($unique) {
    $event_items = _asu_events_filter_unique_title($event_items);
  }

  $event_items = array_slice ( $event_items , 0, $max_range, true );
  return $event_items;
}

function _asu_events_filter_unique_title($event_items) {
  $tmp = array();

  foreach($event_items as $key => $item) {
    if (in_array($item->title, $tmp)) {
      unset($event_items[$key]);
    }
    else {
      $tmp[] = $item->title;
    }
  }
  return $event_items;
}

/**
 * Helper function to get events
 * @param  int     $max_range max number of items to retrieve
 * @param  array   $fields    field names, column id, value, and op to filter by
 * @param  string  $order_by  field name to sort by
 * @param  boolean $pager     to have or not a pager returned with results
 * @return array              event nodes in an array format
 */
function _asu_events_get_asudegrees_items($max_range, $fields = NULL, $order_by = NULL, $pager = FALSE, $number = 10) {
  $degree_items = array();
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'asu_degree')
    ->propertyCondition('status', NODE_PUBLISHED);

  if (!empty($fields)) {
    foreach ($fields as $field) {
      $query->fieldCondition($field['name'], $field['id'], $field['value'], $field['op']);
    }
  }

  $query->range(0, $max_range);

  if ($pager) {
    $query->pager($number);
  }

  $result = $query->execute();

  if (isset($result['node'])) {
    $degree_items_nids = array_keys($result['node']);
    $degree_items = entity_load('node', $degree_items_nids);
  }

  return $degree_items;
}

/**
 * Helper function to retrieve images with styles
 * @param  string         $image_style Name of the image style
 * @param  object         $node        Node object that contains the image
 * @return render array()              Render array with the image information
 */
function _asu_events_get_image($image_style, $node) {
  $image = '';
  $images = field_get_items('node', $node, 'field_asuevent_image');
  if(!empty($images)) {
    $image = field_view_value('node', $node, 'field_asuevent_image', $images[0], array(
        'type' => 'image',
        'settings' => array(
          'image_style' => $image_style, // could be 'thumbnail'
        )
      )
    );
    $image['#item']['attributes'] = array(
     'data-object-fit' => 'cover',
    );
  }
  else {
    $default_img_path = drupal_get_path('module', 'asu_events') . '/theme/images/asu-logo-sq_360.png';

    $image = array(
      '#theme' => 'image',
      '#path' => $default_img_path,
      '#attributes' => array(
        'data-object-fit' => 'cover',
      ),
    );
  }
  return $image;
}

/**
 * Issues with importing the data, this function will render a json object Map
 */
function _asu_events_render_map_from_json($map_json) {
  $display = array();
  $delta = array();
  $element = array();
  $height = array();
  $map_items = drupal_json_decode($map_json);

  if (!empty($map_items)) {
    if ($map_items[0]['name'] == 'maps_enhanced_settings') {
      $map_settings = $map_items[0];

      if (isset($map_settings['map_height'])) {
        $height = $map_settings['map_height'];
      }

      unset($map_items[0]);
    }
  }

  $settings = $display['settings'];
  $formatter = $display['type'];

  $element[0]['#markup'] .= theme('asu_maps_enhanced_view', array(
    'items' => $map_items,
    'delta' => $delta,
    'settings' => $settings,
    'height' => $height,
    'map_settings' => $map_settings
  ));

  return $element;
}

function _asu_events_search_listing_group_nodes_by_day ($nodes_render) {
  $sorted_nodes = array();
  unset($nodes_render['nodes']['#sorted']);
  foreach($nodes_render['nodes'] as $nid => $node) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $date_field = $wrapper->field_asuevent_very_start_date->value();
    $date_field_array = explode('T', $date_field['value']);
    $key = str_replace('-', '_', $date_field_array[0]);
    $sorted_nodes[$key][] = $node;
  }
  return $sorted_nodes;
}

function _asu_events_insert_other_dates_modal() {
  // Include the CTools tools that we need.
      ctools_include('ajax');
      ctools_include('modal');

      // Add CTools' javascript to the page.
      ctools_modal_add_js();

      // Create our own javascript that will be used to theme a modal.
      $other_dates_style = array(
        'other-dates-modal-style' => array(
          'modalSize' => array(
            'type' => 'fixed',
            'width' => 944,
            'height' => 622,
            'addWidth' => 0,
            'addHeight' => 0,
            'contentRight' => 0,
            'contentBottom' => 0,
          ),
          'modalOptions' => array(
            'opacity' => .6,
            'background-color' => '#000',
          ),
          // 'animation' => 'fadeIn',
          'modalTheme' => 'other_dates_modal',
          // Customize the AJAX throbber like so:
          // This function assumes the images are inside the module directory's "images"
          // directory:
          // ctools_image_path($image, $module = 'ctools', $dir = 'images')
          'throbber' => theme('image', array('path' => ctools_image_path('throbber.gif'), 'alt' => t('Loading...'), 'title' => t('Loading'))),
          'closeImage' => theme('image', array('path' => drupal_get_path('module', 'asu_events') . '/theme/images/events-modal-close.png', 'alt' => t(''), 'title' => t(''))),
        ),
      );
    // Add the settings array defined above to Drupal 7's JS settings:
    drupal_add_js($other_dates_style, 'setting');
    // The function below assumes the happy.js file resides in [module_dir]/js
    ctools_add_js('asu_events', 'asu_events', 'theme/js');
    // // The function below assumes the happy.css file resides in [module_dir]/css
    // ctools_add_css('happy', 'happy');
}

function _asu_events_get_all_terms_by_parent($vid) {
  $tree = taxonomy_get_tree($vid);
  $terms = array();
  foreach($tree as $item) {
    $terms[$items->tid] = $items->title;
  }
  return $terms;
}

function _asu_events_has_other_dates($node) {
  $title = $node->title;

  $query = new EntityFieldQuery();


 $entities = $query->entityCondition('entity_type', 'node')
  ->propertyCondition('type', 'asu_event')
  ->propertyCondition('title', $title)
  ->propertyCondition('status', 1)
  ->fieldCondition('field_asuevent_very_start_date', 'value', date("Y-m-d"), '>=')
  ->execute();

  $event_items = array();

  if (isset($entities['node'][$node->nid])) {
    unset($entities['node'][$node->nid]);
  }

  if (!empty($entities['node'])) {
    $event_items_nids = array_keys($entities['node']);
    $event_items = entity_load('node', $event_items_nids);
  }

  return (!empty($event_items));
}
