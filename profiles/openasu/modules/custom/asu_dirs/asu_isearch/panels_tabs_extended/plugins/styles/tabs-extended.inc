<?php

/**
 * @file
 * Definition of the 'Tabs Extended' panel style.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Tabs Extended'),
  'description' => t('Show panel panes in a region as tabs by adding tab panes.'),
  'render region' => 'panels_tabs_extended_style_render_region',
  'settings form' => 'panels_tabs_extended_pane_settings_form',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_tabs_extended_style_render_region($vars) {
  $display = $vars['display'];
  $region_id = $vars['region_id'];
  $owner_id = $vars['owner_id'];
  $panes = $vars['panes'];
  $settings = $vars['settings'];

  $tab_id = 'tabs-';
  $pattern = isset($settings['panel_tab_id_pattern']) ? $settings['panel_tab_id_pattern'] : 'region';
  if ($pattern == 'random') {
    $tab_id .= md5($owner_id . $region_id . REQUEST_TIME . rand());
  }
  else {
    $tab_id .= $owner_id . '-' . $region_id;
  }

  $tab_class = '';
  if (!empty($settings['region_class'])) {
    $tab_class = ' class="' . check_plain($settings['region_class']) . '"';
  }

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
    '#prefix' => '<div id="' . $tab_id . '"' . $tab_class . '>' . $region_title,
    '#suffix' => '</div>',
    '#attached' => array(
      'library' => array(array('system', 'ui.tabs')),
      'js' => array(
        drupal_get_path('module', 'panels_tabs_extended') . '/js/panels_tabs_extended.js' => array('type' => 'file'),
      ),
    ),
  );

  $js_settings = array();
  $js_settings['panelsTabsExtended']['tabsID'][] = $tab_id;

  $element['#attached']['js'][] = array(
    'type' => 'setting',
    'data' => $js_settings,
  );

  // Get the pane titles.
  $items = array();

  // We only want to render the defined tabs as tab titles
  $defined_tabs = panels_tabs_extended_pane_get_tabs();

  foreach ($defined_tabs as $pane_id => $tab_title) {
    $delta = $pane_id;
    $tab_title = $tab_title ? $tab_title : t('Tab @delta', array('@delta' => $delta));
    $items[$delta] = '<a href="#' . $tab_id . '-' . $delta . '">' . $tab_title . '</a>';
  }

  if (empty($items)) {
    // No tabs to show, the tabs wrapper must not be rendered.
    return '';
  }

  $element['tabs_title'] = array('#theme' => 'item_list', '#items' => $items);

  // loop through each pane
  $tab_content = array();
  $defined_tabs_keys = array_keys($defined_tabs);

  $delta = 0;

  foreach ($panes as $pane_id => $item) {
    // we have a tab title, no need to render it
    if (in_array($pane_id, $defined_tabs_keys)) {
      $delta = $pane_id;
      $tab_content[$delta] = '';
      continue;
    }
    $tab_content[$delta] .= $item;
  }

  foreach ($tab_content as $delta => $content) {
    // if the tab content is empty, then we'll hide the tab for now
    // TODO: Check some override to see if they intended to keep this tab content empty.
    if ($content === '') {
      unset($element['tabs_title']['#items'][$delta]);
      continue;
    }

    $element['tabs_content'][$delta] = array(
      '#prefix' => '<div id="' . $tab_id . '-' . $delta . '">',
      '#suffix' => '</div>',
      '#markup' => $content,
    );
  }

  return drupal_render($element);
}

/**
 * Settings form for the plugin.
 */
function panels_tabs_extended_pane_settings_form($style_settings) {
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
