ASU News Feeds Feature creates a feed importer for ASU News feeds, with a corresponding content type and a view page of news teasers by date.

=========================================================
Requirements
=========================================================

Module requires Chaos tools, Date, Date API, Date Views, Views, Features, Feeds, Job Scheduler, Feeds Admin UI, Feeds XPath Parser, Fieldgroup, Link, Strongarm, Viewfield, Views PHP, Views UI

=========================================================
Installation & Configuration
=========================================================

1. Install the ASU News Feeds Feature module.  The module will incicate any dependencies.  Download and enable those modules as well.

2. Enable the module.  You will see an error message like: "The Date API requires that you set up the site timezone and first day of week settings and the date format settings to function correctly."  

3. To add new date formats, go to admin/config/regional/date-time/formats.
	3a. Add three new date formats, by clicking "Add a format". 
		- For the first "Format string" add 'F' (no quotes), for the second, 'Y'; and for the third, 'F j, Y'
	3b. Go to the "Types" tab. Click "Add date type". 
		- Name the first 'Month' and select the month alone option from the dropdown.  
		- Name the second 'Year' and select the year alone option from the dropdown.  
		- Name the third 'Very short' and select the month date, year option from the dropdown.  

3. Go to /import/asu_news_importer, add the feed URL of your ASU News feed, and click Import.  (You can get a feed and the url by writing to Brandon Jenson at ASU News.)

=========================================================
Troubleshooting
=========================================================

If you get this error when importing:

	cURL error (28) Operation timed out after 15000 milliseconds with 0 bytes received

Add this code to the bottom of your /sites/default/settings.php file:

	$conf = array(
	   'http_request_timeout' => '60',
	);

=========================================================
Bugs
=========================================================
Send bug reports and patches at http://drupal.asu.edu/build/asu-news-feature

=========================================================
Thanks
=========================================================
Thanks to Chizuko Swanson who created the Drupal 6 version and whose news feature for clas.asu.edu was the basis for this feature module.