<?php

/**
 * @file
 * Forms for creating / editing, deleting, issuing licenses
 */

// -----------------------------------------------------------------------
// Entity forms

/**
 * Form callback: create or edit a license.
 *
 * @param $entity
 *   The object to edit through the form.
 */
function commerce_file_license_form($form, &$form_state, $entity, $op = 'edit') {
  $module_path = drupal_get_path('module', 'commerce_file');
  $field_names = _commerce_file_get_field_names();
  $license_id = $entity->internalIdentifier();
  $have_line_items = FALSE;

  // we can always wrap since entity_ui_get_form() creates new entity if $op = 'add'
  $wrapper = commerce_file_license_wrapper($entity);

  // add help text
  if ($op == 'add' && ($help = variable_get('commerce_file_license_help_text', ''))) {
    $form['help'] = array(
      '#weight' => -100,
      '#markup' => '<p>' . filter_xss_admin($help) . '</p>',
    );
  }

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = $module_path . '/includes/commerce_file_license.forms.inc';

  // add license after build handler
  $form['#after_build'][] = 'commerce_file_license_form_after_build';

  // set formatted date if creating new
  if (empty($entity->created)) {
    $entity->is_new = TRUE;
    $entity->date = format_date(REQUEST_TIME, 'custom', 'Y-m-d H:i:s O');
  }

  // get any line items
  $line_items = array();
  if (!empty($wrapper->{$field_names['license_line_items']})) {
    $line_items = $wrapper->{$field_names['license_line_items']}->value();
  }
  $have_line_items = !empty($line_items);
  $form_state['have_line_items'] = $have_line_items;


  // Add the user account and e-mail fields.
  $user_field_disabled = $have_line_items && !empty($entity->owner);
  $form['user'] = array(
    '#type' => 'fieldset',
    '#title' => t('Owner information'),
    '#collapsible' => TRUE,
    '#collapsed' => $user_field_disabled,
    '#weight' => -10,
  );
  $form['user']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Owned by'),
    '#description' => t('Owner cannot be left blank.', array('%anonymous' => variable_get('anonymous', t('Anonymous')))),
    '#maxlength' => 60,
    '#autocomplete_path' => 'user/autocomplete',
    '#default_value' => isset($entity->owner) && isset($entity->owner->name) ? $entity->owner->name : '',
    '#required' => TRUE,
    '#weight' => -1,
    '#disabled' => $user_field_disabled,
  );

  // Add the field related form elements and allow extra_fields weights to be set
  $form_state[COMMERCE_FILE_LICENSE_ENTITY_NAME] = $entity;
  field_attach_form(COMMERCE_FILE_LICENSE_ENTITY_NAME, $entity, $form, $form_state);


  // file field pre-processing
  $file_field_name = $field_names['license_file'];
  $file_lang = isset($form[$file_field_name]['#language']) ? $form[$file_field_name]['#language'] : LANGUAGE_NONE;
  if (!empty($form[$file_field_name][$file_lang])) {
    foreach (element_children($form[$file_field_name][$file_lang]) as $delta) {
      if (is_int($delta)) {
        $file_element = &$form[$file_field_name][$file_lang][$delta];
        $file_element['data']['#collapsed'] = FALSE;
/** @todo add a js display of current limits that changes with file settings changes **************/
        /*
        if (isset($file_element['data']['#attributes']['class'])) {
          $file_element['data']['#attributes']['class'] = array_merge($file_element['data']['#attributes']['class'], array('clearfix'));
        }
        else {
          $file_element['data']['#attributes']['class'] = array('clearfix');
        }


        $file_element['data']['_current_limits'] = array(
          '#markup' => '<div class="commerce-file-license-current-limits"><pre>'.print_r($entity->limits,1).'</pre></div>',
          '#weight' => -10,
        );
        */

        unset($file_element);
      }
    }

    //$form['#attached']['js'][] = drupal_get_path('module', 'commerce_file') . '/js/commerce_file.forms.js';
  }


  // line item field pre-processing
  $line_item_fieldname = $field_names['license_line_items'];
  if (isset($form[$line_item_fieldname])) {
    $line_item_description = t('The line item references are shown for display purposes only. Line items are automatically linked and un-linked through order management.');

    // always disable line item form
    $line_item_lang = isset($form[$line_item_fieldname]['#language']) ? $form[$line_item_fieldname]['#language'] : LANGUAGE_NONE;
    $form[$line_item_fieldname]['#disabled'] = TRUE;
    $form[$line_item_fieldname][$line_item_lang]['actions'] = array(
      '#markup' => $line_item_description,
    );

    // get view if we have line items
    $line_items_embedded_view = views_embed_view('commerce_license_line_items_list', 'default', $license_id);
    if (!empty($line_items_embedded_view)) {

      // hide line item form and show summary view display
      $form[$line_item_fieldname]['#access'] = FALSE;
      $form[$line_item_fieldname . '_summary'] = array(
        '#type' => 'item',
        '#title' => t('Related Orders'),
        '#description' => $line_item_description,
        '#markup' => $line_items_embedded_view,
        '#weight' => $form[$line_item_fieldname]['#weight'],
      );
    }
  }

  // setup vertical tabs
  $form['additional_settings'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 99,
  );


  // Add a section to update the status
  $status_original = isset($entity->status) ? $entity->status : commerce_file_license_status_default('name');
  $granted_original = isset($entity->granted) ? $entity->granted : NULL;
  $status_options = commerce_file_license_status_options_list();

  $form['license_status'] = array(
    '#type' => 'fieldset',
    '#title' => t('License status'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'additional_settings',
    '#attached' => array(
      'js' => array(
        //$module_path . '/js/commerce_file_license.forms.js',
        array(
          'type' => 'setting',
          'data' => array('status_titles' => $status_options),
        ),
      ),
    ),
    '#weight' => 20,
  );
  $form['license_status']['status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#options' => $status_options,
    '#default_value' => $status_original,
  );
  $form['license_status']['status_original'] = array(
    '#type' => 'hidden',
    '#value' => $status_original,
    '#attributes' => array('id' => 'edit-status-original'),
  );
  $form['license_status']['granted'] = array(
    '#type' => 'textfield',
    '#title' => t('Granted on'),
    '#maxlength' => 25,
    '#default_value' => !empty($granted_original) ? format_date($granted_original, 'short') : '',
  );
  $form['license_status']['granted_original'] = array(
    '#type' => 'hidden',
    '#value' => !empty($granted_original) ? format_date($granted_original, 'short') : '',
    '#attributes' => array('id' => 'edit-granted-original'),
  );


  // Add History info
  $form['license_history'] = array(
    '#type' => 'fieldset',
    '#title' => t('License history', array(), array('context' => 'a drupal commerce file license')),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'additional_settings',
    //'#attached' => array(
    //  'js' => array($module_path . '/js/commerce_file_license.forms.js'),
    //),
    '#weight' => 40,
  );

  // Created and changed date
  $form['license_history']['date'] = array(
    '#type' => 'textfield',
    '#title' => t('Created on'),
    '#description' => t('Format: %time. The date format is YYYY-MM-DD and %timezone is the time zone offset from UTC. Leave blank to use the time of form submission.', array('%time' => !empty($entity->date) ? date_format(date_create($entity->date), 'Y-m-d H:i:s O') : format_date($entity->created, 'custom', 'Y-m-d H:i:s O'), '%timezone' => !empty($entity->date) ? date_format(date_create($entity->date), 'O') : format_date($entity->created, 'custom', 'O'))),
    '#maxlength' => 25,
    '#default_value' => !empty($entity->created) ? format_date($entity->created, 'custom', 'Y-m-d H:i:s O') : '',
  );
  $form['license_history']['created'] = array(
    '#type' => 'hidden',
    '#value' => !empty($entity->created) ? format_date($entity->created, 'short') : '',
    '#attributes' => array('id' => 'edit-created'),
  );
  $form['license_history']['changed'] = array(
    '#type' => 'hidden',
    '#value' => !empty($entity->changed) ? format_date($entity->changed, 'short') : '',
    '#attributes' => array('id' => 'edit-changed'),
  );


  // actions
  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 100,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save License'),
    '#weight' => 40,
  );


  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'commerce_file_license_form_validate';

  return $form;
}

