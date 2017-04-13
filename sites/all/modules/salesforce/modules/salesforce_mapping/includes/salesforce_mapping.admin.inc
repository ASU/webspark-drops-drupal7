<?php

/**
 * @file
 * Configuration page for creating and modifying a mapping.
 */

/**
 * Return a form for a Salesforce mapping entity.
 */
function salesforce_mapping_form($form, &$form_state, SalesforceMapping $mapping = NULL, $op = 'edit') {
  if ($op == 'clone') {
    $mapping->label .= ' (cloned)';
    $mapping->name = '';
  }
  $form['#id'] = 'salesforce_mapping_form';
  if (!isset($form_state['salesforce_mapping'])) {
    $form_state['salesforce_mapping'] = $mapping;
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => _salesforce_mapping_get_default_value('label', $form_state),
    '#description' => t('The human-readable name of this field mapping.'),
    '#required' => TRUE,
    '#maxlength' => SALESFORCE_MAPPING_NAME_LENGTH,
    '#size' => 30,
  );

  $mapping_name = _salesforce_mapping_get_default_value('name', $form_state);
  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'machine_name',
    '#description' => t(''),
    '#default_value' => $mapping_name,
    '#disabled' => isset($mapping->name) && !empty($mapping->name),
    '#machine_name' => array(
      'exists' => 'salesforce_mapping_load',
      'source' => array('label'),
    ),
  );

  $form['drupal_entity'] = array(
    '#title' => t('Drupal entity'),
    '#type' => 'fieldset',
    '#attributes' => array(
      'id' => array('edit-drupal-entity'),
    ),
  );

  $drupal_entity_type = _salesforce_mapping_get_default_value('drupal_entity_type', $form_state);
  $form['drupal_entity']['drupal_entity_type'] = array(
    '#title' => t('Drupal Entity Type'),
    '#id' => 'edit-drupal-entity-type',
    '#type' => 'select',
    '#description' => t('Select a Drupal entity type to map to a Salesforce object.'),
    '#options' => _salesforce_mapping_get_drupal_entities($form_state),
    '#default_value' => $drupal_entity_type,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => 'salesforce_mapping_form_callback',
      'wrapper' => 'edit-drupal-entity',
    ),
  );

  $drupal_bundle = _salesforce_mapping_get_default_value('drupal_bundle', $form_state);
  $form['drupal_entity']['drupal_bundle'] = array(
    '#title' => t('Drupal Entity Bundle'),
    '#id' => 'edit-drupal-bundle',
    '#type' => 'select',
    '#required' => TRUE,
    '#description' => t('Select a Drupal entity bundle to map to a Salesforce object.'),
    '#ajax' => array(
      'callback' => 'salesforce_mapping_form_callback',
      'wrapper' => 'edit-drupal-entity',
    ),
  );
  if ($drupal_entity_type) {
    $form['drupal_entity']['drupal_bundle'] += array(
      '#default_value' => $drupal_bundle,
      '#options' => _salesforce_mapping_get_entity_bundle_options($drupal_entity_type),
    );
  }
  else {
    $form['drupal_entity']['drupal_bundle'] += array(
      '#disabled' => TRUE,
      '#default_value' => '',
      '#options' => array(
        '' => t('Select drupal entity type'),
      ),
    );
  }

  $form['salesforce_object'] = array(
    '#title' => t('Salesforce object'),
    '#id' => 'edit-salesforce-object',
    '#type' => 'fieldset',
  );

  $salesforce_object_type = _salesforce_mapping_get_default_value('salesforce_object_type', $form_state);
  $form['salesforce_object']['salesforce_object_type'] = array(
    '#title' => t('Salesforce object'),
    '#id' => 'edit-salesforce-object-type',
    '#type' => 'select',
    '#description' => t('Select a Salesforce object to map.'),
    '#default_value' => $salesforce_object_type,
    '#options' => _salesforce_mapping_get_salesforce_object_type_options($form_state),
    '#ajax' => array(
      'callback' => 'salesforce_mapping_form_callback',
      'wrapper' => 'edit-salesforce-object',
    ),
    '#required' => TRUE,
  );

  $form['salesforce_object']['salesforce_record_type'] = array(
    '#title' => t('Salesforce record type'),
    '#id' => 'edit-salesforce-record-type',
  );
  if (!empty($salesforce_object_type)) {
    // Check for custom record types.
    $salesforce_record_type_default = _salesforce_mapping_get_default_value('salesforce_record_type_default', $form_state);
    $salesforce_record_types_allowed_default = _salesforce_mapping_get_default_value('salesforce_record_types_allowed', $form_state);
    $salesforce_record_type_options = _salesforce_mapping_get_salesforce_record_type_options($salesforce_object_type, $form_state);
    $record_type_count = count($salesforce_record_type_options) - 1;
    if ($record_type_count > 1) {
      // There are multiple record types for this object type, so the user must
      // choose a default and list of allowed types.
      $form['salesforce_object']['salesforce_record_types_allowed'] = array(
        '#title' => t('Allowed Record Types'),
        '#description' => t('Reducing the allowed Record Types can provide significant performance improvements when pulling data from Salesforce.'),
        '#type' => 'checkboxes',
        '#options' => $salesforce_record_type_options,
        '#default_value' => $salesforce_record_types_allowed_default,
      );
      unset($form['salesforce_object']['salesforce_record_types_allowed']['#options']['']);
      $form['salesforce_object']['salesforce_record_type_default'] = array(
        '#title' => t('Default record type'),
        '#type' => 'select',
        '#description' => t('If you do not specify a record type in the mappings, new records will be created using this record type.'),
        '#default_value' => $salesforce_record_type_default,
        '#options' => $salesforce_record_type_options,
        '#required' => TRUE,
      );
    }
    else {
      // There is only one record type for this object type.  Don't bother the
      // user and just set the single record type by default.
      $form['salesforce_object']['salesforce_record_type_default'] = array(
        '#type' => 'hidden',
        '#value' => $salesforce_record_type_default,
      );
      $form['salesforce_object']['salesforce_record_types_allowed'] = array(
        '#type' => 'hidden',
        '#value' => array($salesforce_record_type_default => $salesforce_record_type_default),
      );
    }
    $sf_date_fields = _salesforce_mapping_get_salesforce_field_options($salesforce_object_type, $form_state, FALSE, 'datetime');
    $date_default = _salesforce_mapping_get_default_value('pull_trigger_date', $form_state);
    if (!$date_default) {
      $date_default = 'LastModifiedDate';
    }
    $form['salesforce_object']['pull_trigger_date'] = array(
      '#title' => t('Date field to trigger pull'),
      '#id' => 'edit-trigger-date',
      '#type' => 'select',
      '#description' => t('Select a date field to base pull triggers on. (Default of "Last Modified Date" is usually appropriate).'),
      '#required' => TRUE,
      '#default_value' => $date_default,
      '#options' => $sf_date_fields,
    );
  }

  $form['salesforce_field_mappings_wrapper'] = array(
    '#title' => t('Field map'),
    '#type' => 'fieldset',
    '#id' => 'edit-salesforce-field-mappings-wrapper',
    '#description' => '* Key refers to an property mapped to a Salesforce external ID. if specified an UPSERT will be used to avoid duplicate data when possible.',
  );

  // Check to see if we have enough information to allow mapping fields.  If
  // not, tell the user what is needed in order to have the field map show up.
  $fields_required_to_map = _salesforce_mapping_get_required_mapping_fields($form, $form_state);
  if (!empty($fields_required_to_map)) {
    $message = t('Select a value for !fields in order to map fields.',
      array('!fields' => implode(' ' . t('and') . ' ', $fields_required_to_map)));
    $form['salesforce_field_mappings_wrapper']['helptext'] = array(
      '#markup' => '<p>' . $message . '</p>',
    );
  }

  // Field mapping form.
  else {
    $form['salesforce_field_mappings_wrapper']['salesforce_field_mappings'] = array(
      '#theme' => 'salesforce_fieldmap_form_table',
      '#tree' => TRUE,
      '#header' => array(
        'drupal_field' => t('Drupal field'),
        'salesforce_field' => t('Salesforce field'),
        'key' => t('Key') . '*',
        'direction' => t('Direction'),
        'delete_field_mapping' => t('Delete'),
      ),
      '#attributes' => array(
        'id' => array('edit-salesforce-field-mappings'),
      ),
    );

    $drupal_type_options = _salesforce_mapping_get_drupal_type_options();
    $sf_fields = _salesforce_mapping_get_salesforce_field_options($salesforce_object_type, $form_state);
    $has_token_type = FALSE;
    $field_mappings = _salesforce_mapping_get_default_value('field_mappings', $form_state);
    foreach ($field_mappings as $delta => $value) {
      $row_id = 'edit-salesforce-field-mappings-' . $delta;
      $form['salesforce_field_mappings_wrapper']['salesforce_field_mappings'][$delta] = array(
        '#type' => 'container',
        '#attributes' => array(
          'id' => array($row_id),
        ),
      );
      $row = &$form['salesforce_field_mappings_wrapper']['salesforce_field_mappings'][$delta];

      $row['drupal_field'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'id' => array('edit-drupal-field-' . $delta),
        ),
      );

      $fieldmap_type_name = _salesforce_mapping_get_default_value('fieldmap_type', $form_state, $delta);
      $fieldmap_type = salesforce_mapping_get_fieldmap_types($fieldmap_type_name);
      $has_token_type = ($fieldmap_type_name == 'token') ? TRUE : $has_token_type;
      $row['drupal_field']['fieldmap_type'] = array(
        '#id' => 'edit-fieldmap-type-' . $delta,
        '#type' => 'select',
        '#options' => $drupal_type_options,
        '#default_value' => $fieldmap_type_name,
        '#ajax' => array(
          'wrapper' => $row_id,
          'callback' => 'salesforce_mapping_form_field_callback',
        ),
      );

      if ($fieldmap_type_name) {
        $row['drupal_field']['fieldmap_value'] = array(
          '#id' => 'edit-fieldmap-value-' . $delta,
          '#type' => $fieldmap_type['field_type'],
          '#description' => check_plain($fieldmap_type['description']),
          '#size' => !empty($fieldmap_type['description']) ? $fieldmap_type['description'] : 30,
          '#default_value' => _salesforce_mapping_get_default_value('fieldmap_value', $form_state, $delta),
        );
        if (!empty($fieldmap_type['options_callback'])) {
          $row['drupal_field']['fieldmap_value']['#options'] = call_user_func($fieldmap_type['options_callback'], $drupal_entity_type, $drupal_bundle);
          $row['drupal_field']['fieldmap_value']['#options'][''] = '- ' . t('Select @field_type', array('@field_type' => $fieldmap_type_name)) . ' -';
        }
      }

      $row['salesforce_field'] = array(
        '#id' => 'edit-salesforce-field-' . $delta,
        '#type' => 'select',
        '#description' => t('Select a Salesforce field to map.'),
        '#multiple' => (isset($fieldmap_type['salesforce_multiple_fields']) && $fieldmap_type['salesforce_multiple_fields']) ? TRUE : FALSE,
        '#options' => $sf_fields,
        '#default_value' => _salesforce_mapping_get_default_value('salesforce_field', $form_state, $delta),
      );

      $row['key'] = array(
        '#id' => 'edit-key-' . $delta,
        '#type' => 'radio',
        '#name' => 'key',
        '#return_value' => $delta,
        '#tree' => FALSE,
        '#default_value' => _salesforce_mapping_get_default_value('key', $form_state, $delta),
      );

      $row['direction'] = array(
        '#id' => 'edit-direction-' . $delta,
        '#type' => 'radios',
        '#options' => _salesforce_mapping_get_direction_options(),
        '#required' => TRUE,
        '#default_value' => _salesforce_mapping_get_default_value('direction', $form_state, $delta),
      );

      $row['delete_field_mapping'] = array(
        '#id' => 'edit-delete-field-mapping-' . $delta,
        '#type' => 'checkbox',
        '#name' => 'delete_field_mapping-' . $delta,
        '#ajax' => array(
          'callback' => 'salesforce_mapping_form_callback',
          'wrapper' => 'edit-salesforce-field-mappings-wrapper',
          'delta' => $delta,
        ),
      );
    }

    $form['salesforce_field_mappings_wrapper']['ajax_warning'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => array('edit-ajax_warning'),
      ),
    );

    $form['salesforce_field_mappings_wrapper']['token_tree'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => array('edit-token-tree'),
      ),
    );

    if ($has_token_type) {
      $info = token_get_info();
      // Entity type machine names have underscores, not dashes.
      // The token key can be either, so $token_type is set based on a match in
      // $info['types'].
      if(isset($info['types'][$drupal_entity_type])) {
        $token_type = $drupal_entity_type;
      }
      else {
        $token_type = str_replace("_", "-", $drupal_entity_type);
      }

      if(isset($info['types'][$token_type])) {
        $form['salesforce_field_mappings_wrapper']['token_tree']['tree'] = array(
          '#theme' => 'token_tree',
          '#token_types' => array($token_type),
          '#global_types' => TRUE,
          '#dialog' => TRUE,
        );
      }
    }

    $form['salesforce_field_mappings_wrapper']['salesforce_add_field'] = array(
      '#value' => t('Add another field mapping'),
      '#id' => 'edit-salesforce-add-field',
      '#name' => 'salesforce_add_field',
      '#type' => 'button',
      '#description' => t('Add one or more fields to configure a mapping for.'),
      '#executes_submit_callback' => FALSE,
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'salesforce_mapping_form_callback',
        'wrapper' => 'edit-salesforce-field-mappings-wrapper',
      ),
    );
  }

  $trigger_options = _salesforce_mapping_get_sync_trigger_options();
  $trigger_defaults = _salesforce_mapping_get_default_value('sync_triggers', $form_state);
  $form['sync_triggers'] = array(
    '#title' => t('Action triggers'),
    '#type' => 'checkboxes',
    '#description' => t('Select which actions on Drupal entities and Salesforce objects should trigger a synchronization. These settings are used by the salesforce_push and salesforce_pull modules respectively.'),
    '#default_value' => $trigger_defaults,
    '#options' => $trigger_options,
  );

  $form['push_async'] = array(
    '#title' => t('Process asynchronously'),
    '#type' => 'checkbox',
    '#description' => t('If selected, push data will be queued for processing and synchronized when cron is run. This may increase site performance, but changes will not be reflected in real time.'),
    '#default_value' => _salesforce_mapping_get_default_value('push_async', $form_state),
  );
  $form['push_batch'] = array(
    '#title' => t('Batch records'),
    '#type' => 'checkbox',
    '#default_value' => _salesforce_mapping_get_default_value('push_batch', $form_state),
  );
  if (module_exists('salesforce_soap')) {
    $requirements_description = t('Requires "Process asynchronously" option to be enabled.');
    $form['push_batch']['#states'] = array(
      'enabled' => array(
        ':input[name="push_async"]' => array('checked' => TRUE),
      ),
    );
  }
  else {
    $requirements_description = t('Requires the "Salesforce SOAP (salesforce_soap)" module to be enabled, and the "Process asynchronously" option to be checked.');
    $form['push_batch']['#disabled'] = TRUE;
  }
  $push_batch_description = t('Push items will be processed in a single batch to the Salesforce API rather than one at a time. This may be preferable if API limits are of concern, although changes are not reflected immediately in Salesforce.');
  $form['push_batch']['#description'] = $requirements_description . ' ' . $push_batch_description;

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#value' => t('Save mapping'),
    '#type' => 'submit',
  );

  return $form;
}

