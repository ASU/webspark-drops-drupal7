<?php

/**
 * @file
 * Definition of views_handler_field_membership_term_datetime.
 */

/**
 * Field handler for membership term dates.
 */
class views_handler_field_membership_term_datetime extends views_handler_field_date {
  /**
   * {@inheritdoc}
   */
  function construct() {
    parent::construct();
    $this->additional_fields['mid'] = 'mid';
    $this->additional_fields['timezone'] = 'timezone';
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['timezone'] = array(
      '#type' => 'value',
      '#value' => 'UTC',
    );
  }

  /**
   * {@inheritdoc}
   */
  public function get_value($values, $field = NULL) {
    $value = parent::get_value($values, $field);
    if (empty($field) || $field == $this->real_field) {
      $date = new DateObject($value, 'UTC');
      return $date->format('U');
    }
    return $value;
  }

  /**
   * {@inheritdoc}
   */
  function render($values) {
    // Load the membership object and settings.
    if ($mid = $this->get_value($values, 'mid')) {
      $type = db_query("SELECT type FROM {membership_entity} WHERE mid = :mid", array(':mid' => $mid))->fetchColumn();
      $bundle_settings = membership_entity_get_bundle_settings($type);

      // Force timezone to respect membership type settings.
      $this->options['timezone'] = date_get_timezone($bundle_settings['tz_handling'], $this->get_value($values, 'timezone'));
      return parent::render($values);
    }
  }
}
