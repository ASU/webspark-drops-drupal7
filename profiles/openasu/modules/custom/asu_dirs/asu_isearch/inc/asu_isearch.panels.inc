<?php

/**
 * Implements hook_panels_pane_content_alter().
 */
function asu_isearch_panels_pane_content_alter($content, $pane, $args, $contexts) {
  $content_empty = (is_object($content) && empty($content->content));
  $content_disabled = (isset($content->content[0]['#markup']) && strlen($content->content[0]['#markup']) === 0);

  if (is_null($content) || $content_empty || $content_disabled) {
    return;
  }

  if ($pane->subtype == 'node:field_isearch_rsrch_website') {
    $website = $content->content['#items'][0]['value'];
    $content->content[0]['#markup'] = l($website, $website, array(
      'attributes' => array(
        'target' => '_blank',
      )
    ));
  }

  if ($pane->subtype == 'node:field_isearch_tch_website') {
    $website = $content->content['#items'][0]['value'];
    $content->content[0]['#markup'] = l($website, $website, array(
      'attributes' => array(
        'target' => '_blank',
      )
    ));
  }

  // Get permission to display profile image
  if ($pane->subtype == 'node:field_isearch_photo_url') {
    // check and see if we have uploaded a local image
    // if so, display it vs whatever settings they currently have
    if (isset($content->content['#object']->field_isearch_local_photo_url) && !empty($content->content['#object']->field_isearch_local_photo_url)) {
      $content->content[0]['#item'] = (array) $content->content['#object']->field_isearch_local_photo_url[LANGUAGE_NONE][0];
    }
    else {
      $photo_preference = $content->content['#object']->field_isearch_photo_preference[LANGUAGE_NONE][0]['value'];
      $photo_permission = $content->content['#object']->field_isearch_photo_permission[LANGUAGE_NONE][0]['value'];

      if ($photo_preference == 'none' || $photo_permission != 'public') {

        $display_default_photo = variable_get('isearch_display_default_photo', FALSE);
        $default_photo = asu_isearch_get_default_photo();

        if ($display_default_photo && $default_photo) {
          $content->content[0]['#item'] = (array) $default_photo;
        }
        else {
          $content->content['#access'] = FALSE;
        }
      }
    }

    $content->content[0]['#image_style'] = 'asu_isearch_profile';
  }

  // Add email icon to email address
  if ($pane->subtype == 'node:field_isearch_email') {
    $email = $content->content['#items'][0]['email'];
    $content->content[0]['#markup'] = l('<i class="fa fa-envelope"></i> ' . $email, 'mailto:' . $email, array('html' => TRUE));
  }

  // Add email icon to phone number
  if ($pane->subtype == 'node:field_isearch_phone') {
    $phone = $content->content['#items'][0]['value'];
    $link = preg_replace('/[^\d]/', '', $phone);
    $content->content[0]['#markup'] = l('<i class="fa fa-phone"></i> ' . $phone, 'tel:' . $link, array('html' => TRUE));
  }

  // Add file icon to CV url
  if ($pane->subtype == 'node:field_isearch_cv_url') {
    $cvurl = $content->content['#items'][0]['value'];
    $link = ASU_ISEARCH_DIRECTORY_URL . '/sites/default/files/' . $cvurl;
    $cvinfo = pathinfo($link);
    $content->content[0]['#markup'] = '<i class="fa fa-file"></i> ' . l($cvinfo['basename'], $link, array(
        'attributes' => array(
          'target' => '_blank',
        ),
      ));
  }

  // @TODO: There could possibly be a small bug here if there isn't a building but a room is present
  // Add pin icon to location
  if ($pane->subtype == 'node:field_isearch_campus_building') {
    $building = $content->content['#items'][0]['value'];

    $global_link_buildings = variable_get('isearch_link_buildings', FALSE);
    $profile_link_buildings = FALSE;

    if (!empty($content->content['#object']->field_isearch_link_building_code)) {
      $profile_link_buildings = (bool) $content->content['#object']->field_isearch_link_building_code[LANGUAGE_NONE][0]['value'];
    }

    $building_code = asu_isearch_fetch_asu_building_code($content->content['#items'][0]['value']);

    // test for a 2-5 alphanumeric code
    if ($global_link_buildings && $profile_link_buildings && $building_code) {

      // look for campus - this may not be required?
      $campus = '';
      if (!empty($content->content['#object']->field_isearch_primary_campus)) {
        $campus = '&campus=' . check_plain($content->content['#object']->field_isearch_primary_campus[LANGUAGE_NONE][0]['value']);
      }

      $content->content[0]['#markup'] = l('<i class="fa fa-map-marker"></i> ' . $building_code, 'http://www.asu.edu/map/interactive/?building=' . $building_code . $campus,
        array(
          'attributes' => array(
            'target' => '_blank',
          ),
          'html' => TRUE,
        ));
    }
    else {
      $content->content[0]['#markup'] = '<i class="fa fa-map-marker"></i> ' . $building;
    }
  }


  // social icons
  $social_fields_icons = array(
    'node:field_isearch_social_facebook' => 'fa-facebook-square',
    'node:field_isearch_social_twitter' => 'fa-twitter-square',
    'node:field_isearch_social_googleplus' => 'fa-google-plus-square',
    'node:field_isearch_social_linkedin' => 'fa-linkedin-square',
    'node:field_isearch_social_personalweb' => 'fa-globe',
  );

  if (array_key_exists($pane->subtype, $social_fields_icons)) {
    $value = $content->content[0]['#markup'];
    $content->content[0]['#markup'] = l('<i class="fa ' . $social_fields_icons[$pane->subtype] . '"></i>', $value, array(
      'attributes' => array(
        'target' => '_blank',
      ),
      'html' => TRUE,
    ));
  }


  if ($pane->panel == 'affiliations' && $pane->subtype == 'node:field_isearch_affiliations') {

    // unique quicktabs identifier
    $name = 'isearch_affiliations';

    // initial settings
    $settings = array(
      'ajax' => 0,
      'hide_if_empty' => 1,
      'default_tab' => 0,
      'title' => 'My custom quicktab',
      'renderer' => 'quicktabs',
      'style' => 'isearch',
    );

    $tabs = array();
    $weight = 0;

    foreach ($content->content['#items'] as $key => $item_id) {
      $item = current($content->content[$key]['entity']['field_collection_item']);
      $title = $item['#entity']->field_isearch_affil_title[LANGUAGE_NONE][0]['value'];

      $tab_html = drupal_render($content->content[$key]);

      $tabs[] = array(
        'type' => 'prerendered',
        'title' => $title,
        'weight' => $weight,
        'contents' => $tab_html,
      );
      $weight++;
    }

    $html = quicktabs_build_quicktabs($name, $settings, $tabs);

    $content->content = array(
      '#markup' => drupal_render($html),
    );
  }
}


