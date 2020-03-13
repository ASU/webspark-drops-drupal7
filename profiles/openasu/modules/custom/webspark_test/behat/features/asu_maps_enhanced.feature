Feature: Configure and display an interactive map showing an ASU building location
  Background:
    Given I am logged in as a user with the "administrator" role

  @javascript @api @asu_maps_enhanced
  Scenario: Display a map panel with 1 location.
    Given I am at "/node/add"
    When I click "Content Page"
    And I fill in "Title" with "Test page for directory panel"
    And I type "testing in body" in the "edit-body-und-0-value" WYSIWYG editor
    And I press the "Publish" button
    And I click "Customize this page"
    And I click "Add new pane"
    And I click "Add ASU enhanced map"
    And I wait 30 seconds
    Then I should see "Title"
    And I click the "#6268>div>a" element
    And I click the "#6274>div>a" element
    And I click the "#62862 input" element
    And I click the "#62861 input" element
    When I fill in the following:
      | Title                                                    | ASU Map |
      | field_asu_maps_enhanced_items[und][0][campus_selection]  | TEMPE   |
    And I click the "#edit-return" element
    And I press "Save as custom"
    And I switch to the iframe "enhanced-map-frame"
    And I wait 3 seconds
    Then I should see "College of Design North"

  @javascript @api @asu_maps_enhanced
  Scenario: Display a map panel with categories.
    Given I am at "/node/add"
    When I click "Content Page"
    And I fill in "Title" with "Test page for directory panel"
    And I type "testing in body" in the "edit-body-und-0-value" WYSIWYG editor
    And I press the "Publish" button
    And I click "Customize this page"
    And I click "Add new pane"
    And I click "Add ASU enhanced map"
    And I wait 30 seconds
    Then I should see "Title"
    And I click the "#6268>div>a" element
    And I click the "#6273>div>input" element
    When I fill in the following:
      | Title                                                    | ASU Map |
      | field_asu_maps_enhanced_items[und][0][campus_selection]  | TEMPE   |
    And I click the "#edit-return" element
    And I press "Save as custom"
    And I switch to the iframe "enhanced-map-frame"
    And I wait 2 seconds
    And I click the '[alt="Palo Verde West map marker"]' element
    And I wait 2 seconds
    Then I should see "Palo Verde West"
