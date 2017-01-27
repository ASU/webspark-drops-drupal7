<?php


/**
 * Implements hook_views_pre_render()
 */
function asu_isearch_views_pre_render(&$view) {
  /*
  if ($view->name == 'isearch_affiliations') {
    // If we're not displaying all affiliations, hide the title so it isn't redundant.
    $display_affiliations = (bool) variable_get('isearch_display_affiliations', 0);
    if (FALSE === $display_affiliations) {
      $view->field['field_isearch_affil_title']->options['exclude'] = TRUE;
    }
  }*/

  if (asu_isearch_is_isearch_view($view) && isset($view->view_config)) {


    $view->exposed_data[] = drupal_json_encode($view->view_config);

    $display_options = array(
      'display_header' => $view->view_config->display_header,
      'display_photo' => $view->view_config->display_photo,
      'display_name' => $view->view_config->display_name,
      'display_contact' => $view->view_config->display_contact,
      'display_expertise' => $view->view_config->display_expertise,
    );
    $display_options = (object) $display_options;
    $view_column_widths = asu_isearch_get_view_column_widths($display_options);

    $column_names = array_keys($view_column_widths);
    foreach ($view->field as $field_name => $data) {
      if ($view->field[$field_name]->options['exclude'] == 0) {
        foreach ($column_names as $column_name) {
          if (strstr($view->field[$field_name]->options['element_wrapper_class'], 'user-' . $column_name)) {
            $view->field[$field_name]->options['element_wrapper_class'] .= ' col-md-' . $view_column_widths[$column_name];
          }
        }
      }
    }

    // prepare various variables for condition checks
    $view_link_building = (bool) $view->view_config->link_building_codes;
    $global_link_buildings = variable_get('isearch_link_buildings', TRUE);

    foreach ($view->result as $key => $result) {
      $entity = $result->_field_data['nid']['entity'];
      $wrapper = entity_metadata_wrapper('node', $entity);

      // building code link
      if ($view_link_building && $global_link_buildings) {
        // TODO: Logic for linking building in view listing
        if (!empty($view->result[$key]->field_field_isearch_campus_building)) {
          if ($building_code = (asu_isearch_fetch_asu_building_code($view->result[$key]->field_field_isearch_campus_building[0]['raw']['value']))) {
            $building_label = $view->result[$key]->field_field_isearch_campus_building[0]['raw']['value'];
            $building_map_link = l($building_label, 'http://www.asu.edu/map/interactive/?building=' . $building_code,
              array(
                'attributes' => array(
                  'target' => '_blank',
                ),
              ));

            $view->result[$key]->field_field_isearch_campus_building[0]['rendered']['#markup'] = $building_map_link;
          }
        }
      }

      // display correct photo if any
      $photo_permission = strtolower($wrapper->field_isearch_photo_permission->value());
      if ($photo_permission != 'public' || empty($entity->field_isearch_photo_url)) {

        $display_default_photo = variable_get('isearch_display_default_photo', FALSE);
        $default_photo = asu_isearch_get_default_photo();


        if ($display_default_photo && $default_photo) {

          $view->result[$key]->field_field_isearch_photo_url[0]['rendered']['#access'] = TRUE;
          $view->result[$key]->field_field_isearch_photo_url[0]['rendered']['#theme'] = 'image_formatter';
          $view->result[$key]->field_field_isearch_photo_url[0]['rendered']['#item'] = (array) $default_photo;
          $view->result[$key]->field_field_isearch_photo_url[0]['raw'] = (array) $default_photo;
        }
        else {
          $view->result[$key]->field_field_isearch_photo_url = array();
        }
      }

      // add alt attribute to images
      $view->result[$key]->field_field_isearch_photo_url[0]['rendered']['#item']['alt'] = $view->result[$key]->node_title;
      $view->result[$key]->field_field_isearch_photo_url[0]['raw']['alt'] = $view->result[$key]->node_title;
    }
  }
}

/**
 * Implements hook_views_pre_view()
 */
function asu_isearch_views_pre_view(&$view, &$display_id, &$args) {
  if ($view->name == 'isearch_affiliations') {
    if ($node = menu_get_object()) {
      if (isset($node->type) && $node->type == 'asu_isearch_profile') {
        $args[0] = $node->nid;
      }

      $display_affiliations = (bool) variable_get('isearch_display_affiliations', 0);
      if (FALSE === $display_affiliations) {

        $local_primary_affiliation = (!empty($node->field_isearch_primary_aff))
          ? $node->field_isearch_primary_aff[LANGUAGE_NONE][0]['target_id']
          : NULL;

        if (!empty($node->field_isearch_local_primary_aff)) {
          $local_primary_affiliation = $node->field_isearch_local_primary_aff[LANGUAGE_NONE][0]['target_id'];
        }

        $args[1] = $local_primary_affiliation;
        $view->style_options['tab_field'] = 'affiliation_tab_title';
      }
    }
  }
}


