###################################
January 2021 UPDATE: The Innovation theme will soon be deprecated. Use the WS2.0 theming instructions instead.
###################################

Creating a Subtheme for Innovation (the new Web Standards theme)

(Note: These instructions are specific to creating a subtheme of the new Innovation theme. Refer to
README-CUSTOMIZING-WEBSPARK-THEMING.txt for how to create a subtheme for Webspark Classic.)

-----------
Q: What is a subtheme?
-----------

A: Subthemes in Drupal are child themes that inherit certain attributes from its parent theme. This allows you to
use an established theme as a base theme and derive layouts/styles from it in the subtheme on the same site,
without needing to alter or duplicate the original theme.

In this case, you will be creating a subtheme of the new Innovation theme (which is itself a subtheme of Kalatheme).

-----------
Q: Who needs to do this?
-----------

A: Anyone who wants to customize Innovation's look/feel and plans on applying those changes as code (CSS files, template/layout
files, etc.), via SFTP or Git. Any theming customizations stored inside the DB is not affected.

-----------
Q: Why can't I just edit the existing Innovation theme in /profiles/openasu/themes for my custom theme changes?
-----------

A: Any changes applied to any files or folders in the /profiles directory (including the Webspark theme folder
in /profiles/openasu/themes) will be overwritten EVERY TIME UTO updates Webspark and those changes are subsequently
applied by site admins in the Pantheon Dashboard.

These updates are important because they will sometimes include security updates to Drupal core, so they shouldn't be avoided.

To apply changes to the theme that will persist, they need to be made in a new and distinct subtheme of the
Innovation subtheme, which makes it a "sub-subtheme":

Kalatheme   ->   Innovation   ->   Your New Sub-Subtheme
(base theme)     (sub theme)       (sub sub theme)

This new sub-subtheme will inherit the settings/styles of its parent themes, and again, it MUST end up in /sites/all/themes.

-----------
Q: How do I do this?
-----------

A: Two different methods are laid out below, with step-by-step instructions below.

-----------
Creating a Subtheme.
-----------

1. In the Pantheon Dashboard in the Code section, Switch the Connection Mode to SFTP. (If left in Git mode, a ZIP file
   of an incorrectly configured subtheme will be generated.)
2. In the development site's navbar men, click Menu, and then click Appearance.
3. Click "Set Default" next to the Kalatheme theme.
4. Under Menu, click Configuration, then Performance, then Clear all Caches.
5. Under Menu, click Appearance. At the bottom of the page under Administrative Theme select Kalatheme from the
   dropdown box and click Save Configuration. (This will make the appearance of the admin area of your site appear to be a little broken/odd but it is nothing to worry about. This will be corrected later in this process.)
6. If another theme is still enabled as the subtheme (ex. "Innovation, etc."), click Disable under that theme.
7. Click "Setup Kalatheme" at the top of the page. (If this link is not there, verify that Steps 4-6 were all done.)
8. Name your theme, using lowercase letters and underscores (we recommend innovationcustom - and that will be referred to as the choice for the rest of these steps). Select "Innovation" from the dropdown under Subtheme Base.
   Leave all other settings the same and click 'Dress me up'. When this step has completed, your subtheme has been
   selected but there's still work to do.
