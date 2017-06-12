<?php
/**
 * @file
 * Provide Behat step-definitions for the Innovation theme, based on functions
 * from panopoly_test.behat.inc.
 */
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\RawDrupalContext;
class WebsparkBehatTests extends RawDrupalContext implements DrupalSubContextInterface {
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
   * @Then the :field Innovation radio button should be set to :option
   *
   * @description - Tweaked copy of the theRadioButtonShouldBeSetTo function in
   * panopoly_test.behat.inc. Built to deal with the Font Awesome icons in
   * <label> tags.
   */
  public function theInnovationRadioButtonShouldBeSetTo($field, $option) {
    $page = $this->getSession()->getPage();
    $div = $page->find('xpath', "//div[contains(., '$field') and @class[contains(.,'form-type-radio')]]");
    if ($div) {
      $radios = $div->find('xpath', "//input[@type='radio']");
      if ($radios) {
        // XPath altered for Webspark DOM customization
        $checkedRadio = $div->find('xpath', "//input[@type='radio' and @checked='checked']/parent::label[contains(., '$option')]");
        if (!$checkedRadio) {
          throw new \Exception(sprintf('We found the radio buttons for "%s", but "%s" was not selected.', $field, $option));
        }
      } elseif (!$radios) {
        throw new \Exception(sprintf('We found "%s", but it did not contain any radio buttons".', $field));
      }
    } elseif (!$div) {
      throw new \Exception(sprintf('We couldn\'nt find "%s" on the page', $field));
    } else {
      throw new \Exception('General exception from '.__FUNCTION__);
    }
  }
}