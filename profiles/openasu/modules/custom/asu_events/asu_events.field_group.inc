<?php
/**
 * @file
 * asu_events.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function asu_events_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_asuevents_artist_info|node|asu_event|full';
  $field_group->group_name = 'group_asuevents_artist_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_event';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Artist information',
    'weight' => '15',
    'children' => array(
      0 => 'field_asuevent_artists',
      1 => 'field_asuevent_closing_recep',
      2 => 'field_asuevent_curator',
      3 => 'field_asuevent_opening_recep',
      4 => 'field_asuevent_past_exhibitions',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_asuevents_artist_info|node|asu_event|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_asuevents_info|node|asu_event|full';
  $field_group->group_name = 'group_asuevents_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_event';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'For more information:',
    'weight' => '14',
    'children' => array(
      0 => 'field_asuevent_contact_name',
      1 => 'field_asuevent_email_view',
      2 => 'field_asuevent_more_info',
      3 => 'field_asuevent_phone',
      4 => 'field_asuevent_registration_url',
      5 => 'field_asuevent_rsvp_url',
      6 => 'field_asuevent_ticketing_url',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_asuevents_info|node|asu_event|full'] = $field_group;

  return $export;
}
