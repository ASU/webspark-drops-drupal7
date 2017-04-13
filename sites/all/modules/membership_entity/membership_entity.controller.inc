<?php

/**
 * @file
 * Containse the MembershipEntityController class.
 */

/**
 * Entity controller class for membership entities.
 */
class MembershipEntityController extends EntityAPIController {
  /**
   * Overrides EntityAPIController::create().
   */
  public function create(array $values = array()) {
    // Add some defaults.
    $values += array(
      'mid' => 0,
      'uid' => 0,
      'member_id' => '',
      'type' => 'membership',
      'created' => REQUEST_TIME,
      'status' => MEMBERSHIP_ENTITY_ACTIVE,
      'secondary_members' => array(),
    );
    $values = parent::create($values);

    // Allow modules to add stuff to the default membership.
    $this->invoke('create', $values);
    return $values;
  }

  /**
   * Overrides EntityAPIController::load().
   */
  public function load($mids = array(), $conditions = array()) {
    $memberships = parent::load($mids, $conditions);

    if (empty($memberships)) {
      // Early exit if membership loading failed.
      return array();
    }

    // Load secondary members.
    foreach ($memberships as $membership) {
      $membership->secondary_members = array();
      $secondary_members = db_query('SELECT uid, weight FROM {membership_entity_secondary_member} WHERE mid = :mid ORDER BY weight', array(
        ':mid' => $membership->mid,
      ));
      foreach ($secondary_members as $member) {
        $membership->secondary_members[$member->weight] = $member->uid;
      }
    }
    return $memberships;
  }

  /**
   * Load a single membership by member id.
   *
   * @param string $member_id
   *   The unique membership member id.
   *
   * @return MembershipEntity
   *   The membership object identified by member id.
   */
  public function loadByMemberID($member_id) {
    return reset($this->load(FALSE, array('member_id' => $member_id)));
  }

  /**
   * Load all memberships for a given user.
   *
   * @param object|int $account
   *   A user account object or uid.
   * @param string $bundle
   *   The membership bundle to load.
   *
   * @return MembershipEntity[]
   *   An array of all memberships for the given user account, keyed by
   *   bundle. Or a single membership object if $bundle is provided.
   */
  public function loadByUser($account, $bundle = NULL) {
    // Support uid or entire user object.
    $uid = is_object($account) ? $account->uid : $account;
    $memberships = $this->load(FALSE, array('uid' => $uid));

    if (empty($memberships)) {
      // Early exist if no memberships found.
      return array();
    }

    $bundles = array();
    foreach ($memberships as $membership) {
      $bundles[] = $membership->type;
    }
    $return = array_combine($bundles, $memberships);
    return !empty($bundle) ? $return[$bundle] : $return;
  }

  /**
   * Overrides EntityAPIController::save().
   */
  public function save($membership, DatabaseTransaction $transaction = NULL) {
    $transaction = isset($transaction) ? $transaction : db_transaction();
    $data = membership_entity_get_bundle_settings($membership->type);

    try {
      $roles = array();

      // Add or remove old roles depending on membership status.
      $roles[$membership->uid] = array(
        'rid' => $data['primary_role'],
        'op' => ($membership->status == MEMBERSHIP_ENTITY_ACTIVE) ? 'add' : 'remove',
      );
      foreach ($membership->secondary_members as $uid) {
        $roles[$uid] = array(
          'rid' => $data['secondary_role'],
          'op' => ($membership->status == MEMBERSHIP_ENTITY_ACTIVE) ? 'add' : 'remove',
        );
      }

      // Remove old roles.
      if (!empty($membership->mid)) {
        $params = array(':mid' => $membership->mid);
        $original_uid = db_query('SELECT uid FROM {membership_entity} WHERE mid = :mid', $params)->fetchField();
        if ($membership->uid != $original_uid) {
          $roles[$original_uid] = array(
            'rid' => $data['primary_role'],
            'op' => 'remove',
          );
        }

        $original_secondary = array_keys(db_query('SELECT uid FROM {membership_entity_secondary_member} WHERE mid = :mid', $params)->fetchAllAssoc('uid'));
        foreach (array_diff($original_secondary, $membership->secondary_members) as $uid) {
          $roles[$uid] = array(
            'rid' => $data['secondary_role'],
            'op' => 'remove',
          );
        }
      }
      _membership_entity_update_roles($roles);
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('membership_entity', $e);
      throw $e;
    }

    // Save the membership.
    $status = parent::save($membership, $transaction);

    try {
      // Update secondary members.
      db_delete('membership_entity_secondary_member')->condition('mid', $membership->mid)->execute();
      if (!empty($membership->secondary_members)) {
        $query = db_insert('membership_entity_secondary_member')
          ->fields(array('mid', 'uid', 'weight'));
        foreach ($membership->secondary_members as $weight => $uid) {
          $query->values(array(
            'mid' => $membership->mid,
            'uid' => $uid,
            'weight' => $weight,
          ));
        }
        $query->execute();
      }
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('membership_entity', $e);
      throw $e;
    }

    return $status;
  }

  /**
   * Overrides EntityAPIController::delete().
   */
  public function delete($mids, DatabaseTransaction $transaction = NULL) {
    $memberships = $mids ? $this->load($mids) : FALSE;
    if (!$memberships) {
      // Early exit if no memberships were loaded.
      return;
    }

    try {
      // Remove roles.
      $roles = array();
      foreach ($memberships as $membership) {
        $bundle_settings = membership_entity_get_bundle_settings($membership->type);
        $roles[$membership->uid] = array(
          'rid' => $bundle_settings['primary_role'],
          'op' => 'remove',
        );
        foreach ($membership->secondary_members as $uid) {
          $roles[$uid] = array(
            'rid' => $bundle_settings['secondary_role'],
            'op' => 'remove',
          );
        }
      }
      _membership_entity_update_roles($roles);

      // Delete secondary members.
      db_delete('membership_entity_secondary_member')
        ->condition('mid', $mids, 'IN')
        ->execute();
    }
    catch (Exception $e) {
      if (isset($transaction)) {
        $transaction->rollback();
      }
      watchdog_exception($this->entityType, $e);
      throw $e;
    }

    // Finish deleting the memberships;
    parent::delete($mids, $transaction);
  }
}
