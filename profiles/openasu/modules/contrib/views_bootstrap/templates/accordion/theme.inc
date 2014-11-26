<?php

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_accordion_plugin_style(&$vars) {
  $view = &$vars['view'];
  $title_field = $vars['options']['title_field'];

  $vars['classes_array'][] = 'panel-group';

  // Get titles.
  if (isset($view->field[$title_field])) {
    foreach ($vars['view']->result as $key => $field) {
      $vars['titles'][$key] = strip_tags($view->style_plugin->get_field($key, $title_field));
    }
  }
}
