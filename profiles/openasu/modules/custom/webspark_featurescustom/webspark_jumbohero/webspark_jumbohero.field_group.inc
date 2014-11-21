<?php
/**
 * @file
 * webspark_jumbohero.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function webspark_jumbohero_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_webspark_jumbohero_buttons|fieldable_panels_pane|jumbohero|form';
  $field_group->group_name = 'group_webspark_jumbohero_buttons';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'jumbohero';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Recommended buttons',
    'weight' => '3',
    'children' => array(
      0 => 'field_webspark_hero_ugradbtn',
      1 => 'field_webspark_hero_gradbtn',
      2 => 'field_webspark_hero_primarybtn',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Recommended buttons',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-webspark-jumbohero-buttons field-group-fieldset',
        'description' => '<strong>Recommended:</strong>   Add exploring undergraduate and graduate degree program buttons as the Calls to Action.<br><br>
<strong>Alternative:</strong>  In place of degree buttons, a single call to action can be use to support the content, driving the user the single most important item of the message.',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_webspark_jumbohero_buttons|fieldable_panels_pane|jumbohero|form'] = $field_group;

  return $export;
}
