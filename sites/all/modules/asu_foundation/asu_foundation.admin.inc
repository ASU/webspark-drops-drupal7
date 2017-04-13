<?php

function cybersource_admin_settings($form, &$form_state) 
{
  $form = array();
  $form['cybersource_server_mode'] = array(
    '#type' => 'radios',
    '#title' => 'CyberSource Server Mode',
    '#options' => array(
      'Live' => t('Live'),
      'Test' => t('Test'),
    ),
    '#description' => t('CyberSource transaction mode. If you change this, CyberSource may no longer function correctly.'),
    '#default_value' => variable_get('cybersource_server_mode', 'Test'),
  );

  return system_settings_form($form);
}
