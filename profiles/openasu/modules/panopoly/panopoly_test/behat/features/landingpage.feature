Feature: Add landing page
  In order to create a fully customizable page
  As a site administrator
  I need to be able to create a landing page

  Background:
    Given I am logged in as a user with the "administrator" role
      #temporarily add page titles back
    When I visit the default theme settings page
      And I check the box "edit-always-show-page-title"
      And I press "edit-submit"
      And I visit "/node/add/panopoly-landing-page"
      And I fill in the following:
        | Title         | Testing landing page title |

  @api @panopoly_pages @webspark_broken @webspark_fixed
  Scenario: Add a landing page
    # Normally, here we'd press "Publish", however some child distribtions
    # don't use 'save_draft', and this makes this test compatible with them.
    #When I press "Publish"
    When I press "edit-submit"
    Then the "h1" element should contain "Testing landing page title"

    When I visit the default theme settings page
      And I uncheck the box "edit-always-show-page-title"
      And I press "edit-submit"
      And I visit the default theme settings page
    Then the "edit-always-show-page-title" checkbox should not be checked
