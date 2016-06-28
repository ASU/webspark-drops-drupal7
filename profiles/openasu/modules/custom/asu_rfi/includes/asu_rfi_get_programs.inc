<?php

function asu_rfi_get_programs()
{
  $options = array(
    'method' => 'GET',
    'timeout' => 15,
    'headers' => array('Content-type' => 'application/json', 'Accept' => 'application/json'),
  );

  $response = drupal_http_request('https://asuonline.asu.edu/lead-submissions-v3/programs', $options);

  if (isset($response) && $response->code >= 200 && $response->code < 300) {
    $data = $response->data;
    return $data;
  } else {
    watchdog('asu_rfi', 'Failed to utilize the Get Programs API');
    return false;
  }
}

function asu_rfi_check_programs()
{
  $programs = variable_get('asu_rfi_cached_programs');
  $timestamp = variable_get('asu_rfi_cached_programs_timestamp');
  $now = time();

  if (!isset($programs) || !isset($timestamp) || $now - $timestamp > 86400) {
    $getPrograms = asu_rfi_get_programs();
    if ($getPrograms == false) {
      watchdog('asu_rfi', 'Failed to set the cached Online Programs');
      return false;
    }
    variable_set('asu_rfi_cached_programs', $getPrograms);
    variable_set('asu_rfi_cached_programs_timestamp', $now);
    return true;
  }
  return false;

}

function asu_rfi_parse_programs()
{
  $programString = variable_get('asu_rfi_cached_programs');

  if (isset($programString)) {
    $programs = json_decode($programString);

    return $programs;

  } else {

    watchdog('asu_rfi', 'Attempted to parse the list of online programs, but this list does not exist.');
    return FALSE;
  }
}