/**
 * After build callback for commerce_file_license_form().
 *  - alter form after all element process callbacks
 */
function commerce_file_license_form_after_build($form, &$form_state) {
  $entity = $form_state[COMMERCE_FILE_LICENSE_ENTITY_NAME];

  $field_names = _commerce_file_get_field_names();
  $license_info = _commerce_file_collate_license_info();
  $file_fieldset_description = t('<strong>These settings are added to the cumulative value of all of the limit settings in the line item references.</strong>');
  $have_line_items = !empty($form_state['have_line_items']);

  // file field processing
  $file_field_name = $field_names['license_file'];
  if (isset($form[$file_field_name])) {
    $file_lang = isset($form[$file_field_name]['#language']) ? $form[$file_field_name]['#language'] : LANGUAGE_NONE;
    if (!empty($form[$file_field_name][$file_lang])) {
      foreach (element_children($form[$file_field_name][$file_lang]) as $file_delta) {
        $element = &$form[$file_field_name][$file_lang][$file_delta];

        // unset remove button for files if we have line items
        $element['remove_button']['#access'] = !$have_line_items;

        // alter settings
        if (isset($element['data'])) {
          if (!empty($element['data']['#description'])) {
            $element['data']['#description'] .= ' ' . $file_fieldset_description;
          }
          else {
            $element['data']['#description'] = $file_fieldset_description;
          }
        }
      }
      unset($element);
    }
  }


  return $form;
}

