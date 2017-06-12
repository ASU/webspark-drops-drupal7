<?php
/**
 * @file
 * Theming functions for the asu_isearch module.
 *
 * @author Sebastian Nievas (snievas@asu.edu)
 *
 */

/**
 *Implements hook_theme()
 */
function asu_isearch_theme() {
  return array(
    // iSearch Directory Panel Pane
    'fieldable_panels_pane__isearch_directory' => array(
      'template' => 'theme/fieldable-panels-pane--isearch-directory',
      'render element' => 'elements',
      'file' => 'inc/asu_isearch.theme.inc',
      'type' => 'module'
    ),
    // ASU Spotlight container
    'asu_isearch_dept_picker' => array(
      'variables' => array(
        'items' => array(),
        'settings' => array(),
        'label' => 'Select Department'
      ),
      'template' => 'theme/asu_isearch.dept_picker',
      'file' => 'inc/asu_isearch.theme.inc',
    ),
    // iSearch Department Tree
    'asu_isearch_dept_tree' => array(
      'variables' => array(
        'item' => array(),
        'settings' => array(),
        'caption' => ''
      ),
      'file' => 'inc/asu_isearch.theme.inc',
    ),
    'pager__isearch_directory__isearch_directory_list' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'file' => 'inc/asu_isearch.theme.inc',
    ),
    'asu_dir_pager_link' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'file' => 'inc/asu_isearch.theme.inc',
    ),
    'asu_dir_pager_previous' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'file' => 'inc/asu_isearch.theme.inc',
    ),
    'asu_dir_pager_next' => array(
      'variables' => array('items' => array(), 'settings' => array()),
      'file' => 'inc/asu_isearch.theme.inc',
    )
  );
}

/***
 * Override the default pager for our view
 *
 * @param $vars
 * @return string
 */
function theme_pager__isearch_directory__isearch_directory_list(&$variables) {

  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;
  $li_first = NULL;
  $li_last = NULL;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }

  // End of generation loop preparation.
  $tags[1] = '<i class="fa fa-angle-double-left" aria-hidden="true"></i>';
  $tags[3] = '<i class="fa fa-angle-double-right" aria-hidden="true"></i>';

  //$li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('asu_dir_pager_previous', array(
    'text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters
  ));
  $li_next = theme('asu_dir_pager_next', array(
    'text' => (isset($tags[3]) ? $tags[3] : t('next ›')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters
  ));
  //$li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('asu_dir_pager_previous', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($pager_current - $i),
              'parameters' => $parameters
            )),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current'),
            'data' => $i,
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('asu_dir_pager_next', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($i - $pager_current),
              'parameters' => $parameters
            )),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }


    if ($li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }


    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
        'items' => $items,
        'attributes' => array('class' => array('pager')),
      ));
  }
}

/*
function theme_asu_dir_pager_previous($text, $limit, $element = 0, $interval = 1, $parameters = array()) {
  global $pager_page_array;
  $output = '';

  // If we are anywhere but the first page
  if ($pager_page_array[$element] > 0) {
    $page_new = pager_load_array($pager_page_array[$element] - $interval, $element, $pager_page_array);

    // If the previous page is the first page, mark the link as such.
    if ($page_new[$element] == 0) {
      //$output = theme('pager_first', $text, $limit, $element, $parameters);
    }
    // The previous page is not the first page.
    else {
      $output = theme('asu_dir_pager_link', $text, $page_new, $element, $parameters);
    }
  }

  return $output;
}*/

function theme_asu_dir_pager_previous($variables) {
  $text = $variables['text'];
  $element = $variables['element'];
  $interval = $variables['interval'];
  $parameters = $variables['parameters'];
  global $pager_page_array;
  $output = '';

  // If we are anywhere but the first page
  if ($pager_page_array[$element] > 0) {
    $page_new = pager_load_array($pager_page_array[$element] - $interval, $element, $pager_page_array);

    $output = theme('asu_dir_pager_link', array(
      'text' => $text,
      'page_new' => $page_new,
      'element' => $element,
      'parameters' => $parameters
    ));
    /*
    // If the previous page is the first page, mark the link as such.
    if ($page_new[$element] == -1) {
      $output = theme('pager_first', array('text' => $text, 'element' => $element, 'parameters' => $parameters));
    }
    // The previous page is not the first page.
    else {

    }*/
  }

  return $output;
}

