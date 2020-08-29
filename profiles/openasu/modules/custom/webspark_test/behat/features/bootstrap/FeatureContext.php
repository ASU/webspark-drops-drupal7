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
   * @throws Exception
   */
  public function iMockTheMigrationSource($arg1) {
    $path = $this->getMinkParameter('files_path') . '/' . $arg1;
    $file_contents = file_get_contents($path);
    $destination = 'private://isearch/feeds';
    $dir_uri = drupal_realpath($destination);

    if (!$file_contents) {
      throw new \Exception('Migration mocking failed at ' . __FUNCTION__ . '. ' . check_plain($arg1)
        . ' not found or was unreadable.');
    }
    $file = file_save_data($file_contents, $destination . '/asu_isearch_master.json', FILE_EXISTS_REPLACE);

    if (!$file) {
      throw new \Exception('Migration mocking failed at ' . __FUNCTION__
        . ': Check the permissions for the ' . $dir_uri . ' directory first.');
    }
  }

  /**
   * @When I click the :arg1 element
   */
  public function iClickTheElement($selector) {
    $page = $this->getSession()->getPage();
    $element = $page->find('css', $selector);

    if (empty($element)) {
      throw new Exception("No html element found for the selector ('$selector')");
    }

    $element->click();
  }

  /**
   * @Given /^I switch to the iframe "([^"]*)"$/
   */
  public function iSwitchToIframe($arg1 = null) {
    $this->getSession()->switchToIFrame($arg1);
  }

  /**
   * @When I scroll :elementId into view
   */
  public function iScrollIntoView($elementId) {
    $function = <<<JS
(function(){
  var elem = document.getElementById("$elementId");
  elem.scrollIntoView(false);
})()
JS;
    try {
      $this->getSession()->executeScript($function);
    } catch (Exception $e) {
      throw new \Exception('ScrollIntoView failed');
    }
  }
}
