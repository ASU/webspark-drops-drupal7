<?php

/**
 * @file
 * Definition of better_watchdog_ui_handler_field_watchdog_message.
 */

/**
 * Provides message display options for the watchdog entry.
 *
 * @ingroup views_field_handlers
 */
class better_watchdog_ui_handler_field_watchdog_message extends views_handler_field {

  /**
   * Option to link message to entry.
   */
  public function option_definition() {

    $options = parent::option_definition();

    $options['link_to_watchdog'] = array('default' => TRUE, 'bool' => TRUE);

    return $options;
  }

  /**
   * Link to watchdog option form.
   */
  public function options_form(&$form, &$form_state) {
    $form['link_to_watchdog'] = array(
      '#title' => t('Link this field to the watchdog entry'),
      '#description' => t("Enable to override this field's links."),
      '#type' => 'checkbox',
      '#default_value' => $this->options['link_to_watchdog'],
    );
    parent::options_form($form, $form_state);
  }

  /**
   * Render the field.
   */
  public function render($values) {
    $message = $this->get_value($values);
    $variables = unserialize($this->get_value($values, 'variables'));

    $data = is_array($variables) ? format_string($message, $variables) : $message;

    $wid = $this->get_value($values, 'wid');

    if (!empty($this->options['link_to_watchdog'])) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = BETTER_WATCHDOG_UI_DETAIL_PATH . '/' . $wid;
    }

    return $data;
  }
}
