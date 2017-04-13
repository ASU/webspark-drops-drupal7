<?php

/**
 * @file
 * Page callbacks for viewing and deleting watchdog entities.
 */

/**
 * Callback for Watchdog entry title.
 */
function better_watchdog_ui_watchdog_title($watchdog) {
  return t('Details #!wid', array('!wid' => $watchdog->wid));
}

/**
 * Callback for Watchdog entry view.
 */
function better_watchdog_ui_watchdog_view($watchdog, $view_mode = 'full') {
  // Theme setup.
  $watchdog->content = array(
    '#theme' => 'better_watchdog_ui_watchdog',
    '#element' => $watchdog,
    '#view_mode' => $view_mode,
    '#language' => LANGUAGE_NONE,
  );

  // TYPE.
  $watchdog->content['type'] = array(
    '#type' => 'item',
    '#title' => t('Type'),
    '#markup' => $watchdog->type,
  );
  // DATE.
  $watchdog->content['timestamp'] = array(
    '#type' => 'item',
    '#title' => t('Date'),
    '#markup' => format_date($watchdog->timestamp),
  );
  // USER.
  $author = user_load($watchdog->uid);
  $watchdog->content['user'] = array(
    '#type' => 'item',
    '#title' => t('User'),
    '#markup' => theme('username', array('account' => $author)),
  );
  // LOCATION.
  $watchdog->content['location'] = array(
    '#type' => 'item',
    '#title' => t('Location'),
    '#markup' => l($watchdog->location, $watchdog->location),
  );
  // REFERER.
  $watchdog->content['referer'] = array(
    '#type' => 'item',
    '#title' => t('Referer'),
    '#markup' => l($watchdog->referer, $watchdog->referer),
  );
  // MESSAGE.
  $replacement = unserialize($watchdog->variables);
  $message = is_array($replacement) ? format_string($watchdog->message, $replacement) : $watchdog->message;
  $watchdog->content['message'] = array(
    '#type' => 'item',
    '#title' => t('Message'),
    '#markup' => $message,
  );
  // SEVERITY.
  $severity_level = watchdog_severity_levels();
  $watchdog->content['severity'] = array(
    '#type' => 'item',
    '#title' => t('Severity'),
    '#markup' => $severity_level[$watchdog->severity],
  );
  // HOSTNAME.
  $watchdog->content['hostname'] = array(
    '#type' => 'item',
    '#title' => t('Hostname'),
    '#markup' => $watchdog->hostname,
  );
  // OPERATIONS.
  $delete_form = drupal_get_form('better_watchdog_ui_watchdog_delete_form', $watchdog->wid);
  $watchdog->content['operations'] = array(
    '#type' => 'item',
    '#title' => t('Operations'),
    '#markup' => render($delete_form),
  );

  // Allow other modules to alter the watchdog event page.
  drupal_alter('better_watchdog_ui_event_page', $watchdog, $view_mode);

  if (module_exists('better_watchdog_ui_rules')) {
    rules_invoke_event('better_watchdog_ui_watchdog_view', $watchdog, $view_mode);
  }

  return $watchdog->content;
}

/**
 * Form for Watchdog entry deletion.
 */
function better_watchdog_ui_watchdog_delete_form($form, &$form_state, $watchdog) {
  $form = array();

  $form['watchdog'] = array(
    '#type' => 'hidden',
    '#value' => $watchdog,
  );

  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );

  return $form;
}

/**
 * Watchdog entity delete form submit.
 */
function better_watchdog_ui_watchdog_delete_form_submit($form, &$form_state) {
  better_watchdog_ui_watchdog_delete_multiple(array($form_state['values']['watchdog']));
  drupal_set_message(t('Entry #%wid deleted', array('%wid' => $form_state['values']['watchdog'])), 'status');
  $form_state['redirect'] = BETTER_WATCHDOG_UI_VIEW_PATH;
}
