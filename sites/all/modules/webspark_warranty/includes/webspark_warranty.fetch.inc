<?php

/**
 * webspark_warranty_get_warranty_status() - Compares all installed modules to
 *                                           all warranty-covered modules and
 *                                           returns whether not discrepancies exist
 *
 * @return $status - String that is either 'True' or 'False' depending on the
 *                   warranty status
 */
function webspark_warranty_get_warranty_status()
{
  $status = true;

  $unsupportedmodules = webspark_warranty_get_unsupported_modules();

  if (sizeof($unsupportedmodules) > 0)
  {
    $status = FALSE;
  }

  return $status ? 'True' : 'False';
}

/**
 * webspark_warranty_get_unsupported_modules() - Gets all modules installed that
 *                                               are not covered in the Webspark
 *                                               Warranty
 *
 * @return $unsupportedmodules - Array of names of all unsupported modules
 *                               installed
 */
function webspark_warranty_get_unsupported_modules()
{
  $installedModules = webspark_warranty_get_installed_modules();
  $supportedModules = webspark_warranty_get_warranty_modules();

  $unsupportedmodules = arrayRecursiveDiff($installedModules, $supportedModules);

  return $unsupportedmodules;
}

/**
 * webspark_warranty_get_installed_modules() - Uses Drupal's Database API to get
                                              all of the modules currently installed
 *                                            on the site (which resides within
 *                                            the {system} table)
 *
 * @return $allModulesArr - All installed modules in a flattened array
 */
function webspark_warranty_get_installed_modules()
{
  // All installed modules output as a flat array with Standard Class Objects
  $allModulesStd = db_select('system', 's')
    ->fields('s', array('name', 'type'))
    ->condition('status', '1')
    ->execute()
    ->fetchAll();

  // Converts from Standard Class Objects to an associative array
  $allModulesArr = json_decode(json_encode($allModulesStd), true);

  return $allModulesArr;
}

/**
 * webspark_warranty_get_warranty_modules() - Imports all warranty-covered module
 *                                            names listed within a JSON file and
 *                                            puts them all into one PHP associative array
 *
 * @return $warrantyModulesArr - All modules covered under Webspark's warranty
 *                               in a flattened array
 */
function webspark_warranty_get_warranty_modules()
{
  $warrantyModulesJSON = file_get_contents(drupal_get_path('module', 'webspark_warranty') .
                                            "/assets/standardModuleList.json", true);
  $warrantyModulesArr = json_decode($warrantyModulesJSON, true);

  return $warrantyModulesArr;
}
