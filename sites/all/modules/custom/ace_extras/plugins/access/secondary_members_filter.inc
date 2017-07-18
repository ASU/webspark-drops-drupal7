<?php

/**
 * Plugin for checking access based on Membership Entity modules in commerce
 */

$plugin = array(
  'title' => t('Secondary Membership filter'),
  'description' => t('Block access to users with secondary membership accounts'),
  'callback' => 'ace_extras_secondary_member_access_check',
  'default' => array('negate' => 0),
  'settings form' => 'ace_extras_secondary_member_access_settings',
  'summary' => 'ace_extras_secondary_member_summary'
);

/**
 * Settings form for the 'term depth' access plugin.
 */
function ace_extras_secondary_member_access_settings($form, &$form_state, $conf) {
  return $form;
}

/**
 * Provide a summary description.
 */
function ace_extras_secondary_member_summary($conf, $context) {
  return t('Block access to Secondary Membership accounts in Commerce');
}

/**
 * Access check - Block all secondary members (return FALSE)
 */
function ace_extras_secondary_member_access_check($conf, $context) {
  if (ace_extras_secondary_member_access_filter()) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}