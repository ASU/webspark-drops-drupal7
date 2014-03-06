Feature: Add spotlight widget
  In order to promote content
  As a site administrator
  I need to be able to add a spotlight

  Background:
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
    When I customize this page with the Panels IPE
      And I click "Add new pane"
      And I click "Add spotlight"
    Then I should see "Configure new Add spotlight"

  @api @javascript
  Scenario: Add a spotlight
    When I fill in the following:
      | field_basic_spotlight_items[und][0][title] | Testing item title  |
      | Link                                       | http://drupal.org   |
      | Description                                | Testing description |
      And I attach the file "panopoly.png" to "files[field_basic_spotlight_items_und_0_fid]"
      And I press "edit-return"
      #And I press "Save"
      And I wait for the Panels IPE to deactivate
    Then I should see "Testing description"
    #And I should see "Testing item title"
      # Per an old bug described in issue #2075903
      #And I should not see "Spotlight"

  @api @javascript
  Scenario: Image is required per issue #2075903
    When I fill in the following:
      | field_basic_spotlight_items[und][0][title] | Testing item title  |
      | Link                                       | http://drupal.org   |
      | Description                                | Testing description |
      And I press "edit-return"
    Then I should see "Image field is required"
