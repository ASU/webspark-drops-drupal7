<?php

/**
 * @file
 * asu_directory.field.inc
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
*Function to check if asu_maps_enhanced field is empty
*
*/
function asu_dir_field_is_empty($item, $field) {
  $configs = drupal_json_decode($item['directory_config']);

  if ($configs['dept_id'] == NULL || $configs['dept_id'] == "" || $configs['dept_id'] == ASU_DIRECTORY_TOP_LEVEL_PS_ID) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Implementation of hook_field_formatter_info().
 *
 * This function defines a custom field formatter for
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
 *
 *
 */
function asu_dir_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  /*$map_items = array();*/
  $element = array();

  $admin_flag = FALSE;
  $standalone = FALSE;

  $field_configs = drupal_json_decode($items[0]['directory_config']);
  $field_items = drupal_json_decode($items[0]['directory_items']);

  $display_markup = '';

  $people_class = 'col-md-12';

  $display_markup .= asu_dir_generate_people_display_head();

  //generate the entire tree display
  if ($field_configs['show_tree']) {
    $people_class = 'col-md-8';
    $display_markup .= '<div class="row"><div class="col-md-4">' . asu_dir_departments_content($standalone) . '</div>';
  }

  //generate the people display
  $display_markup .= '<div class="' . $people_class . '" >' . asu_dir_people_content($field_configs, $field_items, $admin_flag) . '</div></div>';

  $element[0]['#markup'] = $display_markup;

  return $element;
}


/*
* Implements hook_field_widget_info().
*
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
 * With this we can control the widget behavior for the asu_directory custom field
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

    $admin_flag = TRUE;
    $standalone = FALSE;

    $field_configs = isset($items[$delta]['directory_config']) ? $items[$delta]['directory_config'] :
      '{
         "show_tree": false,
         "sub_toggle": false,
         "show_managers": false,
         "dept_id" : "",
         "employee_types": ["Show All"],
         "breadcrumb": ""
         }';

    $field_items = isset($items[$delta]['directory_items']) ? $items[$delta]['directory_items'] : '[' . ASU_DIRECTORY_TOP_LEVEL_DEPT_NID . ']';

    $decoded_field_configs = drupal_json_decode($field_configs);
    $decoded_field_items = drupal_json_decode($field_items);

    $root_directory = array();
    $root_directory[] = ASU_DIRECTORY_TOP_LEVEL_DEPT_NID;

    $admin_controls = asu_dir_generate_admin_controls();

    $markup = $admin_controls . "<div class='col-md-4'>" . asu_dir_departments_content($standalone);
    $markup .= "</div><div class='col-md-8'>" . asu_dir_people_content($decoded_field_configs, $decoded_field_items, $admin_flag) . "</div>";

    $element['tree_display'] = array(
      '#type' => 'item',
      '#markup' => $markup,
      '#prefix' => '<div class="row"><h3>ASU Department Directory</h3><div id="asu-dept-mgr-hierarchy">',
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
 * Function to generate the admin controls
 *
 */

function asu_dir_generate_admin_controls() {
  $admin_box = '';

  //this generates the display options (show managers at top/show tree in display)
  $admin_box .= '<div class="row btn-group">';
  $admin_box .= '<h4>Display Options</h4>';
  $admin_box .= '<div class="btn-group col-md-12" role="group" id="asu_directory_admin_toggles">';
  $admin_box .= '<button type="button" id="asu_directory_show_tree" class="btn btn-default">Show Tree in Display</button>';
  $admin_box .= '<button type="button" id="asu_directory_show_managers" class="btn btn-default">Show Managers at Top of Display</button>';
  $admin_box .= '</div>';
  $admin_box .= '</div>';


  //this generates the employee type display, by first grabbing the types from the endpoint
  //and then using logic to group them into 3 columns
  $employee_types = asu_dir_get_employee_types();
  $employee_types = $employee_types['nodes'];

  //Prepend the 'Show All' option to the front of the aray
  $show_all = array('node' => array('name' => 'Show All'));
  array_unshift($employee_types, $show_all);

  //calculate number of types per column
  $num_per_col = count($employee_types) / 3 + 1;

  //start the markup for the employee type selection
  $admin_box .= '<div class="row"  id="asu_directory_employee_type_select">';
  $admin_box .= '<h4>Select employee types to be shown</h4>';
  $admin_box .= '<div class="col-md-4 btn-group-vertical">';

  $count = 1;

  foreach ($employee_types as $type) {
    $admin_box .= '<button type="button" class="btn-group btn btn-default asu_directory_type_select" value="' . $type['node']['name'] . '">' . $type['node']['name'] . '</button>';

    if (($count % $num_per_col == 0) && ($count < count($employee_types))) {
      $admin_box .= '</div>';
      $admin_box .= '<div class="col-md-4 btn-group-vertical">';
    }

    $count++;
  }

  $admin_box .= '</div>';
  $admin_box .= '</div>';
  //end of employee type select generation


  //generate button for asu_dept_mgr tool
  $admin_box .= '<div class="row">';
  $admin_box .= '<a type="button" role="link" class="btn dept-mgr-btn" href="https://isearch.asu.edu/asu_dept_mgr" target="_blank">Go To ASU Directory Admin Tool</a>';
  $admin_box .= '</div>';

  $admin_box .= '<div class="asu_directory_toggle_subdirectory" >Showing this department <span id="asu_directory_show_subs"> + Sub-Departments
      <i class="fa fa-arrow-circle-down"></i></span></div>';

  return $admin_box;
}


/**
 * Implements hook_field_validate().
 *
 * Function to validate whether the root department selected is valid or not
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
 * This is needed to take away the preview option from the node edit form.
 *
 * @param $form
 * @param $form_state
 * @param $form_id
 */

function asu_dir_form_asu_directory_node_form_alter(&$form, &$form_state, $form_id) {
  $form['actions']['preview']['#access'] = FALSE;
}
