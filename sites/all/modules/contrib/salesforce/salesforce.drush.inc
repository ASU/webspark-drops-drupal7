<?php

/**
 * @file
 * Drush integration for Salesforce.
 */

/**
 * Implements hook_drush_command().
 */
function salesforce_drush_command() {
  $items['sf-rest-version'] = array(
    'description' => 'Displays information about the current REST API version',
    'aliases' => array('sfrv'),
  );
  $items['sf-list-objects'] = array(
    'description' => 'List the objects that are available in your organization and available to the logged-in user.',
    'aliases' => array('sflo'),
  );
  $items['sf-describe-object'] = array(
    'description' => 'Retrieve all the metadata for an object, including information about each field, URLs, and child relationships.',
    'aliases' => array('sfdo'),
    'arguments' => array(
      'object' => 'The object name in Salesforce.',
    ),
    'options' => array(
      'fields' => 'Display information about fields that are part of the object.',
      'field-data' => 'Display information about a specific field that is part of an object',
    ),
  );
  $items['sf-read-object'] = array(
    'description' => 'Retrieve all the data for an object with a specific ID.',
    'aliases' => array('sfro'),
    'arguments' => array(
      'object' => 'The object name in Salesforce (e.g. Account).',
      'id' => 'The object ID in Salesforce.',
    ),
    'options' => array(
      'format' => array(
        'description' => 'Format to output the object. Use "print_r" for print_r (default), "export" for var_export, and "json" for JSON.',
        'example-value' => 'export',
      ),
    ),
  );
  $items['sf-create-object'] = array(
    'description' => 'Create an object with specified data.',
    'aliases' => array('sfco'),
    'arguments' => array(
      'object' => 'The object type name in Salesforce (e.g. Account).',
      'data' => 'The data to use when creating the object (default is JSON format). Use \'-\' to read the data from STDIN.',
    ),
    'options' => array(
      'format' => array(
        'description' => 'Format to parse the object. Use  "json" for JSON (default) or "query" for data formatted like a query string, e.g. \'Company=Foo&LastName=Bar\'.',
        'example-value' => 'json',
      ),
    ),
  );
  $items['sf-query-object'] = array(
    'description' => 'Query an object using SOQL with specified conditions.',
    'aliases' => array('sfqo'),
    'arguments' => array(
      'object' => 'The object type name in Salesforce (e.g. Account).',
    ),
    'options' => array(
      'format' => array(
        'description' => 'Format to output the objects. Use "print_r" for print_r (default), "export" for var_export, and "json" for JSON.',
        'example-value' => 'export',
      ),
      'where' =>array(
        'description' => 'A WHERE clause to add to the SOQL query',
        'example-value' => 'isDeleted = TRUE',
      ),
      'fields' =>array(
        'description' => 'A comma-separated list fields to select in the SOQL query. If absent, an API call is used to find all fields',
        'example-value' => 'Id, LastName',
      ),
    ),
  );
  $items['sf-list-resources'] = array(
    'description' => 'Lists the resources available for the specified API version. It provides the name and URI of each resource.',
    'aliases' => array('sflr'),
  );
  $items['sf-execute-query'] = array(
    'description' => 'Execute a SOQL query.',
    'aliases' => array('sfeq'),
    'arguments' => array(
      'query' => 'The query to execute.',
    ),
  );
  return $items;
}

/**
 * List the resources available for the specified API version.
 *
 * This command provides the name and URI of each resource.
 */
function drush_salesforce_sf_list_resources() {
  $salesforce = _drush_salesforce_drush_get_api();
  $resources = $salesforce->listResources();
  if ($resources) {
    $items[] = array('Resource', 'URL');
    foreach ($resources as $resource => $url) {
      $items[] = array($resource, $url);
    }
    drush_print("The following resources are available:\n");
    drush_print_table($items);
  }
  else {
    drush_log('Could not obtain a list of resources!', 'error');
  }

}

/**
 * Describes a Salesforce object.
 *
 * Use the --fields option to display information about the fields of an object,
 * or the --field-data option to display information about a single field in an
 * object.
 *
 * @param string $object_name
 *   The name of a Salesforce object to query.
 */
function drush_salesforce_sf_describe_object($object_name = NULL) {
  if (!$object_name) {
    return drush_log('Please specify an object as an argument.', 'error');
  }
  $salesforce = _drush_salesforce_drush_get_api();

  $object = $salesforce->objectDescribe($object_name);

  // Return if we cannot load any data.
  if (!is_array($object)) {
    return drush_log(dt('Could not load data for object !object', array('!object' => $object)), 'error');
  }
  // Display only information about fields for an option,
  if (drush_get_option('fields')) {
    $rows = array(array('Name', 'Type', 'Label'));
    foreach ($object['fields'] as $field) {
      $rows[] = array($field['name'], $field['type'], $field['label']);
    }
    drush_print_r($rows);
    drush_print_table($rows, TRUE);
    return;
  }

  // Display only information about a specific field.
  if ($fieldname = drush_get_option('field-data')) {
    $field_data = NULL;
    foreach ($object['fields'] as $field) {
      if ($field['name'] === $fieldname) {
        $field_data = $field;
        break;
      }
    }
    if (!$field_data) {
      drush_log(dt('Could not load data for field !field on !object object', array(
        '!field' => $fieldname,
        '!object' => $object_name,
      )), 'error');
    }
    else {
      drush_print_r($field);
    }

    return;
  }

  // Display information about the object.
  // @TODO add remaining field objects?
  $rows = array();
  $rows[] = array('Name', $object['name']);
  $rows[] = array(
    'Fields',
    isset($object['fields']) ? count($object['fields']) : 0,
  );
  $rows[] = array(
    'Child Relationships',
    isset($object['childRelationships']) ? count($object['childRelationships']) : 0,
  );
  $rows[] = array(
    'Searchable',
    ($object['searchable'] == 1) ? 'TRUE' : 'FALSE',
  );
  $rows[] = array('Creatable', ($object['createable'] == 1) ? 'TRUE' : 'FALSE');
  $rows[] = array('Deletable', ($object['deletable'] == 1) ? 'TRUE' : 'FALSE');
  $rows[] = array('Mergeable', ($object['mergeable'] == 1) ? 'TRUE' : 'FALSE');
  $rows[] = array('Queryable', ($object['queryable'] == 1) ? 'TRUE' : 'FALSE');
  drush_print_table($rows);
}

