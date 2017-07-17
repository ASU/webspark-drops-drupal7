<?php

/**
 * @file
 * Export Drupal Commerce file licenses to Views.
 */

/**
 * Implements hook_views_data()
 */
function commerce_file_views_data() {
  $data = array();

  // -----------------------------------------------------------------------
  // License Table

  $data['commerce_file_license']['table']['group']  = t('Commerce File License');
  $data['commerce_file_license']['table']['base'] = array(
    'field' => 'license_id',
    'title' => t('Commerce File License'),
    'help' => t('File Licenses granted in the store.'),
  );

  // For other base tables, explain how we join
  // 'left_field' is the primary key in the referenced table.
  // 'field' is the foreign key in this table.
  $data['commerce_file_license']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'commerce_file_license_log' => array(
      'left_field' => 'license_id',
      'field' => 'license_id',
    ),
  );


  $data['commerce_file_license']['license_id'] = array(
    'title' => t('License ID', array(), array('context' => 'a drupal commerce file license')),
    'help' => t('The unique internal identifier of the license.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
  );

  // Expose the license type.
  // - only 1 type for now
/*
  $data['commerce_file_license']['type'] = array(
    'title' => t('License type', array(), array('context' => 'a drupal commerce file license')),
    'help' => t('The type of the license.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license_type',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_file_handler_filter_license_type',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
*/

  $data['commerce_file_license']['status'] = array(
    'title' => t('License status'),
    'help' => t('The status of the license.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license_status',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_file_handler_filter_license_status',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['commerce_file_license']['created'] = array(
    'title' => t('Created date'),
    'help' => t('The date the license was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['commerce_file_license']['changed'] = array(
    'title' => t('Updated date'),
    'help' => t('The date the license was last updated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['commerce_file_license']['uid'] = array(
    'title' => t('Owner uid'),
    'help' => t('Uid of the file license owner.'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name', // display this field in the summary
    ),
    'filter' => array(
      'title' => t('Name'),
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('License owner'),
    ),
  );

  $data['commerce_file_license']['granted'] = array(
    'title' => t('Granted date'),
    'help' => t('The date the license was initially granted.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );



  // -----------------------------------------------------------------------
  // Entity Property Fields

  // -- Limits ---------------------------------------------- //
  $data['commerce_file_license']['duration'] = array(
    'title' => t('Duration'),
    'help' => t('The duration of the license.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license_duration',
    ),
  );

  $data['commerce_file_license']['expiration'] = array(
    'title' => t('Expiration'),
    'help' => t('The date the license expires.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license_expiration',
    ),
  );

  $data['commerce_file_license']['download_limit'] = array(
    'title' => t('Download limit'),
    'help' => t('The number of times the licensed file may be downloaded by the owner.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license_limit',
    ),
  );

  $data['commerce_file_license']['address_limit'] = array(
    'title' => t('Address limit'),
    'help' => t('The number of different IP addresses from which the licensed file may be downloaded.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license_limit',
    ),
  );


  // -- Access Stats ---------------------------------------- //

  $data['commerce_file_license']['download_count'] = array(
    'title' => t('Current number of downloads'),
    'help' => t('The current number of downloads of the licensed file.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license_property',
    ),
  );

  $data['commerce_file_license']['address_count'] = array(
    'title' => t('Current number of addresses'),
    'help' => t('The current number of addresses used to access the licensed file.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license_property',
    ),
  );

  $data['commerce_file_license']['time_remaining'] = array(
    'title' => t('Current time remaining'),
    'help' => t('The current time remaining until expiration the license.'),
    'field' => array(
      'handler' => 'commerce_file_handler_field_license_duration',
    ),
  );



  // -- Admin links ---------------------------------------- //
  $data['commerce_file_license']['view_license'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the view of the license.'),
      'handler' => 'commerce_file_handler_field_license_link',
    ),
  );
  $data['commerce_file_license']['edit_license'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a simple link to edit the license.'),
      'handler' => 'commerce_file_handler_field_license_link_edit',
    ),
  );
  $data['commerce_file_license']['clone_license'] = array(
    'field' => array(
      'title' => t('Clone link'),
      'help' => t('Provide a simple link to clone the license.'),
      'handler' => 'commerce_file_handler_field_license_link_clone',
    ),
  );
  $data['commerce_file_license']['delete_license'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a simple link to delete the license.'),
      'handler' => 'commerce_file_handler_field_license_link_delete',
    ),
  );


  // -----------------------------------------------------------------------
  // License Log Table

  $data['commerce_file_license_log']['table']['group']  = t('Commerce File License Log');
  $data['commerce_file_license_log']['table']['base'] = array(
    'field' => 'aid',
    'title' => t('Commerce File License Log'),
    'help' => t('Logs for File Licenses granted in the store.'),
  );

  // For other base tables, explain how we join
  // 'left_field' is the primary key in the referenced table.
  // 'field' is the foreign key in this table.
  $data['commerce_file_license_log']['table']['join'] = array(
    'commerce_file_license' => array(
      'left_field' => 'license_id',
      'field' => 'license_id',
    ),
  );

  $data['commerce_file_license_log']['aid'] = array(
    'title' => t('Access ID'),
    'help' => t('The unique internal identifier of the access log.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'wid',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['commerce_file_license_log']['license_id'] = array(
    'title' => t('License ID'),
    'help' => t('The unique internal identifier of the license.'),
    'field' => array(
      'handler' => 'views_handler_filter_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
  );

  $data['commerce_file_license_log']['timestamp'] = array(
    'title' => t('Access Timestamp'),
    'help' => t('The date the log was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['commerce_file_license_log']['hostname'] = array(
    'title' => t('Hostname'),
    'help' => t('Hostname of the user.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function commerce_file_views_data_alter(&$data) {
  // Product alters
  if (isset($data['commerce_product'])) {
    // Add the product filter for filtering by product types with Commerce File Fields
    $data['commerce_product']['commerce_file_product_type'] = array(
      'title' => t('Product is a product type with Commerce File fields'),
      'help' => t("Filter products to those of a product types that contain Commerce File fields."),
      'filter' => array(
        'handler' => 'commerce_file_handler_filter_file_product_type',
      ),
    );
  }

  // Order alters
  if (isset($data['commerce_order'])) {
    // Define a handler for an area used for order issue licenses.
    $data['commerce_order']['license_issue_form'] = array(
      'title' => t('Issue File Licenses Form'),
      'help' => t('Displays a form to update all file licenses associated with this order.'),
      'area' => array(
        'handler' => 'commerce_file_handler_area_license_issue_order_form',
      ),
    );
  }

  // Line item alters
  if (isset($data['commerce_line_item'])) {
    // Adds a field for a form to issue licenses based on a line item.
    $data['commerce_line_item']['license_issue_form'] = array(
      'field' => array(
        'title' => t('Issue File Licenses Form'),
        'help' => t('Displays a form to update all file licenses associated with this line item.'),
        'handler' => 'commerce_file_handler_field_license_issue_line_item_form',
      ),
    );

    // Line item reference field inverse relationship
    // - Adds inverse relationships between the line items and entity types referencing
    // - Commerce File is one of the few modules to use line item references outside of orders
    foreach (field_info_fields() as $field_name => $field) {
      if ($field['type'] !== 'commerce_line_item_reference') {
        continue;
      }

      foreach ($field['bundles'] as $entity_type => $bundles) {
        if ($entity_type == 'commerce_order') {
          continue;
        }

        $entity_info = entity_get_info($entity_type);
        $pseudo_field_name = 'reverse_' . $field['field_name'] . '_' . $entity_type;
        list($label, $all_labels) = field_views_field_label($field['field_name']);
        $entity_label = $entity_info['label'];
        if ($entity_label == t('Node')) {
          $entity_label = t('Content');
        }

        if (!isset($data['commerce_line_item'][$pseudo_field_name]['relationship'])) {
          $data['commerce_line_item'][$pseudo_field_name]['relationship'] = array(
            'title' => t('@entity using @field', array('@entity' => $entity_label, '@field' => $label)),
            'help' => t('Relate each @entity with a @field set to the line item.', array('@entity' => $entity_label, '@field' => $label)),
            'handler' => 'views_handler_relationship_entity_reverse',
            'field_name' => $field['field_name'],
            'field table' => _field_sql_storage_tablename($field),
            'field field' => $field['field_name'] . '_line_item_id',
            'base' => $entity_info['base table'],
            'base field' => $entity_info['entity keys']['id'],
            'label' => t('!field_name', array('!field_name' => $field['field_name'])),
            'join_extra' => array(
              0 => array(
                'field' => 'entity_type',
                'value' => $entity_type,
              ),
              1 => array(
                'field' => 'deleted',
                'value' => 0,
                'numeric' => TRUE,
              ),
            ),
          );
        }
      }
    }
  }
}

/**
 * Implements hook_field_views_data().
 *
 * Views integration for commerce_file fields.
 * - Adds a file relationship to the default field data.
 *
 * @see field_views_field_default_views_data()
 */
function commerce_file_field_views_data($field) {
  $data = field_views_field_default_views_data($field);
  foreach ($data as $table_name => $table_data) {
    // Add the relationship only on the fid field.
    $data[$table_name][$field['field_name'] . '_fid']['relationship'] = array(
      'handler' => 'views_handler_relationship',
      'base' => 'file_managed',
      'entity type' => 'file',
      'base field' => 'fid',
      'label' => t('file from !field_name', array('!field_name' => $field['field_name'])),
    );
  }

  return $data;
}

/**
 * Implements hook_field_views_data_views_data_alter().
 */
function commerce_file_field_views_data_views_data_alter(&$data, $field) {
  // Provide reverse relationships on commerce_file fields.
  foreach ($field['bundles'] as $entity_type => $bundles) {
    $entity_info = entity_get_info($entity_type);
    $pseudo_field_name = 'reverse_' . $field['field_name'] . '_' . $entity_type;

    list($label, $all_labels) = field_views_field_label($field['field_name']);
    $entity = $entity_info['label'];
    if ($entity == t('Node')) {
      $entity = t('Content');
    }

    if (!isset($data['file_managed'][$pseudo_field_name]['relationship'])) {
      $data['file_managed'][$pseudo_field_name]['relationship'] = array(
        'title' => t('@entity using @field', array('@entity' => $entity, '@field' => $label)),
        'help' => t('Relate each @entity with a @field set to the file.', array('@entity' => $entity, '@field' => $label)),
        'handler' => 'views_handler_relationship_entity_reverse',
        'field_name' => $field['field_name'],
        'field table' => _field_sql_storage_tablename($field),
        'field field' => $field['field_name'] . '_fid',
        'base' => $entity_info['base table'],
        'base field' => $entity_info['entity keys']['id'],
        'label' => t('!field_name', array('!field_name' => $field['field_name'])),
        'join_extra' => array(
          0 => array(
            'field' => 'entity_type',
            'value' => $entity_type,
          ),
          1 => array(
            'field' => 'deleted',
            'value' => 0,
            'numeric' => TRUE,
          ),
        ),
      );
    }
  }
}

/**
 * Implements hook_views_plugins
 */
function commerce_file_views_plugins() {
  return array(
    'argument validator' => array(
      'commerce_file_user' => array(
        'title' => t('Commerce File User'),
        'handler' => 'commerce_file_plugin_argument_validate_user',
        'path' => drupal_get_path('module', 'commerce_file') . '/views/handlers', // not necessary for most modules
      ),
    ),
  );
}
