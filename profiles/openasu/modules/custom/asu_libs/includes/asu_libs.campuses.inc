<?php

/**
 * Returns correct campusID string for Salesforce compatibility
 *
 * @param $campus - Human-readable campus name (or PeopleSoft/Salesforce IDs if $reverse)
 * @param $reverse - Reverse the keys + values in return (defaults to FALSE)
 * @return string - The campus code (or human name, if $reverse). Returns empty string if no match is found.
 * @TODO pull in from feed to stay up to date
 */
function asu_libs_get_campus_codes($campus, $reverse = FALSE) {
  // Legacy code conversion
  if ($campus === "TMPE") { $campus = 'TEMPE'; }
  if ($campus === "DOWNTOWN") { $campus = 'DTPHX'; }

  $campuses = array(
    "Tempe" => 'TEMPE',
    "Downtown" => "DTPHX",
    "Online" => "ONLNE",
    "Polytechnic" => "POLY",
    "West" => "WEST",
    'ASU@Cochise' => 'COCHS',
    'ASU@Lake Havasu' => 'CALHC',
    'ASU@Los Angeles' => 'LOSAN',
    'ASU@MexicoCity' => 'MXCTY',
    'ASU@Northeastern Arizona' => 'NEAZ',
    'ASU@Pima' => 'PIMA',
    'ASU@Pinal' => 'CAC',
    'ASU@The Gila Valley' => 'EAC',
    'ASU@Tucson' => 'TUCSN',
    'ASU@Washington, D.C.' => 'WASHD',
    'ASU@Yavapai' => 'YAVAP',
    'ASU@Yuma' => 'AWC',
  );
  // Flip campus keys + values if desired
  if ($reverse === TRUE) {
    $campuses = array_flip($campuses);
  }
  foreach ($campuses as $key => $value) {
    if (stristr($key, $campus) !== FALSE) {
      return $value;
      break;
    }
  }
  return '';
}
