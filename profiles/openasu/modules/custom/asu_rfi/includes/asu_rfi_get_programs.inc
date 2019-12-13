<?php

/**
 * Get asuonline.asu.edu programs from feed
 * @return mixed|bool
 */
function asu_rfi_import_online_programs() {
  $url = "https://asuonline.asu.edu/lead-submissions-v3.3/programs";
  $curl = curl_init();
  curl_setopt_array($curl, array(
    CURLOPT_URL => $url,
    CURLOPT_HEADER => true,
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_HTTPHEADER => array('Accept: application/json')
  ));

  $header = explode("\n", curl_exec($curl));
  curl_close($curl);

  if (!empty($header) && !empty($header[0])) {
    $code = explode(" ", $header[0]);
    $finalHeader = count($header) - 1;
    if (isset($code[1]) && $code[1] >= 200 && $code[1] < 400) {
      if (isset($header[$finalHeader]) && !empty($header[$finalHeader])) {
        $data = $header[$finalHeader];
        return $data;
      }
    } else {
      watchdog('asu_rfi', __FUNCTION__ . ' -- The ASUOnline programs list at ' . $url
        . ' is returning status code @code.',
        array('@code' => $code[1]), WATCHDOG_NOTICE);
    }
  }
  if (!isset($data)) {
    watchdog('asu_rfi', __FUNCTION__ . ' -- Failed to pull online programs from ' . $url, array(),
    WATCHDOG_ERROR);
  }
  return false;
}

/**
 *  Re-pull programs from asuonline.asu.edu under certain circumstances
 * @return bool
 */
function asu_rfi_check_cached_programs() {
  $programs = variable_get('asu_rfi_cached_programs');
  $timestamp = variable_get('asu_rfi_cached_programs_timestamp');
  $now = time();

  if (!isset($programs) || !isset($timestamp) || $now - $timestamp > ASU_RFI_STALE_TIME_DEFAULT || strlen($programs) < 25) {
    // Re-pull and update programs
    $getPrograms = asu_rfi_import_online_programs();
    if ($getPrograms == false) {
      watchdog('asu_rfi', __FUNCTION__ . ' -- Failed to import set
      Online programs cache.',
        array(), WATCHDOG_ERROR);
      return false;
    }
    variable_set('asu_rfi_cached_programs', $getPrograms);
    variable_set('asu_rfi_cached_programs_timestamp', $now);
    return true;
  }
  return false;
}

/**
 * Parse JSON list of programs previously pulled in and cached in asu_rfi_cached_programs
 * @return mixed
 */
function _asu_rfi_parse_programs() {
  $programs = &drupal_static(__FUNCTION__);
  if (!isset($programs)) {
    $programString = variable_get('asu_rfi_cached_programs');
    if (isset($programString)) {
      $programs = json_decode($programString);
      if ($programs == NULL) {
        watchdog('asu_rfi', __FUNCTION__ . ' -- The cached JSON of
        programs cannot be parsed.', array(), WATCHDOG_ERROR);
        return FALSE;
      }
    }
    else {
      watchdog('asu_rfi', __FUNCTION__ . ' -- Cannot find cached JSON
      list of programs to parse.', array(), WATCHDOG_ERROR);
      return FALSE;
    }
  }
  return $programs;
}
