Feature: Restore standard Webspark settings after testing
  In order to restore site to normal operations
  As a site administrator
  I need to be able to turn back on GTM includes

  @api @webspark_added @webspark_exit
  Scenario: Turn off ASU Brand module extras for CI testing
    Given I run drush "vset asu_brand_ci_testing 0"
    Then drush output should contain 'asu_brand_ci_testing was set to 0'
