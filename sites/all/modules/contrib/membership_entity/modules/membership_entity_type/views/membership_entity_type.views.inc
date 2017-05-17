<?php

/**
 * @file
 * Defines the MembershipEntityTypeViews Controller class.
 */

/**
 * Membership entity type views controller class.
 */
class MembershipEntityTypeViewsController extends EntityDefaultViewsController {
  /**
   * Overrides EntityDefaultViewsController::views_data().
   */
  public function views_data() {
    $info = parent::views_data();
    $data = &$info['membership_entity_type'];

    $data['edit'] = array(
      'title' => t('Edit'),
      'help' => t('A link to edit the membership type.'),
      'field' => array(
        'op' => 'edit',
        'handler' => 'views_handler_field_membership_link',
      ),
    );

    $data['clone'] = array(
      'title' => t('Clone'),
      'help' => t('A link to clone the membership type.'),
      'field' => array(
        'op' => 'clone',
        'handler' => 'views_handler_field_membership_link',
      ),
    );

    $data['delete'] = array(
      'title' => t('Delete'),
      'help' => t('A link to delete the membership type.'),
      'field' => array(
        'op' => 'delete',
        'handler' => 'views_handler_field_membership_link',
      ),
    );

    $data['export'] = array(
      'title' => t('Export'),
      'help' => t('A link to export the membership type.'),
      'field' => array(
        'op' => 'export',
        'handler' => 'views_handler_field_membership_link',
      ),
    );

    return $info;
  }
}
