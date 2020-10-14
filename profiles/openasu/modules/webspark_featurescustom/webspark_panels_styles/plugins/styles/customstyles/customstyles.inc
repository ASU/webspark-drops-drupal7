<?php

/**
 * @file
 * Definition of the Custom Styles panels style plugin.
 */

$plugin = array(
  'title' => t('Spacing and backgrounds (Colors, Images)'),
  'description' => t('Custom styles for ASU Standards themed sites.'),
  'render region' => 'customstyles_render_region',
  'render pane' => 'customstyles_render_pane',
  'settings form' => 'customstyles_pane_settings_form',
  'pane settings form' => 'customstyles_pane_settings_form',
  'weight' => 100,
);

/**
 * Theme function for the region style.
 */
function theme_customstyles_render_region($vars) {
  $content = $vars['panes'];
  $settings = $vars['settings'];

  $settings['attributes'] = '';
  foreach ($settings as $key => $param) {
    $settings['attributes'] .= ' ' . $param;
  }
  // Theme.
  if (!empty($settings['theme']) && $settings['theme']) {
    $output = theme('panels_default_style_render_region', $vars);
  }
  else {
    $output = implode(PHP_EOL, $content);
  }

  // Wrap
  if (!empty($output)) {
    $content_wrapper = _customstyles_wrapper_wrap($settings);
    $output = $content_wrapper['prefix'] . $output . $content_wrapper['suffix'];
  }
  return $output;
}

/**
 * Theme function for the pane style.
 * @throws Exception
 */
function theme_customstyles_render_pane($vars) {
  $content = &$vars['content'];
  $settings = $vars['settings'];

  if (!isset($content->css_class)) {
    $content->css_class = '';
  }
  // Add attributes to classes string
  foreach ($settings as $key => $param) {
     $content->css_class .= ' ' . $param;
  }
  // Custom additions of alt style custom classes
  $classes = _customstyles_alt_styles_check('divider', $content->css_class);
  if ($classes !== FALSE) {
    $content->css_class .= ' ' . $classes;
  }
  return theme('panels_pane', $vars);
}

/**
 * Return CSS classes to add a particular alt styling (white, gray, black).
 *
 * @param string $type - Type of pane content (i.e. divider, etc.). Usually from a CSS class part (prefix?)
 * @param string $classes - Current list of classes
 * @return false|string
 */
function _customstyles_alt_styles_check($type, $classes) {
  if (preg_match('/' . $type . '-(\w{4,7})-(white|gray|black)/', $classes, $matches)) {
    return ' ws2-element-alt ws2-element-alt-' . $matches[2];
  } else {
    return FALSE;
  }
}

/**
 * Options for the Panels style plugin to help style panes.
 */
