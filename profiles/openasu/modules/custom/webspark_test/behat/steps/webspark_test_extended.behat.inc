<?php
/**
 * @file
 * Provide Behat step-definitions for the Innovation theme, based on functions
 * from webspark_test.behat.inc.
 */
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\RawDrupalContext;
class WebsparkCustomBehatTests extends RawDrupalContext implements DrupalSubContextInterface {

  /**
   * Contains the DrupalDriverManager.
   *
   * @var \Drupal\DrupalDriverManager
   */
  private $drupal;

  /**
   * Initializes context.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Click some text using identifiers
   *
   * @When /^I click on the element "([^"]*)" which has property "([^"]*)" with value "([^"]*)"$/
   */
  public function iClickOnTheElement($element, $property, $val)
  {
    $session = $this->getSession();
    $element = $session->getPage()->
    find('xpath',$session->getSelectorsHandler()->selectorToXpath('xpath', "//" . $element . "[@" . $property . "='" . $val ."']" ));

    if (null === $element) {
      throw new \InvalidArgumentException(print('Cannot find the specified item.'));
    }

    $element->click();

  }

  /**
   * Click some text wrapped by some tag
   *
   * @When /^I click on the text "([^"]*)" in the "([^"]*)" tag$/
   */
  public function iClickOnTheText($text,$tag)
  {
    $session = $this->getSession();
    $element = $session->getPage()->
    find('xpath',$session->getSelectorsHandler()->selectorToXpath('xpath', "//" . $tag. '[text()="' . $text  . '"]'));

    if (null === $element) {
      throw new \InvalidArgumentException(print('Cannot find the specified text.'));
    }

    $element->click();

  }

  /**
   * See a certain element with identifiers
   *
   * @When /^I should see the property "([^"]*)" from the element "([^"]*)" with value "([^"]*)"$/
   */
  public function iSeeTheElement($property,$element, $nid)
  {
    $session = $this->getSession();
    $element = $session->getPage()->
    find('xpath',$session->getSelectorsHandler()->selectorToXpath('xpath', "//" . $element . "[@" . $property . "='" . $nid ."']" ));

    if (null === $element) {
      throw new \InvalidArgumentException(print('Cannot find the specified item.'));
    }

  }

  /**
   * See a certain element with identifiers
   *
   * @When /^I should not see the property "([^"]*)" from the element "([^"]*)" with value "([^"]*)"$/
   */
  public function iShouldNotSeeTheElement($property,$element, $nid)
  {
    $session = $this->getSession();
    $element = $session->getPage()->
    find('xpath',$session->getSelectorsHandler()->selectorToXpath('xpath', "//" . $element . "[@" . $property . "='" . $nid ."']" ));

    if (null != $element) {
      throw new \InvalidArgumentException(print('The specified item was found.'));
    }

  }
}