<?php

/**
 * @file
 * Provides entity views integration.
 */

/**
 * Provides views integration for memberships.
 */
class MembershipEntityViewsController extends EntityDefaultViewsController {
  /**
   * Overrides EntityDefaultViewsController::views_data().
   */
  public function views_data() {
    $info = parent::views_data();
    $data = &$info['membership_entity'];

    $data['primary_member']['title'] = t('Primary member');
    $data['primary_member']['relationship']['label'] = t('Primary member');
    $data['primary_member']['field'] = array(
      'type' => 'user',
      'handler' => 'views_handler_field_membership_primary_member',
    );

    $data['secondary_members'] = array(
      'title' => t('Secondary members'),
      'help' => t('Secondary members that belong to the membership.'),
      'field' => array(
        'handler' => 'views_handler_field_membership_secondary_member',
      ),
    );

    $data['url'] = array(
      'title' => t('Link'),
      'help' => t('A link to view the membership.'),
      'field' => array(
        'op' => 'view',
        'handler' => 'views_handler_field_membership_link',
      ),
    );

    $data['edit'] = array(
      'title' => t('Edit'),
      'help' => t('A link to edit the membership.'),
      'field' => array(
        'op' => 'edit',
        'handler' => 'views_handler_field_membership_link',
      ),
    );

    $data['delete'] = array(
      'title' => t('Delete'),
      'help' => t('A link to delete the membership.'),
      'field' => array(
        'op' => 'delete',
        'handler' => 'views_handler_field_membership_link',
      ),
    );

    $info['membership_entity_secondary_member'] = array(
      'table' => array(
        'group' => t('Secondary members'),
        'join' => array(
          'membership_entity' => array(
            'left_field' => 'mid',
            'field' => 'mid',
          ),
        ),
      ),
    );

    $info['membership_entity_secondary_member']['uid'] = array(
      'title' => t('User'),
      'help' => t('Secondary members that belong to the membership.'),
      'relationship' => array(
        'label' => t('Secondary member'),
        'handler' => 'views_handler_relationship',
        'base' => 'users',
        'base field' => 'uid',
        'relationship field' => 'uid',
      ),
    );

    $info['membership_entity_secondary_member']['weight'] = array(
      'title' => t('Weight'),
      'help' => t('The secondary member weight field.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );

    $user = &$info['users'];
    $user['membership_entity']['title'] = t('Primary membership');
    $user['membership_entity']['relationship']['label'] = t('Primary membership');

    return $info;
  }
}
