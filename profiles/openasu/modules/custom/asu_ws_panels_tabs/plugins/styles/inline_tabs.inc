<?php

/**
 * @file
 * Definition of the 'Tabs' panel style.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Inline Tabs'),
  'description' => t('Show panel panes in a region as inline Webspark-accessible tabs.'),
  'render region' => 'asu_ws_panels_tabs_style_render_region',
  'settings form' => 'asu_ws_panels_tabs_pane_settings_form',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_asu_ws_panels_tabs_style_render_region($vars) {

  $display = $vars['display'];
  $region_id = $vars['region_id'];
  $owner_id = $vars['owner_id'];
  $panes = $vars['panes'];
  $settings = $vars['settings'];
  $form_filters = '';

  /* todo: uncomment for universal filters
  if (isset($settings['region_asu_dir_filter_form']) && $settings['region_asu_dir_filter_form']) {
    $form_filters = asu_ws_panels_tabs_asu_dir_filters();
  }*/

  $tab_id = 'tabs-';
  $pattern = isset($settings['panel_tab_id_pattern']) ? $settings['panel_tab_id_pattern'] : 'region';
  if ($pattern == 'random') {
    $tab_id .= md5($owner_id . $region_id . REQUEST_TIME . rand());
  }
  else {
    $tab_id .= $owner_id . '-' . $region_id;
  }

  $tab_class = ' class="webspark-panels-tabs-region';


  if (!empty($settings['region_class'])) {
    $tab_class .= ' ' . check_plain($settings['region_class']);
  }

  $tab_class .= '"';

  $region_title = '';
  if (!empty($settings['region_title'])) {
    $title_element = isset($settings['region_title_tag']) ? $settings['region_title_tag'] : 'none';
    $context = isset($vars['renderer']->display_context) ? $vars['renderer']->display_context : $display->context;
    $title_text = check_plain(ctools_context_keyword_substitute($settings['region_title'], array(), $context));
    if ($title_element != 'none') {
      $region_title = '<' . $title_element . '>' . $title_text . '</' . $title_element . '>';
    }
    else {
      $region_title = $title_text;
    }
  }

  $element = array(
    '#prefix' => $form_filters . '<div id="' . $tab_id . '"' . $tab_class .'>' . $region_title,
    '#suffix' => '</div>',
    '#attached' => array(
      'library' => array(array('system', 'ui.tabs')),
      'js' => array(
        drupal_get_path('module', 'asu_ws_panels_tabs') . '/js/jquery.tabgroups.js' => array('type' => 'file'),
        drupal_get_path('module', 'asu_ws_panels_tabs') . '/js/asu_ws_panels_tabs.js' => array('type' => 'file'),
      ),
      'css' => array(
        drupal_get_path('module', 'asu_ws_panels_tabs') . '/css/asu_ws_panels_tabs.css' => array('type' => 'file'),
      )
    ),
  );

  $js_settings = array();
  $js_settings['websparkPanelsTabs']['tabsID'][] = $tab_id;

  $element['#attached']['js'][] = array(
    'type' => 'setting',
    'data' => $js_settings,
  );

  // Get the pane titles.
  $items = array();
  $delta = 1;

  if (isset($display->panels[$region_id])) {
    foreach ($display->panels[$region_id] as $pane_id) {
      // Make sure the pane exists.
      if (!empty($panes[$pane_id])) {
        $title = asu_ws_panels_tabs_pane_titles($display->did, $pane_id);

        $title = $title ? $title : t('Tab @delta', array('@delta' => $delta));
        $items[] = '<a style="padding: 0; font-weight: 400; font-size: 18px;" href="#' . $tab_id . '-' . $delta . '" class="webspark-tab-link">' . $title . '</a>';
        $delta++;
      }
    }
  }

  if ($delta === 1) {
    // No tabs to show, the tabs wrapper must not be rendered.
    return '';
  }

  $element['tabs_title'] = array('#theme' => 'item_list', '#items' => $items);

  $delta = 1;
  foreach ($panes as $pane_id => $item) {
    $element['tabs_content'][$pane_id] = array(
      '#prefix' => '<div id="' . $tab_id . '-' . $delta . '" class="webspark-panels-tabs">',
      '#suffix' => '</div>',
      '#markup' => $item,
    );
    $delta++;
  }

  return drupal_render($element);
}

