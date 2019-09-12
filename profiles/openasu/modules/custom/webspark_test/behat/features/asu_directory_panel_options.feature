Feature: Add ASU directory panel with options
  Background:
    Given I am logged in as a user with the "administrator" role

  @private_files @javascript @api @panopoly_magic @drushTest
  Scenario: Add ASU directory panel with department tree
    Given I am at "/node/add"
    When I click "Content Page"
    And I fill in "Title" with "Test page for directory panel"
    And I type "testing in body" in the "edit-body-und-0-value" WYSIWYG editor
    And I press the "Publish" button
    And I click "Customize this page"
    And I click "Add new pane"
    And I click "Add ASU directory panel"
    And I press the "Browse" button
    And I click on the element "li" which has property "dept_nid" with value "1359"
    And I press the "Submit" button
    And I click on the element "label" which has property "for" with value "edit-field-asu-directory-items-und-0-horizontal-tabs-content-content-tabs-department-show-tree"
    And I press the "Add" button
    And I press the "Save as custom" button
    And I click on the text "View" in the "a" tag
    And I click on the element "div" which has property "id" with value "treediv1"
    Then I should see the property "class" from the element "div" with value "row row-header asu_directory_people_row "

  @private_files @javascript @api @panopoly_magic @drushTest
  Scenario: Add ASU directory panel without filters
    Given I am at "/node/add"
    When I click "Content Page"
    And I fill in "Title" with "Test page for directory panel"
    And I type "testing in body" in the "edit-body-und-0-value" WYSIWYG editor
    And I press the "Publish" button
    And I click "Customize this page"
    And I click "Add new pane"
    And I click "Add ASU directory panel"
    And I press the "Browse" button
    And I click on the element "li" which has property "dept_nid" with value "1359"
    And I press the "Submit" button
    And I click on the text " Appearance" in the "strong" tag
    And I click "Exposed Filters"
    And I click on the element "label" which has property "for" with value "edit-field-asu-directory-items-und-0-horizontal-tabs-appearance-appearance-tabs-exposed-show-filters"
    And I press the "Add" button
    And I press the "Save as custom" button
    And I click on the text "View" in the "a" tag
    Then I should not see "Sort:"

  @private_files @javascript @api @panopoly_magic @drushTest
  Scenario: Add ASU directory panel with location column
    Given I am at "/node/add"
    When I click "Content Page"
    And I fill in "Title" with "Test page for directory panel"
    And I type "testing in body" in the "edit-body-und-0-value" WYSIWYG editor
    And I press the "Publish" button
    And I click "Customize this page"
    And I click "Add new pane"
    And I click "Add ASU directory panel"
    And I press the "Browse" button
    And I click on the element "li" which has property "dept_nid" with value "1359"
    And I press the "Submit" button
    And I click on the text " Appearance" in the "strong" tag
    And I click "Columns"
    And I click on the element "label" which has property "for" with value "edit-field-asu-directory-items-und-0-horizontal-tabs-appearance-appearance-tabs-columns-display-building"
    And I press the "Add" button
    And I press the "Save as custom" button
    And I click on the text "View" in the "a" tag
    Then I should see "USB"

  @private_files @javascript @api @panopoly_magic @drushTest
  Scenario: Add ASU directory panel without A-Z index
    Given I am at "/node/add"
    When I click "Content Page"
    And I fill in "Title" with "Test page for directory panel"
    And I type "testing in body" in the "edit-body-und-0-value" WYSIWYG editor
    And I press the "Publish" button
    And I click "Customize this page"
    And I click "Add new pane"
    And I click "Add ASU directory panel"
    And I press the "Browse" button
    And I click on the element "li" which has property "dept_nid" with value "1359"
    And I press the "Submit" button
    And I click on the text " Appearance" in the "strong" tag
    And I click "Exposed Filters"
    And I click on the element "label" which has property "for" with value "edit-field-asu-directory-items-und-0-horizontal-tabs-appearance-appearance-tabs-exposed-show-az-index"
    And I press the "Add" button
    And I press the "Save as custom" button
    And I click on the text "View" in the "a" tag
    Then I should not see "ALL"

  @private_files @javascript @api @panopoly_magic @drushTest
  Scenario: Add ASU directory panel without search box
    Given I am at "/node/add"
    And I click "Content Page"
    And I fill in "Title" with "Test page for directory panel"
    When I type "testing in body" in the "edit-body-und-0-value" WYSIWYG editor
    And I press the "Publish" button
    And I click "Customize this page"
    And I click "Add new pane"
    And I click "Add ASU directory panel"
    And I press the "Browse" button
    And I click on the element "li" which has property "dept_nid" with value "1359"
    And I press the "Submit" button
    And I click on the text " Appearance" in the "strong" tag
    And I click "Exposed Filters"
    And I click on the element "label" which has property "for" with value "edit-field-asu-directory-items-und-0-horizontal-tabs-appearance-appearance-tabs-exposed-show-filter-omni"
    And I press the "Add" button
    And I press the "Save as custom" button
    And I click on the text "View" in the "a" tag
    Then I should not see the property "class" from the element "input" with value "input-main-search form-control form-text required"