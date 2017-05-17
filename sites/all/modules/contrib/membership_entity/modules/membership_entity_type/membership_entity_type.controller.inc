<?php

/**
 * @file
 * Contains the MembershipEntityTypeController class.
 */

/**
 * Entity controller class for membership types.
 */
class MembershipEntityTypeController extends EntityAPIControllerExportable {
  /**
   * Overrides EntityAPIControllerExportable::create().
   */
  public function create(array $values = array()) {
    $values += array(
      'label' => '',
      'type' => '',
      'description' => '',
      'weight' => 0,
      'data' => array(
        'cardinality' => '1',
        'show_on_profile' => 1,
        'all_edit' => 0,
        'roles' => array(),
        'primary_role' => '',
        'secondary_role' => '',
      ),
    );
    return parent::create($values);
  }

  /**
   * Overrides EntityAPIControllerExportable::save().
   */
  public function save($type, DatabaseTransaction $transaction = NULL) {
    $status = parent::save($type, $transaction);

    // Clear field info and menu caches.
    field_info_cache_clear();
    menu_rebuild();

    return $status;
  }
}
