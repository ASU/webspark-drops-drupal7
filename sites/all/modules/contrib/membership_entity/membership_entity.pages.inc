<?php

/**
 * @file
 * Page callbacks for membership entities.
 */

/**
 * Form builder: membership settings form.
 */
function membership_entity_settings_form($form, &$form_state, $data = array()) {
  $form['#attached'] = array(
    'css' => array(drupal_get_path('module', 'membership_entity') . '/css/membership_entity_admin.css'),
  );

  if (empty($data)) {
    $data = membership_entity_get_bundle_settings();
  }
  $form['#data'] = $data;

  $form['membership_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Membership options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $member_id_plugins = membership_entity_get_member_id();
  $options = array();
  foreach ($member_id_plugins as $id => $plugin) {
    $options[$id] = '<div class="membership-entity-radio-label">' . check_plain($plugin['title']) . '<br /><small>' . check_plain($plugin['description']) . '</small></div>';
  }
  $wrapper_id = 'membership-entity-settings-wrapper';

  $default_format = !empty($form_state['membership_entity']['member_id_format']) ? $form_state['membership_entity']['member_id_format'] : $data['member_id_format'];
  $form['membership_settings']['member_id_format'] = array(
    '#type' => 'radios',
    '#title' => t('Member ID Format'),
    '#options' => $options,
    '#default_value' => $default_format,
    '#required' => TRUE,
    '#element_validate' => array('membership_entity_member_id_format_validate'),
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'membership_entity_settings_ajax',
      'wrapper' => $wrapper_id,
      'effect' => 'fade',
    ),
  );

  $form['membership_settings']['member_id_settings'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#element_validate' => array('membership_entity_member_id_settings_validate'),
    '#attributes' => array(
      'id' => $wrapper_id,
      'class' => array('membership-entity-member-id-settings'),
    ),
  );

  $handler = _membership_entity_member_id_get_instance($default_format, $data['member_id_settings']);
  $settings_form = $handler->settingsForm($form_state);
  if (!empty($settings_form)) {
    $form['membership_settings']['member_id_settings']['#type'] = 'fieldset';
    $form['membership_settings']['member_id_settings']['#title'] = t('Member ID Settings');
    $form['membership_settings']['member_id_settings'] += $settings_form;
  }

  $form['membership_settings']['member_id_submit'] = array(
    '#type' => 'submit',
    '#name' => 'member_id_submit',
    '#value' => t('Change plugin'),
    '#limit_validation_errors' => array(),
    '#attributes' => array('class' => array('js-hide')),
    '#submit' => array('membership_entity_settings_ajax_submit'),
  );

  $form['user_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Member options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['user_settings']['cardinality'] = array(
    '#type' => 'select',
    '#title' => t('Number of users per membership'),
    '#options' => array(
      FIELD_CARDINALITY_UNLIMITED => t('Unlimited'),
      '1' => t('1'),
      '2' => t('2'),
      '3' => t('3'),
      '4' => t('4'),
      '5' => t('5'),
      '6' => t('6'),
      '7' => t('7'),
      '8' => t('8'),
      '9' => t('9'),
      '10' => t('10'),
    ),
    '#default_value' => $data['cardinality'],
    '#description' => t('Select the number of users that may belong to a single membership of this type. (Including the primary member.)'),
  );

  $roles = user_roles(TRUE);
  $form['user_settings']['primary_role'] = array(
    '#title' => t('Primary member role'),
    '#type' => 'select',
    '#options' => $roles,
    '#default_value' => $data['primary_role'],
    '#required' => TRUE,
    '#description' => t('Select the role that will be assigned to the primary member when the membership is active.'),
  );

  $form['user_settings']['secondary_role'] = array(
    '#title' => t('Secondary member role'),
    '#type' => 'select',
    '#options' => array('primary' => 'Same as primary member') + $roles,
    '#default_value' => ($data['secondary_role'] == $data['primary_role']) ? 'primary' : $data['secondary_role'],
    '#description' => t('Select the role that will be assigned to secondary members when the membership is active.'),
    '#states' => array(
      'invisible' => array(
        ':input[name="cardinality"]' => array('value' => '1'),
      ),
    ),
  );

  $form['user_settings']['show_on_profile'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display membership information on the user profile.'),
    '#default_value' => $data['show_on_profile'],
  );

  $form['user_settings']['all_edit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow secondary members to edit the membership.'),
    '#default_value' => $data['all_edit'],
    '#description' => t('If not checked, only the primary member will be able to edit membership fields.'),
    '#states' => array(
      'invisible' => array(
        ':input[name="cardinality"]' => array('value' => '1'),
      ),
    ),
  );

  $form['#validate'][] = 'membership_entity_settings_form_validate';
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#submit' => array('membership_entity_settings_form_submit'),
  );

  // Allow other modules to add settings to the form.
  drupal_alter('membership_entity_settings', $form, $form_state, $data);
  return $form;
}

