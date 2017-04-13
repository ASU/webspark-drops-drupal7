Creating a Subtheme for Webspark

-----------
Q: What is a subtheme?
-----------

A: Subthemes in Drupal are child themes that inherit certain attributes from its parent theme. This allows you to 
use an established theme as a base theme and derive layouts/styles from it in the subtheme on the same site, 
without needing to alter or duplicate the original theme. 

In this case, you will be creating a subtheme of Webspark (which is itself a subtheme of Kalatheme).

-----------
Q: Who needs to do this?
-----------

A: Anyone who wants to customize Webspark's look/feel and plans on applying those changes as code (CSS files, template/layout 
files, etc.), via SFTP or Git. Any theming customizations stored inside the DB is not affected.

-----------
Q: Why can't I just edit the existing Webspark theme in /profiles/openasu/themes for my custom theme changes?
-----------

A: Any changes applied to any files or folders in the /profiles directory (including the Webspark theme folder 
in /profiles/openasu/themes) will be overwritten every time UTO updates Webspark and those changes are subsequently 
applied by site admins in the Pantheon Dashboard. These updates are inevitable and shouldn't be avoided because they 
will include security updates to Drupal core.

To apply changes to the theme that will persist, they need to be made in a new and distinct Webspark 
subtheme, which must end up in /sites/all/themes.

-----------
Q: How do I do this?
-----------

A: Two different methods are laid out below, with step-by-step instructions below.

-----------
Creating a Subtheme.
-----------

1. On the Pantheon Dashboard in the Code section, Switch the Connection Mode to SFTP. (If left in Git mode, a ZIP file 
   of an incorrectly configured subtheme will be generated.)
2. In the development site, under Menu, click Appearance.
3. Click "Set Default" next to the Kalatheme theme.
4. Under Menu, click Configuration, then Performance, then Clear all Caches.
5. Under Menu, click Appearance. At the bottom of the page under Administrative Theme select Kalatheme from the
   dropdown box and click Save Configuration. (This will make the appearance of your site a little broken/odd until we are
   finished but it is nothing to worry about.)
6. If another theme is still enabled as the subtheme (ex. "ASU WebSpark Bootstrap..."), click Disable under that theme.
7. Click "Setup Kalatheme" at the top of the page. (If this link is not there, verify that Steps 4-6 were all done.)
8. Name your theme mysite_asuwebsparkbootstrap. Select "ASU WebSpark Bootstrap" from the dropdown under Subtheme Base. 
   Leave all other settings the same. Click 'Dress me up'. When this step has completed, your subtheme has been 
   selected but there's still work to do.
9. On your Pantheon Dashboard in the Code section, click Commit. (If you don't see a message saying there are 'X file 
   changes' and the Commit button is grayed out, refresh the Code page.


--If you are using Git:
10. Switch the Connection Mode to Git in your Pantheon Dashboard and pull the changes.
11. In your IDE, copy the newly created theme folder (mysite_asuwebsparkbootstrap) from profiles/openasu/themes
    to sites/all/themes.
12. Copy all of the folder contents of /profiles/openasu/libaries/asu_webspark_bootstrap_bootstrap/* into the newly created
    directory /sites/all/libraries/mysite_asuwebsparkbootstrap_bootstrap.
13. Copy the regions section from profiles/openasu/themes/asu_webspark_bootstrap.info into the new subtheme's 
    (mysite_asuwebsparkbootstrap) .info file to match the regions.
14. (Optional) To retain Webspark's custom styling, copy /profiles/openasu/themes/asu_webspark_bootstrap/css/main.css into 
    /sites/all/themes/mysite_asuwebsparkbootstrap/css/.
15. Commit all changes and push them to Pantheon.

--If you are using SFTP:
10. Pull all of the newly created files via SFTP down to your local copy of the site. (Should be two folders: 
    /code/profiles/openasu/themes/mysite_asuwebsparkbootstrap and 
    /code/sites/all/libraries/mysite_asuwebsparkbootstrap_bootstrap.)
11. Copy the newly created theme folder (mysite_asuwebsparkbootstrap) from profiles/openasu/themes
    to sites/all/themes.
12. Copy the folder /profiles/openasu/libaries/asu_webspark_bootstrap_bootstrap/* into newly created 
    asu_webspark_bootstrap_bootstrap directory in /sites/all/libraries.
13. Copy the regions section from profiles/openasu/themes/asu_webspark_bootstrap/asu_webspark_bootstrap.info 
    into the new subtheme's (mysite_asuwebsparkbootstrap) .info file to match the regions.
14. (Optional) To retain Webspark's custom CSS styling, copy the following files from left to right:
    * /profiles/openasu/themes/asu_webspark_bootstrap/css/main.css -> /sites/all/themes/mysite_asuwebsparkbootstrap/css/main.css
15. Push file changes back to Pantheon and commit all changes in the Pantheon Dashboard.

-- Continuing steps for both Git and SFTP users:

16. Clear all caches (see Step 4).
17. If the ASU Brand module (places the global ASU headers/footers) is being used, go to Menu, click Structure, 
    then click Blocks.
    The following blocks need to be enabled as follows (block name -> region):
    -- ASU Brand: header -> Header
    -- System help -> Header, below ASU Brand: header
    -- Main menu -> Menu
    -- ASU Brand: footer -> Footer
    Be sure to click Save Blocks.
    (If these regions are not available to you, check Step 13 above.)
18. Clear all caches. 
19. Go to Appearance. Click "Set Default" for Kalatheme. Then click "Disable" for mysite_asuwebsparkbootstrap.
20. Delete the /profiles/openasu/themes/mysite_asuwebsparkbootstrap folder and its contents, and then using either the Git 
    or SFTP workflow, commit and push up the code changes to Pantheon.
21. Clear all caches.
22. Go to Appearance. Click "Enable and Set Default" for mysite_asuwebsparkbootstrap.

Your new subtheme should be now ready to use and customize in /sites/all/themes/mysite_asuwebsparkbootstrap! You can also 
set the administrative theme back to the default or Seven theme. (If you want to repeat this process, you will need to 
set Kalatheme as the administrative theme again.)

-----------
Locally creating a subtheme using Drush.
-----------

1. On your Pantheon Dashboard in the Code section, switch the Connection Mode to SFTP.
2. If the /sites/all/libraries directory hasn't been created yet locally, create it now. Ensure that folder exists wherever 
   the subtheme is being created.
3. In your local copy, go to web's base directory (Drupal root).
4. Enter the CLI command: drush kalatheme "mytheme_webspark" --strict=0
5. Once the subtheme is created, see Steps 13-14 and 16-18 from "Creating a Subtheme" for adding the ASU 
   customization (CSS styling from Webspark, adding regions & header/footer blocks). Commit the changes and push up to 
   Pantheon. The new subtheme will now be available to select on your site's Appearance page.

-----------
Q. Do I need to keep the Kalatheme as the administrative theme after this is done?
-----------

A. No - You can set that back to the default or Seven themes. If you want to repeat this process, you will need to 
set Kalatheme as the administrative theme again.

-----------
Q. Where is there more info on this process or subtheming with Kalatheme?
-----------

A. Below are links to the Drupal.org page for the Kalatheme subtheme you will be using along with some general subtheming
documentation you may find helpful. 

https://drupal.org/project/kalatheme
https://drupal.org/node/225125
https://drupal.org/node/1010576
https://drupal.org/node/2167149 - Has some good screenshots and more explanation of the subtheme creation process.