/**
 * Ajax callback for salesforce_mapping_form().
 */
function salesforce_mapping_form_callback($form, $form_state) {
  $trigger = $form_state['triggering_element']['#name'];
  $parents = $form_state['triggering_element']['#array_parents'];
  $delta = isset($parents[2]) ? $parents[2] : NULL;
  $commands = array();
  switch ($trigger) {
    case 'drupal_entity_type':
    case 'drupal_bundle':
      // Requires updating itself and the field map.
      $commands = array(
        ajax_command_replace('#edit-drupal-entity', render($form['drupal_entity'])),
        ajax_command_replace('#edit-salesforce-field-mappings-wrapper', render($form['salesforce_field_mappings_wrapper'])),
      );
      break;

    case 'salesforce_object_type':
      // Requires updating itself and the field map.
      $commands = array(
        ajax_command_replace('#edit-salesforce-object', render($form['salesforce_object'])),
        ajax_command_replace('#edit-salesforce-field-mappings-wrapper', render($form['salesforce_field_mappings_wrapper'])),
      );
      break;

    case 'salesforce_add_field':
    case 'delete_field_mapping-' . $delta:
      // Replace the field map table.
      $commands = array(
        ajax_command_replace('#edit-salesforce-field-mappings-wrapper', render($form['salesforce_field_mappings_wrapper'])),
      );
      break;
  }
  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Ajax callback for deleting a field mapping row.
 */
function salesforce_mapping_form_field_callback($form, $form_state) {
  $errors = array('#theme' => 'status_messages');
  $ajax_warn = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('messages', 'warning'),
    ),
    'message' => array(
      '#type' => 'markup',
      '#markup' => 'Changes made in this list will not be saved until the form is submitted.',
    ),
  );

  // Retreive the row's form information.
  $wrapper = $form_state['triggering_element']['#ajax']['wrapper'];
  $parents = $form_state['triggering_element']['#array_parents'];
  $delta = $parents[2];
  $row = $form[$parents[0]][$parents[1]][$delta];

  // Render the row.  This requires rendering it as a table, then stripping away
  // unwanted tags in order to leave only the HTML of a table row.  Finally,
  // all line breaks had to be removed in order to prevent the ajax replace from
  // wrapping the output in a div.
  $table_row = array(
    '#theme' => 'salesforce_mapping_form_table_row',
    '#tree' => TRUE,
    '#columns' => array_keys($form['salesforce_field_mappings_wrapper']['salesforce_field_mappings']['#header']),
    '#row' => $row,
  );
  $rendered_table = render($table_row);
  $rendered_row = str_replace(array("\r", "\n"), "", $rendered_table);

  $commands = array(
    // Replace the row.
    ajax_command_replace('#' . $wrapper, $rendered_row),
    ajax_command_replace("#edit-token-tree", render($form['salesforce_field_mappings_wrapper']['token_tree'])),
    ajax_command_replace("#edit-ajax-warning", render($ajax_warn)),

    // Set messages if found.
    ajax_command_remove('.messages'),
    ajax_command_after('#page-title', render($errors)),
  );
  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Theme a single row for our ajax callback to inject into an existing table.
 * @see salesforce_mapping_form_field_callback()
 * @see theme_table()
 */
