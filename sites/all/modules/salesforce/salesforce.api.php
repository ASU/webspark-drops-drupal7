<?php

/**
 * @file
 * These are the hooks that are invoked by the Salesforce core.
 *
 * Core hooks are typically called in all modules at once using
 * module_invoke_all().
 */

/**
 * @defgroup salesforce_hooks Hooks provided by Salesforce API
 * @{
 */

/**
 * Trigger action when first building the list of fieldmap types.
 */
function hook_salesforce_mapping_fieldmap_type() {

}

/**
 * Alter existing fieldmap types.
 *
 * @param array $fieldmap_type
 *   Array of fieldmap Salesforce types
 */
function hook_salesforce_mapping_fieldmap_type_alter($fieldmap_type) {

}

/**
 * Define or alter the mapping object during a pull.
 *
 * @param mixed $mapping_object
 *   The mapping object that was detected based on existing mappings or FALSE
 *   if no exisitng mapping object exists.
 * @param array $sf_object
 *   The salesforce object data that will be used in this pull.
 * @param SalesforceMapping $mapping
 *   The salesforce mapping that will be used during the pull.
 */
function hook_salesforce_pull_mapping_object_alter(&$mapping_object, $sf_object, $mapping) {
  // Do some prematching for incoming user pulls if we don't already have a
  // match.
  if (!$mapping_object && $mapping->drupal_entity_type == 'user') {
    // Run some complex custom prematching logic that searches for an existing
    // Drupal user that is a match to the incoming Salesforce data.
    $matched_user = mymodule_custom_sf_pull_prematch($sf_object, $mapping);
    if ($matched_user) {
      // If we have a match create mapping object on-the-fly and then reload it
      // This means that the rest of the pull logic will target this matched
      // user instead of creating a new one.
      entity_create('salesforce_mapping_object', array(
        'salesforce_id' => $sf_object['Id'],
        'entity_type' => $mapping->drupal_entity_type,
        'entity_id' => $matched_user->uid,
        'last_sync_message' => t('User prematch on pull'),
        'last_sync_status' => SALESFORCE_MAPPING_STATUS_SUCCESS
      ))->save();
      $mapping_object = salesforce_mapping_object_load_by_sfid($sf_object['Id'], TRUE);
    }
  }
}

/**
 * Define or alter the mapping object during a push.
 *
 * @param mixed $mapping_object
 *   The mapping object that was detected based on existing mappings or FALSE
 *   if no exisitng mapping object exists.
 * @param object $entity
 *   The Drupal entity that is being pushed.
 * @param SalesforceMapping $mapping
 *   The salesforce mapping that will be used during the push.
 */
function hook_salesforce_push_mapping_object_alter(&$mapping_object, $entity, $mapping) {
  // Do some prematching for outgoing user pushes if we don't already have a
  // match.
  if (!$mapping_object && $mapping->drupal_entity_type == 'user') {
    // Run some complex custom prematching logic that queries Salesforce for an
    // existing contact (beyond a basic external key comparison) that is a match
    // to this Drupal user.
    $matched_contact = mymodule_custom_sf_push_prematch($entity, $mapping);
    if ($matched_contact) {
      // If we have a match create mapping object on-the-fly and then reload it
      // This means that the rest of the push logic will target this matched
      // contact instead of creating a new one.
      entity_create('salesforce_mapping_object', array(
        'salesforce_id' => $matched_contact['Id'],
        'entity_type' => $mapping->drupal_entity_type,
        'entity_id' => $entity->uid,
        'last_sync_message' => t('User prematch on push'),
        'last_sync_status' => SALESFORCE_MAPPING_STATUS_SUCCESS
      ))->save();
      $mapping_object = salesforce_mapping_object_load_by_drupal('user', $entity->uid, TRUE);
    }
  }
}

/**
 * Alter parameters mapped to a Salesforce object before syncing to Salesforce.
 *
 * @param array $params
 *   Associative array of key value pairs.
 * @param object $mapping
 *   Salesforce mapping object.
 * @param object $entity_wrapper
 *   EntityMetadataWrapper of entity being mapped.
 */
function hook_salesforce_push_params_alter(&$params, $mapping, $entity_wrapper) {

}

/**
 * Provide URIs manually for poorly-behaved entity types.
 *
 * Note that this hook is self-implemented in salesforce_mapping.module, where
 * User and Node are both initialized.
 *
 * @param array $entity_uris
 *   An array of items indexed as 'entity_type' => URI, where URI contains a
 *   $path index.
 */
