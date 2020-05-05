<?php

/**
 * Validation - ZIP Codes
 *
 * @param string $country - Human-readable name
 * @param integer $zip - ZIP Code
 * @param boolean $us_long_allowed - Accept XXXXX-XXXX digit codes for the United States. Defaults to FALSE.
 * @param string $zip_field_name - Drupal Form API key for this field. Defaults to 'zipcode'.
 */
function asu_libs_validate_zipcode($country, $zip, $us_long_allowed = FALSE, $zip_field_name = 'zipcode') {
  module_load_include('inc', 'asu_libs', 'includes/asu_libs.countries');
  if ($country == "United States") {
    if ((strlen($zip) < 5)) {
      form_set_error($zip_field_name, t('Domestic postal/ZIP codes cannot be less than 5 digits.'));
    }
    $zip_pattern = ($us_long_allowed === TRUE) ? '/^\d{5}(-\d{4})?$/' : '/^\d{5}$/';
    $zip_pattern_error = ($us_long_allowed === TRUE) ? ' (or 12345-6789)' : '';
    if (!preg_match($zip_pattern, $zip)) {
      form_set_error($zip_field_name, t('US Postal/ZIP codes may only be formatted like 12345' . $zip_pattern_error . '.'));
    }
  } else {
    if (!preg_match("/^[a-zA-Z0-9\s-]+$/", $zip)) {
      form_set_error($zip_field_name, t('Postal code is not valid (contains invalid characters - numbers, letters, or dashes only)'));
    }
    if ((strlen($zip) < 4)) {
      form_set_error($zip_field_name, t('International postal codes cannot be less than 4 characters.'));
    }
    if (strlen($zip) > 20) {
      form_set_error($zip_field_name, t('International postal codes cannot be longer than 20 characters.'));
    }
  }
}

/**
 * Validation - Birthdate
 * @param string $birthdate - Formatted birthday m(required_delimiter)d(required_delimiter)yyyy
 * @param string $birth_field_name - Drupal Form API key for birth date field. Defaults to 'birthdate'.
 * @param string $required_delimiter - Use when a non-slash delimiter is required. Only options are the dot ., or dash (-). Defaults to slash.
 * @param boolean $leading_zeroes - Require zeroes in front of day and month for days and months 109. Defaults to FALSE.
 * @param string $module - Name of module for better error reporting, if desired. Defaults to asu_dirs.
 */
function asu_libs_validate_birthdate($birthdate, $birth_field_name = 'birthdate', $required_delimiter = '/', $leading_zeroes = FALSE, $module = 'asu_dirs') {
  if (($required_delimiter !== '/')) {
    $required_delimiter = (preg_match('|^[\-/.]$|', $required_delimiter, $matches));
    if ($required_delimiter !== 1) {
      watchdog($module, '@field is trying to use an invalid delimiter (@delimiter).',
        array('@field' => $birth_field_name, '@delimiter' => $required_delimiter), WATCHDOG_ERROR);
      form_set_error($birth_field_name, 'The ' . $birth_field_name . ' field is incorrectly configured. Please contact'
        . ' your site administrator about this error.');
    } else {
      $required_delimiter = $matches[0];
    }
  } else {
    $required_delimiter = '/';
  }
  $error_month = 'm';
  $error_day = 'd';
  if ($leading_zeroes === TRUE) {
    $zero_pattern = '[0]?';
    $error_month .= 'm';
    $error_day .= 'd';
  } else {
    $zero_pattern = '';
  }

  // get number of occurrences of $delimiter in the DOB
  $delimiter_count = substr_count($birthdate, $required_delimiter);
  $default_error_message = t('Date of birth accepts the format ' . $error_month . $required_delimiter . $error_day . $required_delimiter . 'yyyy'
    . ' (Ex. 3' . $required_delimiter . '28' . $required_delimiter . '2000)');

  if ($delimiter_count == 2) {
    $date_format = explode($required_delimiter, $birthdate);
    $month = $date_format[0];
    $day = $date_format[1];
    $year = $date_format[2];
    $current_year = date('Y');
    $year_limit = $current_year - 1;
    $isLeapYear = date('L');

    if (strlen($birthdate) < 11) {
      if (($month < 1) || ($month > 12)) {
        form_set_error($birth_field_name, t('Month range has to be between 1 and 12.'));
      }

      if (($month == 1) || ($month == 3) || ($month == 5) || ($month == 7) || ($month == 8) || ($month == 10) || ($month == 12)) {
        if (($day < 1) || ($day > 31)) {
          form_set_error($birth_field_name, t('Day range has to be between 1 and 31.'));
        }
      }

      if (($month == 4) || ($month == 6) || ($month == 9) || ($month == 11)) {
        if (($day < 1) || ($day > 30)) {
          form_set_error($birth_field_name, t('Day range has to be between 1 and 30.'));
        }
      }
      if ($month == 2) { // February checks
        if ($isLeapYear == 1) {
          if (($day < 1) || ($day > 29)) {
            form_set_error($birth_field_name, t('Day range has to be between 1 and 29.'));
          }
        }
        if ($isLeapYear == 0) {
          if (($day < 1) || ($day > 28)) {
            form_set_error($birth_field_name, t('Day range has to be between 1 and 28.'));
          }
        }
      }
      if (strlen($year) !== 4) {
        form_set_error($birth_field_name, t('Birth year must be 4 digits.'));
      }
      if ($year > $year_limit) {
        form_set_error($birth_field_name, t('Year cannot be greater than ' . $year_limit));
      }

      // Main date check
      $pattern = '@^(' . $zero_pattern . '[1-9]|1[012])' . $required_delimiter . '(' . $zero_pattern
        . '[1-9]|[12][0-9]|3[01])' . $required_delimiter . '(19|20)\d\d$@';
      if (!preg_match($pattern, $birthdate)) {
        form_set_error($birth_field_name, $default_error_message);
      }
    } else {
      form_set_error($birth_field_name, $default_error_message);
    }
  } else {
    form_set_error($birth_field_name, $default_error_message);
  }
}

