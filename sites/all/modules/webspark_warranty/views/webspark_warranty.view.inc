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
        '#markup' => '<h1>Current Status: <span style="color: green">In Warranty</span></h1>
                      <h2>If you are experiencing issues regarding your site, please visit the following link: ' .
                      l(t('https://drupal.asu.edu/wcs'), 'https://drupal.asu.edu/wcs',
                          array('attributes' => array('class' => array('lead'), 'target' => '_blank'))) .
                      '</h2>'
      )
    );
  }

  else
  {
    // Outputs renderable array that holds violation message and table holding unsupported modules
    $output = array(
      'message' => array(
        '#type' => 'markup',
        '#markup' => '<h1>Current Status: <span style="color: red">Out of Warranty</span></h1>
                      <h2>The following modules / themes are not covered by the Webspark Warranty: </h2>'
      ),
      'table' => array(
        '#theme' => 'table',
        '#header' => array(t('Name'), t('Type')),
        '#rows' => webspark_warranty_get_unsupported_modules()
      )
    );
  }

  return $output;
}
