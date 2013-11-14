<?php
/**
 * @file
 * asu_eadvisor_degree_feed_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function asu_eadvisor_degree_feed_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_asu_eadvisor_degree';
  $strongarm->value = 'edit-submission';
  $export['additional_settings__active_tab_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_asu_eadvisor_degree_feed';
  $strongarm->value = 'edit-menu';
  $export['additional_settings__active_tab_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_asu_eadvisor_degree';
  $strongarm->value = 0;
  $export['comment_anonymous_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_asu_eadvisor_degree_feed';
  $strongarm->value = 0;
  $export['comment_anonymous_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_asu_eadvisor_degree';
  $strongarm->value = '1';
  $export['comment_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_asu_eadvisor_degree_feed';
  $strongarm->value = '1';
  $export['comment_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_asu_eadvisor_degree';
  $strongarm->value = 1;
  $export['comment_default_mode_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_asu_eadvisor_degree_feed';
  $strongarm->value = 1;
  $export['comment_default_mode_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_asu_eadvisor_degree';
  $strongarm->value = '50';
  $export['comment_default_per_page_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_asu_eadvisor_degree_feed';
  $strongarm->value = '50';
  $export['comment_default_per_page_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_asu_eadvisor_degree';
  $strongarm->value = 1;
  $export['comment_form_location_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_asu_eadvisor_degree_feed';
  $strongarm->value = 1;
  $export['comment_form_location_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_asu_eadvisor_degree';
  $strongarm->value = '1';
  $export['comment_preview_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_asu_eadvisor_degree_feed';
  $strongarm->value = '1';
  $export['comment_preview_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_asu_eadvisor_degree';
  $strongarm->value = 1;
  $export['comment_subject_field_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_asu_eadvisor_degree_feed';
  $strongarm->value = 1;
  $export['comment_subject_field_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_asu_eadvisor_degree';
  $strongarm->value = array();
  $export['menu_options_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_asu_eadvisor_degree_feed';
  $strongarm->value = array();
  $export['menu_options_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_asu_eadvisor_degree';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_asu_eadvisor_degree_feed';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_asu_eadvisor_degree';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_asu_eadvisor_degree_feed';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_asu_eadvisor_degree';
  $strongarm->value = '1';
  $export['node_preview_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_asu_eadvisor_degree_feed';
  $strongarm->value = '1';
  $export['node_preview_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_asu_eadvisor_degree';
  $strongarm->value = 0;
  $export['node_submitted_asu_eadvisor_degree'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_asu_eadvisor_degree_feed';
  $strongarm->value = 1;
  $export['node_submitted_asu_eadvisor_degree_feed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_node_view_disabled';
  $strongarm->value = FALSE;
  $export['page_manager_node_view_disabled'] = $strongarm;

  return $export;
}
