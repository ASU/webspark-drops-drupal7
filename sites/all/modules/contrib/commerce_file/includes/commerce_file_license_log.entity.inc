<?php

/**
 * @file
 * Provides a base class for CommreceFileLicenseLogEntity.
 */

/**
 * A Commerce File License Log entity class.
 *
 * It's suggested, but not required, to extend this class and to override
 * __construct() in order to specify a fixed entity type.
 *
 * For providing an entity label and URI it is suggested to override the
 * defaultLabel() and defaultUri() methods, and to specify the
 * entity_class_label() and entity_class_uri() as respective callbacks in
 * hook_entity_info(). That way modules are able to override your defaults
 * by altering the hook_entity_info() callbacks, while $entity->label() and
 * $entity->uri() reflect this changes as well.
 */
class CommerceFileLicenseLogEntity extends Entity {

  /**
   * Overridden __construct()
   *  - set fixed entity type
   *  - merge in defaults
   */
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, COMMERCE_FILE_LICENSE_LOG_ENTITY_NAME);
  }

  // -----------------------------------------------------------------------
  // Base Class overridden functions

  /**
   * Overridden buildContent()
   *  - add custom fields to the output.
   */
  public function buildContent($view_mode = 'full', $langcode = NULL) {
    return $this->get_controller()->buildContent($this, $view_mode, $langcode, $content);
  }

  /**
   * Specifies the default label, which is picked up by label() by default.
   */
  protected function defaultLabel() {
    if (!empty($this->entityInfo['entity keys']['label']) && isset($this->{$this->entityInfo['entity keys']['label']})) {
      return $this->{$this->entityInfo['entity keys']['label']};
    }
    return FALSE;
  }

  /**
   * Specifies the default uri, which is picked up by uri() by default.
   */
  protected function defaultURI() {
    return array('path' => $this->entityType . 's/' . $this->identifier());
  }


  // -----------------------------------------------------------------------
  // Custom functions

  /**
   * Return entity controller
   */
  public function get_controller() {
    return entity_get_controller($this->entityType);
  }

  /**
   * Access callback
   */
  public function access($op = 'view', $account = NULL) {
    return entity_access($op, $this->entityType, $this, $account);
  }

  /**
   * Invoke hook
   */
  public function invoke($hook) {
    return $this->get_controller()->invoke($hook, $this);
  }

  /**
   * License
   */
  public function license() {
    if (isset($this->license_id)) {
      return commerce_file_license_load($this->license_id);
    }
    return NULL;
  }
}
