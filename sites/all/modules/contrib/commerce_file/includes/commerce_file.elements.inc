<?php

/**
 * @file
 * Commerce File form elements
 */

define('COMMERCE_FILE_LIMIT_INHERITED', '-1');
define('COMMERCE_FILE_LIMIT_UNLIMITED', 'UNLIMITED');

/**
 * Implements hook_element_info().
 */
function commerce_file_element_info() {
  $types = array();

  // A limit integer textfield
  $types['commerce_file_limit_integer'] = array(
    '#input' => TRUE,
    '#tree' => TRUE,
    '#pre_render' => array('form_pre_render_conditional_form_element'),
    '#value_callback' => 'commerce_file_limit_integer_element_value',
    '#process' => array('commerce_file_limit_integer_element_process'),
    '#element_validate' => array('commerce_file_limit_integer_element_validate'),
    '#limit_inherited_value' => NULL,
    '#default_value' => array(
      'mode' => COMMERCE_FILE_LIMIT_UNLIMITED,
      'value' => '',
    ),
  );


  // A limit duration form element which represents the duration in seconds.
  $types['commerce_file_limit_duration'] = array(
    '#input' => TRUE,
    '#tree' => TRUE,
    '#pre_render' => array('form_pre_render_conditional_form_element'),
    '#value_callback' => 'commerce_file_limit_duration_element_value',
    '#process' => array('commerce_file_limit_duration_element_process'),
    '#element_validate' => array('commerce_file_limit_duration_element_validate'),
    '#limit_inherited_value' => NULL,
    '#default_value' => array(
      'mode' => COMMERCE_FILE_LIMIT_UNLIMITED,
      'value' => '',
    ),
  );

  return $types;
}


/**
 * Return keyed array of limit mode options
 */
function _commerce_file_limit_element_get_mode_options($element, $inherited_format_callback = '') {
  $options = array(
    COMMERCE_FILE_LIMIT_UNLIMITED => t('Unlimited'),
    'value' => t('Custom value'),
  );

  // prepend inherited option
  if (isset($element['#limit_inherited_value'])) {
    $inherited_value = $element['#limit_inherited_value'];
    if (!empty($inherited_format_callback)) {
      $inherited_value = $inherited_format_callback($inherited_value);
    }

    $options = array(
      COMMERCE_FILE_LIMIT_INHERITED => t('Inherited (@inherited)', array('@inherited' => $inherited_value)),
    ) + $options;
  }

  return $options;
}


// -----------------------------------------------------------------------
// Limit Textfield

/**
 * FAPI process callback for limit textfield element type.
 */
function commerce_file_limit_integer_element_process($element, &$form_state) {
  // Put the child elements in a container div.
  $element['#prefix'] = isset($element['#field_prefix']) ? $element['#field_prefix'] : '';
  $element['#prefix'] = '<div class="commerce-file-limit-integer-element commerce-file-limit-element">' . $element['#prefix'];
  unset($element['#field_prefix']);

  // move description to the top
  if (isset($element['#description'])) {
    $element['description'] = array(
      '#markup' => '<div class="description">' . $element['#description'] . '</div>',
      '#weight' => -10,
    );
    unset($element['#description']);
  }

  // close container
  $element['#suffix'] = isset($element['#field_suffix']) ? $element['#field_suffix'] : '';
  $element['#suffix'] .= '</div>';
  unset($element['#field_suffix']);

  // attach css
  $element['#attached']['css'][] = drupal_get_path('module', 'commerce_file') . '/css/commerce_file.forms.css';

  // build limit mode and value
  $element['#mode_options'] = _commerce_file_limit_element_get_mode_options($element);
  $defaults = _commerce_file_limit_element_get_defaults($element);

  $element['mode'] = array(
    '#type' => 'radios',
    '#options' => $element['#mode_options'],
    '#default_value' => $defaults['mode'],
    '#attributes' => array('class' => array('commerce-file-limit-element-mode')),
  );

  $element['value'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => $defaults['value'],
    '#attributes' => array('class' => array('commerce-file-limit-element-value')),
    '#states' => array(
      'visible' => array(
        ':input[name="' . $element['#name'] . '[mode]"]' => array('value' => 'value'),
      ),
    ),
  );


  return $element;
}

