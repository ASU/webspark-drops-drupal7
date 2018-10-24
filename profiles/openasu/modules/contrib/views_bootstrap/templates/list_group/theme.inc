<?php

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_list_group_plugin_style(&$vars) {
  $view = $vars['view'];
  $link_field = $vars['options']['link_field'];

  $vars['linked_items'] = !empty($link_field);

  foreach (array_keys($vars['rows']) as $key) {
    $vars['link_fields'][$key] = $view->style_plugin->get_field($key, $link_field);
  }
}
