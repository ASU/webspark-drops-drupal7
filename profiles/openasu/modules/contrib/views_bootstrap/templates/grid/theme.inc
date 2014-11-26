<?php

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_grid_plugin_style(&$vars) {
  $view     = $vars['view'];
  $options  = $view->style_plugin->options;
  $horizontal = ($options['alignment'] === 'horizontal');

  $columns = $options['columns'];

  // Split items by rows and columns.
  $vars['items'] = _views_bootstrap_split_rows($vars, $columns, $horizontal);
  $vars['column_type'] = 12 / $columns;
}
