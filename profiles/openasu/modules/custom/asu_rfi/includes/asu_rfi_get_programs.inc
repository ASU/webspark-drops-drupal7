<?php

function asu_rfi_get_programs()
{

  $url = "asuonline.asu.edu/lead-submissions-v3.3/programs";
  $curl = curl_init();
  curl_setopt_array($curl, array(
    CURLOPT_URL => $url,
    CURLOPT_HEADER => true,
    CURLOPT_SSLVERSION => 5,
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
      watchdog('asu_rfi', 'The ASUOnline API is returning a status code of ' . $code[1]);
    }
  }

  if (!isset($data)) {
    watchdog('asu_rfi', 'Failed to utilize the Get Programs API');
  }
  return false;
}

function asu_rfi_check_programs()
{
  $programs = variable_get('asu_rfi_cached_programs');
  $timestamp = variable_get('asu_rfi_cached_programs_timestamp');
  $now = time();

  if (!isset($programs) || !isset($timestamp) || $now - $timestamp > 86400 || strlen($programs) < 25) {
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