/**
 * Element validate callback for the member id format.
 */
function membership_entity_member_id_format_validate(&$element, &$form_state, $form) {
  $trigger = $form_state['triggering_element'];
  if ($trigger['#name'] == 'member_id_format') {
    $form_state['membership_entity']['member_id_format'] = $trigger['#value'];
  }
}

/**
 * Element validate callback or member id settings.
 */
function membership_entity_member_id_settings_validate(&$element, &$form_state, $form) {
  $values = $form_state['values'];
  if ($instance = _membership_entity_member_id_get_instance($values['member_id_format'], $values['member_id_settings'])) {
    $instance->validateSettings($element, $form_state);
  }
}

/**
 * Ajax callback for the settings form.
 */
function membership_entity_settings_ajax($form, &$form_state) {
  return $form['membership_settings']['member_id_settings'];
}

/**
 * Ajax callback for the settings form.
 */
function membership_entity_settings_ajax_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Validate handler for the settings form.
 */
function membership_entity_settings_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  if (isset($values['secondary_role']) && $values['secondary_role'] == 'primary') {
    form_set_value($form['user_settings']['secondary_role'], $values['primary_role'], $form_state);
  }

  // Make sure member_id_settings are set even if the chosen plugin does not
  // define a settings form.
  if (empty($values['member_id_settings'])) {
    $values['member_id_settings'] = array();
  }
}

/**
 * Form submission handler for membership_entity_settings_form().
 */
function membership_entity_settings_form_submit($form, &$form_state) {
  // Remove extra fields and save the values.
  form_state_values_clean($form_state);
  variable_set('membership_entity_settings', $form_state['values']);
  drupal_set_message(t('The configuration options have been saved'));
}

/**
 * Menu callback: Edit a membership.
 */
function membership_entity_edit($membership) {
  drupal_set_title(t('Edit membership: @id', array('@id' => $membership->member_id)));
  return drupal_get_form('membership_entity_edit_form', $membership);
}

/**
 * Form builder to create/edit membership entities.
 *
 * @see membership_entity_form_validate()
 * @see membership_entity_form_submit()
 */