function theme_asu_dir_pager_next($variables) {
  $text = $variables['text'];
  $element = $variables['element'];
  $interval = $variables['interval'];
  $parameters = $variables['parameters'];
  global $pager_page_array, $pager_total;
  $output = '';

  // If we are anywhere but the last page
  if ($pager_page_array[$element] < ($pager_total[$element] - 1)) {
    $page_new = pager_load_array($pager_page_array[$element] + $interval, $element, $pager_page_array);
    // If the next page is the last page, mark the link as such.


    $output = theme('asu_dir_pager_link', array(
      'text' => $text,
      'page_new' => $page_new,
      'element' => $element,
      'parameters' => $parameters
    ));
    /*
    if ($page_new[$element] == ($pager_total[$element] - 1)) {
      $output = theme('pager_last', array('text' => $text, 'element' => $element, 'parameters' => $parameters));
    }
    // The next page is not the last page.
    else {

    }*/
  }

  return $output;
}

function theme_asu_dir_pager_link($variables) {
  $text = $variables['text'];
  $page_new = $variables['page_new'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  //$attributes = $variables['attributes'];
  $attributes = array();

  $page = isset($_GET['page']) ? $_GET['page'] : '';

  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();
  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }
  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  // Set each pager link title
  if (!isset($attributes['title'])) {
    static $titles = NULL;
    if (!isset($titles)) {
      $titles = array(
        t('« first') => t('Go to first page'),
        t('‹ previous') => t('Go to previous page'),
        t('next ›') => t('Go to next page'),
        t('last »') => t('Go to last page'),
      );
    }
    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    elseif (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array('@number' => $text));
    }
  }

  //
  $attributes['href'] = url($_GET['q'], array('query' => $query));
  return '<a' . drupal_attributes($attributes) . '>' . $text . '</a>';
}

/**
 * Default theme implementation for iSearch department tree
 */
function theme_asu_isearch_dept_tree(&$vars) {
  $standalone = FALSE;
  $whole_tree = FALSE;
  $config_target = FALSE;

  if (isset($vars['settings']['standalone_tree'])) {
    $standalone = $vars['settings']['standalone_tree'];
  }

  if (isset($vars['settings']['whole_tree'])) {
    $whole_tree = $vars['settings']['whole_tree'];
  }

  if (isset($vars['settings']['config_target'])) {
    $config_target = $vars['settings']['config_target'];
  }

  $tree = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_TREE_ENDPOINT, FALSE); //asu_dir_utilities_get_dept_tree();

  // jqTree (http://mbraak.github.com/jqTree)
  libraries_load('jqtree');
  libraries_load('fontawesome');

  // Custom
  drupal_add_css(drupal_get_path('module', 'asu_isearch') . '/css/asu_isearch.dept_tree.css');
  drupal_add_js(drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch.dept_tree.js');

  $top_level_ids = array(
    "top_level_psid" => ASU_ISEARCH_DIRECTORY_TOP_LEVEL_PS_ID,
    "top_level_nid" => ASU_ISEARCH_DIRECTORY_TOP_LEVEL_DEPT_NID
  );

  // Pass our items and configs to the JS
  // will need to pass extra configs if the tree is being used without the people display (standalone)
  if ($standalone) {
    if (isset($vars['items'][0]['directory_items'])) {
      $nids = $vars['items'][0]['directory_items'];
    }
    else {
      $nids = array(ASU_ISEARCH_DIRECTORY_TOP_LEVEL_DEPT_NID);
    }

    $settings = array(
      'tree' => $tree,
      'top_level_ids' => $top_level_ids,
      'standalone' => $standalone,
      'dept_nids' => $nids,
    );
  }
  else {
    $settings = array(
      'tree' => $tree,
      'whole_tree' => $whole_tree,
      'top_level_ids' => $top_level_ids
    );
  }

  $settings['config_target'] = $config_target;

  drupal_add_js(array('asu_isearch_dept_tree' => $settings), 'setting');


  $form = array();
  $form['include_subdepts'] = array(
    '#type' => 'checkbox',
    '#title' => 'Include sub-departments?',
    '#attributes' => array(
      'id' => 'asu-isearch-dept-include-subdept',
      'name' => 'include_subdepts',
    ),
    '#description' => t('This will include all sub-departments beneath the selected department.'),
  );

  $form['dialog_submit'] = array(
    '#type' => 'button',
    '#value' => 'Select',
    '#attributes' => array(
      'id' => 'asu-isearch-dept-picker-select',
      'type' => 'button',
    ),
  );

  $form['dialog_cancel'] = array(
    '#type' => 'button',
    '#value' => 'Cancel',
    '#attributes' => array(
      'id' => 'asu-isearch-dept-picker-cancel',
      'type' => 'button',
    ),
  );

  return '<div class="asu-directory-tree-hierarchy">
    <div class="dialog-title">
      Choose a department
      <div class="close-dialog"><span class="fa fa-close"></span></div>
    </div>
    <div class="tree-wrapper">
      <div id="treediv"></div>
    </div>
    <div class="actions">
      ' . drupal_render($form) . '
    </div>
  </div>';

}