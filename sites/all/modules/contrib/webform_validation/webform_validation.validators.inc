<?php

/**
 * @file
 * Provides validation functionality and hooks
 */

/**
 * Implements hook_webform_validation_validators().
 *
 * This function returns an array of validators, in the validator key => options array form.
 * Possible options:
 * - name (required): name of the validator
 * - component types (required): defines which component types can be validated by this validator. Specify 'all' to allow all types
 * - negatable (optional): define whether the rule can be negated, meaning it will validate the inverse of the rule.
 * - custom_error (optional): define whether a user can specify a custom error message upon creating the validation rule.
 * - custom_data (optional): define whether custom data can be added to the validation rule
 * - min_components (optional): define the minimum number of components to be selected for creating a validation rule
 * - max_components (optional): define the maximum number of components to be selected for creating a validation rule
 * - description (optional): provide a descriptive explanation about the validator
 */
function webform_validation_webform_validation_validators() {
  $validators = array(
    'numeric' => array(
      'name' => t('Numeric values'),
      'component_types' => array(
        'hidden',
        'number',
        'textfield',
      ),
      'custom_data' => array(
        'label' => t('Specify numeric validation range'),
        'description' => t('Optionally specify the minimum-maximum range to validate the user-entered numeric value against.') . ' ' . t('Usage') . ':'
          . theme('item_list', array('items' => array(t('empty: no value validation'), t('"100": greater than or equal to 100'), t('"|100": less than or equal to 100 (including negative numbers)'), t('"0|100": greater than or equal to 0 &amp; less than or equal to 100'), t('"10|100": greater than or equal to 10 &amp; less than or equal to 100'), t('"-100|-10": greater than or equal to -100 &amp; less than or equal to -10')))),
        'required' => FALSE,
      ),
      'description' => t('Verifies that user-entered values are numeric, with the option to specify min and / or max values.'),
    ),
    'min_length' => array(
      'name' => t('Minimum length'),
      'component_types' => array(
        'email',
        'hidden',
        'number',
        'textarea',
        'textfield',
      ),
      'custom_data' => array(
        'label' => t('Minimum number of characters'),
        'description' => t('Specify the minimum number of characters that have to be entered to pass validation.'),
      ),
      'description' => t('Verifies that a user-entered value contains at least the specified number of characters.'),
    ),
    'max_length' => array(
      'name' => t('Maximum length'),
      'component_types' => array(
        'email',
        'hidden',
        'number',
        'textarea',
        'textfield',
      ),
      'custom_data' => array(
        'label' => t('Maximum number of characters'),
        'description' => t('Specify the maximum number of characters that can be entered to pass validation.'),
      ),
      'description' => t('Verifies that a user-entered value contains at most the specified number of characters.'),
    ),
    'min_words' => array(
      'name' => t('Minimum number of words'),
      'component_types' => array(
        'hidden',
        'html_textarea',
        'textarea',
        'textfield',
      ),
      'custom_data' => array(
        'label' => t('Minimum number of words'),
        'description' => t('Specify the minimum number of words that have to be entered to pass validation. Words are defined as strings of letters separated by spaces.'),
      ),
      'description' => t('Verifies that a user-entered value contains at least the specified number of words.'),
    ),
    'max_words' => array(
      'name' => t('Maximum number of words'),
      'component_types' => array(
        'hidden',
        'html_textarea',
        'textarea',
        'textfield',
      ),
      'custom_data' => array(
        'label' => t('Maximum number of words'),
        'description' => t('Specify the maximum number of words that have to be entered to pass validation. Words are defined as strings of letters separated by spaces.'),
      ),
      'description' => t('Verifies that a user-entered value contains at most the specified number of words.'),
    ),
    // Only available in Webform 4; removed below if not.
    'sum' => array(
      'name' => t('Adds up to'),
      'component_types' => array(
        'number',
      ),
      'custom_data' => array(
        'label' => t('Number the fields add up to'),
        'description' => t('Specify the number and the type of comparison. For example:') . theme('item_list', array('items' => array(
          t('Enter "=3" if the components must add up to exactly 3.'),
          t('Enter ">10" if the components must add up to greater than 10.'),
          t('Enter ">=10" if the components must add up to greater than or equal to 10.'),
          t('Enter "<20" if the components must add up to less than 20.'),
          t('Enter "<=20" if the components must add up to less than or equal to 20.'),
        ))),
      ),
      'description' => t('Require the values of the selected fields to add up to exactly, greater than or equal to, or less than or equal to a specified number.'),
    ),
    'equal' => array(
      'name' => t('Equal values'),
      'component_types' => array(
        'date',
        'email',
        'hidden',
        'number',
        'select',
        'textarea',
        'textfield',
        'time',
        'boolean',
      ),
      'min_components' => 2,
      'description' => t('Verifies that all specified components contain equal values. If all components are of type email, they will get case-insensitive comparison.'),
    ),
    'comparison' => array(
      'name' => t('Compare two values'),
      'component_types' => array(
        'date',
        'email',
        'hidden',
        'number',
        'select',
        'textarea',
        'textfield',
        'time',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Comparison operator'),
        'description' => t('Specify the comparison operator you want to use. Must be one of: >, >=, <, <=. The validator will compare the first component with the second using this operator. If the components are of type email, they will get case-insensitive comparison.'),
      ),
      'min_components' => 2,
      'max_components' => 2,
      'description' => t('Compare two values for greater than (>), less than (<), greater than or equal to (>=), or less than or equal to (<=).'),
    ),
    'unique' => array(
      'name' => t('Unique values'),
      'component_types' => array(
        'date',
        'email',
        'hidden',
        'number',
        'select',
        'textarea',
        'textfield',
        'time',
        'boolean',
      ),
      'min_components' => 2,
      'description' => t('Verifies that none of the specified components contain the same value as another selected component in this submission. (To check that values are unique between submissions, use the unique validation option on the "Edit component" page for that component.) If all components are of type email, they will get case-insensitive comparison.'),
    ),
    'specific_value' => array(
      'name' => t('Specific value(s)'),
      'negatable' => TRUE,
      'component_types' => array(
        'email',
        'hidden',
        'number',
        'select',
        'textarea',
        'textfield',
        'boolean',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('(Key) value'),
        'description' => t('Specify the specific value(s) you want the component to contain. Separate multiple options by a comma. For components that have keys, use the key value instead.'),
      ),
      'max_components' => 1,
      'description' => t('Verifies that the value of the specified component is from a list of allowed values.'),
    ),
    'default_value' => array(
      'name' => t('Default value'),
      'negatable' => TRUE,
      'component_types' => array(
        'email',
        'hidden',
        'number',
        'select',
        'textarea',
        'textfield',
        'boolean',
      ),
      'custom_error' => TRUE,
      'description' => t('Verifies that the user-entered value is the default value for that component. Negate if you want not the default value.'),
    ),
    'someofseveral' => array(
      'name' => t('Some of several'),
      'component_types' => array(
        'date',
        'email',
        'file',
        'number',
        'select',
        'textarea',
        'textfield',
        'time',
        'boolean',
      ),
      'custom_data' => array(
        'label' => t('Number to be completed'),
        'description' => t('Specify the number that must be completed and the type of comparison. For example:') . theme('item_list', array('items' => array(
          t('Enter ">=1" if the user must complete <b>at least</b> 1 of the selected components.'),
          t('Enter "=3" if the user must complete <b>exactly</b> 3 of the selected components.'),
          t('Enter "<=2" if the user must complete <b>at most</b> 2 of the selected components.'),
        ))),
      ),
      'min_components' => 2,
      'description' => t('Requires the user to complete some number of components out of a group of components. For example, complete at least 2 out of 3, complete at most 4 out of 6, or complete exactly 3 our of 4.'),
    ),
    'select_min' => array(
      'name' => t('Minimum number of selections required'),
      'component_types' => array(
        'select',
      ),
      'custom_data' => array(
        'label' => t('Minimum number of selections'),
        'description' => t('Specify the minimum number of options a user should select.'),
      ),
      'description' => t('Forces the user to select at least a defined number of options from the specified webform components.'),
    ),
    'select_max' => array(
      'name' => t('Maximum number of selections allowed'),
      'component_types' => array(
        'select',
      ),
      'custom_data' => array(
        'label' => t('Maximum number of selections'),
        'description' => t('Specify the maximum number of options a user can select.'),
      ),
      'description' => t('Forces the user to select at most a defined number of options from the specified webform components.'),
    ),
    'select_exact' => array(
      'name' => t('Exact number of selections required'),
      'negatable' => TRUE,
      'component_types' => array(
        'select',
      ),
      'custom_data' => array(
        'label' => t('Number of selections'),
        'description' => t('Specify how many options a user can select.'),
      ),
      'description' => t('Forces the user to select exactly the defined number of options from the specified webform components.'),
    ),
    'plain_text' => array(
      'name' => t('Plain text (disallow tags)'),
      'negatable' => TRUE,
      'component_types' => array(
        'email',
        'hidden',
        'textarea',
        'textfield',
      ),
      'description' => t('Verifies that user-entered data doesn\'t contain HTML tags.'),
    ),
    'starts_with' => array(
      'name' => t('Starts with'),
      'negatable' => TRUE,
      'component_types' => array(
        'email',
        'hidden',
        'number',
        'textarea',
        'textfield',
      ),
      'custom_data' => array(
        'label' => t('Starts with'),
        'description' => t('Enter the text that this field must start with.'),
      ),
      'description' => t('Verifies that user-entered data starts with a given string.'),
    ),
    'ends_with' => array(
      'name' => t('Ends with'),
      'negatable' => TRUE,
      'component_types' => array(
        'email',
        'hidden',
        'number',
        'textarea',
        'textfield',
      ),
      'custom_data' => array(
        'label' => t('Ends with'),
        'description' => t('Enter the text that this field must end with.'),
      ),
      'description' => t('Verifies that user-entered data ends with a given string.'),
    ),
    'pattern' => array(
      'name' => t('Pattern'),
      'component_types' => array(
        'hidden',
        'textarea',
        'textfield',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Pattern'),
        'description' => t('Specify a pattern where:')
          . theme('item_list', array('items' => array(t('@ = any letter A-Z'), t('# = any numeral 0-9'), t('| = separates two or more acceptable patterns'), t('Any other character must appear in its exact position'))))
          . t('Examples')
          . theme('item_list', array('items' => array(t('North American phone number: (###) ###-####'), t('D-2500 series model numbers: D-25##'), t('UK Postal Code: @# #@@|@## #@@|@@# #@@|@@## #@@|@#@ #@@|@@#@ #@@|GIR0AA')))),
      ),
      'description' => t('Verifies that a user-entered value follows to a specified pattern.'),
    ),
    'regex' => array(
      'name' => t('Regular expression, case-sensitive'),
      'negatable' => TRUE,
      'component_types' => array(
        'email',
        'hidden',
        'number',
        'textarea',
        'textfield',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Regex code (case-sensitive)'),
        'description' => t('Specify regex code to validate the user input against. Do not include delimiters such as /.'),
      ),
      'description' => t('Validates user-entered text against a case-sensitive regular expression.'),
    ),
    'regexi' => array(
      'name' => t('Regular expression, case-insensitive'),
      'negatable' => TRUE,
      'component_types' => array(
        'email',
        'hidden',
        'number',
        'textarea',
        'textfield',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Regex code (case-insensitive)'),
        'description' => t('Specify regex code to validate the user input against. Do not include delimiters such as /.'),
      ),
      'description' => t('Validates user-entered text against a case-insensitive regular expression.'),
    ),
    'must_be_empty' => array(
      'name' => t('Must be empty'),
      'component_types' => array(
        'hidden',
        'number',
        'textarea',
        'textfield',
      ),
      'description' => t('Verifies that a specified textfield remains empty. Recommended use case: used as an anti-spam measure by hiding the element with CSS.'),
    ),
    'blacklist' => array(
      'name' => t('Words blacklist'),
      'negatable' => TRUE,
      'component_types' => array(
        'email',
        'hidden',
        'textarea',
        'textfield',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Blacklisted words'),
        'description' => t('Specify illegal words, seperated by commas.'),
      ),
      'description' => t('Validates that user-entered data doesn\'t contain any of the specified illegal words.'),
    ),
    'username' => array(
      'name' => t('Must match a username'),
      'negatable' => TRUE,
      'component_types' => array(
        'hidden',
        'textfield',
      ),
      'description' => t('Validates that user-entered data matches a username.'),
    ),
    'valid_url' => array(
      'name' => t('Valid URL'),
      'negatable' => TRUE,
      'component_types' => array(
        'hidden',
        'textfield',
      ),
      'description' => t('Validates that the user-entered data is a valid URL.'),
    ),
  );

  // Only available in Webform 4.
  module_load_include('inc', 'webform', 'components/number');
  if (!function_exists('webform_compare_floats')) {
    unset($validators['sum']);
  }

  if (module_exists('email_verify')) {
    $validators['email_verify'] = array(
      'name' => t('Email Verify'),
      'component_types' => array(
        'email',
      ),
      'description' => t('Verifies that an email address actually exists using the <a href="https://drupal.org/project/email_verify">Email Verification module</a>.'),
    );
  }

  return $validators;
}

