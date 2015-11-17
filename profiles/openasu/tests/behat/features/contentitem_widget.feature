Feature: Add existing content
  In order to put in a particular existing content item on a page
  As a site administrator
  I need to be able to choose which existing content item

  @api @javascript
  Scenario: Add existing content
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled
    When I visit "/node/add/panopoly-page"
      And I fill in the following:
        | Title               | Testing title |
        | Editor              | plain_text    |
        | body[und][0][value] | Testing body  |
        #And I press "Publish"
      And I press "Save"
      #Then the "h1" element should contain "Testing title"
      Then I should see "Testing body"
      And I should see "Content Page Testing title has been created."
    When I customize this page with the Panels IPE
      And I click "Add new pane"
      And I click "Add existing content"
    Then I should see "Configure new Add existing content"
    When I fill in the following:
      | exposed[title]        |Mobile Formatted|
    When I select "Content Page" from "exposed[type]"
      And I press "edit-return"
      And I press "Save as custom"
      And I wait for the Panels IPE to deactivate
    Then I should see "Mobile Formatted"
    And I should see "June 27, 2013"
      And I should see "Posted by admin"

