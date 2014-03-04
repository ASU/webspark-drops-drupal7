<?php

/**
 * @file
 * Provides settings pages for the CAS Attributes module.
 */

/**
 * Administrative settings form.
 */
function cas_attributes_admin_settings() {

  $form['cas_attributes_sync_every_login'] = array(
    '#type' => 'radios',
    '#title' => t('Fetch CAS Attributes'),
    '#default_value' => variable_get('cas_attributes_sync_every_login', NULL),
    '#options' => array(
      0 => 'only when a CAS account is created (i.e., the first login of a CAS user).',
      1 => 'every time a CAS user logs in.'
    ),
    '#weight' => -10,
  );

  $form['cas_attributes_overwrite'] = array(
    '#type' => 'radios',
    '#title' => t('Overwrite existing values'),
    '#default_value' => variable_get('cas_attributes_overwrite', TRUE),
    '#options' => array(
      0 => 'only store data from attributes for fields that are empty (don\'t overwrite user fields that already have data).',
      1 => 'always store data from attributes (overwrite user fields that already have data).',
    ),
    '#weight' => -9,
  );

  $relations = variable_get('cas_attributes_relations', array());
  $form['cas_attributes_relations'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('CAS attribute mappings'),
  );

  $form['cas_attributes_relations']['help'] = array(
    '#markup' => t('Token replacement strings used to populate each <a href="@url">user field</a>?  Only text fields are eligible to be populated.  Entries left blank will be ignored.', array('@url' => url('admin/config/people/accounts/fields'))),
  );

  // Provide fields for username and e-mail address.
  $form['cas_attributes_relations']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => isset($relations['name']) ? $relations['name'] : '',
    '#size' => 50,
    '#description' => t('The account username.'),
  );
  $form['cas_attributes_relations']['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#default_value' => isset($relations['mail']) ? $relations['mail'] : '',
    '#size' => 50,
    '#description' => t('The account e-mail address.'),
  );

  // Provide fields for fields attached to the user bundle.
  foreach (field_info_instances('user', 'user') as $name => $instance) {
    $field = field_info_field($instance['field_name']);
    if ($field['type'] == 'text') {
      $form['cas_attributes_relations'][$name] = array(
        '#type' => 'textfield',
        '#title' => t($instance['label']),
        '#default_value' => isset($relations[$name]) ? $relations[$name] : '',
        '#size' => 50,
        '#description' => t('The account field with name %field_name.', array('%field_name' => $instance['field_name'])),
      );
    }
  }

  // Role Management
  $form['cas_attributes_roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role Mapping'),
    '#access' => user_access('administer permissions'),
    '#description' => t('You may choose to manage assignment of one or more of the roles on this Drupal site based on the values of certain CAS attributes. ' .
      'Only the roles you select to manage will be affected.  Managed roles will be assigned or revoked whenever a user logs in thru CAS (regardless of how you set the ' .
      '"Overwrite existing values" setting above).<br>' .
      'For each managed role: if the role name is present in at least one of the attributes you specify, ' .
      'the role will be granted to the user.  If the role name is not present in any of the attributes, it will be removed from the user.<br>' .
      'Roles must be specified by name (not by numeric ID, since that is site specific).<br>'),
  );

  $roles = user_roles(TRUE);
  unset($roles[DRUPAL_AUTHENTICATED_RID]);
  asort($roles);

  $form['cas_attributes_roles']['cas_attributes_roles_manage'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles to manage'),
    '#description' => t('Which roles should be managed by these attributes.'),
    '#default_value' => variable_get('cas_attributes_roles_manage', array()),
    '#options' => $roles,
  );

  $form['cas_attributes_roles']['cas_attributes_roles_mapping'] = array(
    '#type' => 'textarea',
    '#title' => t('Attributes'),
    '#description' => t('List the names of the CAS attributes which may ' .
      'contain names of the managed roles.  List one attribute per line - ' .
      'for example, <strong>department</strong> or <strong>affiliations' .
      '</strong>. Do not use token syntax, as it will not be processed. ' .
      'If the name of a managed role is present in at least one of these ' .
      'attributes, that role will be given to the user; otherwise, it will ' .
      'be taken away.'),
    '#default_value' => variable_get('cas_attributes_roles_mapping', ''),
  );

  $form['token_tree'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('cas'),
    '#global_types' => FALSE,
  );

  return system_settings_form($form);
}

/**
 * Lists available CAS Attributes.
 */
function cas_attributes_list() {
  cas_phpcas_load();
  cas_phpcas_init();

  phpCAS::forceAuthentication();
  $attributes = phpCAS::getAttributes();

  $header = array('Token', 'Value');
  $rows = array();

  foreach ($attributes as $attribute => $value) {
    if (is_array($value)) {
      $value = $value[0];
    }
    $rows[] = array(
      t('[cas:attribute:@attribute]', array('@attribute' => drupal_strtolower($attribute))),
      check_plain($value),
    );
  }

  if (empty($rows)) {
    $rows[] = array(
      'data' => array(
        array(
          'data' => t('No CAS attributes were returned by the CAS server.'),
          'colspan' => 2,
        ),
      ),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}