function customstyles_pane_settings_form($style_settings) {
  // Options
  $bgcolor_options = array(
    '' => t('None'),
    'js-lightgraybg' => t('Light gray background'),
    'js-darkgraybg' => t('Dark gray background'),
  );
  $ws2_divider_options = array (
    '' => t('None'),
    'divider-topo-white' => t('Topographical White'),
    'divider-topo-black' => t('Topographical Black'),
    'divider-morse-white' => t('Morse code White'),
    'divider-morse-black' => t('Morse code Black'),
    'divider-network-white' => t('Network White'),
    'divider-network-black' => t('Network Black'),
  );
  $padtop_options = array (
    '' => t('None'),
    'space-top-sm' => t('Add 12px top padding'),
    'space-top-md' => t('Add 28px top padding'),
    'row-padding-top' => t('Add 42px top padding'),
  );
  $padbot_options = array (
    '' => t('None'),
    'space-bot-sm' => t('Add 12px bottom padding'),
    'space-bot-md' => t('Add 28px bottom padding'),
    'row-padding-bottom' => t('Add 42px bottom padding'),
  );
  $martop_options = array (
    '' => t('None'),
    'remove-6-above' => t('Remove 6px margin above'),
    'remove-12-above' => t('Remove 12px margin above'),
    'remove-28-above' => t('Remove 28px margin above'),
    'remove-42-above' => t('Remove 42px margin above'),
    'add-margin-12-above' => t('Add 12px margin above'),
    'add-margin-28-above' => t('Add 28px margin above'),
    'add-margin-42-above' => t('Add 42px margin above'),
  );
  $marbot_options = array (
    '' => t('None'),
    'remove-6-below' => t('Remove 6px margin below'),
    'remove-12-below' => t('Remove 12px margin below'),
    'remove-28-below' => t('Remove 28px margin below'),
    'remove-42-below' => t('Remove 42px margin below'),
    'add-margin-12-below' => t('Add 12px margin below'),
    'add-margin-28-below' => t('Add 28px margin below'),
    'add-margin-42-below' => t('Add 42px margin below'),
  );

  // Form API - form elements
  $default_attributes = array(
    '#prefix' => '<div class="well">',
    '#suffix' => '</div>',
    '#type' => 'radios',
    '#required' => FALSE,
  );
  $form['bgcolors'] = $default_attributes + array(
    '#title' => t('Add background color to the entire row:'),
    '#description' => t('This will be applied to the entire row that contains this pane or region.'),
    '#options' => $bgcolor_options,
    '#default_value' => isset($style_settings['bgcolors']) ? $style_settings['bgcolors'] : '',
  );
  $form['bgimages'] = $default_attributes + array(
    '#title' => t('Add background image to the entire row:'),
    '#description' => t('Added for WS2.0. Will be applied to the entire row that contains this pane or region.'),
    '#options' => $ws2_divider_options,
    '#default_value' => isset($style_settings['bgimages']) ? $style_settings['bgimages'] : '',
  );
  $form['padtop'] = $default_attributes + array(
    '#title' => t('Adjust the padding on the top'),
    '#options' => $padtop_options,
    '#default_value' => isset($style_settings['padtop']) ? $style_settings['padtop'] : '',
  );
  $form['padbot'] = $default_attributes + array(
    '#title' => t('Adjust the padding on the bottom'),
    '#options' => $padbot_options,
    '#default_value' => isset($style_settings['padbot']) ? $style_settings['padbot'] : '',
  );
  $form['martop'] = $default_attributes + array(
    '#title' => t('Adjust the margin on the top'),
    '#options' => $martop_options,
    '#default_value' => isset($style_settings['martop']) ? $style_settings['martop'] : '',
  );
  $form['marbot'] = $default_attributes + array(
    '#title' =>  t('Adjust the margin on the bottom'),
    '#options' => $marbot_options,
    '#default_value' => isset($style_settings['marbot']) ? $style_settings['marbot'] : '',
  );
  return $form;
}

/**
 * Get pane/region styles depending on chosen classes.
 *
 * @param $styles
 * @return string Array with prefix and suffix keys.
 *   Array with prefix and suffix keys.
 */
function _customstyles_get_styles($styles) {
  if (isset($styles)) {
    foreach ($styles as $key => $class) {
      if ($class === 0) {
        unset($styles[$key]);
      }
    }
   return $styles ? ' ' . implode(' ', $styles) : '';
  }
}

/**
 * Create a region wrapper from provided attributes.
 *
 * @param array $item - attributes for theming
 * @return array Array with prefix and suffix keys.
 */
function _customstyles_wrapper_wrap($item = array()) {
  $wrap = array(
    'prefix' => '',
    'suffix' => '',
    'attributes' => '',
  );
  $value = (!empty($item['attributes'])) ? $item['attributes'] : '';
  $wrap['attributes'] .= ' class="' . $value . '"';
  $wrap['prefix'] = (!empty($item['prefix'])) ? PHP_EOL . $item['prefix'] : PHP_EOL . '<div ' . $wrap['attributes'] . '>';
  $wrap['suffix'] = (!empty($item['suffix'])) ? $item['suffix']  . PHP_EOL : '</div>' . PHP_EOL;
  return $wrap;
}