/**
 * Implements hook_preprocess_panels_pane().
 */
function asu_isearch_preprocess_panels_pane(&$variables) {

  if (isset($variables['content']['#bundle']) && $variables['content']['#bundle'] === 'isearch_directory') {

    dpm($variables, 'THE VARS');

    // shortcut to content render array
    $content = &$variables['content'];

    // Setup variables here...
    $content['title'] = '';
    $directory = new IsearchProfileDirectory();

    // load the configuration saved for this pane
    $default_view_config = asu_dir_utilities_get_default_config('asu_isearch');
    $view_config = json_decode($content['field_isearch_config']['#object']->field_isearch_config[LANGUAGE_NONE][0]['value']);
    $view_config = (object) array_merge($default_view_config, (array) $view_config);

    //set the view display option if there is none
    if (!isset($view_config->view_display)) {
      $view_config->view_display = 'isearch_directory:directory_list';
    }

    list($view_name, $view_display_id) = explode(':', $view_config->view_display);

    // build out the view
    $view = views_get_view($view_name);
    $view->view_config = $view_config;
    $view->set_display($view_display_id);
    $view->init_handlers();

    $contextual_filters = asu_isearch_get_filters($view_config, $view);

    // set the contextual filters arguments
    $view_display = asu_isearch_get_rendered_view($view_config, $view);

    // end edit
    $directory->setViewConfig($view_config);

    $directory->setContextualFilters($contextual_filters);

    if ($view_config->show_az_index) {
      $content['isearch_az_index'] = array(
        '#markup' => $directory->renderIndex(),
        '#weight' => -10,
      );
    }

    $content['isearch_view'] = array(
      '#markup' => $view_display,
    );

    if (!$view_config->show_filter_titles
      && !$view_config->show_filter_expertise
      && !$view_config->show_filter_sort
      && !$view_config->show_filter_omni
    ) {
      $view_config->show_filters = FALSE;
    }

    // display filters? - Should we display or hide the filters


    dpm($view_config, 'THE VIEW CONFIG');

    if ($view_config->show_filters) {
      // build the exposed form fields
      $form_state = array(
        'view' => $view,
        'display' => $view->display_handler->display,
        'exposed_form_plugin' => $view->display_handler->get_plugin('exposed_form'),
        'method' => 'get',
        'rerender' => TRUE,
        'no_redirect' => TRUE
        //'ajax' => TRUE
      );

      $form = drupal_build_form('views_exposed_form', $form_state);

      // Attach our custom ajax handling script, if ajax is enabled
      //if ($view->use_ajax) {
      $form['#attached']['js'][] = drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch_omni.js';
      //}

      $form['keys']['#weight'] = -100;
      $form['keys']['#attributes']['placeholder'] = t('Name or Keyword');


      // update search filters
      $view->set_items_per_page(0);
      $view->set_offset(0);

      if ($view_config->show_filter_titles) {
        _asu_isearch_update_view_form_filters($view, $form, $directory);
      }

      // change some values to correctly display the form
      $form['#action'] = '/' . drupal_get_path_alias(current_path());
      $form['#weight'] = -5;

      $form['field_isearch_affil_title_value']['#access'] = (bool) $view_config->show_filter_titles;
      $form['field_isearch_expertise_areas_tid']['#access'] = (bool) $view_config->show_filter_expertise;
      $form['sort_by']['#access'] = (bool) $view_config->show_filter_sort;
      $form['keys']['#access'] = (bool) $view_config->show_filter_omni;

      // set the default sort by
      $form['sort_by']['#value'] = $view_config->default_sort_by;

      // set some form defaults when submitted ...
      $params = drupal_get_query_parameters();

      if (isset($params['field_isearch_expertise_areas_tid'])) {
        $form['field_isearch_expertise_areas_tid']['#value'] = intval($params['field_isearch_expertise_areas_tid']);

        if (isset($params['sort_by'])) {
          $form['sort_by']['#default_value'] = check_url($params['sort_by']);
          $form['sort_by']['#value'] = check_url($params['sort_by']);
        }

        if (isset($params['sort_order'])) {
          // Forcing ascending sort order for now
          $form['sort_order']['#value'] = 'ASC';
        }
      }

      // Add our configs to the exposed form, so that they are resubmitted as
      // part of the ajax process
      $form['omni_configs']['#value'] = drupal_json_encode($view_config);

      dpm($form, 'THE EXPOSED FORM');

      //$form['submit']['#ajax_processed'] = TRUE;
      $content['isearch_view_exposed_form'] = $form;
    }

    // hide configuration
    unset($content['field_isearch_config']);
  }
}


