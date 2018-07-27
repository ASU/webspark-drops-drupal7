<?php
/**
 * File that for creating and customizing blocks for asu_news
 * These blocks are currently not being used.
 * Leaving just in case in the future we might use this. 
 **/

function asu_news_block_info() {
  $blocks['asu_news'] = array(
    'info' => t('Asu News'),
    'cache' => DRUPAL_CACHE_PER_USER | DRUPAL_CACHE_PER_PAGE,
    'visibility' => BLOCK_VISIBILITY_LISTED,
    'mb_enabled' => TRUE,
  );

  $blocks['asu_news_listing'] = array(
    'info' => t('Asu News Listing'),
    'cache' => DRUPAL_CACHE_PER_USER | DRUPAL_CACHE_PER_PAGE,
    'visibility' => BLOCK_VISIBILITY_LISTED,
    'mb_enabled' => TRUE,
  );

  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function asu_news_block_view($delta = '', $multi_id = NULL) {
  switch ($delta) {
    case 'asu_news':
      return asu_news_asu_news_block_view($multi_id);
    case 'asu_news_listing':
      return asu_news_asu_news_listing_block_view();
  }
}

function asu_news_asu_news_listing_block_view() {
  $block = array();
  $news_items = array();
  $block['subject'] = '';

  $news_items = _asu_news_get_asunews_items(10);
  $news_items = node_view_multiple($news_items, 'news_list_page_teaser');

  $block['content'] = $news_items;

  return $block;
}

function asu_news_asu_news_block_view($multi_id = NULL) {

  $instance_settings = _asu_get_block_settings($multi_id['multiblock_delta']['#value']);
  drupal_add_css(drupal_get_path('module', 'asu_news') . '/theme/css/asumod.css', array('group' => CSS_THEME, 'every_page' => TRUE));
  $multi_id = $multi_id ? '_' . $multi_id['multiblock_delta']['#value'] : NULL;

  $block = array();
  $featured = array();
  $nodes_render = array();
  $block['subject'] = 'News';

  if ($instance_settings['display_type'] == 'featured') {
    $nodes = _asu_news_get_asunews_items(3);
    $nodes_render = node_view_multiple($nodes, 'news_small_teaser');
    $featured_node = node_load(5275);
    $featured = node_view($featured_node, 'news_featured_teaser');

    $block['content'] = theme(
      'asu_news_full_block',
       array('featured' => $featured, 'news_items' => $nodes_render)
    );
  }
  else {
    $nodes = _asu_news_get_asunews_items(3);
    $nodes_render = node_view_multiple($nodes, 'news_medium_teaser');

    $block['content'] = theme('asu_news_highlighted_block', array('news_items' => $nodes_render));
  }
  return $block;
}

function asu_news_block_configure($delta = '', $multi_id = NULL) {

  $multi_id = $multi_id ? '_' . $multi_id['multiblock_delta']['#value'] : NULL;
  $form = array();
  if ($delta == 'asu_news') {
    $form['asu_news_block_display_type'. $multi_id] = array(
      '#type' => 'select',
      '#title' => t('Select type of Display'),
      '#default_value' => variable_get('asu_news_block_display_type'.$multi_id, 'featured'),
      '#options' => array(
        'featured' => 'Featured',
        'higlighted' => 'Highlighted',
      ),
    );
  }
  return $form;
}

function asu_news_block_save($delta = '', $edit = NULL) {

  switch ($delta) {
    case 'asu_news':
      $multi_id = isset($edit['multiblock_delta']) ? '_'. $edit['multiblock_delta']['#value'] : NULL;
      variable_set('asu_news_block_display_type'. $multi_id, $edit['asu_news_block_display_type' . $multi_id]);
      break;
  }
}

function _asu_get_block_settings($multi_id) {
  $settings = array();

  $settings['display_type'] = variable_get('asu_news_block_display_type_' . $multi_id, 'featured');

  return $settings;
}
