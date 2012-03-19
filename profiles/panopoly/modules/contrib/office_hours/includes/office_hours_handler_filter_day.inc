<?php
/**
 * @file
 * Implements Views integration: day filter 
 */
// $Id: office_hours_handler_filter_day.inc,v 1.1.2.1 2009/03/07 22:13:50 ozeuss Exp $

class office_hours_handler_filter_day extends content_handler_filter_many_to_one {
  
  function construct() {
    parent::construct();
    $this->value_title = t('Day');
  }
  
  function get_value_options() {
    $this->value_options = array( t('Sunday'), t('Monday'), t('Tuesday'),  t('Wednesday'), t('Thursday'), t('Friday'), t('Saturday') );
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $options['operator']['default'] = 'or';
    $options['value']['default'] = array();
    return $options;
  }
  
  /**
   * Provide inclusive/exclusive matching
   */
  function operator_options() {
    return array(
      'in' => t('Is open on one of the following days'),
      'not in' => t('Is closed on one of the following days'),
    );
  }
 
   /**
   * Provide the form
   */
  function value_form(&$form, &$form_state) {
    $this->get_value_options();
    $options = $this->value_options;
    $default_value = (array) $this->value;

    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];

      if (!empty($this->options['expose']['reduce'])) {
        $options = $this->reduce_value_options();

        if (empty($this->options['expose']['single']) && !empty($this->options['expose']['optional'])) {
          $default_value = array();
        }
      }

      if (!empty($this->options['expose']['single'])) {
        if (!empty($this->options['expose']['optional']) && (empty($default_value) || !empty($this->options['expose']['reduce']))) {
          $default_value = 'All';
        }
        elseif (empty($default_value)) {
          $keys = array_keys($options);
          $default_value = array_shift($keys);
        }
        else {
          $copy = $default_value;
          $default_value = array_shift($copy);
        }
      }
    }

    $form['value'] = array(
      '#type' => $this->value_form_type,
      '#title' => $this->value_title,
      '#options' => $options,
      '#default_value' => $default_value,
      // These are only valid for 'select' type, but do no harm to checkboxes.
      '#multiple' => TRUE,
      '#size' => count($options) > 8 ? 8 : count($options),
    );

    if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier])) {
      $form_state['input'][$identifier] = $default_value;
    }

  }
   function ensure_my_table() {
    $this->helper->ensure_my_table();
  }

  function query() {
   if (empty($this->value)) {
      return;
    }
    $this->ensure_my_table();
    $placeholder = !empty($this->definition['numeric']) ? '%d' : "'%s'";

    $replace = array_fill(0, sizeof($this->value), $placeholder);
    $in = ' (' . implode(", ", $replace) . ')';

    // We use array_values() because the checkboxes keep keys and that can cause
    // array addition problems.
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field " . $this->operator . $in, array_keys($this->value));
  }
  
}