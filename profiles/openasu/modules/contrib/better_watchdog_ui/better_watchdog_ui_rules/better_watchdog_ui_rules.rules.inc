<?php

/**
 * @file
 * General better_watchdog_ui related rules integration.
 */

/**
 * Controller for generating Rules integration.
 */
class WatchdogRulesController {

  protected $type;
  protected $info;

  /**
   * Constructor.
   */
  public function __construct() {
    $this->type = 'better_watchdog_ui_watchdog';
    $this->info = entity_get_info('better_watchdog_ui_watchdog');
  }

  /**
   * Generate event related info.
   */
  public function eventInfo() {
    $type = $this->type;

    $defaults = array(
      'module' => 'better_watchdog_ui',
      'group' => 'Better Watchdog UI',
      'access callback' => 'access site reports',
    );

    $items['better_watchdog_ui_watchdog_view'] = $defaults + array(
      'label' => t('A watchdog entry is viewed'),
      'variables' => entity_rules_events_variables($type, t('viewed better_watchdog_ui_watchdog')),
    );
    $items['better_watchdog_ui_watchdog_create'] = $defaults + array(
      'label' => t('After saving a new watchdog entry'),
      'variables' => entity_rules_events_variables($type, t('created better_watchdog_ui_watchdog')),
    );
    $items['better_watchdog_ui_watchdog_before_delete'] = $defaults + array(
      'label' => t('Before deleting a watchdog entry'),
      'variables' => entity_rules_events_variables($type, t('before deleted better_watchdog_ui_watchdog')),
    );
    $items['better_watchdog_ui_watchdog_after_delete'] = $defaults + array(
      'label' => t('After deleting a watchdog entry'),
      'variables' => entity_rules_events_variables($type, t('after deleted better_watchdog_ui_watchdog')),
    );

    return $items;
  }

}

/**
 * Implements hook_rules_event_info().
 */
function better_watchdog_ui_rules_event_info() {
  $wd_info = entity_get_info('better_watchdog_ui_watchdog');
  $wd_rules_controller = new $wd_info['rules controller class']();
  return $wd_rules_controller->eventInfo();
}

/**
 * Implements hook_rules_condition_info().
 */
function better_watchdog_ui_rules_condition_info() {
  $conditions = array();

  $conditions['better_watchdog_ui_condition_watchdog_severity'] = array(
    'label' => t('Watchdog severity is'),
    'group' => t('Better Watchdog UI'),
    'parameter' => array(
      'better_watchdog_ui_watchdog' => array(
        'type' => 'better_watchdog_ui_watchdog',
        'label' => t('Watchdog'),
        'description' => t('Specifies the database log entry for which to evaluate the condition.'),
      ),
      'severity' => array(
        'type' => 'list<integer>',
        'label' => t('Severity'),
        'options list' => 'watchdog_severity_levels',
      ),
    ),
  );

  $conditions['better_watchdog_ui_condition_watchdog_type'] = array(
    'label' => t('Watchdog type is'),
    'group' => t('Better Watchdog UI'),
    'parameter' => array(
      'better_watchdog_ui_watchdog' => array(
        'type' => 'better_watchdog_ui_watchdog',
        'label' => t('Watchdog'),
        'description' => t('Specifies the database log entry for which to evaluate the condition.'),
      ),
      'type' => array(
        'type' => 'text',
        'label' => t('Type'),
        'description' => t('A list of types separated by either a newline or a comma.'),
      ),
    ),
  );

  $conditions['better_watchdog_ui_condition_watchdog_message'] = array(
    'label' => t('Watchdog message contains'),
    'group' => t('Better Watchdog UI'),
    'parameter' => array(
      'better_watchdog_ui_watchdog' => array(
        'type' => 'better_watchdog_ui_watchdog',
        'label' => t('Watchdog'),
        'description' => t('Specifies the database log entry for which to evaluate the condition.'),
      ),
      'message' => array(
        'type' => 'text',
        'label' => t('Message'),
        'description' => t('Newline separated list of text fragments to look for.'),
      ),
    ),
  );

  $conditions['better_watchdog_ui_condition_watchdog_uid'] = array(
    'label' => t('Watchdog user is'),
    'group' => t('Better Watchdog UI'),
    'parameter' => array(
      'better_watchdog_ui_watchdog' => array(
        'type' => 'better_watchdog_ui_watchdog',
        'label' => t('Watchdog'),
        'description' => t('Specifies the database log entry for which to evaluate the condition.'),
      ),
      'accounts' => array(
        'type' => 'text',
        'label' => t('User list'),
        'description' => t('Newline separated list of usernames.'),
        'optional' => TRUE,
      ),
      'include_anonymus' => array(
        'type' => 'text',
        'label' => t('Include anonymus?'),
        'options list' => '_better_watchdog_ui_yes_no_options_list',
        'default value' => 0,
      ),
    ),
  );

  $conditions['better_watchdog_ui_condition_watchdog_location'] = array(
    'label' => t('Watchdog location is'),
    'group' => t('Better Watchdog UI'),
    'parameter' => array(
      'better_watchdog_ui_watchdog' => array(
        'type' => 'better_watchdog_ui_watchdog',
        'label' => t('Watchdog'),
        'description' => t('Specifies the database log entry for which to evaluate the condition.'),
      ),
      'location' => array(
        'type' => 'text',
        'label' => t('Location'),
        'description' => t('Newline separated list of urls.'),
      ),
    ),
  );

  $conditions['better_watchdog_ui_condition_watchdog_referer'] = array(
    'label' => t('Watchdog referer is'),
    'group' => t('Better Watchdog UI'),
    'parameter' => array(
      'better_watchdog_ui_watchdog' => array(
        'type' => 'better_watchdog_ui_watchdog',
        'label' => t('Watchdog'),
        'description' => t('Specifies the database log entry for which to evaluate the condition.'),
      ),
      'referer' => array(
        'type' => 'text',
        'label' => t('referer'),
        'description' => t('Newline separated list of urls.'),
      ),
    ),
  );

  $conditions['better_watchdog_ui_condition_watchdog_hostname'] = array(
    'label' => t('Watchdog hostname is'),
    'group' => t('Better Watchdog UI'),
    'parameter' => array(
      'better_watchdog_ui_watchdog' => array(
        'type' => 'better_watchdog_ui_watchdog',
        'label' => t('Watchdog'),
        'description' => t('Specifies the database log entry for which to evaluate the condition.'),
      ),
      'hostname' => array(
        'type' => 'text',
        'label' => t('Hostname'),
        'description' => t('Newline separated list of hostnames.'),
      ),
    ),
  );

  return $conditions;
}

