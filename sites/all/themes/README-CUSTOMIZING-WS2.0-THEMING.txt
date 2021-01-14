#######################
Creating a Subtheme for College (the new Web standards 2.0 theme)

------------------------------------------------------------------------------------------------
PLEASE READ BEFORE GETTING STARTED!!
* While we may be able to assist with issues that occur on a very limited scale, UTO does NOT officially support
subthemes, and UTO will not responsible for any breakage that may occur to web sites using subthemes when Webspark
distribution updates are made and pushed out in the Webspark distribution.
We therefore highly recommend not creating a subtheme unless you have a plan in place to maintain the subtheme and keep
it up-to-date and working with Webspark without free UTO support.
IF YOU HAVE READ THE ABOVE AND UNDERSTAND THE IMPLICATIONS/RISKS INVOLVED, AND WANT TO CREATE A SUBTHEME, READ ON...
------------------------------------------------------------------------------------------------

-----------
Q: What is a subtheme?
-----------
A: Subthemes in Drupal are child themes that inherit certain attributes from its parent theme. This allows you to
use an established theme as a base theme and derive layouts/styles from it in the subtheme on the same site,
without needing to alter or duplicate the original theme.
In this case, you will be creating a subtheme of the new College theme (which is itself a subtheme of Kalatheme).
-----------
Q: Who needs to do this?
-----------
A: Anyone who wants to customize College's look/feel and plans on applying those changes as code (CSS files, template/layout
files, etc.), via SFTP or Git. Any theming customizations stored inside the DB is not affected.
-----------
Q: Why can't I just edit the existing College theme in /profiles/openasu/themes for my custom theme changes?
-----------
A: Any changes applied to any files or folders in the /profiles directory (including the Webspark theme folder
in /profiles/openasu/themes) may be overwritten EVERY TIME UTO updates Webspark and those changes are subsequently
applied by site admins in the Pantheon Dashboard.
These updates are important because they will sometimes include security updates to Drupal core, so they shouldn't be avoided.
To apply changes to the theme that will persist, they need to be made in a new and distinct subtheme of the
College subtheme, which makes it a "sub-subtheme":
Kalatheme   ->   College   ->   Your New Sub-Subtheme
(base theme)     (sub theme)       (sub sub theme)
This new sub-subtheme will inherit the settings/styles of its parent themes, and again, the subtheme directory MUST be
placed in /sites/all/themes.
-----------
Q: How do I do this?
-----------
A: Two different methods are laid out below, with step-by-step instructions below.

###########
Creating a Subtheme.
###########

NOTE: Any name can be chosen for the subtheme, but for purposes of this document the subtheme will be named
"college_sub".

1. In the Pantheon Dashboard in the Code section, Switch the Connection Mode to SFTP. (If left in Git mode, a ZIP file
   of an incorrectly configured subtheme will be generated.)
2. In the development site's navbar men, click Menu, and then click Appearance.
3. Click "Set Default" next to the Kalatheme theme.
4. Under Menu, click Configuration, then Performance, then Clear all Caches.
5. Under Menu, click Appearance. At the bottom of the page under Administrative Theme select Kalatheme from the
   dropdown box and click Save Configuration. (This will make the appearance of the admin area of your site appear to be a little broken/odd but it is nothing to worry about. This will be corrected later in this process.)
6. If another theme is still enabled as the subtheme (ex. "College, etc."), click Disable under that theme.
7. Click "Setup Kalatheme" at the top of the page. (If this link is not there, verify that Steps 4-6 were all done.)
8. Name your theme, using lowercase letters and underscores (we recommend something like college_sub, but your choice will
   be referred to as "college_sub" for the rest of these steps). Select "College" from the dropdown under Subtheme Base.
   Leave all other settings the same and click 'Dress me up'. When this step has completed, your subtheme has been
   selected but there's still work to do.
