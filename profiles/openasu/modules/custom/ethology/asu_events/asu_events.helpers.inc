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
function _asu_events_get_asuevents_items($max_range, $fields = NULL, $order_by = NULL, $pager = FALSE) {
  $event_items = array();
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'asu_event')
    ->propertyCondition('status', NODE_PUBLISHED);

  if (!empty($fields)) {
    foreach ($fields as $field) {
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

  $query->range(0, $max_range);

  if ($pager) {
    $query->pager(10);
  }

  $result = $query->execute();

  if (isset($result['node'])) {
    $event_items_nids = array_keys($result['node']);
    $event_items = entity_load('node', $event_items_nids);
  }

  return $event_items;
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
