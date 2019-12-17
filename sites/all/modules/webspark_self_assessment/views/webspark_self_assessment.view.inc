<?php
/***
 * @file - webspark_self_assessment.view.inc
 *
 * Includes file that acts as the view template for a Drupal menu page
 *
 * Refer to following external docs for further assistance:
 * https://www.drupal.org/docs/7/api/render-arrays/render-arrays-overview
 * https://api.drupal.org/api/drupal/includes%21bootstrap.inc/function/t/7.x
 * https://api.drupal.org/api/drupal/includes!common.inc/function/l/7.x
 */

/**
 * Page callback for /reports/self-assessment.
 */
function webspark_self_assessment_status_page()
{
  // Determines message based on whether site deviates from vanilla Webspark
  $status = webspark_self_assessment_get_status();

  if ($status == 'True')
  {
    // Outputs render array that holds message with contact info for WCS
    $output = webspark_self_assessment_regular_view();
  }

  else
  {
    // Outputs render array that holds violation message and table holding unsupported and misplaced modules
    $output = webspark_self_assessment_deviates_view();
  }

  return $output;
}

/**
 * webspark_self_assessment_regular_view() - Creates render array with markup showing status message
 *
 * @return $output - Render array with markup showing status message
 */
function webspark_self_assessment_regular_view()
{
  // Creates render array with markup showing status message
  $output = array(
    'message' => array(
      '#type' => 'markup',
      '#markup' => '<h1>' . t('Current Status: ') . '<span style="color: green">' . t('No Changes') . '</span></h1>' .
        '<h2>' . t('If you are experiencing issues regarding your site, please visit the following link: ') . '</h2>' .
        l(t('https://drupal.asu.edu/wcs'), 'https://drupal.asu.edu/wcs',
          array('attributes' => array('target' => '_blank'))) .
        '</h2>',
    )
  );

  return $output;
}

/**
 * webspark_self_assessment_deviates_view() - Creates render array with markup showing status message,
 *                                            with tables demonstrating violations
 * @return $output - Render array with markup showing status message, with tables demonstrating violations
 */
function webspark_self_assessment_deviates_view()
{
  // Gets all deviations to potentially display in tables
  $deviations = webspark_self_assessment_get_deviations();

  // Saves each type of violation in separate variable to avoid calling resource-intensive function
  $unsupportedModules = $deviations['unsupported'];
  $misplacedModules = $deviations['misplaced'];

  // Default markup showing red error message
  $output = array(
    'deviationMessage' => array(
      '#type' => 'markup',
      '#markup' => '<h1>' . t('Current Status: ') . '<span style="color: red">' . t('Deviations Detected') . '</span></h1>'
    )
  );

  // Appends render array table markup for unsupported modules if any exist
  if (sizeof($unsupportedModules) > 0)
  {
    $output[] = array(
      'unsupportedMessage' => array(
        '#type' => 'markup',
        '#markup' => '<h2>' . t('The following modules / themes are not in Webspark:') . '</h2>'
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
