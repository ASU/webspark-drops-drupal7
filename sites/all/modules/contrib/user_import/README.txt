********************************************************************
                     D R U P A L    M O D U L E
********************************************************************
Name: User Import Module
Author: Robert Castelo <www.codepositive.com>
Drupal: 7.x
********************************************************************
DESCRIPTION:

Import users into Drupal from a CSV file (Comma Separated File).

Features include:

* Creates an account for each user
* Match CSV columns to profile fields.
* Can optionally use the file's first row to map csv data to user profile fields
* Option to create Usernames based on data from file, e.g. "John" + "Smith" => "JohnSmith"
* Usernames can be made of abbreviated data from file, e.g. "Jane" + "Doe" => "JDoe"
* Option to create random, human readable, Usernames
* Option to import passwords
* Option to create random passwords for each user
* Can set user roles
* Option to send welcome email, with account details to each new user
* Can set each user's contact form to enabled
* Test mode option to check for errors
* Processing can be triggered by cron or manually by an administrator
* Can stagger number of users imported, so that not too many emails are sent at one time
* Multiple files can be imported/tested at the same time
* Import into Organic Groups
* Import into Node Profile
* Option to make new accounts immediately active, or inactive until user logs in
* Use CSV file already uploaded through FTP (useful for large imports)
* Designed to be massively scalable

** Supported CSV File Formats **

The following settings are necessary when saving a csv file which will be used for the import.

File needs to be saved as "Character Set: Unicode (UTF-8)".

Field delimiter: ,
- can be configured as something else, a comma is the default though.

Text delimiter: "
- if there's an option to quote all text cells, enable it.

The 'Windows line endings' setting complies with all of the above.

If file import fails with "File copy failed: source file does not exist." try
setting the file extension to .txt.


** IMPORTANT **

- Note that Date fields are not yet supported.

- Note that passwords can only be imported as plain text, and will be converted to MD5 by Drupal.

- Note that if your data contains a backslash before the column separator it may not get imported as expected:

  "123","abc\","def"
  The second field will be imported as: abc","def

  This has been fixed in PHP 5.3


********************************************************************
PREREQUISITES:

  Must have customised Profile fields already entered
  if data is to be imported into user profiles.


********************************************************************
INSTALLATION:

Note: It is assumed that you have Drupal up and running.  Be sure to
check the Drupal web site if you need assistance.

1. Place the entire user_import directory into your Drupal directory:
   sites/all/modules/


2. Enable the user_import modules by navigating to:

   administer > modules

  Click the 'Save configuration' button at the bottom to commit your
  changes.

3. IMPORTANT - Navigate to:
    admin/config/media/file-system 

    Set the 'Private file system path' field.



********************************************************************
CONFIGURATION:

Configuration for User Import:

'People'
-- 'Import'
-- 'Configure' (admin/people/user_import/configure)

* Uploads Directory

   This option provides a directory where files can be uploaded, and then selected when setting up 
   an import. The uploads directory will be in your Private files directory:

   [path to private files]/user_import/uploads/selectable

* Automated Imports

   If this is set then each import template will have the option to create a matching directory which 
   will be scanned for any files that have been uploaded to it, and when a file is found it will 
   automatically be used to create new user accounts. Directories are scanned during cron runs.

   Scanned directories will be in:

   [path to private files]/user_import/uploads/[name of directory]



********************************************************************
USAGE


 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  For more detailed instructions (with pictures) please go to the
  documentation pages for this module:

  http://drupal.org/node/137653
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


1. To set permissions of who can import users into the site, navigate to:

'People'
-- 'Permissions'
-- 'User Import'
-- 'Import users' (admin/people/permissions)

2. To import users, navigate to:

'People'
-- 'Import'
-- 'New Import' (admin/people/user_import/add)

* Note that Drupal may require its caches to be flushed before the User Import menu options appear

3. Press the 'browse' button to select a file to import,
    or select a file already added through FTP.

5. Click on Next.

6. Use the "Use Different CSV File" fieldset to remove and add a different CSV file

7. Under Field Match you should see the various columns from your profile page.

8. For each csv column select a Drupal field to map.

9. Under username select 'No', if the field is not to be used to generate the username, or select '1' - '4'
    for the order to use the field in generating username.

    Example: 'LastName' and 'FirstName' are fields to be used as username.  So under the username
    selection chose '1' for 'FirstName' and '2' for 'Lastname', and the username generated will be in
    the form 'FirstNameLastName'.

10. Under Options you should see Ignore First Line ( use if the first row are labels ),

    Contact, and Send Email.  Select whichever is appropiate.

11. Under Role Assign select the roles the imported users will be assigned.

12. Under Email Message, you can override the default message sent to new users. Leave blank to use the default message.

13. Under Update Existing Users, you can set whether existing users matching ones from the CSV file will be updated, replaced or added.

12. Under Save Settings, you can save your settings for use on future imports.

13. Click "Test" to do an import without committing changes to the database.  Fix any errors that are generated.

14. Click "Import" to complete the import.



********************************************************************
AUTHOR CONTACT

- Report Bugs/Request Features:
   http://drupal.org/project/user_import

- Comission New Features:
   http://drupal.org/user/3555/contact

- Want To Say Thank You:
   http://www.amazon.com/gp/registry/O6JKRQEQ774F


********************************************************************
ACKNOWLEDGEMENT

- I looked at a script by David McIntosh (neofactor.com) before coding this module.
- Documentation help Steve (spatz4000)
- patch by mfredrickson
- patch by idealso
- code from Nedjo Rogers


********************************************************************
SPONSORS

