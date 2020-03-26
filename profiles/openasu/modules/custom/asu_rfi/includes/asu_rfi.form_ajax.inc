<?php

/**
 * Change of Major request form AJAX callback used to update specific AJAX fields listed below.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function asu_rfi_campus_ajax_callback($form, &$form_state) {

  /*
  dpm($form_state['values']['campus'], 'AJAX ' . __FUNCTION__ . ' - form_state=>campus');
  dpm($form['my_interest']['start_date']['#options'], 'AJAX ' . __FUNCTION__ . ' - form=>start_date - AJAX (before commands)');

  $commands = array(
    ajax_command_replace(
      "#asu-rfi-campus-ajax-wrapper .form-item-campus",
      render($form['my_interest']['campus'])),
    ajax_command_replace(
      "#asu-rfi-start-date-ajax-wrapper .form-item-start-date",
      render($form['my_interest']['start_date'])),
    );
  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
  */

  return $form['my_interest']['start_date'];
}
