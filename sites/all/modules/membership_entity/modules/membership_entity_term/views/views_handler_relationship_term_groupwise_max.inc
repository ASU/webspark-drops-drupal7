<?php

/**
 * @file
 * Relationship for membership term groupwise maximum handler.
 */

/**
 * Relationship handler that allows a groupwise maximum of the linked term.
 */
class views_handler_relationship_term_groupwise_max extends views_handler_relationship_groupwise_max {
  /**
   * Defines default values for options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['subquery_status'] = array('default' => array());
    $options['subquery_offset'] = array('default' => 0);
    return $options;
  }

  /**
   * Extends the relationship's basic options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Form type checkboxes may not use 0 as an options key. We'll use -1
    // instead.
    $status_list = membership_entity_get_status_list();
    $status_list[-1] = $status_list[0];
    unset($status_list[0]);

    $form['subquery_status'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Representative term status'),
      '#description' => t('Filter the representative term by status.'),
      '#options' => $status_list,
      '#default_value' => $this->options['subquery_status'],
    );

    $form['subquery_offset'] = array(
      '#type' => 'textfield',
      '#title' => t('Representative term offset'),
      '#description' => t('The number of subquery results to skip. For example, if this field is 3, the 4th result term will be used.'),
      '#default_value' => $this->options['subquery_offset'],
      '#element_validate' => array('element_validate_integer'),
    );

    // Move less common fields to the bottom of the form.
    $form['subquery_namespace']['#weight'] = 98;
    $form['subquery_view']['#weight'] = 99;
    $form['subquery_regenerate']['#weight'] = 100;
  }

  /**
   * Generate a subquery given the user options.
   *
   * This is mostly a copy of parent::left_query except adding a status
   * condition and allowing multiple representative relationships.
   */
  function left_query($options) {
    // Either load another view, or create one on the fly.
    if ($options['subquery_view']) {
      $temp_view = views_get_view($options['subquery_view']);
      // Remove all fields from default display
      unset($temp_view->display['default']->display_options['fields']);
    }
    else {
      // Create a new view object on the fly, which we use to generate a query
      // object and then get the SQL we need for the subquery.
      $temp_view = $this->get_temporary_view();

      // Add the sort from the options to the default display.
      // This is broken, in that the sort order field also gets added as a
      // select field. See http://drupal.org/node/844910.
      // We work around this further down.
      $sort = $options['subquery_sort'];
      if (!empty($sort)) {
        list($sort_table, $sort_field) = explode('.', $sort);
        $sort_options = array('order' => $options['subquery_order']);
        $temp_view->add_item('default', 'sort', $sort_table, $sort_field, $sort_options);
      }
    }

    // Get the namespace string.
    $temp_view->namespace = (!empty($options['subquery_namespace'])) ? '_'. $options['subquery_namespace'] : '_INNER';
    $this->subquery_namespace = (!empty($options['subquery_namespace'])) ? '_'. $options['subquery_namespace'] : 'INNER';

    // The value we add here does nothing, but doing this adds the right tables
    // and puts in a WHERE clause with a placeholder we can grab later.
    $temp_view->args[] = '**CORRELATED**';

    // Add the base table ID field.
    $views_data = views_fetch_data($this->definition['base']);
    $base_field = $views_data['table']['base']['field'];
    $temp_view->add_item('default', 'field', $this->definition['base'], $this->definition['field']);

    // Add the correct argument for our relationship's base
    // ie the 'how to get back to base' argument.
    // The relationship definition tells us which one to use.
    $temp_view->add_item('default', 'argument', $this->definition['argument table'], $this->definition['argument field']);

    // Build the view. The creates the query object and produces the query
    // string but does not run any queries.
    $temp_view->build();

    // Now take the SelectQuery object the View has built and massage it
    // somewhat so we can get the SQL query from it.
    $subquery = $temp_view->build_info['query'];

    // Add a condition based on status.
    $status_list = array_unique(array_filter($options['subquery_status']));
    if (!empty($status_list)) {
      if (array_key_exists(-1, $status_list)) {
        $status_list[-1] = MEMBERSHIP_ENTITY_EXPIRED;
      }
      $subquery->condition($this->definition['base'] . '.status', $status_list, 'IN');
    }

    // Workaround until http://drupal.org/node/844910 is fixed:
    // Remove all fields from the SELECT except the base id.
    $fields =& $subquery->getFields();
    foreach (array_keys($fields) as $field_name) {
      // The base id for this subquery is stored in our definition.
      if ($field_name != $this->definition['field']) {
        unset($fields[$field_name]);
      }
    }

    // Make every alias in the subquery safe within the outer query by
    // appending a namespace to it, '_inner' by default.
    $tables =& $subquery->getTables();
    foreach (array_keys($tables) as $table_name) {
      $tables[$table_name]['alias'] .= $this->subquery_namespace;
      // Namespace the join on every table.
      if (isset($tables[$table_name]['condition'])) {
        $tables[$table_name]['condition'] = $this->condition_namespace($tables[$table_name]['condition']);
      }
    }
    // Namespace fields.
    foreach (array_keys($fields) as $field_name) {
      $fields[$field_name]['table'] .= $this->subquery_namespace;
      $fields[$field_name]['alias'] .= $this->subquery_namespace;
    }
    // Namespace conditions.
    $where =& $subquery->conditions();
    $this->alter_subquery_condition($subquery, $where);
    // Not sure why, but our sort order clause doesn't have a table.
    // TODO: the call to add_item() above to add the sort handler is probably
    // wrong -- needs attention from someone who understands it.
    // In the meantime, this works, but with a leap of faith...
    $orders =& $subquery->getOrderBy();
    foreach ($orders as $order_key => $order) {
      // But if we're using a whole view, we don't know what we have!
      if ($options['subquery_view']) {
        list($sort_table, $sort_field) = explode('.', $order_key);
      }
      $orders[$sort_table . $this->subquery_namespace . '.' . $sort_field] = $order;
      unset($orders[$order_key]);
    }

    // The query we get doesn't include the LIMIT, so add it here.
    $subquery->range($options['subquery_offset'], 1);

    // Extract the SQL the temporary view built.
    $args = $subquery->getArguments();
    $subquery_sql = $subquery->__toString();

    // Replace the placeholder with the outer, correlated field.
    // Eg, change the placeholder ':users_uid' into the outer field 'users.uid'.
    // We have to work directly with the SQL, because putting a name of a field
    // into a SelectQuery that it does not recognize (because it's outer) just
    // makes it treat it as a string. We use a pattern to match multiple
    // relationships.
    $outer_pattern  = '/:' . str_replace('.', '_', $this->definition['outer field']) . '\d*/i';

    // Handle outer field from a relationship.
    list($outer_table, $outer_field) = explode('.', $this->definition['outer field']);
    if (!empty($this->relationship)) {
      $outer_table = $this->relationship;
    }

    $subquery_sql = preg_replace($outer_pattern, "$outer_table.$outer_field", $subquery_sql);
    $subquery_sql = str_replace(array_keys($args), $args, $subquery_sql);
    return $subquery_sql;
  }
}
