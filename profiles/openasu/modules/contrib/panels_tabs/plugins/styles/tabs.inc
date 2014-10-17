<?php

/**
 * @file
 * Definition of the 'Tabs' panel style.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Tabs'),
  'description' => t('Show panel panes in a region as tabs.'),
  'render region' => 'panels_tabs_style_render_region',
  'settings form' => 'panels_tabs_pane_settings_form',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_tabs_style_render_region($vars) {
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
    '#prefix' => '<div id="' . $tab_id . '"' . $tab_class .'>' . $region_title,
    '#suffix' => '</div>',
    '#attached' => array(
      'library' => array(array('system', 'ui.tabs')),
      'js' => array(
        drupal_get_path('module', 'panels_tabs') . '/js/panels_tabs.js' => array('type' => 'file'),
      ),
    ),
  );

  $js_settings = array();
  $js_settings['panelsTabs']['tabsID'][] = $tab_id;

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
        $title = panels_tabs_pane_titles($display->did, $pane_id);
        $title = $title ? $title : t('Tab @delta', array('@delta' => $delta));
        $items[] = '<a href="#' . $tab_id . '-' . $delta . '">' . $title . '</a>';
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
      '#prefix' => '<div id="' . $tab_id . '-' . $delta . '">',
      '#suffix' => '</div>',
      '#markup' => $item,
    );
    $delta++;
  }

  return drupal_render($element);
}

/**
 * Settings form for the plugin.
 */
function panels_tabs_pane_settings_form($style_settings) {
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
