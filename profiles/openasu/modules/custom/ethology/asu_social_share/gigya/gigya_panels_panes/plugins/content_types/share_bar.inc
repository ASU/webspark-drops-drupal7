<?php
/**
 * @file
 *
 * Gigya share bar
 */


require_once drupal_get_path('module', 'gigya') . '/includes/gigya.field.inc';
$defaults = _gigya_field_info_formatter_default_settings('gigya_sharebar_formatter_default');
$plugin = array(
  'single' => TRUE,
  'title' => t('Gigya Share Bar'),
  'description' => t('Shows Gigya Share bar.'),
  'category' => t('Gigya'),
  'edit form' => 'gigya_share_bar_pane_edit_form',
  'render callback' => 'gigya_share_bar_pane_render',
  'admin info' => 'gigya_share_bar_pane_admin_info',
  'required context' => array(new ctools_context_required(t('Entity'), 'entity')),
  'defaults' => $defaults
);

/**
 * 'admin info' callback for panel pane.
 */
function gigya_share_bar_pane_admin_info($subtype, $conf, $contexts) {
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
function gigya_share_bar_pane_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form += gigya_field_formatter_settings_form(array('type' => 'gigya_sharebar'), array('display' => array('default' => array('settings' => $conf))), 'default', $form, $form_state);
  $ctxs = array();
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
function gigya_share_bar_pane_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function gigya_share_bar_pane_render($subtype, $conf, $args, $context) {
  drupal_add_css(drupal_get_path('module', 'gigya') . '/css/gigya.css');
  drupal_add_js(drupal_get_path('module', 'gigya') . '/js/gigya_sharebar.js');
  $defaults = _gigya_field_info_formatter_default_settings('gigya_sharebar_formatter_default');
  if ($conf['gigya_sharebar_override_default']) {
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
  $share_settings = array(
    'gigyaSharebar' => array(
      'ua' => array(
        'linkBack' => filter_xss(token_replace(ctools_context_keyword_substitute($settings['gigya_sharebar_link_back'], array(), $ctx), array($entity_type => $entity))),
        'title' => filter_xss(token_replace(ctools_context_keyword_substitute($settings['gigya_sharebar_title'], array(), $ctx), array($entity_type => $entity))),
        'description' => filter_xss(token_replace(ctools_context_keyword_substitute($settings['gigya_sharebar_desc'], array(), $ctx), array($entity_type => $entity))),
        'imageBhev' => $settings['gigya_sharebar_image_behavior'],
        'imageUrl' => check_url(token_replace(ctools_context_keyword_substitute($settings['gigya_sharebar_image_url'], array(), $ctx), array($entity_type => $entity))),
      ),
      'shareButtons' => $settings['gigya_sharebar_buttons'],
      'shortURLs' => !empty($settings['gigya_sharebar_short_url']) ? 'always' : 'never',
      'containerID' => token_replace(ctools_context_keyword_substitute($settings['gigya_sharebar_container_id'], array(), $ctx), array($entity_type => $entity)),
      'showCounts' => $settings['gigya_sharebar_showcounts'],
      'layout' => $settings['gigya_sharebar_layout'],
    ),
  );
  // Allow other modules to modify global configuration.
  if (!empty($settings['gigya_sharebar_advanced'])) {
    if (is_array($settings['gigya_sharebar_advanced'])) {
      foreach ($settings['gigya_sharebar_advanced'] as $key => $set) {
        $share_settings['gigyaSharebar'][$key] = $set;
      }
    }
    else {
      $share_settings['gigyaSharebar'] = array_merge($share_settings['gigyaSharebar'], drupal_json_decode($settings['gigya_sharebar_advanced']));
    }
  }
  drupal_alter('gigya_sharebar', $share_settings);
  $sharebars['gigyaSharebars'][] = $share_settings;
  drupal_add_js($sharebars, 'setting');
  $block->content = '<div id="' . $settings['gigya_sharebar_container_id'] . '"></div>';
  return $block;
}