/**
 * Implements hook_webform_validation_validate().
 */
function webform_validation_webform_validation_validate($validator_name, $items, $components, $rule) {
  if (!$items) {
    return NULL;
  }

  // For certain validators, if all components to be compared are email
  // components, make the values lower-case to avoid case-sensitive comparison.
  if (in_array($validator_name, array('equal', 'comparison', 'unique'))) {
    $all_email = TRUE;
    foreach ($rule['components'] as $component) {
      if ($component['type'] !== 'email') {
        $all_email = FALSE;
        break;
      }
    }
    if ($all_email) {
      $items = array_map('strtolower', $items);
    }
  }

  // Some components, such as multiple select, send their values as arrays, others don't.
  // Convert all to arrays and write the rules to handle them that way. Remove empty values.
  foreach ($items as $key => $val) {
    $new_values = array();
    foreach ((array) $val as $val_key => $val_val) {
      if ((string) $val_val !== '') {
        $new_values[$val_key] = $val_val;
      }
    }
    $items[$key] = $new_values;
  }
  // Ensure later calls to key() get the first item.
  reset($items);

  $errors = array();
  switch ($validator_name) {
    case 'numeric':
      $num_range = _webform_numeric_check_data($rule['data']);
      foreach ($items as $key => $val) {
        foreach ($val as $subval) {
          // first check if the value is numeric
          if (is_numeric($subval)) {
            $subval = (float) $subval;
          }
          else {
            $errors[$key] = t('%item is not numeric.', array('%item' => $components[$key]['name']));
            continue;
          }

          // now validate the entered numeric value against the validator range settings, if appropriate
          // a. validate min & max
          if (isset($num_range['min']) && isset($num_range['max'])) {
            // validate the min - max range
            if ($subval < $num_range['min'] || $subval > $num_range['max']) {
              $errors[$key] = t('%item is not within the allowed range %range.', array('%item' => $components[$key]['name'], '%range' => str_replace('|' , ' - ', $rule['data'])));
            }
          }
          else {
            // b. validate min
            if (isset($num_range['min'])) {
              if ($subval < $num_range['min']) {
                $errors[$key] = t('%item should be greater than or equal to %val.', array('%item' => $components[$key]['name'], '%val' => $num_range['min']));
              }
            }
            // c. validate max
            if (isset($num_range['max'])) {
              if ($subval > $num_range['max']) {
                $errors[$key] = t('%item should be less than or equal to %val.', array('%item' => $components[$key]['name'], '%val' => $num_range['max']));
              }
            }
          }
        }
      }
      return $errors;
    case 'min_length':
      $min_length = $rule['data'];
      foreach ($items as $key => $val) {
        foreach ($val as $subval) {
          if (drupal_strlen($subval) < $min_length) {
            $errors[$key] = t('%item should be at least %num characters long.', array('%item' => $components[$key]['name'], '%num' => $min_length));
          }
        }
      }
      return $errors;
    case 'max_length':
      $max_length = $rule['data'];
      foreach ($items as $key => $val) {
        foreach ($val as $subval) {
          if (drupal_strlen($subval) > $max_length) {
            $errors[$key] = t('%item should be at most %num characters long.', array('%item' => $components[$key]['name'], '%num' => $max_length));
          }
        }
      }
      return $errors;
    case 'min_words':
      $min_words = $rule['data'];
      foreach ($items as $key => $val) {
        foreach ($val as $subval) {
          if (_webform_validation_count_words($subval) < $min_words) {
            $error = format_plural($min_words, '%item should be at least 1 word long.', '%item should be at least @count words long.', array('%item' => $components[$key]['name']));
            $errors[$key] = $error;
          }
        }
      }
      return $errors;
    case 'max_words':
      $max_words = $rule['data'];
      foreach ($items as $key => $val) {
        foreach ($val as $subval) {
          if (_webform_validation_count_words($subval) > $max_words) {
            $error = format_plural($max_words, '%item should be at most 1 word long.', '%item should be at most @count words long.', array('%item' => $components[$key]['name']));
            $errors[$key] = $error;
          }
        }
      }
      return $errors;
    case 'sum':
      // Get the numbers to sum.
      $sum = array();
      foreach ($items as $item) {
        if (isset($item[0])) {
          $sum[] = $item[0];
        }
      }
      // If none of the components are completed, don't run this validator.
      if (!count($sum)) {
        return array();
      }
      $sum = array_sum($sum);

      // Number being compared with.
      $compare_number = (float) preg_replace('/^[^0-9]+/', '', $rule['data']);

      // Parse the comparision operator and do comparison.
      module_load_include('inc', 'webform', 'components/number');
      $error = FALSE;
      if (substr($rule['data'], 0, 2) === '<=') {
        if (!(webform_compare_floats($sum, $compare_number) <= 0)) {
          $error = t('less than or equal to');
        }
      }
      elseif (substr($rule['data'], 0, 1) === '<') {
        if (!(webform_compare_floats($sum, $compare_number) < 0)) {
          $error = t('less than');
        }
      }
      elseif (substr($rule['data'], 0, 2) === '>=') {
        if (!(webform_compare_floats($sum, $compare_number) >= 0)) {
          $error = t('greater than or equal to');
        }
      }
      elseif (substr($rule['data'], 0, 1) === '>') {
        if (!(webform_compare_floats($sum, $compare_number) > 0)) {
          $error = t('greater than');
        }
      }
      else {
        if (!(webform_compare_floats($sum, $compare_number) === 0)) {
          $error = t('exactly');
        }
      }
      // Set error if needed.
      if ($error) {
        $keys = array_keys($items);
        $errors[$keys[0]] = t('These items must add up to %verb %compare_number:', array('%verb' => $error, '%compare_number' => $compare_number)) . theme('item_list', array('items' => _webform_validation_get_names_of_rule_components($rule)));
      }
      return $errors;
    case 'equal':
      $first_entry_key = key($items);
      $first_entry = array_shift($items);
      foreach ($items as $key => $val) {
        if ($val !== $first_entry) {
          $errors[$key] = t('%item_checked does not match %item_first.', array('%item_checked' => $components[$key]['name'], '%item_first' => $components[$first_entry_key]['name']));
        }
      }
      return $errors;
    case 'comparison':
      foreach (array(1, 2) as $count) {
        $entry[$count]['key'] = key($items);
        $value = array_shift($items);
        if ($components[$entry[$count]['key']]['type'] === 'date') {
          if (!empty($value) && checkdate((int) $value['month'], (int) $value['day'], (int) $value['year'])) {
            $entry[$count]['value'] = date('Y-m-d', mktime(0, 0, 0, (int) $value['month'], (int) $value['day'], (int) $value['year']));
          }
          else {
            $entry[$count]['value'] = NULL;
          }
        }
        elseif ($components[$entry[$count]['key']]['type'] === 'time') {
          $time = $value['hour'] . ':' . $value['minute'];
          if (!empty($value['ampm'])) {
            $time .= ' ' . $value['ampm'];
          }
          $time = strtotime($time);
          if ($time) {
            $entry[$count]['value'] = date('H:i', $time);
          }
          else {
            $entry[$count]['value'] = NULL;
          }
        }
        else {
          $entry[$count]['value'] = _webform_validation_flatten_array($value);
        }
      }

      // Don't validate if either are empty.
      if ((string) $entry[1]['value'] === '' || (string) $entry[2]['value'] === '') {
        return array();
      }

      $error = FALSE;
      switch ($rule['data']) {
        case '>':
          if (!($entry[1]['value'] > $entry[2]['value'])) {
            $error = TRUE;
          }
          break;
        case '>=':
          if (!($entry[1]['value'] >= $entry[2]['value'])) {
            $error = TRUE;
          }
          break;
        case '<':
          if (!($entry[1]['value'] < $entry[2]['value'])) {
            $error = TRUE;
          }
          break;
        case '<=':
          if (!($entry[1]['value'] <= $entry[2]['value'])) {
            $error = TRUE;
          }
          break;
      }

      if ($error) {
        $errors[$entry[2]['key']] = _webform_validation_i18n_error_message($rule);
      }
      return $errors;
    case 'unique':
      foreach ($items as $key => $val) {
        $items[$key] = _webform_validation_flatten_array($val);
      }
      // now we count how many times each value appears, and find out which values appear more than once
      $items_count = array_count_values(array_map('drupal_strtolower', array_map('trim', $items)));
      $doubles = array_filter($items_count, create_function('$x', 'return $x > 1;'));
      foreach ($items as $key => $val) {
        if (in_array(drupal_strtolower($val), array_keys($doubles))) {
          $errors[$key] = t('The value of %item is not unique.', array('%item' => $components[$key]['name']));
        }
      }
      return $errors;
    case 'specific_value':
      $specific_values = explode(',', $rule['data']);
      $specific_values = array_map('trim', $specific_values);
      foreach ($items as $key => $val) {
        // Selects: Fail if at least one checked and at least one not in the allowed values.
        $val = array_filter($val);
        $test = count($val) && count(array_diff($val, $specific_values));
        _webform_validation_test($errors, $key, $rule, $test);
      }
      return $errors;
    case 'default_value':
      foreach ($items as $key => $val) {
        $val = _webform_validation_flatten_array($val);
        $test = $val != $components[$key]['value'];
        _webform_validation_test($errors, $key, $rule, $test);
      }
      return $errors;
    case 'someofseveral':
      // Determine the number of components completed.
      foreach ($items as $key => $val) {
        $items[$key] = _webform_validation_flatten_array($val);
        $items[$key] = (bool) strlen($items[$key]);
      }
      $number_completed = count(array_filter($items));

      // Number being compared with.
      $compare_number = (int) preg_replace('/[^0-9]+/', '', $rule['data']);
      if ($compare_number < 1) {
        $compare_number = 1;
      }
      elseif ($compare_number > count($rule['components'])) {
        $compare_number = count($rule['components']);
      }

      // Parse the comparision operator and do comparison.
      $error = FALSE;
      if (substr($rule['data'], 0, 1) === '=') {
        if (!($number_completed === $compare_number)) {
          $error = t('exactly');
        }
      }
      elseif (substr($rule['data'], 0, 2) === '<=') {
        if (!($number_completed <= $compare_number)) {
          $error = t('at most');
        }
      }
      else {
        if (!($number_completed >= $compare_number)) {
          $error = t('at least');
        }
      }

      // Set error if needed.
      if ($error) {
        $keys = array_keys($items);
        $errors[$keys[0]] = t('You must complete %verb %compare_number of these items:', array('%verb' => $error, '%compare_number' => $compare_number)) . theme('item_list', array('items' => _webform_validation_get_names_of_rule_components($rule)));
      }
      return $errors;
    case 'select_min':
      $min_selections = $rule['data'];
      foreach ($items as $key => $val) {
        if (count(array_filter($val, '_webform_validation_check_false')) < $min_selections) {
          $errors[$key] = t('Please select at least %num options for %item.', array('%num' => $min_selections, '%item' => $components[$key]['name']));
        }
      }
      return $errors;
    case 'select_max':
      $max_selections = $rule['data'];
      foreach ($items as $key => $val) {
        if (count(array_filter($val, '_webform_validation_check_false')) > $max_selections) {
          $errors[$key] = t('Please select maximum %num options for %item.', array('%num' => $max_selections, '%item' => $components[$key]['name']));
        }
      }
      return $errors;
    case 'select_exact':
      $allowed_selections = $rule['data'];
      foreach ($items as $key => $val) {
        $error_strings = array(
          'regular' => 'Please select %num options for %item.',
          'negated' => 'Please do not select %num options for %item.',
        );
        $error_vars = array('%num' => $allowed_selections, '%item' => $components[$key]['name']);
        $test = count(array_filter($val, '_webform_validation_check_false')) != $allowed_selections;
        _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
      }
      return $errors;
    case 'plain_text':
      foreach ($items as $key => $val) {
        $error_strings = array(
          'regular' => '%item only allows the use of plain text.',
          'negated' => '%item must contain HTML tags.',
        );
        $error_vars = array('%item' => $components[$key]['name']);
        foreach ($val as $subval) {
          $test = strcmp($subval, strip_tags($subval));
          _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
        }
      }
      return $errors;
    case 'starts_with':
    case 'ends_with':
      $pattern = preg_quote($rule['data'], '/');
      if ($validator_name === 'starts_with') {
        $pattern = '^' . $pattern;
        $verb = t('start');
      }
      else {
        $pattern .= '$';
        $verb = t('end');
      }
      $pattern = '/' . $pattern . '/';

      foreach ($items as $key => $val) {
        $error_strings = array(
          'regular' => '%item must %verb with "%string".',
          'negated' => '%item must not %verb with "%string".',
        );
        $error_vars = array('%item' => $components[$key]['name'], '%verb' => $verb, '%string' => $rule['data']);
        foreach ($val as $subval) {
          $test = !preg_match($pattern, $subval);
          _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
        }
      }
      return $errors;
    case 'pattern':
      $pattern = preg_quote($rule['data'], '/');
      $pattern = str_replace('@', '[a-zA-Z]', $pattern);
      $pattern = str_replace('#', '[0-9]', $pattern);
      $pattern = '(' . $pattern . ')';
      // Un-escape "|" operator.
      $pattern = preg_replace('/(\\s*)(\\\\)(\\|)(\\s*)/', ')|(', $pattern);
      foreach ($items as $key => $val) {
        foreach ($val as $subval) {
          $test = !preg_match('/^(' . $pattern . ')$/', $subval);
          _webform_validation_test($errors, $key, $rule, $test);
        }
      }
      return $errors;
    case 'regex':
    case 'regexi':
      mb_regex_encoding('UTF-8');
      $regex = $rule['data'];
      foreach ($items as $key => $val) {
        foreach ($val as $subval) {
          if ($validator_name === 'regexi') {
            $match = (bool) mb_eregi($regex, $subval);
          }
          else {
            $match = (bool) mb_ereg($regex, $subval);
          }
          $test = !$match;
          _webform_validation_test($errors, $key, $rule, $test);
        }
      }
      return $errors;
    case 'must_be_empty':
      foreach ($items as $key => $val) {
        if (count($val) !== 0) {
          $errors[$key] = t('%item does not contain the correct data.', array('%item' => $components[$key]['name']));
        }
      }
      return $errors;
    case 'blacklist':
      $blacklist = preg_quote($rule['data'], '/');
      $blacklist = explode(',', $blacklist);
      $blacklist = array_map('trim', $blacklist);
      $blacklist = '/\b(' . implode('|', $blacklist) . ')\b/i';
      foreach ($items as $key => $val) {
        foreach ($val as $subval) {
          $test = preg_match($blacklist, $subval);
          _webform_validation_test($errors, $key, $rule, $test);
        }
      }
      return $errors;
    case 'username':
      foreach ($items as $key => $val) {
        $error_strings = array(
          'regular' => 'The %item field does not match an active username.',
          'negated' => 'The %item field matches an active username.',
        );
        $error_vars = array('%item' => $components[$key]['name']);
        foreach ($val as $subval) {
          $test = !db_query_range('SELECT 1 FROM {users} WHERE name = :username AND status = 1', 0, 1, array(':username' => $subval))->fetchField();
          _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
        }
      }
      return $errors;
    case 'valid_url':
      foreach ($items as $key => $val) {
        $error_strings = array(
          'regular' => '%item does not appear to be a valid URL.',
          'negated' => '%item must not be a valid URL.',
        );
        $error_vars = array('%item' => $components[$key]['name']);
        foreach ($val as $subval) {
          $test = !valid_url($subval, TRUE);
          _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
        }
      }
      return $errors;
    case 'email_verify':
      if (module_exists('email_verify')) {
        foreach ($items as $key => $val) {
          foreach ($val as $subval) {
            $error = email_verify_check($subval);
            if ($error) {
              $errors[$key] = $error;
            }
          }
        }
      }
      return $errors;
  }
}

