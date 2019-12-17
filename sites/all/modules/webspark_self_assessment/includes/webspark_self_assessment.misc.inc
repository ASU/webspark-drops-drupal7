<?php
/***
 * @file - webspark_self_assessment.misc.inc
 *
 * Includes file that holds miscellaneous helper functions which aid with the execution of other tasks
 * throughout the module
 */

/**
 * webspark_self_assessment_module_diff($installedModules, $supportedModules) - Recursively finds the difference between two
 *                                                                      arrays. Edited from Stack Overflow answer
 *
 * @param $installedModules - Installed modules array that is compared to the supported modules array
 * @param $defaultModules - The supported modules array that is being compared from the installed modules array
 *
 * @return $outputDiff - Returns an associative array that holds modules that are either unsupported, or installed in the
 *                       wrong directory (misplaced)
 */
function webspark_self_assessment_module_diff($installedModules, $defaultModules)
{
  // change module name capitalization

  $unsupportedDiff = []; // Installed modules not in vanilla Webspark
  $misplacedDiff = []; // Installed modules that are in vanilla Webspark, but are misplaced

  // Go through all installed modules
  foreach ($installedModules as $installed => $installedElement)
  {
    // Assumes modules are unsupported, and therefore cannot be misplaced
    $found = false;
    $misplaced = false;

    // Go through all supported modules (as written in JSON file)
    foreach ($defaultModules as $supported => $supportedElement)
    {
      // Checks whether or not the selected installed module has the same name and type (actually supported),
      // but in the wrong location (misplaced)
      if ($installedElement['name'] == $supportedElement['name'] && $installedElement['type'] == $supportedElement['type'] &&
        $installedElement['filename'] != $supportedElement['filename'])
      {
        // If true, appends the entry to the misplaced diff array and sets the respective boolean to true
        $misplacedDiff[] = array('name' => $installedElement['name'], 'filename' => $installedElement['filename']);
        $misplaced = true;
      }

      // Checks whether or not the selected installed module has the exact same info (supported)
      else if ($installedElement['name'] == $supportedElement['name'] && $installedElement['type'] == $supportedElement['type'] &&
          $installedElement['filename'] == $supportedElement['filename'])
        // If true, then it sets the respective boolean to true
        $found = true;
    }

    // If the entry is not found and isn't misplaced, then it is added to the unsupported diff array
    if (!$found && !$misplaced)
      $unsupportedDiff[] = array('name' => $installedElement['name'], 'type' => $installedElement['type']);
  }

  // Puts both diff array results into associative array and returns
  return array(
    'unsupported' => $unsupportedDiff,
    'misplaced' => $misplacedDiff
  );
}
