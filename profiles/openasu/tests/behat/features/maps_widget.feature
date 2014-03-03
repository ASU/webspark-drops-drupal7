Feature: Add map widget
  In order to put a map on a page
  As a site administrator
  I need to be able to use the map widget

  @api @javascript
  Scenario: Add map to a page
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled
    When I visit "/node/add/panopoly-page"
      And I fill in the following:
        | Title               | Testing text title |
        | Editor              | plain_text         |
        | body[und][0][value] | Testing text body  |
        #And I press "Publish"
      And I press "Save"
      #Then the "h1" element should contain "Testing text title"
    When I customize this page with the Panels IPE
      And I click "Add new pane"
      And I click "Add map"
    Then I should see "Configure new Add map"
    When I fill in the following:
      | Title       | Widget title            |
      | Editor      | plain_text              |
      | Information | Testing text body field |
      | Address     | Ørnebjergvej 28, Vejle  |
      And I press "edit-return"
      And I press "Save as custom"
      And I wait for the Panels IPE to deactivate
    Then I should see "Widget title"
      And I should see "Testing text body field"
