<?php

/**
 * @file
 * Page callbacks for membership entity types.
 */

/**
 * Page callback: Displays join links for available membership types.
 *
 * @param string $context
 *   The context for adding a membership. Join or admin.
 */
function membership_entity_type_membership_add_page($context = 'join') {
  // Load membership types.
  $ids = db_query('SELECT id FROM {membership_entity_type}')->fetchCol();
  $types = membership_entity_type_load_multiple($ids);

  foreach ($types as $key => $type) {
    if (!membership_entity_access('join', $type->type)) {
      unset($types[$key]);
    }
  }

  // Bypass the type listing if only one type is available.
  if (count($types) == 1) {
    drupal_goto(reset($types)->path($context));
  }

  return theme('membership_entity_type_add_list', array(
    'context' => $context,
    'types' => $types,
  ));
}

/**
 * Page callback: Displays renew links for available membership types.
 */
function membership_entity_type_renew_page() {
  // Get a list of membership types for the current user.
  $results = db_query('SELECT mid, type FROM {membership_entity} WHERE uid = :uid', array(
    ':uid' => $GLOBALS['user']->uid,
  ))->fetchAllKeyed();

  // Show a login message if no membership was found.
  if (empty($results)) {
    module_load_include('inc', 'membership_entity_term', 'membership_entity_term.pages');
    return membership_entity_term_renew_page();
  }

  // Check renewal access for each membership.
  $memberships = membership_entity_load_multiple(array_keys($results));
  foreach ($memberships as $key => $membership) {
    if (!membership_entity_term_access('renew', $membership)) {
      unset($memberships[$key]);
    }
  }

  // Bypass the type listing if only one membership is available.
  if (count($memberships) == 1) {
    $type_url_string = str_replace('_', '-', reset($memberships)->type);
    drupal_goto('user/renew/' . $type_url_string);
  }

  $output['select_membership'] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => t('Which membership would you like to renew?'),
  );

  $output['table'] = array(
    '#theme' => 'table',
    '#header' => array(t('Membership'), t('Type'), t('Options')),
    '#rows' => array(),
    '#empty' => t('There are no memberships to renew.'),
  );

  foreach ($memberships as $membership) {
    $type_url_string = str_replace('_', '-', $membership->type);
    $output['table']['#rows'][] = array(
      array('data' => $membership->member_id),
      array('data' => membership_entity_type_get_name($membership)),
      array('data' => l(t('Renew'), 'user/renew/' . $type_url_string, array(
        'attributes' => array('class' => array('button')),
      ))),
    );
  }

  return $output;
}

/**
 * Returns HTML for a list of available membership types.
 */
function theme_membership_entity_type_add_list($variables) {
  $types = $variables['types'];
  $context = $variables['context'];
  $membership_entity_term = module_exists('membership_entity_term');

  $rows = array();
  if (!empty($types)) {
    $rows = array(
      'type' => array(array()),
      'description' => array(array(
        'data' => t('Description'),
        'header' => TRUE,
      )),
    );

    if ($membership_entity_term) {
      $rows['terms'] = array(array(
        'data' => t('Term Options'),
        'header' => TRUE,
      ));
    }

    $rows['join'] = array(array());
  }

  foreach ($types as $type) {
    $rows['type'][] = array('data' => '<h3>' . check_plain($type->label) . '</h3>');
    $rows['description'][] = array('data' => check_plain($type->description));

    if ($membership_entity_term) {
      $rows['terms'][] = array('data' => theme('item_list', array(
        'items' => array_map('check_plain', $type->data['available_term_lengths']),
        'type' => 'ul',
      )));
    }

    $rows['join'][] = array('data' => l(t('Select'), $type->path($context), array(
      'attributes' => array('class' => array('button')),
    )));
  }

  return theme('table', array(
    'caption' => t('Available Membership Types'),
    'empty' => t('There are no available membership types.'),
    'header' => array(),
    'rows' => $rows,
  ));
}
