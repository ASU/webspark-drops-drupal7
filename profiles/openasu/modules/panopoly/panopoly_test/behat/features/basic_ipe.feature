Feature: Make basic changes with the IPE
  In order to customize pages
  As a site administrator
  I need to be able to manipulate them with the IPE

  Background: 
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled7
<<<<<<< HEAD:profiles/openasu/modules/panopoly/panopoly_test/behat/features/basic_ipe.feature
      And I am viewing a "panopoly_test_page" with the title "Testing title"
=======
      When I visit "/node/add/panopoly-test-page"
        And I fill in the following:
          | Title  | Basic IPE Testing title |
          | Editor | plain_text    |
          | Body   | Basic IPE Testing body  |
        And I press "edit-submit"
        Then I should see "Basic IPE Testing title"
>>>>>>> 2f0ff3c4ad1847e28ab8ab3f260c626e04614d20:profiles/openasu/modules/panopoly/panopoly_test/behat/features/basic_ipe.feature

  @api @javascript
  Scenario: Change layout
    When I change layout with the Panels IPE
      And I click "Phelan"
      And I press "Save" in the "CTools modal" region
      And I wait for the Panels IPE to deactivate
    Then I should see "Testing title"