/**
 * Validation - Email
 *
 * @param string $email - Email address to test.
 * @param string $email_field_name - Alternate Form API key for this field. Defaults to 'email'.
 * @return mixed|string
 */
function asu_libs_validate_email($email, $email_field_name = 'email') {
  if (!empty($email)) {
    if (!preg_match("/^([a-zA-Z0-9])+([a-zA-Z0-9._-])*@([a-zA-Z0-9_-])+([a-zA-Z0-9._-]+)*(\.[a-zA-Z]{2,6})+$/", $email)) {
      form_set_error($email_field_name, t('You entered an invalid email address.'));
    }
  } else {
    form_set_error($email_field_name, 'You need to enter an email address.');
  }
}

/**
 *  * Validation - Phone number
 *
 * @param string $phone - Phone number to validate. Defaults to empty (skip).
 * @param boolean $return_phone - Return revised/formatted phone number. Defaults to FALSE.
 * @param string $phone_field_name - Alternate Form API key for this field. Defaults to 'phone'
 * @return mixed|string - Return revised number IF return_phone is TRUS
 */
function asu_libs_validate_phone($phone, $return_phone = FALSE, $phone_field_name = 'phone') {
  /** If mobile number field is checked, then check for USA format, else check for special characters **/
  if (!empty($phone)) {
    if (strpos($phone, '011', 0) === 0) { // swap out old '011' with +
      $phone = preg_replace('|^011[-\s.]?([^-\s.])(.+?)$|', "+$1$2", $phone);
    } elseif (strpos($phone, '1', 0) === 0) { // Leading 1 removal for domestic numbers
      $phone = preg_replace('|^1[-\s.]?([^-\s.])(.+?)$|', "$1$2", $phone);
    }
    if (!preg_match("/^([+]?)([(]?[0-9]{3}[)]?)([-\s.]?)([0-9]{3})([-\s.]?)([0-9]{4,6})$/im", $phone, $matches)) {
      form_set_error($phone_field_name, t('You entered an invalid Phone number. See its field description for acceptable formats/examples.'));
    } else {
      if ($return_phone === TRUE) { // Return formatted number for domestic numbers (or do nothing)
        return asu_libs_process_phone_number($matches);
      }
    }
  }
}

/**
 * Reformat phone number for Salesforce IF domestic number. (All others not altered here.)
 *
 * @param array $matches - preg_match output
 * @return mixed|string - Phone number string, depending on locale. (XXX) XXX-XXXX for domestic.
 */
function asu_libs_process_phone_number($matches) {
  if ($matches[1] === '+' || strpos($matches[2], '0') === 0) { // Int'l number - leave alone
    return $matches[0];
  } else {
    if (strpos($matches[2], '(', 0) === 0 && strpos($matches[2], ')', 0) === 4){ // Domestic number with parens already
      return $matches[2] . ' ' . $matches[4] . '-' . $matches[6];
    } else { // Default: Domestic (xxx) xxx-xxxx
      return '(' . $matches[2] . ') ' . $matches[4] . '-' . $matches[6];
    }
  }
}