function membership_entity_edit_form($form, &$form_state, $membership = NULL, $type = 'membership') {
  if (empty($membership)) {
    $membership = membership_entity_create(array('type' => $type));
  }

  $form['#attributes']['class'][] = 'membership-entity-edit-form';
  if (!empty($membership->type)) {
    $form['#attributes']['class'][] = 'membership-entity-' . $membership->type . '-edit-form';
  }

  // Add the membership entity form fields.
  $form['#membership_entity'] = $membership;
  $form['#bundle_settings'] = membership_entity_get_bundle_settings($membership->type);
  if (empty($form['#bundle_settings']['status'])) {
    drupal_set_message(t('Missing configuration settings for membership type %type. Please visit the <a href="!url">settings page</a> to configure the membership type.', array(
      '%type' => $membership->type,
      '!url' => url("admin/memberships/types/manage/$membership->type"),
    )), 'error');

    return '';
  }

  membership_entity_form($form, $form_state);
  $form['#validate'][] = 'membership_entity_form_validate';

  // Add the buttons.
  $form['actions'] = array(
    '#type' => 'actions',
    '#weight' => 9999,
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('membership_entity_edit_form_submit'),
    ),
  );

  if (!empty($membership->mid) && membership_entity_access('delete', $membership)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#limit_validation_errors' => array(),
      '#submit' => array('membership_entity_edit_form_delete'),
    );
  }

  // Add type specific submit handlers.
  if (function_exists($membership->type . '_membership_entity_edit_form_submit')) {
    $form['#submit'][] = $membership->type . '_membership_entity_edit_form_submit';
  }

  return $form;
}

/**
 * Form builder for the join form.
 */
function membership_entity_join_form($form, &$form_state, $bundle = 'membership') {
  $form['#attributes']['class'][] = 'membership-entity-join-form';

  $form['#membership_entity'] = membership_entity_create(array(
    'uid' => $GLOBALS['user']->uid,
    'type' => $bundle,
  ));

  $form['#bundle_settings'] = membership_entity_get_bundle_settings($bundle);
  if (empty($form['#bundle_settings'])) {
    return '';
  }

  membership_entity_form($form, $form_state);
  $form['#validate'][] = 'membership_entity_form_validate';

  // Hide fields where the 'membership_entity_join_form' setting is turned off.
  foreach (field_info_instances('membership_entity', $bundle) as $field_name => $instance) {
    if (empty($instance['settings']['membership_entity_join_form'])) {
      $form[$field_name]['#access'] = FALSE;
    }
  }

  // Design decision: Do not allow secondary members during a new join.
  // Secondary members may be added after the primary member is verified via
  // email or payment.
  if (isset($form['membership']['secondary_members'])) {
    $form['membership']['secondary_members']['#access'] = FALSE;
  }

  $form['actions'] = array(
    '#type' => 'actions',
    '#weight' => 9999,
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Join'),
      '#submit' => array('membership_entity_edit_form_submit'),
    ),
  );

  // Add the registration form for anonymous users.
  if (!user_is_logged_in()) {
    $form['#user'] = drupal_anonymous_user();

    $form['user'] = array(
      '#type' => 'container',
      '#parents' => array('user'),
      '#tree' => TRUE,
      '#pre_render' => array('_membership_entity_extra_fields_pre_render'),
      '#weight' => -10,
      '#attributes' => array(
        'class' => array(
          'user-info-from-cookie',
          'membership-entity-user-info',
        ),
      ),
      '#attached' => array(
        'library' => array(
          array('system', 'jquery.cookie'),
        ),
      ),
    );

    $form['user']['login'] = array(
      '#prefix' => '<p>',
      '#suffix' => '</p>',
      '#markup' => t('Click <a href="@url">here to log in</a> if you already have an account.', array(
        '@url' => url('user/login', array('query' => drupal_get_destination())),
      )),
      '#weight' => -9999.
    );

    // Start with the default user account fields.
    form_load_include($form_state, 'inc', 'membership_entity', 'membership_entity.user_register');
    membership_entity_user_account_form($form, $form_state);

    // Attach field widgets, and hide the ones where the 'user_register_form'
    // setting is not on.
    $langcode = entity_language('user', $form['#user']);
    field_attach_form('user', $form['#user'], $form['user'], $form_state, $langcode);
    foreach (field_info_instances('user', 'user') as $field_name => $instance) {
      if (empty($instance['settings']['user_register_form'])) {
        $form['user'][$field_name]['#access'] = FALSE;
      }
    }

    // User account validate handlers need to run first.
    array_unshift($form['#validate'], 'membership_entity_user_join_register_validate');
    array_unshift($form['#validate'], 'membership_entity_user_account_form_validate');

    // User account submit handler needs to run first.
    array_unshift($form['actions']['submit']['#submit'], 'membership_entity_user_join_register_submit');
  }

  return $form;
}

