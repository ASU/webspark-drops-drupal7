<?php

/**
 * @file
 * Hooks provided by the Commerce File module.
 */

/**
 * Lets modules prevent the download of a file.
 *
 * Returning FALSE will cause the commerce_file formatter to show the file
 * without the download link and the download callback to return
 * "Access denied".
 *
 * @param $license
 *   The license entity.
 * @param $file
 *   The file entity.
 * @param $account
 *   The user to check for.
 *
 * @see commerce_file_can_delete().
 */
function hook_commerce_file_can_download($license, $file, $account) {
  if ($account->name == 'john') {
    // We don't like you, John.
    return FALSE;
  }
  else {
    return TRUE;
  }
}

/**
 * Lets modules change how the file's download limit is determined.
 *
 * @param $license
 *   The license entity.
 * @param $file
 *   The file entity.
 * @param $account
 *   The user to check for.
 *
 * @return
 *   $download_limit as an integer.
 */
function hook_commerce_file_get_download_limit($license, $file, $account) {
  $download_limit = 20;

  return $download_limit;
}
