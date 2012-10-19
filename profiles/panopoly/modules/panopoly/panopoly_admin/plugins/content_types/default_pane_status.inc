<?php

/**
 * @file
 * A panel plugin to provide administrative information about the site's pane default status
 */

$plugin = array(
  'title' => t('Default Pane Status'),
  'description' => t('This is list of the pane types and their default status.'),
  'content_types' => array('default_pane_status'),
  'category' => t('Admin'),
  'required context' => new ctools_context_required(t('Panopoly Admin'), 'string'),
  'single' => TRUE,
);

/**
  * Put the output for you pages type in the blocks pages.
  */
function panopoly_admin_default_pane_status_content_type_render($subtype, $conf, $panel_args, $context) {

  // Get the default pane status
  $panels_page_default = variable_get('panels_page_default');
  $content_types = ctools_get_content_types();
  $content_types['other']['title'] = t('Content of other types');
  $header = array(
    array('data' => t('Title')), 
    array('data' => t('Status'), 'style' => 'width: 40%'),
  );
  $rows = array();

  foreach ($panels_page_default as $plugin_type => $plugin_type_status) {
    $rows[] = array(
      $content_types[$plugin_type]['title'],
      (!empty($plugin_type_status)) ? _panopoly_admin_plugin_type_get_status($plugin_type, 'enable') : _panopoly_admin_plugin_type_get_status($plugin_type, 'disable'),
    );
  }

  $pane->title = t('Default Pane Status');
  $pane->content = theme('table', array('header' => $header, 'rows' => $rows));
  return $pane;
  return $pane;
}