function asu_ws_panels_tabs_asu_dir_filters() {

  // open wrapper
  $html = '<div class="row asu-dir-universal-filters">';

  // search box
  $html .= '<div id="asu-dir-ajax-solr-search-universal" class="col-md-3 asu-dir-search">
              <input title="Search" class="input-main-search form-control form-text required" placeholder="Enter Name or Keyword" size="15" maxlength="128"\>
            </div>';

  // expertise dropdown
  $html .= '<div class="col-md-2">
              <div class="form-type-select">
                <select title="Expertise Areas" id="asu-dir-ajax-solr-expertise-universal">
                    <option value="0">Select Expertise
                    </option>
                </select>    
              </div>
            </div>';

  // titles dropdown
  $html .= '<div class="col-md-2">
              <div class="form-type-select">
                <select title="Titles" id="asu-dir-ajax-solr-title-universal">
                    <option value="0">Select Title
                    </option>
                </select>    
              </div>
            </div>';

  // titles dropdown
  $html .= '<div class="col-md-2">
              <div class="form-type-select">
                <select title="Sort By" id="asu-dir-ajax-solr-sort-universal">
                    <option value="tsort">Sort by Rank</option>
                    <option value="lastNameSort">Sort by Last Name</option>
                    <option value="firstNameSort">Sort by First Name</option>
                </select>    
              </div>
            </div>';

  // search/apply filter button
  $html .= '<div class="col-md-3 asu-dir-universal-buttons">
                <button class="asu-dir-universal-people-search-btn btn-main-search btn" type="submit">
                    Search
                </button>
                <button class="asu-dir-universal-people-reset-btn btn-main-reset btn">
                    Reset
                </button>
            </div>';

  //close wrapper
  $html .= '</div>';

  return $html;

}

/**
 * Settings form for the plugin.
 */
function asu_ws_panels_tabs_pane_settings_form($style_settings) {
  $form = array();

  $form['region_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('Optional title of the region.'),
    '#required' => FALSE,
    '#default_value' => (isset($style_settings['region_title'])) ? $style_settings['region_title'] : ''
  );

  $form['region_title_tag'] = array(
    '#title' => t('Title tag'),
    '#type' => 'select',
    '#options' => array(
      'none' => t('- No tag -'),
      'h1' => t('h1'),
      'h2' => t('h2'),
      'h3' => t('h3'),
      'h4' => t('h4'),
      'h5' => t('h5'),
      'h6' => t('h6'),
      'div' => t('div'),
    ),
    '#default_value' => empty($style_settings['region_title_tag']) ? 'none' : $style_settings['region_title_tag'],
  );

  /* todo: uncomment for universal filters
  $form['region_asu_dir_filter_form'] = array(
    '#title' => t('Activate ASU DIRS Universal filters. Places a universal directory filter form into the region. Activate in regions with ASU Directory panels only.'),
    '#type' => 'checkbox',
    '#default_value' => empty($style_settings['region_asu_dir_filter_form']) ? FALSE : $style_settings['region_asu_dir_filter_form'],
  );*/

  $form['region_class'] = array(
    '#title' => t('Region CSS class'),
    '#description' => t('Additional CSS class of the region.'),
    '#type' => 'textfield',
    '#default_value' => empty($style_settings['region_class']) ? '' : $style_settings['region_class'],
  );

  $form['panel_tab_id_pattern'] = array(
    '#type' => 'radios',
    '#title' => t("Tab ID pattern"),
    '#decsription' => t("Method to generate HTML id attribute for tabs."),
    '#default_value' => isset($style_settings['panel_tab_id_pattern']) ? $style_settings['panel_tab_id_pattern'] : 'region',
    '#options' => array(
      'region' => t('Fixed, based on region id (select this when panel region can be placed on the page only once)'),
      'random' => t('Generate random id (select this when panel region can be placed on the page multiple times)'),
    ),
  );

  return $form;
}
