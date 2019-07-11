<?php
/**
 * @file
 * The main Behat context.
 */

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;

/**
 * Define application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {
  
  /**
   * Initializes context.
   * Every scenario gets its own context object.
   *
   * @param array $parameters
   *   Context parameters (set them in behat.yml)
   */
  public function __construct() {
    // Initialize your context here
  }

  /**
   * @When I mock the migration source :arg1
   */
  public function iMockTheMigrationSource($arg1) {
    $path = $this->getMinkParameter('files_path') . '/' . $arg1;
    $file_contents = file_get_contents($path);
    $file = file_save_data( $file_contents, "private://isearch/feeds/asu_isearch_master.json", FILE_EXISTS_REPLACE );

    if (!$file) {
      throw new \Exception('Migration mocking failed at '.__FUNCTION__);
    }
  }

  /**
   * @When I click the :arg1 element
   */
  public function iClickTheElement($selector)
  {
      $page = $this->getSession()->getPage();
      $element = $page->find('css', $selector);

      if (empty($element)) {
          throw new Exception("No html element found for the selector ('$selector')");
      }

      $element->click();
  }
}
