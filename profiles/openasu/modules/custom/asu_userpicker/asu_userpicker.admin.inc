<?php

/**
 * @file
 * asu_userpicker.admin.inc - ASU Userpicker admin settings code.
 *
 * @author
 * Michael Samuelson <mlsamuel@asu.edu> / <mlsamuelson@gmail.com>
 *
 */

/**
 * Admin settings page/form.
 *
 */
function asu_userpicker_admin_settings($form, &$form_state) {

  // NOTE: A good general CAS and CAS Attributes setup page is available at
  // https://drupal.asu.edu/create/mapping-user-fields-cas-and-ldap-modules

  $intro = '<p>The ASU Userpicker module provides an AJAX autocomplete ';
  $intro .= 'userpicker widget which allows you to search by name and ';
  $intro .= 'ASURITE ID to select users within your Drupal site as well as ';
  $intro .= 'from ASU Solr or LDAP records.</p><p>If you select a user not yet in ';
  $intro .= 'your Drupal site, the userpicker creates the user when the ';
  $intro .= 'form is submitted.</p><p>This widget is easily assignable to ';
  $intro .= 'user reference fields using the Fields UI in Drupal and ';
  $intro .= 'is automatically setup for the ';
  $intro .= '<a href="@add_cas_user">Add CAS User form</a>. ';
  $intro .= 'ASU Userpicker requires the CAS Attributes, LDAP Servers and ';
  $intro .= 'User Reference modules to be enabled, and at least one LDAP ';
  $intro .= 'Server to be configured.</p>';

  // Intro
  $form['asu_userpicker_intro'] = array(
    '#title' => t('About the ASU Userpicker'),
    '#type' => 'item',
    '#markup' => t($intro, array('@add_cas_user' => url('admin/people/cas/create'))),
  );

  $setup = '<p>When installed, the ASU Userpicker module creates ';
  $setup .= 'an ASU Solr server configuration. If the ldap_servers module is ';
  $setup .= 'present and enabled at the time of install, then an ASU LDAP configuration will ';
  $setup .= 'be created also. In order to begin using the ';
  $setup .= 'userpicker with LDAP <strong>you must obtain an LDAP ';
  $setup .= 'application ID and password by emailing ';
  $setup .= '<a href="mailto:EDNATeam@asu.edu?subject=LDAP%20Application%20Account%20Request">EDNATeam@asu.edu</a>';
  $setup .= '</strong>. Please provide your site URLs and a brief ';
  $setup .= 'description of your project. Then update the ';
  $setup .= '"DN for non-anonymous search" and ';
  $setup .= '"Password for non-anonymous search" settings in the ';
  $setup .= '"Binding method" section of ';
  $setup .= '<a href="@server_conf">that server\'s configuration</a> ';
  $setup .= 'with the account credentials you receive.</p>';

  $form['asu_userpicker_setup'] = array(
    '#title' => t('Requesting an LDAP Account'),
    '#type' => 'item',
    '#markup' => t($setup, array('@server_conf' => url('admin/config/people/ldap/servers/edit/asu_ldap'))),
  );

  $form['asu_userpicker_solr_query_url'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('asu_userpicker_solr_query_url', 'https://asudir-solr.asu.edu/asudir/directory/select'),
    '#title' => t('ASU Solr Query URL'),
    '#description' => t('Provide the ASU Solr People Query URL. Probably https://asudir-solr.asu.edu/asudir/directory/select' ),
    '#required' => TRUE,
  );


  $options = array(
    'autocomplete/asu/user/solr' => 'Solr'
  );

  // If LDAP modules are present and enabled, then we add the option and the server config field
  if (asu_userpicker_has_ldap()) {
    // Get the skinny on the LDAP server to use. User should consult ldap_server
    // settings.
    $form['asu_userpicker_ldap_server'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('asu_userpicker_ldap_server', array()),
      '#title' => t('LDAP server machine name'),
      '#description' => t('Provide the machine name of the LDAP server to query.  ' . l('See LDAP servers available.', 'admin/config/people/ldap/servers')),
      '#required' => TRUE,
    );

    $options['autocomplete/asu/user'] = 'LDAP';
  }

  $form['asu_userpicker_service_default'] = array(
    '#type' => 'select',
    '#default_value' => variable_get('asu_userpicker_service_default', ASU_USERPICKER_SOLR_AUTOCOMPLETE_PATH),
    '#title' => t('Default Service'),
    '#description' => t('Use either the Solr or LDAP service by default for new ASU User Autocomplete field widgets.' ),
    '#options' => $options,
    '#required' => TRUE,
  );

  // We only want user fields, don't you know.
  $entity_type = 'user';
  $bundle = 'user';

  // When displaying the form, make sure the list of fields is up-to-date.
  if (empty($form_state['post'])) {
    field_info_cache_clear();
  }

  // General field info for reference.
  //$field_types = field_info_field_types();
  //$widget_types = field_info_widget_types();
  //$extra_fields = field_info_extra_fields($entity_type, $bundle, 'form');
  // All fields, execpt those used....
  //module_load_include('inc', 'field_ui', 'field_ui.admin');
  //$existing_fields = field_ui_existing_field_options($entity_type, $bundle);

  // Gather user entity, user bundle fields.
  $instances = field_info_instances($entity_type, $bundle);

  $field_options = array();
  foreach ($instances as $field_name => $info) {
    $text = t('@label (@field_name)', array(
      '@label' => $info['label'],
      '@field' => $info['field_name'],
    ));
    $field_options[$field_name] = truncate_utf8($text, 80, FALSE,
TRUE);
  }
  asort($field_options);

  $form['asu_userpicker_search_user_fields'] = array(
    '#type' => 'checkboxes',
    '#options' => $field_options,
    '#default_value' => variable_get('asu_userpicker_search_user_fields', array()),
    '#title' => t('User fields to search with ASU Userpicker widget'),
    '#description' => t('In addition to select LDAP / ASURITE values and local Drupal usernames and emails, the checked Drupal user fields will be consulted when using the ASU Userpicker'),
  );


  $advanced_setup = '<p>It is possible when new users are created via the ';
  $advanced_setup .= 'ASU Userpicker to automatically map the user\'s first ';
  $advanced_setup .= 'and last names to the user entity. To do this, setup ';
  $advanced_setup .= 'CAS Attribute mapping to user fields:</p>';
  $advanced_setup .= '<ol><li>Navigate to the ';
  $advanced_setup .= '<a href="@cas_attr_conf">CAS Attributes admin page</a>.';
  $advanced_setup .= '<br />Set the first name field to [cas:ldap:givenname].';
  $advanced_setup .= '<br />Set the last name field to [cas:ldap:sn]. </li>';
  $advanced_setup .= '<li>Map other LDAP attributes to your user fields as ';
  $advanced_setup .= 'necessary by using the [cas:ldap:?] tokens (see ';
  $advanced_setup .= '<a href="@cas_attr_tokens">CAS attribute tokens</a>).</li>';
  $advanced_setup .= '</ol>';
  $advanced_setup .= '<p>Do not set the Username and E-mail address fields ';
  $advanced_setup .= 'as those user fields will automatically get populated ';
  $advanced_setup .= 'by the CAS module when the user first logs in.</p>';

  $form['asu_userpicker_advanced_setup'] = array(
    '#title' => t('Automatic user attribute mappings'),
    '#type' => 'item',
    '#markup' => t($advanced_setup, array('@cas_attr_conf' => url('admin/config/people/cas/attributes'), '@cas_attr_tokens' => url('admin/config/people/cas/attributes/ldap'))),
  );

  return system_settings_form($form); 
}