/**
 * Returns an array of available views
 */
function asu_isearch_get_views() {
  $views = array();
  $loaded_views = views_get_all_views();

  foreach ($loaded_views as $view_name => $view) {
    // loop through display
    foreach ($view->display as $display_name => $display) {
      if ($display_name == 'default') {
        continue;
      }

      // limit displays to those which have the isearch-directory-list class assigned
      $display_options = (isset($view->display['default'])) ? $view->display['default']->display_options : array();
      $display_options = array_merge($display_options, $display->display_options);

      if (isset($display_options['css_class']) && (preg_match('/\bisearch-directory-list/', $display_options['css_class']) || $display_name == 'isearch_directory_titles')) {

        $id = $view_name . ':' . $display_name;
        $views[$id] = strip_tags(format_string(':view: :display (:display_id)', array(
          ':view' => $view->human_name,
          ':display' => $display->display_title,
          ':display_id' => $display_name
        )));
      }
    }
  }

  return $views;
}


/**
 * Implements hook_views_query_alter()
 */
function asu_isearch_views_query_alter(&$view, &$query) {

  if (asu_isearch_is_isearch_view($view) && isset($view->view_config)) {

    // reset the sort when passed in
    if (isset($_GET['sort_by'])) {
      $view->view_config->default_sort_by = $_GET['sort_by'];
    }

    switch ($view->view_config->default_sort_by) {
      case 'field_isearch_firstname_value':
        if (isset($view->sort['field_isearch_lastname_value'])) {
          unset($view->sort['field_isearch_lastname_value']);
        }

      case 'field_isearch_lastname_value':
        if (isset($view->sort['field_isearch_affil_rank_weight_value'])) {
          unset($view->sort['field_isearch_affil_rank_weight_value']);
        }

        break;

      case 'field_isearch_affil_rank_weight_value':
      default:
        if (isset($view->sort['field_isearch_affil_rank_weight_value'])) {
          $view->sort['field_isearch_affil_rank_weight_value']->options['order'] = 'ASC';
          unset($view->sort['field_isearch_firstname_value']);
        }

        break;
    }

    $query->orderby = array();

    foreach ($view->sort as $field => $sort) {
      $query->orderby[] = array(
        'field' => $sort->field,
        'direction' => $sort->options['order'],
      );
    }

    /* deprecated
    if ($view->view_config->employee_type_exclude == 1) {
      $dept_id_field = 'field_collection_item_field_data_field_isearch_affiliations__field_data_field_isearch_affil_empl_key.field_isearch_affil_empl_key_value';
      $found_employee_type_filter = FALSE;

      foreach ($query->where as $item_index => $item) {
        if (!empty($item['conditions'])) {
          foreach ($item['conditions'] as $condition_index => $condition) {
            if (!is_object($condition['field']) && $condition['field'] == $dept_id_field) {
              $found_employee_type_filter = TRUE;
              if (is_array($query->where[$item_index]['conditions'][$condition_index]['value'])) {
                $operator = 'NOT IN';
              }
              else {
                $operator = '!=';
              }
              $query->where[$item_index]['conditions'][$condition_index]['operator'] = $operator;
            }
          }
        }
      }

      if (!$found_employee_type_filter) {
        $query->where[0]['conditions'][] = array(
          'field' => $dept_id_field,
          'operator' => '=',
          'value' => 'unknown',
        );
      }
    }*/


    // Set the lastname filter if a letter is selected
    if (isset($view->view_config->index_letter) && $view->view_config->index_letter != 'ALL') {
      $letter = $view->view_config->index_letter;

      $query->where[] = array(
        'conditions' => array(
          0 => array(
            'field' => ' field_data_field_isearch_lastname.field_isearch_lastname_value',
            'operator' => 'RLIKE',
            'value' => '^' . $letter . '.*'
          )
        ),
        'args' => array(),
        'type' => 'AND'
      );
    }
  }
}

/**
 * Implements hook_query_TAG_alter()
 */
function asu_isearch_query_asu_isearch_list_alter(QueryAlterableInterface $query) {
  $query->groupBy('nid');
}

/***
 * Implements hook_js_alter
 *
 * We replace the ajax_view js with a custom solution, which will allow multiple
 * exposed filters on the same page.
 *
 * @param $javascript
 */
