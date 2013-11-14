ASU Event Feeds Feature creates a feed importer for ASU event feeds.

=========================================================
Requirements
=========================================================

Module requires ctools date features feeds field_collection field_group field_sql_storage filter image link node number strongarm taxonomy text viewfield views

=========================================================
Installation & Configuration
=========================================================

1. Install the ASU Events Feeds Feature module.  The module will incicate any dependencies.  Download and enable those modules as well.

2. Enable the module.  You will see an error message like: "The Date API requires that you set up the site timezone and first day of week settings and the date format settings to function correctly."  

3. To add new date formats, go to admin/config/regional/date-time/formats.
	3a. Add three new date formats, by clicking "Add a format". 
		- For the first "Format string" add 'F' (no quotes), for the second, 'Y'; and for the third, 'F j, Y'
	3b. Go to the "Types" tab. Click "Add date type". 
		- Name the first 'Month' and select the month alone option from the dropdown.  
		- Name the second 'Year' and select the year alone option from the dropdown.  
		- Name the third 'Very short' and select the month date, year option from the dropdown.  

4. Go to /import/asu_events_importer, add the feed URL of your ASU event feed, and click Import.  (You can get an events feed and the url by writing to Tanya.Amos@asu.edu.)

=========================================================
Troubleshooting
=========================================================
1. If you aren't able to import some fields, compare the fields on /admin/structure/feeds/edit/asu_events_importer/settings/FeedsXPathParserXML with the tags on your feed.

2. If you get this error when importing:

	cURL error (28) Operation timed out after 15000 milliseconds with 0 bytes received

Add this code to the bottom of your /sites/default/settings.php file:

	$conf = array(
	   'http_request_timeout' => '60',
	);

=========================================================
Bugs
=========================================================
Send bug reports and patches to webconsulting@asu.edu.

=========================================================
Thanks
=========================================================
Thanks to Chizuko Swanson who created the Drupal 6 version and whose events feature for clas.asu.edu was the basis for this feature module.
