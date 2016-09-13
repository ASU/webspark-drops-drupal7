<?php
/**
 * @file
 *
 * Gigya comments
 */

$defaults = array(
  'gigya_comments_categoryid' => variable_get('gigya_comments_categoryid', ''),
  'gigya_comments_container' => variable_get('gigya_comments_container', 'comments'),
  'gigya_comments_override_default' => FALSE,
  'gigya_comments_stream_id' => "st1",
  'gigya_comments_extra' => ""
);
$plugin = array(
  'single' => TRUE,
  'title' => t('Gigya Comments'),
  'description' => t('Shows Comments.'),
  'category' => t('Gigya'),
  'edit form' => 'gigya_comments_pane_edit_form',
  'render callback' => 'gigya_comments_pane_render',
  'admin info' => 'gigya_comments_pane_admin_info',
  'required context' => array(new ctools_context_optional(t('Entity'), 'entity')),
  'defaults' => $defaults
);


/**
 * 'admin info' callback for panel pane.
 */
function gigya_comments_pane_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Shows Gigya comments');
    return $block;
  }
}

function gigya_comments_pane_edit_form($form, $form_state) {
  $conf = $form_state['conf'];
  $form['gigya_comments_override_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override default Gigya comments configuration'),
    '#description' => t('Override the default configuration as set in the gigya comments admin page'),
    '#default_value' => isset($conf['gigya_comments_override_default']) ? $conf['gigya_comments_override_default'] : FALSE,

  );
  $form['gigya_comments_stream_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Gigya Comments stream ID'),
    '#description' => t('The stream ID from this comment instance.'),
    '#required' => TRUE,
    '#default_value' => isset($conf['gigya_comments_stream_id']) ? $conf['gigya_comments_stream_id'] : "st1"
  );
  $form['gigya_comments_categoryid'] = array(
    '#type' => 'textfield',
    '#title' => t('Gigya Comments category ID'),
    '#description' => t('Category as set up in the Gigya admin site.'),
    '#attributes' => array('placeholder' => 'category1'),
    '#default_value' => isset($conf['gigya_comments_categoryid']) ? $conf['gigya_comments_categoryid'] : "" ,
    '#states' => array(
      'visible' => array(
        ':input[name="gigya_comments_override_default"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['gigya_comments_container'] = array(
    '#type' => 'textfield',
    '#title' => t('Container ID'),
    '#size' => 30,
    '#description' => t('The container ID that the comments will be displayed in the default is "comments" (Drupal default)'),
    '#default_value' => isset($conf['gigya_comments_container']) ? $conf['gigya_comments_container'] : "",
    '#states' => array(
      'visible' => array(
        ':input[name="gigya_comments_override_default"]' => array('checked' => TRUE),
      ),
    ),
  );
  $comments_extra_parms = isset($conf['gigya_comments_extra']) ? $conf['gigya_comments_extra'] : array();
  $form['gigya_comments_extra'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showCommentsUI settings'),
    '#rows' => 5,
    '#element_validate' => array('gigya_key_val_filed_validate'),
    '#description' => t('Enter values in key|value format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/020_Methods/socialize.showCommentsUI', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
      )
    ),
    '#default_value' => !empty($comments_extra_parms) ? gigya_values_array_to_string($comments_extra_parms) : '',
    '#states' => array(
      'visible' => array(
        ':input[name="gigya_comments_override_default"]' => array('checked' => TRUE),
      ),
    ),
  );

  return $form;
}


/**
 * The submit form stores the data in $conf.
 */
function gigya_comments_pane_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function gigya_comments_pane_render($subtype, $conf, $args, $context) {
  $defaults = array(
    'gigya_comments_categoryid' => variable_get('gigya_comments_categoryid', ''),
    'gigya_comments_container' => variable_get('gigya_comments_container', 'comments'),
    'gigya_comments_stream_id' => $conf['gigya_comments_stream_id']
  );
  if ($conf['gigya_comments_override_default']) {
    $settings = $conf;
    $defaults = array_filter($defaults);
    $settings += $defaults;
  }
  else {
    $settings = $defaults;
  }
  $block = new stdClass();
  if ($conf['override_title']) {
    $block->title = t($conf['override_title_text']);
  }
  $comments_params = array(
    'categoryID' => ctools_context_keyword_substitute($settings['gigya_comments_categoryid'], array(), $context),
    'streamID' => ctools_context_keyword_substitute($settings['gigya_comments_stream_id'], array(), $context),
    'containerID' => ctools_context_keyword_substitute($settings['gigya_comments_container'], array(), $context),
    'scope' => variable_get('gigya_comments_af_scope', 'external'),
    'privacy' => variable_get('gigya_activety_feed_privacy', 'private'),
    'context' => array('id' => $settings['gigya_comments_container']),
    'version' => 2,
  );
  // Try to fetch type-specific extra parameters. If empty, fetch default.
  $extra_comments = isset($settings['gigya_comments_extra']) ? $settings['gigya_comments_extra'] : variable_get('gigya_comments_extra', array());
  // Merge in extra parameters, if any were found.
  if (!empty($extra_comments)) {
    if (is_array($extra_comments)) {
      foreach ($extra_comments as $key => $parm) {
        $comments_params[$key] = $parm;
      }
    }
    else {
      $comments_params = array_merge($comments_params, drupal_json_decode($extra_comments));
    }
  }
  // Allow modules to alter the object before adding the JS to the page.
  drupal_alter('gigya_comments', $comments_params);
  drupal_add_js(drupal_get_path('module', 'gigya') . '/js/gigya_comments.js', array(
    'type' => 'file',
    'scope' => 'footer',
  ));
  drupal_add_js(array('gigyaComments' => array('commentsUIparams' => $comments_params)), 'setting');
  $block->content = '<div id="' . $settings['gigya_comments_container'] . '"></div>';
  return $block;
}