/**
 * Helper to add default and field api membership entity fields.
 */
function membership_entity_form(&$form, &$form_state) {
  $membership = $form['#membership_entity'];
  $bundle_settings = $form['#bundle_settings'];

  $form['#entity_type'] = 'membership_entity';
  $form['#bundle'] = $membership->type;
  $form['#membership_entity_form'] = TRUE;

  // Basic information.
  foreach (array('mid', 'type', 'created', 'entity_type') as $key) {
    $form[$key] = array(
      '#type' => 'value',
      '#value' => isset($membership->{$key}) ? $membership->{$key} : NULL,
    );
  }
  $form['changed'] = array(
    '#type' => 'hidden',
    '#default_value' => isset($membership->changed) ? $membership->changed : NULL,
  );

  $form['membership'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('membership-entity-membership-info'),
    ),
  );

  if (!empty($membership->member_id)) {
    if (user_access('administer memberships')) {
      $schema = drupal_get_schema('membership_entity');
      $form['membership']['member_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Membership ID'),
        '#description' => t('Unique membership id.'),
        '#default_value' => $membership->member_id,
        '#required' => TRUE,
        '#maxlength' => $schema['fields']['member_id']['length'],
      );
    }
    else {
      $form['membership']['member_id'] = array(
        '#type' => 'value',
        '#value' => $membership->member_id,
      );

      $form['membership']['member_id_display'] = array(
        '#type' => 'markup',
        '#markup' => t('Unique membership id: %id', array('%id' => $membership->member_id)),
      );
    }
  }

  $form['membership']['uid'] = array(
    '#type' => 'membership_entity_member_select',
    '#title' => t('Primary member'),
    '#access' => user_access('administer memberships'),
    '#required' => TRUE,
    '#default_value' => !empty($membership->uid) ? array($membership->uid) : array(),
  );

  $cardinality = (int) $bundle_settings['cardinality'];
  if ($cardinality > 1 || $cardinality == FIELD_CARDINALITY_UNLIMITED) {
    $form['membership']['secondary_members'] = array(
      '#type' => 'membership_entity_member_select',
      '#title' => format_plural($cardinality, t('Secondary member'), t('Secondary members')),
      '#cardinality' => ($cardinality == FIELD_CARDINALITY_UNLIMITED) ? $cardinality : $cardinality - 1,
      '#default_value' => $membership->secondary_members,
    );
  }

  $form['membership']['status'] = array(
    '#type' => 'radios',
    '#title' => t('Status'),
    '#options' => membership_entity_get_status_list(),
    '#default_value' => $membership->status,
    '#required' => TRUE,
    '#access' => user_access('administer memberships'),
  );

  // Add field UI items.
  field_attach_form('membership_entity', $membership, $form, $form_state);

  // Allow other modules to alter the form.
  drupal_alter('membership_entity_form', $form, $form_state, $membership);
}

/**
 * Validate the membership entity form.
 *
 * @see membership_entity_form()
 */