/**
 * Return an array of the names of the components in a validation rule.
 *
 * @param $rule array
 *   Array of information about a validation rule.
 *
 * @return array
 *   Array of the filtered names of the components in $rule.
 */
function _webform_validation_get_names_of_rule_components(array $rule) {
  $names = array();
  foreach ($rule['components'] as $component) {
    $names[] = _webform_filter_xss($component['name']);
  }
  return $names;
}

/**
 * Helper function to negate validation rules as needed and create the correct error message.
 */
function _webform_validation_test(&$errors, $key, $rule, $test, array $error_strings = NULL, array $error_vars = NULL) {
  $rule['negate'] = !empty($rule['negate']);
  if ($rule['negate']) {
    $test = !$test;
  }
  if ($test) {
    if ($error_strings) {
      $error = t($error_strings[$rule['negate'] ? 'negated' : 'regular'], $error_vars);
    }
    else {
      $error = _webform_validation_i18n_error_message($rule);
    }
    $errors[$key] = $error;
  }
}

/**
 * Count the number of words in a value.
 *
 * Strip HTML first.
 *
 * @param string|array $val
 *   A string or array of strings in which to count words.
 *
 * @return int
 *   The number of words in the input.
 */
function _webform_validation_count_words($val) {
  $val = _webform_validation_flatten_array($val);

  // Strip any HTML tags so they're not counted in the word count.
  $val = strip_tags($val);
  // Convert character entities back to characters. Without this, entities for
  // whitespace characters would not be counted as word boundaries.
  $val = html_entity_decode($val);

  return count(preg_split('/[[:space:]\xC2\xA0]+/', $val));
}

