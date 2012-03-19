<?php

/**
 * @file office_hours.elements.inc
 * Office hours form elements and their theming and validation.
 * This file is only included during the edit process to reduce memory usage.
 */

/**
 * Implementation of hook_elements().
 */

function _office_hours_elements() {
  return array(
    'office_hours' => array(
      '#input' => TRUE,
      '#tree' => TRUE,
      '#columns' => array('day', 'starthours', 'endhours'),
      '#process' => array('office_hours_field_process'),
      '#element_validate' => array('office_hours_validate'),
      '#theme' => 'office_hours',
    ),
    'office_hours_select' => array(
      '#input' => TRUE,
      '#tree' => TRUE,
      '#process' => array('office_hours_select_process'),
      '#element_validate' => array('office_hours_select_validate'),
      '#theme' => 'office_hours_select',
    ),
  );
}

/*
function office_hours_field_preprocess($vars) {
}
*/

/**
 * Process an individual element.
 *
 * Build the form element. When creating a form using FAPI #process,
 * note that $element['#value'] is already set.
 * The $fields array is in $form['#field_info'][$element['#field_name']].
 * D7 : in $form_state['field'][$element['#field_name']][$element['#language']]['field']
 */
function office_hours_field_process($element, &$form_state, $form) {
  drupal_add_js(drupal_get_path('module', 'office_hours') . "/office_hours.js", 'file');
  // test if the element is well placed in the array, switch element if not;
 /* if (is_array($element['#value'])) {
	if (isset($element['#value']['day']) and  $element['#value']['day'] != $element['#weight']) {
	$tmp = $form_state['complete form'][$element['#field_name']][$element['#language']][$element['#weight']];
	$tmp['#weight'] = $element['#value']['day'];
	$tmp['#delta'] = $element['#value']['day'];
	$form_state['complete form'][$element['#field_name']][$element['#language']][$element['#value']['day']]['#weight'] = $element['#weight'];
	$form_state['complete form'][$element['#field_name']][$element['#language']][$element['#value']['day']]['#delta'] = $element['#weight'];
	$form_state['complete form'][$element['#field_name']][$element['#language']][$element['#weight']] = $form_state['complete form'][$element['#field_name']][$element['#language']][$element['#value']['day']];
	$form_state['complete form'][$element['#field_name']][$element['#language']][$element['#value']['day']] = $tmp;
	$element = $form_state['complete form'][$element['#field_name']][$element['#language']][$element['#weight']];
	}}*/
  $day = $element['#weight'];
  $field = $form_state['field'][$element['#field_name']][$element['#language']]['field'];
  $day = ($day == 0) ? 0 : (($day & 1) ? ($day-1)/2 : $day/2);
  $field_day = $element['#columns'][0];
  $field_strhrs = $element['#columns'][1];
  $field_endhrs = $element['#columns'][2];
  $days = date_week_days_untranslated();
  if (!($element['#weight'] & 1)) { //first cell
    $element['#prefix'] = '<div class="office-hours-block"><div class="dayname">' . $days[$day] . '</div>';
  }
  elseif ($field['settings']['addhrs']) {  // second cell, we're supposed to show the 'add hours link'
    $link = l(t('Add more hours'), '', array('attributes' => array('class' => 'oh-add-more-link'))) . '<div class="office-hours-block" style = "display:none;">' . '<div class="dayname">' . t('and') . '</div>';
    $element['#prefix'] = isset($element['#value'][$field_strhrs]) ? '<div class="office-hours-block">' . '<div class="dayname">' . t('and') . '</div>' : $link;
  }
  else { //this is the second cell and were not showing it- better clear it (in case a value was entered before).
    $element['#prefix'] = "<div class='oh-hide'>";
    $element['#value'][$field_strhrs] = '';
  }
  $element['#suffix'] = '</div>';
  $element[$field_day] = array(
    '#type' => 'value',
    '#value' => $element['#weight'],
  );
  $element[$field_strhrs] = array(
    '#type' => 'office_hours_select',
    '#prefix' => t(' from'),
    '#default_hours' => isset($element['#value'][$field_strhrs]) ? $element['#value'][$field_strhrs] : '' ,
    '#granularity' => $field['settings']['granularity'],
    '#hoursformat' => $field['settings']['hoursformat'],
  );
  $element[$field_endhrs] = array(
    '#type' => 'office_hours_select',
    '#prefix' => t('until'),
    '#default_hours' => isset($element['#value'][$field_endhrs]) ? $element['#value'][$field_endhrs] : '',
    '#granularity' => $field['settings']['granularity'],
    '#hoursformat' => $field['settings']['hoursformat'],
  );

  $form_state['field'][$element['#field_name']][$element['#language']]['field']  = $field;

  return $element;
}

/**
 * Process the hours selector element.
 */
function office_hours_select_process($element, &$form_state, $form) {
  $ampm = 'am';
  $defhr = '';
  $defmin = '';
  if (is_numeric($element['#default_hours'])) {
    $hour = _office_hours_mil_to_tf($element['#default_hours']);
    list($defhr, $defmin) = explode(":", $hour);
    if ($element['#hoursformat']) {
      if ($defhr >= 12) {
        $defhr -= ($defhr != 12) ? 12 : 0;
        $ampm = 'pm';
      }
      elseif ($defhr == 0) {
        $defhr +=12;
      }
    }
    else {
      $defhr = str_pad($defhr, 2, '0', STR_PAD_LEFT);
    }
  }

  $hours = ($element['#hoursformat'] == 1) ? date_hours('g') : date_hours('H');
  $minutes = date_minutes('i', FALSE, $element['#granularity']);

  $element['hours'] = array(
    '#type' => 'select',
    '#options' => drupal_map_assoc($hours),
    '#default_value' => isset($defhr) ? $defhr : 0,
  );

  $element['minutes'] = array(
    '#type' => 'select',
    '#options' => drupal_map_assoc($minutes),
    '#default_value' => isset($defmin) ? $defmin : '',
  );
  if ($element['#hoursformat'] == 1) {
    $element['ampm'] = array(
      '#type' => 'select',
      '#options' => date_ampm(),
      '#default_value' => $ampm,
    );
  }
  return $element;
}

/**
 * Validate the hours selector element.
 */
function office_hours_select_validate($element, &$form_state) {
  //$hour = $element['#value']['hours'];
  $hour = $element['hours']['#value'];
  $minutes = ($element['minutes']['#value'] == 0) ? '00' : $element['minutes']['#value'];
  //$minutes = ($element['#value']['minutes'] == 0) ? '00' : $element['#value']['minutes'];
  if ($element['#hoursformat']) {
    if ($element['ampm']['#value'] == 'pm' && $hour < 12) $hour += 12;
    if ($element['ampm']['#value'] == 'am' && $hour == 12) $hour = '00';
  }
  if ($hour != '' && $minutes != '') {
    form_set_value($element, (string)$hour . $minutes, $form_state);
  }
  else {
     form_set_value($element, '', $form_state);
  }
  if ($hour < 0 || $hour > 23) {
    form_error($element, t('Hours should be between 0 and 23.'));
  }
  if ($minutes < 0 || $minutes > 59) {
    form_error($element, t('Minutes should be between 0 and 59.'));
  }
}

