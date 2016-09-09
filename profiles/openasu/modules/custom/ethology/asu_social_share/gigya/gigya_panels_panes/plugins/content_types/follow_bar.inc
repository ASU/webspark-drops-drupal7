<?php
/**
 * @file
 *
 * Gigya follow bar
 */

require_once drupal_get_path('module', 'gigya') . '/includes/gigya.field.inc';
$defaults = _gigya_field_info_formatter_default_settings('gigya_follow_bar_formatter_default');
$plugin = array(
  'single' => TRUE,
  'title' => t('Gigya Follow Bar'),
  'description' => t('Shows Gigya Follow bar.'),
  'category' => t('Gigya'),
  'edit form' => 'gigya_follow_bar_pane_edit_form',
  'render callback' => 'gigya_follow_bar_pane_render',
  'admin info' => 'gigya_follow_bar_pane_admin_info',
  'required context' => array(new ctools_context_required(t('Entity'), 'entity')),
  'defaults' => $defaults
);

/**
 * 'admin info' callback for panel pane.
 */
function gigya_follow_bar_pane_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Shows Gigya Share bar');
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function gigya_follow_bar_pane_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form += gigya_field_formatter_settings_form(array('type' => 'gigya_follow_bar'), array('display' => array('default' => array('settings' => $conf))), 'default', $form, $form_state);
  foreach ($form_state['contexts'] as $ctx) {
    $ctxs[] = $ctx->keyword;
  }
  $token_list = theme('token_tree', array('token_types' => $ctxs, 'global_types' => FALSE));
  $form['tokens_list']['#markup'] = $token_list;
  return $form;
}


/**
 * The submit form stores the data in $conf.
 */
function gigya_follow_bar_pane_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function gigya_follow_bar_pane_render($subtype, $conf, $args, $context) {
  drupal_add_css(drupal_get_path('module', 'gigya') . '/css/gigya.css');
  drupal_add_js(drupal_get_path('module', 'gigya') . '/js/gigya_follow_bar.js');
  $defaults = _gigya_field_info_formatter_default_settings('gigya_follow_bar_formatter_default');
  if ($conf['gigya_follow_bar_override_default']) {
    $settings = $conf;
    $defaults = array_filter($defaults);
    $settings += $defaults;
  }
  else {
    $settings = $defaults;
  }
  $ctx = reset($context);
  $entity_type = $ctx->keyword;
  $entity = $ctx->data;
  $block = new stdClass();
  if ($conf['override_title']) {
    $block->title = t($conf['override_title_text']);
  }
  $follow_bar = (string) str_replace(array("\r", "\r\n", "\n"), '', $settings['gigya_follow_bar_buttons']);
  $follow_bar = (string) preg_replace('/\s+/', ' ', $follow_bar);
  $follow_bar_settings = array(
    'gigyaFollowBar' => array(
      'follow_bar' => token_replace(ctools_context_keyword_substitute($follow_bar, array(), $ctx), array($entity_type => $entity)),
      'containerID' => token_replace(ctools_context_keyword_substitute($settings['gigya_follow_bar_container_id'], array(), $ctx), array($entity_type => $entity)),
      'layout' => $settings['gigya_follow_bar_layout'],
      'context' => array('id' => token_replace(ctools_context_keyword_substitute($settings['gigya_follow_bar_container_id'], array(), $ctx), array($entity_type => $entity))),
    )
  );

  // Merge extra parameters.
  if (!empty($settings['gigya_follow_bar_advanced'])) {
    if (is_array($settings['gigya_follow_bar_advanced'])) {
      foreach ($settings['gigya_follow_bar_advanced'] as $key => $set) {
        $follow_bar_settings['gigyaFollowBar'][$key] = $set;
      }
    }
    else {
      $follow_bar_settings['gigyaFollowBar'] = array_merge($follow_bar_settings['gigyaFollowBar'], drupal_json_decode($settings['gigya_follow_bar_advanced']));
    }
  }
  // Allow other modules to modify global configuration.
  drupal_alter('gigya_follow_bar', $follow_bar_settings);
  $followbars['gigyaFollowBars'][] = $follow_bar_settings;
  drupal_add_js($followbars, 'setting');
  $block->content = '<div id="' . $settings['gigya_follow_bar_container_id'] . '"></div>';
  return $block;
}
