<?php
/**
 * File that creates configurable panel for events listing page.
 */

// Creates a plugin for panels, which creates a new panel.
$plugin = array(
  'single' => TRUE,
  'title' => t('ASU Search Events Listing'),
  'description' => t('Shows ASU Events with configuration options.'),
  'category' => t('ASU Events'),
  'edit form' => 'asu_events_asu_events_search_listing_edit_form',
  'render callback' => 'asu_events_asu_events_search_listing_render',
  'admin info' => 'asu_events_asu_events_search_listing_admin_info',
  'defaults' => array(
    'asu_events_block_display_event_type' => 'exhibit',
    'asu_events_search_listing_display_type' => 'full',
    'asu_events_search_listing_featured' => '',
    //'tweets_to_show' => 5,
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function asu_events_asu_events_search_listing_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Display format: <em>@display</em>.', array(
      '@display' => $conf['asu_events_search_listing_display_type'],
    ));
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function asu_events_asu_events_search_listing_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['asu_events_search_listing_display_type'] = array(
    '#type' => 'select',
    '#title' => t('Select type of Display'),
    '#default_value' => $conf['asu_events_listing_display_type'],
    '#options' => array(
      'full' => 'Full',
      'compact' => 'Compact',
      'calendar' => 'Calendar'
    ),
  );

  $form['asu_events_search_breadcrumbs'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Display Breadcrumbs?'),
    '#default_value' => $conf['asu_events_search_breadcrumbs'],
    '#options' => array(
      '0' => 'No',
      '1' => 'Yes',
    ),
  );

  $form['asu_events_search_listing_featured'] = array(
    '#type' => 'textfield',
    '#title' => 'Featured ASU Event Item',
    '#default_value' => $conf['asu_events_listing_featured'],
    '#description' => 'Start typing title of ASU news, and use autocomplete feature.',
    '#autocomplete_path' => 'events/autocomplete',
    '#states' => array(
      // Hide the settings when the cancel notify checkbox is disabled.
      'invisible' => array(
       ':input[name="asu_events_listing_display_type"]' => array('value' => 'compact'),
      ),
    ),
  );

  $form['asu_events_block_display_event_type'] = array(
    '#type' => 'select',
    '#title' => t('Select type of Event to Display'),
    '#default_value' => $conf['asu_events_block_display_event_type'],
    '#options' => array(
      'exhibit' => 'Exhibit',
      'Other' => 'Other',
    ),
  );

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function asu_events_asu_events_search_listing_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function asu_events_asu_events_search_listing_render($subtype, $conf, $panel_args, $context = NULL) {

  $block = new stdClass();
  $nodes_render = array();
  $block->title = '';
  $breadcrumbs = block_load('easy_breadcrumb', 'easy_breadcrumb');
  $bc_render_array = _block_get_renderable_array(_block_render_blocks(array($breadcrumbs)));
  $bc_render_array['easy_breadcrumb_easy_breadcrumb']['easy_breadcrumb']['#prefix'] = '<div class="column container">';
  $bc_render_array['easy_breadcrumb_easy_breadcrumb']['easy_breadcrumb']['#suffix'] = '</div>';
  $bc_render_array['easy_breadcrumb_easy_breadcrumb']['easy_breadcrumb']['#breadcrumb'][1]['content'] = 'Events';

  $module_path = drupal_get_path('module', 'asu_events');
  drupal_add_css($module_path . '/theme/css/asumod-events.css', array('group' => CSS_THEME, 'every_page' => TRUE));
  $upcoming_title = array(
    '#type' => 'markup',
    '#markup' => '<div class="upcoming-title">Upcoming Events</div>'
  );

  if (!empty($conf['asu_events_block_display_event_type']) && $conf['asu_events_block_display_event_type'] == 'exhibit') {
    $term = taxonomy_get_term_by_name('exhibit');
    $term = current($term);
    $field = array(
      'name' => 'field_asuevent_tax_type',
      'id' => 'tid',
      'value' => $term->tid,
      'op' => '='
    );
    $field_filters[] = $field;
  }

  if ($conf['asu_events_search_breadcrumbs']) {
    $block->content['breadcrumb'] = $bc_render_array;
  }
  if (!$conf['override_title']) {
    $block->content['upcoming_title'] = $upcoming_title;
  }
  //$nodes = _asu_events_get_search_asuevents_items(30, null, null, true);
  $server = search_api_server_load('database_server');
  $index = search_api_index_load('database_node_index');
  $query = new SearchApiQuery($index);
  $query->condition('status', '1', '=');
  $query->condition('type', 'asu_event', '=');
  $query->range(0, 10);

  if (!empty($conf['asu_events_block_display_event_type']) && $conf['asu_events_block_display_event_type'] == 'exhibit') {
    $term = taxonomy_get_term_by_name('exhibit');
    $term = current($term);
    $query->condition('field_asuevent_tax_type', $term->tid, '=');

    $upcoming_title = array(
      '#type' => 'markup',
      '#markup' => '<div class="upcoming-title">Exhibitions</div>'
    );
  }



  // $query->pager(10);
  $qp = drupal_get_query_parameters();

  if (isset($qp['keywords']) && !empty($qp['keywords'])) {
    $keywords = $qp['keywords'];
    $keywords = urldecode($keywords);
    $keywords = drupal_strip_dangerous_protocols($keywords);
    $keywords = check_plain($keywords);
    $query->keys($keywords);
    $query->fields(array('title','body:value'));
  }

  if (isset($qp['category']) && !empty($qp['category'])) {
    //field_asuevent_tax_category
    $category = $qp['category'];
    $category = urldecode($category);
    $category = drupal_strip_dangerous_protocols($category);
    $category = check_plain($category);
    $term = taxonomy_get_term_by_name($category, 'asu_events_category');
    $term = current($term);
    $query->condition('field_asuevent_tax_category', $term->tid, '=');
  }

  $srv= new SearchApiDbService($server);
  $result = $srv->search($query);
  if (!empty($result['results'])) {
    $nids = array_keys($result['results']);
    $nodes = node_load_multiple($nids);
    $nodes_render = node_view_multiple($nodes, 'events_list_page_teaser');

    $nodes_render = _asu_events_search_listing_group_nodes_by_day($nodes_render);
    $grouped_render = array();
    foreach($nodes_render as $date => $dates) {
      $date = str_replace('_', '-', $date);
      $date_formated = format_date(strtotime($date), 'custom', 'd l F');
      $month_1 = format_date(strtotime($date), 'custom', 'F');
      $day_1 = format_date(strtotime($date), 'custom', 'j');
      $week_day_1 = format_date(strtotime($date), 'custom', 'l');
      $time_1 = format_date(strtotime($date) + (7*HOUR), 'custom', 'g:i a');
      $grouped_nodes = array();
      $wrapper = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('nodes-date-wrapper'),
        ),
        'date_title' => array(
          '#type' => 'markup',
          '#markup' => '<div class="upcoming-title"><span>' . $day_1 . '</span> <span><span>' . $week_day_1 . '</span> <span>' . $month_1 . '</span></span></div>',
        ),
        'nodes' => $dates,
      );

      $grouped_render[] = $wrapper;
    }
    $block->content['event_items']['events'] = $grouped_render;

    $block->content['#attached']['js'][] = $module_path . '/theme/js/jquery.autopager-1.0.0.js';
    $block->content['#attached']['js'][] = $module_path . '/theme/js/throbber.js';
    $block->content['#attached']['js'][] = $module_path . '/theme/js/asu_events.load_more.js';
    $block->content['#attached']['js'][] = array(
      'data' => $module_path . '/theme/js/object-fit-polyfill.js',
      'type' => 'file',
      'weight' => 0,
      'scope' => 'footer',
    );
  }


  return $block;
}

