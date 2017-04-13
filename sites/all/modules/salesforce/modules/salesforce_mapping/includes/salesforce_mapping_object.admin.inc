<?php

/**
 * Implements hook_form().
 */
function salesforce_mapping_object_form($form, &$form_state, $mapping_object = NULL, $entity_type = '', $entity_id = '') {
  $form = array();

  $form['entity_type'] = array(
    '#type' => 'value',
    '#value' => $entity_type,
  );

  $form['entity_id'] = array(
    '#type' => 'value',
    '#value' => $entity_id,
  );

  $form['salesforce_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Salesforce Id'),
    '#description' => t('15 character Ids will be treated as case sensitive and will be converted to their 18 character counterpart before saving.'),
    '#default_value' => isset($mapping_object->salesforce_id) ? $mapping_object->salesforce_id : '',
    '#size' => 19,
    '#maxlength' => 18,
    '#required' => TRUE,
  );

  // @TODO options to trigger push or pull?
  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => isset($mapping_object->salesforce_mapping_object_id) ? t('Update mapping') : t('Save mapping'),
      '#submit' => array('salesforce_mapping_object_form_save_mapping_submit'),
      '#validate' => array('salesforce_mapping_object_form_save_mapping_validate')
    ),
  );
  if ($mapping_object && empty($mapping_object->is_new)) {
    $uri = $mapping_object->uri();
    $form['actions']['delete_link'] = array(
      '#markup' => l(t('Delete'), $uri['path'] . '/delete',
        array(
          'attributes' => array(
            'id' => array('mapped_object-delete-' . $mapping_object->salesforce_mapping_object_id),
            'class' => array('button remove'),
          ),
          'query' => array('destination' => 'admin/content/salesforce'),
        )
      ),
      '#access' => isset($mapping_object->salesforce_mapping_object_id),
    );
  }
  $form_state['salesforce_mapping_object'] = $mapping_object;
  return $form;
}

/**
 * Implements hook_form_validate().
 */
function salesforce_mapping_object_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  $mapping_object = $form_state['salesforce_mapping_object'];
  $entity_type = isset($values['entity_type']) ? $values['entity_type'] : $mapping_object->entity_type;
  $entity_id = isset($values['entity_id']) ? $values['entity_id'] : $mapping_object->entity_id;
  $entity = entity_load_single($entity_type, $entity_id);

  if (!$entity) {
    // Invalid entity.
    form_set_error('entity_id', t('Entity is invalid.'));
    return;
  }
  else {
    list($entity_id, , $bundle) = entity_extract_ids($entity_type, $entity);
    $mappings = salesforce_mapping_load_multiple(array(
      'drupal_entity_type' => $entity_type,
      'drupal_bundle' => $bundle,
    ));

    // Check that entity is of a mapped type/bundle.
    if (empty($mappings)) {
      form_set_error('entity_id', t('Selected entity is of a bundle that is not mapped.'));
      return;
    }
  }

  // For new mappings, validate entity type/id.
  if (!empty($mapping_object->is_new) && $mapping_object->is_new) {
    // Check for existing mapping based on the Drupal entity.
    $mapping_object_drupal = salesforce_mapping_object_load_by_drupal($entity_type, $entity_id, TRUE);

    if ($mapping_object_drupal &&
      (empty($mapping_object->salesforce_mapping_object_id) || $mapping_object_drupal->salesforce_mapping_object_id != $mapping_object->salesforce_mapping_object_id)) {
      form_set_error('entity_id', t('Drupal entity is already mapped to a Salesforce object.'));
    }
  }
  $mapping = reset($mappings);

  // Convert to 18-char if 15-char ID was given. 
  $values['salesforce_id'] = Salesforce::convertId($values['salesforce_id']);

  // Check for existing mapping based on the Salesforce Id.
  $mapping_object_sf = salesforce_mapping_object_load_by_sfid($values['salesforce_id'], TRUE);
  $sf_object_type = $mapping->salesforce_object_type;

  if ($mapping_object_sf &&
    (empty($mapping_object->salesforce_mapping_object_id) || $mapping_object_sf->salesforce_mapping_object_id != $mapping_object->salesforce_mapping_object_id)) {
    form_set_error('salesforce_id', t('Salesforce object is already mapped to a Drupal entity.'));
  }

  $sfapi = salesforce_get_api();
  // Not authorized, we need to bail this time around.
  if (!$sfapi->isAuthorized()) {
    form_set_error('salesforce_id', t('Salesforce is not authorized.'));
  }
}

