<?php

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_tab_plugin_style(&$vars) {
  $view = &$vars['view'];
  $tab_field = $vars['options']['tab_field'];

  $vars['tab_type'] = $vars['options']['tab_type'];
  $vars['justified'] = $vars['options']['justified'];

  // Get tabs.
  if (isset($view->field[$tab_field])) {
    foreach (array_keys($vars['rows']) as $key) {
      $vars['tabs'][$key] = $view->style_plugin->get_field_value($key, $tab_field);
    }
  }

  $keys = array_keys($vars['rows']);
  $vars['first_key'] = reset($keys);
}
