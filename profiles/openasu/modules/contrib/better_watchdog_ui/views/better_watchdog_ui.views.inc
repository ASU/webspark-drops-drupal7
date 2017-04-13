<?php

/**
 * @file
 * Provide views field and filter handlers for better_watchdog_ui.module.
 */

/**
 * Implements hook_views_data_alter().
 */
function better_watchdog_ui_views_data_alter(&$data) {

  // Base table.
  $data['watchdog']['table'] = array(
    'base' => array(
      'field' => 'wid',
      'title' => t('Watchdog'),
      'help' => t('Table that contains logs of all system events.'),
      'weight' => 25,
    ),
    'group' => t('Watchdog'),
    'join' => array(
      'users' => array(
        'field' => 'uid',
        'left_field' => 'uid',
      ),
    ),
  );

  // --- FIELDS ---.
  // Watchdog WID.
  $data['watchdog']['wid'] = array(
    'title' => t('Wid'),
    'help' => t('Unique watchdog event ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'wid',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Watchdog UID.
  $data['watchdog']['uid'] = array(
    'title' => t('User'),
    'help' => t('The user who triggered the event.'),
    'field' => array(
      'handler' => 'better_watchdog_ui_handler_field_watchdog_uid',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'uid',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Watchdog TYPE.
  $data['watchdog']['type'] = array(
    'title' => t('Type'),
    'help' => t('Type of log message.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'type',
    ),
    'filter' => array(
      'handler' => 'better_watchdog_ui_handler_filter_watchdog_type',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Watchdog MESSAGE.
  $data['watchdog']['message'] = array(
    'title' => t('Message'),
    'help' => t('Text of log message.'),
    'field' => array(
      'handler' => 'better_watchdog_ui_handler_field_watchdog_message',
      'additional fields' => array('wid', 'variables'),
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'message',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Watchdog VARIABLES - not needed so far, included in watchdog message.
  // Watchdog SEVERITY.
  $data['watchdog']['severity'] = array(
    'title' => t('Severity'),
    'help' => t('The severity level of the event.'),
    'field' => array(
      'handler' => 'better_watchdog_ui_handler_field_watchdog_severity',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'severity',
    ),
    'filter' => array(
      'handler' => 'better_watchdog_ui_handler_filter_watchdog_severity',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Watchdog LINK.
  $data['watchdog']['link'] = array(
    'title' => t('Link'),
    'help' => t('Link to view the result of the event.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'link',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Watchdog LOCATION.
  $data['watchdog']['location'] = array(
    'title' => t('Location'),
    'help' => t('URL of the origin of the event.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'location',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Watchdog REFERER.
  $data['watchdog']['referer'] = array(
    'title' => t('Referer'),
    'help' => t('URL of referring page.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'referer',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Watchdog HOSTNAME.
  $data['watchdog']['hostname'] = array(
    'title' => t('Hostname'),
    'help' => t('Hostname of the user who triggered the event.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'hostname',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Watchdog TIMESTAMP.
  $data['watchdog']['timestamp'] = array(
    'title' => t('Timestamp'),
    'help' => t('Unix timestamp of when event occurred.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
      'name field' => 'timestamp',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_query_alter().
 */
function better_watchdog_ui_views_query_alter(&$view, &$query) {
  if ($view->name == 'better_watchdog_ui_view') {
    // Add order by entity ID as a second ordering. Show latest entries,
    // except when table order is by date.
    if ($query->orderby[0]['field'] == 'watchdog_timestamp') {
      $order_direction = $query->orderby[0]['direction'];
    }
    else {
      $order_direction = 'DESC';
    }
    $query->orderby[] = array(
      'field' => 'wid',
      'direction' => $order_direction,
    );
  }
}