/***
 * Function to render the custom view
 *
 * @param $view_config
 * @return mixed
 */
function asu_isearch_get_rendered_view($view_config, &$view) {

  list($view_name, $view_display_id) = explode(':', $view_config->view_display);

  // set other display options

  if (asu_isearch_is_isearch_view($view)) {
    $display_header = TRUE;
    $display_photo = TRUE;
    $display_name = TRUE;
    $display_contact = TRUE;
    $display_expertise = TRUE;

    if (isset($view_config->display_header) && (bool) $view_config->display_header == FALSE) {
      $display_header = FALSE;
    }

    if (isset($view_config->display_photo) && (bool) $view_config->display_photo == FALSE) {
      $view->field['field_isearch_local_photo_url']->options['exclude'] = TRUE;
      $display_photo = FALSE;
    }

    if (isset($view_config->display_name) && (bool) $view_config->display_name == FALSE) {
      $view->field['nothing_1']->options['exclude'] = TRUE;
      $display_name = FALSE;
    }

    if (isset($view_config->display_contact) && (bool) $view_config->display_contact == FALSE) {
      $view->field['nothing']->options['exclude'] = TRUE;
      $display_contact = FALSE;
    }

    if (isset($view_config->display_expertise) && (bool) $view_config->display_expertise == FALSE) {
      $view->field['field_isearch_expertise_areas']->options['exclude'] = TRUE;
      $display_expertise = FALSE;
    }

    $display_options = (object) array(
      'display_header' => $display_header,
      'display_photo' => $display_photo,
      'display_name' => $display_name,
      'display_contact' => $display_contact,
      'display_expertise' => $display_expertise,
    );

    $directory_header = theme_render_template(drupal_get_path('module', 'asu_isearch') . '/theme/asu_isearch_view_header.tpl.php', array(
      'display_options' => $display_options,
    ));

    $view->display_handler->handlers['header']['area_text_custom']->options['content'] = $directory_header;

  }

  if (isset($view_config->display_short_bio) && !$view_config->display_short_bio) {
    $view->display_handler->handlers['field']['field_isearch_short_bio']->options['alter']['alter_text'] = TRUE;
    $view->display_handler->handlers['field']['field_isearch_short_bio']->options['alter']['text'] = '&nbsp;';
  }

  if (isset($view_config->display_building) && !$view_config->display_building) {
    $view->display_handler->handlers['field']['field_isearch_campus_building']->options['alter']['alter_text'] = TRUE;
    $view->display_handler->handlers['field']['field_isearch_campus_building']->options['alter']['text'] = '&nbsp;';
  }

  if (isset($view_config->display_room) && !$view_config->display_room) {
    $view->display_handler->handlers['field']['field_isearch_campus_room']->options['alter']['alter_text'] = TRUE;
    $view->display_handler->handlers['field']['field_isearch_campus_room']->options['alter']['text'] = '&nbsp;';
  }

  // pagination options
  $view->set_items_per_page($view_config->pager_items_per_page);
  //$view->set_offset($view_config->pager_offset);

  if ($view_config->pager_display != 'paged') {
    $pager = $view->display_handler->get_option('pager');
    $pager['type'] = 'none';

    if ($view_config->pager_display == 'fixed') {
      $pager['type'] = 'some';
    }

    $pager['options']['items_per_page'] = $view_config->pager_items_per_page;
    $view->display_handler->set_option('pager', $pager);
  }

  // Add the title filter
  if (isset($view_config->filter_title)) {
    if (trim($view_config->filter_title) != '') {
      $view->filter['field_isearch_affil_title_value_1']->value = $view_config->filter_title;
      $view->filter['field_isearch_affil_title_value_1']->options['value'] = $view_config->filter_title;
    }
  }

  $view->pre_execute();

  $view_display = $view->render($view_display_id);

  $view->post_execute();

  return $view_display;

}

/****
 * Add the filters to the view
 *
 *
 * @param $view_config
 * @param $view
 * @return array
 */
