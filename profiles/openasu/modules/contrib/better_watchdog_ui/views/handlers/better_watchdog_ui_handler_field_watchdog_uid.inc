<?php

/**
 * @file
 * Definition of better_watchdog_ui_handler_field_watchdog_uid.
 */


/**
 * Provides user display options for the watchdog entry.
 *
 * @ingroup views_field_handlers
 */
class better_watchdog_ui_handler_field_watchdog_uid extends views_handler_field_user {

  /**
   * Render uid as plain username or link .
   */
  public function render_link($data, $values) {

    $author = user_load($data);
    if (!empty($this->options['link_to_user']) || !$data) {
      if (!$author) {
        $author = (object) array('uid' => 0);
      }
      $author->wid = $values->wid;
      $author->severity = $values->watchdog_severity;
      $author->type = $values->watchdog_type;
      $author->timestamp = $values->watchdog_timestamp;
      $author->message = $values->watchdog_message;
      $author->variables = $values->watchdog_variables;
      $data = theme('username', array('account' => $author));
    }
    else {
      $data = format_username($author);
    }

    return $data;
  }

}
