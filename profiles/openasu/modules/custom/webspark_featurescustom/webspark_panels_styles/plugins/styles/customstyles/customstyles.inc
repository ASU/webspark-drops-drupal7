<?php

/**
 * @file
 * Definition of the Custom Styles panels style plugin.
 */

$plugin = array(
  'title' => t('Spacing and background colors'),
  'description' => t('Custom styles for ASU Standards themed sites.'),
  'render region' => 'customstyles_render_region',
  'render pane' => 'customstyles_render_pane',
  'settings form' => 'customstyles_pane_settings_form',
  'pane settings form' => 'customstyles_pane_settings_form',
  'weight' => 100,
);

/**
 * Theme fuction for the region style.
 */
function theme_customstyles_render_region($vars) {
  $content = $vars['panes'];
  $settings = $vars['settings'];

  $settings['attributes'] = '';
  foreach ($settings as $key=>$param) {
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
 */
function theme_customstyles_render_pane($vars) {
  $content = &$vars['content'];
  $settings = $vars['settings'];

  // This is needed to prevent throwing an error in php 5.5+
  if (!isset($content->css_class)) {
    $content->css_class = '';
  }
  foreach ($settings as $key=>$param) { 
     $content->css_class .= ' ' . $param;
  }
  $output = theme('panels_pane', $vars);

  return $output;
}

/**
 * Options for the Panels style plugin to help style panes.
 */
function customstyles_pane_settings_form($style_settings) {
   
   $bgcolors_default_value = isset($style_settings['bgcolors']) ? $style_settings['bgcolors'] : ''; 
   $bgcolor_options = array(
			'' => t('None'), 
			'js-lightgraybg' => t('Light gray background'),
			'js-darkgraybg' => t('Dark gray background'),
    );
    $form['bgcolors'] = array(
      '#prefix' => '<div class="well">',
      '#suffix' => '</div>',
      '#type' => 'radios',
			'#title' => t('Add background color to the entire row:'),
			'#description' => t('The background color will be applied to the entire row that contains this pane or region.'),
			'#required' => FALSE,
      '#options' => $bgcolor_options,
      '#default_value' => $bgcolors_default_value,
    );

    $padtop_default_value = isset($style_settings['padtop']) ? $style_settings['padtop'] : ''; 
    $padbot_default_value = isset($style_settings['padbot']) ? $style_settings['padbot'] : ''; 
    $martop_default_value = isset($style_settings['martop']) ? $style_settings['martop'] : ''; 
    $marbot_default_value = isset($style_settings['marbot']) ? $style_settings['marbot'] : ''; 
    
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

   $form['padtop'] = array(
      '#prefix' => '<div class="well">',
      '#suffix' => '</div>',
			'#type' => 'radios',
			'#title' => t('Adjust the padding on the top'),
			'#description' => t(''),
      '#options' => $padtop_options,
      '#required' => FALSE,
      '#default_value' => $padtop_default_value,
    );

   $form['padbot'] = array(
      '#prefix' => '<div class="well">',
      '#suffix' => '</div>',
			'#type' => 'radios',
			'#title' => t('Adjust the padding on the bottom'),
      '#description' => t(''),
      '#options' => $padbot_options,
      '#required' => FALSE,
      '#default_value' => $padbot_default_value,
    );

   $form['martop'] = array(
      '#prefix' => '<div class="well">',
      '#suffix' => '</div>',
			'#type' => 'radios',
			'#title' => t('Adjust the margin on the top'),
			'#description' => t(''),
      '#options' => $martop_options,
      '#required' => FALSE,
      '#default_value' => $martop_default_value,
    );

   $form['marbot'] = array(
      '#prefix' => '<div class="well">',
      '#suffix' => '</div>',
			'#type' => 'radios',
			'#title' =>  t('Adjust the margin on the bottom'),
			'#description' => t(''),
      '#options' => $marbot_options,
      '#required' => FALSE,
      '#default_value' => $marbot_default_value,
    ); 

  return $form;
}

/**
 * Get pane/region styles depending on chosen classes.
 *
 * @return array
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
 * @return array
 *   Array with prefix and suffix keys.
 */
function _customstyles_wrapper_wrap($item = array()) {
  $wrap['prefix'] = NULL;
  $wrap['suffix'] = NULL;
  $wrap['attributes'] = NULL;

  if (!empty($item['attributes'])) {
    $value = $item['attributes'];
    $wrap['attributes'] .= " class=\"$value\"";
  }

  $wrap['prefix'] = '<div ' . $wrap['attributes'] . '>';
  $wrap['suffix'] = '</div>';

  if (!empty($item['prefix'])) {
    $wrap['prefix'] = $item['prefix'];
  }
  if (!empty($item['suffix'])) {
    $wrap['suffix'] = $item['suffix'];
  }

  $wrap['prefix'] = PHP_EOL . $wrap['prefix'];
  $wrap['suffix'] = $wrap['suffix'] . PHP_EOL;

  return $wrap;
}

