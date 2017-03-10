<?php

/**
 * Implements hook_form_alter()
 */
function asu_isearch_form_alter(&$form, &$form_state, $form_id) {

  // hide the profile tabs placeholder field that can be rendered on a node display
  if ($form_id == 'asu_isearch_profile_node_form') {

    // If we are adding a new custon node, or are editing a custom node, then display all fields
    // for editing
    if (arg(1) == 'add' || $form['#node']->field_isearch_eid['und'][0]['value'] == -1) {

      $form['field_isearch_local_photo_url']['#access'] = FALSE;

      $form['field_isearch_eid']['und'][0]['value']['#default_value'] = -1;
      $form['field_isearch_eid']['#access'] = FALSE;
      $form['field_isearch_photo_preference']['#access'] = FALSE;
      $form['field_isearch_photo_permission']['#access'] = FALSE;

      //get the employee types and populate a helper widget
      $employee_types = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_EMPLOYEE_TYPES_ENDPOINT);

      //dropdown widget to select employee type
      $prefix = "<div class='asu-isearch-e-type-select'>" .
        "<select>";
      $prefix .= "<option>Select Employee Type to Autofill</option>";
      foreach ($employee_types['nodes'] as $emp) {
        $prefix .= "<option>" . $emp['node']['name'] . "</option>";
      }

      $prefix .= "</select>";

      $form['field_isearch_employee_type']['#prefix'] = $prefix;
      $form['field_isearch_employee_type']['#suffix'] = "</div>";

      $settings = array();
      $configs = asu_isearch_get_dept_config();
      $dept_tree = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_TREE_ENDPOINT);

      $locations = array();

      foreach ($configs['items'] as $conf) {
        $root = asu_isearch_dept_find_root($dept_tree, $conf['dept_nid']);

        if (isset($conf['options']) && $conf['options']['subdepts']) {
          $newItem = new stdClass();
          $newItem->name = $root->name;
          $newItem->dept_nid = $root->dept_nid;

          $locations[] = $newItem;
        }
        else {
          $locations = array_merge($locations, asu_dir_utilities_dept_get_tree_data($root));
        }
      }

      //sort by the name of the department
      function naturalSortByName($a, $b) {
        return strnatcmp($a->name, $b->name);
      }

      usort($locations, "naturalSortByName");

      $settings['employee_types'] = $employee_types;
      $settings['imported_depts'] = $locations;

      drupal_add_js(array('asu_isearch_profile_form' => $settings), 'setting');
      drupal_add_js(drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch_profile_form.js');

      if (isset($form['field_isearch_affiliations']['und'])) {

        foreach ($form['field_isearch_affiliations']['und'] as $key => $item) {
          if (is_int($key)) {

            //dropdown to select department
            $dept_prefx = "<div class='asu-isearch-dept-select-wrap'>";
            $dept_prefx .= "<select class='chosen-disable'>";
            $dept_prefx .= "<option>Select Department to Autofill</option>";
            foreach ($locations as $loc) {
              $dept_prefx .= "<option deptnid='$loc->dept_nid'>$loc->name</option>";
            }

            $dept_prefx .= "</select>";

            $form['field_isearch_affiliations']['und'][$key]['field_isearch_affil_dept_id']['#prefix'] = $dept_prefx;
            $form['field_isearch_affiliations']['und'][$key]['field_isearch_affil_dept_name']['#suffix'] = "</div>";

            //dropdown widget to select employee type
            $prefx = "<div class='asu-isearch-empl-type-select'>" .
              "<select>";
            $prefx .= "<option>Select Employee Type to Autofill</option>";
            foreach ($employee_types['nodes'] as $emp) {
              $prefx .= "<option>" . $emp['node']['name'] . "</option>";
            }

            $prefx .= "</select>";

            $form['field_isearch_affiliations']['und'][$key]['field_isearch_affil_empl_type']['#prefix'] = $prefx;
            $form['field_isearch_affiliations']['und'][$key]['field_isearch_affil_empl_key']['#suffix'] = '</div>';
          }
        }
      }
    }
    else {

      $form['field_isearch_profile_tabs']['#access'] = FALSE;
//     $form['field_isearch_hash']['#access'] = FALSE;
      $form['title'] = array(
        '#default_value' => 'Set on save...',
        '#disabled' => TRUE,
      );

      // provide a list of fields we allow users to edit
      $field_exception_manifest = array(
        'field_isearch_local_tags',
        'field_isearch_local_photo_url',
        'field_isearch_local_office_hours',
        'field_isearch_local_primary_aff',
        'field_isearch_affiliations',
        'field_isearch_affil_local_weight',
        'field_isearch_link_building_code',
      );

      // also exclude the new fields,
      // since they don't follow naming convention
      $also_excluded = array(
        'field_consulting',
        'field_board',
        'field_industry_positions',
        'field_pro_bono'
      );

      // Hide the rest of the fields
      // handle top level fields
      foreach ($form as $form_field => $value) {
        $is_local_field = (bool) preg_match('/^field_isearch_local_/', $form_field);

        if ((!$is_local_field && preg_match('/^field_isearch_/', $form_field) && !in_array($form_field, $field_exception_manifest)) ||
          in_array($form_field, $also_excluded)
        ) {

          if (asu_isearch_devmode() === FALSE) {
            $form[$form_field]['#disabled'] = TRUE;
            $form[$form_field]['#access'] = FALSE;
          }
        }
      }

      // loop through any field collection fields
      $protected_field_collections = array(
        'field_isearch_affiliations',
      );

      foreach ($protected_field_collections as $field_collection) {

        if (asu_isearch_devmode() === FALSE) {
          $form[$field_collection][LANGUAGE_NONE]['add_more']['#disabled'] = TRUE;
        }

        foreach ($form[$field_collection][LANGUAGE_NONE] as $item_key => $item_value) {
          if (is_integer($item_key)) {
            foreach ($form[$field_collection][LANGUAGE_NONE][$item_key] as $field_key => $field_value) {
              if (asu_isearch_devmode() === FALSE) {
                $form[$field_collection][LANGUAGE_NONE][$item_key]['remove_button']['#disabled'] = TRUE;
                $form[$field_collection][LANGUAGE_NONE][$item_key]['field_isearch_affil_rank_tenure']['#access'] = FALSE;
                $form[$field_collection][LANGUAGE_NONE][$item_key]['field_isearch_affil_rank_weight']['#access'] = FALSE;
              }

              if (preg_match('/^field_isearch_/', $field_key) && !in_array($field_key, $field_exception_manifest)) {
                if (asu_isearch_devmode() === FALSE) {
                  $form[$field_collection][LANGUAGE_NONE][$item_key][$field_key]['#disabled'] = TRUE;
                }
              }
            }
          }
        }
      }
    }
  }

  // restrict access to delete isearch fields
  if (asu_isearch_devmode() === FALSE && $form_id == 'field_ui_field_delete_form') {
    if (preg_match('/field_isearch_.*?delete$/', $form['#action'])) {
      drupal_access_denied();
      drupal_exit();
    }
  }

  // do not allow any isearch fields to be deleted by hiding the link (fields prefixed with 'field_isearch_')
  if (asu_isearch_devmode() === FALSE && $form_id == 'field_ui_field_overview_form') {
    $field_groups = array(
      'group_basic',
      'group_links',
      'group_expertise_area',
      'group_personal',
      'group_research',
      'group_teaching',
      'group_public_work',
      'group_media',
      'group_advanced',
    );

    foreach ($form['#groups'] as $field_key) {
      if (in_array($field_key, $field_groups)) {
        $form['fields'][$field_key]['delete'] = array();
        $form['fields'][$field_key]['edit'] = array();
      }
    }

    foreach ($form['#fields'] as $field_key) {
      if (preg_match('/^field_isearch_/', $field_key)) {
        $form['fields'][$field_key]['delete'] = array();
        $form['fields'][$field_key]['edit'] = array();
      }
    }
  }

  if ($form_id == 'views_exposed_form') {
    if (asu_isearch_is_isearch_view($form_state['view'])) {
      asu_isearch_directory_list_form_alter($form, $form_state, $form_id);
    }
  }
}

