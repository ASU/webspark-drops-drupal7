<?php
$plugin = array(
  'single' => TRUE,
  'title' => t('ASU Events Exhibitions Block'),
  'description' => t('Shows ASU Events Exhibitions with configuration options.'),
  'category' => t('ASU Events'),
  'edit form' => 'asu_events_asu_events_exhibitions_block_edit_form',
  'render callback' => 'asu_events_asu_events_exhibitions_block_render',
  'admin info' => 'asu_events_asu_events_exhibitions_block_admin_info',
  'defaults' => array(
    'asu_events_exhibitions_block_start_date' => date("Y-m-d"),
    'asu_events_exhibitions_block_default_number' => 3,
    'asu_events_block_content_type' => '',
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function asu_events_asu_events_exhibitions_block_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Display format: <em>@@display</em>.', array(
      '@display' => $conf['asu_events_block_display_type'],
    ));
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function asu_events_asu_events_exhibitions_block_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['asu_events_exhibitions_block_start_date'] = array(
    '#type' => 'textfield',
    '#title' => 'Start Date',
    '#default_value' => $conf['asu_events_block_start_date'],
    '#description' => 'Show only asu event items that start after this date',
  );

  $form['asu_events_block_content_type'] = array(
    '#type' => 'select',
    '#title' => 'Content Type to Display',
    '#default_value' => $conf['asu_events_block_content_type'],
    '#description' => 'Start typing title of ASU content type, and use autocomplete feature.',
    "#options" => array(
      'asu_event' => t('ASU Event'),
      'asu_degree' => t('ASU Degree'),
    ),
    // '#states' => array(
    //   // Hide the settings when the cancel notify checkbox is disabled.
    //   'invisible' => array(
    //    ':input[name="asu_events_listing_display_type"]' => array('value' => 'compact'),
    //   ),
    // ),
  );

  $form['asu_events_exhibitions_block_default_number'] = array(
    '#type' => 'textfield',
    '#title' => 'Default Number to show',
    '#default_value' => $conf['asu_events_block_end_date'],
    '#description' => 'Show only this number of exhibitions by default',
  );

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function asu_events_asu_events_exhibitions_block_edit_form_submit($form, &$form_state) {
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
function asu_events_asu_events_exhibitions_block_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $nodes_render = array();
  $block->title = '';

  $module_path = drupal_get_path('module', 'asu_events');
  $upcoming_title = array(
    '#type' => 'markup',
    '#markup' => '<div class="upcoming-title">Current Exhibitions</div>'
  );

  $num_to_show = (empty($conf['asu_events_exhibitions_block_default_number'])) ? 3 : $conf['asu_events_exhibitions_block_default_number'];

  $show_type = (empty($conf['asu_events_block_content_type']))? 'asu_events' : $conf['asu_events_block_content_type'];
  switch ($show_type) {
    case 'asu_event':
      $nodes = _asu_events_get_asuevents_items(30, null, null, true, $num_to_show);
      $nodes_render = node_view_multiple($nodes, 'events_three_teaser');
      break;
    case 'asu_degree':
      $nodes = _asu_events_get_asudegrees_items(30, null, null, true, $num_to_show);
      $nodes_render = node_view_multiple($nodes, 'degrees_three_teaser');
      break;
    default:
      $nodes = _asu_events_get_asuevents_items(30, null, null, true, $num_to_show);
      $nodes_render = node_view_multiple($nodes, 'events_three_teaser');
  }


  $block->subject = '';
  if (!$conf['override_title']) {
    $block->content['upcoming_title'] = $upcoming_title;
  }
  $block->content['event_items'] = $nodes_render;
  $block->content['event_items']['#prefix'] = '<div class="asu-events-exhibitions-listing-wrapper sidebar-view">';
  $block->content['event_items']['#suffix'] = '</div>';
  $block->content['pager'] = array('#theme' => 'pager');
  $block->content['load_more'] = array(
    '#type' => 'link',
    '#title' => 'Load More',
    '#href' => '#',
    '#attributes' => array(
      'class' => array('asu-news-load-more-btn'),
    ),
  );

  $block->content['#attached']['js'][] = $module_path . '/theme/js/jquery.autopager-1.0.0.js';
  $block->content['#attached']['js'][] = $module_path . '/theme/js/throbber.js';
  $block->content['#attached']['js'][] = $module_path . '/theme/js/asu_events.load_more.js';
  $block->content['#attached']['js'][] = array(
    'data' => $module_path . '/theme/js/object-fit-polyfill.js',
    'type' => 'file',
    'weight' => 0,
    'scope' => 'footer',
  );

  return $block;
}