/**
 * Implements hook_rules_action_info().
 */
function better_watchdog_ui_rules_action_info() {
  $actions = array();

  $actions['better_watchdog_ui_action_add_watchdog'] = array(
    'label' => t('Add watchdog entry'),
    'group' => t('Better Watchdog UI'),
    'type' => 'better_watchdog_ui_watchdog',
    'configurable' => FALSE,
    'parameter' => array(
      'type' => array(
        'type' => 'text',
        'label' => t('Type'),
      ),
      'message' => array(
        'type' => 'text',
        'label' => t('Message'),
      ),
      'severity' => array(
        'type' => 'text',
        'label' => t('Severity'),
        'options list' => 'watchdog_severity_levels',
      ),
    ),
  );

  return $actions;
}

/**
 * Watchdog entry severity condition.
 */
function better_watchdog_ui_condition_watchdog_severity($better_watchdog_ui_watchdog, $severity) {
  return in_array($better_watchdog_ui_watchdog->getSeverity(), $severity);
}

/**
 * Watchdog entry type condition.
 */
function better_watchdog_ui_condition_watchdog_type($better_watchdog_ui_watchdog, $type) {
  $types_array = preg_split("/[\r\n,]+/", $type, -1, PREG_SPLIT_NO_EMPTY);
  return in_array($better_watchdog_ui_watchdog->getType(), $types_array);
}

/**
 * Watchdog entry message condition.
 */
function better_watchdog_ui_condition_watchdog_message($better_watchdog_ui_watchdog, $message) {
  $wd_message = $better_watchdog_ui_watchdog->getMessage();
  $messages_array = preg_split("/[\r\n]+/", $message, -1, PREG_SPLIT_NO_EMPTY);
  foreach ($messages_array as $message_fragment) {
    if (strpos($wd_message, $message_fragment) !== FALSE) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Watchdog entry user condition.
 */
function better_watchdog_ui_condition_watchdog_uid($better_watchdog_ui_watchdog, $accounts, $include_anonymus) {
  $account_array = preg_split("/[\r\n]+/", $accounts, -1, PREG_SPLIT_NO_EMPTY);
  $wd_uid = $better_watchdog_ui_watchdog->getUid();
  $wd_user = user_load($wd_uid);
  if ($include_anonymus && $wd_uid == 0) {
    return TRUE;
  }
  foreach ($account_array as $account_name) {
    if ($account_name == $wd_user->name) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Watchdog entry location condition.
 */
function better_watchdog_ui_condition_watchdog_location($better_watchdog_ui_watchdog, $location) {
  $location_array = preg_split("/[\r\n]+/", $location, -1, PREG_SPLIT_NO_EMPTY);
  foreach ($location_array as $location_fragment) {
    if (strpos($better_watchdog_ui_watchdog->getLocation(), $location_fragment) !== FALSE) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Watchdog entry referer condition.
 */
function better_watchdog_ui_condition_watchdog_referer($better_watchdog_ui_watchdog, $referer) {
  $referer_array = preg_split("/[\r\n]+/", $referer, -1, PREG_SPLIT_NO_EMPTY);
  foreach ($referer_array as $referer_fragment) {
    if (strpos($better_watchdog_ui_watchdog->getReferer(), $referer_fragment) !== FALSE) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Watchdog entry hostname condition.
 */
function better_watchdog_ui_condition_watchdog_hostname($better_watchdog_ui_watchdog, $hostname) {
  $hostname_array = preg_split("/[\r\n]+/", $hostname, -1, PREG_SPLIT_NO_EMPTY);
  $wd_hostname = $better_watchdog_ui_watchdog->getHostname();
  foreach ($hostname_array as $hostname_option) {
    if ($wd_hostname == $hostname_option) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Add a watchdog entry as action.
 */
function better_watchdog_ui_action_add_watchdog($type, $message, $severity) {
  watchdog($type, $message, array(), $severity);
}

/**
 * Simple yes/no dropdown options list for rules.
 */
function _better_watchdog_ui_yes_no_options_list() {
  return array(
    0 => t('No'),
    1 => t('Yes'),
  );
}
