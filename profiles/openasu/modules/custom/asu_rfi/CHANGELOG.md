# ASU Request for Information Changelog

### ASU RFI 7.x-3.5, 2020-10-19
Online campus selections for WPCarey no longer return a, "Country not selected", error.

### ASU RFI 7.x-3.4, 2020-06-17
- Updating from version 1.15 or older will now delete all locally-saved RFI submissions older than 45 days to prevent the
  creation of duplicate contacts in Salesforce.

### ASU RFI 7.x-3.3, 2020-06-09
- The RFI module settings now correctly block the resubmissions of older, locally-saved RFI submissions as originally intended.
- Locally-saved copies of RFI submissions are now deleted 45 days after their initial submission, up from 14 days.
- Added option to manually set the RFI submission retention time.
- Standalone RFI forms now auto-update the campus options based on the degree selected.

### ASU RFI 7.x-3.2, 2020-05-28
- Fixed issue that was blocking the processing of production RFI submissions on sites hosted outside the ASU network
 (e.g., Pantheon hosted sites). All RFI form submissions once again submit to the RFI middleware when the module is set
  to production mode. Those submissions that had their status incorrectly set to ‘CANCELLED’ will be resubmitted and sent
  onto the middleware with the next cron run.

### ASU RFI 7.x-3.1, 2020-05-15
- Reverted changes to test mode in the previous release that broke the RFI module's ability to 1) source the term start
  dates, campuses, countries, and states option lists, and 2) submit test submissions for non production websites hosted
  outside the ASU network. Test mode works again as expected in those cases
- Updated the RFI Submission Status field labels/values to better differentiate between Salesforce integration and middleware
  integration
- Updated documentation in both the README.md file and the RFI settings form to reflect these changes
- The Online campus, "not yet online", error (visible only to administrators) now defaults to hidden -
  and can be toggled on/off in the RFI. The error's purpose has also been clarified in its own messaging.
- Updated, "This is in TEST MODE", messaging above forms when the site is in test mode
- Added error logging for when the Online campus programs feed is not working

- RFI configuration page improvements/fixes
    * Added new categories and moved existing settings, moved and collapsed rarely-used options at the bottom of the
      settings page to improve end-user experience
    * Added separate middleware environment selection option to the RFI configuration page for use within the ASU enterprise
      environment
    * Added basic ASU Enterprise webhosting availability checking for determining what middleware is available
    * Added new "None" option (on top of Test vs. Production) to allow no middleware delivery at all and to improve the
      submission posting code for better performance and organization

### ASU RFI 7.x-3.0, 2020-04-07
#### Major overhaul of the entire module
##### Architecture & Development

- Refactored and/or consolidated many functionally duplicitous functions and files
- Fixed the naming convention of configuration variables and private PHP functions to match Drupal standards
- Removed unused configuration variables
- Created Fun Logger (flogger) module to improve the developer debugging experience
- Added internal documentation/comments for developers
- Required EntityReference_autocomplete contrib module as a dependency
- Updated Multiblock contrib module (v1.6) plus other patches
- Integrated the Queue API to queue larger middleware submission related tasks (to avoid web page timeouts)
- Utilized drupal_static for performance improvements
- Added UNDERGRAD/GRAD constants for universal module use.
- Added "Delete RFI submissions" permission for RFI submissions report operations
- Integrated usage of the Database API
- Utilized the Batch API to update existing data for the code and UI changes.
- Combined comparable RFI form element generation into single location to maintain element consistency between
  form types
- Moved many form customizations from hook_form_alter into the initial form generation logic so AJAX rendering
  would consistently work

##### More bug fixes

- Updated deprecated PHP code to PHP 7.x standards
- The Request Info button now correctly chooses when and how to point to existing RFI forms
- RFI multiblock instance settings now correctly save for grad RFI forms when all majors are wanted for a single RFI form block
- Fixed multiblock ID issues.
- Fixed instance settings for multistep RFI form blocks
- Fixed JSON feed URL to ASUOnline program data sources (also forces an HTTPS connection)
- Added endpoint availability detection to avoid hanging a site while attempting to POST submissions to unavailable middleware
- Added try/catch to cURL calls for graduate RFI posts to middleware
- Re-added limited integration with deprecated ASU Degrees module-generated degrees pages
- Fixed state and country form field logic
- Refactored the CSS, JS (ECMAScript v1.6+) and added other module theming improvements

##### UI/UX Improvements

- RFI submission reports page improvements
    * Updated RFI submission status value options, and improved the related help text
    * Reorganized the report's columns to put more relevant data up towards the front
    * Improved the messaging of the submission's current status for end users
    * Added a "Delete submissions" bulk operation option
    * Cleaned up the view's theming

