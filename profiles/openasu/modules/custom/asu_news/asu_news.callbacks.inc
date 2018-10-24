<?php
/**
 * Page to handle all callbacks for asu news modules
 */

/**
 * Callback function for select drop down configuration on Events block panel
 * @param  string $string String to match event name
 * @return json           Outputs a json object with the events matching the passed string
 */
function select_all_asu_news($string) {
  $result = db_query("SELECT title, nid FROM {node} WHERE title LIKE '%$string%' AND type = 'asu_news' LIMIT 10");
  $matches = array();
  foreach($result as $item) {
    $key = sprintf('%s [nid: %d]', $item->title, $item->nid);
    $matches[$key] = check_plain($item->title);
  }
  drupal_json_output($matches);
  exit;
}
