<?php

/**
 * @file
 * Definition of the 'asu gold' panel style.
 */

$plugin = array(
  'title' => t('Arizona State Gold'),
  'description' => t('Wraps panes in the ASU gold style.'),
  'render pane' => 'openasu_bootstrap_asu_gold_render_pane',
  'weight' => -10,
);

/**
 * Theme function for the pane style.
 */
function theme_openasu_bootstrap_asu_gold_render_pane($vars) {
  $content = $vars['content'];
  $pane = $vars['pane'];
  $display = $vars['display'];
  $plugin = $vars['style'];
  
  $content->css_class .= ' yellow-pane';
  
  // if the style is gone or has no theme of its own, just display the output.
  return theme('panels_pane', array('content' => $content, 'pane' => $pane, 'display' => $display));
}