- RFI configuration page improvements/fixes
    * Added easier to find "RFI settings" admin menu link under "Configuration"
    * Reorganized the configuration form items into categories
    * Added dynamic messaging about middleware auth key status
    * Inserted Online campus URL feed field for future update flexibility
    * Confirmation pages can now be selected via autocomplete based on the page's title
    * The automatic resubmission of failed RFI submissions and the deletion of qualifying RFI submissions (both via cron jobs) can be toggled on/off

- Form improvements
    * The major is now chosen automatically regardless of the RFI form type (works for both undergrad and graduate programs)
    * Added missing form field validation to email, phone number, and email fields
    * RFI blocks now display error messages (to admins only) with helper instructions for when the form isn't rendering within a correctly placed block on a degrees page
    * Added AJAX-powered, dynamic start term options generation for graduate degrees, based on degree and campus selections
    * Updated ASU campus list options
    * Added better, "this program is not available", logic
    * Removed 'align="left|right|center"' <td> tag properties to improve accessibility.

- Updated README documentation for end users

##### Data Management

- Updated RFI submission deletion policies to adhere to the University Data Handling Standard.
    * Upon updating the module to this version, all submissions older than 14 days old upon updating the module, regardless of status
    * All submissions that have successfully been sent onto any Salesforce middleware are deleted upon every cron run
    * All submissions that have not been sent on (status SF_Failed) are resubmitted every time a cron job runs
    * All submissions that have failed for 14 days past the initial submission date are deleted at the next cron run - regardless of their status

---

### ASU RFI 7.x-1.16, 2019-10-04
- Fixed PHP 7.x compatibility issues/warnings
- More refactoring of code

### ASU RFI 7.x-1.15, 2019-08-02
- Fixed file permissions (755 to 644) for PHP files
- Refactored and reduced code for form widgets with pre-populating values/options
  (states, countries, semester dates)

### ASU RFI 7.x-1.14, 2019-02-25
- Update RFI confirmation email wording
- Fix undefined index notice generated by RFI graduate programs

### ASU RFI 7.x-1.13, 2018-07-17
- Syntax updates to make compatible with PHP 7. Credit to Jeremy Leggat,
  Cronkite School IT.

### ASU RFI 7.x-1.12, 2018-07-17
- Update Lead API Programs URL
- Update Lead API submissions to Lead API 4.0 and handling to support.

### ASU RFI 7.x-1.11, 2018-05-24
- Add RFI-specific jQuery to module instead of Innovation theme
- Fix program name text when email is rendered and sent
- Fix up the changelog

### ASU RFI 7.x-1.10, 2018-05-09
- Amended RFI module logic to better behave with ASU Academic Programs module
  after switching from ASU Degrees

### ASU RFI 7.x-1.9, 2018-03-15
- Removed ASU Degrees dependency
- Removed ASU Feeds dependency
- Added degree mappings helper function
- Changed degree variables to use degree mappings helper function
- Added initial support for ASU Academic Programs (make sure to
  read the upgrade instructions before applying this update)

### ASU RFI 7.x-1.8, 2017-03-02
- Add missing ->save() calls on the failed lead submission status
  transitioning.
- Fix value used on "action_required" leads to match what's configured.

### ASU RFI 7.x-1.7, 2016-10-15
- Fixing EdPlus API call
- Increased "college_name" size on RFI forms
- Increased text limit for "From" email field
- Updated the auto-response email

### ASU RFI 7.x-1.6, 2016-08-31
- Implemented new location functionality
- Added new Web Standards styling to the forms
- The RFI now supports requests for Online degree information from EdPlus
- Fixed a bug causing a white screen after some graduate submissions
- Fixed the logic behind the Graduate submission routing.

### ASU RFI 7.x-1.5, 2016-07-15
- Fixed a typo in the auto-response email

### ASU RFI 7.x-1.4, 2016-04-15
- Implementing updated email templates for both grad and undergrad submissions
- fixing grad environment check
- Updating queue handling to better prevent duplicate submissions
- Changing the way that the URL is grabbed for submissions

### ASU RFI 7.x-1.3, 2016-04-15
- Adding Salesforce tracking code to the first part of the multistep form.

### ASU RFI 7.x-1.2, 2015-07-27
- Updated module to send message to middleware upon App key request.
— Updated module to show error log message to admins upon form submission failure if the connection between middleware and the form is lost.
- Added “Action require” status term to ASU RFI Submissions cck field.
- Updated the module to send pending submissions to middleware only once and alert site admins of failed submissions.
- Added Google analytics tracking code.
- Enhanced RFI lead submissions view to include search by students email or last name.
- Fixed “uncaught error” message in Jquery file.
- Added CSS to Date of birth modal message box
- Fixed some upper case and lower case field names.

### ASU RFI 7.x-1.1, 2015-05-15
- Updated form mode variable value
- Updated RFI module link settings
- Updated title of ASU RFI settings menu
- Added the ability to add customized confirmation node ids for Grad RFI form and Undergrad RFI form (if both exist in the site) on the admin settings page.

### ASU RFI 7.x-1.0, 2014-11-15
- Initial release
