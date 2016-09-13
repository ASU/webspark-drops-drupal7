<?php

/**
 * @file
 * Gigya rules for Drupal.
 *
 * Development of this module is sponsered by Gigya, Inc.
 */

/**
 * Implements hook_rules_action_info().
 *
 * On behalf of the system module.
 */
function gigya_rules_action_info() {
  return array(
    'gigya_share_action' => array(
      'label' => t('Gigya show share ui action'),
      'group' => t('Gigya'),
      'parameter' => array(
        'gigya_shareui_title' => array(
          'label' => t('Share title'),
          'type' => 'text',
        ),
        'gigya_shareui_desc' => array(
          'label' => t('Share description'),
          'type' => 'text',
        ),
        'gigya_shareui_link_back' => array(
          'label' => t('Share link back'),
          'type' => 'text',
        ),
        'gigya_shareui_image_behavior' => array(
          'label' => t('Share image behavior'),
          'type' => 'token',
          'default value' => variable_get('gigya_share_image_behavior', 'default'),
          'options list' => 'gigya_rules_image_behavior_options',
          'restriction' => 'input',
        ),
        'gigya_shareui_image_url' => array(
          'label' => t('Share image URL'),
          'type' => 'uri',
          'default value' => variable_get('gigya_share_image_url', ''),
          'optional' => TRUE,

        ),
      ),
      'base' => 'gigya_show_share_ui_action',
    ),
    'gigya_gm_action' => array(
      'label' => t('Gigya Game Mechanics action'),
      'group' => t('Gigya'),
      'parameter' => array(
        'gigya_action_name' => array(
          'label' => t('Action name'),
          'type' => 'text',
          'description' => t('Please select the action that would be submitted to gigya'),
          'options list' => 'gigya_get_gm_actions',
        )
      )
    ),
    'gigya_ci_action' => array(
      'label' => t('Notify Gigya Signal'),
      'group' => t('Gigya'),
      'parameter' => array(
        'gigya_ci_class' => array(
          'label' => t('Signal class'),
          'type' => 'text',
          'description' => t('Please select the signal class that would be submitted to gigya'),
          'options list' => 'gigya_get_counters_classes',
        ),
        'gigya_ci_path' => array(
          'label' => t('Signal path'),
          'type' => 'text',
          'description' => t('Please select the signal path that would be submitted to gigya'),
          'options list' => 'gigya_get_counters_paths',
        ),
        'gigya_ci_value' => array(
          'label' => t('Signal value'),
          'type' => 'integer',
          'description' => t('Please select the value of the signal that would be submitted to gigya'),
          'optional' => TRUE,
          'default_value' => 0
        ),
        'gigya_ci_count' => array(
          'label' => t('Signal count'),
          'type' => 'integer',
          'description' => t('Please select the count of the signal that would be submitted to gigya'),
          'optional' => TRUE,
          'default_value' => 1
        )
      )
    )
  );
}

/**
 * Adds the js to show the share popup.
 *
 * @param string $title
 *   The share title.
 * @param string $desc
 *   The share description.
 * @param string $link_back
 *   A  url that share will link back to.
 * @param string $image_bhv
 *   The way that the we would take the image from.
 * @param strin $image_url
 *   The image url.
 */
function gigya_show_share_ui_action($title, $desc, $link_back, $image_bhv, $image_url) {
  $shareui_params = array(
    'linkBack' => $link_back,
    'title' => $title,
    'description' => $desc,
    'imageBhev' => $image_bhv,
    'scope' => variable_get('gigya_share_af_scope', 'external'),
    'privacy' => variable_get('gigya_activety_feed_privacy', 'private'),
  );
  if ($image_bhv == 'url' && !empty($image_url)) {
    $shareui_params['imageUrl'] = $image_url;
  }
  // Allow other module to alter parmeters.
  drupal_alter('gigya_shareui', $shareui_params);
  drupal_add_js(array('gigya' => array('shareUIParams' => $shareui_params)), 'setting');
}

/**
 * Returns the options for image behavior.
 *
 * @return array
 *   An array of options for image behavior.
 */
function gigya_rules_image_behavior_options() {
  return array(
    'default' => t('Use image tag if exists, first image on post otherwise.'),
    'first' => t('First image on the post'),
    'url' => t('Specify an image url'),
  );
}

