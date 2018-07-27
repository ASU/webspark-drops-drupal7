<?php
// Creates a plugin for panels, which creates a new panel.
$plugin = array(
  'single' => TRUE,
  'title' => t('ASU News Listing'),
  'description' => t('Shows ASU News with configuration options.'),
  'category' => t('ASU News'),
  'edit form' => 'asu_news_asu_news_listing_edit_form',
  'render callback' => 'asu_news_asu_news_listing_render',
  'admin info' => 'asu_news_asu_news_listing_admin_info',
  'defaults' => array(
    'asu_news_listing_display_type' => 'full',
    'asu_news_listing_featured' => '',
    //'tweets_to_show' => 5,
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function asu_news_asu_news_listing_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Display format: <em>@display</em>.', array(
      '@display' => $conf['asu_news_listing_display_type'],
    ));
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function asu_news_asu_news_listing_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['asu_news_listing_display_type'] = array(
    '#type' => 'select',
    '#title' => t('Select type of Display'),
    '#default_value' => $conf['asu_news_listing_display_type'],
    '#options' => array(
      'full' => 'Full',
      'compact' => 'Compact',
    ),
  );

  $form['asu_news_listing_featured'] = array(
    '#type' => 'textfield',
    '#title' => 'Featured ASU News Item',
    '#default_value' => $conf['asu_news_listing_featured'],
    '#description' => 'Start typing title of ASU news, and use autocomplete feature.',
    '#autocomplete_path' => 'news/autocomplete',
    '#states' => array(
      // Hide the settings when the cancel notify checkbox is disabled.
      'invisible' => array(
       ':input[name="asu_news_listing_display_type"]' => array('value' => 'compact'),
      ),
    ),
  );

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function asu_news_asu_news_listing_edit_form_submit($form, &$form_state) {
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
function asu_news_asu_news_listing_render($subtype, $conf, $panel_args, $context = NULL) {

  $block = new stdClass();
  $featured = array();
  $nodes_render = array();
  $block->title = '';
  $module_path = drupal_get_path('module', 'asu_news');
  $breadcrumbs = block_load('easy_breadcrumb', 'easy_breadcrumb');
  $bc_render_array = _block_get_renderable_array(_block_render_blocks(array($breadcrumbs)));
  $bc_render_array['easy_breadcrumb_easy_breadcrumb']['easy_breadcrumb']['#prefix'] = '<div class="column container">';
  $bc_render_array['easy_breadcrumb_easy_breadcrumb']['easy_breadcrumb']['#suffix'] = '</div>';
  $bc_render_array['easy_breadcrumb_easy_breadcrumb']['easy_breadcrumb']['#breadcrumb'][1]['content'] = 'News';

  $block->content['breadcrumb'] = $bc_render_array;
  if ($conf['asu_news_listing_display_type'] == 'full') {
    $news_items = _asu_news_get_asunews_items(30, null, null, true);
    $news_items = node_view_multiple($news_items, 'news_list_page_teaser');

    if(!empty($conf['asu_news_listing_featured'])) {
      $nid = preg_match_all('/nid:[a-zA-Z0-9\ \+\-(\(\))]+/', $conf['asu_news_listing_featured'], $matches);
      $nid = $matches[0][0];
      $nid = str_replace("nid: ", "", $nid);

      $featured = node_load($nid);
      if ($featured) {
        $featured = node_view($featured, 'news_list_page_featured_teaser');
      }
    }

    $block->subject = '';
    $block->content['featured'] = $featured;
    $block->content['news_items'] = $news_items;
    $block->content['news_items']['#prefix'] = '<div class="asu-news-listing-wrapper">';
    $block->content['news_items']['#suffix'] = '</div>';
  }
  else {
    $nodes = _asu_news_get_asunews_items(30, null, null, true);
    $nodes_render = node_view_multiple($nodes, 'news_list_page_compact_teaser');

    $block->subject = '';
    $block->content['news_items'] = $nodes_render;
    $block->content['news_items']['#prefix'] = '<div class="asu-news-listing-wrapper">';
    $block->content['news_items']['#suffix'] = '</div>';
  }
  $block->content['pager'] = array('#theme' => 'pager');
  $block->content['load_more'] = array(
    '#type' => 'link',
    '#title' => 'Load More',
    '#href' => '#',
    '#attributes' => array(
      'class' => array('asu-news-load-more-btn'),
    ),
  );

  global $pager_total;
  $pager_settings = array(
    'pager_total' => $pager_total,
  );

  drupal_add_js(array('asu_news' => $pager_settings), 'setting');

  $block->content['#attached']['js'][] = $module_path . '/theme/js/jquery.autopager-1.0.0.js';
  $block->content['#attached']['js'][] = $module_path . '/theme/js/throbber.js';
  $block->content['#attached']['js'][] = $module_path . '/theme/js/asu_news.load_more.js';
  $block->content['#attached']['js'][] = array(
    'data' => $module_path . '/theme/js/object-fit-polyfill.js',
    'type' => 'file',
    'weight' => 0,
    'scope' => 'footer',
  );

  return $block;
}
