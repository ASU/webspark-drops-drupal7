Feature: Live preview
  In order to do more WYSIWYG
  As a site administrator
  I need to be able to have a live preview of my changes to the widgets

  @api @javascript
  Scenario: Automatic live preview should show changes immediately
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are automatic
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
      And I click "Add table"
    Then I should see "Configure new Add table"
    When I fill in "Title" with "Widget title"
      And I wait for live preview to finish
    Then I should see "Widget title" in the "Live preview" region
    When I fill in "tablefield_0_cell_0_0" with "c-1-r-1"
      And I wait for live preview to finish
    Then I should see "c-1-r-1" in the "Live preview" region
    When I fill in "tablefield_0_cell_0_1" with "c-2-r-1"
      And I wait for live preview to finish
    Then I should see "c-2-r-1" in the "Live preview" region
    # Test that we can make the title into a link
    Then I should not see the link "Widget title" in the "Live preview" region
    When I check the box "Make title a link"
      And I wait for live preview to finish
      And I fill in "path" with "http://drupal.org"
      And I wait for live preview to finish
    Then I should see the link "Widget title" in the "Live preview" region
    When I press "Save" in the "CTools modal" region
      And I press "Save as custom"
      And I wait for the Panels IPE to deactivate
    Then I should see "Widget title"
      And I should see the link "Widget title"
      And I should see "c-1-r-1"
      And I should see "c-2-r-1"

  @api @javascript
  Scenario: Live preview should work with views
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are automatic
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
      And I click "Add content list"
    Then I should see "Configure new Add content list"
    When I fill in "widget_title" with "Content list widget"
      And I wait for live preview to finish
    Then I should see "Content list widget" in the "Live preview" region
    # @todo: we need to test switching the content type, but there's only
    # one included with our demo data.
    # Test changing the "Items to Show".
    Then I should see the link "Testing title" in the "Live preview" region
      And I should see the link "How to Edit a Site" in the "Live preview" region
      And I should see the link "Maps" in the "Live preview" region
    When I fill in "items_per_page" with "1"
      And I wait for live preview to finish
    Then I should see the link "Testing title" in the "Live preview" region
      And I should not see the link "Maps" in the "Live preview" region
      And I should not see the link "How to Edit a Site" in the "Live preview" region
    # Test changing the sort order.
    When I fill in "exposed[sort_order]" with "ASC"
      And I wait for live preview to finish
    Then I should not see the link "Testing title" in the "Live preview" region
    #And I should see the link "Vegetables are Great" in the "Live preview" region
    # Test changing the sort by.
    When I fill in "exposed[sort_by]" with "title"
      And I wait for live preview to finish
      #Then I should not see the link "Vegetables are Great" in the "Live preview" region
      #And I should see the link "Content Demo" in the "Live preview" region
    # Test changing the Display Type to "Content".
    Then I should not see the link "Read more" in the "Live preview" region
    When I select the radio button "Content"
      And I wait for live preview to finish
    Then I should see the link "Read more" in the "Live preview" region
    # Test changing the Display Type to "Table".
    When I select the radio button "Table"
      And I wait for live preview to finish
    # @todo: How do I test that there is a table there?
    Then I should not see the link "Read more" in the "Live preview" region
    # Test enabling the table header.
    Then I should not see "Image" in the "Live preview" region
      And I should not see "Title" in the "Live preview" region
      And I should not see "Date" in the "Live preview" region
      And I should not see "Posted by" in the "Live preview" region
    When I fill in "header_type" with "titles"
      And I wait for live preview to finish
    Then I should see "Image" in the "Live preview" region
      And I should see "Title" in the "Live preview" region
      And I should see "Date" in the "Live preview" region
      And I should see "Posted by" in the "Live preview" region
    # Test removing each of the fields.
    When I uncheck the box "fields_override[field_featured_image]"
      And I wait for live preview to finish
    Then I should not see "Image" in the "Live preview" region
    When I uncheck the box "fields_override[title]"
      And I wait for live preview to finish
    Then I should not see "Title" in the "Live preview" region
    When I uncheck the box "fields_override[created]"
      And I wait for live preview to finish
    Then I should not see "Date" in the "Live preview" region
    When I uncheck the box "fields_override[name]"
      And I wait for live preview to finish
    Then I should not see "Posted by" in the "Live preview" region

  @api @javascript
  Scenario: Manual live preview should show changes when requested
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are manual
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
      And I click "Add text"
    Then I should see "Configure new Add text"
    When I fill in "Title" with "Widget title"
    Then I should not see "Widget title" in the "Live preview" region
    When I press "Update Preview"
      And I wait for live preview to finish
    Then I should see "Widget title" in the "Live preview" region

  @api @javascript
  Scenario: Automatic live preview should validation errors immediately
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are automatic
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
    When I fill in "Description" with "Testing description"
      And I wait for live preview to finish
    Then I should see "Image field is required"
