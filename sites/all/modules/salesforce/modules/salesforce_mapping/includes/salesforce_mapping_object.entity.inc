<?php

/**
 * @file
 * Contains SalesforceMappingObject.
 */

/**
 * Entity class for Salesforce Mapping Objects
 */
class SalesforceMappingObject extends Entity {

  // @codingStandardsIgnoreStart
  public
    $salesforce_mapping_object_id,
    $revision_id,
    $salesforce_id,
    $entity_id,
    $entity_type,
    $created,
    $entity_updated,
    $last_sync,
    $last_sync_action,
    $last_sync_status,
    $last_sync_message;
  // @codingStandardsIgnoreEnd

  /**
   * Constructor for SalesforceMappingObject.
   *
   * @param array $values
   *   Associated array of values this entity should start with.
   */
  public function __construct(array $values = array()) {
    parent::__construct($values, 'salesforce_mapping_object');
  }

  /**
   * Retrieve the default URI.
   *
   * @return array
   *   Associated array with the default URI on the 'path' key.
   */
  protected function defaultUri() {
    $uri = NULL;

    $wrapper = entity_metadata_wrapper($this->entityType(), $this);
    $entity = $wrapper->entity->value();
    if ($entity) {
      $uri = method_exists($entity, 'uri') ? $entity->uri() : entity_uri($this->entity_type, $entity);
    }
    if (is_null($uri)) {
      $path = 'admin/content/salesforce/' . $this->entity_type . '/' . $this->entity_id;
    }
    else {
      $path = $uri['path'];
    }
    return array('path' => $path . '/salesforce_activity');
  }

  /**
   * Retrieve the default label.
   */
  protected function defaultLabel() {
    if (isset($this->is_new) && $this->is_new === TRUE) {
      return '';
    }
    $label = NULL;
    $wrapper = entity_metadata_wrapper('salesforce_mapping_object', $this);
    $label = $wrapper->entity->label();
    $label = ($label) ? $label : $this->entity_type . ':' . $this->entity_id;
    return t('"@label" to "@sf_id"', array('@label' => $label, '@sf_id' => $this->salesforce_id));
  }

  /**
   * Save the entity.
   *
   * @return object
   *   The newly saved version of the entity.
   */
  public function save() {
    if (isset($this->is_new) && $this->is_new) {
      $this->created = REQUEST_TIME;
    }

    if (!isset($this->is_new_revision)) {
      $this->is_new_revision = TRUE;
    }

    if (!isset($this->default_revision)) {
      $this->default_revision = TRUE;
    }

    return parent::save();
  }

}
