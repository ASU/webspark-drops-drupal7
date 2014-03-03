Feature: Anonymous user login
In order to access content for authenticated users
As an anonymous user
I want to be able to login

  Scenario: Admin user is able to login
    Given I am on "/user"
    When I fill in "admin" for "edit-name"
    And I fill in "admin" for "edit-pass"
    And I press "Log in"
    Then I should see "Log out"

  Scenario: User can request a new password if it has been lost
    Given I am on "/user/login"
    Then I should see "If you forgot your password, request a new password."
    #When I click "request a new password"
    #Then I should see "Request new password"
    #When I fill in "admin" for "name"
    #  And press "E-mail new password"
    #Then I should see "Further instructions have been sent to your e-mail address."
    #  And I should see "Log in"
