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
*Check if asu_dir field is empty
*
*/
function asu_dir_field_is_empty($item, $field) {

  $tree_items = array();

  if (isset($item['horizontal_tabs']['content']['content_tabs']['department']['isearch_dept_tree'])) {
    $tree_items = drupal_json_decode($item['horizontal_tabs']['content']['content_tabs']['department']['isearch_dept_tree']);
    if (count($tree_items['items']) > 0) {
      return FALSE;
    }
    else {
      return TRUE;
    }
  }
  else {
    return TRUE;
  }
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
    '#theme' => 'asu_dir_ajax_solr_field',
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

    variable_set('panopoly_magic_live_preview', 0);

    //$form['#submit'][] = 'asu_isearch_form_fieldable_panels_panes_fieldable_panels_pane_content_type_edit_form_submit';
    $form['#pre_render'][] = 'asu_dir_field_widget_form_group_pre_render';
    $form['#attributes']['class'][] = 'asu-isearch-configuration';

    $settings['admin'] = TRUE;
    $settings['standalone_tree'] = FALSE;
    $settings['whole_tree'] = TRUE;


    $default_configs = asu_dir_get_default_config();

    $field_configs = isset($items[$delta]['directory_config']) ?  drupal_json_decode($items[$delta]['directory_config']) : $default_configs;
    $field_items = isset($items[$delta]['directory_items']) ? drupal_json_decode($items[$delta]['directory_items']) : array(); //'[' . ASU_DIR_UTILITIES_TOP_LEVEL_DEPT_NID . ']';

    $config = array_merge($default_configs, $field_configs);

    // handle the case of legacy configuration
    if (!empty($field_items)&& isset($field_configs['dept_id']) && empty($config['depts']['items'])) {
      $config['depts']->items[0] = array(
        'dept_id' => $field_configs['dept_id'],
        'dept_nid' => $field_items[0],
        'tree_nids' => $field_items
      );

      $config['depts']['options'][$field_configs]['dept_id'] = array(
        'subdepts' => $config['sub_toggle']
      );
    }

    $element['#attributes']['class'][] = 'asu-isearch-configuration';

    $element['#attached']['css'][] = drupal_get_path('module', 'asu_dir') . '/css/asu_dir_form.css';
    //asu_isearch_load_js();
    $element['#attached']['css'][] = drupal_get_path('module', 'asu_dir') . '/css/asu_dir_config.css';
    $element['#attached']['js'][] = drupal_get_path('module', 'asu_dir') . '/js/form/bootstrap.js';
    $element['#attached']['js'][] = drupal_get_path('module', 'asu_dir') . '/js/form/asu_dir_config.js';
    $element['#attached']['js'][] = drupal_get_path('module', 'asu_dir') . '/js/form/asu_dir_field_config.js';

    // Horizontal tabs definition
    $element['horizontal_tabs'] = array(
      '#type' => 'horizontal_tabs',
      '#tree' => TRUE,
      '#prefix' => '<div id="isearch-config-tabs">',
      '#suffix' => '</div>',
      '#attached' => array(
        'css' => array(drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.css'),
        'js' => array(drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.js'),
      ),
    );

    // Content horizontal tab definition
    $element['horizontal_tabs']['content'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Content'),
    );

    // Content vertical tabs definition
    $element['horizontal_tabs']['content']['content_tabs'] = array(
      '#type' => 'vertical_tabs',
      '#default_tab' => '',
    );


    // Content -> Department group
    $element['horizontal_tabs']['content']['content_tabs']['department'] = array(
      '#type' => 'fieldset',
      '#title' => t('Department'),
      '#collapsible' => TRUE,
      '#group' => 'content_tabs',
    );

    $element['horizontal_tabs']['content']['content_tabs']['department']['include_subdepts'] = array(
      '#type' => 'checkbox',
      '#title' => 'Include sub-departments',
      '#default_value' => $config['include_subdepts'],
      '#access' => FALSE,
    );

    $element['horizontal_tabs']['content']['content_tabs']['department']['show_tree'] = array(
      '#type' => 'checkbox',
      '#title' => 'Show Department Tree',
      '#default_value' => $config['show_tree']
    );

    $element['horizontal_tabs']['content']['content_tabs']['department']['new_tab'] = array(
      '#type' => 'checkbox',
      '#title' => 'Open Profile Links in New Tab',
      '#default_value' => $config['new_tab']
    );

    $element['horizontal_tabs']['content']['content_tabs']['department']['show_breadcrumbs'] = array(
      '#type' => 'checkbox',
      '#title' => 'Show Breadcrumbs',
      '#default_value' => $config['show_breadcrumbs']
    );

    // get all nids of the dept tree, and pass them to
    // the dept picker
    $tree = asu_dir_utilities_get_dept_tree();
    $tree_nids = asu_dir_utilities_dept_get_tree_nids($tree);

    $element['horizontal_tabs']['content']['content_tabs']['department']['isearch_dept_tree'] = array(
      '#type' => 'asu_dept_picker',
      '#default_value' => json_encode($config['depts']),
      '#attributes' => array('id' => 'filter_departments'),
      '#delta' => 0,//$element['#entity']->fpid,
      '#asu_dept_tree' => array(
        'showOnly' => $tree_nids,
      ),
    );
    /** end department picker **/


    // Content -> Employee Types group
    $element['horizontal_tabs']['content']['content_tabs']['employeetypes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Employee Types'),
      '#collapsible' => TRUE,
      '#group' => 'content_tabs',
    );

    /*
    $element['horizontal_tabs']['content']['content_tabs']['employeetypes']['employee_type_exclude'] = array(
      '#type' => 'radios',
      '#options' => array(0 => 'Show', 1 => 'Hide'),
      '#title' => 'Select employee types to Show/Hide',
      '#default_value' => $config->employee_type_exclude,
      '#description' => t('Show will include all types selected below. Hide will include all types except those selected.'),
    );*/

    // build employee types field groups
    $default_employee_types = array();
    foreach ($config['employee_types'] as $value) {
      $default_employee_types[] = $value;
    }

    // helper checkbox to check all employee types
    $element['horizontal_tabs']['content']['content_tabs']['employeetypes']['select_all'] = array(
      '#type' => 'checkbox',
      '#title' => 'Toggle All',
      '#default_value' => in_array('All', $default_employee_types) ? 1 : 0,
      '#description' => t('Toggle all the employee type options below.'),
      '#attributes' => array(
        'id' => 'toggle-all-employee-types',
      ),
    );

    // create a map of how we want to organize known employee types
    // if the api fetches a new item, we will drop it under 'other'
    $employee_type_map = array(
      // Faculty
      'Faculty' => 'faculty',
      'Faculty w/Admin Appointment' => 'faculty',
      'Academic Professional' => 'faculty',
      'Academic Prof w/Admin Appt' => 'faculty',
      // Staff
      'Administrative' => 'staff',
      'University Staff' => 'staff',
      'Classified' => 'staff',
      // Other
      'Post Doctoral Scholars' => 'other',
      'Graduate Assistant/Associate' => 'other',
      'Student Worker' => 'other',
    );

    // create our groups...
    $employee_type_groups = array('Faculty', 'Staff', 'Other');

    // dynamically create our field groups
    foreach ($employee_type_groups as $group_name) {
      $group_key = strtolower($group_name);
      $element['horizontal_tabs']['content']['content_tabs']['employeetypes'][$group_key] = array(
        '#title' => $group_name,
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#options' => array(),
        '#attributes' => array(
          'class' => array(
            'employee-types-group',
            'employee-types-group-' . $group_key
          ),
        ),
      );
      $element['horizontal_tabs']['content']['content_tabs']['employeetypes'][$group_key]['options'] = array(
        '#type' => 'checkboxes',
        '#options' => array(),
        '#default_value' => $default_employee_types,
      );
    }

    // fetch employee types
    $employee_types = asu_dir_utilities_get_employee_types();

    // employee type options array
    $employee_types_options = array();

    // loop over our employee types and assign to field group
    foreach ($employee_types['nodes'] as $employee_type_node) {
      $employee_type = $employee_type_node['node']['name'];
      $employee_types_options[] = $employee_type;

      // we will set the group to 'other' by default unless it is identified
      $group = 'other';
      if (isset($employee_type_map[$employee_type])) {
        $group = $employee_type_map[$employee_type];
      }

      // add checkbox option to appropriate field group
      $element['horizontal_tabs']['content']['content_tabs']['employeetypes'][$group]['options']
      ['#options'][$employee_type] = $employee_type;
    }

    // tenure control will be added to faculty employee types group for now

    $default_tenure_display = asu_dir_get_tenure_config($config['tenure_display']);

    $element['horizontal_tabs']['content']['content_tabs']['employeetypes']['faculty']['tenure_display'] = array(
      '#type' => 'radios',
      '#options' => drupal_map_assoc(array('Tenure', 'Non-Tenure', 'Both')),
      '#default_value' => $default_tenure_display,
      '#title' => 'Show Tenure/Non-Tenure/Both',
      '#description' => t('This selection will only apply to types in the Faculty list above.'),
      '#weight' => 10,
    );

    // Content -> Other Filters group
    $element['horizontal_tabs']['content']['content_tabs']['otherfilters'] = array(
      '#type' => 'fieldset',
      '#title' => t('Other Filters'),
      '#collapsible' => TRUE,
      '#group' => 'content_tabs',
    );

    /*$expertise_vocabulary = taxonomy_vocabulary_machine_name_load('isearch_expertise');
    if ($expertise_terms = taxonomy_get_tree($expertise_vocabulary->vid, 0, NULL, TRUE)) {
      $expertise_areas = array();

      foreach ($expertise_terms as $term) {
        $expertise_areas[$term->tid] = $term->name;
      }

      if (!is_array($config->expertise_areas)) {
        $config->expertise_areas = (array) $config->expertise_areas;
      }*/

    //if (!empty($expertise_areas)) {

    //for right now we'll go with a regex filter like the  filter title
    $element['horizontal_tabs']['content']['content_tabs']['otherfilters']['isearch_expertise_areas'] = array(
      '#type' => 'textfield',
      '#default_value' => $config['expertise_areas'],
      '#title' => t('Limit results by the expertise area. Regular expression allowed.'),
    );
    /*}
  }*/

    $element['horizontal_tabs']['content']['content_tabs']['otherfilters']['filter_title'] = array(
      '#type' => 'textfield',
      '#title' => 'Filter Title',
      '#description' => t('Limit results by the affiliation title. Regular expression allowed.'),
      '#default_value' => $config['filter_title'],
    );

    /*$local_tags_vocabulary = taxonomy_vocabulary_machine_name_load('isearch_local_tags');

    if ($local_tags_terms = taxonomy_get_tree($local_tags_vocabulary->vid, 0, NULL, TRUE)) {
      $local_tags = array();

      foreach ($local_tags_terms as $term) {
        $local_tags_areas[$term->tid] = $term->name;
      }

      if (!is_array($config->local_tags)) {
        $config->local_tags = (array) $config->local_tags;
      }

      $element['horizontal_tabs']['content']['content_tabs']['otherfilters']['isearch_local_tags'] = array(
        '#type' => 'select',
        '#options' => $local_tags_areas,
        '#default_value' => $config->local_tags,
        '#multiple' => TRUE,
        '#title' => t('Filter profiles by these local tags'),
      );
    }*/

    // Appearance horizontal tab definition
    $element['horizontal_tabs']['appearance'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Appearance'),
    );

    // Appearance vertical tabs definition
    $element['horizontal_tabs']['appearance']['appearance_tabs'] = array(
      '#type' => 'vertical_tabs',
      '#default_tab' => '',
    );


    $display_types = array(
      'list' => 'List',
      'grid' => 'Grid'
    );

    // Appearance -> Display group
    $element['horizontal_tabs']['appearance']['appearance_tabs']['display'] = array(
      '#type' => 'fieldset',
      '#title' => t('Display'),
      '#collapsible' => TRUE,
      '#group' => 'appearance_tabs',
    );

    // Appearance -> Sorting group
    $element['horizontal_tabs']['appearance']['appearance_tabs']['display']['display_type'] = array(
      '#type' => 'select',
      '#options' => $display_types,
      '#title' => 'Display Type',
      '#default_value' => $config['display_type'],
    );

    // Appearance -> Sorting group
    $element['horizontal_tabs']['appearance']['appearance_tabs']['sorting'] = array(
      '#type' => 'fieldset',
      '#title' => t('Sorting'),
      '#collapsible' => TRUE,
      '#group' => 'appearance_tabs',
    );

    $element['horizontal_tabs']['appearance']['appearance_tabs']['sorting']['show_filter_sort'] = array(
      '#type' => 'checkbox',
      '#title' => 'Hide Rank Sort Option',
      '#default_value' => $config['hide_filter_rank_sort'],
      '#description' => t('Hide the sorting option to sort employees by rank within a department. The rank sort order can be modified at
        https://isearch.asu.edu/asu_dept_mgr.'),
    );

    $default_sort_by_options = array(
      'tsort' => 'Rank',
      'lastNameSort' => 'Last Name',
      'firstNameSort' => 'First Name',
    );

    $element['horizontal_tabs']['appearance']['appearance_tabs']['sorting']['default_sort_by'] = array(
      '#type' => 'select',
      '#options' => $default_sort_by_options,
      '#title' => 'Default sort order',
      '#default_value' => $config['default_sort_by'],
    );

    // Appearance -> Exposed filters group
    $element['horizontal_tabs']['appearance']['appearance_tabs']['exposed'] = array(
      '#type' => 'fieldset',
      '#title' => t('Exposed Filters'),
      '#collapsible' => TRUE,
      '#group' => 'appearance_tabs',
    );

    $element['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filters'] = array(
      '#type' => 'checkbox',
      '#title' => 'Show filters',
      '#default_value' => $config['show_filters'],
      '#description' => t('These options are shown to visitors, allowing them to further sort and filter the list.'),
    );

    $element['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_omni'] = array(
      '#type' => 'checkbox',
      '#title' => 'Search box',
      '#default_value' => $config['show_filter_omni'],
      '#description' => t('This will allow visitors to search for keywords in titles, expertise areas, and short bios (even if these columns are not enabled in appearance).'),
    );

    $element['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_expertise'] = array(
      '#type' => 'checkbox',
      '#title' => 'Expertise dropdown',
      '#default_value' => $config['show_filter_expertise'],
      '#description' => t('This will allow visitors to filter the list to the specified expertise area. This dropdown will list all expertise areas associated with people in the department.'),
    );

    /*  TODO:  can we have a primary title facet?
    $element['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_titles'] = array(
      '#type' => 'checkbox',
      '#title' => 'Title dropdown',
      '#default_value' => $config->show_filter_titles,
      '#description' => t('This will allow visitors to filter the list by people of a specified title. This dropdown is populated with titles of people in the current list only.'),
    );*/

    $element['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_faculty_titles'] = array(
      '#type' => 'checkbox',
      '#title' => 'Faculty Title dropdown',
      '#default_value' => $config['show_filter_faculty_titles'],
      '#description' => t('This will allow visitors to filter the list by people of a specified faculty title. This dropdown is populated with titles of people in the current list only.'),
    );


    $element['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_az_index'] = array(
      '#type' => 'checkbox',
      '#title' => 'Show A-Z index',
      '#default_value' => $config['show_az_index'],
      '#description' => t('Allows visitors to click on a letter that will filter the directory list to profiles with last names beginning with that letter.'),
    );


    // Appearance -> Paging group
    $element['horizontal_tabs']['appearance']['appearance_tabs']['paging'] = array(
      '#type' => 'fieldset',
      '#title' => t('Paging'),
      '#collapsible' => TRUE,
      '#group' => 'appearance_tabs',
    );

    $element['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_display'] = array(
      '#type' => 'select',
      '#options' => array(
        'paged' => 'Paged output',
        'all' => 'Display all items'
      ),
      '#title' => 'Display pagination',
      '#default_value' => $config['pager_display'],
    );

    $element['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_items_per_page'] = array(
      '#type' => 'textfield',
      '#title' => 'Items to display per page.',
      '#description' => t('The number of items to display per page. Enter 0 for no limit.'),
      '#default_value' => $config['pager_items_per_page'],
    );

    // Appearance -> Columns group
    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns'] = array(
      '#type' => 'fieldset',
      '#title' => t('Columns'),
      '#collapsible' => TRUE,
      '#group' => 'appearance_tabs',
    );
    /*
    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_header'] = array(
      '#type' => 'checkbox',
      '#title' => 'Header labels',
      '#default_value' => $config->display_header,
    );*/

    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_photo'] = array(
      '#type' => 'checkbox',
      '#title' => 'Photo',
      '#default_value' => $config['display_photo'],
    );
    /*
    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_name'] = array(
      '#type' => 'checkbox',
      '#title' => 'Name/Title column',
      '#default_value' => $config->display_name,
    );

    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_contact'] = array(
      '#type' => 'checkbox',
      '#title' => 'Contact column',
      '#default_value' => $config->display_contact,
    );*/

    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_expertise'] = array(
      '#type' => 'checkbox',
      '#title' => 'Expertise column',
      '#default_value' => $config['display_expertise'],
    );

    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_building'] = array(
      '#type' => 'checkbox',
      '#title' => 'Location',
      '#default_value' => $config['display_building'],
      '#description' => t('The building and room fields are displayed in the contact column. They are populated from the first and second lines of Campus Address.'),
    );

    /*
    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_room'] = array(
      '#type' => 'checkbox',
      '#type' => 'checkbox',
      '#title' => 'Room',
      '#default_value' => $config->display_room,
      '#description' => t('The building and room fields are displayed in the contact column. They are populated from the first and second lines of Campus Address.'),
    );*/

    /*
    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns']['link_building_codes'] = array(
      '#type' => 'checkbox',
      '#title' => 'Link building codes',
      '#default_value' => $config->link_building_codes,
      '#description' => t('This will link properly formatted building codes to the ASU interactive map. If the building code is not properly formatted, it will not be linked.'),
    );*/

    $element['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_short_bio'] = array(
      '#type' => 'checkbox',
      '#title' => 'Display short bio field?',
      '#default_value' => $config['display_short_bio'],
      '#description' => t('The short bio is displayed below the title in the name column.'),
    );

    // Advanced horizontal tab definition
    $element['horizontal_tabs']['advanced'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Advanced'),
    );

    // Advanced tab content
    $element['horizontal_tabs']['advanced']['use_custom_q'] = array(
      '#type' => 'checkbox',
      '#title' => 'Custom Solr Filter',
      '#default_value' => $config['use_custom_q'],
      '#description' => t('Specify custom filter query value to use in the Solr query of department people.
                        Check out the Solr documentation on the "fq" param here:  https://wiki.apache.org/solr/CommonQueryParameters.
                        Also, the field schema for ASU Solr Directory can be found here:  https://asudir-solr.asu.edu/asudir/directory/schema/fields.'),
    );

    $element['horizontal_tabs']['advanced']['fq'] = array(
      '#type' => 'textarea',
      '#title' => 'fq=',
      '#default_value' => $config['custom_q']['fq'],
      '#description' => t('The "fq" value for the Solr query.'),
    );

    // Advanced horizontal tab definition
    $element['horizontal_tabs']['preview'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Preview'),
      '#access' => FALSE,
    );

    $element['horizontal_tabs']['preview']['preview_placeholder'] = array(
      '#type' => 'item',
      '#markup' => '<div id="isearch-preview"></div>',
    );

    // executes iSearch configuration form visuals
    $element['footer']['react'] = array(
      '#type' => 'item',
      '#markup' => '<script type="text/javascript">initIsearchConfig();</script>',
    );

    // Hide isearch config field
    $element['field_isearch_config']['#access'] = FALSE;
    unset($element['#validate']);
    $element['#validate'] = array('asu_dir_field_validate');

    return $element;
  }
}

