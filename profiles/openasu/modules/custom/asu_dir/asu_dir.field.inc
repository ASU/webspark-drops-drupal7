<?php

/**
 * @file
 * asu_directory.theme.inc
 *
 * This include defines the ASU Directory custom field via the Field API
 *
 * @author Colton Testamarck (colt@asu.edu)
 *
 */

/**
 * Implementation of hook_field_info()
 * Defines a custom field which can store and render the ASU Directory
 *
 * @return array
 */
function asu_dir_field_info() {
  return array(
    'asu_directory' => array(
      'label' => t('ASU Directory'),
      'description' => t('A field to store ASU Directory items'),
      'default_widget' => 'asu_directory_form',
      'default_formatter' => 'asu_directory',
      'settings' => array(),
      'instance_settings' => array(),
    ),
  );
}

/*
*Implements hook_field_is_empty
*Check if asu_maps_enhanced field is empty
*
*/
function asu_dir_field_is_empty($item, $field) {
  $configs = drupal_json_decode($item['directory_config']);

  if ($configs['dept_id'] == NULL || $configs['dept_id'] == "" || $configs['dept_id'] == ASU_DIRECTORY_TOP_LEVEL_PS_ID) {

    if ($configs['use_custom_q'] && isset($configs['custom_q'])) {
      return FALSE;
    }

    return TRUE;
  }

  return FALSE;
}

/**
 * Implements hook_field_formatter_info().
 *
 * Defines a custom field formatter for
 *
 */
function asu_dir_field_formatter_info() {
  return array(
    'asu_directory' => array(
      'label' => t('ASU Directory'),
      'field types' => array('asu_directory'),
      'settings' => array(),
    ),
  );
}


/**
 * Implements hook_field_formatter_view().
 * Creates the render array from the form items
 *
 */
function asu_dir_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {

  $settings['admin'] = FALSE;
  $settings['standalone_tree'] = FALSE;

  $element = array(
    '#theme' => 'asu_dir',
    '#items' => $items,
    '#settings' => $settings,
  );

  return $element;
}


/*
* Implements hook_field_widget_info().
*
* Registers custom field_widget
**/
function asu_dir_field_widget_info() {
  return array(
    'asu_directory_form' => array(
      'label' => t('ASU Directory'),
      'field types' => array('asu_directory'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_DEFAULT,
        'default value' => FIELD_BEHAVIOR_DEFAULT,
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_form()
 *
 * Creates widget for the asu_directory custom field
 *
 * @param $form
 * @param $form_state
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 * @param $delta
 * @param $element
 * @return mixed
 */
function asu_dir_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  if ($instance['widget']['type'] == 'asu_directory_form') {

    $settings['admin'] = TRUE;
    $settings['standalone_tree'] = FALSE;
    $settings['whole_tree'] = TRUE;

    $field_configs = isset($items[$delta]['directory_config']) ? $items[$delta]['directory_config'] :
      '{ "show_tree": false,
         "sub_toggle": false,
         "show_managers": false,
         "show_breadcrumbs": true,
         "dept_id" : "",
         "employee_types": ["Show All"],
         "breadcrumb": "",
         "use_custom_q": false,
         "custom_q": {
            "q" : "",
            "fq" : "",
            "sort" : "lastNameSort asc"
         }
       }';

    $field_items = isset($items[$delta]['directory_items']) ? $items[$delta]['directory_items'] : '[' . ASU_DIRECTORY_TOP_LEVEL_DEPT_NID . ']';

    $items[0]['directory_config'] = drupal_json_decode($field_configs);
    $items[0]['directory_items'] = drupal_json_decode($field_items);

    $element['tree_display'] = array(
      '#type' => 'item',
      '#markup' => theme('asu_dir_form_field', array(
        'items' => $items,
        'settings' => $settings
      )),
      '#prefix' => '<div class="row"><h3>ASU Department Directory</h3><div id="asu-directory-form">',
      '#suffix' => '</div>',
      //'#default_value' =>
    );

    $element['directory_config'] = array(
      '#type' => 'hidden',
      '#prefix' => '<div id="dhidden_config">',
      '#suffix' => '</div>',
      '#default_value' => $field_configs,
    );

    $element['directory_items'] = array(
      '#type' => 'hidden',
      '#prefix' => '<div id="dhidden_items">',
      '#suffix' => '</div>',
      '#default_value' => $field_items,
    );

    if (libraries_detect('innovation_bootstrap')) {
      libraries_load('innovation_bootstrap');
    }
    else {
      if (libraries_detect('bootstrap')) {
        libraries_load('bootstrap');
      }
      else {

        $element['#attached']['js']['https://maxcdn.bootstrapcdn.com/bootstrap/3.1.0/js/bootstrap.min.js'] = array(
          'type' => 'external',
        );

        $element['#attached']['css']['https://maxcdn.bootstrapcdn.com/bootstrap/3.1.0/css/bootstrap.min.css'] = array(
          'type' => 'external',
        );
      }
    }

    return $element;
  }
}


/**
 * Implements hook_field_validate().
 *
 * Validate whether the root department selected is valid or not
 *
 */
function asu_dir_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {

  foreach ($items as $delta => $item) {
    if (asu_dir_field_is_empty($item, $field)) {
      $errors[$field['field_name']][$langcode][$delta][] = array(
        'error' => 'Please select a valid root department',
        'message' => t('!name root department is not valid.', array('!name' => t('ASU Directory'))),
      );
    }
  }
}


/**
 * Implements hook_form_alter.
 *
 * Take away the preview option from the node edit form.
 *
 * @param $form
 * @param $form_state
 * @param $form_id
 */

function asu_dir_form_asu_directory_node_form_alter(&$form, &$form_state, $form_id) {
  $form['actions']['preview']['#access'] = FALSE;
}
