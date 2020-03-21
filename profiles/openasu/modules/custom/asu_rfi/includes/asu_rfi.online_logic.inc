<?php

/**
 * Is the program managed by Online folks? (i.e. not "asu")
 * @param $program
 * @param $getProgramsList
 * @return bool
 */
function _asu_rfi_check_managed_online($program, $getProgramsList) {
  foreach ($getProgramsList as $onlineItem){
    if ($onlineItem->plancode == $program && $onlineItem->crmdestination !== "asu") {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Compares the degree feed programs listed with online availability, using the
 * cached Get Programs API list.
 * @param string $programsFromDegreeFeed The current program
 * @param array $getProgramsAPIList The cached list of programs currently available with ASU Online. Cached Daily
 * @return boolean $available True False value determining whether it can be handled by ASU Online.
 */
function _asu_rfi_check_program_online_availability($programsFromDegreeFeed, $getProgramsAPIList) {
  $available = FALSE;
  if ($getProgramsAPIList !== FALSE) {
    foreach ($getProgramsAPIList as $item) {
      if ($programsFromDegreeFeed == $item->plancode) {
        $available = TRUE;
      }
    }
  }
  return $available;
}

/**
 * Alter submission_data for online campus submissions.
 *
 * -- NOT A drupal_alter()!
 *
 * @param $type - undergrad or graduate
 * @param $default - $submission_data
 * @param $server - Server data (including type)
 * @param $college_code - College code
 * @param $enterpriseclientid - Google Analytics code
 * @param $nid - Node ID
 * @param string $form_mode - test mode or no?
 * @return array - Revised list of fields for EdPlus consumption
 */
function _asu_rfi_online_fields_alter($type, $default, $server, $college_code, $enterpriseclientid, $nid, $form_mode) {
  if ($type === ASU_RFI_PROSPECT_LEVEL_UNDERGRAD) {
    return array(
      'first_name' => $default['first_name'],
      'last_name' => $default['last_name'],
      'program' => $college_code . '-' . $default['program'],
      'email' => $default['email'],
      'phone' => $default['phone'],
      'prod_test_flag' => $default['prod_test_flag'],
      'base_url' => $server['domain'],
      'origin_uri' => $server['domain'] . '/' . request_path(),
      'remote_nid' => $nid,
      'ldetect_v' => $server['ipAddress'],
      'campaign' => $server['source'],
      'sourceid' => $nid, // Overwritten with API key in Middleware.
      'enterpriseclientid' => $enterpriseclientid,
    );
  }
  elseif ($type === ASU_RFI_PROSPECT_LEVEL_GRAD) {
    return array(
      'first_name' => $default['firstName'],
      'last_name' => $default['lastName'],
      'program' => $college_code . '-' . $default['poiCode'],
      'email' => $default['emailAddress'],
      'phone' => $default['phoneNumber'],
      'prod_test_flag' => $form_mode,  // UPDATE + Verify availability
      'base_url' => $server['domain'],
      'origin_uri' => $server['domain'] . '/' . request_path(),
      'remote_nid' => $nid,
      'ldetect_v' => $server['ipAddress'],
      'campaign' => $server['source'],
      'sourceid' => $nid, // Overwritten with API key in Middleware.
      'enterpriseclientid' => $enterpriseclientid,
    );
  }
}