9. On your Pantheon Dashboard in the Code section, click Commit. (If you don't see a message saying there are 'X file
   changes' and the Commit button is grayed out, refresh the Code page.


--If you are using Git:
10. In your Pantheon Dashboard, Switch the Connection Mode to Git and pull the changes.
11. In your IDE, copy the newly created theme folder (custominnovation) from profiles/openasu/themes
    to sites/all/themes.
12. Copy all of the folder contents of /profiles/openasu/libaries/innovation_bootstrap/* into the newly created
    directory /sites/all/libraries/custominnovation_bootstrap.
13. Copy the regions section from profiles/openasu/themes/innovation.info into the new subtheme's
    (custominnovation) .info file to match the regions.
14. (Optional) To retain Webspark's custom styling, copy /profiles/openasu/themes/innovation/css/main.css into
    /sites/all/themes/custominnovation/css/.
15. Commit all changes and push them to Pantheon.

--If you are using SFTP (with /code as the web root folder):
10. Pull all of the newly created files via SFTP down to your local copy of the site. (Should be two folders:
    /code/profiles/openasu/themes/custominnovation and
    /code/sites/all/libraries/custominnovation_bootstrap.)
11. Copy the newly created theme folder (custominnovation) from profiles/openasu/themes
    to sites/all/themes.
12. Copy the folder /profiles/openasu/libaries/innovation_bootstrap/* into newly created
    custominnovation_bootstrap directory in /sites/all/libraries.
13. Copy the regions section from profiles/openasu/themes/innovation/innovation.info
    into the new subtheme's (custominnovation) .info file to match the regions.
14. (Optional) To retain Webspark's custom CSS styling, copy the following files from left to right:
    - /profiles/openasu/themes/innovation/css/main.css -> /sites/all/themes/custominnovation/css/main.css
    - /profiles/openasu/themes/innovation/images/* -> /sites/all/themes/custominnovation/images/
15. Push file changes back to Pantheon and commit all changes in the Pantheon Dashboard.

-- Continuing steps for both Git and SFTP users:

16. Clear all caches (see Step 4).
17. If the ASU Brand module (places the global ASU headers/footers) is being used, go to Menu, click Structure,
    then click Blocks.
    The following blocks need to be enabled as follows (block name -> region):
    -- ASU Brand: header -> Header
    -- System help -> Header, below ASU Brand: header
    -- TB Mega Menu: Main menu -> Menu
    (The ASU Brand footer shouldn't be needed for the Innovation theme.)
    Be sure to click Save Blocks.
    (If these regions are not available to you, check Step 13 above.)
18. Clear all caches.
19. Go to Appearance. Click "Set Default" for Kalatheme. Then click "Disable" for custominnovation.
20. Delete the /profiles/openasu/themes/custominnovation folder and its contents, and then using either the Git
    or SFTP workflow, commit and push up the code changes to Pantheon.
21. Clear all caches.
22. Go to Appearance. Click "Enable and Set Default" for custominnovation.

Your new subtheme should be now ready to use and customize in /sites/all/themes/custominnovation! You can now
set the administrative theme back to the default (Seven). (If you want to repeat this process, you will need to
set Kalatheme as the administrative theme again.)

-----------
Locally creating a subtheme using Drush.
-----------

1. On your Pantheon Dashboard in the Code section, switch the Connection Mode to SFTP.
2. If the /sites/all/libraries directory hasn't been created yet locally, create it now. Ensure that folder exists wherever
   the subtheme is being created.
3. In your local copy, go to web's base directory (Drupal root).
4. Enter the CLI command: drush kalatheme "custominnovation" --strict=0
5. Once the subtheme is created, see Steps 13-14 and 16-18 from "Creating a Subtheme" for adding the ASU
   customization (CSS styling from Webspark, adding regions & header/footer blocks). Commit the changes and push up to
   Pantheon. The new subtheme will now be available to select on your site's Appearance page.

-----------
Q. Do I need to keep the broken-looking Kalatheme as the administrative theme after this is done?
-----------

A. No - You should set that back to the default or Seven themes. If you want to repeat this process, you will need to set Kalatheme as the administrative theme again.

-----------
Q. Where is there more info on this process or subtheming with Kalatheme?
-----------

A. Below are links to the Drupal.org page for the Kalatheme subtheme you will be using along with some general subtheming
documentation you may find helpful.

https://drupal.org/project/kalatheme
https://drupal.org/node/225125
https://drupal.org/node/1010576
https://drupal.org/node/2167149 - Has some good screenshots and more explanation of the subtheme creation process.

-----------
Q. I still can't figure this out. Who can I contact for help?
-----------

There are a couple of options:

A. Send an email to webconsulting@asu.edu, or
B. On-site Help Desk (with students available to help out)
  USB 2651
  M-F, 10AM-3PM
  727-5506