/**
 * Adds a calendar to the current render block.
 * @param object $block       Render object that contains the block information.
 * @param array $event_items  Array of events.
 * @return object             Render object that contains the block info with attached calendar.
 */
// function _asu_events_listing_add_calendar(&$block, $event_items) {
//   $module_path = drupal_get_path('module', 'asu_events');
//   drupal_add_css(drupal_get_path('module', 'asu_events') . '/theme/js/fullcalendar/fullcalendar.min.css', array('group' => CSS_THEME, 'every_page' => TRUE));
//
//   $block->content['#attached']['js'][] = $module_path . '/theme/js/fullcalendar/lib/moment.min.js';
//   $block->content['#attached']['js'][] = $module_path . '/theme/js/fullcalendar/fullcalendar.min.js';
//   $block->content['#attached']['js'][] = $module_path . '/theme/js/asu_events.calendar.js';
//
//   $block->content['event_items']['calendar'] = array(
//     '#type' => 'markup',
//     '#markup' => '<div id="calendar"></div>',
//   );
//
//   $event_dates = '';
//   foreach($event_items as $key => $item) {
//     $wrapper =  entity_metadata_wrapper('node', $item);
//     $date_field = $wrapper->field_asuevent_very_start_date->value();
//     $title = $wrapper->title->value();
//     $url = drupal_lookup_path('alias',"node/" . $item->nid);
//     $event_dates .= '{"title": "' . check_plain($title) . '","start":"' . $date_field['value'] . '-07:00", "end":"' . $date_field['value2'] . '-07:00","url":"'. $url .'"},';
//   }
//
//   $event_dates = rtrim($event_dates,",");
//   //$event_dates = "{title: 'event1', 'start':'2016-07-11T09:00:00', 'end':'2016-07-11T11:00:00'}";
//   //$dates_json = drupal_json_encode($event_dates);
//   drupal_add_js(array('asu_events_dates' => $event_dates), 'setting');
//
//   return $block;
// }
