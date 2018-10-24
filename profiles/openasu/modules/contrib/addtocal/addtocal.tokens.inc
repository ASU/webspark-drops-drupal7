<?php
/**
 * @file
 * Token module integration.
 */

/**
 * Implements hook_token_info_alter().
 */
function addtocal_token_info_alter(&$info) {

  $entities = addtocal_get_addtocal_entities();

  foreach ($entities as $entity_name => $fields) {
    foreach ($fields as $field_name => $display) {
      $info['tokens'][$entity_name][$field_name]['addtocal'] = array(
        'name' => t('Add to cal'),
        'description' => t("Rendered AddToCal html block, suitable for onsite use or in the body of an email message."),
        'module' => 'addtocal',
        'type' => 'date',
      );
    }
  }
}

/**
 * Implements hook_tokens().
 */
function addtocal_tokens($type, $tokens, array $data = array(), array $options = array()) {

  $replacements = array();

  if ($type == 'entity' && !empty($data['entity'])) {

    $sanitize = !empty($options['santitize']);

    // Get basic entity info
    $entity_type = $data['entity_type'];
    list($entity_id) = entity_extract_ids($entity_type, $data['entity']);

    // Get Add to Cal entities list
    $entities = addtocal_get_addtocal_entities();

    if (array_key_exists($entity_type,$entities)) {

      foreach ($tokens as $name => $original) {
        $field_type = explode(":",$name);
        $field_type = $field_type[0];
        if (array_key_exists($field_type, $entities[$entity_type]) && strpos($original,'addtocal') !== FALSE) {
          $field = $data['entity']->$field_type;
          $field = $field['und'][0];

          // Set start date, end date, timezone
          if (is_array($field['value'])) {
            $start_date = $field['value'][0];
            $end_date = $field['value'][1];
          } else {
            $start_date = $field['value'];
            $end_date = '';
          }
          $timezone = $field['timezone'];

          // Set url
          $url = '';

          // Set $ics_url, $google_url, $yahoo_url
          $base_url = $entity_type . '/' . $entity_id . '/' . $field_type . '/token';
          $ics_url = $base_url . '/addtocal.ics';
          $google_url = $base_url . '/addtocal-google';
          $yahoo_url = $base_url . '/addtocal-yahoo';

          // Sew it up
          $render = addtocal_render(
            $entity_type,
            $entity_id,
            $start_date,
            $end_date,
            $timezone,
            $url,
            $ics_url,
            $google_url,
            $yahoo_url,
            true            // format for email
          );
          $html = drupal_render($render);
          $replacements[$original] = $html;
        }
      }
    }
  }

  return $replacements;
}