/**
 * FAPI element validate callback for limit textfield element type.
 */
function commerce_file_limit_integer_element_validate($element, &$form_state) {
  $data = $element['#value'];
  $value = NULL;

  if (empty($data)) {
    return;
  }

  if ($data['mode'] == 'value') {
    // process entered value
    $value = $data['value'];

    // validate as not empty here since #required on value would require for all modes
    if (_commerce_file_element_value_is_empty($value)) {
      form_error($element, t('%name field is required.', array('%name' => $element['#title'])));
      return;
    }

    // validate as positive integer or 0
    if (!_commerce_file_is_integer_or_zero($value)) {
      form_error($element, t('%name must be a positive integer or zero.', array('%name' => $element['#title'])));
      return;
    }

    // ensure integer value stored
    $value = intval($value);
  }
  else {
    // set value to the mode key
    $value = $data['mode'];
  }


  // Consolidate into one value.
  form_set_value($element, $value, $form_state);
}

/**
 * FAPI value callback for limit textfield element type.
 */
function commerce_file_limit_integer_element_value($element, $input = FALSE, $form_state = array()) {
  return _commerce_file_limit_element_value($element, $input, $form_state);
}


// -----------------------------------------------------------------------
// Limit Duration

/**
 * FAPI process callback for limit textfield element type.
 */
function commerce_file_limit_duration_element_process($element, &$form_state) {
  // Put the child elements in a container div.
  $element['#prefix'] = isset($element['#field_prefix']) ? $element['#field_prefix'] : '';
  $element['#prefix'] = '<div class="commerce-file-limit-duration-element commerce-file-limit-element">' . $element['#prefix'];
  unset($element['#field_prefix']);

  // move description to the top
  if (isset($element['#description'])) {
    $element['description'] = array(
      '#markup' => '<div class="description">' . $element['#description'] . '</div>',
      '#weight' => -10,
    );
    unset($element['#description']);
  }

  // close container
  $element['#suffix'] = isset($element['#field_suffix']) ? $element['#field_suffix'] : '';
  $element['#suffix'] .= '</div>';
  unset($element['#field_suffix']);

  // attach css
  $element['#attached']['css'][] = drupal_get_path('module', 'commerce_file') . '/css/commerce_file.forms.css';

  // build limit mode and value
  $element['#mode_options'] = _commerce_file_limit_element_get_mode_options($element, '_commerce_file_limit_format_interval');
  $defaults = _commerce_file_limit_element_get_defaults($element);

  $element['mode'] = array(
    '#type' => 'radios',
    '#options' => $element['#mode_options'],
    '#default_value' => $defaults['mode'],
    '#attributes' => array('class' => array('commerce-file-limit-element-mode')),
  );

  $default_value = NULL;
  $default_unit = 86400;
  if (isset($defaults['value'])) {
    // split into value and unit of greatest divisor
    list($default_value, $default_unit) = _commerce_file_limit_duration_element_explode_value($defaults['value']);
  }

  $element['value'] = array(
    '#type' => 'container',
    'value' => array(
      '#type' => 'textfield',
      '#size' => 10,
      '#default_value' => $default_value,
      '#element_validate' => array('_commerce_file_element_validate_integer_positive_or_zero'),
    ),
    'unit' => array(
      '#type' => 'select',
      '#default_value' => $default_unit,
      '#options' => _commerce_file_limit_duration_element_units(),
    ),
    'description' => array(
      '#markup' => '<div class="description">' . t('Enter an integer value or zero.<br/>Months are based on 30 days.') . '</div>',
    ),
    '#attributes' => array('class' => array('commerce-file-limit-element-value container-inline')),
    '#states' => array(
      'visible' => array(
        ':input[name="' . $element['#name'] . '[mode]"]' => array('value' => 'value'),
      ),
    ),
  );


  return $element;
}

/**
 * FAPI element validate callback for limit integer element type.
 */
