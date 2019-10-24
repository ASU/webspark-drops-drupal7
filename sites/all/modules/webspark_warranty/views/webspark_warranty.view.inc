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
    // Outputs renderable array that holds message with contact info for WCS
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
  }

  else
  {
    // Outputs renderable array that holds violation message and table holding unsupported modules
    $output = array();
    $warrantyViolations = webspark_warranty_get_warranty_violations();
    $unsupportedModules = $warrantyViolations[0];
    $misplacedModules = $warrantyViolations[1];

    if (sizeof($unsupportedModules) > 0)
    {
      $output[] = array(
        'unsupportedMessage' => array(
          '#type' => 'markup',
          '#markup' => '<h1>' . t('Current Status: ') . '<span style="color: red">' . t('Out of Warranty') . '</span></h1>' .
            '<h2>' . t('The following modules / themes are not covered by the Webspark Warranty:') . '</h2>'
        ),
        'unsupportedTable' => array(
          '#theme' => 'table',
          '#header' => array(t('Name'), t('Type')),
          '#rows' => webspark_warranty_get_warranty_violations()[0]
        ),
      );
    }

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
          '#rows' => webspark_warranty_get_warranty_violations()[1]
        )
      );
    }
  }

  return $output;
}
