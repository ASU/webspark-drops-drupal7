<?php

/**
 * @file
 * Token module integration.
 */

/**
 * Implements hook_token_info_alter().
 */
function cas_attributes_token_info_alter(&$data) {
  if (function_exists('cas_phpcas_attributes')) {
    $data['tokens']['cas']['attribute'] = array(
      'name' => t('Attribute'),
      'description' => t('A CAS attribute of the user. (Only available if user is logged into CAS). Always stored as an array token (thus supporting multivalue attributes); therefore be sure to remember to specify which array member you want (for instance, to get the first value: [cas:attribute:?:first]).  <a href="@url">Available tokens</a>.', array('@url' => url('admin/config/people/cas/attributes/cas'))),
      'dynamic' => TRUE,
    );
  }
}

/**
 * Implements hook_tokens().
 */
function cas_attributes_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $sanitize = !empty($options['sanitize']);
  $replacements = array();

  if ($type == 'cas' && !empty($data['cas'])) {
    $cas = $data['cas'];

    // Provide [cas:attribute:?] dynamic tokens.
    if ($attribute_tokens = token_find_with_prefix($tokens, 'attribute')) {
      $attribute = array_change_key_case(cas_phpcas_attributes($cas));
      foreach ($attribute_tokens as $name => $original) {
        // If there are no options specified have it return all values.
        if (strpos($name, ':') === FALSE) {
          $name .= ':join';
        }

        // Break out the token into attributes and the options for them.
        list($name, $token) = explode(':', $name, 2);

        $name = drupal_strtolower($name);
        if (isset($attribute[$name])) {
          $value = $attribute[$name];
          if (!is_array($value)) {
            $value = array($value);
          }
          $replacements += token_generate('array', array($token => $original), array('array' => $value), $options);
        }
        elseif ($name == '?') {
          $keys = array_keys($attribute);
          if ($sanitize) {
            $keys = array_map('check_plain', $keys);
          }
          $replacements[$original] = t('Available attributes: %keys', array('%keys' => implode(', ', $keys)));
        }
      }
    }
  }

  return $replacements;
}
