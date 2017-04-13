<?php
/**
 * @file
 * Provide Behat step-definitions for the Innovation theme, based on functions
 * from panopoly_test.behat.inc.
 */

use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\RawDrupalContext;

class WebsparkWysiwygBehatTests extends RawDrupalContext implements DrupalSubContextInterface {

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
   * Get the instance variable to use in Javascript.
   *
   * @param string $instanceId
   *   The instanceId used by the WYSIWYG module to identify the instance.
   *
   * @throws Exeception
   *   Throws an exception if the editor doesn't exist.
   *
   * @return string
   *   A Javascript expression representing the WYSIWYG instance.
   */
  protected function getWysiwygInstance($instanceId) {
    $instance = "Drupal.wysiwyg.instances['$instanceId']";

    if (!$this->getSession()->evaluateScript("return !!$instance")) {
      throw new \Exception(sprintf('The editor "%s" was not found on the page %s', $instanceId, $this->getSession()->getCurrentUrl()));
    }

    return $instance;
  }

  /**
   * Get a Mink Element representing the WYSIWYG toolbar.
   *
   * @param string $instanceId
   *   The instanceId used by the WYSIWYG module to identify the instance.
   * @param string $editorType
   *   Identifies the underlying editor (for example, "tinymce").
   *
   * @throws Exeception
   *   Throws an exception if the toolbar can't be found.
   *
   * @return \Behat\Mink\Element\NodeElement
   *   The toolbar DOM Node.
   */
  protected function getWysiwygToolbar($instanceId, $editorType) {
    $driver = $this->getSession()->getDriver();

    switch ($editorType) {
      case 'tinymce':
        $toolbarElement = $driver->find("//div[@id='{$instanceId}_toolbargroup']");
        $toolbarElement = !empty($toolbarElement) ? $toolbarElement[0] : NULL;
        break;

      case 'markitup':
        $elementId = 'markItUp' . ucfirst($instanceId);
        $toolbarElement = $driver->find("//div[@id='{$elementId}']//div[@class='markItUpHeader']");
        $toolbarElement = !empty($toolbarElement) ? $toolbarElement[0] : NULL;
        break;
    }

    if (!$toolbarElement) {
      throw new \Exception(sprintf('Toolbar for editor "%s" was not found on the page %s', $instanceId, $this->getSession()->getCurrentUrl()));
    }

    return $toolbarElement;
  }


  /**
   * Click on the WYSIWYG drop down elements (<a> tags) to initially open them.
   *
   * @When I click the :action element identified by the :attributeType attribute in the :instanceId WYSIWYG editor
   */
  public function iClickTheDDInTheWysiwygEditor($action, $attributeType, $instanceId) {
    $driver = $this->getSession()->getDriver();

    $instance = $this->getWysiwygInstance($instanceId);
    $editorType = $this->getSession()
      ->evaluateScript("return $instance.editor");
    $toolbarElement = $this->getWysiwygToolbar($instanceId, $editorType);

    // Click the action button.
    $button = $toolbarElement->find("xpath", "//a[starts-with(@" . $attributeType . ", '$action')]");
    if (!$button) {
      throw new \Exception(sprintf('The "%s" element with attribute "%s" was not found in %s', $action, $attributeType, strtoupper($editorType)));
    }
    $button->click();
    $driver->wait(1000, TRUE);
  }

  /**
   * Click on the WYSIWYG dropdown options (<a> tags)
   *
   * @When I click the :styling option in the opened :dropDownName WYSIWYG editor drop down list
   *
   */
  public function iClickTheDDOptionInTheWysiwygEditor($styling, $dropDownName) {

    $page = $this->getSession()->getPage();
    $dropDownName = strtolower($dropDownName);
    $div = $page->find('xpath', "//div[@id[contains(., 'value_$dropDownName')] and @class[contains(., 'mceListBoxMenu')]]");
    if ($div) {
      $link = $div->find('xpath', "//span[@title='$styling']/parent::a");
      if (!$link) {
        throw new \Exception(sprintf('We found the text "%s" in the "%s" menu, but it wasn\'t a link.', $styling, $dropDownName));
      }
    } elseif (!$div) {
      throw new \Exception(sprintf('We couldn\'nt find "%s" on the page.', $styling));
    }
    if ($link) {
      $driver = $this->getSession()->getDriver();
      $link->click();
      $driver->wait(1000, TRUE);
    }
  }

}