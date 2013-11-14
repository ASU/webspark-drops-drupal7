<?php

/**
 * @file
 * Provides settings pages for the CAS LDAP module.
 */

/**
 * Lists available CAS Attributes.
 */
function cas_ldap_list() {
  $cas_attributes = variable_get('cas_attributes', array());

  if (empty($cas_attributes['ldap']['server'])) {
    // No CAS server configured.
    return t('An <a href="@url">LDAP server</a> must be selected.', array('@url' => url('admin/config/people/cas/attributes')));
  }
  $ldap_server = ldap_servers_get_servers($cas_attributes['ldap']['server'], 'enabled', TRUE);

  if (empty($ldap_server->testingDrupalUsername)) {
    return t('Please configure the LDAP server\'s <a href="@url">testing Drupal username</a>.', array('@url' => url('admin/config/people/ldap/servers/edit/' . $ldap_server->sid)));
  }

  $header = array('Token', 'Value');
  $rows = array();

  $attributes = cas_ldap_attributes($ldap_server->testingDrupalUsername);
  foreach ($attributes as $attribute => $value) {
    if (is_numeric($attribute)) {
      continue;
    }
    if (is_array($value)) {
      $value = $value[0];
    }
    $rows[] = array(
      t('[cas:ldap:@attribute]', array('@attribute' => drupal_strtolower($attribute))),
      check_plain($value),
    );
  }

  if (empty($rows)) {
    $rows[] = array(
      'data' => array(
        array(
          'data' => t('No LDAP attributes were returned by the LDAP server. Please ensure the <a href="@url">LDAP server</a> is configured correctly.', array('@url' => url('admin/config/people/ldap/servers/edit/' . $ldap_server->sid))),
          'colspan' => 2,
        ),
      ),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