function theme_salesforce_mapping_form_table_row($variables) {
  watchdog('row', "<pre>" . var_export($variables, 1));
  $elements = $variables['elements'];

  // Build the rows array.
  $columns = !empty($elements['#columns']) ? $elements['#columns'] : array();
  $row = !empty($elements['#row']) ? $elements['#row'] : array();
  $attributes = !empty($row['#attributes']) ? $row['#attributes'] : array();

  $output = '<tr' . drupal_attributes($attributes) . '>';

  $data = array();
  foreach ($columns as $column) {
    if (isset($row[$column])) {
      $cell = array(
        'data' => drupal_render($row[$column]),
      );
      if (isset($row[$column]['#attributes'])) {
        foreach ($row[$column]['#attributes'] as $key => $value) {
          $cell[$key] = ($key == 'id') ? (is_array($value) ? array($value[0] . '-cell') : $value . '-cell') : $value;
        }
      }
      $output .= _theme_table_cell($cell);
    }
  }
  $output .= "</tr>";
  return $output;  
}

/**
 * Themes the field associations on a fieldmap edit form into a table.
 */
function theme_salesforce_fieldmap_form_table($variables) {
  $elements = $variables['elements'];

  // Build the rows array.
  $columns = isset($elements['#columns']) ? $elements['#columns'] : (isset($elements['#header']) ? array_keys($elements['#header']) : array());
  $rows = array();
  foreach (element_children($elements) as $child_key) {
    $child = & $elements[$child_key];
    $data = array();
    $row_columns = empty($columns) ? element_children($child) : $columns;
    foreach ($row_columns as $column) {
      if (isset($child[$column])) {
        $cell = array('data' => drupal_render($child[$column]));
        if (isset($child[$column]['#attributes'])) {
          foreach ($child[$column]['#attributes'] as $key => $value) {
            $cell[$key] = ($key == 'id') ? (is_array($value) ? array($value[0] . '-cell') : $value . '-cell') : $value;
          }
        }
        $data[] = $cell;
      }
    }
    $row = array('data' => $data);
    if (isset($child['#attributes'])) {
      foreach ($child['#attributes'] as $key => $value) {
        $row[$key] = $value;
      }
    }
    $rows[] = $row;
  }

  $config = array(
    'rows' => $rows,
  );
  if (isset($elements['#header'])) {
    $config['header'] = $elements['#header'];
  }
  if (isset($elements['#attributes']) && is_array($elements['#attributes'])) {
    $config['attributes'] = $elements['#attributes'];
  }

  return theme('table', $config);
}

