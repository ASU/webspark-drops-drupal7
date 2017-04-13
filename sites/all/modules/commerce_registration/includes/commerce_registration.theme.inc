<?php
/**
 * @file
 * Commerce Registration theme functions.
 */

/**
 * Theme the registrations for viewing on a user's order view page.
 */
function theme_commerce_registration_order($variables) {
  $header = array(
    array(
      'data' => t('id'),
      'field' => 'registration_id',
      'type' => 'property',
      'specifier' => 'registration_id'
    ),
    array(
      'data' => t('Email'),
      'field' => 'mail',
      'type' => 'property',
      'specifier' => 'mail'
    ),
    array(
      'data' => t('User'),
      'field' => 'user_uid',
      'type' => 'property',
      'specifier' => 'user'
    ),
    array(
      'data' => t('Product'),
      'field' => 'entity',
      'type' => 'property',
      'specifier' => 'entity'
    ),
    array(
      'data' => t('Count'),
      'field' => 'count',
      'type' => 'property',
      'specifier' => 'count'
    ),
    array(
      'data' => t('Created'),
      'field' => 'created',
      'sort' => 'desc',
      'type' => 'property',
      'specifier' => 'created'
    ),
    array(
      'data' => t('State'),
      'field' => 'state',
      'type' => 'property',
      'specifier' => 'state'
    ),
  );
  $title = "<div class='commerce-registration registration-list'><h2>";
  $title .= t('Registrations');
  $title .= "</h2>";
  $rows = array();

  foreach ($variables['registrations'] as $registration) {
    $wrapper = entity_metadata_wrapper('registration', $registration);
    $host_entity = $wrapper->entity->value();

    $host_label = entity_label($registration->entity_type, $host_entity);
    $host_uri = entity_uri($registration->entity_type, $host_entity);

    $user_col = '';
    if ($registration->user_uid) {
      $user = $wrapper->user->value();
      $uri = entity_uri('user', $user);
      $user_col = l($user->name, $uri['path']);
    }

    $link = $host_label;
    if (isset($host_uri['path'])) {
      $link = l($host_label, $host_uri['path']);
    }

    $rows[] = array(
      l($registration->registration_id, 'registration/' . $registration->registration_id),
      l($wrapper->mail->value(), 'mailto:' . $wrapper->mail->value()),
      $user_col,
      $link,
      $registration->count,
      format_date($registration->created),
      entity_label('registration_state', $wrapper->state->value())
    );
  }
  $table = array(
    'header' => $header,
    'rows' => $rows
  );

  return $title . theme('table', $table) . theme('pager') . "</div>";
}