function salesforce_mapping_object_form_save_mapping_validate($form, &$form_state) {
  if (empty($form_state['values']['salesforce_id'])) {
    form_set_error('salesforce_id', t('Salesforce ID is required to save a new mapping.'));
  }
  $form_state['values']['salesforce_id'] = Salesforce::convertId($form_state['values']['salesforce_id']);
  if (strlen($form_state['values']['salesforce_id']) != 18) {
    form_set_error('salesforce_id', t('Invalid Salesforce ID.'));
  }
}

/**
 * Implements hook_form_submit().
 */
function salesforce_mapping_object_form_save_mapping_submit($form, &$form_state) {
  $mapping_object = $form_state['salesforce_mapping_object'];
  if (is_null($mapping_object)) {
    $mapping_object = entity_create('salesforce_mapping_object', array(
      'entity_id' => $form_state['values']['entity_id'],
      'entity_type' => $form_state['values']['entity_type'],
      'last_sync' => time(),
    ));
  }
  $mapping_object->salesforce_id = $form_state['values']['salesforce_id'];
  // @todo this would be sensible but causes a DB explosion:
  // $mapping_object->last_sync->set(NULL);
  $mapping_object->last_sync_message = t('Mapping object edited via the UI.');
  $mapping_object->last_sync_status = SALESFORCE_MAPPING_STATUS_SUCCESS;
  $mapping_object->last_sync_action = $form_state['values']['submit'] == 'Update mapping' ? 'relink' : 'created';
  $mapping_object->entity_updated = REQUEST_TIME;
  $mapping_object->save();
  drupal_set_message(t('Salesforce mapping object has been saved.'));
  $uri = $mapping_object->uri();
  $form_state['redirect'] = $uri['path'];
}

/**
 * Form definition for the mapping object filter form.
 */
