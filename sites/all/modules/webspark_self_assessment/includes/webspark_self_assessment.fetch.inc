<?php
/***
 * @file - webspark_warranty.fetch.inc
 *
 * Includes file that holds all functions relating to fetching data, either in local files or
 * through the database, as well as simple manipulations of data
 *
 * Refer to following external docs for further assistance:
 * https://api.drupal.org/api/drupal/includes!database!database.inc/function/db_select/7.x
 * https://api.drupal.org/api/drupal/includes%21common.inc/function/drupal_get_path/7.x
 * https://www.php.net/manual/en/function.file-get-contents.php
 * https://www.php.net/manual/en/function.json-decode.php
 * https://www.php.net/manual/en/function.json-encode.php
 */

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

  $warrantyViolations = webspark_warranty_get_warranty_violations();

  // Checks whether any modules installed are unsupported or misplaced in the file directory
  if (sizeof($warrantyViolations['unsupported']) > 0 || sizeof($warrantyViolations['misplaced']) > 0)
    $status = FALSE;

  return $status ? 'True' : 'False';
}

/**
 * webspark_warranty_get_warranty_violations() - Gets all modules installed that
 *                                               are misplaced or not covered in the Webspark
 *                                               Warranty
 *
 * @return $warrantyViolations - Array of names of all unsupported / misplaced modules
 *                               installed
 */
function webspark_warranty_get_warranty_violations()
{
  $installedModules = webspark_warranty_get_installed_modules(); // All modules installed on the site
  $supportedModules = webspark_warranty_get_warranty_modules(); // All modules supported under the warranty

  $warrantyViolations = webspark_warranty_module_diff($installedModules, $supportedModules); // Any unsupported or misplaced modules

  return $warrantyViolations;
}

/**
 * webspark_warranty_get_installed_modules() - Uses Drupal's Database API to get
 *                                            all of the modules currently installed
 *                                            on the site (which resides within
 *                                            the {system} table)
 *
 * @return $allModulesArr - All installed modules in a sorted associative array
 */
function webspark_warranty_get_installed_modules()
{
  // Queries {system} table to get all fields sorted by name
  // All installed modules output as a flat array with Standard Class Objects for each entry
  $allModulesStd = db_select('system', 's')
                    ->fields('s', array('name', 'filename', 'type'))
                    ->condition('status', '1')
                    ->orderBy('name', 'ASC')
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
 *                               in a simple associative array
 */
function webspark_warranty_get_warranty_modules()
{
  // Pulls in contents from JSON file within module directory
  $warrantyModulesJSON = file_get_contents(drupal_get_path('module', 'webspark_warranty') .
                                            "/assets/standardModuleList.json", true);

  // Converts JSON to associative array with PHP library function
  $warrantyModulesArr = json_decode($warrantyModulesJSON, true);

  return $warrantyModulesArr;
}
