<?php

/**
 * @file
 * ws2_banners.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ws2_banners_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_banner_text|fieldable_panels_pane|banners_ws2|default';
  $field_group->group_name = 'group_banner_text';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'banners_ws2';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '0',
    'children' => array(
      0 => 'field_banner_body',
      1 => 'field_banner_title_int',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'col-sm-12 col-lg-6 col-md-6',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_banner_text|fieldable_panels_pane|banners_ws2|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_banner_text|fieldable_panels_pane|banners_ws2|form';
  $field_group->group_name = 'group_banner_text';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'banners_ws2';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Banner text',
    'weight' => '2',
    'children' => array(
      0 => 'field_banner_body',
      1 => 'field_banner_title_int',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_banner_text|fieldable_panels_pane|banners_ws2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_buttons|fieldable_panels_pane|banners_ws2|default';
  $field_group->group_name = 'group_buttons';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'banners_ws2';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '1',
    'children' => array(
      0 => 'field_ws2_button',
      1 => 'field_ws2_button_2',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'col-sm-12 col-lg-5 col-md-5',
        'element' => 'div',
        'show_label' => '0',
        'label_element' => 'div',
        'attributes' => '',
      ),
    ),
  );
  $field_groups['group_buttons|fieldable_panels_pane|banners_ws2|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_buttons|fieldable_panels_pane|banners_ws2|form';
  $field_group->group_name = 'group_buttons';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'banners_ws2';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Buttons',
    'weight' => '3',
    'children' => array(
      0 => 'field_ws2_button',
      1 => 'field_ws2_button_2',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Buttons',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-buttons field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_buttons|fieldable_panels_pane|banners_ws2|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Banner text');
  t('Buttons');

  return $field_groups;
}