function salesforce_mapping_object_filter_form($form, &$form_state) {

  $form = array();

  $values = !empty($_GET['search']) ? $_GET['search'] : NULL;

  $form['search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($values),
    '#tree' => TRUE,
  );

  // Get list of mapped entity types.
  $mapped_entities = salesforce_mapping_get_mapped_entities();
  $entity_options = array('' => '');
  // Build an options array of entity types that have mappings.
  foreach ($mapped_entities as $type => $bundles) {
    $info = entity_get_info($type);
    $entity_options[$type] = $info['label'];
  }

  $form['search']['entity_type'] = array(
    '#type' => 'select',
    '#title' => t('Entity type'),
    '#options' => $entity_options,
    '#empty_option' => t('- Select an entity type -'),
    '#default_value' => isset($values['entity_type']) ? $values['entity_type'] : '',
  );

  $form['search']['entity_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Drupal Entity Id'),
    '#size' => 19,
    '#default_value' => isset($values['entity_id']) ? $values['entity_id'] : '',
    '#states' => array(
      'visible' => array(
        ':input[name="search[entity_type]"]' => array('!value' => key($entity_options)),
      ),
    ),
  );

  $form['search']['salesforce_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Salesforce Id'),
    '#size' => 19,
    '#maxlength' => 18,
    '#default_value' => isset($values['salesforce_id']) ? $values['salesforce_id'] : '',
  );

  $form['search']['last_sync_action'] = array(
    '#type' => 'select',
    '#title' => t('Last sync action'),
    '#empty_option' => t('- Any -'),
    // @TODO fix this options definition
    '#options' => array(
      'push' => t('Push'),
      'pull' => t('Pull'),
      'relink' => t('Relink'),
      'created' => t('Created'),
    ),
    '#default_value' => isset($values['last_sync_action']) ? $values['last_sync_action'] : '',
  );

  $form['search']['last_sync_status'] = array(
    '#type' => 'select',
    '#title' => t('Last sync status'),
    '#empty_option' => t('- Any -'),
    '#options' => salesforce_mapping_object_sync_status(),
    '#default_value' => isset($values['last_sync_status']) ? $values['last_sync_status'] : '',
  );

  // Check to see if date_popup is installed so we can provide a friendlier UI.
  $date_popup_installed = FALSE;
  if (module_exists('date_popup')) {
    $date_popup_installed = TRUE;
  }

  $form['search']['last_sync'] = array(
    '#type' => 'item',
    '#title' => t('Last sync'),
    '#tree' => TRUE,
  );

  $form['search']['last_sync']['from'] = array(
    '#type' => 'textfield',
    '#title' => t('From'),
    '#default_value' => $values['last_sync']['from'],
    '#description' => t('Format: %time.', array(
      '%time' => format_date(time(), 'custom', 'Y-m-d H:i:s'),
      )
    ),
  );

  $form['search']['last_sync']['to'] = array(
    '#type' => 'textfield',
    '#title' => t('To'),
    '#default_value' => $values['last_sync']['to'],
    '#description' => t('Format: %time.', array(
        '%time' => format_date(time(), 'custom', 'Y-m-d H:i:s'),
      )
    ),
  );

  if ($date_popup_installed) {
    $form['search']['last_sync']['from']['#type'] = 'date_popup';
    $form['search']['last_sync']['from']['#format'] = 'Y-m-d H:i:s';
    unset($form['search']['last_sync']['from']['#maxlength']);
    unset($form['search']['last_sync']['from']['#description']);

    $form['search']['last_sync']['to']['#type'] = 'date_popup';
    $form['search']['last_sync']['to']['#format'] = 'Y-m-d H:i:s';
    unset($form['search']['last_sync']['to']['#maxlength']);
    unset($form['search']['last_sync']['to']['#description']);
  }
  $form['search']['limit'] = array(
    '#type' => 'select',
    '#title' => t('Items per page'),
    '#options' => array(
      25 => 25,
      50 => 50,
      100 => 100,
      150 => 150,
      200 => 200,
    ),
    '#default_value' => !empty($values['limit']) ? $values['limit'] : 25,
  );

  $form['search']['search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );

  $form['search']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#limit_validation_errors' => array(),
    '#submit' => array('salesforce_mapping_object_filter_form_reset'),
  );

  return $form;
}

/**
 * Submit handler for salesforce_mapping_object_filter_form().
 */
function salesforce_mapping_object_filter_form_submit($form, &$form_state) {
  $filters = array(
    'search' => $form_state['values']['search'],
  );
  $form_state['redirect'] = array($_GET['q'], array('query' => $filters));
}

/**
 * Submit handler to reset the filter form.
 */
function salesforce_mapping_object_filter_form_reset($form, &$form_state) {
  $form_state['redirect'] = array($_GET['q']);
}

/**
 * Callback to render a list of mapping objects.
 */
function salesforce_mapping_object_overview_page() {

  $header = array(
    'entity_type' => array(
      'data' => t('Entity type'),
      'field' => 'entity_type',
    ),
    'entity' => array(
      'data' => t('Entity label'),
    ),
    'salesforce_id' => array(
      'data' => t('Salesforce object'),
      'field' => 'salesforce_id',
    ),
    'last_sync_action' => array(
      'data' => t('Action'),
      'field' => 'last_sync_action',
    ),
    'last_sync' => array(
      'data' => t('Date/time'),
      'field' => 'last_sync',
      'sort' => 'desc',
    ),
    'last_sync_status' => array(
      'data' => t('Sync status'),
      'field' => 'last_sync_status',
    ),
    'last_sync_message' => array(
      'data' => t('Message'),
      'field' => 'last_sync_message',
    ),
  );

  $statuses = salesforce_mapping_object_sync_status();
  foreach ($statuses as $status_id => $status) {
    $field = 'status_' . $status_id;
    $header[$field] = array(
      'data' => t('@status Count', array('@status' => $status)),
      'field' => $field,
    );
  }

  $header['operations'] = array('data' => t('Operations'));

  return salesforce_mapping_object_overview_table($header);
}

