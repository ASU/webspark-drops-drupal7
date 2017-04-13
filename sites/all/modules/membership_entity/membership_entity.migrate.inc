<?php

/**
 * @file
 * Migrate module support for memberships.
 */

/**
 * Destination class implementing migration into memberships.
 */
class MigrateDestinationMembershipEntity extends MigrateDestinationEntity {
  static public function getKeySchema() {
    return array(
      'mid' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'description' => 'ID of destination membership',
      ),
    );
  }

  /**
   * Return an options array for membership destinations.
   *
   * @param string $language
   *   Default language for memberships created via this destination class.
   */
  static public function options($language) {
    return compact('language');
  }

  /**
   * Basic initialization.
   *
   * @param string $bundle
   *   The membership type.
   * @param array $options
   *   Options applied to memberships.
   */
  public function __construct($bundle, array $options = array()) {
    parent::__construct('membership_entity', $bundle, $options);
  }

  /**
   * Returns a list of fields available to be mapped for the membership type.
   *
   * @param Migration $migration
   *   Optionally, the migration containing this destination.
   * @return array
   *   Keys: machine names of the fields (to be passed to addFieldMapping)
   *   Values: Human-friendly descriptions of the fields.
   */
  public function fields($migration = NULL) {
    $fields = array();

    // Core membership properties
    $fields['mid'] = t('Membership: Internal membership ID');
    $fields['type'] = t('Membership: The type of membership');
    $fields['member_id'] = t('Membership: The unique member ID');
    $fields['uid'] = t('Membership: The primary member (uid)');
    $fields['secondary_members'] = t('Membership: The secondary member(s) (uid)');
    $fields['status'] = t('Membership: The membership status code');
    $fields['created'] = t('Membership: created timestamp');
    $fields['changed'] = t('Membership: modified timestamp');
    $fields['is_new'] = t('Option: Indicates a new membership with the specified mid should be created');

    // Add in anything provided by handlers
    $fields += migrate_handler_invoke_all('Entity', 'fields', $this->entityType, $this->bundle, $migration);
    $fields += migrate_handler_invoke_all('MembershipEntity', 'fields', $this->entityType, $this->bundle, $migration);

    return $fields;
  }

  /**
   * Delete a batch of memberships at once.
   *
   * @param $mids
   *   Array of membership IDs to be deleted.
   */
  public function bulkRollback(array $mids) {
    migrate_instrument_start('membership_entity_delete_multiple');
    $this->prepareRollback($mids);
    membership_entity_delete_multiple($mids);
    $this->completeRollback($mids);
    migrate_instrument_stop('membership_entity_delete_multiple');
  }

  /**
   * Import a single membership.
   *
   * @param $membership
   *   The membership entity object to build. Prefilled with any fields mapped
   *   in the Migration.
   * @param $row
   *   Raw source data object - passed through to prepare/complete handlers.
   * @return array
   *   Array of key fields (mid) of the membership that was saved.
   *   FALSE on failure.
   */
  public function import(stdClass $membership, stdClass $row) {
    // Migrate flattens single value arrays by default. Make sure
    // secondary_members is always an array.
    if (isset($membership->secondary_members) && !is_array($membership->secondary_members)) {
      $membership->secondary_members = array($membership->secondary_members);
    }

    // Convert $membership to an instance of MembershipEntity.
    $membership = membership_entity_create_from_stdclass($membership);

    // Updating previously-migrated content?
    $migration = Migration::currentMigration();
    if (isset($row->migrate_map_destid1)) {
      // Make sure is_new is off
      $membership->is_new = FALSE;
      if (isset($membership->mid)) {
        if ($membership->mid != $row->migrate_map_destid1) {
          throw new MigrateException(t("Incoming mid !mid and map destination mid !destid1 don't match",
            array('!mid' => $membership->mid, '!destid1' => $row->migrate_map_destid1)));
        }
      }
      else {
        $membership->mid = $row->migrate_map_destid1;
      }
    }
    if ($migration->getSystemOfRecord() == Migration::DESTINATION) {
      if (!isset($membership->mid)) {
        throw new MigrateException(t('System-of-record is DESTINATION, but no destination mid provided'));
      }
      $old_membership = membership_entity_load($membership->mid);
      if (empty($old_membership)) {
        throw new MigrateException(t('System-of-record is DESTINATION, but membership !mid does not exist',
                                   array('!mid' => $membership->mid)));
      }
      if (!isset($membership->created)) {
        $membership->created = $old_membership->created;
      }
      if (!isset($membership->status)) {
        $membership->status = $old_membership->status;
      }
      if (!isset($membership->uid)) {
        $membership->uid = $old_membership->uid;
      }
      if (!isset($membership->secondary_members)) {
        $membership->secondary_members = $old_membership->secondary_members;
      }
    }
    elseif (!isset($membership->type)) {
      $membership->type = $this->bundle;
    }

    if ($migration->getSystemOfRecord() == Migration::SOURCE) {
      if (isset($membership->created)) {
        $membership->created = MigrationBase::timestamp($membership->created);
      }
      else {
        $membership->created = REQUEST_TIME;
      }
      if (isset($membership->changed)) {
        $membership->changed = MigrationBase::timestamp($membership->changed);
      }
      if (!isset($membership->secondary_members)) {
        $membership->secondary_members = array();
      }
    }

    // Invoke migration prepare handlers
    $this->prepare($membership, $row);

    // Trying to update an existing membership.
    if ($migration->getSystemOfRecord() == Migration::DESTINATION) {
      // Incoming data overrides existing data, so only copy non-existent fields
      foreach ($old_membership as $field => $value) {
        if (property_exists($membership, $field) && $membership->$field === NULL) {
          // Ignore this field
          continue;
        }
        elseif (!isset($membership->$field)) {
          $membership->$field = $old_membership->$field;
        }
      }
    }

    if (isset($membership->mid) && !(isset($membership->is_new) && $membership->is_new)) {
      $updating = TRUE;
    }
    else {
      $updating = FALSE;
    }

    migrate_instrument_start('membership_entity_save');
    membership_entity_save($membership);
    migrate_instrument_stop('membership_entity_save');

    if (isset($membership->mid)) {
      if ($updating) {
        $this->numUpdated++;
      }
      else {
        $this->numCreated++;
      }

      $return = array($membership->mid);
    }
    else {
      $return = FALSE;
    }

    $this->complete($membership, $row);
    return $return;
  }
}
