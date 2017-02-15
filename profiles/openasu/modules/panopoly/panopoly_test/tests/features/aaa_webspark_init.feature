Feature: Alter standard Webspark settings for testing
  In order to run tests without being interrupted by Javascript popups
  As a site administrator
  I need to be able to turn off GTM includes

  @api @webspark_added @webspark_init
  Scenario: Turn off ASU Brand module extras for CI testing
    Given I run drush "vset asu_brand_ci_testing 1"
    Then drush output should contain 'asu_brand_ci_testing was set to "1"'
