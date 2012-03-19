<?php
/**
 * @file
 * Implements Views integration: hours filter 
 */
// $Id: office_hours_handler_filter_hours.inc,v 1.1.2.1 2009/03/07 22:13:50 ozeuss Exp $

class office_hours_handler_filter_hours extends views_handler_filter_numeric {

  // Add a date handler to the filter.
  function construct() {
    parent::construct();
  }
  var $no_single = TRUE;/*
  function option_definition() {
    $options = parent::option_definition();

    $options['value'] = array(
      'contains' => array(
        'min' => array('default' => ''),
        'max' => array('default' => ''),
        'value' => array('default' => ''),
      ),
    );

    return $options;
  }
 
  /* function operators() {
    $operators = array(
      '<' => array(
        'title' => t('Is less than'),
        'method' => 'op_simple',
        'short' => t('<'),
        'values' => 1,
      ),
      '<=' => array(
        'title' => t('Is less than or equal to'),
        'method' => 'op_simple',
        'short' => t('<='),
        'values' => 1,
      ),
      '=' => array(
        'title' => t('Is equal to'),
        'method' => 'op_simple',
        'short' => t('='),
        'values' => 1,
      ),
      '!=' => array(
        'title' => t('Is not equal to'),
        'method' => 'op_simple',
        'short' => t('!='),
        'values' => 1,
      ),
      '>=' => array(
        'title' => t('Is greater than or equal to'),
        'method' => 'op_simple',
        'short' => t('>='),
        'values' => 1,
      ),
      '>' => array(
        'title' => t('Is greater than'),
        'method' => 'op_simple',
        'short' => t('>'),
        'values' => 1,
      ),
      'between' => array(
        'title' => t('Is between'),
        'method' => 'op_between',
        'short' => t('between'),
        'values' => 2,
      ),
      'not between' => array(
        'title' => t('Is not between'),
        'method' => 'op_between',
        'short' => t('not between'),
        'values' => 2,
      ),
    );
    return $operators;
  }
*/

/**
 * Provide a list of all the numeric operators
 */
/* function operator_options($which = 'title') {
    $options = array();
    foreach ($this->operators() as $id => $info) {
      $options[$id] = $info[$which];
    }

    return $options;
  }

  function operator_values($values = 1) {
    $options = array();
    foreach ($this->operators() as $id => $info) {
      if ($info['values'] == $values) {
        $options[] = $id;
      }
    }

    return $options;
  }
*/

/**
  * Provide the form
  */
function value_form(&$form, &$form_state) {
    $form['value']['#tree'] = TRUE;
    $opt = _create_hours_arr($field, FALSE);
    // We have to make some choices when creating this as an exposed
    // filter form. For example, if the operator is locked and thus
    // not rendered, we can't render dependencies; instead we only
    // render the form items we need.
    $which = 'all';
    if (!empty($form['operator'])) {
      $source = ($form['operator']['#type'] == 'radios') ? 'radio:options[operator]' : 'edit-options-operator';
    }

    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];

      if (empty($this->options['expose']['use_operator']) || empty($this->options['expose']['operator'])) {
        // exposed and locked.
        $which = in_array($this->operator, $this->operator_values(2)) ? 'minmax' : 'value';
      }
      else {
        $source = 'edit-' . drupal_clean_css_identifier($this->options['expose']['operator']);
      }
    }

   if ($which == 'all') {
      $form['value']['value'] = array(
        '#type' => 'select',
        '#title' => empty($form_state['exposed']) ? t('Choose hour') : '',
        //'#prefix' => t('<div class="form-item"><label>Filter by hours</label><p>Choose the hour to filter by working hours (\'between\') or closed hours(\'not between\')</p></div>'),
        '#default_value' => $this->value['value'],
        '#options' => $opt,
        '#process' => array('views_process_dependency'),
        '#dependency' => array($source => $this->operator_values(1)),
      );
      if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier]['value'])) {
        $form_state['input'][$identifier]['value'] = $this->value['value'];
      }
   }
    elseif ($which == 'value') {
      // When exposed we drop the value-value and just do value if
      // the operator is locked.
      $form['value'] = array(
        '#type' => 'select',
        '#title' => empty($form_state['exposed']) ? t('Choose hour') : '',
        '#default_value' => $this->value['value'],
        '#options' => $opt,
      );
      if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier])) {
        $form_state['input'][$identifier] = $this->value['value'];
      }
    }

    if ($which == 'all' || $which == 'minmax') {
      $form['value']['min'] = array(
        '#type' => 'select',
        '#title' => empty($form_state['exposed']) ? t('Choose hour') : '',
        '#default_value' => $this->value['min'],
        '#options' => $opt,
      );
      $form['value']['max'] = array(
         '#type' => 'select',
        '#title' => empty($form_state['exposed']) ? t('Choose hour') : '',
        '#default_value' => $this->value['max'],
        '#options' => $opt,  
      );
      if ($which == 'all') {
        $dependency = array(
          '#process' => array('views_process_dependency'),
          '#dependency' => array($source => $this->operator_values(2)),
        );
        $form['value']['min'] += $dependency;
        $form['value']['max'] += $dependency;
      }
      if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier]['min'])) {
        $form_state['input'][$identifier]['min'] = $this->value['min'];
      }
      if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier]['max'])) {
        $form_state['input'][$identifier]['max'] = $this->value['max'];
      }
    }
  }
  
}