/**
 * Validation callback for commerce_file_license_form().
 */
function commerce_file_license_form_validate($form, &$form_state) {
  $entity = $form_state[COMMERCE_FILE_LICENSE_ENTITY_NAME];

  // Validate the "owned by" field.
  if (!empty($form_state['values']['name']) && !($account = user_load_by_name($form_state['values']['name']))) {
    // The use of empty() is mandatory in the context of usernames as the empty
    // string denotes an anonymous user.
    form_set_error('name', t('The username %name does not exist.', array('%name' => $form_state['values']['name'])));
  }

  // Validate the "created on" field.
  if (!empty($form_state['values']['date']) && strtotime($form_state['values']['date']) === FALSE) {
    form_set_error('date', t('You have to specify a valid date.'));
  }

  // Notify field widgets to validate their data.
  field_attach_form_validate(COMMERCE_FILE_LICENSE_ENTITY_NAME, $entity, $form, $form_state);
}

/**
 * Submit callback for commerce_file_license_form().
 */
function commerce_file_license_form_submit($form, &$form_state) {
  global $user;

  $entity = $form_state[COMMERCE_FILE_LICENSE_ENTITY_NAME];
  $values = &$form_state['values'];

  // If the user is editing, load a fresh copy to merge changes to.
  if (!empty($entity->license_id)) {
    $entity = $form_state[COMMERCE_FILE_LICENSE_ENTITY_NAME] = commerce_file_license_load($entity->license_id);
  }

  // Set the license's owner uid based on the supplied name
  // - name exists since it is REQUIRED and checked for existence
  $account = user_load_by_name($values['name']);
  $entity->uid = $account->uid;


  // Set created timestamp
  $entity->created = !empty($values['date']) ? strtotime($values['date']) : REQUEST_TIME;

  // Notify field widgets.
  field_attach_submit(COMMERCE_FILE_LICENSE_ENTITY_NAME, $entity, $form, $form_state);

  // Update the status if specified.
  if ($values['status'] != $values['status_original']) {
    // We skip saving in the update since we do it below once for the entire form submission.
    commerce_file_license_status_update($entity, $values['status'], TRUE);
  }

  // Save the license.
  if ($entity->save()) {
    drupal_set_message(t('License saved.'));
  }
  else {
    drupal_set_message(t('License NOT saved. An error has occurred during saving the license.'), 'error');
  }
}

/**
 * Form callback: confirmation form for deleting a license.
 *
 * @param $entity
 *   The object to delete through the form.
 *
 * @return
 *   The form array to add or edit a license.
 *
 * @see confirm_form()
 */
function commerce_file_license_delete_form($form, &$form_state, $entity) {
  $form_state[COMMERCE_FILE_LICENSE_ENTITY_NAME] = $entity;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_file') . '/includes/commerce_file_license.forms.inc';

  $form['#submit'][] = 'commerce_file_license_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete the file license for @filename owned by @owner_name?', array('@filename' => $entity->file['filename'], '@owner_name' => $entity->owner->name)),
    '',
    '<p>' . t('Deleting this license cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for commerce_file_license_delete_form().
 */
function commerce_file_license_delete_form_submit($form, &$form_state) {
  $entity = $form_state[COMMERCE_FILE_LICENSE_ENTITY_NAME];
  $tokens = array('@filename' => $entity->file['filename'], '@owner_name' => $entity->owner->name);

  if ($entity->delete()) {
    drupal_set_message(t('The file license has been deleted for @filename owned by @owner_name.', $tokens));
  }
  else {
    drupal_set_message(t('The file license could not be deleted for @filename owned by @owner_name.', $tokens), 'error');
  }
}


// -----------------------------------------------------------------------
// Issue License form

/**
 * Returns the base form array for issuing licenses on a host entity
 */
function commerce_file_license_issue_by_host_form($form, &$form_state, $entity_type, $entity) {
  global $user;

  // Add access to entire form
  // @todo: check create also?
  $form['#access'] = commerce_file_license_admin_access('update', $user);

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_file') . '/includes/commerce_file_license.forms.inc';

  // store the order object
  $form_state['entity_type'] = $entity_type;
  $form_state['entity'] = $entity;
  $form_state['entity_label'] = entity_label($entity_type, $entity);

  // set default status
  $default_status = NULL;
  $allowed_statuses = commerce_file_license_statuses(array('state' => 'allowed'));
  if (!empty($allowed_statuses)) {
    $default_status = key($allowed_statuses);
  }
  else {
    $default_status = commerce_file_license_status_default('name');
  }

  // build form elements
  $form['license_status'] = array(
    '#type' => 'select',
    '#title' => t('License status'),
    '#default_value' => $default_status,
    '#options' => commerce_file_license_status_options_list(),
    '#required' => TRUE,
  );

  $form['product_refresh'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sync to current product'),
    '#description' => t('Enabling this will update the as-purchased snapshot of the files on the line items with the current product files and access limits.'),
    '#default_value' => FALSE,
  );

  // Add actions
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#weight' => 40,
  );

  $form['#submit'][] = 'commerce_file_license_issue_by_host_form_submit';

  return $form;
}

