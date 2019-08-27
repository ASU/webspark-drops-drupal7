Feature: Import and display iSearch Profiles
  Background:
    Given I am logged in as a user with the "administrator" role

  @javascript @api @asu_isearch
  Scenario: Run an import, then add directory panel with imported profiles
    Given I am at "/admin/content/isearch/configure"
    When I click on the element "label" which has property "data-reactid" with value ".1.1"
    And I press the "Browse" button
    And I click the '[dept_nid="1359"] a.jqtree-toggler' element
    And I click the '[dept_nid="1569"] a.jqtree-toggler' element
    And I click on the element "li" which has property "dept_nid" with value "2163"
    And I click on the text " Include sub-departments?" in the "label" tag
    And I press the "Submit" button
    And I press the "Save configuration" button
    And I mock the migration source "asu_isearch.test_mock_one.json"
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
    And I click "Add ASU directory panel"
    And I press the "Browse" button
    And I click the '[dept_nid="1359"] a.jqtree-toggler' element
    And I click the '[dept_nid="1569"] a.jqtree-toggler' element
    And I click on the element "li" which has property "dept_nid" with value "2163"
    And I click on the text " Include sub-departments?" in the "label" tag
    And I press the "Submit" button
    And I click on the element "a" which has property "href" with value "#edit-field-asu-directory-items-und-0-horizontal-tabs-advanced"
    And I click on the element "label" which has property "for" with value "edit-field-asu-directory-items-und-0-horizontal-tabs-advanced-always-display-view"
    And I press the "Add" button
    And I press the "Save as custom" button
    And I click on the text "View" in the "a" tag
    And I click on the text "ALL" in the "li" tag
    Then I should see "Customized Drupal Developer Senior"

  @javascript @api @asu_isearch
  Scenario: Run an import to update profiles, then load updated profile
    Given I am at "/admin/content/isearch/import"
    And I run drush "vset isearch_local_lock 1"
    When I mock the migration source "asu_isearch.test_mock_one.json"
    And I fill in "edit-isearch-import-limit-value" with "50"
    And I press the "Begin import" button
    And I wait for 30 seconds
    Then I should see "Processed"
    When I am at "/content/sparky-webspark"
    Then I should see "Sparky Webspark"
    And I should see "Customized Drupal Developer Senior"
    And I should see "This is a mock bio."
    When I click on the element "a" which has property "id" with value "ui-id-2"
    Then I should see the "a" element with the "href" attribute set to "https://isearch.asu.edu/asu-people/testvalue" in the "Content" region
    And I should see the "a" element with the "href" attribute set to "https://www.asu.edu/" in the "Content" region
    When I am at "/admin/content/isearch/import"
    When I mock the migration source "asu_isearch.test_mock_two.json"
    And I fill in "edit-isearch-import-limit-value" with "50"
    And I press the "Begin import" button
    And I wait for 30 seconds
    Then I should see "Updated"
    When I am at "/content/sparky-webspark"
    Then I should see "Super Drupal Developer Senior"
    When I run drush "vset isearch_local_lock 0"
    And I am at "/content/sparky-webspark"
    Then I should see "Profile not found."
    