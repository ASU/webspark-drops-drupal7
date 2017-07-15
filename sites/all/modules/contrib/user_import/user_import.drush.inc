<?php

/**
 * @file
 * Drush integration for the User Import module.
 */

function user_import_drush_help($command) {
  switch ($command) {
    case 'drush:user-import':
      return dt('Queue an import of users from a CSV file');
    case 'error:template-not-found':
      return dt('Template not found');
    case 'error:file-not-found':
      return dt('File not found');
    case 'error:no-default-template':
      return dt('There is no default template configured');
  }
}

/**
 * Implementation of hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * See `drush topic docs-commands` for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function user_import_drush_command() {
  $commands                = array();
  $commands['user-import'] = array(
    'description' => dt('Queue an import of users'),
    'arguments'   => array(
      'file'     => dt('The CSV file with user data'),
      'template' => dt('Name of the template to use (optional, if not provided the default template is used)'),
    ),
    'examples'    => array(
      dt('standard example') => 'drush user-import users.csv',
    ),
  );

  return $commands;
}

function drush_user_import($original_file = NULL, $template_name = NULL) {

  if (!file_exists($original_file)) {
    return drush_set_error('file-not-found');
  }
  $original_file = realpath($original_file);

  if ($template_name) {
    $template = db_query("SELECT * FROM {user_import} WHERE name = :name AND setting = 'template'", array(':name' => $template_name))->fetchObject();

    if (!$template) {
      return drush_set_error('template-not-found');
    }
  }
  else {
    $template_id = variable_get('user_import_settings', '0');

    if (!$template_id) {
      return drush_set_error('no-default-template');
    }

    $template = db_query("SELECT * FROM {user_import} WHERE import_id = :import_id AND setting = 'template'", array(':import_id' => $template_id))->fetchObject();

    if (!$template) {
      return drush_set_error('template-not-found');
    }

    drush_print(dt('Using default settings template "!template"', array('!template' => $template->name)));
  }

  $template->options     = unserialize($template->options);
  $template->field_match = unserialize($template->field_match);
  $template->roles       = unserialize($template->roles);

  $file           = new stdClass();
  $file->filepath = $original_file;
  $file->filename = basename($original_file);
  $destination = 'private://user_import/processing';
  $filepath = file_unmanaged_copy($file->filepath, $destination, FILE_EXISTS_RENAME);

  // initialize import from template
  $import                  = new stdClass();
  $import->oldfilename     = basename($original_file);
  $import->filename        = $file->filename;
  $import->filepath        = $filepath;
  $import->started         = time();
  $import->field_match     = $template->field_match;
  $import->roles           = $template->roles;
  $import->options         = $template->options;
  $import->setting         = 'import';
  $result                  = drupal_write_record('user_import', $import);

  if ($result == SAVED_NEW) {
    drush_print(dt('Successfully queued user import. The original CSV file !file has been copied to the Drupal installation and can be removed.', array('!file' => $original_file)));
  }
  else {
    drush_set_error('import_failed', dt('Unable to queue the user import.'));
  }
}
