<?php
/**
 * File that creates configurable panel for events listing page.
 */

// Creates a plugin for panels, which creates a new panel.
$plugin = array(
  'single' => TRUE,
  'title' => t('ASU Search Events Filters'),
  'description' => t('Shows ASU Events Filters with configuration options.'),
  'category' => t('ASU Events'),
  'edit form' => 'asu_events_asu_events_search_filters_edit_form',
  'render callback' => 'asu_events_asu_events_search_filters_render',
  'admin info' => 'asu_events_asu_events_search_filters_admin_info',
  'defaults' => array(
    'asu_events_search_filters_display_type' => 'full',
    'asu_events_search_filters_by' => '',
    'asu_events_search_filter_term' => '',
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function asu_events_asu_events_search_filters_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Display format: <em>@display</em>.', array(
      '@display' => $conf['asu_events_search_filters_display_type'],
    ));
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function asu_events_asu_events_search_filters_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['asu_events_search_filters_display_type'] = array(
    '#type' => 'select',
    '#title' => t('Select type of Display'),
    '#default_value' => $conf['asu_events_search_filters_display_type'],
    '#options' => array(
      'full' => 'Full',
      'compact' => 'Compact',
    ),
  );

  $form['asu_events_search_filters_by'] = array(
    '#type' => 'textfield',
    '#title' => 'Filter ASU Events By',
    '#default_value' => $conf['asu_events_search_filters_by'],
    '#description' => 'Start typing name of ASU Vocab, and use autocomplete feature.',
    '#autocomplete_path' => 'asu_vocab/autocomplete',
  );

  $vocab = $conf['asu_events_search_filters_by'];
  $vid = '';
  if (!empty($vocab)) {
    $vid = preg_match_all('/vid:[a-zA-Z0-9\ \+\-(\(\))]+/', $vocab, $matches);
    $vid = $matches[0][0];
  }

  $form['asu_events_search_filter_term'] = array(
    '#type' => 'select',
    '#title' => 'Featured ASU Event Item' . $vids,
    '#default_value' => $conf['asu_events_search_filter_term'],
    '#description' => 'Start typing title of ASU news, and use autocomplete feature. If this term is set the children of this term will be displayed.',
    '#options' => _asu_events_get_all_terms_by_parent($vid),
  );

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function asu_events_asu_events_search_filters_edit_form_submit($form, &$form_state) {
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
function asu_events_asu_events_search_filters_render($subtype, $conf, $panel_args, $context = NULL) {

  $block = new stdClass();
  $nodes_render = array();
  $block->title = '';

  $module_path = drupal_get_path('module', 'asu_events');
  drupal_add_css($module_path . '/theme/css/asumod-events.css', array('group' => CSS_THEME, 'every_page' => TRUE));
  drupal_add_js($module_path . '/theme/js/asu_events.search.js', array('type'=>'file'));

  $upcoming_title = array(
    '#type' => 'markup',
    '#markup' => '<div class="upcoming-title">Upcoming Events</div>'
  );
  //$block->content['breadcrumb'] = $bc_render_array;
  //$block->content['upcoming_title'] = $upcoming_title;

  //$nodes = _asu_events_get_search_asuevents_items(30, null, null, true);
  $vocab = $conf['asu_events_search_filters_by'];

  $vid = preg_match_all('/vid:[a-zA-Z0-9\ \+\-(\(\))]+/', $vocab, $matches);
  $vid = $matches[0][0];
  $vid = str_replace("vid: ", "", $vid);

  $terms = taxonomy_get_tree($vid);

  $term_vars = array();
  $qp = drupal_get_query_parameters();

  $active = (isset($qp['category']) && !empty($qp['category']))? 'active' : '';

  foreach($terms as $key => $term) {
    if (!empty($term->name)) {
      $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term->tid);
      $image = $term_wrapper->__isset('field_category_image') ? $term_wrapper->field_category_image->value() : '';
      $url = (!empty($image)) ? file_create_url($image['uri']) : '';
      $active_term = '';
      if ($active) {
        $active_term = ($term->name == $qp['category'])? 'active' : '';
      }
      $term_vars[] = array(
        'title' => $term->name,
        'img' => $url,
        'active' => $active_term,
      );
    }
  }

  $filters['top'] = $term_vars;
  $filters['class'] = $active;

  $block->content['filters'] = array(
    '#type' => 'markup',
    '#markup' => theme('asu_events_taxonomy_search_filter', array('filters' => $filters)),
  );

  return $block;
}
