<?php

/**
 * @file
 * Migrate module support for membership terms.
 */

/**
 * Destination class implementing migration into memberships terms.
 */
class MigrateDestinationMembershipEntityTerm extends MigrateDestinationEntity {
  static public function getKeySchema() {
    return array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'description' => 'ID of destination membership term',
      ),
    );
  }

  /**
   * Basic initialization.
   *
   * @param array $options
   *   Options applied to membership terms.
   */
  public function __construct($bundle = 'membership', array $options = array()) {
    parent::__construct('membership_entity_term', $bundle, $options);
  }

  /**
   * Returns a list of fields available to be mapped for the membership term.
   *
   * @param Migration $migration
   *   Optionally, the migration containing this destination.
   * @return array
   *   Keys: machine names of the fields (to be passed to addFieldMapping)
   *   Values: Human-friendly descriptions of the fields.
   */
  public function fields($migration = NULL) {
    $fields = array();

    // Core membership term properties
    $fields['id'] = t('Membership term: Internal term ID');
    $fields['mid'] = t('Membership term: The membership internal id');
    $fields['status'] = t('Membership term: The membership term status code');
    $fields['term'] = t('Membership term: The human readable term length');
    $fields['modifiers'] = t('Membership term: term length modifiers');
    $fields['start'] = t('Membership term: start date datetime');
    $fields['end'] = t('Membership term: end date datetime');
    $fields['timezone'] = t('Membership term: Start and end date timezone');

    // Add in anything provided by handlers
    $fields += migrate_handler_invoke_all('Entity', 'fields', $this->entityType, $this->bundle, $migration);
    $fields += migrate_handler_invoke_all('MembershipEntityTerm', 'fields', $this->entityType, $this->bundle, $migration);

    return $fields;
  }

  /**
   * Delete a batch of memberships terms at once.
   *
   * @param $mids
   *   Array of membership term IDs to be deleted.
   */
  public function bulkRollback(array $ids) {
    migrate_instrument_start('membership_entity_term_delete_multiple');
    $this->prepareRollback($ids);
    membership_entity_term_delete_multiple($ids);
    $this->completeRollback($ids);
    migrate_instrument_stop('membership_entity_term_delete_multiple');
  }

  /**
   * Import a single membership term.
   *
   * @param $term
   *   The membership term entity object to build. Prefilled with any fields
   *   mapped in the Migration.
   * @param $row
   *   Raw source data object - passed through to prepare/complete handlers.
   * @return array
   *   Array of key fields (mid) of the membership term that was saved.
   *   FALSE on failure.
   */
  public function import(stdClass $term, stdClass $row) {
    // Convert $term to an instance of MembershpEntityTerm.
    $term = membership_entity_term_create_from_stdclass($term);

    // Updating previously-migrated content?
    $migration = Migration::currentMigration();
    if (isset($row->migrate_map_destid1)) {
      // Make sure is_new is off
      $term->is_new = FALSE;
      if (isset($term->id)) {
        if ($term->id != $row->migrate_map_destid1) {
          throw new MigrateException(t("Incoming id !id and map destination id !destid1 don't match",
            array('!id' => $term->mid, '!destid1' => $row->migrate_map_destid1)));
        }
      }
      else {
        $term->id = $row->migrate_map_destid1;
      }
    }
    if ($migration->getSystemOfRecord() == Migration::DESTINATION) {
      if (!isset($term->id)) {
        throw new MigrateException(t('System-of-record is DESTINATION, but no destination id provided'));
      }
      $old_term = membership_entity_term_load($term->id);
      if (empty($old_term)) {
        throw new MigrateException(t('System-of-record is DESTINATION, but membership term !id does not exist',
                                   array('!id' => $term->id)));
      }
      if (!isset($term->term)) {
        $term->term = $old_term->term;
      }
      if (!isset($term->status)) {
        $term->status = $old_term->status;
      }
      if (!isset($term->start)) {
        $term->start = $old_term->start;
      }
      if (!isset($term->mid)) {
        $term->mid = $old_term->mid;
      }
      if (!isset($term->modifiers)) {
        $term->modifiers = $old_term->modifiers;
      }
    }

    if ($migration->getSystemOfRecord() == Migration::SOURCE) {
      if (isset($term->start)) {
        $term->start = $this->datetime($term->start);
      }
      else {
        $term->start = REQUEST_TIME;
      }
      if (isset($term->end)) {
        $term->end = $this->datetime($term->end);
      }
      if (!isset($term->modifiers)) {
        $term->modifiers = array();
      }
    }

    // Invoke migration prepare handlers
    $this->prepare($term, $row);

    // Trying to update an existing membership term.
    if ($migration->getSystemOfRecord() == Migration::DESTINATION) {
      // Incoming data overrides existing data, so only copy non-existent fields
      foreach ($old_term as $field => $value) {
        if (property_exists($term, $field) && $term->{$field} === NULL) {
          // Ignore this field
          continue;
        }
        elseif (!isset($term->{$field})) {
          $term->{$field} = $old_term->{$field};
        }
      }
    }

    if (isset($term->id) && !(isset($term->is_new) && $term->is_new)) {
      $updating = TRUE;
    }
    else {
      $updating = FALSE;
    }

    migrate_instrument_start('membership_entity_term_save');
    membership_entity_term_save($term);
    migrate_instrument_stop('membership_entity_term_save');

    if (isset($term->id)) {
      if ($updating) {
        $this->numUpdated++;
      }
      else {
        $this->numCreated++;
      }

      $return = array($term->id);
    }
    else {
      $return = FALSE;
    }

    $this->complete($term, $row);
    return $return;
  }

  /**
   * Convert an incoming date to datetime format.
   *
   * @param mixed $value
   *   The incoming date value as a string or timestamp.
   * @return string
   *   The date in datetime format.
   */
  static protected function datetime($value) {
    if (empty($value)) {
      $value = 'now';
    }

    // Is it a timestamp?
    if (is_numeric($value)) {
      return format_date($value, 'custom', DATE_FORMAT_DATETIME);
    }

    $date = new DateObject($value, new DateTimezone('UTC'));
    return date_format_date($date, 'custom', DATE_FORMAT_DATETIME);
  }
}
