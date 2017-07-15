<?php

/**
 * Implementation of hook_user_import_form_fieldsets().
 */
function subscribed_user_import_form_fieldset($import, $collapsed) {

  if (module_exists('publication') && module_exists('schedule')) {

    $publications = publication_select_publications('enewsletter');
    if (empty($publications)) return;

    $form['subscribed'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('Subscriptions'),
      '#collapsible' => TRUE,
      '#collapsed'   => $collapsed,
      '#tree'        => TRUE,
    );

    foreach ($publications as $publication) {

      $type = $publication->type;

      $form['subscribed'][$type] = array(
        '#type'  => 'fieldset',
        '#title' => check_plain($type),
      );

    }

    reset($publications);
    $subscribed = $import['options']['subscribed'];

    foreach ($publications as $publication) {

      $options    = array();
      $schedules  = schedule_select_schedules($type, $publication->publication_id);
      $options[0] = t('No Subscription');

      foreach ($schedules as $schedule) {
        $options[$schedule['schedule_id']] = $schedule['schedule_title'];
      }

      $subscription_default = empty($subscribed[$type][$publication->publication_id]) ? 0 : $subscribed[$type][$publication->publication_id][0];

      $form['subscribed'][$type][$publication->publication_id][] = array(
        '#type'          => 'radios',
        '#title'         => check_plain($publication->title),
        '#default_value' => $subscription_default,
        '#options'       => $options,
        '#description'   => check_plain($publication->description),
      );

    }
  }

  return $form;
}

/**
 * Implementation of hook_user_import_form_update_user().
 */
function subscribed_user_import_form_update_user() {
  $form['subscribed'] = array('title' => t('Subscribed'), 'description' => t('Affected: subscriptions.'));

  return $form;
}

/**
 * Implementation of hook_user_import_after_save().
 */
function subscribed_user_import_after_save($settings, $account, $password, $fields, $updated) {
  /**
   * @todo change to new update architecture
   */
  if (!module_exists('publication') || !module_exists('schedule') || !module_exists('identity_hash') || empty($settings['options']['subscribed'])) return;

  $subscribed_settings = $settings['options']['subscribed'];
  $uid                 = $account->uid;

  if (is_array($subscribed_settings)) {

    foreach ($subscribed_settings as $type => $type_subscriptions) {

      $subscriptions = $type_subscriptions;

      foreach ($type_subscriptions as $publication_id => $schedule) {
        if (empty($schedule[0])) unset($subscriptions[$publication_id]);
      }

      $publications = publication_select_publications_and_terms($type);

      if (!empty($publications) && !empty($subscriptions)) {
        subscribed_set_subscriptions($type, $uid, $publications, $subscriptions);
        subscribed_set_subscriptions_terms($type, $uid, $publications, $subscriptions);
        identity_hash_set_hash($uid);
      }
    }
  }

  return;
}
