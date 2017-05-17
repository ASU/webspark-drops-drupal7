<?php

/**
 * @file
 * Definition of views_handler_filter_membership_term_datetime.
 */

/**
 * A handler to filter on the membership term dates.
 */
class views_handler_filter_membership_term_datetime extends date_views_filter_handler_simple {
  function init(&$view, &$options) {
    parent::init($view, $options);
    $this->date_handler->date_type = DATE_DATETIME;
  }
}
