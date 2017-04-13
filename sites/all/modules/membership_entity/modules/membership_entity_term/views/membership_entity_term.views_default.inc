<?php

/**
 * @file
 * Export of default views for membership terms.
 */

/**
 * Implements hook_views_default_views().
 */
function membership_entity_term_views_default_views() {
  $view = new view();
  $view->name = 'membership_entity_terms';
  $view->description = t('Display a list of terms for a membership.');
  $view->tag = 'membership_entity';
  $view->base_table = 'membership_entity_term';
  $view->human_name = t('Membership Terms');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE;

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Membership Terms';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = '[current_1]';
  $handler->display->display_options['style_options']['columns'] = array(
    'current' => 'current',
    'term' => 'term',
    'modifiers' => 'term',
    'start' => 'start',
    'end' => 'end',
    'status' => 'status',
    'edit' => 'edit',
    'current_1' => 'current_1',
  );
  $handler->display->display_options['style_options']['default'] = 'start';
  $handler->display->display_options['style_options']['info'] = array(
    'current' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'term' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'modifiers' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'start' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'end' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 1,
    ),
    'current_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'There are no membership terms to display.';
  /* Field: Membership term: Current */
  $handler->display->display_options['fields']['current']['id'] = 'current';
  $handler->display->display_options['fields']['current']['table'] = 'views_entity_membership_entity_term';
  $handler->display->display_options['fields']['current']['field'] = 'current';
  $handler->display->display_options['fields']['current']['label'] = '';
  $handler->display->display_options['fields']['current']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['current']['type'] = 'current';
  $handler->display->display_options['fields']['current']['not'] = 0;
  $handler->display->display_options['fields']['current']['link_to_entity'] = 0;
  /* Field: Membership term: Term length */
  $handler->display->display_options['fields']['term']['id'] = 'term';
  $handler->display->display_options['fields']['term']['table'] = 'membership_entity_term';
  $handler->display->display_options['fields']['term']['field'] = 'term';
  /* Field: Membership term: Modifiers */
  $handler->display->display_options['fields']['modifiers']['id'] = 'modifiers';
  $handler->display->display_options['fields']['modifiers']['table'] = 'membership_entity_term';
  $handler->display->display_options['fields']['modifiers']['field'] = 'modifiers';
  $handler->display->display_options['fields']['modifiers']['label'] = '';
  $handler->display->display_options['fields']['modifiers']['element_label_colon'] = FALSE;
  /* Field: Membership term: Start date */
  $handler->display->display_options['fields']['start']['id'] = 'start';
  $handler->display->display_options['fields']['start']['table'] = 'membership_entity_term';
  $handler->display->display_options['fields']['start']['field'] = 'start';
  $handler->display->display_options['fields']['start']['date_format'] = 'short';
  /* Field: Membership term: End date */
  $handler->display->display_options['fields']['end']['id'] = 'end';
  $handler->display->display_options['fields']['end']['table'] = 'membership_entity_term';
  $handler->display->display_options['fields']['end']['field'] = 'end';
  $handler->display->display_options['fields']['end']['date_format'] = 'short';
  /* Field: Membership term: Term Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'membership_entity_term';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Membership term: Edit */
  $handler->display->display_options['fields']['edit']['id'] = 'edit';
  $handler->display->display_options['fields']['edit']['table'] = 'membership_entity_term';
  $handler->display->display_options['fields']['edit']['field'] = 'edit';
  $handler->display->display_options['fields']['edit']['label'] = 'Operations';
  /* Field: Row class (current) */
  $handler->display->display_options['fields']['current_1']['id'] = 'current_1';
  $handler->display->display_options['fields']['current_1']['table'] = 'views_entity_membership_entity_term';
  $handler->display->display_options['fields']['current_1']['field'] = 'current';
  $handler->display->display_options['fields']['current_1']['ui_name'] = 'Row class (current)';
  $handler->display->display_options['fields']['current_1']['label'] = '';
  $handler->display->display_options['fields']['current_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['current_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['current_1']['type'] = 'custom';
  $handler->display->display_options['fields']['current_1']['type_custom_true'] = 'current';
  $handler->display->display_options['fields']['current_1']['not'] = 0;
  $handler->display->display_options['fields']['current_1']['link_to_entity'] = 0;
  /* Sort criterion: Membership term: Start date */
  $handler->display->display_options['sorts']['start']['id'] = 'start';
  $handler->display->display_options['sorts']['start']['table'] = 'membership_entity_term';
  $handler->display->display_options['sorts']['start']['field'] = 'start';
  $handler->display->display_options['sorts']['start']['order'] = 'DESC';
  /* Contextual filter: Membership ID */
  $handler->display->display_options['arguments']['membership']['id'] = 'membership';
  $handler->display->display_options['arguments']['membership']['table'] = 'membership_entity_term';
  $handler->display->display_options['arguments']['membership']['field'] = 'membership';
  $handler->display->display_options['arguments']['membership']['ui_name'] = 'Membership ID';
  $handler->display->display_options['arguments']['membership']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['membership']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['membership']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['membership']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['membership']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['membership']['validate']['fail'] = 'ignore';

  /* Display: Term list */
  $handler = $view->new_display('block', 'Term list', 'term_list');
  $handler->display->display_options['display_description'] = 'A list of terms for a membership.';
  $handler->display->display_options['block_description'] = 'Membership Terms';

  $views[$view->name] = $view;
  return $views;
}
