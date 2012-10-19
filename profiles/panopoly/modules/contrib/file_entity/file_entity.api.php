<?php

/**
 * @file
 * Hooks provided by the File Entity module.
 */

/**
 * Declare that your module provides default file types.
 *
 * Your module may already implement this hook for other CTools plugin types.
 * If so, copy the body of this function into the existing hook.
 */
function hook_ctools_plugin_api($owner, $api) {
  if ($owner == 'file_entity' && $api == 'file_type') {
    return array('version' => 1);
  }
}

/**
 * Define default file types.
 *
 * File types are implemented as CTools exportables, so modules can alter the
 * defaults via hook_file_default_types_alter(), and the administrator can
 * save overridden and custom types to the {file_type} database table.
 *
 * @return array
 *   An array whose keys are file type names and whose values are objects
 *   representing the file type, with the following key/value pairs:
 *   - api_version: The version of this data.
 *   - type: The file type name.
 *   - label: The human-readable name of the file type.
 *   - description: The description of this file type.
 *   - mimetypes: An array of mimetypes that this file type will map to.
 */
function hook_file_default_types() {
  return array(
    'image' => (object) array(
      'api_version' => 1,
      'type' => 'image',
      'label' => t('Image'),
      'description' => t("An <em>Image</em> is a two-dimensional picture that has a similar appearance to some subject, usually a physical object or a person."),
      'mimetypes' => array(
        'image/jpeg',
        'image/gif',
        'image/png',
      ),
    ),
  );
}

/**
 * Alter default file types.
 *
 * @see hook_file_default_types()
 */
function hook_file_default_types_alter(&$types) {
  $types['image']->mimetypes[] = 'image/svg+xml';
}

/**
 * Define file formatters.
 *
 * @return
 *   An array whose keys are file formatter names and whose values are arrays
 *   describing the formatter.
 *
 * @todo Document key/value pairs that comprise a formatter.
 *
 * @see hook_file_formatter_info_alter()
 */
function hook_file_formatter_info() {
  // @todo Add example.
}

/**
 * Perform alterations on file formatters.
 *
 * @param $info
 *   Array of information on file formatters exposed by
 *   hook_file_formatter_info() implementations.
 */
function hook_file_formatter_info_alter(&$info) {
  // @todo Add example.
}

/**
 * @todo Add documentation.
 *
 * Note: This is not really a hook. The function name is manually specified via
 * 'view callback' in hook_file_formatter_info(), with this recommended callback
 * name pattern.
 */
function hook_file_formatter_FORMATTER_view($file, $display, $langcode) {
}

/**
 * @todo Add documentation.
 *
 * Note: This is not really a hook. The function name is manually specified via
 * 'settings callback' in hook_file_formatter_info(), with this recommended
 * callback name pattern.
 */
function hook_file_formatter_FORMATTER_settings($form, &$form_state, $settings) {
}

/**
 * @todo Add documentation.
 */
function hook_file_displays_alter($displays, $file, $view_mode) {
}

/**
 * @todo Add documentation.
 */
function hook_file_view($file, $view_mode, $langcode) {
}

/**
 * @todo Add documentation.
 */
function hook_file_view_alter($build, $type) {
}

/**
 * Defines bulk file operations.
 *
 * This hook enables modules to inject custom operations into the mass
 * operations dropdown found at admin/content/file, by associating a callback
 * function with the operation, which is called when the form is submitted.
 * The callback function receives one initial argument, which is an array of
 * the checked files.
 *
 * @return
 *  An associave array of operations keyed by machine name.
 *    - label: A string to show in the operations dropdown.
 *    - callback (string): A callback function to call for the operation. This
 *        function will be passed an array of file_ids which were selected.
 *    - confirm (boolean): Whether or not this operation requires a confirm form
 *        In the case where confirm is set to true, callback should be a function
 *        which can return a confirm form.
 *
 * @see hook_file_operation_info_alter()
 * @see file_entity_get_file_operation_info()
 */
function hook_file_operation_info() {
  $info['fluff'] = array(
    'label' => t('Fluff selected files'),
    'callback' => 'file_fluff_files',
  );

  return $info;
}

/**
 * Perform alterations on bulk file operations.
 *
 * @param $info
 *   Array of information on bulk file operations exposed by
 *   hook_file_operation_info() implementations.
 *
 * @see hook_file_operation_info()
 * @see file_entity_get_file_operation_info()
 */
function hook_file_operation_info_alter(&$info) {
  // Remove the 'Fluff selected files' operation.
  unset($info['fluff']);
}

/**
 * Decides which file type (bundle) should be assigned to a file entity.
 *
 * @param $file
 *   File object.
 *
 * @return
 *   Array of file type machine names that can be assigned to a given file type.
 *   If there are more proposed file types the one, that was returned the first,
 *   wil be chosen. This can be, however, changed in alter hook.
 *
 * @see hook_file_type_alter()
 */
function hook_file_type($file) {
  // Assign all files uploaded by anonymous users to a special file type.
  if (user_is_anonymous()) {
    return array('untrusted_files');
  }
}

/**
 * Alters list of file types that can be assigned to a file.
 *
 * @param $types
 *   List of proposed types.
 * @param $file
 *   File object.
 */
function hook_file_type_alter(&$types, $file) {
  // Choose a specific, non-first, file type.
  $types = array($types[4]);
}