function asu_isearch_get_filters($view_config, &$view) {

  $contextual_last_name = 'all';
  $contextual_employee_types = 'all';
  $contextual_departments = 'all';
  $contextual_tenure_display = 'all';
  $contextual_expertise_areas = 'all';
  $contextual_local_tags = 'all';

  // display only certain employee types?
  if ($view_config->expertise_areas) {
    $contextual_expertise_areas = implode('+', (array) $view_config->expertise_areas);
  }

  // display only certain tags?
  if (!empty($view_config->local_tags)) {
    $contextual_local_tags = implode('+', (array) $view_config->local_tags);
  }

  if (count($view_config->depts->items) && $view_config->depts->items[0] != NULL) {
    $contextual_departments = array();
    $department_options = (object) $view_config->depts->options;

    foreach ($view_config->depts->items as $dept_item) {
      $contextual_departments[] = $dept_item->dept_nid;
      $dept_id = $dept_item->dept_id;

      // should we include all subdepartments?
      if ($department_options->$dept_id->subdepts) {
        $contextual_departments = array_merge($contextual_departments, $dept_item->tree_nids);
      }
    }
    $contextual_departments = implode(',', array_unique($contextual_departments));
  }

  // display only certain employee types?
  if (is_array($view_config->employee_types) && !empty($view_config->employee_types) && $view_config->employee_types[0] != 'All') {
    $employee_type_keys = array();
    foreach ($view_config->employee_types as $type) {
      $employee_type_keys[] = preg_replace('/[^a-zA-Z]/', '_', trim($type));
    }
    $contextual_employee_types = implode(',', $employee_type_keys);
  }

  // limit display to tenure type?
  if (!empty($view_config->tenure_display)) {
    // backwards compatible code
    switch (asu_isearch_get_tenure_config($view_config->tenure_display)) {
      case 'Tenure'    :
        $tenure_display = '1';
        break;
      case 'Non-Tenure':
        $tenure_display = '0';
        break;
      default:
        $tenure_display = 'all';
        break;
    }

    $contextual_tenure_display = $tenure_display;
  }

  // check against the argument list for the view, before settings filter vals
  $contextual_filter_map = array(
    'field_isearch_lastname_value' => $contextual_last_name,
    'field_isearch_affil_empl_key_value' => $contextual_employee_types,
    'field_isearch_affil_dept_id_value_1' => $contextual_departments,
    'field_isearch_affil_rank_tenure_value' => $contextual_tenure_display,
    'tid' => $contextual_expertise_areas,
    'tid_1' => $contextual_local_tags,
  );

  $contextual_filters = array();

  $arglist = $view->argument;

  foreach ($arglist as $key => $obj) {

    $value = 'all';

    if (array_key_exists($key, $contextual_filter_map)) {
      $value = $contextual_filter_map[$key];
    }

    $contextual_filters[] = $value;

  }

  $view->set_arguments($contextual_filters);

  return $contextual_filters;
}

function _asu_isearch_update_view_form_filters($view, &$form, $directory) {
  if (isset($form['field_isearch_affil_title_value']) && $form['field_isearch_affil_title_value']['#type'] == 'select') {
    $default = array('' => $form['field_isearch_affil_title_value']['#options']['']);
    $title_options = $directory->getTitleOptions();
    $title_options = array_merge($default, $title_options);

    $form['field_isearch_affil_title_value']['#options'] = $title_options;
  }
}


/**
 * Implements hook_preprocess_fieldable_panels_pane().
 */
function asu_isearch_preprocess_fieldable_panels_pane(&$variables) {
  if ($variables['elements']['#bundle'] === 'isearch_directory') {
    $title = $variables['elements']['#fieldable_panels_pane']->title;
    $variables['elements']['title'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'h2',
      '#value' => $title
    );
  }
}


/**
 * Implementation of hook_form_FORM_ID_alter()
 */
function asu_isearch_form_ctools_entity_field_content_type_formatter_options_alter(&$form, &$form_state, $form_id) {

  $content_type = isset($form_state['display']->context['panelizer']->data->type)
    ? $form_state['display']->context['panelizer']->data->type
    : FALSE;

  if ($content_type == 'asu_isearch_profile' && asu_isearch_devmode() == FALSE) {
    $isearch_field = str_replace('node:', '', $form_state['subtype_name']);
    $form[$isearch_field]['#disabled'] = TRUE;
  }
}


/**
 * Implementation of hook_form_FORM_ID_alter()
 */
