<?php

/**
 * @file
 * Definition of views_handler_field_membership_primary_member.
 */

/**
 * Field handler to show the primary member from the membership.
 */
class views_handler_field_membership_primary_member extends entity_views_handler_field_entity {
  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['display']['#options'] = array(
      'label' => t('Show username'),
      'id' => t('Show user id'),
      'view' => t('Show complete user'),
    );

    $form['link_to_entity']['#title'] = t('Link to user');
    $form['link_to_entity']['#description'] = t('Link this field to the user.');

    $form['bypass_access']['#description'] = t('If enabled, access permissions for rendering the user are not checked.');
  }
}
