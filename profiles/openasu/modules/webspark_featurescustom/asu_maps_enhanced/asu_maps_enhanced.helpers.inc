<?php

function asu_maps_enhanced_get_default_settings() {
  $map_settings = array(
    'display_campus_select' => 'NO',
    'campus' => 'NONE',
    'name' => 'maps_enhanced_settings',
    'map_height' => 642,
    'hide_map' => 'YES',
    'campus_coords' => asu_maps_enhanced_get_campus_coords()
  );

  return $map_settings;

}

function asu_maps_enhanced_get_campus_coords() {
  return array(
    "THUNDERBIRD" => "mc/33.6224937,-112.1847479?z/17",
    "POLY" => "mc/33.30463351165877,-111.67764695106507?z/16",
    "DOWNTOWN" => "mc/33.4517422046421,-112.06978201586912?z/16",
    "WEST" => "mc/33.60560202626335,-112.16131285054018?z/16",
    "RESEARCH" => "mc/33.34149389022663,-111.89817340740967?z/16",
    "SKYSONG" => "mc/33.46387500000001,-111.92400399999997?z/17",
    "HAVASU" => "mc/34.472362999999994,-114.32183099999997?z/18",
    "TEMPE" => "mc/33.42184849843031,-111.9283177883301?z/15"
  );
}

/***
 * Returns a JSON representation of the campus bird tree data
 */
function asu_maps_enhanced_json_tree()
{

  $tree = NULL;

  // Check for cache
  if ($cache = cache_get('asu_maps_enhanced_cbird_tree')) {
    $tree = $cache->data;
  }
  // Create content and cache if no cache available
  else {

    //Get the tree and cache
    $tree = asu_maps_enhanced_get_cbird_tree();

    // Create cache, set to hold cache for number of hours specified
    if (count($tree['children']) > 0) {

      $tree = json_encode($tree);

      $expire_date = time() + 3600 * ASU_MAPS_ENHANCED_TREE_CACHE_DURATION;
      cache_set('asu_maps_enhanced_cbird_tree', $tree, 'cache', $expire_date);
    }
  }

  return $tree;
}


/***
 * Get the campus bird data and treeify it
 */
function asu_maps_enhanced_get_cbird_tree()
{

  $locations = asu_maps_enhanced_get_cbird('locations', '', TRUE);
  $categories = asu_maps_enhanced_get_cbird('categories', '', TRUE);

  $tree = array(
    'catId' => 0,
    'children' => array()
  );

  $stop = FALSE;

  //Add categories to the tree
  while (!$stop) {

    // We compare the count of categories before and after the foreach loop.
    // If no more items can be placed into the tree, then set stop to TRUE,
    // and exit the while loop
    $before = count($categories);

    foreach ($categories as $key => $cat) {
      if (asu_maps_enhanced_find_parent($tree, $cat, 'category')) {
        unset($categories[$key]);
      }
    }

    $after = count($categories);

    // if we went through all categories without finding anymore parents,
    // then stop
    if ($before == $after) {
      $stop = TRUE;
    }
  }

  $stop = FALSE;

  // Add locations to the tree
  while (!$stop) {

    $before = count($locations);

    foreach ($locations as $key => $loc) {
      if (asu_maps_enhanced_find_parent($tree, $loc, 'location')) {
        unset($locations[$key]);
      }
    }

    $after = count($locations);

    // if we went through all remaining locations without finding anymore parents,
    // then stop
    if ($before == $after) {
      $stop = TRUE;
    }
  }

  return $tree;
}

/***
 * Adds individual items to a tree of campus bird items (2 types - categories and locations)
 *
 * @param $tree - a tree of campus bird items
 * @param $bird - item to place into the tree
 * @return bool - returns TRUE if item is successfully placed into the tree
 */
function asu_maps_enhanced_find_parent(&$tree, $bird, $type)
{

  if ($type == 'category' && isset($tree['catId'])) {

    //if the tree item has a category, id, and the item has a
    if ($tree['catId'] == $bird['parent']) {
      if (isset($tree['children'])) {
        $tree['children'][] = $bird;
      } else {
        $tree['children'] = array(
          $bird
        );
      }

      return TRUE;
    } else {
      if (isset($tree['children'])) {
        $test = FALSE;

        foreach ($tree['children'] as $key => $child) {

          $test = asu_maps_enhanced_find_parent($tree['children'][$key], $bird, $type);

          if ($test) {
            return TRUE;
          }
        }

        return $test;
      } else {
        return FALSE;
      }
    }
  } else {
    if ($type == 'location' && !isset($tree['id']) && isset($bird['catId'])) {
      //if the tree item has a category, id, and the item has a
      if ($tree['catId'] == $bird['catId']) {
        if (isset($tree['children'])) {
          $tree['children'][] = $bird;
        } else {
          $tree['children'] = array(
            $bird
          );
        }

        return TRUE;
      } else {
        if (isset($tree['children'])) {
          $test = FALSE;

          foreach ($tree['children'] as $key => $child) {

            $test = asu_maps_enhanced_find_parent($tree['children'][$key], $bird, $type);

            if ($test) {
              return TRUE;
            }
          }

          return $test;
        } else {
          return FALSE;
        }
      }
    } else {
      return FALSE;
    }
  }
}

/**
 *Function to get json objects from campus bird
 * @param  string $type needs to be either locations or categories for now
 * @param string $category is the category id of locations to return (optional)
 * @param boolean $visible , if set to true, will only return an array of items
 *        which are set to private=0 by Campus Bird
 */
function asu_maps_enhanced_get_cbird($type, $category = '', $visible = TRUE)
{
  $visible = $visible || FALSE;
  $URL1 = ASU_MAPS_ENHANCED_API_ENDPOINT;
  $KEY = '&key=' . ASU_MAPS_ENHANCED_API_USAGE_KEY;
  $MAP = '?map=120';
  $COD = NULL;

  switch ($type) {
    case 'locations':
      //list of locations
      $COD = $URL1 . $type . '/' . $category . $MAP . $KEY;
      break;
    case 'categories':
      //list of categories
      $COD = $URL1 . $type . $MAP . $KEY;
      break;
  }

  $request = drupal_http_request($COD);
  $jsonarray = drupal_json_decode($request->data);

  if ($visible) {
    $filtered = array_filter($jsonarray, function ($x) {
      return $x['private'] == '0';
    });

    return $filtered;
  }

  return $jsonarray;
}

/***
 * Get proper YES/NO value from the
 *
 */
function asu_maps_enhanced_get_select_value($item, $key) {

  $defaults = asu_maps_enhanced_get_default_settings();

  if (!isset($item[$key])) {
    return $defaults[$key];
  }

  if ($item[$key] !== 'NO' && $item[$key] !== '0') {
    $value = ($item[$key]) ? 'YES' : 'NO';

    return $value;
  }
  else {
    return 'NO';
  }
}