function asu_isearch_form_fieldable_panels_panes_fieldable_panels_pane_content_type_edit_form_alter(&$form, &$form_state, $form_id) {
  if (isset($form['#entity']) && $form['#entity']->bundle == 'isearch_directory') {

    //turn off live preview
    variable_set('panopoly_magic_live_preview', 0);

    // add our custom submit handler
    $form['#submit'][0] = 'asu_isearch_form_fieldable_panels_panes_fieldable_panels_pane_content_type_edit_form_submit';
    //unset($form['#submit'][1]);
    //$form['#pre_render'][] = 'asu_isearch_form_fieldable_panels_panes_fieldable_panels_pane_content_type_group_pre_render';
    $form['#attributes']['class'][] = 'asu-isearch-configuration';

    $form['isearch_custom'] = array(
      '#type' => 'div',
      '#prefix' => '<div class="asu-isearch-pane-config">',
      '#suffix' => '</div>',
    );

    $form['#attached']['css'][] = drupal_get_path('module', 'asu_isearch') . '/css/asu_isearch.panelizer.css';
    asu_isearch_load_js();
    $form['#attached']['css'][] = drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch_config/asu_isearch_config.css';
    $form['#attached']['js'][] = drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch_config/bootstrap.js';
    $form['#attached']['js'][] = drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch_config/asu_isearch_config.js';
    $form['#attached']['js'][] = drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch_pane_config.js';

    $config = asu_dir_utilities_get_default_config('asu_isearch');

    // we are setting this up for the first time...
    if (!isset($form['#entity']->is_new) || !$form['#entity']->is_new) {
      // load the configuration from saved entity
      $config_defaults = $config;
      $config = (array) @json_decode($form['#entity']->field_isearch_config[LANGUAGE_NONE][0]['value']);
      $config = array_merge($config_defaults, $config);
    }

    $config = (object) $config;

    // Horizontal tabs definition
    $form['horizontal_tabs'] = array(
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
    $form['horizontal_tabs']['content'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Content'),
    );

    // Content vertical tabs definition
    $form['horizontal_tabs']['content']['content_tabs'] = array(
      '#type' => 'vertical_tabs',
      '#default_tab' => '',
    );


    // Content -> Department group
    $form['horizontal_tabs']['content']['content_tabs']['department'] = array(
      '#type' => 'fieldset',
      '#title' => t('Department'),
      '#collapsible' => TRUE,
      '#group' => 'content_tabs',
    );

    $form['horizontal_tabs']['content']['content_tabs']['department']['include_subdepts'] = array(
      '#type' => 'checkbox',
      '#title' => 'Include sub-departments',
      '#default_value' => $config->include_subdepts,
      '#access' => FALSE,
    );

    // get list of imported departments
    $dept_picker_items = array();
    $feed_depts = json_decode(asu_isearch_get_dept_config(), TRUE);
    $feed_items = $feed_depts['items'];

    foreach ($feed_items as $dept) {
      $id = $dept['dept_id'];

      if ($feed_depts['options'][$id]['subdepts']) {
        $dept_picker_items = array_merge($dept_picker_items, $dept['tree_nids']);
      }
      else {
        array_push($dept_picker_items, $dept['dept_nid']);
      }
    }

    $form['horizontal_tabs']['content']['content_tabs']['department']['isearch_dept_tree'] = array(
      '#type' => 'asu_dept_picker',
      '#default_value' => json_encode($config->depts),
      '#attributes' => array('id' => 'filter_departments'),
      '#delta' => $form['#entity']->fpid,
      '#asu_dept_tree' => array(
        'showOnly' => $dept_picker_items,
      ),
    );
    /** end department picker **/


    // Content -> Employee Types group
    $form['horizontal_tabs']['content']['content_tabs']['employeetypes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Employee Types'),
      '#collapsible' => TRUE,
      '#group' => 'content_tabs',
    );

    $form['horizontal_tabs']['content']['content_tabs']['employeetypes']['employee_type_exclude'] = array(
      '#type' => 'radios',
      '#options' => array(0 => 'Show', 1 => 'Hide'),
      '#title' => 'Select employee types to Show/Hide',
      '#default_value' => $config->employee_type_exclude,
      '#description' => t('Show will include all types selected below. Hide will include all types except those selected.'),
    );

    // build employee types field groups
    $default_employee_types = array();
    foreach ($config->employee_types as $value) {
      $default_employee_types[] = $value;
    }

    // helper checkbox to check all employee types
    $form['horizontal_tabs']['content']['content_tabs']['employeetypes']['select_all'] = array(
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
      $form['horizontal_tabs']['content']['content_tabs']['employeetypes'][$group_key] = array(
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
      $form['horizontal_tabs']['content']['content_tabs']['employeetypes'][$group_key]['options'] = array(
        '#type' => 'checkboxes',
        '#options' => array(),
        '#default_value' => $default_employee_types,
      );
    }

    // fetch employee types
    $employee_types = asu_dir_utilities_get_isearch_data(ASU_DIR_UTILITIES_EMPLOYEE_TYPES_ENDPOINT); //asu_dir_utilities_get_employee_types();

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
      $form['horizontal_tabs']['content']['content_tabs']['employeetypes'][$group]['options']
      ['#options'][$employee_type] = $employee_type;
    }

    // tenure control will be added to faculty employee types group for now

    $default_tenure_display = asu_isearch_get_tenure_config($config->tenure_display);

    $form['horizontal_tabs']['content']['content_tabs']['employeetypes']['faculty']['tenure_display'] = array(
      '#type' => 'radios',
      '#options' => drupal_map_assoc(array('Tenure', 'Non-Tenure', 'Both')),
      '#default_value' => $default_tenure_display,
      '#title' => 'Show Tenure/Non-Tenure/Both',
      '#description' => t('This selection will only apply to types in the Faculty list above.'),
      '#weight' => 10,
    );

    // Content -> Other Filters group
    $form['horizontal_tabs']['content']['content_tabs']['otherfilters'] = array(
      '#type' => 'fieldset',
      '#title' => t('Other Filters'),
      '#collapsible' => TRUE,
      '#group' => 'content_tabs',
    );

    $expertise_vocabulary = taxonomy_vocabulary_machine_name_load('isearch_expertise');
    if ($expertise_terms = taxonomy_get_tree($expertise_vocabulary->vid, 0, NULL, TRUE)) {
      $expertise_areas = array();

      foreach ($expertise_terms as $term) {
        $expertise_areas[$term->tid] = $term->name;
      }

      if (!is_array($config->expertise_areas)) {
        $config->expertise_areas = (array) $config->expertise_areas;
      }

      if (!empty($expertise_areas)) {
        $form['horizontal_tabs']['content']['content_tabs']['otherfilters']['isearch_expertise_areas'] = array(
          '#type' => 'select',
          '#options' => $expertise_areas,
          '#default_value' => $config->expertise_areas,
          '#multiple' => TRUE,
          '#title' => t('Limit to these expertise areas'),
        );
      }
    }

    $form['horizontal_tabs']['content']['content_tabs']['otherfilters']['filter_title'] = array(
      '#type' => 'textfield',
      '#title' => 'Filter Title',
      '#description' => t('Limit results by the affiliation title. Regular expression allowed.  Do not use any spaces between text and regex operators.'),
      '#default_value' => $config->filter_title,
    );

    $local_tags_vocabulary = taxonomy_vocabulary_machine_name_load('isearch_local_tags');

    if ($local_tags_terms = taxonomy_get_tree($local_tags_vocabulary->vid, 0, NULL, TRUE)) {
      $local_tags = array();

      foreach ($local_tags_terms as $term) {
        $local_tags_areas[$term->tid] = $term->name;
      }

      if (!is_array($config->local_tags)) {
        $config->local_tags = (array) $config->local_tags;
      }

      $form['horizontal_tabs']['content']['content_tabs']['otherfilters']['isearch_local_tags'] = array(
        '#type' => 'select',
        '#options' => $local_tags_areas,
        '#default_value' => $config->local_tags,
        '#multiple' => TRUE,
        '#title' => t('Filter profiles by these local tags'),
      );
    }


    // Appearance horizontal tab definition
    $form['horizontal_tabs']['appearance'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Appearance'),
    );

    // Appearance vertical tabs definition
    $form['horizontal_tabs']['appearance']['appearance_tabs'] = array(
      '#type' => 'vertical_tabs',
      '#default_tab' => '',
    );

    // Appearance -> Sorting group
    $form['horizontal_tabs']['appearance']['appearance_tabs']['sorting'] = array(
      '#type' => 'fieldset',
      '#title' => t('Sorting'),
      '#collapsible' => TRUE,
      '#group' => 'appearance_tabs',
    );
    /* Deprecate this field
    $form['horizontal_tabs']['appearance']['appearance_tabs']['sorting']['show_managers'] = array(
      '#type' => 'checkbox',
      '#title' => 'Show managers at top',
      '#default_value' => $config->show_managers,
    );*/

    $default_sort_by_options = array(
      'field_isearch_affil_rank_weight_value' => 'Rank',
      'field_isearch_lastname_value' => 'Last Name',
      'field_isearch_firstname_value' => 'First Name',
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['sorting']['default_sort_by'] = array(
      '#type' => 'select',
      '#options' => $default_sort_by_options,
      '#title' => 'Default sort order',
      '#default_value' => $config->default_sort_by,
    );

    // Appearance -> Exposed filters group
    $form['horizontal_tabs']['appearance']['appearance_tabs']['exposed'] = array(
      '#type' => 'fieldset',
      '#title' => t('Exposed Filters'),
      '#collapsible' => TRUE,
      '#group' => 'appearance_tabs',
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filters'] = array(
      '#type' => 'checkbox',
      '#title' => 'Show filters',
      '#default_value' => $config->show_filters,
      '#description' => t('These options are shown to visitors, allowing them to further sort and filter the list.'),
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_omni'] = array(
      '#type' => 'checkbox',
      '#title' => 'Search box',
      '#default_value' => $config->show_filter_omni,
      '#description' => t('This will allow visitors to search for keywords in titles, expertise areas, and short bios (even if these columns are not enabled in appearance).'),
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_expertise'] = array(
      '#type' => 'checkbox',
      '#title' => 'Expertise dropdown',
      '#default_value' => $config->show_filter_expertise,
      '#description' => t('This will allow visitors to filter the list to the specified expertise area. This dropdown will list all expertise areas associated with people in the department.'),
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_titles'] = array(
      '#type' => 'checkbox',
      '#title' => 'Title dropdown',
      '#default_value' => $config->show_filter_titles,
      '#description' => t('This will allow visitors to filter the list by people of a specified title. This dropdown is populated with titles of people in the current list only.'),
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_sort'] = array(
      '#type' => 'checkbox',
      '#title' => 'Sort by dropdown',
      '#default_value' => $config->show_filter_sort,
      '#description' => t('Allows visitors to sort the list based on Rank, First Name, or Last Name.'),
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_az_index'] = array(
      '#type' => 'checkbox',
      '#title' => 'Show A-Z index',
      '#default_value' => $config->show_az_index,
      '#description' => t('Allows visitors to click on a letter that will filter the directory list to profiles with last names beginning with that letter.'),
    );


    // Appearance -> Paging group
    $form['horizontal_tabs']['appearance']['appearance_tabs']['paging'] = array(
      '#type' => 'fieldset',
      '#title' => t('Paging'),
      '#collapsible' => TRUE,
      '#group' => 'appearance_tabs',
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_display'] = array(
      '#type' => 'select',
      '#options' => array(
        'paged' => 'Paged output',
        'all' => 'Display all items',
        'fixed' => 'Display a specified number of items'
      ),
      '#title' => 'Display pagination',
      '#default_value' => $config->pager_display,
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_items_per_page'] = array(
      '#type' => 'textfield',
      '#title' => 'Items to display',
      '#description' => t('The number of items to display. Enter 0 for no limit.'),
      '#default_value' => $config->pager_items_per_page,
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_offset'] = array(
      '#type' => 'textfield',
      '#title' => 'Offset',
      '#description' => t('The number of items to skip. For example, if this field is 3, the first 3 items will be skipped and not displayed.'),
      '#default_value' => $config->pager_offset,
    );


    // Appearance -> Columns group
    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns'] = array(
      '#type' => 'fieldset',
      '#title' => t('Columns'),
      '#collapsible' => TRUE,
      '#group' => 'appearance_tabs',
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_header'] = array(
      '#type' => 'checkbox',
      '#title' => 'Header labels',
      '#default_value' => $config->display_header,
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_photo'] = array(
      '#type' => 'checkbox',
      '#title' => 'Photo column',
      '#default_value' => $config->display_photo,
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_name'] = array(
      '#type' => 'checkbox',
      '#title' => 'Name/Title column',
      '#default_value' => $config->display_name,
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_contact'] = array(
      '#type' => 'checkbox',
      '#title' => 'Contact column',
      '#default_value' => $config->display_contact,
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_expertise'] = array(
      '#type' => 'checkbox',
      '#title' => 'Expertise column',
      '#default_value' => $config->display_expertise,
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_building'] = array(
      '#type' => 'checkbox',
      '#title' => 'Building',
      '#default_value' => $config->display_building,
      '#description' => t('The building and room fields are displayed in the contact column. They are populated from the first and second lines of Campus Address.'),
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_room'] = array(
      '#type' => 'checkbox',
      '#title' => 'Room',
      '#default_value' => $config->display_room,
      '#description' => t('The building and room fields are displayed in the contact column. They are populated from the first and second lines of Campus Address.'),
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns']['link_building_codes'] = array(
      '#type' => 'checkbox',
      '#title' => 'Link building codes',
      '#default_value' => $config->link_building_codes,
      '#description' => t('This will link properly formatted building codes to the ASU interactive map. If the building code is not properly formatted, it will not be linked.'),
    );

    $form['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_short_bio'] = array(
      '#type' => 'checkbox',
      '#title' => 'Display short bio field?',
      '#default_value' => $config->display_short_bio,
      '#description' => t('The short bio is displayed below the title in the name column.'),
    );


    // Advanced horizontal tab definition
    $form['horizontal_tabs']['advanced'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Advanced'),
    );

    // Advanced tab content
    $available_views = asu_isearch_get_views();
    $form['horizontal_tabs']['advanced']['isearch_view_display'] = array(
      '#type' => 'select',
      '#title' => 'Select a view to display',
      '#options' => $available_views,
      '#default_value' => $config->view_display,
      '#description' => t('You can select a custom view that was cloned from the iSearch Directory view. Please note, some settings may not work as expected when using a custom view and changes are made to fields and filters.'),
    );

    // Advanced horizontal tab definition
    $form['horizontal_tabs']['preview'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Preview'),
      '#access' => FALSE,
    );

    $form['horizontal_tabs']['preview']['preview_placeholder'] = array(
      '#type' => 'item',
      '#markup' => '<div id="isearch-preview"></div>',
    );

    // executes iSearch configuration form visuals
    $form['footer']['react'] = array(
      '#type' => 'item',
      '#markup' => '<script type="text/javascript">initIsearchConfig();</script>',
    );

    // Hide isearch config field
    $form['field_isearch_config']['#access'] = FALSE;
  }
}