/**
 * Displays information about the REST API version the site is using.
 */
function drush_salesforce_sf_rest_version() {
  $salesforce = _drush_salesforce_drush_get_api();
  if (isset($salesforce->rest_api_version)) {
    $rows[] = array('Salesforce', 'Value');
    foreach ($salesforce->rest_api_version as $key => $value) {
      $rows[] = array($key, $value);
    }
    $rows[] = array('login url', $salesforce->login_url);
    drush_print_table($rows, TRUE);
  }
  else {
    drush_log('Could not obtain information about the current REST API version!', 'error');
  }
}

/**
 * Wrapper around salesforce_get_api().
 *
 * If salesforce_get_api() does not return a connection to Salesforce,
 * this function can prompt the user for username/password to obtain a new
 * token.
 *
 * @TODO implement this function
 */
function _drush_salesforce_drush_get_api() {
  if ($salesforce = salesforce_get_api()) {
    return $salesforce;
  }
}

/**
 * List Salesforce objects.
 *
 * This command lists Salesforce objects that are available in your organization
 * and available to the logged-in user.
 */
function drush_salesforce_sf_list_objects() {
  $salesforce = _drush_salesforce_drush_get_api();
  if ($objects = $salesforce->objects()) {
    drush_print('The following objects are available in your organization and available to the logged-in user.');
    $rows[] = array('Name', 'Label', 'Label Plural');
    foreach ($objects as $object) {
      $rows[] = array(
        $object['name'],
        $object['label'],
        $object['labelPlural'],
      );
    }
    drush_print_table($rows, TRUE);
  }
  else {
    drush_log('Could not load any information about available objects.', 'error');
  }

}

/**
 * Read a Salesforce object available to the logged-in user.
 *
 * @param $name
 *   The object type name, e.g. Account
 * @param $id
 *   The Salesforce ID
 */
function drush_salesforce_sf_read_object($name, $id) {
  $salesforce = _drush_salesforce_drush_get_api();
  try {
    if ($object = $salesforce->objectRead($name, $id)) {
      drush_print(drush_format($object));
    }
  }
  catch (SalesforceException $e) {
    drush_log($e->getMessage(), 'error');
  }
}

/**
 * Create a Salesforce object available to the logged-in user.
 *
 * @param $name
 *   The object type name, e.g. Account
 * @param $data
 *   The object data, or '-' to read from stdin
 */
function drush_salesforce_sf_create_object($name, $data) {

  if ($data == '-') {
    $data = stream_get_contents(STDIN);
  }
  $format = drush_get_option('format', 'json');
  $params = array();
  switch ($format) {
    case 'query':
      parse_str($data, $params);
      break;
    case 'json':
      $params = json_decode($data, TRUE);
      break;
    default:
      drush_log(dt('Invalid format'), 'error');
      return;
  }
  $salesforce = _drush_salesforce_drush_get_api();
  try {
    if ($result = $salesforce->objectCreate($name, $params)) {
      drush_print_r($result);
    }
  }
  catch (SalesforceException $e) {
    drush_log($e->getMessage(), 'error');
  }
}

/**
 * Query Salesforce objects available to the logged-in user.
 *
 * @param $name
 *   The object type name, e.g. Account
 */
function drush_salesforce_sf_query_object($name) {
  $salesforce = _drush_salesforce_drush_get_api();
  $fields = drush_get_option('fields', '');
  if (!$fields) {
    try {
      $object = $salesforce->objectDescribe($name);
    }
    catch (SalesforceException $e) {
      drush_log($e->getMessage(), 'error');
      return;
    }
    $names = array();
    foreach ($object['fields'] as $field) {
      $names[] = $field['name'];
    }
    $fields = implode(',', $names);
  }
  try {
    $where = drush_get_option('where', '');
    if ($where) {
      $where = ' WHERE ' . $where;
    }
    $query = 'SELECT ' . $fields . ' FROM ' . $name;
    // @todo - figure how to leverage SalesforceSelectQuery.
    $result = $salesforce->apiCall('query?q=' . urlencode($query . $where));
    drush_print(drush_format($result));
  }
  catch (SalesforceException $e) {
    drush_log($e->getMessage(), 'error');
  }
}

/**
 * Execute a SOQL query.
 *
 * @param $query
 *   The query to execute
 */
function drush_salesforce_sf_execute_query($query = NULL) {
  if (!$query) {
    return drush_log('Please specify a query as an argument.', 'error');
  }
  $salesforce = _drush_salesforce_drush_get_api();
  try {
    $result = $salesforce->apiCall('query?q=' . urlencode($query));
    drush_print(drush_format($result));
  }
  catch (SalesforceException $e) {
    drush_log($e->getMessage(), 'error');
  }
}
