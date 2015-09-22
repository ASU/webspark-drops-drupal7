ASU eAdvisor Degree Feed Feature module will require all the modules that are needed to do the following:
- Pulls degree information from ASU eAdvisor web services by college code. For example, CLA is for College of Liberal Arts and Sciences.
- Creates ASU eAdvisor Degree nodes in Drupal site.
- Displays each ASU eAdvisor Degree's information in Panel's page.
- Creates Views pages that display nodes that are type of ASU eAdvisor Degree.

=================
REQUIREMENTS
=================

Modules:
ASU Feeds
CTools
Features
Feeds
IXR
Job Scheduler
Link
Panels
Strongarm
Views

============================
INSTALLATION & CONFIGURATION
============================

1. Place the ASU eAdvisor Degree Feed Feature module (asu_eadvisor_degree_feed_feature folder) into an appropriate location on the server, usually /sites/all/modules/.

2. Enable ASU eAdvisor Degree Feed Feature module in Modules page (your_site.asu.edu/admin/modules). In order to enable the ASU eAdvisor Degree Feed Feature module, you will have to install/enable the modules that are listed in the ASU eAdvisor Degree Feed Feature module's Description column.

3. Clear Drupal site's cache.
your_site.asu.edu/admin/config/development/performance -> Click on "Clear all caches"

4. Create 3 new ASU eAdvisor Degree Feeds: Undergrad Major, Undergrad Minor and Certificate, and Graduate

Undergrad Major:
(1) Go to your_site.asu.edu/node/add/asu-eadvisor-degree-feed

(2) Title: "eAdvisor degree feed - Undergrad majors", for example.

(3) Under the "Feed" heading,
Protocol: HTTPS
Server name: webapp4.asu.edu
Path: /programs/XmlRpcServer
Service: eAdvisorDSFind.findDegreeByCollegeAndProgram
College code: CLA, for example.

(4) Under the "Feed" heading,
Program: Undergrad
Certificate: False

(5) Then, "Save". This will import degree information in the college into Drupal site. This will create ASU eAdvisor degree nodes.

Undergrad Minor:
(1), (2), (3) are the same as above.

(4) Under the "Feed" heading,
Program: Undergrad
Certificate: True

(5) is the same as above.

Graduate:
(1), (2), (3) are the same as above.

(4) Under the "Feed" heading,
Program: Graduate
Certificate: False

*When "Program: Graduate" is chosen, Certificate ooption will be ignored and False will be used.

(5) is the same as above.
Known issue:

Also see Troubleshooting below.

- http://drupal.org/node/1107522 - When importing empty/blank values, field label is still displayed in node
The following patch worked to solve the issue as of 10/26/2011 with Feeds 7.x-2.0-alpha4:
http://drupal.org/node/1107522#comment-4870676
To apply patch:
(1) Place the patch (1107522-empty-fields-2.patch) in your_modules_directory/feeds/mappers/ directory.
(2) Then, run the following command from command window from the your_modules_directory/feeds/mappers/ directory:
patch (3) Then, delete all imported nodes and re-import nodes.

===============
TROUBLESHOOTING
===============

- ****If you are getting "There is no new content" message when you do "Import", you might need to increase SSL IXR client timeout setting to 500 for IXR module at your_site.asu.edu/admin/settings/ixr (Drupal 6) or at your_site.asu.edu/admin/config/ixr (Drupal 7).*****

- There are following Views pages:
your_site.asu.edu/eadvisor_degree/ugrad/all
your_site.asu.edu/eadvisor_degree/ugrad/major
your_site.asu.edu/eadvisor_degree/ugrad/minor_cert
your_site.asu.edu/eadvisor_degree/grad

Also, you can see degrees that have been imported at your_site.asu.edu/admin/content/node (Drupal 6) or at your_site.asu.edu/admin/content (Drupal 7).

- Feel free to adjust/change which information to be displayed in Views page, "asu_eadvisor_degree" at your_site.asu.edu/admin/build/views/edit/asu_eadvisor_degree (Drupal 6) or at your_site.asu.edu/admin/structure/views/view/asu_eadvisor_degree/edit (Drupal 7). For department site, you will probably want to filter the View by department code (field_asu_degree_dept_code). So, it will show only degrees for the department.

- Feel free to adjust/change which information to be displayed in each degree's page through Panels at your_site.asu.edu/admin/build/pages/edit/node_view (Drupal 6) or at your_site.asu.edu/admin/structure/pages/edit/node_view (Drupal 7).

=============
Big Thanks to
=============
Jeff Beeman
John Nguyen
Maximo Mena Vasquez

Updated on 10/31/2011
