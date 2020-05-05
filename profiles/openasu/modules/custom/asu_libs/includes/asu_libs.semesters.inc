<?php

/**
 * Get semester code for right now
 *
 * @param int $month - 1, 11
 * @param int $day - 1-31
 * @param bool $summer - Check for summer semester. Defaults to false.
 * @return int - Semester codes. 1 = Spring, 4 = Summer, 7 = Fall
 */
function asu_libs_get_current_semester($month, $day, $summer = FALSE) {
  if (($month >= 8)) { // FALL (8/15 and forward)
    if (($month !== 8) || ($month === 8 && $day > 14)) {
      return '7'; // FALL
    }
  }
  else { // Spring OR summer (before 8/15)
    if ($summer) {
      if (($month === 5 && $day > 14) || ($month === 8 && $day <= 14)) {
        return '4'; // SUMMER
      }
    } else {
      return '1'; // SPRING
    }
  }
  return 'unknown'; // No semester?
}

/**
 * Get human readable name of semester from code
 *
 * @param $code - one digit code for semester
 * @return bool|string - Human readable semester name or FALSE is no matches
 */
function asu_libs_semester_digits_to_text($code) {
  $semesters = asu_libs_get_semester_digits(TRUE);
  $code = (int) $code;
  foreach ($semesters as $digit => $semester_name) {
    if ($code === (int) $digit) {
      return $semester_name;
      break;
    }
  }
  return "InvalidSemester";
}

/**
 * Get Semester PeopleSoft codes + human-readable names
 *
 * @param bool $summer
 * @return array list of semester names + PeopleSoft codes
 */
function asu_libs_get_semester_digits($summer = FALSE) {
  $semesters = array(
    '1' => "Spring",
  );
  if ($summer) {
    $semesters['4'] = "Summer";
  }
  $semesters['7'] = "Fall";
  return $semesters;
}

/**
 * Create upcoming 4-digit semester codes and map to human readable semester names
 *
 * @param bool $summer - Include summer semester
 * @param string $key_type - Return either peopleSoft codes (ps) or 4-digit codes (digits). Defaults to 'digits'.
 * @param array $all_avail_terms - All terms (PS codes => human readable names)
 * @param int $addl_years - Number of additional years to create drop down options
 * @return array - All 4-digit (Or PS) semester codes (key) (ex. 1) => human-readable counterparts (Ex. Fall 2020)
 */
function asu_libs_get_sem_codes_human_mapping($summer, $all_avail_terms, $key_type = 'digits', $addl_years = 2) {
  $options = &drupal_static(__FUNCTION__);
  if (!isset($options)) {
    // 1) Build the date array
    $semester = asu_libs_get_semester_digits($summer);
    $semester_today = asu_libs_get_current_semester(date('m'), date('d'), $summer);

    // 2) Generate semester digits from semLabel field
    $addl_years++; // <= years + 1
    $date = $new = $options = array();
    $year = (int)date('Y');
    for ($i = 0; $i <= $addl_years; $i++) {
      $date[$i] = $year + $i;
      $new[$i] = substr_replace(($date[$i]), "", 1, 1);
      if ($i === 0) {  // Current year (nothing sent in fall semester)
        if ($semester_today !== '7') { // Before fall start
          if ($summer && $semester_today === '1') { // Spring time and summer included
            $human_term = ($date[$i]) . " " . $semester['4'];  // YYYY Summer
            $key = ($key_type === 'ps')
              ? asu_libs_get_ps_sem_code_key($human_term, $all_avail_terms)
              : ($new[$i]) . '4';
            $options[$key] = $human_term;
          }
          $human_term = ($date[$i]) . " " . $semester['7']; // YYYY Fall
          $key = ($key_type === 'ps')
            ? asu_libs_get_ps_sem_code_key($human_term, $all_avail_terms)
            : ($new[$i]) . '7';
          $options[$key] = $human_term;
        }
      } else { // Future years
        $human_term = ($date[$i]) . " " . $semester["1"]; // YYYY Spring
        $future_key = ($key_type === 'ps')
          ? asu_libs_get_ps_sem_code_key($human_term, $all_avail_terms)
          : ($new[$i]) . "1";  // append 1 to the key depending on the season. For spring, add 1.
        $options[$future_key] = $human_term;
        if ($summer) {
          $human_term = ($date[$i]) . " " . $semester['4'];
          $future_key = ($key_type === 'ps')
            ? asu_libs_get_ps_sem_code_key($human_term, $all_avail_terms)
            : ($new[$i]) . "4";
          $options[$future_key] = $human_term;
        }
        $human_term = ($date[$i]) . " " . $semester['7'];
        $future_key = ($key_type === 'ps')
          ? asu_libs_get_ps_sem_code_key($human_term, $all_avail_terms)
          : ($new[$i]) . "7";
        $options[$future_key] = $human_term;
      }
    }
  }
  return $options;
}

/**
 * Select PS code for the term from available options
 *
 * @param $term - Human readable term
 * @param $available_terms - All available terms
 * @return string
 */
function asu_libs_get_ps_sem_code_key($term, $available_terms) {
  $key = array_search($term, $available_terms);
  if ($key !== FALSE) {
    return $key;
  } else {
//    watchdog('asu_rfi', 'No matching PeopleSoft term for @term. Consider running cron to ensure that your'
//      . ' locally stored available start terms are up-to-date.', array('@term' => $term), WATCHDOG_WARNING);
    return FALSE;
  }
}