9. On your Pantheon Dashboard in the Code section, click Commit. (If you don't see a message saying there are 'X file
   changes' and the Commit button is grayed out, refresh the Code page.

--If you are using Git:
10. In your Pantheon Dashboard, Switch the Connection Mode to Git and pull the changes.
11. In your IDE, copy the newly created theme folder (college_sub) from profiles/openasu/themes
    to sites/all/themes.
12. Copy the /profiles/openasu/libaries/college_bootstrap folder contents into the newly created
    directory /sites/all/libraries/college_sub_bootstrap. (NOTE: Be sure to NOT re-use the Innovation version of the
    bootstrap library.)
13. Copy the regions section from profiles/openasu/themes/college.info into the new subtheme's
    (college_sub) .info file to make the same regions available in the subtheme.
14. (Optional) To retain Webspark's custom styling, copy the following files from left to right:
    - /profiles/openasu/themes/college/images/* -> /sites/all/themes/college_sub/images/
15. Commit all changes and push them to Pantheon.

--If you are using SFTP (with /code as the web root folder):
10. Pull all of the newly created files via SFTP down to your local copy of the site. (Should be two folders:
    <webRootDir>/profiles/openasu/themes/college_sub and
    <webRootDir>/sites/all/libraries/college_sub_bootstrap.)
11. Copy the newly created theme folder (college_sub) from profiles/openasu/themes
    to sites/all/themes.
12. Copy the contents of /profiles/openasu/libaries/college_bootstrap/ into newly created
    college_sub_bootstrap directory in /sites/all/libraries. (NOTE: Be sure to NOT re-use the Innovation version of the
    bootstrap library.)
13. Copy the regions, features, settings, and panel layout sections from profiles/openasu/themes/college/college.info
    into the new subtheme's (college_sub) .info file to make the same regions available in the subtheme.
14. Copy the favicon.ico from /profiles/openasu/themes/college to /sites/all/themes/collegecustom
15. (Optional) To retain College's custom styling, copy the following files from left to right:
    - /profiles/openasu/themes/college/images/* -> /sites/all/themes/college_sub/images/.
16. Push file changes back to Pantheon and commit all changes in the Pantheon Dashboard.

-- Continuing steps for both Git and SFTP users:
17. Clear all caches (see Step 4).
18. If the ASU Brand module (places the global ASU headers/footers) is being used, go to Menu, click Structure,
    then click Blocks.
    The following blocks need to be enabled as follows (block name -> region):
    -- WS2.0: Header -> Header (at the top of all blocks)
    -- System help -> Header, below WS2.0: header
    -- TB Mega Menu: Main menu -> Menu
    -- Mega Footer -> Footer (Most sites use the Mega Footer, some do not)
    -- WS2.0: Footer -> Footer (at the bottom of all blocks)
    (The ASU Brand footer shouldn't be needed for the College theme.)
    Be sure to click Save Blocks at the bottom of the page.
    (If these regions are not available to you, check Step 13 above.)
19. Clear all caches.
20. Go to Appearance. Click "Set Default" for Kalatheme. Then click "Disable" for college_sub.
21. Delete the /profiles/openasu/themes/college_sub folder and its contents, and then using either the Git
    or SFTP workflow, commit and push up the code changes to Pantheon.
22. Clear all caches.
23. Go to Appearance.
24. Click "Enable and Set Default" for college_sub.
Your new subtheme should be now ready to use and customize in /sites/all/themes/college_sub.
***Note - If you already had a subtheme when using the Innovation theme, copy over all appropriate .tpl files and .css files from the Innovation subtheme into your new college_sub directory.  Keep in mind you may need to alter some of the code in hte files to match the new code in the College theme files.
You can also now set the administrative theme back to the default (usually Webspark Seven). (If you want to
repeat this process, you will need to set Kalatheme as the administrative theme again.)

-----------
Locally creating a subtheme using Drush.
-----------
1. On your Pantheon Dashboard in the Code section, switch the Connection Mode to SFTP.
2. If the /sites/all/libraries directory hasn't been created yet locally, create it now. Ensure that folder exists wherever
   the subtheme is being created.
3. In your local copy, go to web's base directory (Drupal root).
4. Enter the CLI command: drush kalatheme "yoursubthemename" --strict=0
   We recommend something like college_sub, but this is up to you.
5. Once the subtheme is created, see Steps 13-14 and 16-18 from "Creating a Subtheme" for adding the ASU
   customization (CSS styling from Webspark, adding regions & header/footer blocks). Commit the changes and push up to
   Pantheon. The new subtheme will now be available to select on your site's Appearance page.

-----------
Q. Do I need to keep the broken-looking Kalatheme as the administrative theme after this is done?
-----------
A. No - You should set that back to the Webspark Seven theme (recommended) or your default WS2.0 theme (college or
subtheme) for the administrative theme (at yoursite.asu.edu/admin/appearance). If you want to repeat this process, you
will need to set Kalatheme as the administrative theme again.
-----------
Q. Where is there more info on this process or subtheming with Kalatheme?
-----------
A. While you should never have to touch the Kalatheme theme, below are links to the Drupal.org page for the Kalatheme subtheme you will be using along with some general subtheming documentation you may find helpful.
https://drupal.org/project/kalatheme
https://drupal.org/node/225125
https://drupal.org/node/1010576
https://drupal.org/node/2167149 - Has some good screenshots and more explanation of the subtheme creation process.
-----------
Q. I still can't figure this out. Who can I contact for help?
-----------
A: There are a few options:
BEST: Join the ASU Web Community Slack, and go to the #general channel to ask for help, or
BETTER: Go to drupal.asu.edu/wcs and review the content there. If your answers aren't there, fill out the form
and someone will reach out to you as soon as help is available, or
GOOD: Send an email to webconsulting@asu.edu. Someone will reach out to you as soon as help is available.
