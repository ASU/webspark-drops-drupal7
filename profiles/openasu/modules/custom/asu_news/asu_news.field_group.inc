<?php
/**
 * @file
 * asu_news.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function asu_news_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contributor|node|asu_news|default';
  $field_group->group_name = 'group_contributor';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'asu_news';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contributor',
    'weight' => '3',
    'children' => array(
      0 => 'field_asunews_contri_affiliation',
      1 => 'field_asunews_contri_email',
      2 => 'field_asunews_contri_name',
      3 => 'field_asunews_contri_phone',
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
  $export['group_contributor|node|asu_news|default'] = $field_group;

  return $export;
}
