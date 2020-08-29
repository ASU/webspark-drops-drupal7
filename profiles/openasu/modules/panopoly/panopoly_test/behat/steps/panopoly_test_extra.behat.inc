<?php

namespace Drupal\DrupalExtension\Context;

use Behat\Behat\Context\TranslatableContext;
use Behat\Mink\Exception\UnsupportedDriverActionException;
use Exception;

/**
 * Extensions to the Mink Extension.
 */
class PanopolyExtraMinkContext extends MinkContext implements TranslatableContext {
  /**
   * Visit the default theme path. Modeled after MinkContext->assertAtPath()
   *
   * @When /^I visit the default theme settings page$/
   */
  public function assertDefaultThemePath() {
    try {
      $theme = variable_get('theme_default', '');
      if (empty($theme)) {
        throw new Exception('No default theme name/value found in the site.');
      }
    } catch (Exception $e) {
      echo "Error: " . $e->getMessage();
    }

    $path = '/admin/appearance/settings/' . $theme;
    $this->getSession()->visit($this->locatePath($path));
    // If available, add extra validation that this is a 200 response.
    try {
      $this->getSession()->getStatusCode();
      $this->assertHttpResponse('200');
    } catch (UnsupportedDriverActionException $e) {
      // Simply continue on, as this driver doesn't support HTTP response codes.
    }
  }
}