function membership_entity_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  $membership = $form['#membership_entity'];

  if (!empty($values['member_id'])) {
    // Member ID must be unique.
    if ((bool) db_query_range('SELECT mid FROM {membership_entity} WHERE mid <> :mid AND member_id = :member_id', 0, 1, array(':mid' => $membership->mid, ':member_id' => $values['member_id']))->fetchField()) {
      form_set_error('member_id', t('The member ID %member_id already exists.', array(
        '%member_id' => $values['member_id'],
      )));
    }
  }

  // Flatten the primary member field and make sure there is not already a
  // membership for this user.
  if (!empty($values['uid']) && $uid = reset($values['uid'])) {
    if ($uid != $membership->uid && $mid = db_query('SELECT mid FROM {membership_entity} WHERE uid = :uid AND type = :type', array(':uid' => $uid, ':type' => $membership->type))->fetchField()) {
      form_set_error('uid', t('A membership already exists for %name. Did you want to <a href="!url">renew</a> this membership?', array(
        '%name' => format_username(user_load($uid)),
        '!url' => url('membership/' . $mid . '/renew'),
      )));
    }
    form_set_value($form['membership']['uid'], $uid, $form_state);
  }

  if (!empty($values['secondary_members'])) {
    // Make sure secondary members are unique.
    form_set_value($form['membership']['secondary_members'], array_values(array_unique($values['secondary_members'])), $form_state);

    // Don't allow the primary member as a secondary member.
    foreach ($values['secondary_members'] as $delta => $value) {
      if ($values['uid'] == $value) {
        form_set_error("secondary_members][$delta][value", t('%name is the primary member.', array(
          '%name' => format_username(user_load($values['uid'])),
        )));
      }
    }
  }

  // Validate custom fields.
  entity_form_field_validate('membership_entity', $form, $form_state);
}

/**
 * Validate handler for the join form registration.
 */
function membership_entity_user_join_register_validate($form, &$form_state) {
  _membership_entity_form_field_validate('user', $form['user'], $form_state);
}

/**
 * Submit handler for the join form registration.
 *
 * @see user_register_submit().
 */
function membership_entity_user_join_register_submit($form, &$form_state) {
  $values = &$form_state['values']['user'];

  $pass = !variable_get('user_email_verification', TRUE) ? $pass = $values['pass'] : user_password();

  // Remove unneeded values.
  form_state_values_clean($form_state);

  $values['pass'] = $pass;
  $values['init'] = $values['mail'];

  $account = $form['#user'];
  _membership_entity_form_submit_build_entity('user', $account, $form['user'], $form_state);

  // Populate $edit with the properties of $account, which have been edited on
  // this form by taking over all values, which appear in the form values too.
  $edit = array_intersect_key((array) $account, $values);
  $account = user_save($account, $edit);

  // Terminate if an error occurred during user_save().
  if (!$account) {
    drupal_set_message(t('Error saving user account.'), 'error');
    $form_state['redirect'] = '';
    return;
  }
  $form_state['user'] = $account;
  $form_state['values']['uid'] = $values['uid'] = $account->uid;

  watchdog('membership_entity', 'New user registration with membership: %name (%email).', array(
    '%name' => $values['name'],
    '%email' => $values['mail'],
  ), WATCHDOG_NOTICE, l(t('edit'), 'user/' . $account->uid . '/edit'));

  $account->password = $pass;
  // No e-mail verification required; log in user immediately.
  if (!variable_get('user_email_verification', TRUE) && $account->status) {
    _user_mail_notify('register_no_approval_required', $account);
    $form_state ['uid'] = $account->uid;
    user_login_submit(array(), $form_state);
    drupal_set_message(t('Registration successful. You are now logged in.'));
    $form_state ['redirect'] = '';
  }
  // No administrator approval required.
  elseif ($account->status) {
    _user_mail_notify('register_no_approval_required', $account);
    drupal_set_message(t('A welcome message with further instructions has been sent to your e-mail address.'));
    $form_state['redirect'] = '';
  }
  else {
    _user_mail_notify('register_pending_approval', $account);
    drupal_set_message(t('Thank you for applying for an account. Your account is currently pending approval by the site administrator.<br />In the meantime, a welcome message with further instructions has been sent to your e-mail address.'));
    $form_state['redirect'] = '';
  }
}

/**
 * Submit the membership entity form.
 *
 * @see membership_entity_form()
 * @see membership_entity_form_validate()
 */
