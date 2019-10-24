<?php

/**
 * Page callback for /reports/warranty.
 */
function webspark_warranty_status_page()
{
  // Determines message based on whether site is in warranty or not
  $status = webspark_warranty_get_warranty_status();

  if ($status == 'True')
  {
    // Outputs render array that holds message with contact info for WCS
    $output = webspark_warranty_under_warranty_view();
  }

  else
  {
    // Outputs render array that holds violation message and table holding unsupported and misplaced modules
    $output = webspark_warranty_violates_warranty_view();
  }

  return $output;
}

/**
 * webspark_warranty_under_warranty_view() - Creates render array with markup showing under-warranty message
 *
 * @return $output - Render array with markup showing under-warranty message
 */
function webspark_warranty_under_warranty_view()
{
  // Creates render array with markup showing under-warranty message
  $output = array(
    'message' => array(
      '#type' => 'markup',
      '#markup' => '<h1>' . t('Current Status: ') . '<span style="color: green">' . t('In Warranty') . '</span></h1>' .
        '<h2>' . t('If you are experiencing issues regarding your site, please visit the following link: ') . '</h2>' .
        l(t('https://drupal.asu.edu/wcs'), 'https://drupal.asu.edu/wcs',
          array('attributes' => array('target' => '_blank'))) .
        '</h2>',
    )
  );

  return $output;
}

/**
 * webspark_warranty_violates_warranty_view() - Creates render array with markup showing warranty violation message,
 *                                              with tables demonstrating violations
 * @return $output - Render array with markup showing warranty violation message, with tables demonstrating violations
 */
function webspark_warranty_violates_warranty_view()
{
  // Gets all warranty violations to potentially display in tables
  $warrantyViolations = webspark_warranty_get_warranty_violations();

  // Saves each type of violation in separate variable to avoid calling resource-intensive function
  $unsupportedModules = $warrantyViolations['unsupported'];
  $misplacedModules = $warrantyViolations['misplaced'];

  // Default markup showing red error message
  $output = array(
    'violationMessage' => array(
      '#type' => 'markup',
      '#markup' => '<h1>' . t('Current Status: ') . '<span style="color: red">' . t('Out of Warranty') . '</span></h1>'
    )
  );

  // Appends render array table markup for unsupported modules if any exist
  if (sizeof($unsupportedModules) > 0)
  {
    $output[] = array(
      'unsupportedMessage' => array(
        '#type' => 'markup',
        '#markup' => '<h2>' . t('The following modules / themes are not covered by the Webspark Warranty:') . '</h2>'
      ),
      'unsupportedTable' => array(
        '#theme' => 'table',
        '#header' => array(t('Name'), t('Type')),
        '#rows' => $unsupportedModules
      ),
    );
  }

  // Appends render array table markup for misplaced modules if any exist
  if (sizeof($misplacedModules) > 0)
  {
    $output[] = array(
      'misplacedMessage' => array(
        '#type' => 'markup',
        '#markup' => '<h2>' . t('The following modules / themes are not installed at the correct path:') . '</h2>'
      ),
      'misplacedTable' => array(
        '#theme' => 'table',
        '#header' => array(t('Name'), t('File Path')),
        '#rows' => $misplacedModules
      )
    );
  }

  // Appends message on recommended action. Probably will change
  $output[] = array(
    'recommendedActionsMessage' => array(
      '#type' => 'markup',
      '#markup' => '<h2>' . t('TENTATIVE: Please resolve the issues listed above before contacting Web Consulting Services') . '</h2>'
    )
  );

  return $output;
}
