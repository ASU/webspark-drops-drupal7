<?php
/**
 * @file
 *
 * Gigya reactions bar
 */



require_once drupal_get_path('module', 'gigya') . '/includes/gigya.field.inc';
$defaults = _gigya_field_info_formatter_default_settings('gigya_reactions_formatter_default');
$plugin = array(
  'single' => TRUE,
  'title' => t('Gigya Reactions Bar'),
  'description' => t('Shows Gigya Reactions bar.'),
  'category' => t('Gigya'),
  'edit form' => 'gigya_reactions_bar_pane_edit_form',
  'render callback' => 'gigya_reactions_bar_pane_render',
  'admin info' => 'gigya_reactions_bar_pane_admin_info',
  'required context' => array(new ctools_context_required(t('Choose the entity to pass as a context'), 'entity')),
  'defaults' => $defaults
);

/**
 * 'admin info' callback for panel pane.
 */
function gigya_reactions_bar_pane_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Shows Gigya Reactions Bar');
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function gigya_reactions_bar_pane_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form += gigya_field_formatter_settings_form(array('type' => 'gigya_reactions'), array('display' => array('default' => array('settings' => $conf))), 'default', $form, $form_state);
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
function gigya_reactions_bar_pane_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function gigya_reactions_bar_pane_render($subtype, $conf, $args, $context) {
  drupal_add_css(drupal_get_path('module', 'gigya') . '/css/gigya.css');
  drupal_add_js(drupal_get_path('module', 'gigya') . '/js/gigya_reactions.js');
  $defaults = _gigya_field_info_formatter_default_settings('gigya_reactions_formatter_default');
  if ($conf['gigya_reactions_override_default']) {
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
  $reactions = (string) str_replace(array("\r", "\r\n", "\n"), '', $conf['gigya_reactions_buttons']);
  $reactions = (string) preg_replace('/\s+/', ' ', $reactions);
  if (!empty($settings['gigya_reactions_override_default'])) {
    $defaults = array_filter($defaults);
    $settings += $defaults;
  }
  else {
    $settings = $defaults;
  }
  $reactions_settings = array(
    'gigyaReactions' => array(
      'reactions' => $reactions,
      'ua' => array(
        'title' => filter_xss(token_replace(ctools_context_keyword_substitute($settings['gigya_reactions_title'], array(), $ctx), array($entity_type => $entity))),
        'linkBack' => check_url(token_replace(ctools_context_keyword_substitute($settings['gigya_reactions_link_back'], array(), $ctx), array($entity_type => $entity))),
        'imageBhev' => $settings['gigya_reactions_image_behavior'],
        'imageUrl' => check_url(token_replace(ctools_context_keyword_substitute($settings['gigya_reactions_image_url'], array(), $ctx), array($entity_type => $entity))),
      ),
      'barID' => token_replace(ctools_context_keyword_substitute($settings['gigya_reactions_bar_id'], array(), $ctx), array($entity_type => $entity)),
      'containerID' => token_replace(ctools_context_keyword_substitute($settings['gigya_reactions_container_id'], array(), $ctx), array($entity_type => $entity)),
      'multipleReactions' => !empty($settings['gigya_reactions_multiple_reactions']) ? 'true' : 'false',
      'showCounts' => $settings['gigya_reactions_show_counts'],
      'layout' => $settings['gigya_reactions_layout'],
      'countType' => $settings['gigya_reactions_count_type'],
      'scope' => variable_get('gigya_reactions_af_scope', 'external'),
      'privacy' => variable_get('gigya_activety_feed_privacy', 'private'),
      'context' => array('id' => token_replace(ctools_context_keyword_substitute($settings['gigya_reactions_container_id'], array(), $ctx), array($entity_type => $entity))),
    ),
  );

  // Merge extra parameters.
  if (!empty($settings['gigya_reactions_advanced'])) {
    if (is_array($settings['gigya_reactions_advanced'])) {
      foreach ($settings['gigya_reactions_advanced'] as $key => $set) {
        $reactions_settings['gigyaReacations'][$key] = $set;
      }
    }
    else {
      $reactions_settings['gigyaReactions'] = array_merge($reactions_settings['gigyaReactions'], drupal_json_decode($settings['gigya_reactions_advanced']));
    }
  }

  // Allow other modules to modify global configuration.
  drupal_alter('gigya_reactions', $reactions_settings);
  $reactionbars['gigyaReactionsBars'][] = $reactions_settings;
  drupal_add_js($reactionbars, 'setting');
  $block->content = '<div id="' . $settings['gigya_reactions_container_id'] . '"></div>';
  return $block;
}
