<?php
$plugin = array(
  'single' => TRUE,
  'title' => t('ASU Events Search Block'),
  'description' => t('Search ASU Events with configuration options.'),
  'category' => t('ASU Events'),
  'edit form' => 'asu_events_asu_events_search_block_edit_form',
  'render callback' => 'asu_events_asu_events_search_block_render',
  'admin info' => 'asu_events_asu_events_block_search_admin_info',
  'defaults' => array(
    'asu_events_search_block_filter_vocab' => '',
    // 'asu_events_block_featured' => '',
    // 'asu_events_block_start_date' => date("Y-m-d"),
    // 'asu_events_block_end_date'
    //'tweets_to_show' => 5,
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function asu_events_asu_events_search_block_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Display format: <em>@@display</em>.', array(
      '@display' => $conf['asu_events_search_block_display_type'],
    ));
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function asu_events_asu_events_search_block_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['asu_events_search_block_filter_vocab'] = array(
    '#type' => 'textfield',
    '#title' => 'Vocabulary to show',
    '#default_value' => $conf['asu_events_search_block_filter_vocab'],
    '#description' => 'Vocabulary to use to display term filters.',
    '#autocomplete_path' => 'asu_vocab/autocomplete',
    // '#states' => array(
    //   // Hide the settings when the cancel notify checkbox is disabled.
    //   'invisible' => array(
    //    ':input[name="asu_events_block_display_type"]' => array('value' => 'one'),
    //    ':input[name="asu_events_block_display_type"]' => array('value' => 'two'),
    //   ),
    // ),
  );

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function asu_events_asu_events_search_block_edit_form_submit($form, &$form_state) {
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
function asu_events_asu_events_search_block_render($subtype, $conf, $panel_args, $context = NULL) {
  $module_path = drupal_get_path('module', 'asu_events');
  drupal_add_css($module_path . '/theme/css/asumod-events.css', array('group' => CSS_THEME, 'every_page' => TRUE));
  drupal_add_js($module_path . '/theme/js/asu_events.search.js', array('type'=>'file'));

  $block = new stdClass();
  $vars = array();

  if (empty($conf['asu_events_search_block_filter_vocab'])) {
    $vocab = taxonomy_vocabulary_machine_name_load('asu_events_category');
    $vars['topics'] = taxonomy_get_tree($vocab->vid);
    $vars['topics_title'] = t('Topics');
  }
  else {
    $vocab = $conf['asu_events_search_block_filter_vocab'];

    $vid = preg_match_all('/vid:[a-zA-Z0-9\ \+\-(\(\))]+/', $vocab, $matches);
    $vid = $matches[0][0];
    $vid = str_replace("vid: ", "", $vid);
    $vocab = taxonomy_vocabulary_load($vid);
    $terms = taxonomy_get_tree($vid);

    $vars['topics_title'] = t($vocab->name);
    $vars['topics'] = $terms;
  }

  $block->content = theme('asu_events_search_block', array('vars' => $vars));
  return $block;
}
