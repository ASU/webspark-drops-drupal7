<?php

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_thumbnail_plugin_style(&$vars) {
  $view     = $vars['view'];
  $options  = $view->style_plugin->options;
  $horizontal = ($options['alignment'] === 'horizontal');

  $columns = $options['columns'];

  // Split items by rows and columns.
  $vars['items'] = _views_bootstrap_split_rows($vars, $columns, $horizontal);
  $vars['column_type'] = 12 / $columns;
}

/**
 * Implementation of template preprocess for the view fields.
 */
function template_preprocess_views_bootstrap_thumbnail_plugin_rows(&$vars) {
  $view = &$vars['view'];

  foreach ($vars['options'] as $id => $field) {
    switch ($id) {
      case 'image':
      case 'title':
        if (isset($view->field[$field])) {
          $vars[$id] = $view->style_plugin->get_field($view->row_index, $field);
        }
        break;

      case 'content':
        $vars[$id] = array();
        foreach (array_filter($field) as $content_field) {
          if (isset($view->field[$content_field])) {
            $vars[$id][$content_field] = $view->style_plugin->get_field($view->row_index, $content_field);
          }
        }
        break;
    }
  }
}