function membership_entity_edit_form_submit($form, &$form_state) {
  $membership = $form['#membership_entity'];

  // Remove extra stuff.
  form_state_values_clean($form_state);
  entity_form_submit_build_entity('membership_entity', $membership, $form, $form_state);
  $status = membership_entity_save($membership);

  // Add the saved membership object to $form_state for other modules.
  $form_state['membership_entity'] = $membership;

  $t_args = array('%member_id' => $membership->member_id);
  switch ($status) {
    case SAVED_NEW:
      if (user_access('administer memberships')) {
        drupal_set_message(t('Membership %member_id has been created.', $t_args));
        $form_state['redirect'] = 'membership/' . $membership->mid;
      }
      elseif (user_is_logged_in()) {
        drupal_set_message(t('Your membership has been created.'));
        $form_state['redirect'] = 'user';
      }
      break;

    case SAVED_UPDATED:
      drupal_set_message(t('Membership %member_id has been updated.', $t_args));
      $form_state['redirect'] = 'membership/' . $membership->mid;
      break;
  }
}

/**
 * Submit handler to delete a membership.
 */
function membership_entity_edit_form_delete($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $membership = $form['#membership_entity'];
  $form_state['redirect'] = array(
    'membership/' . $membership->mid . '/delete',
    array('query' => $destination),
  );
}

/**
 * Dispaly a confirmation page before delteing a membership.
 */