function commerce_file_limit_duration_element_validate($element, &$form_state) {
  $data = $element['#value'];
  $value = NULL;

  if (empty($data)) {
    return;
  }

  if ($data['mode'] == 'value') {
    // process entered value
    $duration = $data['value'];

    // validate as not empty here since #required on value would require for all modes
    if (!isset($duration['value']) || _commerce_file_element_value_is_empty($duration['value'])) {
      form_error($element, t('%name field is required.', array('%name' => $element['#title'])));
      return;
    }

    // set seconds to store
    $value = $duration['value'];
    if (!empty($duration['unit'])) {
      $value *= $duration['unit'];
    }

    // ensure integer value stored
    $value = intval($value);
  }
  else {
    // set value to the mode key
    $value = $data['mode'];
  }


  // Consolidate into one value.
  form_set_value($element, $value, $form_state);
}

/**
 * FAPI value callback for limit duration element type.
 */
function commerce_file_limit_duration_element_value($element, $input = FALSE, $form_state = array()) {
  return _commerce_file_limit_element_value($element, $input, $form_state);
}

/**
 * Defines possible duration multipliers.
 */
function _commerce_file_limit_duration_element_units() {
  $units = &drupal_static(__FUNCTION__);
  if (!isset($units)) {
    $units = array(
      365*86400 => t('years'),
      30*86400 => t('months'),
      7*86400 => t('weeks'),
      86400 => t('days'),
      3600 => t('hours'),
      60 => t('minutes'),
      1 => t('seconds'),
    );
  }

  return $units;
}

/**
 * Returns an array of scalar value, greatest unit multiplier
 */
function _commerce_file_limit_duration_element_explode_value($value) {
  if (!is_scalar($value)) {
    return array();
  }

  $unit = _commerce_file_limit_duration_element_greatest_unit($value);
  return array($value / $unit, $unit);
}

/**
 * Returns the greatest unit multiplier that yields an integer value
 */
function _commerce_file_limit_duration_element_greatest_unit($value) {
  $units = _commerce_file_limit_duration_element_units();
  foreach ($units as $multiplier => $label) {
    if ($multiplier && ($value % $multiplier == 0)) {
      return $multiplier;
    }
  }

  // fallback to seconds
  return 1;
}


// -----------------------------------------------------------------------
// Limit Helpers

/**
 * FAPI value callback for limit element types.
 */
function _commerce_file_limit_element_value($element, $input = FALSE, $form_state = array()) {
  if ($input !== FALSE) {
    return $input;
  }

  $return = array();

  $mode_options = _commerce_file_limit_element_get_mode_options($element);
  $default_value = isset($element['#default_value']) ? $element['#default_value'] : COMMERCE_FILE_LIMIT_UNLIMITED;

  if (is_scalar($default_value) && isset($mode_options[$default_value])) {
    $return['mode'] = $default_value;
    $return['value'] = '';
  }
  else {
    $return['mode'] = 'value';
    $return['value'] = $default_value;
  }

  return $return;
}

/**
 * Returns an array of defaults for the given element
 */
function _commerce_file_limit_element_get_defaults($element) {
  $defaults = array('mode' => COMMERCE_FILE_LIMIT_UNLIMITED, 'value' => NULL);
  if (isset($element['#default_value'])) {
    if (is_array($element['#default_value'])) {
      $defaults = $element['#default_value'] + $defaults;
    }
    elseif (isset($element['#mode_options'][$element['#default_value']])) {
      $defaults['mode'] = $element['#default_value'];
    }
    else {
      $defaults['mode'] = 'value';
      $defaults['value'] = $element['#default_value'];
    }
  }

  return $defaults;
}

/**
 * Returns TRUE if the limit is inherited
 */
function _commerce_file_limit_is_inherited($value) {
  return strcmp($value, COMMERCE_FILE_LIMIT_INHERITED) === 0;
}

/**
 * Returns TRUE if the limit is unlimited
 */
function _commerce_file_limit_is_unlimited($value) {
  return strcmp($value, COMMERCE_FILE_LIMIT_UNLIMITED) === 0;
}

/**
 * Returns limit formatted as an interval with consideration for UNLIMITED
 */
function _commerce_file_limit_format_interval($interval, $granularity = 2, $langcode = NULL) {
  if (_commerce_file_limit_is_unlimited($interval) || _commerce_file_limit_is_inherited($interval)) {
    return $interval;
  }

  return format_interval($interval, $granularity, $langcode);
}
