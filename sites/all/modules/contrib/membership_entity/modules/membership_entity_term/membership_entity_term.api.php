<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Alter a membership term start date before it is saved.
 *
 * Membership term start dates default to when the term is created. This hook
 * allows you to apply special rules when calculating the start date.
 *
 * @param DateObject $start
 *   The start date. Timezone is UTC. Defaults to now.
 * @param MembershipEntityTerm $term
 *   The full membership term object.
 */
function hook_membership_entity_term_start_date_alter(&$start, $term) {
  // Determine the renewal start date.
  if (!empty($term->is_renewal)) {
    $membership = membership_entity_load($term->mid);
    $bundle_settings = membership_entity_get_bundle_settings($membership->type);
    $latest_term = end($membership->terms);

    if (!empty($latest_term)) {
      $grace = new DateObject($latest_term->end, 'UTC');

      // Check for grace period.
      if (preg_match(MEMBERSHIP_ENTITY_TERM_LENGTH_REGEX, $bundle_settings['grace_period'])) {
        $grace = _membership_entity_term_modify_date($grace, $bundle_settings['grace_period']);
      }

      // If the renewal is within the grace period there is no lapse in
      // membership terms. The new term starts when the old term ended.
      if ($grace > $start) {
        $start = new DateObject($latest_term->end, 'UTC');
      }
    }
  }
}

/**
 * Alter a membership term end date before it is saved.
 *
 * Membership term end dates are calculated automatically based on start date
 * and term length. This hook allows you to apply special rules when
 * calculating the end date.
 *
 * @param DateObject $end
 *   The end date based on term start date and term length. Timezone is UTC.
 * @param MembershipEntityTerm $term
 *   The full membership term object.
 */
function hook_membership_entity_term_end_date_alter(&$end, $term) {
  // Add term modifiers.
  foreach ($term->modifiers as $modifier) {
    $end = _membership_entity_term_modify_date($end, $modifier);
  }
}
