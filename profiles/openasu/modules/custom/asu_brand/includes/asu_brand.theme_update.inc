<?php

/**
 * Update/insert header/footer placement for Web standards themes.
 *
 * @param string $theme - The current/new theme machine name
 * @param array $ws_data - Contains both the current and previous header version at the time of this change.
 * @throws InvalidMergeQueryException
 */
function asu_brand_block_theme_update($theme, $ws_data) {
  if ($theme === '__standalone__') { // ASU Brand standalone code
    $theme = variable_get('theme_default');
  }
  if (empty($ws_data)) { // Defaults to WS1.0
    $ws_data['curr_suffix'] = '';
    $ws_data['kill_suffix'] = '_ws2';
  }
  try {
    // Enable the Global header block
    db_merge('block')
      ->key(array(
        'module' => 'asu_brand',
        'delta' => 'asu_brand_header' . $ws_data['kill_suffix'],
        'theme' => $theme,
      ))
      ->fields(array(
          'region' => '-1',
          'status' => '0',
        )
      )->execute();
    db_merge('block')
      ->key(array(
        'module' => 'asu_brand',
        'delta' => 'asu_brand_header' . $ws_data['curr_suffix'],
        'theme' => $theme,
      ))
      ->fields(array(
          'region' => 'header',
          'status' => '1',
        )
      )->execute();

//    // Enable the Global footer block
    db_merge('block')
      ->key(array(
        'module' => 'asu_brand',
        'delta' => 'asu_brand_footer' . $ws_data['kill_suffix'],
        'theme' => $theme,
      ))
      ->fields(array(
          'region' => '-1',
          'status' => '0',
        )
      )->execute();
    $weight = db_select('block', 'b')
      ->fields('b', array('weight'))
      ->condition('region', 'footer')
      ->condition('theme', $theme)
      ->condition('delta', 'mega_footer')
      ->execute()
      ->fetchField();
    $weight = (int)$weight + 1;
    db_merge('block')
      ->key(array(
        'module' => 'asu_brand',
        'delta' => 'asu_brand_footer' . $ws_data['curr_suffix'],
        'theme' => $theme,
      ))
      ->fields(array(
          'region' => 'footer',
          'status' => '1',
          'weight' => $weight,
        )
      )->execute();
    drupal_set_message('The Web standards header and footer blocks have been updated for the ' . strtoupper(check_plain($theme))
      . ' theme.', 'status', FALSE);
  } catch (Exception $e) {
    $message = 'All Web standards blocks for ' . check_plain($theme) . ' could not be updated or created'
      . ' by the ASU Brand module. Go to <a href="/admin/structure/block/list/' . check_plain($theme)
      . '">' . check_plain($theme) . ' to place the blocks in their proper locations.';
    watchdog('asu_brand', $message, array(), WATCHDOG_ERROR);
    drupal_set_message($message, 'error', FALSE);
  }
}

/**
 * Get header version, suffix of block machine names based on theme (or subtheme name)
 *
 * @param $ws_theme_test_result
 * @return array|string[] settings
 */
function asu_brand_get_ws_data($ws_theme_test_result) {
  $ws_data = array();
  switch ($ws_theme_test_result) {
    case 'college':
      return array(
        'curr_version' => '5.0',
        'curr_suffix' => '_ws2',
        'kill_version' => 'stable',
        'kill_suffix' => '',
      );
    case 'innovation':
      return array(
        'curr_version' => 'stable',
        'curr_suffix' => '',
        'kill_version' => '5.0',
        'kill_suffix' => '_ws2',
      );
    default:
      return $ws_data;
  }
}
