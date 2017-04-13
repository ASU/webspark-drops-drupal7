<?php

/**
 * @file
 * Theme functions for the membership_entity module.
 */

/**
 * Preprocess variables for membership-entity.tpl.php.
 */
function template_preprocess_membership_entity(&$variables) {
  $membership = $variables['membership']['#membership_entity'];

  $variables['view_mode'] = $variables['membership']['#view_mode'];
  $variables['membership_entity'] = $membership;
  $variables['member_id'] = check_plain($membership->member_id);
  $variables['primary_member'] = theme('username', array('account' => user_load($membership->uid)));

  // Add the $content variable.
  $variables['content'] = array();
  foreach (element_children($variables['membership']) as $key) {
    $variables['content'][$key] = $variables['membership'][$key];
  }

  field_attach_preprocess('membership_entity', $membership, $variables['content'], $variables);

  // Add some classes.
  $variables['classes_array'][] = drupal_html_class('membership', 'membership-type-' . $membership->type);
  switch ($membership->status) {
    case MEMBERSHIP_ENTITY_EXPIRED:
      $variables['classes_array'][] = 'membership-expired';
      break;

    case MEMBERSHIP_ENTITY_ACTIVE:
      $variables['classes_array'][] = 'membership-active';
      break;

    case MEMBERSHIP_ENTITY_CANCELLED:
      $variables['classes_array'][] = 'membership-cancelled';
      break;

    case MEMBERSHIP_ENTITY_PENDING:
      $variables['classes_array'][] = 'membership-pending';
      break;
  }
  if ($variables['view_mode'] == 'account') {
    $variables['classes_array'][] = 'membership-account';
  }

  // Add some template suggestions.
  $variables['theme_hook_suggestions'][] = 'membership_entity__' . $membership->type;
  if ($variables['view_mode'] != 'full') {
    $variables['theme_hook_suggestions'][] = 'membership_entity__' . $variables['view_mode'];
  }
}
