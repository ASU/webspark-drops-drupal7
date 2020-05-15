PREAMBLE
--------------------------
Definitions to know before reading on:
- Lead - Prospective student that submits an RFI form.
- Middleware - Centrally located web sites/servers that capture RFI form submissions, process said
submissions, and then forward them to Salesforce.
- Multiform - Multipage RFI form (currently two pages) that breaks the data gathering
into multiple steps.

DESCRIPTION
--------------------------
The ASU RFI module provides ASU sites with RFI form functionality with automatic
posting to ASU's SalesForce middleware. (NOTE: Future versions of this module will connect directly
to SalesForce and skip the middleware.)

INSTALLATION
--------------------------
**Prerequisite Drupal module**: ASU Academic Programs (asu_ap). In order to populate
the program/degree options in the RFI forms, you *must* use the ASU Academic Programs
module to import the available degree programs into your site. While installing
the asu_ap module doesn't have to be done prior to installing this module, the
configuration forms for the RFI forms will not function properly until that
is completed. (See the asu_ap module's README.txt for more information.)

Simply enable the ASU Request for Information (asu_rfi) and ASU RFI feature
(asu_rfi_feature) modules as usual (See http://drupal.org/node/70151 for
further information on enabling Drupal modules).

CONFIGURATION
--------------------------
After installing and enabling the module, the ASU RFI module requires configuration
is required.

### RFI Form deployment & configuration

#### Creating an RFI form block

RFI forms are deployed to your site via the Drupal blocks system, with help
from the Multiblock module.

The ASU RFI module provides a master block titled "RFI Master." You won't use
that block; instead, you will instead create an "instance" (i.e. copy) of that
block that will contain a new, individual RFI form to place in your site.

You can create as many instances of the RFI Master block as you want. (We
recommend giving them descriptive names, to aid in administering them later.)

Go to Admin > Structure > Blocks > Instances (/admin/structure/block/instances).
Under Add Instance, enter a descriptive name and select "RFI Master" for Block type.

#### Adding an RFI form block to web content

Once you've created an instance, it will appear in the main Drupal blocks admin page
(Admin > Structure > Blocks, or /admin/structure/block), where you can deploy it to
regions in your theme, apply access controls, etc.

**For WebSpark (or Panopoly/Panels) users**: RFI forms can also be assigned to
panels in the site through its interface the same way you would add other ASU Web
standards elements.

##### SPECIAL CASE: The Multiform option

The multiform option:

* ..must ONLY be used on an ASU Academic Programs content type page (typically generated
 by the asu_ap module) because it requires that page's academic plan code. The form will
 not autofill certain required form fields without that data.

* ..cannot be added in Panels because it **must** be added to a page-level region called
"Prefooter" or it will not display. Panels only allows the selection of node-level regions
(which are all within the area of the page-level region called "Content"), so the multiform
must be added to pages in that block's configuration form or at Admin > Structure > Blocks.

#### Configuring individual RFI form blocks

Each RFI block instance has its own independent settings, configurable through
Admin > Structure > Blocks > [your block] Configure. It's here where you define which
form type to use (multistep, undegraduate long form, graduate long form, current
undergraduate form, current graduate form).

Some of the form types automatically define which programs will be listed in the form while
 others allow you to manually determine the program options.

For more detailed instructions on configuration, go to
https://brandguide.asu.edu/executing-the-brand/web-and-mobile/webspark/features/asu_rfi.

### Global configuration

Global RFI module settings are at /admin/config/asu/asurfi. Go to that page for usage
instructions. (If this is inaccessible, check to make sure proper permissions are set (see
"Permissions" below.)

Submissions to Salesforce
--------------------------

When RFI forms are successfully submitted by end users (no validation errors, etc.), the
form submission is temporarily saved in the site's database and its status is immediately
set to "Ready for SF POST". (Exception: multipage forms. See below...)

The RFI process isn't over yet, however. During that same submission process (i.e. same HTTP request),
but AFTER the "Ready for SF POST" status has been set (you won't see this setting), the
module immediately attempts to submit a modified version of the submission data to one of
multiple SalesForce middleware servers.

NOTE: Which middleware server used is based on the module's Global settings and the
web site's environment (dev/test or live/production).

If that separate submission to the middleware is also successful, then the process is
truly completed _*for this module*_ - and the status of the form submission is set to "Middleware POST
Successful". (NOTE: The submission still has to be passed into Salesforce by the middleware,
and there is currently no mechanism in the RFI module to tell you if the middleware ->
Salesforce process was successfully completed.)

#### Submission status exception for multistep/multipage forms

When the 1st page of the multiform is submitted by the end user, the submission's status is
set to "Partial Multiform Submitted". This status will remain until either 1) the second
half of the form is also submitted by the end user, or 2) the site's cron job is run. At that time,
the site will try (during the same HTTP request) to submit the submission to the middleware (the
same as above). This will end up with a status of "SUCCESSFUL Middleware POST" or "FAILED Middleware POST"
(when an error is returned by the middleware).