/**
 * Validate callback for salesforce_mapping_form().
 */
function salesforce_mapping_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  $mapping = $form_state['salesforce_mapping'];

  // Validate label and name length.
  if (strlen($values['label']) > SALESFORCE_MAPPING_NAME_LENGTH) {
    form_set_error('label', t('Label must not exceed @max characters.', array('@max' => SALESFORCE_MAPPING_NAME_LENGTH)));
  }
  if (strlen($values['name']) > SALESFORCE_MAPPING_NAME_LENGTH) {
    form_set_error('name', t('Name must not exceed @max characters.', array('@max' => SALESFORCE_MAPPING_NAME_LENGTH)));
  }
  if (isset($values['salesforce_record_type_default']) && !in_array($values['salesforce_record_type_default'], $values['salesforce_record_types_allowed'])) {
    form_set_error('salesforce_record_type_default', t('Default record type must be one of the Allowed Record Types.'));
  }

  $properties = array(
    'salesforce_object_type' => $values['salesforce_object_type'],
    'drupal_entity_type' => $values['drupal_entity_type'],
    'drupal_bundle' => $values['drupal_bundle'],
  );

  $existing_mappings = salesforce_mapping_load_multiple($properties);
  foreach ($existing_mappings as $existing_mapping) {
    // Existing mapping, ensure not using any other unique combo. Less
    // efficient than adding a condition to the query, but works easily
    // with salesforce_mapping_load_multiple().
    if (isset($mapping->name) && $mapping->name == $existing_mapping->name) {
      continue;
    }
    foreach ($values['sync_triggers'] as $trigger => $trigger_enabled) {
      if ($trigger_enabled && $existing_mapping->sync_triggers & $trigger) {
        form_set_error('sync_triggers[' . $trigger . ']', t('This Drupal bundle has already been mapped to a Salesforce object using this trigger.'));
      }
    }
  }

  // If Salesforce Object Create is selected, ensure that at least one mapping
  // is set to sync or SF to Drupal to prevent "empty" entities.
  if ($values['sync_triggers'][SALESFORCE_MAPPING_SYNC_SF_CREATE] && isset($values['salesforce_field_mappings'])) {
    $valid_salesforce_create = FALSE;
    foreach ($values['salesforce_field_mappings'] as $mapping) {
      if ($mapping['direction'] == SALESFORCE_MAPPING_DIRECTION_SYNC || $mapping['direction'] == SALESFORCE_MAPPING_DIRECTION_SF_DRUPAL) {
        $valid_salesforce_create = TRUE;
        break;
      }
    }
    if (!$valid_salesforce_create) {
      form_set_error('mapping issue', t('One mapping must be set to "Sync" or "SF to Drupal" when "Salesforce object create" is selected'));
    }
  }

  if (isset($values['salesforce_field_mappings'])) {
    // Validate field mappings.
    $info = entity_get_info($values['drupal_entity_type']);
    $properties = entity_get_all_property_info($values['drupal_entity_type']);
    $sfobject = _salesforce_mapping_get_salesforce_object($values['salesforce_object_type'], $form_state);
    $sf_fields = isset($sfobject['fields']) ? $sfobject['fields'] : array();
    $key_delta = isset($values['key']) ? $values['key'] : FALSE;

    foreach ($values['salesforce_field_mappings'] as $key => $mapping) {
      $drupal_field_type = $mapping['drupal_field']['fieldmap_type'];
      $field_map = salesforce_mapping_get_fieldmap_types($drupal_field_type);
      if (!empty($mapping['drupal_field']) && !empty($mapping['salesforce_field']) && isset($field_map['validation_callback'])) {
        if (isset($field_map['salesforce_multiple_fields']) && $field_map['salesforce_multiple_fields']) {
          $sf_field = array();
          foreach ($mapping['salesforce_field'] as $field) {
            $sf_field[] = reset(array_values(array_filter($sf_fields, salesforce_field_filter($field))));
          }
        }
        else {
          $filtered = array_filter($sf_fields, salesforce_field_filter($mapping['salesforce_field']));
          $sf_field = reset($filtered);
        }

        $field_array = explode(':', $mapping['drupal_field']['fieldmap_value']);
        $drupal_field = count($field_array) === 1 ? $properties[$field_array[0]] : $properties[$field_array[0]]['property info'][$field_array[1]];
        if (isset($field_map['salesforce_multiple_fields']) && $field_map['salesforce_multiple_fields']) {
          foreach ($sf_field as $field) {
            call_user_func($field_map['validation_callback'], $drupal_field, $field, $mapping['direction'], $key);
          }
        }
        else {
          call_user_func($field_map['validation_callback'], $drupal_field, $sf_field, $mapping['direction'], $key);
        }
        // Ensure valid SF external ID field.
        if ($key_delta !== FALSE && $key === (int) $key_delta && !$sf_field['externalId']) {
          form_set_error('salesforce_field_mappings][' . $key . '][salesforce_field', t('Salesforce field %name is not configured as an external id.',
            array(
              '%name' => $mapping['salesforce_field'],
            )
          ));
        }
      }
    }
  }
}

