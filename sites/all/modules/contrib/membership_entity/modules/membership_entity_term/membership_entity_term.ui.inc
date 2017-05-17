<?php

/**
 * @file
 * Contains the MembershipEntityTermUIController.
 */

/**
 * Membership term UI controller.
 */
class MembershipEntityTermUIController extends EntityDefaultUIController {
  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage membership terms and fields.';
    return $items;
  }
}