A site administrator will need to resolve the "Middleware POST FAILED" issues and then
re-post/resubmit it manually at /admin/reports/asu-rfi-submissions-report under "Operations".

See /admin/reports/asu-rfi-submissions-report for the list of submissions and their statuses.

#### Deletion of submissions

For privacy/security reasons, RFI form submissions MUST NOT BE STORED in the RFI module's website
beyond an honest attempt to submit the data to Salesforce.

Starting with ASU RFI version 3.0, these submissions will be deleted intermittently by the module
during a cron job if they are not manually deleted by the site administrator.

PERMISSIONS
--------------------------
'Administer ASU RFI module' - access the module's admin.

'Execute ASU RFI VBOs' - Execute ASU RFI VBOs from RFI Submissions view to submit or delete
submission nodes. (This is on top of pre-existing Drupal CRUD permissions for nodes.)

Additional access and permissions considerations to the RFI forms themselves can be managed through
the Drupal blocks system's access controls.

REPORTS
--------------------------
View the RFI form submissions currently stored in your site at
/admin/reports/asu-rfi-submissions-report

From this Views Bulk Operation view of lead submissions, you can see which
submissions have succeeded or failed, resubmit failed leads to the middleware,
and export leads to CSV.

MODULES
--------------------------
Module ships with ASU RFI Feature module.

See .info files for dependencies.

PAGES
--------------------------
Module provides
Admin settings: /admin/config/asu/asurfi

Block and Instances configurations
/admin/structure/block
/admin/structure/block/instances

Listing of submissions and their statuses (a Drupal view called "RFI lead submissions")
/admin/reports/asu-rfi-submissions-report
/admin/content (filter for content type "ASU RFI form submissions")

TABLES
--------------------------
* asu_rfi_states_list - List of states for RFI forms
* asu_rfi_countries - List of countries for RFI forms
* asu_rfi_sem_dates - List of available semester dates

BLOCKS
--------------------------
RFI Master block - *DO NOT USE THIS BLOCK!*

Instead, create Block Instances for individual RFI forms based off the RFI Master block.

HOOKS
--------------------------
None.

TROUBLESHOOTING
--------------------------
#### Known issues

**What do the statuses of forms mean?**
See the explanation of submission statuses at https://_yoursite_.asu.edu/admin/reports/asu-rfi-submissions-report.

**How long does the module wait before deleting completed/expired submissions?**

The submission is currently considered to be expired and marked for deletion at 14 days after the
initial submission.

**Can I keep the submissions because we have a special use case?**

No. They must be deleted for privacy/security reasons. Please use Salesforce instead.

**No available majors are available to select in the block's configuration form.**

Make sure the ASU Academic Programs module is enabled, and that you have imported the desired
degrees/programs. (See that module's README for more information.)

**This module was working with the ASU Degrees module pulling in the desired degrees, but it broke after a Webspark update. What happened?**

The ASU Degrees module has been superseded by the ASU Academic Programs (asu_ap) module. This module no
longer 100% works with the ASU Degrees module. (See the asu_ap module's README for more information.)

**I've updated the degrees in the site, but the new major options aren't appearing in the block's configuration form.**

If you use caching in your site, RFI form blocks configured so they automatically detect context
and determine which programs to display can get cached and display incorrect options. To avoid this
issue, enable the Ajax Block module, and on the block configuration page, set the block to load via
Ajax. That means an un-cached copy of the form will be added to the page via Javascript after the
cached page loads. This occurs very quickly and doesn't affect the user experience to any great degree.

**I'm a non-Webspark user, and the block configurations on RFI form instances are not saving.**

In order to avoid a per-instance bug with the Multiblock module where it forgets settings, you should
apply the patch in comment #5 on: https://www.drupal.org/node/1370966#comment-6408056.) Webspark has
had that patch applied to resolve that issue.

**I don't see my issue listed below, and I've read through the instructions at
https://brandguide.asu.edu/executing-the-brand/web-and-mobile/webspark/features/asu_rfi. What do I do?**

Go to https://drupal.asu.edu/wcs for assistance.

CREDITS
--------------------------
ASU RFI module was created by
Archana Puliroju <apuliroj@asu.edu> and
Michael Samuelson <mlsamuel@asu.edu>

Updated by Bryan Roseberry <aubjr@asu.edu>

Maintained by Development, Applications and Design in the UTO.