/**
 * Closure used sf_field filter.
 */
function salesforce_field_filter($sf_mapping_field) {
  return function ($sf_field) use ($sf_mapping_field) {
    $pass = FALSE;
    if (isset($sf_field['name']) && $sf_mapping_field == $sf_field['name']) {
      $pass = TRUE;
    }
    return $pass;
  };
}

/**
 * Submit handler for salesforce_mapping_form().
 */
function salesforce_mapping_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $mappings = array();
  if (isset($values['key'])) {
    $key_delta = isset($values['key']) ? $values['key'] : FALSE;
    $sfobject = _salesforce_mapping_get_salesforce_object($values['salesforce_object_type'], $form_state);
    $sf_fields = isset($sfobject['fields']) ? $sfobject['fields'] : array();
    foreach ($values['salesforce_field_mappings'] as $key => $mapping) {
      $drupal_field_type = $mapping['drupal_field']['fieldmap_type'];
      $field_map = salesforce_mapping_get_fieldmap_types($drupal_field_type);
      if (!empty($mapping['drupal_field']) && !empty($mapping['salesforce_field'])) {
        if (isset($field_map['salesforce_multiple_fields']) && $field_map['salesforce_multiple_fields']) {
          $sf_field = array();
          foreach ($mapping['salesforce_field'] as $field) {
            $filtered = array_filter($sf_fields, salesforce_field_filter($field));
            $sf_field[] = reset($filtered);
          }
        }
        else {
          $filtered = array_filter($sf_fields, salesforce_field_filter($mapping['salesforce_field']));
          $sf_field = reset($filtered);
        }
        $mappings[] = array(
          'drupal_field' => $mapping['drupal_field'],
          'salesforce_field' => $sf_field,
          'key' => $key_delta !== FALSE && $key_delta != ""
          && ($key === (int) $key_delta),
          'direction' => $mapping['direction'],
        );
      }
    }
  }

  $sync_values = array_filter($values['sync_triggers']);
  $sync_triggers = SALESFORCE_MAPPING_SYNC_OFF;
  foreach ($sync_values as $value) {
    $sync_triggers = $sync_triggers | $value;
  }

  $params = array(
    'label' => $values['label'],
    'salesforce_object_type' => $values['salesforce_object_type'],
    'salesforce_record_types_allowed' => $values['salesforce_record_types_allowed'],
    'salesforce_record_type_default' => $values['salesforce_record_type_default'],
    'drupal_entity_type' => $values['drupal_entity_type'],
    'drupal_bundle' => $values['drupal_bundle'],
    'description' => '',
    'field_mappings' => $mappings,
    'sync_triggers' => $sync_triggers,
    'pull_trigger_date' => $values['pull_trigger_date'],
    'push_async' => $values['push_async'],
    'push_batch' => $values['push_batch'],
  );

  if ($form_state['salesforce_mapping']->name) {
    $mapping = $form_state['salesforce_mapping'];
    foreach ($params as $key => $value) {
      $mapping->{$key} = $value;
    }
  }
  else {
    $params['name'] = $values['name'];
    $mapping = entity_create('salesforce_mapping', $params);
  }

  $mapping->save();

  salesforce_set_message(t('Salesforce field mapping saved.'));
  $form_state['redirect'] = 'admin/structure/salesforce/mappings';
}

/**
 * Helper to retrieve the current value for a given form field.
 *
 * @param string $field
 *   Name of the field who's value to retreive.
 * @param array $form_state
 *   Current state of the form to compare with.
 * @param mixed $delta
 *   Optionally provide the delta of the specific field map to check.
 *
 * @return mixed
 *   Value of the field that is appropriate for #default_value.
 */
