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
    foreach ($vars['view']->result as $key => $field) {
      $vars['tabs'][$key] = strip_tags($view->style_plugin->get_field($key, $tab_field));
    }
  }
}
