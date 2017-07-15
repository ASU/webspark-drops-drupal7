<?php

// Functionality depends on node_import and CCK.
if (module_exists('node_import') && module_exists('content')) {

  // Load the required API files.
  include_once('./' . drupal_get_path('module', 'node_import') . '/node_import.api.php');
  include_once('./' . drupal_get_path('module', 'node_import') . '/node_import.inc');


  /**
   * Implementation of hook_user_import_form_field_match(). Add supported Content Profile fields into our dropdown list.
   */
  function content_profile_user_import_form_field_match() {
    $options                    = array();
    $options['content_profile'] = array();
    $field_options              = array();
    $contentprofile_types       = content_profile_get_types();

    foreach ($contentprofile_types as $type => $data) {
      $fields = node_import_fields('node:' . $type, TRUE);

      // Give fields a more descriptive title.
      foreach (array_keys($fields) as $key) {
        if (strstr($key, 'cck:field_')) {
          $field_options["$type $key"] = t('Content Profile: (!type) !key ', array('!key' => $fields[$key]['title'], '!type' => $type));
        }
      }

      // skip merge if there are no fields on the content type
      if (!empty($field_options)) {
        $options['content_profile'] = array_merge($options['content_profile'], $field_options);
      }
    }

    /* We do not support taxonomy yet */

    return $options;
  }

  /**
   * Implementation of hook_user_import_form_update_user().
   */
  function content_profile_user_import_form_update_user() {
    $form['content_profile'] = array('title' => t('Content Profile'), 'description' => t('Affected: fields in Content Profile nodes.'));

    return $form;
  }

  /**
   * Implementation of hook_user_import_data().
   */
  function content_profile_user_import_data($settings, $update_setting, $column_settings, $module, $field_id, $data, $column_id) {
    if ($module != 'content_profile') return;

    return trim($data[$column_id]);
  }

  /**
   * Implementation of hook_user_import_after_save().
   */
  function content_profile_user_import_after_save($settings, $account, $password, $fields, $updated, $update_setting_per_module) {

    if (!is_array($fields['content_profile'])) return;

    // check if it's an existing user and if content profile is to be updated
    if ($updated && $update_setting_per_module['content_profile'] == UPDATE_NONE) return;

    // arrange values by content type
    foreach ($fields['content_profile'] as $column_id => $column_data) {
      if (!empty($column_data)) {
        $keys                               = explode(' ', $column_id);
        $contentprofile[$keys[0]][$keys[1]] = $column_data;
      }
    }

    $contentprofile_types = content_profile_get_types();

    // process each $content profile
    foreach ($contentprofile_types as $type => $configuration) {
      content_profile_user_import_node($type, $contentprofile, $account, $fields, $updated, $update_setting_per_module['content_profile']);
    }

    return;
  }

  /**
   *  callback to create or update a node if appropriate
   */
  function content_profile_user_import_node($type, $content_profile, $account, $fields, $updated, $update_setting) {

    if (empty($content_profile[$type])) return; // pass only those, which are used

    $errors      = array();
    $title_empty = time();

    if ($updated) {
      $node = node_load(array('type' => $type, 'uid' => $account->uid));
    }

    if (empty($node)) {
      $node         = new stdClass();
      $node->type   = $type;
      $node->status = 1;
      $node->title  = $title_empty;
    }

    // Assign the mapped fields to the $node.
    foreach ($content_profile[$type] as $column_id => $column_data) {

      $field_data  = explode(':', $column_id);
      $field_name  = !empty($field_data[1]) ? $field_data[1] : $column_id;
      $field_key   = !empty($field_data[2]) ? $field_data[2] : 'value';
      $field_value = array(0 => array($field_key => $column_data[0]));

      if (!$updated) {
        $node->{$field_name} = $field_value;
      }
      elseif ($updated && $update_setting == UPDATE_ADD) {

        $current_content = content_format($field_name, $node->{$field_name}[0], 'default', $node);

        if (empty($current_content) && !empty($column_data[0])) {
          $node->{$field_name} = $field_value;
        }
      }
      elseif ($updated && $update_setting == UPDATE_REPLACE) {
        $node->{$field_name} = $field_value;
      }
    }

    // not actually checking for errors at the moment, but lete's leave this in for when we do
    if (empty($errors)) {
      $node->uid  = $account->uid;
      $node->name = $account->name;

      // Assign a default title if one has not already been mapped.
      if (!isset($node->title) || empty($node->title) || $node->title == $title_empty) {
        $node->title = $node->name;
      }

      $node = node_submit($node);

      // make sure author is not changed when submited (hapens if existing node)
      $node->uid  = $account->uid;
      $node->name = $account->name;

      node_save($node);

      if (!$node->nid) {
        drupal_set_message(t('Unknown error on saving the node: %node_data! Check watchdog logs for details.', array('%node_data' => "$node->title ($node->type)")), 'error');
      }

    }
    else {
      /**
       * @todo report errors
       */
    }
  }

}
else {
  drupal_set_message(t('Please enable %module module!', array('%module' => 'node_import')));
}