function _salesforce_mapping_get_default_value($field, &$form_state, $delta = NULL) {
  $mapping = NULL;
  if (isset($form_state['salesforce_mapping'])) {
    $mapping = &$form_state['salesforce_mapping'];
  }

  $value = NULL;
  if ($field == 'field_mappings') {
    if (!isset($mapping->field_mappings) || !is_array($mapping->field_mappings)) {
      $mapping->field_mappings = array(_salesforce_mapping_get_empty_field_map_row());
    }
    if (isset($form_state['triggering_element'])) {
      if ($form_state['triggering_element']['#name'] == 'salesforce_add_field') {
        $mapping->field_mappings[] = _salesforce_mapping_get_empty_field_map_row();
      }
      if (isset($form_state['triggering_element']['#ajax']['delta']) && $form_state['triggering_element']['#name'] == 'delete_field_mapping-' . $form_state['triggering_element']['#ajax']['delta']) {
        $delta = $form_state['triggering_element']['#ajax']['delta'];
        unset($mapping->field_mappings[$delta]);
      }
    }
    $value = &$mapping->field_mappings;
  }
  elseif (is_null($delta)) {
    if (isset($form_state['input'][$field])) {
      $value = &$form_state['input'][$field];
    }
    elseif (!empty($mapping)) {
      $value = &$mapping->$field;
    }

    // Special case for drupal bundle.
    if ($field == 'drupal_bundle') {
      $drupal_entity = _salesforce_mapping_get_default_value('drupal_entity_type', $form_state);
      $entity_bundle_options = array_keys(_salesforce_mapping_get_entity_bundle_options($drupal_entity, FALSE));
      if (empty($drupal_entity) || !in_array($value, $entity_bundle_options)) {
        $value = NULL;
      }
    }

    // Special case for salesforce record type.
    if ($field == 'salesforce_record_type_default') {
      $salesforce_object_type = _salesforce_mapping_get_default_value('salesforce_object_type', $form_state);
      $salesforce_record_type_options = _salesforce_mapping_get_salesforce_record_type_options($salesforce_object_type, $form_state, FALSE);
      $record_type_count = count($salesforce_record_type_options);
      $default = $record_type_count > 1 ? 0 : SALESFORCE_MAPPING_DEFAULT_RECORD_TYPE;
      $value = (!empty($value) && $record_type_count > 1) ? $value : $default;
    }

    // Special case for sync triggers.
    if ($field == 'sync_triggers') {
      if (is_array($value)) {
        $sync_values = array_filter($value);
        $sync_triggers = SALESFORCE_MAPPING_SYNC_OFF;
        foreach ($sync_values as $value) {
          $sync_triggers = $sync_triggers | $value;
        }
        $value = $sync_triggers;
      }
      $breakup = array();
      foreach (_salesforce_mapping_get_sync_trigger_options() as $key => $option) {
        if ($key & $value) {
          $breakup[] = $key;
        }
      }
      $value = $breakup;
    }

    // Special case for push_batch.
    if ($field == 'push_batch' && !module_exists('salesforce_soap')) {
      // Enforce this to be disabled when salesforce_soap is disabled.
      $value = 0;
    }
  }
  else {
    switch ($field) {
      case 'fieldmap_type':
      case 'fieldmap_value':
        if (isset($form_state['input']['salesforce_field_mappings'][$delta]['drupal_field'][$field])) {
          $value = &$form_state['input']['salesforce_field_mappings'][$delta]['drupal_field'][$field];
        }
        elseif (!empty($mapping) && isset($mapping->field_mappings[$delta]['drupal_field'][$field])) {
          $value = &$mapping->field_mappings[$delta]['drupal_field'][$field];
        }
        break;

      case 'salesforce_field':
        $salesforce_object_type = _salesforce_mapping_get_default_value('salesforce_object_type', $form_state);
        if (empty($salesforce_object_type)) {
          $value = NULL;
        }
        else {
          if (isset($form_state['input']['salesforce_field_mappings'][$delta][$field])) {
            $value = &$form_state['input']['salesforce_field_mappings'][$delta][$field];
          }
          elseif (!empty($mapping) && isset($mapping->field_mappings[$delta])) {
            $fieldmap_type_name = _salesforce_mapping_get_default_value('fieldmap_type', $form_state, $delta);
            $fieldmap_type = salesforce_mapping_get_fieldmap_types($fieldmap_type_name);
            if (isset($fieldmap_type['salesforce_multiple_fields']) && $fieldmap_type['salesforce_multiple_fields']) {
              $value = array();
              foreach ($mapping->field_mappings[$delta][$field] as $sf_field) {
                if (is_array($sf_field) && isset($sf_field['name'])) {
                  $value[] = &$sf_field['name'];
                }
                else {
                  $value[] = &$sf_field;
                }
              }
            }
            elseif (isset($mapping->field_mappings[$delta][$field])) {
              $sf_field = &$mapping->field_mappings[$delta][$field];
              if (is_array($sf_field) && isset($sf_field['name'])) {
                $value = &$sf_field['name'];
              }
              else {
                $value = &$sf_field;
              }
            }
            else {
              $value = NULL;
            }
          }
        }
        break;

      case 'key':
        if (isset($form_state['input']['key'])) {
          if ($form_state['input']['key'] == $delta) {
            $value = $delta;
          }
        }
        elseif (isset($mapping->field_mappings[$delta][$field]) && $mapping->field_mappings[$delta][$field] === TRUE) {
          $value = $delta;
        }
        else {
          $value = FALSE;
        }
        break;

      case 'direction':
        // Set default for direction, which cannot be NULL like the others.
        $keys = array_keys(_salesforce_mapping_get_direction_options());
        $value = end($keys);
        // No break for this case, should carry onto the default case.
      default:
        if (isset($form_state['input']['salesforce_field_mappings'][$delta][$field])) {
          $value = &$form_state['input']['salesforce_field_mappings'][$delta][$field];
        }
        elseif (isset($mapping->field_mappings[$delta][$field])) {
          $value = &$mapping->field_mappings[$delta][$field];
        }
        break;
    }
  }

  return $value;
}

