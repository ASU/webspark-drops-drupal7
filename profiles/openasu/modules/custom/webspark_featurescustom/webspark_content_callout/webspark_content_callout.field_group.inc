<?php
/**
 * @file
 * webspark_content_callout.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function webspark_content_callout_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_callout_opts|node|content_callout|form';
  $field_group->group_name = 'group_callout_opts';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'content_callout';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Optional media',
    'weight' => '4',
    'children' => array(
      0 => 'field_callout_image',
      1 => 'field_callout_video',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Optional media',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-callout-opts field-group-fieldset',
        'description' => 'Optionally, add either an image or a video (not both).',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_callout_opts|node|content_callout|form'] = $field_group;

  return $export;
}
