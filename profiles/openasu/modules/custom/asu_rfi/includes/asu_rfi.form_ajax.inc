<?php

/**
 * AJAX callback to update desired campus, start term <select> form fields
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function asu_rfi_program_ajax_callback($form, &$form_state) {
  $commands = array(
    ajax_command_replace(
      "#asu-rfi-campus-ajax-wrapper",
      render($form['my_interest']['campus'])),
    ajax_command_replace(
      "#asu-rfi-start-date-ajax-wrapper",
      render($form['my_interest']['start_date'])),
  );
  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
  //  return $form['my_interest']['campus'];
}

/**
 * AJAX callback to update desired start term <select> form field
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function asu_rfi_campus_ajax_callback($form, &$form_state) {
  $commands = array(
    ajax_command_replace(
      "#asu-rfi-start-date-ajax-wrapper",
      render($form['my_interest']['start_date'])),
  );
  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
  //  return $form['my_interest']['start_date'];
}