/**
 * Helper function to deal with submitted values that are arrays (for example, multiple select component).
 * We flatten the array as a comma-separated list to do the comparison.
 */
function _webform_validation_flatten_array($val) {
  if (is_array($val)) {
    $arr = array_filter($val, '_webform_validation_check_false');
    return implode(',', $arr);
  }
  return $val;
}

/**
 * Get a list of validator definitions.
 *
 * @return
 *   Array of information about validators.
 */
function webform_validation_get_validators() {
  $validators = module_invoke_all('webform_validation_validators');
  // Let modules use hook_webform_validator_alter($validators) to change validator settings.
  drupal_alter('webform_validator', $validators);

  // Remove entries for which only partial information exists.
  foreach ($validators as $validator_key => $validator_info) {
    if (!isset($validator_info['name']) || !isset($validator_info['component_types'])) {
      unset($validators[$validator_key]);
    }
  }

  return $validators;
}

/**
 * Return an array of the names of the validators.
 *
 * @return array
 *   Array of with keys being validator IDs and values validator names.
 */
function webform_validation_get_validators_selection() {
  $selection = array();
  $validators = webform_validation_get_validators();
  if ($validators) {
    foreach ($validators as $validator_key => $validator_info) {
      $selection[$validator_key] = $validator_info['name'];
    }
  }
  return $selection;
}

