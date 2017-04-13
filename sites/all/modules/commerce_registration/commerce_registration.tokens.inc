<?php
/**
 * @file
 * Add token for Commerce Order to Registrations.
 */

/**
 * Implements hook_token_info_alter().
 *
 * @param $data
 */
function commerce_registration_token_info_alter(&$data) {
  $data['tokens']['registration']['commerce_order'] = array(
    'name' => t('Commerce Order ID'),
    'description' => t('The Commerce order number that the registration belongs to.'),
  );
}

/**
 * Implements hook_tokens().
 *
 * @param $type
 * @param $tokens
 * @param array $data
 * @param array $options
 * @return array
 */
function commerce_registration_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $items = array();
  if (!isset($data['registration'])) {
    return array();
  }
  $reg = $data['registration'];
  if ($type == 'registration') {
    foreach ($tokens as $key => $token) {
      switch ($key) {
        case "commerce_order":
          $items[$token] = $reg->order_id;
          break;
      }
    }
  }
  return $items;
}
