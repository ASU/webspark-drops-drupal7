Feature: Add image widget
  In order to add an image to page
  As a site administrator
  I need to be able to use the image widget
 
  @api @javascript @panopoly_widgets @local_files @webspark_broken @webspark_fixed
  Scenario: Add a image
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled
      And I am viewing a landing page
    When I customize this page with the Panels IPE
      And I click "Add new pane"
      And I click "Add responsive image" in the "CTools modal" region
    Then I should see "Configure new Add responsive image"
    When I fill in the following:
      | Title   | Testing image widget title |
      | Editor  | plain_text                 |
      | Caption | Testing caption            |
      And I attach the file "test-sm.png" to "files[field_basic_image_image_und_0]"
      And I press "Upload"
      And I fill in "Alternate text" with "Testing alt text"
      And I press "Save" in the "CTools modal" region
      And I press "Save"
      And I wait for the Panels IPE to deactivate
    Then I should see "Testing image widget title"
      And I should see "Testing caption"
      And I should see the image alt "Testing alt text" in the "Boxton Content" region
      And I should not see the link "Testing alt text" in the "Boxton Content" region

  @api @javascript @panopoly_widgets @local_files
  Scenario: Add an image with link
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled
      And I am viewing a landing page
    When I customize this page with the Panels IPE
      And I click "Add new pane"
      And I click "Add responsive image" in the "CTools modal" region
    Then I should see "Configure new Add responsive image"
    When I fill in the following:
      | Title   | Testing image widget title              |
      | Editor  | plain_text                              |
      | URL     | https://www.drupal.org/project/panopoly |
      And I attach the file "test-sm.png" to "files[field_basic_image_image_und_0]"
      And I press "Upload"
      And I fill in "Alternate text" with "Testing alt text"
      And I press "Save" in the "CTools modal" region
      And I press "Save"
      And I wait for the Panels IPE to deactivate
    Then I should see "Testing image widget title"
      And I should see the image alt "Testing alt text" in the "Boxton Content" region
      And I should see the link "Testing alt text" in the "Boxton Content" region
    When I follow "Testing alt text" in the "Boxton Content" region
    Then the url should match "/project/panopoly"

  # TODO: we use the @panopoly_wysiwyg tag because that is where Linkit comes
  #       from in a default install.
  @api @javascript @panopoly_widgets @panopoly_wysiwyg
  Scenario: Add an image with Linkit support
    Given I am logged in as a user with the "administrator" role
      And Panopoly magic live previews are disabled
      And I am viewing a landing page
    When I customize this page with the Panels IPE
      And I click "Add new pane"
      And I click "Add responsive image" in the "CTools modal" region
    Then I should see "Configure new Add responsive image"
    When I click "Search for existing content" in the "CTools modal" region
    Then I should see "Linkit"

