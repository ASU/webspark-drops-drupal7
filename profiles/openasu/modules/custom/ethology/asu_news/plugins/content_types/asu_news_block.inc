<?php
// Creates a plugin for panels, which creates a new panel.
$plugin = array(
  'single' => TRUE,
  'title' => t('ASU News Block'),
  'description' => t('Shows ASU News with configuration options.'),
  'category' => t('ASU News'),
  'edit form' => 'asu_news_asu_news_block_edit_form',
  'render callback' => 'asu_news_asu_news_block_render',
  'admin info' => 'asu_news_asu_news_block_admin_info',
  'defaults' => array(
    'asu_news_block_display_type' => 'featured',
    'asu_news_block_featured' => '',
    'asu_news_block_saf' => '',
    //'tweets_to_show' => 5,
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function asu_news_asu_news_block_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Display format: <em>@@display</em>.', array(
      '@display' => $conf['asu_news_block_display_type'],
    ));
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function asu_news_asu_news_block_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['asu_news_block_display_type'] = array(
    '#type' => 'select',
    '#title' => t('Select type of Display'),
    '#default_value' => $conf['asu_news_block_display_type'],
    '#options' => array(
      'featured' => 'Featured',
      'higlighted' => 'Highlighted',
    ),
  );

  $form['asu_news_block_featured'] = array(
    '#type' => 'textfield',
    '#title' => 'Featured ASU News',
    '#default_value' => $conf['asu_news_block_featured'],
    '#description' => 'Featured ASU News',
    '#autocomplete_path' => 'news/autocomplete',
    '#states' => array(
      // Hide the settings when the cancel notify checkbox is disabled.
      'invisible' => array(
       ':input[name="asu_news_block_display_type"]' => array('value' => 'higlighted'),
      ),
    ),
  );

  $form['asu_news_block_saf'] = array(
    '#type' => 'textfield',
    '#title' => 'Filter by Category Label',
    '#default_value' => $conf['asu_news_block_saf'],
    '#description' => 'Show only ASU News items with this category label',
    '#autocomplete_path' => 'taxonomy/autocomplete/field_saf',
  );

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function asu_news_asu_news_block_edit_form_submit($form, &$form_state) {
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
function asu_news_asu_news_block_render($subtype, $conf, $panel_args, $context = NULL) {
  $module_path = drupal_get_path('module', 'asu_news');
  drupal_add_css($module_path . '/theme/css/asumod.css', array('group' => CSS_THEME, 'every_page' => TRUE));

  $block = new stdClass();
  $featured = array();
  $nodes_render = array();
  $block->title = 'News';
  $news_link = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('asu-news-list-wrapper'),
    ),
    'list' => array(
      '#type' => 'link',
      '#title' => 'More news',
      '#href' => '/news',
      '#attributes' => array(
        'class' => array('asu-news-list-link'),
      ),
    ),
  );

  $block->title .= render($news_link);

  $field_filters = array();

  if (!empty($conf['asu_news_block_saf'])) {
    $saf_filter = taxonomy_get_term_by_name($conf['asu_news_block_saf']);
    $saf_filter = array_pop($saf_filter);

    $field = array(
      'name' => 'field_saf',
      'id' => 'tid',
      'value' => $saf_filter->tid,
      'op' => '='
    );
    $field_filters[] = $field;
  }

  if ($conf['asu_news_block_display_type'] == 'featured') {
    $featured = array();
    $nodes_render = array();
    if (!empty($conf['asu_news_block_featured'])) {
      $nid = preg_match_all('/nid:[a-zA-Z0-9\ \+\-(\(\))]+/', $conf['asu_news_block_featured'], $matches);
      $nid = $matches[0][0];
      $nid = str_replace("nid: ", "", $nid);

      $featured_node = node_load($nid);
      $featured = node_view($featured_node, 'news_featured_teaser');
      $nodes = _asu_news_get_asunews_items(3, $field_filters);
      $nodes_render = node_view_multiple($nodes, 'news_small_teaser');
    }
    else {
      $nodes = _asu_news_get_asunews_items(4, $field_filters);
      $featured_node = array_pop($nodes);
      $featured = node_view($featured_node, 'news_featured_teaser');
      $nodes_render = node_view_multiple($nodes, 'news_small_teaser');
    }

    $block->content['news'] = array(
      '#type' => 'markup',
      '#markup' => theme(
      'asu_news_full_block',
       array('featured' => $featured, 'news_items' => $nodes_render)),
    );
  }
  else {
    $nodes = _asu_news_get_asunews_items(3);
    $nodes_render = node_view_multiple($nodes, 'news_medium_teaser');

    $block->content['news'] = array(
      '#type' => 'markup',
      '#markup' => theme('asu_news_highlighted_block', array('news_items' => $nodes_render)),
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
