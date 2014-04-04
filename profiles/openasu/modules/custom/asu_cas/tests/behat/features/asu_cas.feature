@api
Feature: ASU CAS Admin UI
  As an admin
  When I edit or add users
  I need to see ASURITE User ID and not CAS username


  Scenario: Admin user adds ASURITE user
    Given I am logged in as a user with the "administrator" role
    And I am on "/admin/people"
    And I click "Add ASURITE User"
    Then I should see "Registration will proceed as if the user with the specified ASURITE User ID just logged in."

  Scenario: Admin
    Given I am logged in as a user with the "administrator" role
    Given I am on "/user/1/edit"
    Then I should not see "CAS username"
    And I should see "ASURITE User ID"
