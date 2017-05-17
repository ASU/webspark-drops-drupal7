<?php

/**
 * @file
 * Containse the MembershipEntityTermController class.
 */

/**
 * Entity controller class for membership term entities.
 */
class MembershipEntityTermController extends EntityAPIController {
  /**
   * Overrides EntityAPIController::create().
   */
  public function create(array $values = array()) {
    // Add some defaults.
    $values += array(
      'id' => 0,
      'mid' => 0,
      'term' => '',
      'status' => MEMBERSHIP_ENTITY_ACTIVE,
      'modifiers' => array(),
      'start' => date_format_date(date_now('UTC'), 'custom', DATE_FORMAT_DATETIME),
      'membership_entity_type' => 'membership',
      'timezone' => 'UTC',
      'created' => REQUEST_TIME,
    );
    return parent::create($values);
  }

  /**
   * Load all terms for a given membership.
   *
   * @param MembershipEntity|int $membership
   *   A membership object or mid.
   */
  public function loadByMembership($membership) {
    // Support mid or entire membership object.
    $mid = is_object($membership) ? $membership->mid : $membership;

    $ids = array();
    $efq = new EntityFieldQuery();
    $result = $efq->entityCondition('entity_type', 'membership_entity_term')
      ->propertyCondition('mid', $mid)
      ->propertyOrderBy('start')
      ->execute();
    if (!empty($result)) {
      $ids = array_merge($ids, array_keys($result['membership_entity_term']));
    }
    return $this->load($ids);
  }

  protected function buildQuery($ids, $conditions = array(), $revision_id = FALSE) {
    $query = parent::buildQuery($ids, $conditions, $revision_id);

    // Specify additional fields from the membership table.
    $query->innerJoin('membership_entity', 'm', 'base.mid = m.mid');
    $query->addField('m', 'type', 'membership_entity_type');
    return $query;
  }
}
