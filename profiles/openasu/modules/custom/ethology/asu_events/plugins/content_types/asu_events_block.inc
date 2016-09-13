<?php
$plugin = array(
  'single' => TRUE,
  'title' => t('ASU Events Block'),
  'description' => t('Shows ASU Events with configuration options.'),
  'category' => t('ASU Events'),
  'edit form' => 'asu_events_asu_events_block_edit_form',
  'render callback' => 'asu_events_asu_events_block_render',
  'admin info' => 'asu_events_asu_events_block_admin_info',
  'defaults' => array(
    'asu_events_block_display_type' => 'featured',
    'asu_events_block_featured' => '',
    'asu_events_block_start_date' => date("Y-m-d"),
    'asu_events_block_end_date'
    //'tweets_to_show' => 5,
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function asu_events_asu_events_block_admin_info($subtype, $conf, $contexts) {
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
function asu_events_asu_events_block_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['asu_events_block_display_type'] = array(
    '#type' => 'select',
    '#title' => t('Select type of Display'),
    '#default_value' => $conf['asu_events_block_display_type'],
    '#options' => array(
      'featured' => 'Featured',
      'one' => 'One Event',
      'two' => 'Two Events'
    ),
  );

  $form['asu_events_block_featured'] = array(
    '#type' => 'textfield',
    '#title' => 'Featured ASU Events',
    '#default_value' => $conf['asu_events_block_featured'],
    '#description' => 'Featured ASU Events',
    '#autocomplete_path' => 'events/autocomplete',
    '#states' => array(
      // Hide the settings when the cancel notify checkbox is disabled.
      'invisible' => array(
       ':input[name="asu_events_block_display_type"]' => array('value' => 'one'),
       ':input[name="asu_events_block_display_type"]' => array('value' => 'two'),
      ),
    ),
  );

  $form['asu_events_block_start_date'] = array(
    '#type' => 'textfield',
    '#title' => 'Start Date',
    '#default_value' => $conf['asu_events_block_start_date'],
    '#description' => 'Show only asu event items that start after this date',
  );

  $form['asu_events_block_end_date'] = array(
    '#type' => 'textfield',
    '#title' => 'End Date',
    '#default_value' => $conf['asu_events_block_end_date'],
    '#description' => 'Show only asu event items that end before this date',
  );

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function asu_events_asu_events_block_edit_form_submit($form, &$form_state) {
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
function asu_events_asu_events_block_render($subtype, $conf, $panel_args, $context = NULL) {
  $module_path = drupal_get_path('module', 'asu_events');
  drupal_add_css($module_path . '/theme/css/asumod-events.css', array('group' => CSS_THEME, 'every_page' => TRUE));

  $block = new stdClass();
  $featured = array();
  $nodes_render = array();
  $block->title = 'Events';

  $events_link = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('asu-events-list-wrapper'),
    ),
    'list' => array(
      '#type' => 'link',
      '#title' => 'View all events',
      '#href' => '/events',
      '#attributes' => array(
        'class' => array('asu-list-link'),
      ),
    ),
  );

  $block->title .= render($events_link);

  $field_filters = array();

  if (!empty($conf['asu_events_block_start_date'])) {

    $field = array(
      'name' => 'field_asuevent_very_start_date',
      'id' => 'value',
      'value' => $conf['asu_events_block_start_date'],
      'op' => '>='
    );
    $field_filters[] = $field;
  }

  if ($conf['asu_events_block_display_type'] == 'featured') {
    $featured = array();
    $nodes_render = array();
    if (!empty($conf['asu_events_block_featured'])) {
      $nid = preg_match_all('/nid:[a-zA-Z0-9\ \+\-(\(\))]+/', $conf['asu_events_block_featured'], $matches);
      $nid = $matches[0][0];
      $nid = str_replace("nid: ", "", $nid);

      $featured_node = node_load($nid);
      $featured = node_view($featured_node, 'events_featured_teaser');
      $nodes = _asu_events_get_asuevents_items(3, $field_filters);
      $nodes_render = node_view_multiple($nodes, 'events_small_teaser');
    }
    else {
      $nodes = _asu_events_get_asuevents_items(4, $field_filters);
      $featured_node = array_shift($nodes);
      $featured = node_view($featured_node, 'events_featured_teaser');
      $nodes_render = node_view_multiple($nodes, 'events_small_teaser');
    }
    $class = 'featured-events';
    $block->content['events'] = array(
      '#type' => 'markup',
      '#markup' => theme(
      'asu_events_full_block',
       array('featured' => $featured, 'events_items' => $nodes_render, 'class' => $class)
      ),
    );
  }
  elseif ($conf['asu_events_block_display_type'] == 'two') {
    $nodes = _asu_events_get_asuevents_items(2, $field_filters);
    $nodes_render = node_view_multiple($nodes, 'events_featured_teaser');
    $class = 'two-events';
    $block->content['events'] = array(
      '#type' => 'markup',
      '#markup' => theme('asu_events_highlighted_block', array('events_items' => $nodes_render, 'class' => $class)),
    );
  }
  else {
    if (!empty($conf['asu_events_block_featured'])) {
      $nid = preg_match_all('/nid:[a-zA-Z0-9\ \+\-(\(\))]+/', $conf['asu_events_block_featured'], $matches);
      $nid = $matches[0][0];
      $nid = str_replace("nid: ", "", $nid);

      $featured_node = node_load($nid);
      if (!empty($featured_node)) {
        $featured = node_view($featured_node, 'events_featured_teaser');
        $nodes_render = $featured;
      }
    }
    else {
      $nodes = _asu_events_get_asuevents_items(1, $field_filters);
      $nodes_render = node_view_multiple($nodes, 'events_full_teaser');
    }

    $block->content['events'] = array(
      '#type' => 'markup',
      '#markup' => theme('asu_events_highlighted_block', array('events_items' => $nodes_render, 'class' => 'single-event')),
    );
  }
  $block->content['#attached']['js'][] = array(
    'data' => $module_path . '/theme/js/object-fit-polyfill.js',
    'type' => 'file',
    'weight' => 0,
    'scope' => 'footer',
  );
  return $block;
}
