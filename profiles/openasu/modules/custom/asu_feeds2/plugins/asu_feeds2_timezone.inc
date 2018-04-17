<?php

$plugin = array(
  'form' => 'asu_feeds2_timezone_form',
  'callback' => 'asu_feeds2_timezone_callback',
  'name' => 'Adjust imported time for timezone',
);

function asu_feeds2_timezone_form($importer, $element_key, $settings) {
  $form = array();

  $form['timezone'] = array(
    '#type' => 'textfield',
    '#title' => t('Length'),
    '#description' => t('Timezone used to adjust incoming timestamp, defaults to America/Phoenix'),
    '#default_value' => isset($settings['timezone']) ? $settings['timezone'] : 'America/Phoenix',
    '#size' => 10,
    '#required' => TRUE,
  );

  return $form;
}

function asu_feeds2_timezone_callback($result, $item_key, $element_key, &$field, $settings) {
  $tz_str = isset($settings['timezone']) ? $settings['timezone'] : 'America/Phoenix';

  $field = $field + (7*3600); // 3600 seconds = 1 hour
}
