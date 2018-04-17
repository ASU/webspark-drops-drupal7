<?php
/**
 * Page to handle all callbacks for asu events module
 */

/**
 * Callback function for select drop down configuration on Events block panel
 * @param  string $string String to match event name
 * @return json           Outputs a json object with the events matching the passed string
 */
function select_all_asu_events($string) {
  $result = db_query("SELECT title, nid FROM {node} WHERE title LIKE '%$string%' AND type = 'asu_event' LIMIT 20");
  $matches = array();
  foreach($result as $item) {
    $key = sprintf('%s [nid: %d]', $item->title, $item->nid);
    $matches[$key] = check_plain($item->title);
  }
  drupal_json_output($matches);
  exit;
}

/**
 * Callback function for select drop down configuration on Events block panel
 * @param  string $string String to match event name
 * @return json           Outputs a json object with the events matching the passed string
 */
function select_all_content_types($string) {
  $result = node_type_get_types();
  $matches = array();
  foreach($result as $key => $item) {
    $matches[$key] = check_plain($item->name);
  }
  drupal_json_output($matches);
  exit;
}

/**
 * Callback function for select drop down configuration on Events block panel
 * @param  string $string String to match event name
 * @return json           Outputs a json object with the events matching the passed string
 */
function get_all_asu_events_vocab($string) {
  $result = db_query("SELECT name, vid FROM {taxonomy_vocabulary} WHERE name LIKE '%$string%' LIMIT 20");
  $matches = array();
  foreach($result as $item) {
    $key = sprintf('%s [vid: %d]', $item->name, $item->vid);
    $matches[$key] = check_plain($item->name);
  }
  drupal_json_output($matches);
  exit;
}
