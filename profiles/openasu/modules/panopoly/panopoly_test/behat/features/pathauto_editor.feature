Feature: Test pathauto for editor users
  In order to get nice urls
  As a site editor
  I need to be able to trust that pathauto works consistently

  Background:
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled
    When I visit the default theme settings page
      And I check the box "edit-always-show-page-title"
      And I press "edit-submit"
      And I am logged in as a user with the "editor" role
      And I visit "/node/add/panopoly-test-page"
      And I fill in the following:
        | Title  | Testing title |
        | Editor | plain_text    |
        | Body   | Testing body  |
    # Normally, here we'd press "Publish", however some child distribtions
    # don't use 'save_draft', and this makes this test compatible with them.
    #When I press "Publish"
    When I press "edit-submit"
    Then the "h1" element should contain "Testing title"

  @api @panopoly_admin
  Scenario: Pathauto should automatically assign an url
    Then the url should match "testing-title"

  @api @panopoly_admin @webspark_broken @webspark_fixed
  Scenario: Pathauto should automatically assign a new url when changing the title
    When I click "Edit" in the "TabsID" region
      And I fill in the following:
        | Title               | Completely other title |
      And I press "Save"
    Then the url should match "completely-other-title"
    # But visiting the old URL should continue to work
    When I visit "/content/testing-title"
    Then the "h1" element should contain "Completely other title"

  @api @panopoly_admin @webspark_added
  Scenario: Resetting the Innovation theme Always Show Page Title setting
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled
    When I visit the default theme settings page
      And I uncheck the box "edit-always-show-page-title"
      And I press "edit-submit"
      And I visit the default theme settings page
    Then the "edit-always-show-page-title" checkbox should not be checked
