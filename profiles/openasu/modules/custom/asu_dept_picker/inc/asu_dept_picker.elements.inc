<?php

function _asu_dept_picker_elements() {
  return array(
    'asu_dept_picker' => array(
      '#input' => TRUE,
      '#process' => array('_asu_dept_picker_element_process'),
      '#element_validate' => array('_asu_dept_picker_element_validate'),
      '#theme' => array('asu_dept_picker'),
      '#theme_wrappers' => array('form_element'),
    ),
  );
}


function _asu_dept_picker_element_process($element, &$form_state, $complete_form) {
  return $element;
}


function _asu_dept_picker_element_validate($element, &$form_state) {
  
  $data = json_decode($element['#value']);
  if (json_last_error() != JSON_ERROR_NONE) {
    form_error($element, t('The department configuration is malformed.'));
  }

  // Required check
  if ($element['#required']) {
    if (empty($element['#value']) || empty($data->items)) {
      form_error($element, t('The department field is required.'));
    }
  }

  return $element;
}
