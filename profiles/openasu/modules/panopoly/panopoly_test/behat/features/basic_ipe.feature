Feature: Make basic changes with the IPE
  In order to customize pages
  As a site administrator
  I need to be able to manipulate them with the IPE

  Background:
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled
    When I visit "/node/add/panopoly-test-page"
    And I fill in the following:
      | Title  | Basic IPE Testing title |
      | Editor | plain_text    |
      | Body   | Basic IPE Testing body  |
    And I press "edit-submit"
    Then I should see "Basic IPE Testing title"

  @api @javascript @webspark_broken @webspark_fixed
  Scenario: Change layout
    When I change layout with the Panels IPE
      And I click "Phelan"
      And I press "Save" in the "CTools modal" region
      And I wait for the Panels IPE to deactivate
    Then I should see "Testing title"