/**
 * Generate the overview filter form/table for mappings.
 */
function salesforce_mapping_object_overview_table($header, $mapping_id = NULL) {
  $rows = array();

  // Get array of possible statuses.
  $statuses = salesforce_mapping_object_sync_status();

  // Need to ensure the query doesn't execute when posing the form.
  $mapping_object_entities = array();

  if (!isset($_POST['form_id'])) {
    $values = !empty($_GET['search']) ? $_GET['search'] : array();
    unset($values['search_submit']);
    unset($values['reset']);

    $limit = 25;
    if (isset($values['limit'])) {
      $limit = ($values['limit'] > 0) ? $values['limit'] : $limit;
      unset($values['limit']);
    }

    $mapping_object_results = salesforce_mapping_object_filter_query($header, $values, $limit, $mapping_id);

    if ($mapping_object_results) {
      $mapping_object_entities = array();
      if ($mapping_id) {
        foreach ($mapping_object_results as $key => $entity) {
          $mapping_object_entities[] = entity_revision_load('salesforce_mapping_object', $key);
        }
      }
      else {
        $mapping_object_entities = entity_load('salesforce_mapping_object', array_keys($mapping_object_results));
      }
    }
  }
  foreach ($mapping_object_entities as $id => $mapping_object) {
    $mapping_object_id = $mapping_object->salesforce_mapping_object_id;
    $row_id = $mapping_object_id . '-' . $id;
    $uri = $mapping_object->uri();

    $wrapper = entity_metadata_wrapper('salesforce_mapping_object', $mapping_object);

    foreach ($header as $property => $header_settings) {
      if (!empty($wrapper->{$property})) {
        $rows[$row_id][$property] = salesforce_mapping_object_render_property($wrapper, $property, $wrapper->{$property});
      }
    }

    // Only add additional columns when no specific mapping id is provided.
    if (!$mapping_id) {
      foreach ($statuses as $status_id => $status) {
        $field = 'status_' . $status_id;
        $rows[$row_id][$field] = $mapping_object_results[$id]->{$field};
      }
      $rows[$row_id]['operations'] = l(t('view'), $uri['path']) . ' ' .
        l(t('edit'), $uri['path'] . '/edit', array('query' => drupal_get_destination())) . ' ' .
        l(t('delete'), $uri['path'] . '/delete', array('query' => drupal_get_destination()));
    }
  }

  $table['search'] = drupal_get_form('salesforce_mapping_object_filter_form');
  if ($mapping_id) {
    $table['table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    );
  }
  else {
    $table['table'] = drupal_get_form('salesforce_mapping_object_table_form', $header, $rows, $mapping_id);
  }
  $table['pager'] = array('#theme' => 'pager', '#weight' => 99);

  return $table;
}

/**
 * Bulk operations form for Salesforce mapping objects.
 */
function salesforce_mapping_object_table_form($form, &$form_state, $header, $options) {
  $form = array();

  $form['bulk_operations'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bulk Operations'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['bulk_operations']['operations'] = array(
    '#type' => 'select',
    '#options' => array(
      0 => t('Select a bulk operation'),
      'push' => t('Push to Salesforce'),
    ),
  );

  $form['bulk_operations']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  $form['entities'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#attributes' => array('class' => array('entity-sort-table')),
    '#empty' => t('There are no mappings.'),
  );

  return $form;
}

/**
 * Submit handle for the bulk operations form.
 */
function salesforce_mapping_object_table_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['operations'] && count($values['entities']) > 0) {
    // @TODO switch to using the Batch API for processing.
    foreach ($values['entities'] as $value) {
      list($mapping_id) = explode('-', $value);
      $mapping = entity_load_single('salesforce_mapping_object', $mapping_id);
      // Set entity_updated to now to ensure push occurs.
      $mapping->entity_updated = REQUEST_TIME;
      $wrapper = entity_metadata_wrapper('salesforce_mapping_object', $mapping);
      salesforce_push_entity_crud($mapping->entity_type, $wrapper->entity->value(), SALESFORCE_MAPPING_SYNC_DRUPAL_UPDATE);
    }
  }
}
