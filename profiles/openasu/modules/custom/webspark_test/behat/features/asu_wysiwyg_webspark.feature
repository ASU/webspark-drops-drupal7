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
    # the padding via targeted css in the  webspark_seven.css file:
    # .page-node-add-panopoly-test-page .cirkuitSkin .mceMenu { padding: 0; }
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
      | edit-body-und-0-value_styleselect_text  | Oval image                        | p        | class     | img-circle |
      | edit-body-und-0-value_styleselect_text  | Image with rounded corners        | p        | class     | img-rounded |
      | edit-body-und-0-value_styleselect_text  | Image with double-border          | p        | class     | img-thumbnail |
      | edit-body-und-0-value_styleselect_text  | Primary button                    | p        | class     | btn btn-primary |
      | edit-body-und-0-value_styleselect_text  | Primary button large              | p        | class     | btn btn-primary btn-lg |
      | edit-body-und-0-value_styleselect_text  | Primary button full-col-wide      | p        | class     | btn btn-primary btn-block |
      | edit-body-und-0-value_styleselect_text  | Primary button large col-wide     | p        | class     | btn btn-primary btn-lg btn-block |
      | edit-body-und-0-value_styleselect_text  | Secondary button                  | p        | class     | btn btn-secondary |
      | edit-body-und-0-value_styleselect_text  | Secondary button large            | p        | class     | btn btn-secondary btn-lg |
      | edit-body-und-0-value_styleselect_text  | Secondary button full-col-wide    | p        | class     | btn btn-secondary btn-block |
      | edit-body-und-0-value_styleselect_text  | Secondary button large col-wide   | p        | class     | btn btn-secondary btn-lg btn-block |
      | edit-body-und-0-value_styleselect_text  | RFI/Visit/Apply (RVA) button      | p        | class     | btn btn-gold |
      | edit-body-und-0-value_styleselect_text  | RVA button large                  | p        | class     | btn btn-gold btn-lg |
      | edit-body-und-0-value_styleselect_text  | RVA button full-col-wide          | p        | class     | btn btn-gold btn-block |
      | edit-body-und-0-value_styleselect_text  | RVA button large col-wide         | p        | class     | btn btn-gold btn-lg btn-block |
      | edit-body-und-0-value_styleselect_text  | Explore Our Programs (EOP) button | p        | class     | btn btn-blue |
      | edit-body-und-0-value_styleselect_text  | EOP button large                  | p        | class     | btn btn-blue btn-lg |
      | edit-body-und-0-value_styleselect_text  | EOP button full-col-wide          | p        | class     | btn btn-blue btn-block |
      | edit-body-und-0-value_styleselect_text  | EOP button large col-wide         | p        | class     | btn btn-blue btn-lg btn-block |