/***
 * Submit handler for the asu_isearch panel pane form
 *
 * @param $form
 * @param $form_state
 */
function asu_isearch_form_fieldable_panels_panes_fieldable_panels_pane_content_type_edit_form_submit($form, &$form_state) {
  // store values
  $values = $form_state['values'];

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

  $config = array(

    // Content -> Department
    // TODO: Set correct array index for 'depts'... ['horizontal_tabs']['content']['content_tabs']['department']
    'include_subdepts' => $values['horizontal_tabs']['content']['content_tabs']['department']['include_subdepts'],
    'depts' => json_decode($values['horizontal_tabs']['content']['content_tabs']['department']['isearch_dept_tree']),

    // Content -> Employee types
    'employee_types' => $employee_types,
    'employee_type_exclude' => $values['horizontal_tabs']['content']['content_tabs']['employeetypes']['employee_type_exclude'],
    'tenure_display' => $values['horizontal_tabs']['content']['content_tabs']['employeetypes']['faculty']['tenure_display'],

    // Content -> Other filters
    'expertise_areas' => $values['horizontal_tabs']['content']['content_tabs']['otherfilters']['isearch_expertise_areas'],
    'local_tags' => $values['horizontal_tabs']['content']['content_tabs']['otherfilters']['isearch_local_tags'],
    'filter_title' => $values['horizontal_tabs']['content']['content_tabs']['otherfilters']['filter_title'],

    // Appearance -> Sorting
    // deprecated show managers field
    //'show_managers' => $values['horizontal_tabs']['appearance']['appearance_tabs']['sorting']['show_managers'],
    'default_sort_by' => $values['horizontal_tabs']['appearance']['appearance_tabs']['sorting']['default_sort_by'],

    // Appearance -> Exposed Filters
    'show_filters' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filters'],
    'show_filter_omni' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_omni'],
    'show_filter_expertise' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_expertise'],
    'show_filter_titles' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_titles'],
    'show_filter_sort' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_filter_sort'],
    'show_az_index' => $values['horizontal_tabs']['appearance']['appearance_tabs']['exposed']['show_az_index'],

    // Appearance -> Paging
    'pager_display' => $values['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_display'],
    'pager_items_per_page' => $values['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_items_per_page'],
    'pager_offset' => $values['horizontal_tabs']['appearance']['appearance_tabs']['paging']['pager_offset'],

    // Appearance -> Columns
    'display_header' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_header'],
    'display_photo' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_photo'],
    'display_name' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_name'],
    'display_contact' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_contact'],
    'display_expertise' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_expertise'],
    'display_building' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_building'],
    'display_room' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_room'],
    'link_building_codes' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['link_building_codes'],
    'display_short_bio' => $values['horizontal_tabs']['appearance']['appearance_tabs']['columns']['display_short_bio'],

    // Advanced
    'view_display' => $values['horizontal_tabs']['advanced']['isearch_view_display'],
  );

  //$form_state['entity']->field_isearch_config[LANGUAGE_NONE][0]['value'] = json_encode($config);

  $entity = $form_state['entity'];

  // Copy hardcoded fields.
  $entity->title = $form_state['values']['title'];
  $entity->link = $form_state['values']['link'];
  $entity->path = $form_state['values']['path'];
  $entity->language = $form_state['values']['language'];
  $entity->reusable = $form_state['values']['reusable'];
  $entity->category = $form_state['values']['category'];
  $entity->admin_title = $form_state['values']['admin_title'];
  $entity->admin_description = $form_state['values']['admin_description'];
  $entity->field_isearch_config[LANGUAGE_NONE][0]['value'] = json_encode($config);

  $entity->revision = $form_state['values']['revision'];
  // Only set a log message if there was a new revision. This prevents
  // overwriting a log message on the current revision
  if ($entity->revision) {
    $entity->log = $form_state['values']['log'];
  }

  fieldable_panels_panes_save($entity);
  if (!empty($form_state['add submit'])) {
    drupal_set_message(t('The entity has been saved.'));
  }

  /*** FROM fieldable_panels_panes_fieldable_panels_pane_content_type_edit_form_submit   **/
  // Determine how to handle revision locking.
  $revision_context_aware = fieldable_panels_panes_revision_is_lockable($entity);

  // If this is a new entity entity, or revision locking is enabled, look for a
  // specific ID to use.
  if (!empty($entity->is_new) || $revision_context_aware) {
    // If UUID is available, use it.
    if (module_exists('uuid') && isset($entity->uuid)) {
      if ($revision_context_aware) {
        $subtype = 'vuuid:' . $entity->vuuid;
      }
      else {
        $subtype = 'uuid:' . $entity->uuid;
      }
    }

    // Otherwise use the native ID values.
    else {
      if ($revision_context_aware) {
        $subtype = 'vid:' . $entity->vid;
      }
      else {
        $subtype = 'fpid:' . $entity->fpid;
      }
    }
  }

  // The 'current' key will tell FPP to load up the current revision. This
  // bypasses the entity cache on the FPP entity class and loads the revision
  // that was just saved instead of the previous revision. This is only really
  // relevant in Panels IPE administration or similar circumstances.
  else {
    $subtype = 'current:' . $entity->fpid;
  }

  // @todo: This won't work if $form_state does not contain 'pane' which could
  // theoretically happen in a non-Panels use case. Not that anybody uses this
  // outside of Panels.
  $form_state['pane']->subtype = $subtype;
}

/*
function asu_isearch_form_fieldable_panels_panes_fieldable_panels_pane_content_type_group_pre_render(&$element) {
  $element['content_settings']['horizontal_tabs'] = $element['horizontal_tabs'];
  unset($element['horizontal_tabs']);

  return field_group_build_entity_groups($element, 'form');
}*/
