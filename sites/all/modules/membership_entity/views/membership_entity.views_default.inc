<?php

/**
 * @file
 * Export of default views for memberships.
 */

/**
 * Implements hook_views_default_views().
 */
function membership_entity_views_default_views() {
  // Check for some helper modules.
  $vbo = module_exists('views_bulk_operations');
  $types = module_exists('membership_entity_type');
  $terms = module_exists('membership_entity_term');

  // Create the view.
  $view = new view();
  $view->name = 'membership_entity_memberships';
  $view->description = t('Display a list of all memberships on the site.');
  $view->tag = 'membership_entity';
  $view->base_table = 'membership_entity';
  $view->human_name = t('Administration: Memberships');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE;

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Memberships';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer memberships';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array();
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  $handler->display->display_options['style_options']['info'] = array();
  if ($vbo) {
    $handler->display->display_options['style_options']['columns']['views_bulk_operations'] = 'views_bulk_operations';
    $handler->display->display_options['style_options']['info'] += array(
      'views_bulk_operations' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
    );
  }
  $handler->display->display_options['style_options']['columns'] += array(
    'member_id' => 'member_id',
    'primary_member' => 'primary_member',
  );
  $handler->display->display_options['style_options']['info'] += array(
    'member_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'primary_member' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  if ($types) {
    $handler->display->display_options['style_options']['columns']['type'] = 'type';
    $handler->display->display_options['style_options']['info'] += array(
      'type' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
    );
  }
  $handler->display->display_options['style_options']['columns']['status'] = 'status';
  $handler->display->display_options['style_options']['info'] += array(
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  if ($terms) {
    $handler->display->display_options['style_options']['columns'] += array(
      'start' => 'start',
      'end' => 'end',
    );
    $handler->display->display_options['style_options']['info'] += array(
      'start' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
      'end' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
    );
  }
  else {
    $handler->display->display_options['style_options']['columns']['created'] = 'created';
    $handler->display->display_options['style_options']['info'] += array(
      'created' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
    );
  }
  $handler->display->display_options['style_options']['columns'] += array(
    'url' => 'url',
    'edit' => 'url',
  );
  $handler->display->display_options['style_options']['info'] += array(
    'url' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'edit' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  if ($terms) {
    $handler->display->display_options['style_options']['columns']['renew'] = 'url';
    $handler->display->display_options['style_options']['info'] += array(
      'renew' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
      ),
    );
  }
  $handler->display->display_options['style_options']['columns']['delete'] = 'url';
  $handler->display->display_options['style_options']['info'] += array(
    'delete' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['default'] = ($terms) ? 'start' : 'created';

  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = t('There are no memberships to display.');
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';

  if ($terms) {
    /* Relationship: Last Term */
    $handler->display->display_options['relationships']['membership_entity_term_representative']['id'] = 'membership_entity_term_representative';
    $handler->display->display_options['relationships']['membership_entity_term_representative']['table'] = 'membership_entity';
    $handler->display->display_options['relationships']['membership_entity_term_representative']['field'] = 'membership_entity_term_representative';
    $handler->display->display_options['relationships']['membership_entity_term_representative']['ui_name'] = 'Last Term';
    $handler->display->display_options['relationships']['membership_entity_term_representative']['label'] = 'Last term';
    $handler->display->display_options['relationships']['membership_entity_term_representative']['subquery_sort'] = 'membership_entity_term.end';
    $handler->display->display_options['relationships']['membership_entity_term_representative']['subquery_view'] = '';
    $handler->display->display_options['relationships']['membership_entity_term_representative']['subquery_namespace'] = 'last';
    $handler->display->display_options['relationships']['membership_entity_term_representative']['subquery_status'] = array(
      1 => '1',
      -1 => '-1',
      2 => 0,
      3 => 0,
    );
    /* Relationship: First Term */
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['id'] = 'membership_entity_term_representative_1';
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['table'] = 'membership_entity';
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['field'] = 'membership_entity_term_representative';
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['ui_name'] = 'First Term';
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['label'] = 'First Term';
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['required'] = TRUE;
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['subquery_sort'] = 'membership_entity_term.start';
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['subquery_order'] = 'ASC';
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['subquery_view'] = '';
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['subquery_namespace'] = 'first';
    $handler->display->display_options['relationships']['membership_entity_term_representative_1']['subquery_status'] = array(
      1 => '1',
      3 => '3',
      -1 => '-1',
      2 => 0,
    );
  }

  if ($vbo) {
    /* Field: Bulk operations: Membership */
    $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'membership_entity';
    $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
    $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
      'action::membership_entity_cancel_action' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::views_bulk_operations_delete_item' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => 'Delete membership',
      ),
      'action::membership_entity_pathauto_update_action' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
    );
  }

  /* Field: Membership: Internal id */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'membership_entity';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['label'] = '';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['mid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mid']['separator'] = '';

  /* Field: Membership: Member id */
  $handler->display->display_options['fields']['member_id']['id'] = 'member_id';
  $handler->display->display_options['fields']['member_id']['table'] = 'membership_entity';
  $handler->display->display_options['fields']['member_id']['field'] = 'member_id';
  $handler->display->display_options['fields']['member_id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['member_id']['alter']['path'] = 'membership/[mid]';
  $handler->display->display_options['fields']['member_id']['alter']['alt'] = 'View membership [member_id]';

  /* Field: Membership: Primary member */
  $handler->display->display_options['fields']['primary_member']['id'] = 'primary_member';
  $handler->display->display_options['fields']['primary_member']['table'] = 'membership_entity';
  $handler->display->display_options['fields']['primary_member']['field'] = 'primary_member';
  $handler->display->display_options['fields']['primary_member']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['primary_member']['view_mode'] = 'full';
  $handler->display->display_options['fields']['primary_member']['bypass_access'] = 1;

  if ($types) {
    /* Field: Membership: Type */
    $handler->display->display_options['fields']['type']['id'] = 'type';
    $handler->display->display_options['fields']['type']['table'] = 'membership_entity';
    $handler->display->display_options['fields']['type']['field'] = 'type';
  }

  /* Field: Membership: Membership status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'membership_entity';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';

  if ($terms) {
    /* Field: Membership term: Start date */
    $handler->display->display_options['fields']['start']['id'] = 'start';
    $handler->display->display_options['fields']['start']['table'] = 'membership_entity_term';
    $handler->display->display_options['fields']['start']['field'] = 'start';
    $handler->display->display_options['fields']['start']['relationship'] = 'membership_entity_term_representative_1';
    $handler->display->display_options['fields']['start']['label'] = 'Join date';
    $handler->display->display_options['fields']['start']['date_format'] = 'short';
    /* Field: Membership term: End date */
    $handler->display->display_options['fields']['end']['id'] = 'end';
    $handler->display->display_options['fields']['end']['table'] = 'membership_entity_term';
    $handler->display->display_options['fields']['end']['field'] = 'end';
    $handler->display->display_options['fields']['end']['relationship'] = 'membership_entity_term_representative';
    $handler->display->display_options['fields']['end']['label'] = 'Expiration date';
    $handler->display->display_options['fields']['end']['date_format'] = 'short';
  }
  else {
    /* Field: Membership: Date created */
    $handler->display->display_options['fields']['created']['id'] = 'created';
    $handler->display->display_options['fields']['created']['table'] = 'membership_entity';
    $handler->display->display_options['fields']['created']['field'] = 'created';
    $handler->display->display_options['fields']['created']['label'] = 'Created';
    $handler->display->display_options['fields']['created']['date_format'] = 'short';
  }

  /* Field: Membership: Link */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'membership_entity';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['label'] = 'Operations';
  /* Field: Membership: Edit */
  $handler->display->display_options['fields']['edit']['id'] = 'edit';
  $handler->display->display_options['fields']['edit']['table'] = 'membership_entity';
  $handler->display->display_options['fields']['edit']['field'] = 'edit';

  if ($terms) {
    /* Field: Membership: Renew */
    $handler->display->display_options['fields']['renew']['id'] = 'renew';
    $handler->display->display_options['fields']['renew']['table'] = 'membership_entity';
    $handler->display->display_options['fields']['renew']['field'] = 'renew';
  }

  /* Field: Membership: Delete */
  $handler->display->display_options['fields']['delete']['id'] = 'delete';
  $handler->display->display_options['fields']['delete']['table'] = 'membership_entity';
  $handler->display->display_options['fields']['delete']['field'] = 'delete';

  /* Sort criterion: Membership: Member id */
  $handler->display->display_options['sorts']['member_id']['id'] = 'member_id';
  $handler->display->display_options['sorts']['member_id']['table'] = 'membership_entity';
  $handler->display->display_options['sorts']['member_id']['field'] = 'member_id';

  /* Filter criterion: Membership: Member id */
  $handler->display->display_options['filters']['member_id']['id'] = 'member_id';
  $handler->display->display_options['filters']['member_id']['table'] = 'membership_entity';
  $handler->display->display_options['filters']['member_id']['field'] = 'member_id';
  $handler->display->display_options['filters']['member_id']['operator'] = 'contains';
  $handler->display->display_options['filters']['member_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['member_id']['expose']['operator_id'] = 'member_id_op';
  $handler->display->display_options['filters']['member_id']['expose']['label'] = 'Member ID';
  $handler->display->display_options['filters']['member_id']['expose']['operator'] = 'member_id_op';
  $handler->display->display_options['filters']['member_id']['expose']['identifier'] = 'member_id';
  $handler->display->display_options['filters']['member_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Filter criterion: Membership: Membership status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'membership_entity';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  if ($types) {
    /* Filter criterion: Membership: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'membership_entity';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['exposed'] = TRUE;
    $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
    $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
    $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
    $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
    $handler->display->display_options['filters']['type']['expose']['multiple'] = TRUE;
    $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
      2 => '2',
      1 => 0,
      3 => 0,
      4 => 0,
      5 => 0,
    );
  }

  /* Display: Admin Page */
  $handler = $view->new_display('page', 'Admin Page', 'admin');
  $handler->display->display_options['display_description'] = t('A list of membership for administrators.');
  $handler->display->display_options['path'] = 'admin/memberships/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['description'] = t('A list of all memberships');
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Memberships';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  $views[$view->name] = $view;
  return $views;
}
