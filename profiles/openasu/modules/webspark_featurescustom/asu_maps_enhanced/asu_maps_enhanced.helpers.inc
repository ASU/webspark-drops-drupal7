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

