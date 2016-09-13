<?php

/**
 * @file
 * Gigya Comments functionality.
 */

/**
 * Implements hook_form_BASE_FORM_ID_alter().
 */
function gigya_form_node_type_form_alter(&$form, $form_state) {
  if (isset($form['type'])) {
    $node_type = $form['type']['#default_value'];
    $default_cat = variable_get('gigya_comments_categoryid', '');
    $default_cont = variable_get('gigya_comments_container', 'comments');
    $form['comment']['gigya_comments_override_default'] = array(
      '#type' => 'checkbox',
      '#title' => t('Override default Gigya comments configuration'),
      '#description' => t('Override the default configuration as set in the gigya comments admin page'),
      '#default_value' => variable_get('gigya_comments_override_default_' . $node_type, FALSE),
    );
    $form['comment']['gigya_comments_categoryid'] = array(
      '#type' => 'textfield',
      '#title' => t('Gigya Comments category ID'),
      '#description' => t('Category as set up in the Gigya admin site.'),
      '#attributes' => array('placeholder' => 'category1'),
      '#default_value' => variable_get('gigya_comments_categoryid_' . $node_type, $default_cat),
      '#states' => array(
        'visible' => array(
          ':input[name="gigya_comments_override_default"]' => array('checked' => TRUE),
        ),
      ),
    );
    $form['comment']['gigya_comments_container'] = array(
      '#type' => 'textfield',
      '#title' => t('Container ID'),
      '#size' => 30,
      '#description' => t('The container ID that the comments will be displayed in the default is "comments" (Drupal default)'),
      '#default_value' => variable_get('gigya_comments_container_' . $node_type, $default_cont),
      '#states' => array(
        'visible' => array(
          ':input[name="gigya_comments_override_default"]' => array('checked' => TRUE),
        ),
      ),
    );
    $comments_extra_parms = variable_get('gigya_comments_extra_' . $node_type, array());
    $form['comment']['gigya_comments_extra'] = array(
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
  }
}

/**
 * Implements hook_form_BASE_FORM_ID_alter().
 */
function gigya_form_comment_form_alter(&$form, $form_state, $form_id) {
  // Add comments ui from here to be compatible with panels.
  gigya_add_comments_ui($form['#node']);
}

/**
 * Helper function to get the Gigya comments params for the Javascript.
 *
 * @param int $nid
 *   The node ID.
 *
 * @param string $type
 *   node type.
 *
 * @return array
 *   An associative array containing the comments parameters.
 */
function gigya_comments_ui_parmes($nid, $type) {

  // Get overrided state.
  $overrided = variable_get('gigya_comments_override_default_' . $type, FALSE);
  // Try to fetch type-specific category id. If unset, fetch default.
  $catid = variable_get('gigya_comments_categoryid_' . $type, NULL);
  if (!$catid || !$overrided) {
    $catid = variable_get('gigya_comments_categoryid', '');
  }
  // Try to fetch type-specific container id. If unset, fetch default.
  $cid = variable_get('gigya_comments_container_' . $type, NULL);
  if (!$cid || !$overrided) {
    $cid = variable_get('gigya_comments_container', 'comments');
  }
  $comments_params = array(
    'categoryID' => $catid,
    'streamID' => $nid,
    'containerID' => $cid,
    'scope' => variable_get('gigya_comments_af_scope', 'external'),
    'privacy' => variable_get('gigya_activety_feed_privacy', 'private'),
    'context' => array('id' => $cid),
    'version' => 2,
  );
  // Try to fetch type-specific extra parameters. If empty, fetch default.
  $extra_comments = variable_get('gigya_comments_extra_' . $type, array());
  if (empty($extra_comments)) {
    $extra_comments = variable_get('gigya_comments_extra', array());
  }
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
  return $comments_params;
}

/**
 * Add the Gigya comments UI.
 *
 * @param int $nid
 *   Node id.
 * @param string $type
 *   The node type.
 */
function gigya_comments_add_ui($nid, $type) {
  drupal_add_js(drupal_get_path('module', 'gigya') . '/js/gigya_comments.js', array(
      'type' => 'file',
      'scope' => 'footer',
    )
  );
  $parms = gigya_comments_ui_parmes($nid, $type);
  drupal_add_js(array('gigyaComments' => array('commentsUIparams' => $parms)), 'setting');
}

/**
 * Handles AJAX requests to the Gigya component.
 *
 * @return string
 *   A JSON string of the result.
 */
function gigya_comments_ajax() {
  if (user_access('post comments')) {
    $uid = filter_xss($_POST['uid']);
    $comment_text = filter_xss($_POST['commentText']);
    $nid = filter_xss($_POST['nid']);
    global $user;
    $comment['name'] = $user->name;
    $comment['nid'] = $nid;
    $comment['is_anonymous'] = 0;
    $comment['status'] = COMMENT_PUBLISHED;
    $comment['language'] = LANGUAGE_NONE;
    $comment['comment_body'] = array(
      LANGUAGE_NONE => array(
        0 => array(
          'value' => $comment_text,
          'format' => 'filtered_html',
        ),
      ),
    );
    $comm_obj = (object) $comment;
    $comm_obj = comment_submit($comm_obj);
    comment_save($comm_obj);
    return drupal_json_output(array('added' => TRUE));
  }
  return drupal_json_output(array('added' => FALSE));
}

/**
 * Adds the comments ui to the node.
 *
 * @param object $node
 *   Drupal node to add comments to.
 */
function gigya_add_comments_ui(&$node) {
  // Check if comments component is enabled.
  if (_gigya_is_component_enabled('comments') && empty($gigya_comments_ui_added)) {
    static $gigya_comments_ui_added = TRUE;
    // Add the comments ui.
    gigya_comments_add_ui($node->nid, $node->type);
    // Remove login link we have at in the gigya comment widget.
    unset($node->{'content'}['links']['comment']['#links']['comment_forbidden']);
  }
}
