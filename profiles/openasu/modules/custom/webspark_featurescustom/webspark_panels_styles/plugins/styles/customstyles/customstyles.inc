<?php
/**
* Defines a style plugin
*
*  - panestyles: corresponds to directory name of plugin
*  - render pane: the suffix of the theme function for the pane (without "theme_").
*     - Example: If the function name is "theme_panestyles_render_pane",
*       the value of "render pane" is "panestyles_render_pane".
*  - render region: the suffix of the theme function for the region (without "theme_").
*     - Example: If the function name is "theme_panestyles_render_region",
*       the value of "render region" is "panestyles_render_region".
*  - pane settings form: name of function that returns a settings form
*  - hook theme: array of hook theme information
*    - define an array for pane and region. The key must match the first parameter of the returned theme() in the
*       corresponding theme_ function.
*       Example: 'hook theme' => 'panestyles_theme_pane' => array();
*        In function theme_panestyles_render_pane:
*          return theme('panestyles_theme_pane'...) [truncated]
*      - template: corresponds to name of tpl.php for pane, i.e. panestyles-pane.tpl.php
*      - path: the path where the template file lives
*      - variables: an array of variables to add to the $variables array in the theme function
*
*/

$plugin =  array(
  'customstyles' => array(
    'title' => t('Spacing and background colors'),
    'description'   => t('Custom styles for ASU Standards themed sites.'),
    'render pane' => 'customstyles_render_pane',
    'render region' => 'customstyles_render_region',
    'pane settings form' => 'customstyles_settings_form',
    'settings form' => 'customstyles_settings_form', // For region.
    'weight' => 100,
    'hook theme'    => array(
      'customstyles_theme_pane' => array(
        'template' => 'customstyles-pane',
         'path' => drupal_get_path('module', 'webspark_panels_styles') . '/plugins/styles/customstyles',
         'variables' => array(
           'content' => NULL,
           'settings' => NULL,
         ),
       ),
      'customstyles_theme_region' => array(
        'template' => 'customstyles-region',
         'path' => drupal_get_path('module', 'webspark_panels_styles') .'/plugins/styles/customstyles',
         'variables' => array(
           'content' => NULL,
         ),
       ),
    ),
  ),
);


function theme_customstyles_render_pane($vars) {
  $settings = $vars['settings'];
  $content = $vars['content'];

  // Make multi-value settings arrays into strings so they can just be printed
  // in the tpl.
  if (!empty($settings['panerowpad']) && is_array($settings['panerowpad'])) {
    $settings['panerowpad'] = array_filter($settings['panerowpad']);
    $settings['panerowpad'] = implode(' ', $settings['panerowpad']);
  }
  if (!empty($settings['panespace']) && is_array($settings['panespace'])) {
    $settings['panespace'] = array_filter($settings['panespace']);
    $settings['panespace'] = implode(' ', $settings['panespace']);
  }

  return theme('customstyles_theme_pane', array('content' => $content, 'settings' => $settings));
}


function theme_customstyles_render_region($vars) {
  $settings = $vars['settings'];
  $content = '';
  foreach ($vars['panes'] as $pane_id => $pane_output) {
    $content .= $pane_output;
  }
  if (empty($content)) {
    return;
  }

  // Make multi-value settings arrays into strings so they can just be printed
  // in the tpl.
  if (!empty($settings['panerowpad']) && is_array($settings['panerowpad'])) {
    $settings['panerowpad'] = array_filter($settings['panerowpad']);
    $settings['panerowpad'] = implode(' ', $settings['panerowpad']);
  }
  if (!empty($settings['panespace']) && is_array($settings['panespace'])) {
    $settings['panespace'] = array_filter($settings['panespace']);
    $settings['panespace'] = implode(' ', $settings['panespace']);
  }

  return theme('customstyles_theme_region', array('content' => $content, 'settings' => $settings));
}

function customstyles_settings_form($style_settings) {

	$bg_options = array(
		'js-lightgraybg' => t('Light gray background'),
		'js-darkgraybg' => t('Dark gray background'),
		'no-bg' => t('White (or no) background'),
	);
  $form['fullwidthbg'] = array(
    '#type' => 'radios',
    '#title' => t('Add background colors to full-width rows:'),
    '#description' => t('Use on full-width rows only.'),
    '#options' => $bg_options,
    '#required' => FALSE,
    '#default_value' => (isset($style_settings['fullwidthbg'])) ? $style_settings['fullwidthbg'] : '',
  );

	$padding_options = array(
		'js-paddingabove' => t('Add spacing above row'),
		'js-paddingbelow' => t('Add spacing below row'),
		'js-remove2above' => t('Decrease spacing 6px above'),
		'js-remove6above' => t('Decrease spacing 12px above'),
		'js-remove2below' => t('Decrease spacing 6px below'),
		'js-remove6below' => t('Decrease spacing 12px below'),
	);
  $form['panerowpad'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Adjust row spacing:'),
    '#description' => t('Adjust padding on this panes row.'),
    '#options' => $padding_options,
    '#required' => FALSE,
    '#default_value' => (isset($style_settings['panerowpad'])) ? $style_settings['panerowpad'] : '',
  );
  
	$spacing_options = array(
		'space-top-sm' => t('Add 12px spacing above'),
		'space-top-md' => t('Add 30px spacing above'),
		'space-bot-sm' => t('Add 12px spacing below'),
		'space-bot-md' => t('Add 30px spacing below'),
	);
  $form['panespace'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Adjust pane spacing:'),
    '#description' => t('Adjust spacing on only this single pane.'),
    '#options' => $spacing_options,
    '#required' => FALSE,
    '#default_value' => (isset($style_settings['panespace'])) ? $style_settings['panespace'] : '',
  );
  
  return $form;
}
