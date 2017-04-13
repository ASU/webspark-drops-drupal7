<?php

/**
 * @file
 * Devel integration for the membership_entity module.
 */

/**
 * Form builder to generate membership content.
 */
function membership_entity_devel_generate_memberships_form($form, &$form_state) {
  $form['num'] = array(
    '#type' => 'textfield',
    '#title' => t('How many memberships would you like to generate?'),
    '#description' => t('You must have at least the same number of user objects available. Click <a href="!url">here</a> to generate users.', array(
      '!url' => url('admin/config/development/generate/user'),
    )),
    '#default_value' => 50,
    '#element_validate' => array('element_validate_integer_positive'),
    '#size' => 10,
  );

  $form['kill'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete all memberships before generating new memberships.'),
    '#default_value' => FALSE,
  );

  if (module_exists('membership_entity_type')) {
    foreach (membership_entity_type_get_types() as $type) {
      $types[$type->type] = $type->label;
    }
    $form['type'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Membership types'),
      '#description' => t('Select the membership types to select from when generating memberships.'),
      '#options' => $types,
      '#default_value' => array_keys($types),
    );

    $form['multiple_types'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow users to belong to multiple memberships (of different types).'),
      '#default_value' => FALSE,
    );
  }

  if (module_exists('membership_entity_term')) {
    $form['term_count'] = array(
      '#type' => 'textfield',
      '#title' => t('Max number of terms to create per membership'),
      '#description' => t('Enter the maximum number of terms that should be generated for each membership. The actual number of terms for a given membership will be somewhere between 1 and this value.'),
      '#default_value' => 1,
      '#element_validate' => array('element_validate_integer_positive'),
      '#size' => 10,
    );
  }

  $options = array(1 => t('Now'));
  foreach (array(86400, 604800, 2592000, 31536000, 63072000, 94608000, 126144000, 157680000, 315360000, 473040000) as $interval) {
    $options[$interval] = format_interval($interval, 1) . ' ' . t('ago');
  }

  $form['time_range'] = array(
    '#type' => 'select',
    '#title' => t('How old should memberships be?'),
    '#description' => t('Memberships will be distributed randomly from the current time, back to the selected time.'),
    '#required' => TRUE,
    '#options' => $options,
    '#default_value' => 94608000,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate'),
  );

  return $form;
}

/**
 * Submit the form to generate memberships.
 */
function membership_entity_devel_generate_memberships_form_submit($form, &$form_state) {
  form_state_values_clean($form_state);
  membership_entity_devel_create_memberships($form_state['values']);
}

/**
 * Generate some random memberships.
 *
 * @param array $values
 *   An assoicative array with the following keys:
 *   - num: Number of users to generate.
 *   - kill: Boolean that indicates if existing users should be removed first.
 *   - time_range: The max join date of each membership term in seconds.
 *   - type: An array of memberships types to create.
 *   - multiple_type: Whether or not to allow a user to belong to multiple
 *     membership types.
 */
function membership_entity_devel_create_memberships($values) {
  // Load some devel generate helpers.
  module_load_include('inc', 'devel_generate');
  module_load_include('inc', 'devel_generate', 'devel_generate.fields');

  if ($values['kill']) {
    $mids = db_query('SELECT mid FROM {membership_entity}')->fetchAllAssoc('mid');
    membership_entity_delete_multiple(array_keys($mids));
    drupal_set_message(format_plural(count($mids), '1 membership deleted', '@count memberships deleted'));
  }

  $results = db_query('SELECT uid FROM {users} WHERE uid <> 0')->fetchAllAssoc('uid');
  $users = drupal_map_assoc(array_keys($results));

  $used_users = array();
  $results = db_query('SELECT uid, type FROM {membership_entity}');
  foreach ($results as $row) {
    $used_users[$row->type][$row->uid] = $row->uid;
  }

  if (!module_exists('membership_entity_type')) {
    $values['type'] = array('membership' => 'membership');
  }
  $types = array_filter($values['type']);

  $num = min(count($users), $values['num']);
  for ($count = 0; $count < $num; $count++) {
    $type = array_rand($types);
    $bundle_settings = membership_entity_get_bundle_settings($type);
    if (!empty($used_users[$type])) {
      $users = array_diff($users, $used_users[$type]);
    }
    $uid = array_rand($users);
    if (!$uid) {
      // No user was found so we're done.
      break;
    }
    if (empty($values['multiple_types'])) {
      // Only one membership type per user.
      unset($users[$uid]);
    }
    $used_users[$type][$uid] = $uid;

    // Create the membership.
    $created = REQUEST_TIME - mt_rand(0, $values['time_range']);
    $membership = membership_entity_create(array(
      'mid' => NULL,
      'uid' => $uid,
      'type' => $type,
      'created' => $created,
      'status' => MEMBERSHIP_ENTITY_ACTIVE,
    ));
    $membership->member_id = membership_entity_next_member_id($membership);

    // Populate all core fields on behalf of field.module
    devel_generate_fields($membership, 'membership_entity', $membership->type);
    $membership->save();

    if (module_exists('membership_entity_term') && !empty($values['term_count'])) {
      $terms = array();
      $available_terms = drupal_map_assoc($bundle_settings['available_term_lengths']);
      $term_count = rand(1, $values['term_count']);
      for ($i = 0; $i < $term_count; $i++) {
        $term_length = array_rand($available_terms);

        if ($i == 0) {
          // First term starts when the membership was created.
          $start = format_date($created, 'custom', DATE_FORMAT_DATETIME, 'UTC');
        }
        elseif ($terms[$i - 1]->term == 'lifetime') {
          // Don't add anymore terms after a lifetime term.
          break;
        }
        else {
          $term_start = REQUEST_TIME - mt_rand(0, $values['time_range']);
          if ($term_start <= strtotime($terms[$i - 1]->end)) {
            $start = $terms[$i - 1]->end;
          }
          else {
            $start = format_date($term_start, 'custom', DATE_FORMAT_DATETIME, 'UTC');
          }
        }
        $terms[$i] = membership_entity_term_create(array(
          'mid' => $membership->mid,
          'term' => $term_length,
          'start' => $start,
        ));
        $terms[$i]->save();
      }
    }
  }

  drupal_set_message(t('!num generated.', array(
    '!num' => format_plural($count, '1 membership', '@count memberships'),
  )));
}
