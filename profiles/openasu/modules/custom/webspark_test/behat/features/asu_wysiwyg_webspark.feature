Feature: Use rich text editor
  In order to format the content of my pages
  As a site builder
  I need to be able to use a WYSIWYG editor

  Background:
    Given I am logged in as a user with the "administrator" role
    When I visit "/node/add/panopoly-test-page"
    And I fill in the following:
      | Title  | Testing WYSIWYG       |
      | Editor | panopoly_wysiwyg_text |

  @api @javascript @panopoly_wysiwyg @webspark_added
  Scenario Outline: Format text with Webspark-specific styles in the WYSIWYG editor
    When I click the "<Styles>" element identified by the "id" attribute in the "edit-body-und-0-value" WYSIWYG editor
    # For the 'Oval image' option, the padding on the <a> tag for the option was causing the behat ->click() operation to
    # to mistarget, resulting in the style being highlighted but not actually applied. The fix for now is to remove
    # the padding via targeted css in the webspark_seven.css file:
    # .page-node-add-panopoly-test-page .cirkuitSkin .mceMenu { padding: 0; }
    # UPDATE: The Oval image is a deprecated style and has been removed.
    And I click the "<Styling>" option in the opened "Styles" WYSIWYG editor drop down list
    And I type "Testing element" in the "edit-body-und-0-value" WYSIWYG editor
      #And I press "Publish"
    And I press "edit-submit"
    Then I should see "Testing element" in the "<Element>" element with the "<Attribute>" attribute set to "<Value>" in the "Bryant Content" region

    Examples:
      | Styles                                  | Styling                           | Element  | Attribute | Value     |
      | edit-body-und-0-value_styleselect_text  | Image align left                  | p        | class     | pull-left |
      | edit-body-und-0-value_styleselect_text  | Lead paragraph                    | p        | class     | lead-paragraph |
      | edit-body-und-0-value_styleselect_text  | Image align right                 | p        | class     | pull-right |
      | edit-body-und-0-value_styleselect_text  | Image with rounded corners        | p        | class     | img-rounded |
      | edit-body-und-0-value_styleselect_text  | Image with double-border          | p        | class     | img-thumbnail |
      | edit-body-und-0-value_styleselect_text  | Maroon button                     | p        | class     | btn btn-primary |
      | edit-body-und-0-value_styleselect_text  | Gold button                       | p        | class     | btn btn-gold |
      | edit-body-und-0-value_styleselect_text  | Black button                      | p        | class     | btn btn-black |
      | edit-body-und-0-value_styleselect_text  | Gray button                       | p        | class     | btn btn-secondary |
      | edit-body-und-0-value_styleselect_text  | Lead paragraph                    | p        | class     | lead-paragraph |
      | edit-body-und-0-value_styleselect_text  | Alert text success                | p        | class     | alert alert-block alert-success |
      | edit-body-und-0-value_styleselect_text  | Alert text warning                | p        | class     | alert alert-block alert-warning |
      | edit-body-und-0-value_styleselect_text  | Button Disabled                   | p        | class     | ws2-element-style btn btn-disabled |
      | edit-body-und-0-value_styleselect_text  | Alert text danger                 | p        | class     | alert alert-block alert-danger |
      | edit-body-und-0-value_styleselect_text  | Alert text info                   | p        | class     | alert alert-block alert-info |