/**
 * Get a list of valid component types per validator, as defined via hook_webform_validation_validators().
 * If 'all' is specified, all available component types will be returned.
 */
function webform_validation_valid_component_types($validator) {
  $validators = webform_validation_get_validators();
  if ($info = $validators[$validator]) {
    $allowed_types = $info['component_types'];
    if (in_array('all', $allowed_types, TRUE)) {
      return array_keys(webform_components());
    }
    return $info['component_types'];
  }
}

/**
 * Return information about a specified validator.
 *
 * @param $validator_key string
 *   The key of the validator to return information about.
 *
 * @return array
 *   Array of information about the validator.
 */
function webform_validation_get_validator_info($validator_key) {
  $validators = webform_validation_get_validators();
  return $validators[$validator_key];
}

/**
 * Handle translatable error messages, if available
 */
function _webform_validation_i18n_error_message($rule) {
  $rule['error_message'] = filter_xss($rule['error_message']);
  if (module_exists('i18n')) {
    return i18n_string('webform_validation:error_message:' . $rule['ruleid'] . ':message', $rule['error_message']);
  }
  return $rule['error_message'];
}

/**
 * Helper function used by array_filter() to determine if a value is empty.
 *
 * This is used in place of empty() because string '0' needs to be considered
 * not empty and return FALSE.
 *
 * @param mixed $var
 *   The value to check.
 *
 * @return bool
 *   TRUE if $var is not one of FALSE, int 0, or empty string; FALSE otherwise.
 *
 * @see https://www.drupal.org/node/886458
 * @see https://www.drupal.org/node/2638172
 */
function _webform_validation_check_false($var) {
  return $var !== FALSE && $var !== 0 && $var !== '';
}

/**
 * Process the numeric value validation range that was provided in the numeric validator options
 */
function _webform_numeric_check_data($data) {
  $range = array('min' => NULL, 'max' => NULL);
  // if no value was specified, don't validate
  if ($data == '') {
    return $range;
  }

  // If only one numeric value was specified, this is the min value
  if (is_numeric($data)) {
    $range['min'] = (float) $data;
  }

  if (strpos($data, '|') !== FALSE) {
    list($min, $max) = explode('|', $data);
    if ($min != '' && is_numeric($min)) {
      $range['min'] = (float) $min;
    }
    if ($max != '' && is_numeric($max)) {
      $range['max'] = (float) $max;
    }
  }
  return $range;
}
