Feature: Configure and display an interactive map showing an ASU building location
  Background:
    Given I am logged in as a user with the "administrator" role

  @javascript @api @asu_maps_enhanceds
  Scenario: Display a map panel with 1 location.
    Given I am at "/node/add"
    When I click "Content Page"
    And I fill in "Title" with "Test page for directory panel"
    And I type "testing in body" in the "edit-body-und-0-value" WYSIWYG editor
    And I press the "Save" button
    And I click "Customize this page"
    And I click "Add new pane"
    And I click "Add ASU enhanced map"
    Then I should see "Title"
    And I click the "#asu-gis-fp>ol>li:last-child button" element
    And I wait 2 seconds
    And I click the "#asu-gis-fp-CampusBuilding_7147_1" element
    And I wait 2 seconds
    And I click the "#asu-maps-enhanced-tree select" element
    When I fill in the following:
      | Select a Feature | {"id":630,"name":"Academic Center","lat":33.30705300012226,"lng":-111.67845199981096,"parent":"CampusBuilding_7147_1"} |
    And I scroll "edit-return" into view
    And I press the "edit-return" button
    And I press the "panels-ipe-save" button
    And I wait 5 seconds
    And I switch to the only available frame "enhanced-map-frame"
    And I wait 5 seconds
    Then I should see "Academic Center"

