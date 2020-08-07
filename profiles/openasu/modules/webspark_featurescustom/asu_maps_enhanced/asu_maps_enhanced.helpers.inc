<?php

function asu_maps_enhanced_get_default_settings() {
  $map_settings = [
    'name' => 'maps_enhanced_settings',
    'map_height' => 642,
  ];

  return $map_settings;
}

/**
 * Get the GIS map layers from API endpoint
 */
function asu_maps_enhanced_get_layers() {
  $tree = NULL;

  if ($cache = cache_get('asu_maps_enhanced_gis_layer_tree')) {
    $tree = drupal_json_decode($cache->data);
  }
  // Create content and cache if no cache available
  else {

    $url = 'https://' . ASU_MAPS_ENHANCED_GIS_HOST . ASU_MAPS_ENHANCED_GIS_LAYERS_PATH;
    $request = drupal_http_request($url);

    if ($request->code == 200) {
      $data = drupal_json_decode($request->data);

      $layers = $data['operationalLayers'];

      foreach ($layers as $topkey => &$layer) {

        if ($layer['layerType'] != 'ArcGISMapServiceLayer') {
          unset($layers[$topkey]);
          continue;
        }

        $layer['value'] = $layer['id'];
        $layer['label'] = $layer['title'];

        unset($layer['visibleLayers']);

        $layer['children'] = $layer['layers'];
        unset($layer['layers']);


        foreach ($layer['children'] as $key =>  &$sublayer) {

          if ($sublayer['name'] != NULL) {
            unset($sublayer['popupInfo']);
            $sublayer['value'] = $layer['id'] . '_' . $sublayer['id'];
            $sublayer['label'] = $sublayer['name'];

          // if no name is provided for layer, don't include it into the
          // renderable tree
          } else {
            unset($layer['children'][$key]);
          }
        }
      }

      $cached_copy = drupal_json_encode($layers);
      $expire_date = time() + 3600 * ASU_MAPS_ENHANCED_TREE_CACHE_DURATION;

      cache_set('asu_maps_enhanced_gis_layer_tree', $cached_copy, 'cache', $expire_date);

      $tree = $layers;
    }
  }

  return $tree;
}
