<?php

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_table_plugin_style(&$vars) {
  template_preprocess_views_view_table($vars);

  $vars['responsive'] = $vars['options']['responsive'];

  $vars['classes_array'][] = 'table';

  foreach ($vars['options']['bootstrap_styles'] as $style) {
    $vars['classes_array'][] = 'table-' . $style;
  }
}
