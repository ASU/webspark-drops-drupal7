<?php
/**
 * File that creates configurable panel for events listing page.
 */

// Creates a plugin for panels, which creates a new panel.
$plugin = array(
  'single' => TRUE,
  'title' => t('ASU Search Exhibitions Listing'),
  'description' => t('Shows ASU Exhibitions configuration options.'),
  'category' => t('ASU Events'),
  'edit form' => 'asu_events_asu_events_exhibits_search_listing_edit_form',
  'render callback' => 'asu_events_asu_events_exhibits_search_listing_render',
  'admin info' => 'asu_events_asu_events_exhibits_search_listing_admin_info',
  'defaults' => array(
    'asu_events_block_display_event_type' => 'exhibit',
    'asu_events_search_listing_display_type' => 'full',
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function asu_events_asu_events_exhibits_search_listing_admin_info($subtype, $conf, $contexts) {
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
function asu_events_asu_events_exhibits_search_listing_edit_form($form, &$form_state) {
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
function asu_events_asu_events_exhibits_search_listing_edit_form_submit($form, &$form_state) {
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
function asu_events_asu_events_exhibits_search_listing_render($subtype, $conf, $panel_args, $context = NULL) {
  drupal_add_css(drupal_get_path('module', 'asu_events') . '/theme/css/asumod-events.css', array('group' => CSS_THEME, 'every_page' => TRUE));
  $block = new stdClass();
  $nodes_render = array();
  $block->title = '';
  $breadcrumbs = block_load('easy_breadcrumb', 'easy_breadcrumb');
  $bc_render_array = _block_get_renderable_array(_block_render_blocks(array($breadcrumbs)));
  $bc_render_array['easy_breadcrumb_easy_breadcrumb']['easy_breadcrumb']['#prefix'] = '<div class="column container">';
  $bc_render_array['easy_breadcrumb_easy_breadcrumb']['easy_breadcrumb']['#suffix'] = '</div>';
  $bc_render_array['easy_breadcrumb_easy_breadcrumb']['easy_breadcrumb']['#breadcrumb'][1]['content'] = 'Events';

  $module_path = drupal_get_path('module', 'asu_events');
  $upcoming_title = array(
    '#type' => 'markup',
    '#markup' => '<div class="upcoming-title">Exhibitions</div>'
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
  $term = taxonomy_get_term_by_name('exhibit');
  $term = current($term);
  $query->condition('field_asuevent_tax_type', $term->tid, '=');

  // $query->pager(10);
  $qp = drupal_get_query_parameters();

  if (isset($qp['keywords']) && !empty($qp['keywords'])) {
    $keywords = $qp['keywords'];
    $keywords = urldecode($keywords);
	$keywords = preg_replace("/[^a-zA-Z 0-9]+/", " ", $keywords); // TKB added 9/7/17, strips out punctuation
    $keywords = drupal_strip_dangerous_protocols($keywords);
    $keywords = check_plain($keywords);
    $query->keys($keywords);
    $query->fields(array('title','body:value'));
  }

  if (isset($qp['filters']) && !empty($qp['filters'])) {
    //field_asuevent_tax_category
    $filters = $qp['filters'];
    $filters = urldecode($filters);
    $filters = json_decode($filters);
    foreach($filters as $key => $vocab) {
      switch($key) {
        case 'herberger_institute_units':
          $query->condition('field_herberger_institute_unit', $vocab, 'IN');
        break;
        case 'asu_events_event_price':
          $term_names = array();
          foreach($vocab as $tid) {
            $term = taxonomy_term_load($tid);
            $term_names[] = $term->name;
            //$query->condition('field_asuevent_price', $term->name, '=');
          }
          if (count($term_names) == 1) {
            $query->condition('field_asuevent_price', $term_names[0], '=');
          }
          else {
            $query->condition('field_asuevent_price', $term_names, 'IN');
          }
        break;
        //case 'location':
          //$term_names = array();
         // foreach($vocab as $tid) {
            //$term = taxonomy_term_load($tid);
            //$term_names[] = $term->name;
         // }
          //$query->condition('field_locations', $vocab, 'IN');
		  //$query->condition('field_asuevent_location', $vocab, 'IN');
       // break;
	   case 'location':
          $term_names = array();
          foreach($vocab as $tid) {
            $term = taxonomy_term_load($tid);
            $term_names[] = $term->name;
          }
          if (count($term_names) == 1) {
            $query->condition('field_asuevent_location', $term_names[0], '=');
          }
          else {
            $query->condition('field_asuevent_location', $term_names, 'IN');
          }
        break;
        case 'date_range':
          $date_set = true;
          switch($vocab[0]) {
            case 'today':
              $datetime = new DateTime('today');
              $query->condition('field_asuevent_very_start_date:value', $datetime->getTimestamp(), '>');
              $query->condition('field_asuevent_very_start_date:value', $datetime->getTimestamp() + 24*60*60, '<');
            break;
            case 'tomorrow':
              $datetime_tomorrow = new DateTime('tomorrow');
              $query->condition('field_asuevent_very_start_date:value', $datetime_tomorrow->getTimestamp(), '>');
              $query->condition('field_asuevent_very_start_date:value', $datetime_tomorrow->getTimestamp() + 24*60*60, '<');
            break;
            case 'this_weekend':
              $datetime_saturday = new DateTime('this saturday');
              $datetime_sunday = new DateTime('this sunday');
              $query->condition('field_asuevent_very_start_date:value', $datetime_saturday->getTimestamp(), '>');
              $query->condition('field_asuevent_very_start_date:value', $datetime_sunday->getTimestamp() + 24*60*60, '<');
            break;
            case 'this_month':
              $datetime_saturday = new DateTime('first day of this month');
              $datetime_sunday = new DateTime('last day of this month');
              $query->condition('field_asuevent_very_start_date:value', $datetime_saturday->getTimestamp(), '>=');
              $query->condition('field_asuevent_very_start_date:value', $datetime_sunday->getTimestamp() + 24*60*60, '<');
            break;
            case 'all_events':
              $query->condition('field_asuevent_very_start_date:value', strtotime(date('Y-m-d')), '>=');
            break;
          }
          //kpr($datetime->getTimestamp());
        //  kpr(strtotime('+1 day', $datetime->getTimestamp()));
        break;
        case '';
        break;
        default:
        break;
      }
    }

  }

  if (!$date_set) {
    $query->condition('field_asuevent_very_start_date:value', strtotime(date('Y-m-d')), '>=');
  }
  $query->sort('field_asuevent_very_start_date:value', 'ASC');

  $total_query = $query;
     
  $srv= new SearchApiDbService($server);
  $total_results = $srv->search($total_query);


  $items_per_page = 10;
  //add this to the variable array so we might output it in the template
  $block->content['items_per_page'] = $items_per_page;

  $current_page = 0;
  //what page you are on
  if (array_key_exists('current_search_page', $qp)) {
    $current_page =  $qp['current_search_page'];
    variable_set('current_search_page', $current_page);
  }


  global $solr_events_pager_page_array;
  $solr_events_pager_page_array = array($current_page);
  $offset = $current_page * 10;

  // total number of pages
  global $solr_events_pager_total;
  $solr_events_pager_total = array(ceil($total_results['result count'] / $items_per_page));

  $query->range($offset, 10);

  $result = $total_results;//$srv->search($query);

  if (!empty($result['results'])) {
    $nids = array_keys($result['results']);
    $nodes = node_load_multiple($nids);

    $additional_titles = array();
    if (isset($_POST['current_nids']) && !empty($_POST['current_nids'])) {
      $current_nids = $_POST['current_nids'];
      $current_nids = json_decode($current_nids);
      $current_nodes = node_load_multiple($current_nids);
      foreach($current_nodes as $node) {
        $additional_titles[] = $node->title;
      }
    }

    $nodes = _asu_events_filter_unique_title($nodes, $additional_titles);
    if (empty($nodes)) {
      $no_results_wrapper = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('no-results-wrapper'),
        ),
        'date_title' => array(
          '#type' => 'markup',
          '#markup' => '<span>No results found.</span>',
        ),
      );
      $block->content['no_results'] = $no_results_wrapper;
      $block->content['#attached']['js'][] = $module_path . '/theme/js/jquery.autopager-1.0.0.js';
      $block->content['#attached']['js'][] = $module_path . '/theme/js/throbber.js';
      $block->content['#attached']['js'][] = $module_path . '/theme/js/asu_solr_events.load_more.js';
      $block->content['#attached']['js'][] = array(
        'data' => $module_path . '/theme/js/object-fit-polyfill.js',
        'type' => 'file',
        'weight' => 0,
        'scope' => 'footer',
      );

      return $block;
    }
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
        // 'date_title' => array(
        //   '#type' => 'markup',
        //   '#markup' => '<div class="upcoming-title"><span>' . $day_1 . '</span> <span><span>' . $week_day_1 . '</span> <span>' . $month_1 . '</span></span></div>',
        // ),
        'nodes' => $dates,
      );

      $grouped_render[] = $wrapper;
    }
    $block->content['event_items']['events'][] = $grouped_render;
    $block->content['event_items']['events']['#prefix'] = '<div class="solr-items-wrapper">';
    $block->content['event_items']['events']['#suffix'] = '</div>';


    // global $pager_total;
    // $pager_settings = array(
    //   'pager_total' => $solr_events_pager_total,
    // );
    //
    // drupal_add_js(array('asu_events' => $pager_settings), 'setting');
    //
    // $block->content['pager'] = array('#theme' => 'solr_event_pager');
    //
    // $block->content['load_more'] = array(
    //   '#type' => 'link',
    //   '#title' => 'Load more exhibitions',
    //   '#href' => '#',
    //   '#attributes' => array(
    //     'class' => array('asu-solor-events-load-more-btn'),
    //   ),
    // );

    $block->content['#attached']['js'][] = $module_path . '/theme/js/jquery.autopager-1.0.0.js';
    $block->content['#attached']['js'][] = $module_path . '/theme/js/throbber.js';
    $block->content['#attached']['js'][] = $module_path . '/theme/js/asu_solr_events.load_more.js';
    $block->content['#attached']['js'][] = array(
      'data' => $module_path . '/theme/js/object-fit-polyfill.js',
      'type' => 'file',
      'weight' => 0,
      'scope' => 'footer',
    );
  }
  else {
    $no_results_wrapper = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('no-results-wrapper'),
      ),
      'date_title' => array(
        '#type' => 'markup',
        '#markup' => '<span>No results found.</span>',
      ),
    );
    $block->content['no_results'] = $no_results_wrapper;
    $block->content['#attached']['js'][] = $module_path . '/theme/js/jquery.autopager-1.0.0.js';
    $block->content['#attached']['js'][] = $module_path . '/theme/js/throbber.js';
    $block->content['#attached']['js'][] = $module_path . '/theme/js/asu_solr_events.load_more.js';
    $block->content['#attached']['js'][] = array(
      'data' => $module_path . '/theme/js/object-fit-polyfill.js',
      'type' => 'file',
      'weight' => 0,
      'scope' => 'footer',
    );

  }


  return $block;
}
