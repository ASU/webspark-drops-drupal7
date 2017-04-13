<?php

/**
 * @file
 * Contains SalesforceMapping.
 */

/**
 * Entity class for Salesforce Mappings
 */
class SalesforceMapping extends Entity {

  // Only one bundle type for now.
  public $type = 'salesforce_mapping';

  /**
   * Constructor for SalesforceMapping.
   *
   * @param array $values
   *   Associated array of values for the fields the entity should start with.
   */
  public function __construct(array $values = array()) {
    parent::__construct($values, 'salesforce_mapping');
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
    return parent::save();
  }

  /**
   * Retreive the default URI.
   *
   * @return array
   *   Associated array with the default URI on the 'path' key.
   */
  protected function defaultUri() {
    return array('path' => 'admin/structure/salesforce/mappings/manage/' . $this->identifier());
  }

}