/**
 * Return a list of Drupal entities that implement EntityAPIControllerInterface.
 *
 * @param array $form_state
 *   Current state of the form to store and retreive results from to minimize
 *   the need for recalculation.
 * @param bool $include_select
 *   Choice to choose a select option or not.  If TRUE, the first item will be
 *   "-- Select --".  If FALSE, the first item will be the first item of the
 *   retreived bundles.  Defaults to TRUE.
 *
 * @return array
 *   An array of values keyed by machine name of the entity with the label as
 *   the value, formatted to be appropriate as a value for #options.
 */
function _salesforce_mapping_get_drupal_entities(&$form_state, $include_select = TRUE) {
  if (isset($form_state['sfm_storage']['drupal_entity_property_info'])) {
    $property_info = $form_state['sfm_storage']['drupal_entity_property_info'];
  }
  else {
    module_load_include('inc', 'entity', 'entity.info');
    $property_info = entity_get_property_info();
    $entity_info = entity_get_info();
    $property_info = array_merge_recursive($entity_info, $property_info);
    $form_state['sfm_storage']['drupal_entity_property_info'] = $property_info;
  }

  $types = array();
  if ($include_select) {
    $types[''] = '- ' . t('Select Drupal entity') . ' -';
  }
  foreach ($property_info as $type => $properties) {
    // Exclude Salesforce Mapping and Salesforce Object Mapping entities as
    // these will never sync with Salesforce.
    if (in_array($type, array('salesforce_mapping', 'salesforce_mapping_object'))) {
      continue;
    }

    if (!empty($properties['label'])) {
      $types[$type] = $properties['label'];
    }
  }

  return $types;
}

/**
 * Helper to retreive a list of bundle options for a given entity type.
 *
 * @param string $drupal_entity_type
 *   An entity type whose bundles you want to retreive.
 * @param bool $include_select
 *   Choice to choose a select option or not.  If TRUE, the first item will be
 *   "-- Select --".  If FALSE, the first item will be the first item of the
 *   retreived bundles.  Defaults to TRUE.
 *
 * @return array
 *   An array of values keyed by machine name of the bundle with the label as
 *   the value, formatted to be appropriate as a value for #options.
 */
function _salesforce_mapping_get_entity_bundle_options($drupal_entity_type, $include_select = TRUE) {
  $info = entity_get_info($drupal_entity_type);
  $bundles = array();
  if ($include_select) {
    $bundles[''] = '- ' . t('Select entity bundle') . ' -';
  }
  if (isset($info['bundles'])) {
    foreach ($info['bundles'] as $key => $bundle) {
      $bundles[$key] = $bundle['label'];
    }
  }
  return $bundles;
}

/**
 * Helper to retreive a list of object type options.
 *
 * @param array $form_state
 *   Current state of the form to store and retreive results from to minimize
 *   the need for recalculation.
 * @param bool $include_select
 *   Choice to choose a select option or not.  If TRUE, the first item will be
 *   "-- Select --".  If FALSE, the first item will be the first item of the
 *   retreived objects.  Defaults to TRUE.
 *
 * @return array
 *   An array of values keyed by machine name of the object with the label as
 *   the value, formatted to be appropriate as a value for #options.
 */
function _salesforce_mapping_get_salesforce_object_type_options(&$form_state, $include_select = TRUE) {
  if (isset($form_state['sfm_storage']['salesforce_object_type'])) {
    $sfobjects = $form_state['sfm_storage']['salesforce_object_type'];
  }
  else {
    $sfapi = salesforce_get_api();
    // Note that we're filtering SF object types to a reasonable subset.
    $sf_object_filter = array(
      'triggerable' => TRUE,
    );

    //TODO: Handle this somewhere else to validate we can push to this object.
    // if (module_exists('salesforce_push')) {
    //   $sf_object_filter['updateable'] = TRUE;
    // }
    
    $sfobjects = $sfapi->objects($sf_object_filter);
    $form_state['sfm_storage']['salesforce_object_type'] = $sfobjects;
  }

  $sfobject_options = array();
  if ($include_select) {
    $sfobject_options[''] = '- ' . t('Select object type') . ' -';
  }
  foreach ($sfobjects as $object) {
    $sfobject_options[$object['name']] = $object['label'];
  }
  return $sfobject_options;
}

/**
 * Retreive Salesforce's information about an object type.
 *
 * @param string $salesforce_object_type
 *   The object type of whose records you want to retreive.
 * @param array $form_state
 *   Current state of the form to store and retreive results from to minimize
 *   the need for recalculation.
 *
 * @return array
 *   Information about the Salesforce object as provided by Salesforce.
 */
function _salesforce_mapping_get_salesforce_object($salesforce_object_type, &$form_state) {
  if (empty($salesforce_object_type)) {
    return array();
  }
  if (isset($form_state['sfm_storage']['salesforce_object'][$salesforce_object_type])) {
    $sfobject = $form_state['sfm_storage']['salesforce_object'][$salesforce_object_type];
  }
  else {
    $sfapi = salesforce_get_api();
    $sfobject = $sfapi->objectDescribe($salesforce_object_type);
    $form_state['sfm_storage']['salesforce_object'][$salesforce_object_type] = $sfobject;
  }
  return $sfobject;
}

/**
 * Helper to retreive a list of record type options for a given object type.
 *
 * @param string $salesforce_object_type
 *   The object type of whose records you want to retreive.
 * @param array $form_state
 *   Current state of the form to store and retreive results from to minimize
 *   the need for recalculation.
 * @param bool $include_select
 *   Choice to choose a select option or not.  If TRUE, the first item will be
 *   "-- Select --".  If FALSE, the first item will be the first item of the
 *   retreived records.  Defaults to TRUE.
 *
 * @return array
 *   An array of values keyed by machine name of the record with the label as
 *   the value, formatted to be appropriate as a value for #options.
 */
function _salesforce_mapping_get_salesforce_record_type_options($salesforce_object_type, &$form_state, $include_select = TRUE) {
  $sfobject = _salesforce_mapping_get_salesforce_object($salesforce_object_type, $form_state);
  $sf_types = array();
  if (isset($sfobject['recordTypeInfos'])) {
    if ($include_select) {
      $sf_types[''] = '- ' . t('Select record type') . ' -';
    }
    foreach ($sfobject['recordTypeInfos'] as $type) {
      $sf_types[$type['recordTypeId']] = $type['name'];
    }
  }
  return $sf_types;
}

