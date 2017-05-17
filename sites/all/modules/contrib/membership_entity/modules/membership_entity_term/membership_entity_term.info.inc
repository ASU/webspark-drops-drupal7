<?php

/**
 * @file
 * Provides entity metadata integration.
 */

/**
 * Provides metadata for membership terms.
 */
class MembershipEntityTermMetadataController extends EntityDefaultMetadataController {
  /**
   * Overrides EntityDefaultMetadataController::entityPropertyInfo().
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    // Remove unnessesary fields.
    unset($properties['url']);
    unset($properties['membership_entity_type']);

    unset($properties['mid']);
    $properties['membership'] = array(
      'label' => t('Membership'),
      'type' => 'membership_entity',
      'description' => t('The membership for this term.'),
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_setter_method',
      'setter permission' => 'administer memberships',
      'required' => TRUE,
      'schema field' => 'mid',
    );

    $properties['term'] = array(
      'label' => t('Term length'),
      'description' => t('The membership term length.'),
    ) + $properties['term'];

    $properties['status'] = array(
      'label' => t('Term Status'),
      'description' => t('The membership term status.'),
      'options list' => 'membership_entity_get_status_list',
      'setter callback' => 'entity_property_verbatim_set',
    ) + $properties['status'];

    $properties['start'] = array(
      'type' => 'date',
      'label' => t('Start date'),
      'description' => t('The date the membership term begins.'),
      'required' => TRUE,
      'schema field' => 'start',
    );

    $properties['end'] = array(
      'type' => 'date',
      'label' => t('End date'),
      'description' => t('The date membership term ends.'),
      'required' => TRUE,
      'schema field' => 'end',
    );

    $properties['current'] = array(
      'type' => 'boolean',
      'label' => t('Current'),
      'description' => t('A boolean indicating whether this is the current term.'),
      'getter callback' => 'membership_entity_term_get_properties',
      'computed' => TRUE,
      'entity views field' => TRUE,
    );

    return $info;
  }
}
