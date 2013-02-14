<?php

/**
 * @file
 * A panel plugin to provide administrative information about the site's panes
 */

$plugin = array(
  'title' => t('General Panes'),
  'description' => t('This is list of the panes that are generally available on the site.'),
  'content_types' => array('general_panes'),
  'category' => t('Admin'),
  'required context' => new ctools_context_required(t('Panopoly Admin'), 'string'),
  'single' => TRUE,
);

/**
  * Put the output for you pages type in the blocks pages.
  */
function panopoly_admin_general_panes_content_type_render($subtype, $conf, $panel_args, $context) {

  // Get the pane settings and modify accordingly
  ctools_include('common', 'panels');
  ctools_include('plugins', 'panels');
  ctools_include('content');
  $content_types =  ctools_content_get_all_types();
  $header = array(
    array('data' => '', 'style' => 'width: 16px'), 
    array('data' => t('Category'), 'style' => 'width: 15%'),
    array('data' => t('Title')), 
    array('data' => t('Status'), 'style' => 'width: 20%'),
  );

  // Build the data for the different panes
  $plugin_data = array();
  $panels_page_allowed_types = variable_get('panels_page_allowed_types');
  foreach (ctools_content_get_all_types() as $category_name => $category) {
    foreach ($category as $plugin_name => $plugin) {
      $category_label = (is_string($plugin['category'])) ? $plugin['category'] : $plugin['category'][0];
      $category_label = ($category_label == 'Custom') ? 'Global' : $category_label; // Call all custom plugins "Global"
      $plugin_status = (!empty($panels_page_allowed_types[$category_name . '-' . $plugin_name])) ? _panopoly_admin_general_panes_get_status($plugin_name, $category_name, 'enable') : _panopoly_admin_general_panes_get_status($plugin_name, $category_name, 'disable');

      // Only show plugins that are general (no context)
      if (empty($plugin['required context'])) {
        $plugin_data[$category_label . '::' . $plugin_name] = array(
          theme('image', array('path' => ctools_content_admin_icon($plugin))),
          $category_label,
          $plugin['title'],
          $plugin_status,
        );
      }
    } 
  }

  // Create the Output
  ksort($plugin_data);
  $pane->content .= theme('table', array('header' => $header, 'rows' => $plugin_data));
  return $pane;
}