function asu_dir_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {

  // store values
  $values = $items[0];

  $employee_types = array();

  if ($values['horizontal_tabs']['content']['content_tabs']['employeetypes']['select_all']) {
    $employee_types = array('All');
  }
  else {
    $employee_type_groups = array('faculty', 'staff', 'other');
    foreach ($employee_type_groups as $group_key) {
      foreach ($values['horizontal_tabs']['content']['content_tabs']['employeetypes'][$group_key]['options'] as $value) {
        if ($value !== 0) {
          $employee_types[] = $value;
        }
      }
    }
  }

  if (empty($employee_types)) {
    array_push($employee_types, 'All');
  }

  $depts = drupal_json_decode($values['horizontal_tabs']['content']['content_tabs']['department']['isearch_dept_tree']);

  $config = array(

    // Content -> Department
    //'include_subdepts'      => $values['horizontal_tabs']['content']['content_tabs']['department']['include_subdepts'],
    'depts' => $depts,
    'show_tree' => $values['horizontal_tabs']['content']['content_tabs']['department']['show_tree'],
    'new_tab' => $values['horizontal_tabs']['content']['content_tabs']['department']['new_tab'],
    'show_breadcrumbs' => $values['horizontal_tabs']['content']['content_tabs']['department']['show_breadcrumbs'],

    // Content -> Employee types
    'employee_types' => $employee_types,
    //'employee_type_exclude' => $values['horizontal_tabs']['content']['content_tabs']['employeetypes']['employee_type_exclude'],
    'tenure_display' => $values['horizontal_tabs']['content']['content_tabs']['employeetypes']['faculty']['tenure_display'],

    // Content -> Other filters
    'expertise_areas' => $values['horizontal_tabs']['content']['content_tabs']['otherfilters']['isearch_expertise_areas'],
    //'local_tags'=> $values['horizontal_tabs']['content']['content_tabs']['otherfilters']['isearch_local_tags'],
    'filter_title' => $values['horizontal_tabs']['content']['content_tabs']['otherfilters']['filter_title'],

    //Appearance -> Display
    'display_type' => $values['horizontal_tabs']['appearance']['appearance_tabs']['display']['display_type'],

    // Appearance -> Sorting
    //'show_managers'         => $values['horizontal_tabs']['appearance']['appearance_tabs']['sorting']['show_managers'],
    'default_sort_by' => $values['horizontal_tabs']['appearance']['appearance_tabs']['sorting']['default_sort_by'],
    'hide_filter_rank_sort' => $values['horizontal_tabs']['appearance']['appearance_tabs']['sorting']['show_filter_sort'],

    // Appearance -> Exposed Filters
    'show_filters' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filters'],
    'show_filter_omni' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_omni'],
    'show_filter_expertise' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_expertise'],

    //TODO:  see if a regular title facet is viable.  seem to remember a primaryTitlesFacet, but it doesn't appear to be there now
    //'show_filter_titles'    => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_titles'],
    'show_filter_faculty_titles' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_faculty_titles'],

    'show_az_index' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_az_index'],

    // Appearance -> Paging
    'pager_display' => $values['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_display'],
    'pager_items_per_page' => $values['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_items_per_page'],
    //'pager_offset'          => $values['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_offset'],

    // Appearance -> Columns

    //'display_header' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_header'],
    'display_photo' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_photo'],
    //'display_name' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_name'],
    //'display_contact' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_contact'],
    'display_expertise' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_expertise'],
    'display_building' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_building'],

    // deprecated display room, since we now have addressLine1 and Line2 fields, of which we can't guarantee that either
    // is a room or a building
    //'display_room' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_room'],
    //'link_building_codes' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['link_building_codes'],
    'display_short_bio' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_short_bio'],

    // Advanced
    'use_custom_q' => $values['horizontal_tabs']['advanced']['use_custom_q'],
    'custom_q' => array(
      'fq' => $values['horizontal_tabs']['advanced']['fq']
    )
  );


  $root = $depts['items'][0]['dept_id'];

  if ($depts['options'][$root]['subdepts'] == TRUE) {
    $tree_nids = $depts['items'][0]['tree_nids'];
    $config['sub_toggle'] = TRUE;
  }
  else {
    $tree_nids = array($depts['items'][0]['dept_nid']);
    $config['sub_toggle'] = FALSE;
  }

  $config['dept_id'] = $root;

  $items[0]['directory_config'] = drupal_json_encode($config);
  $items[0]['directory_items'] = drupal_json_encode($tree_nids);

  //$form_state['entity']->field_isearch_config[LANGUAGE_NONE][0]['value'] = json_encode($config);
  //entity_save('fieldable_panels_pane', $form_state['entity']);
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
