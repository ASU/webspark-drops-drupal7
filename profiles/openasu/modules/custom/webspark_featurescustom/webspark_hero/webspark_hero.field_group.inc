<?php
/**
 * @file
 * webspark_hero.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function webspark_hero_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_webspark_hero_buttons|fieldable_panels_pane|hero|form';
  $field_group->group_name = 'group_webspark_hero_buttons';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'hero';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Recommended buttons',
    'weight' => '3',
    'children' => array(
      0 => 'field_webspark_hero_gradbtn',
      1 => 'field_webspark_hero_primarybtn',
      2 => 'field_webspark_hero_ugradbtn',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Recommended buttons',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'webspark-hero-buttons field-group-fieldset',
        'description' => '<ul class="help-text">
<li class="help-title">ASU Web Standard Buttons</li>
<li><strong>Recommended:</strong>   Add exploring undergraduate and graduate degree program buttons as the Calls to Action.</li>
<li><strong>Alternative:</strong>  In place of degree buttons, a single call to action can be use to support the content, driving the user the single most important item of the message.</li>
</ul>',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_webspark_hero_buttons|fieldable_panels_pane|hero|form'] = $field_group;

  return $export;
}
