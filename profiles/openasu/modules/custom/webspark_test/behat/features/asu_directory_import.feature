Feature: Import iSearch Profiles
  Background:
    Given I am logged in as a user with the "administrator" role

  @javascript @api
  Scenario: Run an import, then add directory panel with imported profiles
    Given I am at "/admin/content/isearch/configure"
    When I click on the element "label" which has property "data-reactid" with value ".1.1"
    And I press the "Browse" button
    And I click on the element "li" which has property "dept_nid" with value "1344"
    And I click on the text " Include sub-departments?" in the "label" tag
    And I press the "Submit" button
    And I press the "Save configuration" button
    And I click "Import iSearch Profiles"
    And I fill in "edit-isearch-import-limit-value" with "50"
    And I press the "Begin import" button
    And I wait for 30 seconds
    Then I should see "Processed"
    When I am at "/admin/content"
    Then I should see "iSearch Profile"
    When I am at "/node/add"
    And I click "Content Page"
    And I fill in "Title" with "Test page for directory panel"
    And I type "testing in body" in the "edit-body-und-0-value" WYSIWYG editor
    And I press the "Publish" button
    And I click "Customize this page"
    And I click "Add new pane"
    And I click "Add ASU Directory Panel"
    And I press the "Browse" button
    And I click on the element "li" which has property "dept_nid" with value "1344"
    And I click on the text " Include sub-departments?" in the "label" tag
    And I press the "Submit" button
    And I click on the element "a" which has property "href" with value "#edit-field-asu-directory-items-und-0-horizontal-tabs-advanced"
    And I click on the element "label" which has property "for" with value "edit-field-asu-directory-items-und-0-horizontal-tabs-advanced-always-display-view"
    And I press the "Add" button
    And I press the "Save as custom" button
    And I click on the text "View" in the "a" tag
    And I click on the text "ALL" in the "li" tag
    Then I should not see "No employees found."
