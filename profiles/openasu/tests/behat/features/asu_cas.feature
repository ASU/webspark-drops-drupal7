@api
Feature: ASU CAS
  In order to have consistency
  I need to test that ASU CAS uses
  ASURITE User ID language instead of CAS username

  Scenario: Admin user adds ASURITE user
    Given I am logged in as a user with the "administrator" role
    And I am on "/admin/people"
    And I click on "Add ASURITE User"
    Then I should see "Registration will proceed as if the user with the specified ASURITE User ID just logged in."
    And I filli n " for "ASURITE User ID"

  Scenario: User can request a new password if it has been lost
    Given I am on "/user/1/edit"
    Then I should not see "CAS username"
    And I should see "ASURITE User ID"