function hook_salesforce_mapping_entity_uris_alter(&$entity_uris) {
  // For example:
  $entity_uris['node'] = array(
    'path' => 'node/',
  );
}

/**
 * Prevent push to SF for an entity for a given mapping. For example: mapping a
 * single Drupal object to multiple separate Salesforce objects, but only
 * syncing under certain conditions.
 *
 * @param string $entity_type
 *   The type of entity the push is for.
 * @param object $entity
 *   The entity object the push is for.
 * @param int $sf_sync_trigger
 *   Constant for the Drupal operation that triggered the sync.
 * @param SalesforceMapping $mapping
 *   Salesforce mapping object for which to allow/disallow sync.
 *
 * @return bool
 *   FALSE if the entity should not be synced to Salesforce for this mapping/sync trigger.
 */
function hook_salesforce_push_entity_allowed($entity_type, $entity, $sf_sync_trigger, $mapping) {
  // Example: Don't sync the admin user.
  if ($entity_type == 'user' && $entity->uid === 1) {
    return FALSE;
  }
}

/**
 * Alter the value being mapped to an entity property from a Salesforce object.
 *
 * @param string $value
 *   Salesforce field value.
 * @param array $field_map
 *   Associative array containing the field mapping in the form
 *   <code>
 *   'fieldmap_name' => array(
 *      'drupal_field' => array(
 *        'fieldmap_type' => 'property',
 *        'fieldmap_value' => 'first_name'
 *      ),
 *      'salesforce_field' => array()
 *   )
 *   </code>
 * @param object $sf_object
 *   Fully loaded Salesforce object
 */
function hook_salesforce_pull_entity_value_alter(&$value, $field_map, $sf_object) {

}

/**
 * Alter a SOQL select query before it is executed. For example, filter
 * target SObjects by a date value, or add an additional field to the query.
 *
 * @param SalesforceSelectQuery $query
 *   The query object to alter.
 *
 * @see includes/salesforce.select_query.inc
 */
function hook_salesforce_query_alter(SalesforceSelectQuery &$query) {
  if ($query->objectType == 'Contact') {
    $query->fields[] = 'Drupal_Field__c';
    $query->addCondition('Email', "''", '!=');
  }
}

/**
 * A salesforce push has succeeded: Implementations may wish to react, for
 * example, by alerting an administrator.
 *
 * @param string $op
 *   The salesforce operation: Create, Update, Upsert, or Delete
 * @param object $result
 *   The salesforce response
 * @param array $synced_entity
 *   Entity data for this push. This array has 4 keys
 *     'entity_wrapper': entity_metadata_wrapper() for the Drupal entity 
 *     'mapping_object': salesforce mapping object record, if it exists. 
 *       Otherwise null
 *     'queue_item': If this is a SOAP push, Drupal queue item corresponding to
 *       this push attempt. Otherwise FALSE.
 *     'mapping': SalesforceMapping being used for this push
 */
function hook_salesforce_push_success($op, $result, $synced_entity) {
  $mapping_object = FALSE;
  if (!empty($synced_entity['mapping_object'])) {
    $mapping_object = $synced_entity['mapping_object'];
  }
  if (drupal_strtolower($op) == 'delete' && $mapping_object) {
    $mapping_object->delete();
    return;
  }

  if (!$mapping_object) {
    // Create mapping object, saved below.
    $wrapper = $synced_entities[$key]['entity_wrapper'];
    list($entity_id) = entity_extract_ids($wrapper->type(), $wrapper->value());
    $mapping_object = entity_create('salesforce_mapping_object', array(
      'entity_id' => $entity_id,
      'entity_type' => $wrapper->type(),
      'salesforce_id' => $result->id,
      'last_sync_message' => t('Mapping object created via !function.', array('!function' => __FUNCTION__)),
    ));
  }
  else {
    $mapping_object->last_sync_message = t('Mapping object updated via !function.', array('!function' => __FUNCTION__));
  }

  $mapping_object->last_sync_status = SALESFORCE_MAPPING_STATUS_SUCCESS;
  $mapping_object->last_sync = REQUEST_TIME;
  $mapping_object->last_sync_action = 'push';
  $mapping_object->save();

  watchdog('salesforce_push', '%op: Salesforce object %id',
    array('%id' => $result->id, '%op' => $op)
  );
}

