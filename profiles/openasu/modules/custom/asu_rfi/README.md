DESCRIPTION
--------------------------
The ASU RFI module provides ASU sites with RFI form functionality with
automatic posting to ASU's SalesForce middleware.

INSTALLATION
--------------------------
Prerequisites: ASU Degrees and ASU Degrees Features modules.
And others. See the .info files. Of note are the Multiblock and 
Ajax Block modules. 

In order to avoid a per-instance bug with the Multiblock module where it
forgets settings, you should apply the patch in comment #5 on:
https://www.drupal.org/node/1370966#comment-6408056
If you are using WebSpark, that patch is already in place.

Now you're ready to install the ASU RFI module along with the ASU RFI Feature
module. Enable the modules as usual, see http://drupal.org/node/70151 for
further information.

CONFIGURATION
--------------------------
In order to populate the program/degree options in the RFI forms, you must
use the ASU Degrees module to import degree programs into your site. See that
module's README.txt for more information.

Post installation, the ASU RFI module requires configuration in order to post
to the middleware and deploy the forms throughout your site.

GENERAL CONFIGS: 

General sitewide RFI settings are made at /admin/config/asu/asurfi.
To use the middleware, you must obtain an authentication key from
https://webforms.asu.edu/content/access-rfi-middleware-request
If you deploy forms to your site without an authentication key configured,
your site will collect lead submissions but not submit them to middleware.

The Google Analytics identifier is a short string you choose yourself, and
which will show up in ASU's Google Analytics reports, to help diffrentiate
your entries from other sites.

The Confirmation Web Page settings allows you to provide the Node ID (NID)
of a page you've created, from which to obtain confirmation/thank you content.
The content used will come from that page's body.

View the forms stored in your site at
/admin/reports/asu-rfi-submissions-report
From this Views Bulk Operation view of lead submissions, you can see which
submissions have succeeded or failed, resubmit failed leads to the middleware
and export leads to CSV.

RFI FORM DEPLOYMENT AND CONFIGS: 

RFI forms are deployed to your site via the Drupal blocks system, with help
from the Multiblock module.

How it works: The ASU RFI module provides a master block titled "RFI Master."
Browse to Admin > Structure > Blocks > Instances. The Mutiblock Instances page
allows you to create a copy, or "instance," of the RFI Master block, to use
in creating individual RFI form blocks for use in your site. You can create
as many instances of the RFI Master block as you want - giving them descriptive
names, to aid in administration. Once you've created an instance, it will
appear in the main blocks admin page (Admin > Structure > Blocks), where you
can deploy it to regions in your theme, apply access controls, etc. If your
site uses Panopoly/Panels/WebSpark, RFI forms can be assigned to panels in
the site through that interface.

Each RFI block instance has its own independent settings, configurable through
Admin > Structure  > Blocks > [your block] Configure. It's here where you
define which form type to use (multistep, undegraduate long form, graduate
long form, current undergraduate form, current graduate form). Some of the
form types automatically define which programs will be listed in the form
while others allow you to manually determine the program options.

IMPORTANT NOTE: If you use caching in your site, RFI form blocks configured so
they automatically detect context and determine which programs to display can
get cached and display incorrect options. To avoid this issue, enable the Ajax
Block module, and on the block configuration page, set the block to load via
Ajax. That means an un-cached copy of the form will be added to the page via
Javascript after the cached page loads. This occurs very quickly and doesn't
affect the user experience to any great degree.

PERMISSIONS
--------------------------
'Administer ASU RFI module' - access the module's admin.

Additional access and permissions considerations to the RFI forms themselves
can be managed through the Drupal blocks system's access controls.

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

TABLES
--------------------------

BLOCKS
--------------------------
RFI Master block - do not use. 
Create Block Instances for individual RFI forms based off the RFI Master
block.

HOOKS
--------------------------
Provides none.

CREDITS
--------------------------
ASU RFI module was created by
Archana Puliroju <apuliroj@asu.edu> and
Michael Samuelson <mlsamuel@asu.edu>