function membership_entity_delete_confirm($form, &$form_state, $membership) {
  $form_state['memberships'] = array(
    $membership->mid => $membership,
  );

  $form['membership'] = array(
    '#theme_wrappers' => array('container'),
    '#attributes' => array(),
    '#markup' => t('You are about to delete membership %member_id.', array(
      '%member_id' => $membership->member_id,
    )),
  );

  $form['#submit'][] = 'membership_entity_multiple_delete_confirm_submit';
  return confirm_form($form, t('Are you sure you want to delete this membership?'), 'membership/' . $membership->mid, t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

/**
 * Submit the memberships delete confirm form.
 */
function membership_entity_multiple_delete_confirm_submit($form, &$form_state) {
  $memberships = $form_state['memberships'];
  if ($form_state['values']['confirm']) {
    membership_entity_delete_multiple(array_keys($memberships));
    $count = count($memberships);
    drupal_set_message(format_plural($count, 'Deleted 1 membership.', 'Deleted @count memberships.'));
  }
  $form_state['redirect'] = 'admin/memberships';
}

/**
 * Open the register form in a new modal window.
 *
 * @param string $js
 *   ctools javascript status (nojs or ajax)
 * @param string $return_id
 *   The form element HTML id to fill with the new user id.
 */
function membership_entity_modal_register($js = NULL, $return_id = NULL) {
  // Fall back if parameters are not set.
  if (!$js || !$return_id) {
    return drupal_get_form('user_register_form');
  }

  ctools_include('modal');
  ctools_include('ajax');

  $form_state = array(
    'title' => t('Create a new account'),
    'ajax' => TRUE,
    'return_id' => $return_id,
  );
  $output = ctools_modal_form_wrapper('membership_entity_modal_user_register_form', $form_state);
  if (!empty($form_state['ajax_commands'])) {
    $output = $form_state['ajax_commands'];
  }
  print ajax_render($output);
  drupal_exit();
}

/**
 * Custom registration form for membership members.
 *
 * We need the ability for primary members to register new accounts for
 * any secondary members they want to add to the membership. The default
 * register_form will not allow a logged in non-admin to register new accounts.
 *
 * @see user_register_form()
 */
function membership_entity_modal_user_register_form($form, &$form_state) {
  $admin = user_access('administer users');

  // Pass access information to the submit handler. Running an access check
  // inside the submit function interferes with form processing and breaks
  // hook_form_alter().
  $form['administer_users'] = array(
    '#type' => 'value',
    '#value' => $admin,
  );

  $form['#user'] = drupal_anonymous_user();
  $form['#user_category'] = 'register';

  $form['#attached']['library'][] = array('system', 'jquery.cookie');
  $form['#attributes']['class'][] = 'user-info-from-cookie';

  // Start with the default user account fields.
  user_account_form($form, $form_state);

  // Attach field widgets, and hide the ones where the 'user_register_form'
  // setting is not on.
  $langcode = entity_language('user', $form['#user']);
  field_attach_form('user', $form['#user'], $form, $form_state, $langcode);
  foreach (field_info_instances('user', 'user') as $field_name => $instance) {
    if (empty($instance['settings']['user_register_form'])) {
      $form[$field_name]['#access'] = FALSE;
    }
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create new account'),
  );

  $form['#validate'][] = 'user_register_validate';
  $form['#submit'][] = 'membership_entity_modal_user_register_form_submit';
  return $form;
}

/**
 * Submit handler for the user register modal form.
 */
function membership_entity_modal_user_register_form_submit($form, &$form_state) {
  $admin = $form_state['values']['administer_users'];

  if (!variable_get('user_email_verification', TRUE) || $admin) {
    $pass = $form_state['values']['pass'];
  }
  else {
    $pass = user_password();
  }
  $notify = !empty($form_state['values']['notify']);

  // Remove unneeded values.
  form_state_values_clean($form_state);

  $form_state['values']['pass'] = $pass;
  $form_state['values']['init'] = $form_state['values']['mail'];

  $account = $form['#user'];

  entity_form_submit_build_entity('user', $account, $form, $form_state);

  // Populate $edit with the properties of $account, which have been edited on
  // this form by taking over all values, which appear in the form values too.
  $edit = array_intersect_key((array) $account, $form_state['values']);
  $account = user_save($account, $edit);

  // Terminate if an error occurred during user_save().
  if (!$account) {
    drupal_set_message(t("Error saving user account."), 'error');
    $form_state['redirect'] = '';
    return;
  }
  $form_state['user'] = $account;
  $form_state['values']['uid'] = $account->uid;

  watchdog('user', 'New user: %name (%email).', array(
    '%name' => $form_state['values']['name'],
    '%email' => $form_state['values']['mail'],
  ), WATCHDOG_NOTICE, l(t('edit'), 'user/' . $account->uid . '/edit'));

  $account->password = $pass;
  $uri = entity_uri('user', $account);
  if ($admin && !$notify) {
    drupal_set_message(t('Created a new user account for <a href="@url">%name</a>. No e-mail has been sent.', array(
      '@url' => url($uri['path'], $uri['options']),
      '%name' => $account->name,
    )));
  }
  elseif (!$admin && !variable_get('user_email_verification', TRUE) && $account->status) {
    _user_mail_notify('register_no_approval_required', $account);
    $form_state['uid'] = $account->uid;
    drupal_set_message(t('Account created.'));
    $form_state['redirect'] = '';
  }
  elseif ($account->status || $notify) {
    $op = $notify ? 'register_admin_created' : 'register_no_approval_required';
    _user_mail_notify($op, $account);
    if ($notify) {
      drupal_set_message(t('A welcome message with further instructions has been e-mailed to the new user <a href="@url">%name</a>.', array(
        '@url' => url($uri['path'], $uri['options']),
        '%name' => $account->name,
      )));
    }
    else {
      drupal_set_message(t('A welcome message with further instructions has been sent to your e-mail address.'));
      $form_state['redirect'] = '';
    }
  }
  // Administrator approval required.
  else {
    _user_mail_notify('register_pending_approval', $account);
    drupal_set_message(t('Thank you for applying for an account. Your account is currently pending approval by the site administrator.<br />In the meantime, a welcome message with further instructions has been sent to your e-mail address.'));
    $form_state['redirect'] = '';
  }

  // Close the modal and return to the previous form.
  $selector = '#' . $form_state['return_id'];
  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  $form_state['ajax_commands'][] = ajax_command_append('.messages', theme('status_messages'));
  $form_state['ajax_commands'][] = ajax_command_invoke($selector, 'attr', array('value', $form_state['user']->name));
  $form_state['ajax_commands'][] = ajax_command_invoke($selector, 'change');
}