/**
 * Submit callback for commerce_file_license_issue_by_host_form().
 */
function commerce_file_license_issue_by_host_form_submit($form, &$form_state) {
  $issued_count = NULL;
  $values = &$form_state['values'];

  // normalize inputs
  $license_status = isset($values['license_status']) ? $values['license_status'] : NULL;
  $product_refresh = !empty($values['product_refresh']);

  // exit if no entity
  if (empty($form_state['entity_type']) || empty($form_state['entity'])) {
    drupal_set_message(t('Licenses could not be updated or created due to an invalid form state.'), 'error');
    return;
  }

  // extract entity info
  $entity_type = $form_state['entity_type'];
  $entity = $form_state['entity'];
  $entity_label = $form_state['entity_label'];

  // attempt to issue the licenses
  $issued_count = commerce_file_license_issue_by_host_execute($entity_type, $entity, $license_status, $product_refresh);

  // notify of actions performed
  $msg_tokens = array(
    '%label' => $entity_label ? $entity_label : entity_label($entity_type, $entity),
  );

  if (!empty($issued_count)) {
    $message = format_plural($issued_count,
      'Successfully updated 1 license for %label.',
      'Successfully updated @count licenses for %label.',
      $msg_tokens
    );

    drupal_set_message($message);
  }
  elseif (isset($issued_count) && $issued_count === 0) {
    drupal_set_message(t('No licenses were updated or created for %label.', $msg_tokens));
  }
  else {
    drupal_set_message(t('Licenses could not be updated or created for %label. Check the logs for any errors that occurred.', $msg_tokens), 'error');
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 * - Set default status
 * - Set a better line item label
 */
function commerce_file_form_commerce_file_license_issue_by_host_form_alter(&$form, &$form_state, $form_id) {
  $entity_type = $form_state['entity_type'];
  $entity = $form_state['entity'];

  $line_item_ids = array();
  $existing_licenses = array();

  // alter form and set line items based on entity type
  switch ($entity_type) {
    case 'commerce_order':
      $line_item_ref_items = field_get_items($entity_type, $entity, 'commerce_line_items');
      if (!empty($line_item_ref_items)) {
        foreach ($line_item_ref_items as $line_item_ref_item) {
          $line_item_ids[$line_item_ref_item['line_item_id']] = $line_item_ref_item['line_item_id'];
        }
      }
      break;

    case 'commerce_line_item':
      if (!empty($entity->line_item_id)) {
        $line_item_ids[$entity->line_item_id] = $entity->line_item_id;
      }

      // set entity label since line item does not define a useful label callback
      $form_state['entity_label'] = commerce_line_item_title($entity);
      break;
  }


  // set default status based on existing licenses related to line items
  if (!empty($line_item_ids)) {
    $existing_licenses = commerce_file_license_load_by_property(array(), $line_item_ids);
    if (!empty($existing_licenses)) {
      krsort($existing_licenses);
      $latest_license = reset($existing_licenses);
      $default_status = $latest_license->status;

      // determine if all licenses are the same status
      foreach ($existing_licenses as $existing_license) {
        if ($existing_license->status != $default_status) {
          $default_status = NULL;
        }
      }

      if (isset($default_status)) {
        $form['license_status']['#default_value'] = $default_status;
      }
    }
    else {
      // Create licenses
      $form['actions']['submit']['#value'] = t('Create');

      // check if there are line item file fields on any items
      $have_line_item_files = FALSE;
      $line_item_file_field_name = _commerce_file_get_field_names('line_item_files');
      $line_items = commerce_line_item_load_multiple($line_item_ids);

      foreach ($line_items as $line_item_id => $line_item) {
        $file_field_items = field_get_items('commerce_line_item', $line_item, $line_item_file_field_name);
        if (!empty($file_field_items)) {
          $have_line_item_files = TRUE;
          break;
        }
      }

      // can only sync files from the product if no line item files
      if (!$have_line_item_files) {
        $form['product_refresh']['#default_value'] = TRUE;
        $form['product_refresh']['#disabled'] = TRUE;
      }
    }
  }
}
