Feature: Add content list widget
  In order to create a list of certain content
  As a site administrator
  I need to add a list with content I choose

  @api @javascript
  Scenario: Add a content list
    Given I am logged in as a user with the "administrator" role
    And Panopoly magic live previews are disabled
    When I visit "/node/add/panopoly-page"
    And I fill in the following:
      | Title               | Testing title |
      | Editor              | plain_text    |
      | body[und][0][value] | Testing body  |
    And I press "Save"
    #And I press "Publish"
    #Then the "h1" element should contain "Testing title"
    When I customize this page with the Panels IPE
    And I click "Add new pane"
    And I click "Add content list"
    Then I should see "Configure new Add content list"
    When I fill in the following:
      | widget_title    | Content Page List Asc 1 |
      | items_per_page  | 1                       |
    And I select the radio button "Content"
    When I select "Content Page" from "exposed[type]"
    And I select "Asc" from "exposed[sort_order]"
    And I select "Title" from "exposed[sort_by]"
    And I press "edit-return"
    And I press "Save as custom"
    And I wait for the Panels IPE to deactivate
    Then I should see "Content Page List Asc 1"
    Then I should see "About ASU webspark"
    Then I should see "ASU has partnered with Pantheon to provide Drupal web hosting, along with a custom version of Drupal specifically created for ASU called ASU Webspark."
    And I should see "It’s free to create development and test sites in the Pantheon environment and hosting is available for ASU sites from $20 per month."
    When I customize this page with the Panels IPE
     And I click "Settings" in the "Bryant Sidebar" region
    Then I should see "Configure Add content list"
    And the "exposed[sort_by]" field should contain "Title"