function gigya_gm_action($gigya_action_name) {
  if (user_is_logged_in()) {
    $login_mode = variable_get('gigya_login_mode', 'drupal_and_gigya');
    if (in_array($login_mode, array('drupal_and_gigya', 'gigya'))) {
      global $user;
      $params = array('UID' => $user->uid, 'action' => $gigya_action_name);
    }
    elseif ($login_mode == 'raas') {
      if (!empty($_SESSION['gigya_raas_uid'])) {
        $params = array('UID' => $_SESSION['gigya_raas_uid'], 'action' => $gigya_action_name);
      }
      else {
        watchdog('gigya', "failed to notify GM action user does not have a UID in the session", array(), WATCHDOG_ERROR);
      }
    }
    else {
      return;
    }
    drupal_alter('gigya_pre_gm_action', $params);
    $res = _gigya_api('gm.notifyAction', $params, TRUE);
    if (is_numeric($res)) {
      watchdog('gigya', "failed to notify GM action error code was @code", array("@code" => $res), WATCHDOG_ERROR);
    }
  }
}

function gigya_ci_action($ci_class, $ci_path, $ci_value, $ci_count) {
  if (user_is_logged_in()) {
    $params[] = array(
      'class' => $ci_class,
      'path' => $ci_path,
      'value' => $ci_value != NULL ? $ci_value : 0,
      'count' => $ci_count != NULL ? $ci_count : 1
    );
    drupal_alter('gigya_signal_alter', $params);
    $login_mode = variable_get('gigya_login_mode', 'drupal_and_gigya');
    $api_parmas = array();
    if (in_array($login_mode, array('drupal_and_gigya', 'gigya'))) {
      global $user;
      $api_parmas = array('UID' => $user->uid, 'counters' => json_encode($params));
    }
    elseif ($login_mode == 'raas') {
      if (!empty($_SESSION['gigya_raas_uid'])) {
        $api_parmas = array('UID' => $_SESSION['gigya_raas_uid'], 'counters' => json_encode($params));
      }
      else {
        watchdog('gigya', "failed to notify GM action user does not have a UID in the session", array(), WATCHDOG_ERROR);
      }
    }
    if (!empty($api_parmas)) {
      $res = _gigya_api('accounts.incrementCounters', $api_parmas, TRUE);
      if (is_numeric($res)) {
        watchdog('gigya', "failed to increment counter error code was " . $res, array(), WATCHDOG_ERROR);
      }
    }
  }
}

function gigya_get_counters_paths() {
  return gigya_get_registered_ci('paths');
}

function gigya_get_counters_classes() {
  return gigya_get_registered_ci('classes');
}


function gigya_get_registered_ci($type) {
  $from_gigya = array();
  $cache = cache_get('gigya_signals');
  if ($cache == FALSE) {
    $res = _gigya_api('accounts.getRegisteredCounters', NULL, TRUE);
    if (!is_numeric($res)) {
      $counters = $res['counters'];
      $paths = array();
      $classes = array();
      foreach ($counters as $ci) {
        $paths[] = $ci['path'];
        $classes[] = $ci['class'];
      }
      $from_gigya = array('paths' => $paths, 'classes' => $classes);
      cache_set('gigya_signals', $from_gigya);
    }
  }
  else {
    $from_gigya = $cache->data;
  }
  if ($type == 'paths') {
    $paths = array_merge($from_gigya['paths'], array('/'));
    $paths = drupal_map_assoc($paths);
    return $paths;
  }
  elseif ($type == 'classes') {
    $classes = array_merge($from_gigya['classes'], array(
        '_purchases',
        '_ad-click'
      )
    );
    $classes = drupal_map_assoc($classes);
    // remove pageviews
    if (isset($classes['_pageviews'])) {
      unset($classes['_pageviews']);
    }
    return $classes;
  }
  return array();
}


function gigya_get_gm_actions() {
  $gm_actions = _gigya_api('gm.getActionConfig', NULL, TRUE);
  if (!is_numeric($gm_actions)) {
    $actions = $gm_actions['actions'];
    foreach ($actions as $action) {
      $gigya_actions[$action['actionID']] = !empty($action['title']) ? $action['title'] : $action['actionID'];
    }
  }
  return $gigya_actions;
}
