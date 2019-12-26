<?php

/**
 * @file
 * Autocomplete callback for "entityreference" Form API Elements.
 */

/**
 * Page callback for the "entityreference" elements autocomplete path.
 *
 * @param string $entity_type
 *   The type of entity.
 * @param string $bundles
 *   List of bundles.
 * @param string $encoded_query_settings
 *   Query settings string.
 * @param string $string
 *   Search query.
 */
function entityreference_autocomplete_autocomplete_callback($entity_type, $bundles, $encoded_query_settings, $string = '') {
  // If search string contains a slash "/", menu system will think it's a new
  // argument. In such case, reassemble the whole search string.
  $args = func_get_args();

  if (count($args) > 4) {
    array_shift($args);
    array_shift($args);
    array_shift($args);
    $string = implode('/', $args);
  }

  $matches = array();
  // $context will hold the metadata of entities found, so that modules
  // can alter the results in any way they want.
  $context = array();

  // Decode the query settings passed and then parse the result string to get
  // the actual settings array.
  parse_str(decode_entities(urldecode($encoded_query_settings)), $query_settings);

  // The user enters a comma-separated list of entity labels. Autocomplete only
  // the last label.
  $labels_typed = entityreference_autocomplete_explode_tags($string);
  $last_label = drupal_strtolower(array_pop($labels_typed));

  // Prefix string to add to every result.
  $prefix = '';
  if (!empty($last_label)) {
    $prefix = count($labels_typed) ? implode(', ', $labels_typed) . ', ' : '';
  }

  if (isset($last_label)) {
    // Get entity metadata, to be used for some checks.
    $entity_info = entity_get_info($entity_type);

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type);

    // If $bundless is not null, add the 'bundle' condition. Also, save some
    // pain to anyone trying to specify a bundle when the entity has no actual
    // key for bundles.
    if ($bundles && !empty($entity_info['entity keys']['bundle'])) {
      $query->entityCondition('bundle', $bundles);
    }

    // Fetch the column to use as label.
    $label_column = entityreference_autocomplete_resolve_entity_label_column($entity_type);
    $query->propertyCondition($label_column, $last_label, 'CONTAINS');

    // Set property conditions, if any.
    if (!empty($query_settings['property_conditions']) && is_array($query_settings['property_conditions'])) {
      foreach ($query_settings['property_conditions'] as $property_condition) {
        $query->propertyCondition($property_condition[0], $property_condition[1], $property_condition[2]);
      }
    }

    // Add the field conditions declared.
    if (!empty($query_settings['field_conditions']) && is_array($query_settings['field_conditions'])) {
      foreach ($query_settings['field_conditions'] as $field_condition) {
        $column = isset($field_condition[1]) ? $field_condition[1] : NULL;
        $value = isset($field_condition[2]) ? $field_condition[2] : NULL;
        $operator = isset($field_condition[3]) ? $field_condition[3] : NULL;
        $delta_group = isset($field_condition[4]) ? $field_condition[4] : NULL;
        $language_group = isset($field_condition[5]) ? $field_condition[5] : NULL;
        $query->fieldCondition($field_condition[0], $column, $value, $operator, $delta_group, $language_group);
      }
    }

    // Set the maximum number of results returned.
    if (!empty($query_settings['limit']) && is_numeric($query_settings['limit'])) {
      $query->range(0, $query_settings['limit']);
    }

    // Add a tag to the query so modules can alter it.
    $query->addTag('era_query');
    $query->addMetaData('era_search_string', $last_label);

    // Execute query and log any unexpected errors.
    try {
      $result = $query->execute();
    }
    catch (Exception $e) {
      watchdog_exception('entityreference_autocomplete', $e);
    }

    if (!empty($result[$entity_type])) {
      $entities = entity_load($entity_type, array_keys($result[$entity_type]));

      // Iterate through all entities retrieved and process the data to return
      // it as expected by Drupal javascript.
      foreach ($entities as $entity_id => $entity) {
        if (entity_access('view', $entity_type, $entity)) {
          // Get the labels for the key and for the option.
          $option = entityreference_autocomplete_label_for_reference($entity_type, $entity_id, FALSE);
          $key = entityreference_autocomplete_label_for_reference($entity_type, $entity_id);

          // $prefix . $key is the value that will be set in the textfield in
          // the browser, whereas $option is the html that is shown to the user
          // *before* he clicks in one of the options.
          $matches[$prefix . $key] = check_plain($option);

          // Store metadata about the entity returned in a variable.
          list(, , $bundle) = entity_extract_ids($entity_type, $entity);
          $context[$prefix . $key] = array(
            'entity' => $entity,
            'entity_id' => $entity_id,
            'entity_type' => $entity_type,
            'entity_bundle' => $bundle,
            'rendered_html' => check_plain($option),
          );
        }
      }
    }
  }

  // Let other drupal modules alter the results.
  drupal_alter('entityreference_autocomplete_matches', $matches, $context);
  // Finally, output matches in json, as they're are expected by Drupal's ajax.
  drupal_json_output($matches);
}
