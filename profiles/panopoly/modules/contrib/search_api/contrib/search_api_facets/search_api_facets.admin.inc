<?php

/**
 * Displays a form for selecting the indexed fields for which facets should be
 * created.
 *
 * @param SearchApiIndex $index
 *   The index for which to display the settings.
 */
function search_api_facets_index_select(array $form, array &$form_state, SearchApiIndex $index) {
  module_load_include('admin.inc', 'search_api');
  drupal_set_title(search_api_admin_item_title($index));
  $form_state['index'] = $index;
  $index_facets = search_api_facet_load_multiple(FALSE, array('index_id' => $index->machine_name));

  if ($index_facets && module_exists('search_api_facetapi')) {
    $form['#attached']['css'][] = drupal_get_path('module', 'search_api') . '/search_api.admin.css';
    $form['export'] = array(
      '#type' => 'fieldset',
      '#title' => t('Export settings to new module'),
      '#description' => t('<p>This way of defining facets has been deprecated. ' .
          'You can use this form to export your existing facet definitions to the <a href="@url">new settings</a>.</p>' .
          '<p>Once you have migrated the settings for all indexes, you should disable the "Old search facets" module.</p>' .
          '<p><strong>Note:</strong> In case of collisions, the new settings will be overwritten with ' .
          'settings defined here (and in the accompanying block configurations)!</p>',
          array('@url' => url('admin/config/search/search_api/index/' . $index->machine_name . '/facets'))),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['export']['method'] = array(
      '#type' => 'select',
      '#title' => t('Facets to export'),
      '#options' => array(
        'all' => t('All saved facets'),
        'enabled' => t('All enabled facets'),
        'custom' => t('Manual'),
      ),
      '#default_value' => 'all',
    );
    $form['export']['facets'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Select facets to export'),
      '#description' => t('If you select "Manual" above, you can manually select the facets to export for this index here.'),
      '#options' => array(),
      '#attributes' => array('class' => array('search-api-checkboxes-list')),
    );
    $form['export']['facets']['#states']['visible'][':input[name="export[method]"]']['value'] = 'custom';
    foreach ($index_facets as $facet) {
      if (!empty($fields[$facet->field])) {
        $form['export']['#description'] .= '<p>' . t('<strong>Warning</strong>: ' .
            'Multiple facets for the same field are currently not supported by the Facet API. ' .
            'Therefore, they cannot be exported. If having multiple facets for the same field is crucial for your site, ' .
            'please ask for help in the <a href="@url">issue queue</a>.',
            array('@url' => 'http://drupal.org/project/issues/search_api')) . '</p>';
      }
      $form['export']['facets']['#options'][$facet->delta] = $facet->name;
      $fields[$facet->field] = TRUE;
    }
    $form['export']['realms'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Export to realms'),
      '#description' => t('Select the realms to which realm-specific settings will be exported. ' .
          'Global settings will be exported in any case.'),
      '#options' => array(),
      '#default_value' => array(),
      '#attributes' => array('class' => array('search-api-checkboxes-list')),
    );
    foreach (facetapi_get_realm_info() as $key => $realm) {
      $form['export']['realms']['#options'][$key] = $realm['label'];
      $form['export']['realms']['#default_value'][$key] = $key;
    }

    $form['export']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Export settings'),
      '#submit' => array('_search_api_facets_index_export_submit'),
    );
  }
  elseif (!module_exists('search_api_facetapi')) {
    $msg = '<p>' . t('This module has been deprecated in favor of the new "Search facets" module. To switch:') . '</p>';
    $msg .= '<ul>';
    $msg .= '<li>' . t('Download and enable the <a href="@url">Facet API</a> module.', array('@url' => url('http://drupal.org/project/facetapi'))) . '</li>';
    $msg .= '<li>' . t('Enable the new "Search facets" module (which depends on the Facet API).') . '</li>';
    $msg .= '<li>' . t('Come back to this page to export your facet settings  to the new modules.') . '</li>';
    $msg .= '<li>' . t('Possibly do the same for other indexes with defined facets.') . '</li>';
    $msg .= '<li>' . t('Disable the "Old search facets" module.') . '</li>';
    $msg .= '</ul>';
    drupal_set_message($msg, 'warning');
  }

  if (!$index->server() || !$index->server()->supportsFeature('search_api_facets')) {
    // We can't offer any facets, but maybe the user can delete old facet data.
    drupal_set_message(t("The server this index currently lies on doesn't support facets. " .
        'To use facets, you will have to move this index to a server supporting this feature.'), 'error');
    if ($index_facets) {
      $form['description'] = array(
        '#type' => 'item',
        '#title' => t('Delete facet settings'),
        '#description' => t("If you won't use facets with this index anymore, you can delete all facet data associated with it. " .
            "This will delete all settings for facets on this index. Facets on other indexes won't be influenced."),
      );
      $form['button'] = array(
        '#type' => 'submit',
        '#value' => t('Delete facet settings'),
        '#submit' => array('search_api_facets_index_select_submit_delete'),
      );
    }
    return $form;
  }

  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Select the available facet blocks'),
    '#description' => t('<p>All enabled blocks will be shown, along with their names, on the block administration page. ' .
        'For your own convenience, choose unique names. ' .
        'By cloning blocks, you can have multiple facet blocks with seperate configurations for a single index field.</p>' .
        "<p>When you won't be using a disabled facet anymore, you can delete all its settings permanently, reducing database size. " .
        "This won't influence other facets. You can enable it again later, but without the previously stored settings.</p>" .
        "<p>* Checkboxes with an asterisk denote overridden facet configurations. These cannot be deleted, but only be reset to their defaults.</p>" .
        "<p>Note that, even though facets for fulltext fields are available, they won't make much sense in most scenarios.</p>"),
  );
  $form['facets'] = array(
    '#tree' => TRUE,
    '#theme' => 'search_api_facets_form_table',
    '#table_header' => array(
      t('Enabled'),
      t('Field'),
      t('Type'),
      t('Name'),
      t('Clone block'),
      t('Delete data'),
    ),
    '#table_empty' => t('There are currently no fields for which facets can be displayed.'),
  );

  if (!empty($index->options['fields'])) {
    $facets = array();
    if ($disabled = empty($index->enabled)) {
      drupal_set_message('Since this index is at the moment disabled, no facet blocks can be activated.', 'warning');
    }
    $show_status = FALSE;
    foreach ($index_facets as $facet) {
      $facets[$facet->field][] = $facet;
      if ($facet->hasStatus(ENTITY_IN_CODE)) {
        $show_status = TRUE;
      }
    }
    if ($show_status) {
      $form['facets']['#table_header'] = array(
        t('Enabled'),
        t('Status'),
        t('Field'),
        t('Type'),
        t('Name'),
        t('Clone block'),
        t('Delete data'),
      );
      $empty_status = ' ';
    }
    $types = search_api_field_types();
    $entity_types = entity_get_info();
    foreach ($index->options['fields'] as $key => $field) {
      if (isset($field['entity_type']) && isset($entity_types[$field['entity_type']]['label'])) {
        $type = $entity_types[$field['entity_type']]['label'];
      }
      else {
        $type = search_api_extract_inner_type($field['type']);
        $type = isset($types[$type]) ? $types[$type] : $type;
      }
      if (empty($facets[$key])) {
        $facets[$key][] = entity_create('search_api_facet', array(
          'index_id' => $index->machine_name,
          'field' => $key,
          'name' => t('!index: !field', array('!field' => $field['name'], '!index' => $index->name)),
          'enabled' => 0,
          'options' => array(),
        ));
      }
      foreach ($facets[$key] as $i => $facet) {
        $k = $i ? "$key-$i" : $key;
        $form['facets'][$k]['facet'] = array(
          '#type' => 'value',
          '#value' => $facet,
        );
        $form['facets'][$k]['enabled'] = array(
          '#type' => 'checkbox',
          '#default_value' => $facet->enabled,
          '#disabled' => $disabled,
        );
        if ($show_status) {
          $form['facets'][$k]['status']['#markup'] = isset($facet->status) ? theme('entity_status', array('status' => $facet->status)) : $empty_status;
        }
        $form['facets'][$k]['field'] = array(
          '#markup' => $field['name'],
        );
        $form['facets'][$k]['type'] = array(
          '#markup' => $type,
        );
        $form['facets'][$k]['name'] = array(
          '#type' => 'textfield',
          '#maxlength' => max(strlen($facet->name), 80),
          '#default_value' => $facet->name,
        );
        $form['facets'][$k]['clone'] = array(
          '#type' => 'checkbox',
          '#default_value' => FALSE,
        );
        if (($facet->enabled && !$facet->hasStatus(ENTITY_OVERRIDDEN)) || empty($facet->delta) || !$facet->hasStatus(ENTITY_CUSTOM)) {
          $form['facets'][$k]['delete'] = array(
            '#markup' => '&nbsp;',
          );
        }
        else {
          $form['facets'][$k]['delete'] = array(
            '#type' => 'checkbox',
            '#default_value' => FALSE,
          );
          if ($facet->hasStatus(ENTITY_IN_CODE)) {
            $form['facets'][$k]['delete']['#title'] = '*';
          }
        }
      }
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

/**
 * Validation callback for search_api_facets_index_select().
 */
function search_api_facets_index_select_validate(array $form, array &$form_state) {
  $warn = FALSE;
  foreach ($form_state['values']['facets'] as $key => $v) {
    if (!empty($v['facet']->delta) || $v['enabled']) {
      // -> This setting will be stored.
      if (!$v['name']) {
        form_set_error("facets][$key][name", t("You can't set an empty name."));
      }
      elseif (strlen($v['name']) > 80) {
        form_set_error("facets][$key][name", t('Names cannot be longer than 80 characters, but "@name" is @count characters long.',
            array('@name' => $v['name'], '@count' => strlen($v['name']))));
      }
    }
    elseif ($v['facet']->name != $v['name']) {
      $warn = TRUE;
    }
  }
  if ($warn) {
    drupal_set_message(t('Note that changed names of facet blocks that are disabled and have no settings yet, are not saved.'), 'warning');
  }
}

/**
 * Submit callback for search_api_facets_index_select().
 */
function search_api_facets_index_select_submit(array $form, array &$form_state) {
  $index = $form_state['index'];
  $count = 0;
  $clone_count = 0;
  $delete_count = 0;
  $reset_count = 0;

  $counts = array();
  foreach ($form_state['values']['facets'] as $key => $v) {
    $field = $v['facet']->field;
    $c = $counts[$field] = (isset($counts[$field]) ? $counts[$field] + 1 : 1);
    if (empty($v['enabled']) && empty($v['facet']->delta)) {
      // Field is not stored, what use would cloning or deleting be?
      continue;
    }
    if ((empty($v['enabled']) && empty($v['clone'])) || $v['facet']->hasStatus(ENTITY_OVERRIDDEN)) {
      // This is the only case in which a "delete" makes sense.
      if (!empty($v['delete'])) {
        $v['facet']->delete();
        $v['facet']->hasStatus(ENTITY_OVERRIDDEN) ? ++$reset_count : ++$delete_count;
        continue;
      }
    }
    $f = $v['facet'];
    $update = $f->enabled != $v['enabled'] || $f->name != $v['name'];
    if ($update) {
      $f = clone $f;
      $f->enabled = $v['enabled'];
      $f->name = $v['name'];
      $f->save();
      ++$count;
    }
    if ($v['clone']) {
      $f = $v['facet'];
      unset($f->id, $f->delta);
      $f->name = t('!index: !field #!num',
          array('!field' => $index->options['fields'][$f->field]['name'], '!index' => $index->name, '!num' => $c + 1));
      $f->save();
      ++$clone_count;
    }
  }

  if ($clone_count) {
    drupal_set_message(format_plural($clone_count, '1 facet block was successfully cloned.', '@count facet blocks were successfully cloned.'));
  }
  if ($delete_count) {
    drupal_set_message(format_plural($delete_count, 'The settings of 1 facet block were successfully deleted.', 'The settings of @count facet blocks were successfully deleted.'));
  }
  if ($count) {
    drupal_set_message(format_plural($count, '1 facet block was successfully updated.', '@count facet blocks were successfully updated.'));
  }
  if ($reset_count) {
    drupal_set_message(format_plural($reset_count, '1 facet configuration was reset.', '@count facet configurations were reset.'));
  }
  if (!($count + $clone_count + $delete_count + $reset_count)) {
    drupal_set_message(t('No values were changed.'));
  }
}

/**
 * Submit callback for search_api_facets_index_select(), when clicking on
 * "Delete facet settings".
 */
function search_api_facets_index_select_submit_delete(array $form, array &$form_state) {
  $index = $form_state['index'];
  $ret = search_api_facet_delete_multiple(array('index_id' => $index->machine_name));
  if ($ret) {
    drupal_set_message(t('All facet data stored for this index was deleted.'));
  }
  else {
    drupal_set_message(t('There was no data to delete.'), 'warning');
  }
  $form_state['redirect'] = 'admin/config/search/search_api/index/' . $index->machine_name;
}

/**
 * Submit callback for search_api_facets_index_select(), for exporting settings.
 */
function _search_api_facets_index_export_submit(array $form, array &$form_state) {
  $index = $form_state['index'];
  $method = $form_state['values']['export']['method'];

  // Load appropriate facets.
  $ids = ($method == 'custom') ? array_filter($form_state['values']['export']['facets']) : NULL;
  $conditions = ($method == 'enabled') ? array('enabled' => 1) : array();
  $conditions['index_id'] = $index->machine_name;
  $facets = $facets = search_api_facet_load_multiple(FALSE, $method == 'all' ? array() : array('enabled' => 1));

  // Don't include two facets for the same field.
  foreach ($facets as $delta => $facet) {
    if (!empty($fields[$facet->field])) {
      unset($facets[$delta]);
    }
    else {
      $fields[$facet->field] = TRUE;
    }
  }

  // Load realms.
  $realms = array();
  foreach (array_filter($form_state['values']['export']['realms']) as $realm) {
    $realms[$realm] = facetapi_realm_load($realm);
  }
  $realms = array_filter($realms);

  // Export settings.
  search_api_facets_export_to_facetapi($index, $facets, $realms);

  // Show success message.
  $items = array();
  foreach ($facets as $facet) {
    $items[] = $facet->name;
  }
  drupal_set_message('<p>' . t('Successfully exported the settings of the following facets for this index:') . '</p>' .
      theme('item_list', array('items' => $items)));

}

/**
 * Theming function for rendering a form as a table.
 *
 * @param array $variables
 *   An array of variables to use, containing only one entry:
 *   - element: The sub-form to render as a table.
 *
 * @return string
 *   HTML displaying the specified sub-form as a table.
 */
function theme_search_api_facets_form_table(array $variables) {
  $form = $variables['element'];

  $rows = array();
  foreach (element_children($form) as $id) {
    $row = array();
    foreach (element_children($form[$id]) as $field) {
      if ($cell = render($form[$id][$field])) {
        $row[] = $cell;
      }
    }
    $rows[] = $row;
  }

  $vars['rows'] = $rows;
  if (isset($form['#table_header'])) {
    $vars['header'] = $form['#table_header'];
  }
  if (isset($form['#table_empty'])) {
    $vars['empty'] = $form['#table_empty'];
  }
  return theme('table', $vars);
}
