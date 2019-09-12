Feature: Add ASU spotlight widget
  In order to promote content
  As a site administrator
  I need to be able to add a spotlight

  Background:
    Given I am logged in as a user with the "administrator" role
    And Panopoly magic live previews are disabled
    And I am viewing a landing page
    When I customize this page with the Panels IPE
    And I click "Add new pane"
    And I click "Add ASU spotlight" in the "CTools modal" region
    Then I should see "Configure new Add ASU spotlight"

  @api @javascript @drupal_private_files
  Scenario: Add a ASU spotlight
    When I fill in the following:
      | field_asu_spotlight_items[und][0][title]  | Testing item title  |
      | Link for Title                            | http://drupal.org   |
      | Button Link                               | http://drupal.org |
      | Button Text                               | test button            |
      | Button color                              | red              |
      | Text position over image                  | mid-center    |
    And I click "Browse"
    And I switch to the frame "mediaBrowser"
    And I attach the file "test-lg.png" to "files[upload]"
    And I press "Next"
    Then I should see "Destination"
    When I select the radio button "Public local files served by the webserver."
    And I press "Next"
    And I wait 2 seconds
    Then I should see a "#edit-submit" element
    And I should see the "Crop" button
    When I press "Save"
    And I switch out of all frames
    And I wait 2 seconds
    And I press the "Add" button
    And I press the "Save" button
    And I wait for the Panels IPE to deactivate
    Then I should see "Testing item title"
    And I should see "test button"
    And I should see the property "class" from the element "a" with value "btn btn-primary btn-block"
    And I should see the property "class" from the element "div" with value "blurbshell mid-center full-width"
    Then I should see the property "class" from the element "img" with value "asu-spotlight-image"