/****
 * Implements hook_form_alter
 *
 * Modify the directory listing views exposed form
 *
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function asu_isearch_directory_list_form_alter(&$form, &$form_state, $form_id) {

  $form['#attributes'] = array(
    'class' => array('isearch-directory-filters'),
  );

  // Rebuild rank title field into select field
  $form['field_isearch_affil_title_value']['#theme'] = 'select';
  $form['field_isearch_affil_title_value']['#type'] = 'select';
  $form['field_isearch_affil_title_value']['#multiple'] = FALSE;
  unset($form['field_isearch_affil_title_value']['#size']);

  $form['field_isearch_affil_title_value']['#options'] = array('' => t('Select Title')) + asu_isearch_get_rank_titles();

  if (isset($_GET['field_isearch_affil_title_value'])) {
    $form['field_isearch_affil_title_value']['#value'] = check_plain($_GET['field_isearch_affil_title_value']);
  }

  // reset label for expertise field
  $form['field_isearch_expertise_areas_tid']['#options']['All'] = t('Select Expertise');


  $form['#attached']['css'][] = drupal_get_path('module', 'asu_isearch') . '/css/asu_isearch_omni.css';


  // Reset exposed form theme so we can set weights on fields
  $form['#theme'] = '';
  $form['sort_by']['#title'] = '';
  if (isset($form['sort_by']['#options'])) {
    foreach ($form['sort_by']['#options'] as $key => $value) {
      $form['sort_by']['#options'][$key] = "Sort by {$value}";
    }
  }

  $form['submit']['#weight'] = 9;

  // Hide sort order field
  $form['sort_order']['#type'] = 'hidden';

  // tag and hide fields so we can manipulate them with attached javascript
  $hidden_fields = array(
    'omni_configs'
  );

  foreach ($hidden_fields as $fieldname) {
    $form[$fieldname]['#type'] = 'hidden';
    //$form[$fieldname]['#attributes']['class'] = array('omni-search-field');
  }

  // hide some filters if they do not have any options
  if (isset($form['field_isearch_expertise_areas_tid']['#options']) && count($form['field_isearch_expertise_areas_tid']['#options']) == 1) {
    $form['field_isearch_expertise_areas_tid']['#access'] = FALSE;
  }
}