function asu_isearch_js_alter(&$javascript) {

  $asu_isearch_js = drupal_get_path('module', 'asu_isearch') . '/js/asu_isearch_omni.js';

  if (isset($javascript[$asu_isearch_js])) {

    $views_ajax_path = drupal_get_path('module', 'views') . '/js/ajax_view.js';

    unset($javascript[$views_ajax_path]);
  }
}

/**
 * Modified menu callback to load a view via AJAX, based on asu_isearch configs
 */
function asu_isearch_views_ajax() {

  // load the views ajax functions
  require_once drupal_get_path('module', 'views') . '/includes/ajax.inc';

  if (isset($_REQUEST['view_name']) && isset($_REQUEST['view_display_id'])) {
    $name = $_REQUEST['view_name'];
    $display_id = $_REQUEST['view_display_id'];
    $args = isset($_REQUEST['view_args']) && $_REQUEST['view_args'] !== '' ? explode('/', $_REQUEST['view_args']) : array();
    $path = isset($_REQUEST['view_path']) ? rawurldecode($_REQUEST['view_path']) : NULL;
    $dom_id = isset($_REQUEST['view_dom_id']) ? preg_replace('/[^a-zA-Z0-9_-]+/', '-', $_REQUEST['view_dom_id']) : NULL;
    $pager_element = isset($_REQUEST['pager_element']) ? intval($_REQUEST['pager_element']) : NULL;

    // if the omni configs are not set, then return the regular views ajax processing
    if (!isset($_REQUEST['omni_configs'])) {
      return views_ajax();
    }

    $view_config = json_decode($_REQUEST['omni_configs']);
    $index_letter = isset($_REQUEST['isearch_index']) ? $_REQUEST['isearch_index'] : NULL;

    if ($index_letter != NULL) {
      $view_config->index_letter = $index_letter;
    }

    $commands = array();

    // Remove all of this stuff from $_GET so it doesn't end up in pagers and tablesort URLs.
    foreach (array(
               'view_name',
               'view_display_id',
               'view_args',
               'view_path',
               'view_dom_id',
               'pager_element',
               'view_base_path',
               'ajax_html_ids',
               'ajax_page_state'
             ) as $key) {
      if (isset($_GET[$key])) {
        unset($_GET[$key]);
      }
      if (isset($_REQUEST[$key])) {
        unset($_REQUEST[$key]);
      }
      if (isset($_POST[$key])) {
        unset($_POST[$key]);
      }
    }

    if (!isset($view_config->view_display)) {
      $view_config->view_display = 'isearch_directory:directory_list';
    }

    list($view_name, $display_id) = explode(':', $view_config->view_display);

    $view = views_get_view($view_name);

    $view->view_config = $view_config;
    $view->set_display($display_id);
    $view->init_handlers();

    if ($view && $view->access($display_id)) {
      // Fix 'q' for paging.
      if (!empty($path)) {
        $_GET['q'] = $path;
      }

      // Add all $_POST data, because AJAX is always a post and many things,
      // such as tablesorts, exposed filters and paging assume $_GET.
      $_GET = $_POST + drupal_get_query_parameters($_GET, array('page'));

      // Overwrite the destination.
      // @see drupal_get_destination()
      $origin_destination = $path;
      $query = drupal_http_build_query(drupal_get_query_parameters());
      if ($query != '') {
        $origin_destination .= '?' . $query;
      }
      $destination = &drupal_static('drupal_get_destination');
      $destination = array('destination' => $origin_destination);

      // Override the display's pager_element with the one actually used.
      if (isset($pager_element)) {
        $commands[] = views_ajax_command_scroll_top('.view-dom-id-' . $dom_id);
        $view->display[$display_id]->handler->set_option('pager_element', $pager_element);
      }
      // Reuse the same DOM id so it matches that in Drupal.settings.
      $view->dom_id = $dom_id;

      // Attach asu_isearch customized contextual filters
      $contextual_filters = asu_isearch_get_filters($view_config, $view);


      if (isset($_REQUEST['field_isearch_affil_title_value'])) {
        $view_config->current_title = $_REQUEST['field_isearch_affil_title_value'];
      }

      // set the contextual filters arguments
      $view_display = asu_isearch_get_rendered_view($view_config, $view);

      $commands[] = ajax_command_replace('.view-dom-id-' . $dom_id, $view_display);
    }

    //drupal_alter('views_ajax_data', $commands, $view);
    return array('#type' => 'ajax', '#commands' => $commands);
  }
}