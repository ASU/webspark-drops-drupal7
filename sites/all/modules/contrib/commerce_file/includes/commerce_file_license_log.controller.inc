<?php

/**
 * @file
 * The controller for the Commerce File License Log entity containing the CRUD operations.
 */

class CommerceFileLicenseLogEntityController extends EntityAPIController {
  /**
   * Implements EntityAPIControllerInterface::create().
   */
  public function create(array $values = array()) {
    // merge in defaults
    $values += array(
      'timestamp' => REQUEST_TIME,
      'hostname' => ip_address(),
      'is_new' => empty($values[$this->idKey]),
    );
    return parent::create($values);
  }

  /**
   * Implements EntityAPIControllerInterface::save()
   *
   * @param $entity
   *   The full entity object to save.
   * @param $transaction
   *   Optionally a DatabaseTransaction object to use. Allows overrides to pass
   *   in their transaction object.
   *
   * @return
   *   The saved entity object.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $transaction = isset($transaction) ? $transaction : db_transaction();

    // determine is_new
    $is_new = TRUE;
    if (!empty($entity->{$this->idKey})) {
      // if have an id, always update
      unset($entity->is_new);
      $is_new = FALSE;
    }
    elseif (isset($entity->is_new)) {
      // let entity tell us if we're new
      $is_new = $entity->is_new;
    }

    try {
      // set properties for new entities
      if ($is_new) {
        $entity->timestamp = REQUEST_TIME;
      }

      // clone for save so that we dont alter entity object to the serialized arrays
      $clone = clone($entity);
      $return = parent::save($clone, $transaction);

      // alter actual entity after successful save
      if ($return) {
        unset($entity->is_new);
        unset($entity->original);

        // add id
        if ($is_new) {
          $entity->{$this->idKey} = $clone->{$this->idKey};
        }
      }

      return $return;
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception($this->entityType, $e);
      throw $e;
    }
  }

  /**
   * Access callback
   */
  public function access($op = 'view', $entity = NULL, $account = NULL) {
    return entity_access($op, $this->entityType, $entity, $account);
  }
}
