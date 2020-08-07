Feature: Link to page on the site
  In order to create links to my pages
  As a site builder
  I need to be able to use the Linkit function

  Background:
    Given I am logged in as a user with the "administrator" role
      And a "panopoly_test_page" with the title "Linkit Target"
    When I visit "/admin/appearance/settings/innovation"
      And I check the box "edit-always-show-page-title"
      And I press "edit-submit"
      And I visit "/node/add/panopoly-test-page"
      And I fill in the following:
        | Title  | Testing Linkit       |
        | Editor | panopoly_wysiwyg_text |

  @api @javascript @panopoly_wysiwyg @webspark_broken @webspark_ignore
  Scenario: Add a link to an internal page
    When I click the "Link to content" button in the "edit-body-und-0-value" WYSIWYG editor
      And I wait 1 seconds
      And I fill in "edit-linkit-search" with "Target"
      And I wait 1 seconds
      And I press the "Tab" key in the "edit-linkit-search" field
    When I click "Options" in the "Linkit modal" region
      And I fill in "edit-linkit-title" with "Testing title"
      And I wait 1 seconds
    # BROKEN - Linkit autocomplete doesn't fire during testing (works manually)
      And I press "Insert link"
      # Normally, here we'd press "Publish", however some child distribtions
      # don't use 'save_draft', and this makes this test compatible with them.
      #And I press "Publish"
      And I wait 1 seconds
      And I press "edit-submit"
    Then I should see "Linkit Target" in the "a" element with the "title" attribute set to "Testing title" in the "Burr Flipped Content" region
    When I click "Linkit Target"
    Then I should see "Linkit Target"

  @api @javascript @panopoly_wysiwyg
  Scenario: Add a link to an external page
    When I click the "Link to content" button in the "edit-body-und-0-value" WYSIWYG editor
      And I fill in "edit-linkit-path" with "https://drupal.org/project/panopoly"
      And I click "Options" in the "Linkit modal" region
      And I fill in "edit-linkit-title" with "Testing title"
      And I press "Insert link"
      # Normally, here we'd press "Publish", however some child distribtions
      # don't use 'save_draft', and this makes this test compatible with them.
      #And I press "Publish"
      And I press "edit-submit"
    Then I should see "https://drupal.org/project/panopoly" in the "a" element with the "title" attribute set to "Testing title" in the "Bryant Content" region
      And I should see "https://drupal.org/project/panopoly" in the "a" element with the "href" attribute set to "https://drupal.org/project/panopoly" in the "Bryant Content" region

  @api @panopoly_admin @webspark_added
  Scenario: Resetting the Innovation theme Always Show Page Title setting
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled
    When I visit "/admin/appearance/settings/innovation"
      And I uncheck the box "edit-always-show-page-title"
      And I press "edit-submit"
      And I visit "/admin/appearance/settings/innovation"
    Then the "edit-always-show-page-title" checkbox should not be checked