/**
 * A salesforce push has failed: Implementations may wish to react, for
 * example, by logging the failure or alerting an administrator.
 *
 * @param string $op
 *   The salesforce operation: Create, Update, Upsert, or Delete
 * @param object $result
 *   The salesforce response
 * @param array $synced_entity
 *   Entity data for this push. This array has 4 keys
 *     'entity_wrapper': entity_metadata_wrapper() for the Drupal entity 
 *     'mapping_object': salesforce mapping object record, if it exists. 
 *       Otherwise null
 *     'queue_item': If this is a SOAP push, Drupal queue item corresponding to
 *       this push attempt. Otherwise FALSE.
 *     'mapping': SalesforceMapping being used for this push
 */
function hook_salesforce_push_fail($op, $result, $synced_entity) {
  $error_messages = array();
  foreach ($result->errors as $error) {
    watchdog('salesforce_push', '%op error for Salesforce object %id. @code: @message',
      array(
        '%id' => $result->id,
        '@code' => $error->statusCode,
        '@message' => $error->message,
        '%op' => $op,
      ),
      WATCHDOG_ERROR
    );
    $error_messages[] = $error->message;
  }
  if (!empty($synced_entity['mapping_object'])) {
    $mapping_object = $synced_entity['mapping_object'];
    $mapping_object->last_sync = REQUEST_TIME;
    $mapping_object->last_sync_action = 'push';
    $mapping_object->last_sync_status = SALESFORCE_MAPPING_STATUS_ERROR;
    $mapping_object->last_sync_message = t('Push error via %function with the following messages: @message.', array(
      '%function' => __FUNCTION__,
      '@message' => implode(' | ', $error_messages),
    ));
    $mapping_object->save();
  }
}

/**
 * Act on an entity just before it is saved by a salesforce pull operation.
 * Implementations should throw a SalesforcePullException to prevent the pull.
 *
 * @param $entity
 *   The Drupal entity object.
 * @param array $sf_object
 *   The Salesforce query result array.
 * @param SalesforceMapping $sf_mapping
 *   The Salesforce Mapping being used to pull this record
 *
 * @throws SalesforcePullException
 */
function hook_salesforce_pull_entity_presave($entity, $sf_object, $sf_mapping) {
  if (!some_entity_validation_mechanism($entity)) {
    throw new SalesforcePullException('Refused to pull invalid entity.');
  }
  // Set a fictional property using a fictional Salesforce result object.
  $entity->example_property = $sf_object['Lookup__r']['Data__c'];
}

/**
 * Act on an entity after it is inserted by a salesforce pull operation.
 * Implementations may throw SalesforcePullException to prevent updating of the
 * Salesforce Mapping Object, but the entity will already have been saved.
 *
 * @param $entity
 *   The Drupal entity object.
 * @param array $sf_object
 *   The SObject from the pull query (as an array).
 * @param SalesforceMapping $sf_mapping
 *   The Salesforce Mapping being used to pull this record
 *
 * @throws SalesforcePullException
 */
function hook_salesforce_pull_entity_insert($entity, $sf_object, $sf_mapping) {
  // Insert the new entity into a fictional table of all Salesforce-sourced
  // entities.
  $type = $sf_mapping->drupal_entity_type;
  $info = entity_get_info($type);
  list($id) = entity_extract_ids($type, $entity);
  db_insert('example_sf_entity')
    ->fields(array(
      'type' => $type,
      'id' => $id,
      'sf_name' => $sf_object['Name'],
      'created' => REQUEST_TIME,
      'updated' => REQUEST_TIME,
    ))
    ->execute();
}

/**
 * Act on an entity after it is updated by a salesforce pull operation.
 * Implementations may throw SalesforcePullException to prevent updating of the
 * Salesforce Mapping Object, but the entity will already have been saved.
 *
 * @param $entity
 *   The Drupal entity object.
 * @param array $sf_object
 *   The SObject from the pull query (as an array).
 * @param SalesforceMapping $sf_mapping
 *   The Salesforce Mapping being used to pull this record
 *
 * @throws SalesforcePullException
 */
function hook_salesforce_pull_entity_update($entity, $sf_object, $sf_mapping) {
  // Update the entity's entry in a fictional table of all Salesforce-sourced
  // entities.
  $type = $sf_mapping->drupal_entity_type;
  $info = entity_get_info($type);
  list($id) = entity_extract_ids($type, $entity);
  db_update('example_sf_entity')
    ->fields(array(
      'sf_name' => $sf_object['Name'],
      'updated' => REQUEST_TIME,
    ))
    ->condition('type', $type)
    ->condition('id', $id)
    ->execute();
}

/**
 * @} salesforce_hooks
 */