/**
 * Helper to retreive a list of fields for a given object type.
 *
 * @param string $salesforce_object_type
 *   The object type of whose fields you want to retreive.
 * @param array $form_state
 *   Current state of the form to store and retreive results from to minimize
 *   the need for recalculation.
 * @param bool $include_select
 *   Choice to choose a select option or not.  If TRUE, the first item will be
 *   "-- Select --".  If FALSE, the first item will be the first item of the
 *   retreived fields.  Defaults to TRUE.
 *
 * @return array
 *   An array of values keyed by machine name of the field with the label as
 *   the value, formatted to be appropriate as a value for #options.
 */
function _salesforce_mapping_get_salesforce_field_options($salesforce_object_type, &$form_state, $include_select = TRUE, $type = NULL) {
  $sfobject = _salesforce_mapping_get_salesforce_object($salesforce_object_type, $form_state);
  $sf_fields = array();
  if (isset($sfobject['fields'])) {
    if ($include_select) {
      $sf_fields[''] = '- ' . t('Select') . ' -';
    }
    foreach ($sfobject['fields'] as $sf_field) {
      if ($type == NULL || $type == $sf_field['type']) {
        $sf_fields[$sf_field['name']] = $sf_field['label'] . ' - (' . $sf_field['name'] . ')';
      }
    }
  }
  natcasesort($sf_fields);
  return $sf_fields;
}

/**
 * Helper to generate a list of fieldtypes for Drupal fields.
 *
 * @param bool $include_select
 *   Choice to choose a select option or not.  If TRUE, the first item will be
 *   "-- Select --".  If FALSE, the first item will be the first item of the
 *   retreived fields.  Defaults to TRUE.
 *
 * @return array
 *   An array of values keyed by machine name of the fieldmap type with the
 *   label as the value, formatted to be appropriate as a value for #options.
 */
function _salesforce_mapping_get_drupal_type_options($include_select = TRUE) {
  $types = salesforce_mapping_get_fieldmap_types();
  $drupal_type_options = array();
  if ($include_select) {
    $drupal_type_options[''] = '- ' . t('Select Drupal field type') . ' -';
  }
  foreach ($types as $key => $fieldmap_type) {
    $drupal_type_options[$key] = $fieldmap_type['label'];
  }
  return $drupal_type_options;
}

/**
 * Return form options for available sync triggers.
 *
 * @return array
 *   Array of sync trigger options keyed by their machine name with their label
 *   as the value.
 */
function _salesforce_mapping_get_sync_trigger_options() {
  $options = array();
  if (module_exists('salesforce_push')) {
    $options += array(
      SALESFORCE_MAPPING_SYNC_DRUPAL_CREATE => t('Drupal entity create'),
      SALESFORCE_MAPPING_SYNC_DRUPAL_UPDATE => t('Drupal entity update'),
      SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE => t('Drupal entity delete'),
    );
  }
  if (module_exists('salesforce_pull')) {
    $options += array(
      SALESFORCE_MAPPING_SYNC_SF_CREATE => t('Salesforce object create'),
      SALESFORCE_MAPPING_SYNC_SF_UPDATE => t('Salesforce object update'),
      SALESFORCE_MAPPING_SYNC_SF_DELETE => t('Salesforce object delete'),
    );
  }
  return $options;
}

/**
 * Return form options for available direction options.
 *
 * @return array
 *   Array of direction options keyed by their machine name with their label
 *   as the value.
 */
function _salesforce_mapping_get_direction_options() {
  $options = array();
  if (module_exists('salesforce_pull')) {
    $options += array(
      SALESFORCE_MAPPING_DIRECTION_SF_DRUPAL => t('SF to Drupal'),
    );
  }
  if (module_exists('salesforce_push')) {
    $options += array(
      SALESFORCE_MAPPING_DIRECTION_DRUPAL_SF => t('Drupal to SF'),
    );
  }

  if (module_exists('salesforce_pull') && module_exists('salesforce_push')) {
    $options += array(
      SALESFORCE_MAPPING_DIRECTION_SYNC => t('Sync'),
    );
  }

  return $options;
}

/**
 * Helper to discover which fields required for mapping do not have values.
 *
 * @param array $form
 *   FAPI form array.
 * @param array $form_state
 *   Current state of the form.
 *
 * @return array
 *   List of the labels of the fields that are required for mapping fields but
 *   currently do not have any values.
 */
function _salesforce_mapping_get_required_mapping_fields(&$form, &$form_state) {
  // Retreive the label of the fields from the form to keep these in sync and
  // hopefully multilingual compliant.
  $drupal_entity_type_label = &$form['drupal_entity']['drupal_entity_type']['#title'];
  $drupal_bundle_label = &$form['drupal_entity']['drupal_bundle']['#title'];
  $salesforce_object_type_label = &$form['salesforce_object']['salesforce_object_type']['#title'];

  $fields = array(
    $drupal_entity_type_label => _salesforce_mapping_get_default_value('drupal_entity_type', $form_state),
    $drupal_bundle_label => _salesforce_mapping_get_default_value('drupal_bundle', $form_state),
    $salesforce_object_type_label => _salesforce_mapping_get_default_value('salesforce_object_type', $form_state),
  );

  // Weed out fields that have a value to leave us only with those that don't
  foreach ($fields as $label => $value) {
    if (!empty($value)) {
      unset($fields[$label]);
    }
  }

  // Return only the labels.
  return array_keys($fields);
}

/**
 * Helper to rapidly retreive an empty field mapping array.
 *
 * @return array
 *   An empty field mapping array.
 */
function _salesforce_mapping_get_empty_field_map_row() {
  return array(
    'drupal_field' => '',
    'salesforce_field' => '',
    'key' => '',
    'direction' => end(array_keys(_salesforce_mapping_get_direction_options())),
  );
}
