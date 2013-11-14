<?php
/**
 * @file
 * openasu_demo.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function openasu_demo_content_defaults() {
  $content = array();

  $content['about'] = (object) array(
    'exported_path' => 'about',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/about',
      'router_path' => 'node/%',
      'link_title' => 'About',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 1,
      'expanded' => 0,
      'weight' => -49,
      'identifier' => 'main-menu:node-name/about',
    ),
    'title' => 'About',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369020,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'about',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>About ASU web<strong>spark</strong></h3><p>ASU has partnered with <a href="https://drupal.asu.edu/host#plans">Pantheon</a> to provide Drupal web hosting, along with a custom version of Drupal specifically created for ASU called <strong>ASU webspark.</strong></p><p>It’s free to create development and test sites in the Pantheon environment and hosting is available for ASU sites from $20 per month.</p><p><strong><a href="https://drupal.asu.edu/host#plans">view more information about hosting plans</a></strong></p><p>A new web site takes less than 15 minutes to create and once ready, it is easy to customize with different layouts and <a href="/node/7">built-in features</a>. Since&nbsp;ASU webspark is created specifically for the ASU community, an ASU webspark site allows any designated ASU user to serve as administrator or author, by signing in to the site with ASU credentials.</p><p><a href="http://www.youtube.com/playlist?list=PL06Pxw-jVkN085OawfNr0m3ztnffkZSST"><strong>view pantheon video guides</strong></a></p><p><img style="float: left;" src="/sites/all/modules/openasu_demo/images/pantheon-logo-white.png" data-file_info="%7B%22fid%22:%2270%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>About ASU web<strong>spark</strong></h3>
<p>ASU has partnered with <a href="https://drupal.asu.edu/host#plans">Pantheon</a> to provide Drupal web hosting, along with a custom version of Drupal specifically created for ASU called <strong>ASU webspark.</strong></p>
<p>It’s free to create development and test sites in the Pantheon environment and hosting is available for ASU sites from $20 per month.</p>
<p><strong><a href="https://drupal.asu.edu/host#plans">view more information about hosting plans</a></strong></p>
<p>A new web site takes less than 15 minutes to create and once ready, it is easy to customize with different layouts and <a href="/node/7">built-in features</a>. Since ASU webspark is created specifically for the ASU community, an ASU webspark site allows any designated ASU user to serve as administrator or author, by signing in to the site with ASU credentials.</p>
<p><a href="http://www.youtube.com/playlist?list=PL06Pxw-jVkN085OawfNr0m3ztnffkZSST"><strong>view pantheon video guides</strong></a></p>
<p><img style="float:left" src="/sites/default/files/resize/remote/2d45de60d88f6cde27576fb8dddc9fca-244x114.png" width="244" height="114" /></p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['asu-events'] = (object) array(
    'exported_path' => 'asu-events',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/asu-events',
      'router_path' => 'node/%',
      'link_title' => 'ASU Events',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/asu-events',
    ),
    'title' => 'ASU Events ',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1374859320,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'asu-events',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>ASU Events</h3><p>Site administrators add an ASU Events feed to the site which will automatically be updated.</p><h4>Importing Events Feed</h4><p>&nbsp;</p><blockquote><p><strong>Step 1:&nbsp;</strong> In the site administration panel, go to Structure-Feeds importers-ASU Events Importer (/admin/structure/feeds/asu_events_importer). Click Override or Edit and to the right of Node Processor click on Settings and set Bundle to ASU Events.</p></blockquote><p><em>example display:</em><br><img src="/sites/all/modules/openasu_demo/images/Screen%20Shot%202013-07-25%20at%209.55.01%20AM.png" data-file_info="%7B%22fid%22:%22171%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><blockquote><p><strong>Step 2:</strong>&nbsp;Navigate to your_site_address/import/asu_events_importer and add the feed URL of the ASU Events feed, and select Import. (To request an ASU Events Feed and the corresponding url, email <a href="mailto:Tanya.Amos@asu.edu" style="line-height: 1.5em;">Tanya.Amos@asu.edu</a> at ASU Events.)</p></blockquote><p><em>example display:</em><br><img src="/sites/all/modules/openasu_demo/images/importasuevents.png" data-file_info="%7B%22fid%22:%22180%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><h4></h4><h4><strong>Adding Events Views</strong><em><br></em></h4><p><strong></strong>Note: Full details on how the Views module works can be found on the <a href="https://drupal.org/project/views">Views Module page</a> on drupal.org.</p><p>&nbsp;</p><blockquote><p><strong>Step 1:</strong> In the site administration panel, go to Menu-Structure-Views and select "Add new view".<br><strong></strong></p><p>&nbsp;</p><p><strong>Step 2:</strong> Create a name for the view and select "Show Content of type ASU Event". Select "Continue &amp; edit".<br><strong></strong></p><p>&nbsp;</p><p><strong>Step 3:</strong> In the "Format" section, change "Format:Unformatted list" to "Table" and select "Apply all displays".<br><strong></strong></p><p>&nbsp;</p><p><strong>Step 4:</strong>&nbsp;On the right of "Fields", select "Add". This is where any fields that are needed to be displayed should be added. Title and URL at ASU Events Site are two fields that are commonly used, but the fields selected can be chosen based on the needs of the site.<br><strong></strong></p><p>&nbsp;</p><p><strong>Step 5:</strong>&nbsp;Navigate to "PAGER" and change "Display a specified number of items" to "Display all items" &nbsp;and then select "Apply (all displays)". &nbsp;Leave Offset to 0 and select "Apply (all displays)" again.<br><strong></strong></p><p>&nbsp;</p><p><strong>Step 6:&nbsp;</strong><span>Now the view needs to be able to be placed into a panel. &nbsp;To do this click on +Add at the top next to Page. &nbsp;Find and click Content pane. &nbsp;This will allow you to place the content on a page in any column or position you want. &nbsp;</span>&nbsp;</p><p>&nbsp;</p><p><strong>Step 7:</strong> To complete setup, select "Save" at the top of the page.</p></blockquote><p>For any additional information please see <a href="https://drupal.asu.edu/wiki/asu-events-feed-feature">ASU Events Feature</a>.</p><p><img src="/sites/all/modules/openasu_demo/images/events_preset.jpg" /></p><p>An example of what your Events feed could look like.</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>ASU Events</h3>
<p>Site administrators add an ASU Events feed to the site which will automatically be updated.</p>
<h4>Importing Events Feed</h4>
<p> </p>
<blockquote><p><strong>Step 1: </strong> In the site administration panel, go to Structure-Feeds-ASU Events Importer<strong><em>.</em></strong> To the right of Node Processor click on Settings and set Bundle to ASU Events.</p>
</blockquote>
<p><em>example display:</em><br /><img src="/sites/default/files/resize/remote/5374175c25843811c285d7f00459a777-275x98.png" width="275" height="98" /></p>
<blockquote><p><strong>Step 2:</strong> Navigate to your_site_address/import/asu_events_importer and add the feed URL of the ASU Events feed, and select Import. (To request an ASU Events Feed and the corresponding url, email <a href="mailto:Tanya.Amos@asu.edu">Tanya.Amos@asu.edu</a> at ASU Events.)</p>
</blockquote>
<p><em>example display:</em><br /><img src="/sites/default/files/resize/remote/e73f001e7ec9d272f670b0444b323c64-275x247.png" width="275" height="247" /></p>
<h4></h4>
<h4><strong>Adding Events Views</strong><em><br /></em></h4>
<p><strong></strong>Note: Full details on how the Views module works can be found on the <a href="https://drupal.org/project/views">Views Module page</a> on drupal.org.</p>
<p> </p>
<blockquote><p><strong>Step 1:</strong> In the site administration panel, go to Menu-Structure-Views and select "Add new view".<br /><strong></strong></p>
<p> </p>
<p><strong>Step 2:</strong> Create a name for the view and select "Show Content of type ASU Event". Select "Continue &amp; edit".<br /><strong></strong></p>
<p> </p>
<p><strong>Step 3:</strong> In the "Format" section, change "Format:Unformatted list" to "Table" and select "Apply all displays".<br /><strong></strong></p>
<p> </p>
<p><strong>Step 4:</strong> On the right of "Fields", select "Add". This is where any fields that are needed to be displayed should be added. Title and URL at ASU Events Site are two fields that are commonly used, but the fields selected can be chosen based on the needs of the site.<br /><strong></strong></p>
<p> </p>
<p><strong>Step 5:</strong> Navigate to "PAGER" and change "Display a specified number of items" to "Display all items"  and then select "Apply (all displays)".  Leave Offset to 0 and select "Apply (all displays)" again.<br /><strong></strong></p>
<p> </p>
<p><strong>Step 6: </strong><span>Now the view needs to be able to be placed into a panel.  To do this click on +Add at the top next to Page.  Find and click Content pane.  This will allow you to place the content on a page in any column or position you want.  </span> </p>
<p> </p>
<p><strong>Step 7:</strong> To complete setup, select "Save" at the top of the page.</p>
</blockquote>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['asu-header-footer'] = (object) array(
    'exported_path' => 'asu-header-footer',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/asu-header-footer',
      'router_path' => 'node/%',
      'link_title' => 'Header and Footer',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/asu-header-footer',
    ),
    'title' => 'Header and Footer',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369560,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'asu-header-footer',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Header and Footer</h3><p>Each site will automatically incorporate the current version of the standard ASU header and footer. The footer has two style options to select from – the standard footer or My ASU student focused footer. Selections can easily be made during the initial creation of the site or changed at any time within the administrative settings. The framework will also be updated automatically for all users of&nbsp;ASU webspark when there are updates made to either the header or footer.</p><p>&nbsp;</p><h4>Header Options</h4><p><img src="/sites/all/modules/openasu_demo/images/header1.png" data-file_info="%7B%22fid%22:%22108%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p><img src="/sites/all/modules/openasu_demo/images/header2.png" data-file_info="%7B%22fid%22:%22109%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p><img src="/sites/all/modules/openasu_demo/images/header3_0.png" data-file_info="%7B%22fid%22:%22113%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><h4>Standard Footer</h4><p><img src="/sites/all/modules/openasu_demo/images/footer.png" data-file_info="%7B%22fid%22:%22111%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Header and Footer</h3>
<p>Each site will automatically incorporate the current version of the standard ASU header and footer. The footer has two style options to select from – the standard footer or My ASU student focused footer. Selections can easily be made during the initial creation of the site or changed at any time within the administrative settings. The framework will also be updated automatically for all users of ASU webspark when there are updates made to either the header or footer.</p>
<p> </p>
<h4>Header Options</h4>
<p><img src="/sites/default/files/resize/remote/319d8862d4938f6de56bdefb3229700c-525x29.png" width="525" height="29" /></p>
<p><img src="/sites/default/files/resize/remote/feeac646eb08208262e6c497e02b363c-525x29.png" width="525" height="29" /></p>
<p><img src="/sites/default/files/resize/remote/0061eb341f7fdcda21cb1548949862b1-525x29.png" width="525" height="29" /></p>
<p> </p>
<h4>Standard Footer</h4>
<p><img src="/sites/default/files/resize/remote/9b81c3d52e3dc03352dbff8b17d8bc30-525x14.png" width="525" height="14" /></p>
<p> </p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['asu-news-feed'] = (object) array(
    'exported_path' => 'asu-news-feed',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/asu-news-feed',
      'router_path' => 'node/%',
      'link_title' => 'ASU News',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/asu-news-feed',
    ),
    'title' => 'ASU News',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1374859140,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'asu-news-feed',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>ASU News</h3><p>Site administrators add an ASU News feed to the site which will automatically be updated.</p><h4>How to Import a News Feed</h4><p>&nbsp;</p><blockquote><p><strong>Step 1: </strong>In the site administration panel, go to Structure-Feeds importers-ASU Events Importer (/admin/structure/feeds/asu_news_importer). Click Override or Edit and to the right of Node Processor click on Settings and set Bundle to ASU News.</p></blockquote><p>&nbsp;<em>example display:</em></p><p><img src="/sites/all/modules/openasu_demo/images/Screen%20Shot%202013-07-25%20at%209.54.49%20AM.png" data-file_info="%7B%22fid%22:%22172%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><blockquote><p><strong>Step 2: </strong>Navigate to <em>your_site_address</em>/import/asu_news_importer and add the feed URL of the ASU News feed, and select Import. (To request an ASU News Feed and the corresponding url, email <a href="mailto:Brandon.Jenkins@asu.edu" style="line-height: 1.5em;">Brandon.Jenkins@asu.edu</a>&nbsp;at ASU News.)</p></blockquote><p><em><em>example display:</em><br><img src="/sites/all/modules/openasu_demo/images/importasunews.png" data-file_info="%7B%22fid%22:%22179%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D">&nbsp;</em></p><h4>Importing Events Feed</h4><p>&nbsp;</p><blockquote><p><strong>Step 1:&nbsp;</strong> In the site administration panel, go to Structure-Feeds-ASU Events Importer<em></em><strong><em>.</em></strong> Set Bundle to ASU Events.</p></blockquote><p><em>example display:</em><br><img src="/sites/all/modules/openasu_demo/images/Screen%20Shot%202013-07-25%20at%209.55.01%20AM.png" data-file_info="%7B%22fid%22:%22171%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><blockquote><p><strong>Step 2:</strong>&nbsp;Navigate to your_site_address/import/asu_events_importer and add the feed URL of the ASU Events feed, and select Import. (To request an ASU Events Feed and the corresponding url, email <a href="mailto:Tanya.Amos@asu.edu" style="line-height: 1.5em;">Tanya.Amos@asu.edu</a> at ASU Events.)</p></blockquote><p><em>example display:</em><br><img src="/sites/all/modules/openasu_demo/images/importasuevents.png" data-file_info="%7B%22fid%22:%22180%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><p><em>Note: Full details on how the Views module works can be found on the <a href="https://drupal.org/project/views">Views Module page</a> on drupal.org.</em></p><p>&nbsp;</p><blockquote><p><strong>Step 1:</strong> In the site administration panel, go to Menu-Structure-Views and select "Add new view".</p><p>&nbsp;</p><p><strong>Step 2:</strong> Create a name for the view and select "Show Content of type ASU News". Select "Continue &amp; edit".</p><p>&nbsp;</p><p><strong>Step 3:</strong> In the "Format" section, change "Format:Unformatted list" to "Table" and select "Apply all displays".</p><p>&nbsp;</p><p><strong>Step 4:</strong>&nbsp;On the right of "Fields", select "Add". This is where any fields that are needed to be displayed should be added. The usual fields are post date and title (make sure to chceck the box next to <span>Link this field to the original piece of content)</span>, but the fields selected can be chosen based on the needs of the site.</p><p>&nbsp;</p><p><strong>Step 5:</strong> Navigate to "PAGER" and change "Display a specified number of items" to "Display all items" &nbsp;and then select "Apply (all displays)". &nbsp;Leave Offset to 0 and select "Apply (all displays)" again.&nbsp;</p></blockquote><blockquote><p><strong>Step 6:&nbsp;</strong>Now the view needs to be able to be placed into a panel. &nbsp;To do this click on +Add at the top next to Page. &nbsp;Find and click Content pane. &nbsp;This will allow you to place the content on a page in any column or position you want. &nbsp;</p><p>&nbsp;</p><p><strong>Step 7:</strong> To complete setup, select "Save" at the top of the page.</p></blockquote><p>For any additional information please see <a href="https://drupal.asu.edu/create/asu-news-feature">ASU News Feature</a>.</p><p><img src="/sites/all/modules/openasu_demo/images/news_preset.jpg" /></p><p>An example of what your News feed could look like.',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>ASU News</h3>
<p>Site administrators add an ASU News feed to the site which will automatically be updated.</p>
<h4>How to Import a News Feed</h4>
<p> </p>
<blockquote><p><strong>Step 1: </strong>In the site administration panel, go to Structure-Feeds-ASU News Importer<strong><em>.</em></strong> <span>To the right of Node Processor click on Settings and s</span>et Bundle to ASU News.</p>
</blockquote>
<p> <em>example display:</em></p>
<p><img src="/sites/default/files/resize/remote/a4cf50810a55962218b866935fd536b4-289x96.png" width="289" height="96" /></p>
<p> </p>
<blockquote><p><strong>Step 2: </strong>Navigate to <em>your_site_address</em>/import/asu_news_importer and add the feed URL of the ASU News feed, and select Import. (To request an ASU News Feed and the corresponding url, email <a href="mailto:Brandon.Jenkins@asu.edu">Brandon.Jenkins@asu.edu</a> at ASU News.)</p>
</blockquote>
<p><em><em>example display:</em><br /><img src="/sites/default/files/resize/remote/b2dbd89520802d90ab35d4bdc6342e56-275x247.png" width="275" height="247" /> </em></p>
<h4>Importing Events Feed</h4>
<p> </p>
<blockquote><p><strong>Step 1: </strong> In the site administration panel, go to Structure-Feeds importers-ASU Events Importer (/admin/structure/feeds/asu_events_importer). Click Override or Edit and to the right of Node Processor click on Settings and set Bundle to ASU Events.</p>
</blockquote>
<p><em>example display:</em><br /><img src="/sites/default/files/resize/remote/5374175c25843811c285d7f00459a777-275x98.png" width="275" height="98" /></p>
<blockquote><p><strong>Step 2:</strong> Navigate to your_site_address/import/asu_events_importer and add the feed URL of the ASU Events feed, and select Import. (To request an ASU Events Feed and the corresponding url, email <a href="mailto:Tanya.Amos@asu.edu">Tanya.Amos@asu.edu</a> at ASU Events.)</p>
</blockquote>
<p><em>example display:</em><br /><img src="/sites/default/files/resize/remote/e73f001e7ec9d272f670b0444b323c64-275x247.png" width="275" height="247" /></p>
<p> </p>
<p><em>Note: Full details on how the Views module works can be found on the <a href="https://drupal.org/project/views">Views Module page</a> on drupal.org.</em></p>
<p> </p>
<blockquote><p><strong>Step 1:</strong> In the site administration panel, go to Menu-Structure-Views and select "Add new view".</p>
<p> </p>
<p><strong>Step 2:</strong> Create a name for the view and select "Show Content of type ASU News". Select "Continue &amp; edit".</p>
<p> </p>
<p><strong>Step 3:</strong> In the "Format" section, change "Format:Unformatted list" to "Table" and select "Apply all displays".</p>
<p> </p>
<p><strong>Step 4:</strong> On the right of "Fields", select "Add". This is where any fields that are needed to be displayed should be added. The usual fields are post date and title (make sure to chceck the box next to <span>Link this field to the original piece of content)</span>, but the fields selected can be chosen based on the needs of the site.</p>
<p> </p>
<p><strong>Step 5:</strong> Navigate to "PAGER" and change "Display a specified number of items" to "Display all items"  and then select "Apply (all displays)".  Leave Offset to 0 and select "Apply (all displays)" again. </p>
</blockquote>
<blockquote><p><strong>Step 6: </strong>Now the view needs to be able to be placed into a panel.  To do this click on +Add at the top next to Page.  Find and click Content pane.  This will allow you to place the content on a page in any column or position you want.  </p>
<p> </p>
<p><strong>Step 7:</strong> To complete setup, select "Save" at the top of the page.</p>
</blockquote>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['contact-contact'] = (object) array(
    'exported_path' => 'content/contact',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/contact-contact',
      'router_path' => 'node/%',
      'link_title' => 'Contact',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'identifier' => 'main-menu:node-name/contact-contact',
    ),
    'title' => 'Contact',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1382466120,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'contact-contact',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Contact</h3><p>Have questions on how ASU webspark can work for you? Or are you a current user of ASU webspark? Please check out&nbsp;<a href="drupal.asu.edu">drupal.asu.edu</a>&nbsp;for further information.</p><p>&nbsp;</p><blockquote><p>Site administrators can also add custom contact forms to their site. &nbsp;To add a custom form go to Content - Add Content - Webform. &nbsp;This creates a page where your form will be displayed. &nbsp;Give the page a title and some descriptive text. &nbsp;Now to add fields to the form click on Webform at the top of the page (next to Edit). &nbsp;Here you can add the desired webform fields. &nbsp;For more information on creating custom WebForms see&nbsp;http://www.youtube.com/watch?v=fgIL8jEMd4s and&nbsp;http://www.ostraining.com/blog/drupal/webform-module/</p></blockquote><p><img src="/sites/all/modules/openasu_demo/images/contact_form_example.jpg"></p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Contact</h3>
<p>Have questions on how ASU webspark can work for you? Or are you a current user of ASU webspark? Please check out <a href="drupal.asu.edu">drupal.asu.edu</a> for further information.</p>
<p> </p>
<blockquote><p>Site administrators can also add custom contact forms to their site.  To add a custom form go to Content - Add Content - Webform.  This creates a page where your form will be displayed.  Give the page a title and some descriptive text.  Now to add fields to the form click on Webform at the top of the page (next to Edit).  Here you can add the desired webform fields.  For more information on creating custom WebForms see <a href="http://www.youtube.com/watch?v=fgIL8jEMd4s">http://www.youtube.com/watch?v=fgIL8jEMd4s</a> and <a href="http://www.ostraining.com/blog/drupal/webform-module/">http://www.ostraining.com/blog/drupal/webform-module/</a></p>
</blockquote>
<p><img src="/sites/all/modules/openasu_demo/images/contact_form_example.jpg" width="305" height="512" /></p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['content-layout-options'] = (object) array(
    'exported_path' => 'content-layout-options',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/content-layout-options',
      'router_path' => 'node/%',
      'link_title' => 'Content Layout Options',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/content-layout-options',
    ),
    'title' => 'Content Layout Options',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369680,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'content-layout-options',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Content Layout Options</h3><p>ASU webspark includes Panaolopy, a powerful Drupal application that allows site builders flexibility in determining page layouts while utilizing drag and drop style page configuration.</p><p><strong>Key Features:</strong></p><ul><li>Layouts are responsive and allow a site to work seamlessly on mobile devices.</li><li>Drag and drop customizations of pages which allow users to easily switch layouts, change styles and add areas to display text, images, links, maps, submenus, video and spotlights on any page within the site. No coding required.</li><li>Pages utilize WYSIWYG editor (What You See Is What You Get) with a common toolbar to easily modify text, add links or insert images.</li></ul><p>&nbsp;</p><h4>Page Layout Options</h4><p><i><img src="/sites/all/modules/openasu_demo/images/panels.png" data-file_info="%7B%22fid%22:%2263%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></i></p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Content Layout Options</h3>
<p>ASU webspark includes Panaolopy, a powerful Drupal application that allows site builders flexibility in determining page layouts while utilizing drag and drop style page configuration.</p>
<p><strong>Key Features:</strong></p>
<ul>
<li>Layouts are responsive and allow a site to work seamlessly on mobile devices.</li>
<li>Drag and drop customizations of pages which allow users to easily switch layouts, change styles and add areas to display text, images, links, maps, submenus, video and spotlights on any page within the site. No coding required.</li>
<li>Pages utilize WYSIWYG editor (What You See Is What You Get) with a common toolbar to easily modify text, add links or insert images.</li>
</ul>
<p> </p>
<h4>Page Layout Options</h4>
<p><i><img src="/sites/default/files/resize/remote/557ef9038e5886744e41cfdc8126b85d-574x286.png" width="574" height="286" /></i></p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['asu-eadvisor-degree-feed'] = (object) array(
    'exported_path' => 'asu-eadvisor-degree-feed',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/asu-eadvisor-degree-feed',
      'router_path' => 'node/%',
      'link_title' => 'ASU eAdvisor',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/asu-eadvisor-degree-feed',
    ),
    'title' => 'ASU eAdvisor Degree Feed',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1377101640,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'asu-eadvisor-degree-feed',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>ASU eAdvisor Degree Feed</h3><p>Site administrators add an ASU eAdvisor Degrees feed to the site which will automatically be updated.</p><h4>Importing Degrees Feed</h4><blockquote><p>Administrators can create 3&nbsp; ASU eAdvisor Degree Feeds (Undergrad Major, Undergrad Minor and Certificate, and Graduate).</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 1 (Undergrad):&nbsp;</strong>Go to your_site.asu.edu/node/add/asu-eadvisor-degree-feed.</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 2: </strong>Enter a title, for example "eAdvisor degree feed - Undergrad majors".</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 3: </strong>Enter the following in the corresponding setting boxes:<br>Protocol: HTTPS Server name: webapp4.asu.edu <br>Path: /programs/XmlRpcServer <br>Service: eAdvisorDSFind.findDegreeByCollegeAndProgram College Code: enter corresponding college code (example: CLA)<br>Program Undergrad Certificate: False</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 4: </strong>Select Save.&nbsp; Degree information will now be imported to the Drupal site and create the eAdvisor nodes.</p></blockquote><p>&nbsp;</p><blockquote><p><strong>For Undergrad Minor)<br></strong>Follow steps 1-4 above but change:<br>Program: Undergrad Certificate: False</p></blockquote><p>&nbsp;</p><blockquote><p><strong>For Graduate)<br></strong>Follow&nbsp;steps 1-4 above but change:<br>Program: Graduate Certificate: False<br>(Certificate option is ignored when Program: Graduate is chosen)</p></blockquote><p>&nbsp;</p><p>An ASU eAdvisor Degree view will be created for each of the feeds entered. &nbsp;To view feed settings, go to Structure &gt; Views. &nbsp;Under each view make sure to add a filter for your department by selecting Filter Criteria and entering "code" into the text box.&nbsp; Check the box next to Content: Department Code and select Apply. Keep the drop down as "Is equal to" and type in the department code.</p><p>This is also where the URLs can be found for linking each page.</p><p>For any additional information please see <a href="https://drupal.asu.edu/create/asu-eadvisor-degree-feed">ASU eAdvisor Degree Feed</a>.</p><p><img src="/sites/all/modules/openasu_demo/images/eadvisor_preset.jpg" /></p><p>An example of what your eAdvisor feed could look like.</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>ASU eAdvisor Degree Feed</h3>
<p>Site administrators add an ASU eAdvisor Degrees feed to the site which will automatically be updated.</p>
<h4>Importing Degrees Feed</h4>
<blockquote><p>Administrators can create 3  ASU eAdvisor Degree Feeds (Undergrad Major, Undergrad Minor and Certificate, and Graduate).</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 1 (Undergrad): </strong>Go to your_site.asu.edu/node/add/asu-eadvisor-degree-feed.</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 2: </strong>Enter a title, for example "eAdvisor degree feed - Undergrad majors".</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 3: </strong>Enter the following in the corresponding setting boxes:<br />Protocol: HTTPS Server name: webapp4.asu.edu <br />Path: /programs/XmlRpcServer <br />Service: eAdvisorDSFind.findDegreeByCollegeAndProgram College Code: enter corresponding college code (example: CLA)<br />Program Undergrad Certificate: False</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 4: </strong>Select Save.  Degree information will now be imported to the Drupal site and create the eAdvisor nodes.</p>
</blockquote>
<p> </p>
<blockquote><p><strong>For Undergrad Minor)<br /></strong>Follow steps 1-4 above but change:<br />Program: Undergrad Certificate: False</p>
</blockquote>
<p> </p>
<blockquote><p><strong>For Graduate)<br /></strong>Follow steps 1-4 above but change:<br />Program: Graduate Certificate: False<br />(Certificate option is ignored when Program: Graduate is chosen)</p>
</blockquote>
<p> </p>
<p>An ASU eAdvisor Degree view will be created for each of the feeds entered.  To view feed settings, go to Structure &gt; Views.  Under each view make sure to add a filter for your department by selecting Filter Criteria and entering "code" into the text box.  Check the box next to Content: Department Code and select Apply. Keep the drop down as "Is equal to" and type in the department code.</p>
<p>This is also where the URLs can be found for linking each page.</p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['home-slideshow'] = (object) array(
    'exported_path' => 'home-slideshow',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/home-slideshow',
      'router_path' => 'node/%',
      'link_title' => 'Home Slideshow',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/home-slideshow',
    ),
    'title' => 'Home Slideshow',
    'status' => 0,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369800,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'home-slideshow',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Easily include a rotating slideshow of images on the home page.</p><p>&nbsp;</p><p><i>(include instructions/screenshots on how users add modify/add home page images)</i></p><p><i>(include photo resources links)</i></p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<p>Easily include a rotating slideshow of images on the home page.</p>
<p> </p>
<p><i>(include instructions/screenshots on how users add modify/add home page images)</i></p>
<p><i>(include photo resources links)</i></p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['how-edit-site'] = (object) array(
    'exported_path' => 'how-edit-site',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/how-edit-site',
      'router_path' => 'node/%',
      'link_title' => 'How to Edit a Site',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => -49,
      'parent_path' => 'node-name/about',
      'identifier' => 'main-menu:node-name/how-edit-site',
    ),
    'title' => 'How to Edit a Site',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1378948920,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'how-edit-site',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>How to Edit a Site</h3><p>Drupal is an open source content management platform powering millions of websites and applications. It’s built, used, and supported by an active and diverse community of people around the world. Drupal is a robust platform which allows flexibility with thousands of add-on module available.</p><p><strong><a href="https://drupal.org/">learn more about drupal</a></strong></p><h4>Editing an ASU webspark Site</h4><p>There are two ways to edit page content. The first is to select "Edit" at the top of the page (just below the main menu).&nbsp; This will bring up a page with all sections on the page in editable boxes. <br><br>The other way is to select "Customize this Page" at the bottom of the page. This will display all of the content on the page (including sidebars) in panels. Panels can be rearranged through drag and drop controls. Panels can also be edited and deleted by selecting correspoinding buttons at the top of each panel. Additional panels can also be added to the page layout.</p><p>An embed video field can be displayed on a page by utlizing panels.&nbsp; To add a panel select the "+" button in the top right corner of the page. Additional items can also be added to a panel including blocks, forms, page content and views. Each new panel contains various options for customization and can be placed in multiple locations on a page. Be sure to select "Save" at the bottom of every page to save and publish changes to the live web site.</p><p>Navigation can be modified within the Structure menu. Within each menu, a list of the menu links will be displayed. These can be moved by dragging and dropping. Menu items can also be deleted from this page. To edit the display name and URL of a menu item, select "Edit" and change the menu link title and path fields. Be sure to select "Save" at the bottom to save all changes.</p><p>Further documentation can be found on the <strong><a href="https://www.getpantheon.com/">Pantheon website</a></strong>.</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>How to Edit a Site</h3>
<p>Drupal is an open source content management platform powering millions of websites and applications. It’s built, used, and supported by an active and diverse community of people around the world. Drupal is a robust platform which allows flexibility with thousands of add-on module available.</p>
<p><strong><a href="https://drupal.org/">learn more about drupal</a></strong></p>
<h4>Editing an ASU webspark Site</h4>
<p>There are two ways to edit page content. The first is to select "Edit" at the top of the page (just below the main menu).  This will bring up a page with all sections on the page in editable boxes. </p>
<p>The other way is to select "Customize this Page" at the bottom of the page. This will display all of the content on the page (including sidebars) in panels. Panels can be rearranged through drag and drop controls. Panels can also be edited and deleted by selecting correspoinding buttons at the top of each panel. Additional panels can also be added to the page layout.</p>
<p>An embed video field can be displayed on a page by utlizing panels.  To add a panel select the "+" button in the top right corner of the page. Additional items can also be added to a panel including blocks, forms, page content and views. Each new panel contains various options for customization and can be placed in multiple locations on a page. Be sure to select "Save" at the bottom of every page to save and publish changes to the live web site.</p>
<p>Navigation can be modified within the Structure menu. Within each menu, a list of the menu links will be displayed. These can be moved by dragging and dropping. Menu items can also be deleted from this page. To edit the display name and URL of a menu item, select "Edit" and change the menu link title and path fields. Be sure to select "Save" at the bottom to save all changes.</p>
<p>Further documentation can be found on the <strong><a href="https://www.getpantheon.com/">Pantheon website</a></strong>.</p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['maps'] = (object) array(
    'exported_path' => 'maps',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/maps',
      'router_path' => 'node/%',
      'link_title' => 'Maps',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/maps',
    ),
    'title' => 'Maps',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1375308600,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'maps',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Maps</h3><p>Include location maps with the built-in Google Maps feature.</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Maps</h3>
<p>Include location maps with the built-in Google Maps feature.</p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['shortcode-test'] = (object) array(
    'exported_path' => 'shortcode-test',
    'title' => 'Shortcode Test',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1379626200,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'shortcode-test',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec sagittis [highlight]metus lacus, et dignissim tortor consequat at[/highlight]. Nunc vitae augue nec odio ultricies rhoncus quis quis ipsum. Donec et quam eget ipsum interdum porta. Curabitur suscipit magna ipsum, ac semper ante dignissim blandit. Integer vitae neque fermentum, ornare nunc non, molestie nulla. Nullam lacinia dolor felis, vitae pharetra sapien eleifend id. Morbi semper ullamcorper fermentum. Cras eleifend erat eget convallis scelerisque. Fusce risus sem, tristique id tempor et, gravida vel orci. Pellentesque non consequat nisi.</p><p>&nbsp;</p>



[button url="http://www.sooperthemes.com" size="1"]Action Button[/button]',
          'summary' => '',
          'format' => 'panopoly_html_text',
          'safe_value' => '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec sagittis [highlight]metus lacus, et dignissim tortor consequat at[/highlight]. Nunc vitae augue nec odio ultricies rhoncus quis quis ipsum. Donec et quam eget ipsum interdum porta. Curabitur suscipit magna ipsum, ac semper ante dignissim blandit. Integer vitae neque fermentum, ornare nunc non, molestie nulla. Nullam lacinia dolor felis, vitae pharetra sapien eleifend id. Morbi semper ullamcorper fermentum. Cras eleifend erat eget convallis scelerisque. Fusce risus sem, tristique id tempor et, gravida vel orci. Pellentesque non consequat nisi.</p>
<p> </p>
<p>[button url="<a href="http://www.sooperthemes.com">http://www.sooperthemes.com</a>" size="1"]Action Button[/button] </p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['features'] = (object) array(
    'exported_path' => 'features',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/features',
      'router_path' => 'node/%',
      'link_title' => 'Features',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 1,
      'expanded' => 0,
      'weight' => -48,
      'identifier' => 'main-menu:node-name/features',
    ),
    'title' => 'Features',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369500,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'features',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Features</h3><p>webspark includes many features to help enhance a web site. The University Technology Office supports the ongoing maintenance of the webspark theme as well as new feature development.</p><p>The framework is set up for easy editing and includes toolbars to change styles, create menu items and add images.</p><p>&nbsp;</p><h4>Editing Menu</h4><p><img src="/sites/all/modules/openasu_demo/images/editor.png" data-file_info="%7B%22fid%22:%22187%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><h4>Menu and Image Options</h4><p><img src="/sites/all/modules/openasu_demo/images/sidebar.png" data-file_info="%7B%22fid%22:%22188%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Features</h3>
<p>webspark includes many features to help enhance a web site. The University Technology Office supports the ongoing maintenance of the webspark theme as well as new feature development.</p>
<p>The framework is set up for easy editing and includes toolbars to change styles, create menu items and add images.</p>
<p> </p>
<h4>Editing Menu</h4>
<p><img src="/sites/default/files/resize/remote/cfbfeabf1a6dc866058f3793a36bd533-500x63.png" width="500" height="63" /></p>
<p> </p>
<h4>Menu and Image Options</h4>
<p><img src="/sites/default/files/resize/remote/3920a99efaa1e2c0c333d88ef46a0290-300x482.png" width="300" height="482" /></p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['footer-options'] = (object) array(
    'exported_path' => 'footer-options',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/footer-options',
      'router_path' => 'node/%',
      'link_title' => 'Footer Options',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/styles',
      'identifier' => 'main-menu:node-name/footer-options',
    ),
    'title' => 'Footer Options',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372370160,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'footer-options',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Footer Options</h3><p>Site owners may also select from two footer display options. The My ASU footer is intended for student-focused websites or the standard footer can be used without the My ASU option.</p><p>&nbsp;</p><h4><strong>My ASU footer with standard footer:</strong></h4><p><img src="/sites/all/modules/openasu_demo/images/myasu_footer.jpg" data-file_info="%7B%22fid%22:%2265%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><h4></h4><p>&nbsp;</p><h4><strong>Standard footer:</strong></h4><p><strong><img src="/sites/all/modules/openasu_demo/images/footer.jpg" data-file_info="%7B%22fid%22:%2266%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></strong></p><p>&nbsp;</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Footer Options</h3>
<p>Site owners may also select from two footer display options. The My ASU footer is intended for student-focused websites or the standard footer can be used without the My ASU option.</p>
<p> </p>
<h4><strong>My ASU footer with standard footer:</strong></h4>
<p><img src="/sites/default/files/resize/remote/52d883ae84f2b6d36bbd98bf9b9170e4-711x141.jpg" width="711" height="141" /></p>
<h4></h4>
<p> </p>
<h4><strong>Standard footer:</strong></h4>
<p><strong><img src="/sites/default/files/resize/remote/c62fc057a8204c794cb9c9e2eec48376-711x25.jpg" width="711" height="25" /></strong></p>
<p> </p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['google-analytics'] = (object) array(
    'exported_path' => 'google-analytics',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/google-analytics',
      'router_path' => 'node/%',
      'link_title' => 'Google Analytics',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/google-analytics',
    ),
    'title' => 'Google Analytics',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369740,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'google-analytics',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Google Analytics</h3><p>Google Analytics is a service offered by Google that generates detailed statistics about a website\'s traffic and traffic sources and measures conversions and sales. Google Analytics can track visitors from all referrers, including search engines and social networks, direct visits and referring sites. It also displays advertising, pay-per-click networks, email marketing and digital collateral such as links within PDF documents. It\'s one of the most powerful digital analytics solutions available - and it\'s free for anyone to use.</p><p>&nbsp;</p><p><img src="/sites/all/modules/openasu_demo/images/analytics.png" data-file_info="%7B%22fid%22:%2264%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><p>&nbsp;</p><h4>New to Analytics?</h4><p><a href="http://www.google.com/analytics/">Learn more about Google Analytics</a></p><p>&nbsp;</p><h4>How to add Google Analytics</h4><p>&nbsp;</p><blockquote><p><strong>Step 1:</strong> Get a Google Web Property ID. This ID is unique to each site you want to track separately, and is in the form of UA-xxxxxxx-yy. To get a Web Property ID, <a href="http://www.google.com/analytics/">register your site with Google Analytics</a>, or if you already have registered your site, go to your Google Analytics Settings page to see the ID next to every site profile. <a href="https://developers.google.com/analytics/resources/concepts/gaConceptsAccounts#webProperty">Find more information in the Google documentation</a>.</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 2:</strong> Add the site ID to Web Property ID box under Menu-Configuration-System-Google Analytics in the administration settings.</p></blockquote><p><em>example settings display:</em><br><img src="/sites/all/modules/openasu_demo/images/googleanalytics.png" data-file_info="%7B%22fid%22:%2283%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><blockquote><p><strong>Step 3:</strong> Select "Save configuration".</p></blockquote>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Google Analytics</h3>
<p>Google Analytics is a service offered by Google that generates detailed statistics about a website\'s traffic and traffic sources and measures conversions and sales. Google Analytics can track visitors from all referrers, including search engines and social networks, direct visits and referring sites. It also displays advertising, pay-per-click networks, email marketing and digital collateral such as links within PDF documents. It\'s one of the most powerful digital analytics solutions available - and it\'s free for anyone to use.</p>
<p> </p>
<p><img src="/sites/default/files/resize/remote/8d606fd1aba511d3103f29407e6587ee-627x227.png" width="627" height="227" /></p>
<p> </p>
<p> </p>
<h4>New to Analytics?</h4>
<p><a href="http://www.google.com/analytics/">Learn more about Google Analytics</a></p>
<p> </p>
<h4>How to add Google Analytics</h4>
<p> </p>
<blockquote><p><strong>Step 1:</strong> Get a Google Web Property ID. This ID is unique to each site you want to track separately, and is in the form of UA-xxxxxxx-yy. To get a Web Property ID, <a href="http://www.google.com/analytics/">register your site with Google Analytics</a>, or if you already have registered your site, go to your Google Analytics Settings page to see the ID next to every site profile. <a href="https://developers.google.com/analytics/resources/concepts/gaConceptsAccounts#webProperty">Find more information in the Google documentation</a>.</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 2:</strong> Add the site ID to Web Property ID box under Menu-Configuration-System-Google Analytics in the administration settings.</p>
</blockquote>
<p><em>example settings display:</em><br /><img src="/sites/default/files/resize/remote/14cc3e276849ab6aff4e42da2c9fb253-525x465.png" width="525" height="465" /></p>
<p> </p>
<blockquote><p><strong>Step 3:</strong> Select "Save configuration".</p>
</blockquote>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['how-to-start-site'] = (object) array(
    'exported_path' => 'how-to-start-site',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/how-to-start-site',
      'router_path' => 'node/%',
      'link_title' => 'How to Start a Site',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => -50,
      'parent_path' => 'node-name/about',
      'identifier' => 'main-menu:node-name/how-to-start-site',
    ),
    'title' => 'How to Start a Site',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1305237240,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'how-to-start-site',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>How to Start a Site</h3><p>Pantheon is providing ASU’s preferred Drupal web hosting environment and&nbsp;ASU webspark is the template created for ASU sites. When users create a new ASU Pantheon Drupal site,&nbsp;ASU webspark is the installation option to select. This will create a new ASU web site with all of the features, styles and formatting already installed.</p><h4><strong>Demo Content<br></strong></h4><p>New sites will contain the demo content from&nbsp;ASU webspark as default. This provides an easy way to modify the content and navigation, without having to do additional configurations. However, please note that if the demo content module is disabled, all of the changes a user has made to the demo content will be removed. This will not impact any additional settings or content created outside the demo package content.</p><h4><strong>Create a Site</strong></h4><p>&nbsp;</p><blockquote><p><strong>To get started, create a new user account using an ASU email at:</strong> https://dashboard.getpantheon.com</p></blockquote><p><img src="/sites/all/modules/openasu_demo/images/spinupsite.jpg" data-file_info="%7B%22fid%22:%2271%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>How to Start a Site</h3>
<p>Pantheon is providing ASU’s preferred Drupal web hosting environment and ASU webspark is the template created for ASU sites. When users create a new ASU Pantheon Drupal site, ASU webspark is the installation option to select. This will create a new ASU web site with all of the features, styles and formatting already installed.</p>
<h4><strong>Demo Content<br /></strong></h4>
<p>New sites will contain the demo content from ASU webspark as default. This provides an easy way to modify the content and navigation, without having to do additional configurations. However, please note that if the demo content module is disabled, all of the changes a user has made to the demo content will be removed. This will not impact any additional settings or content created outside the demo package content.</p>
<h4><strong>Create a Site</strong></h4>
<p> </p>
<blockquote><p><strong>To get started, create a new user account using an ASU email at:</strong> <a href="https://dashboard.getpantheon.com">https://dashboard.getpantheon.com</a></p>
</blockquote>
<p><img src="/sites/default/files/resize/remote/ad9b8cd28cd16530a37447ce4b21beda-480x282.jpg" width="480" height="282" /></p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );

  $content['mobile-formatted'] = (object) array(
    'exported_path' => 'mobile-formatted',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/mobile-formatted',
      'router_path' => 'node/%',
      'link_title' => 'Mobile Formatted',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/mobile-formatted',
    ),
    'title' => 'Mobile Formatted',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369800,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'mobile-formatted',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Mobile Formatted</h3><p>ASU webspark is designed to be mobile friendly, making it easy for site visitors to view information on phones, tablets or other mobile devices. As new mobility standards and updates become available, site owners can quickly apply the update to a site in the site dashboard.</p><p>&nbsp;</p><p><a href="https://webapp4.asu.edu/mobile/about"><img src="/sites/all/modules/openasu_demo/images/Mobile-My-ASU-Ad.jpg" data-file_info="%7B%22fid%22:%22186%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></a></p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Mobile Formatted</h3>
<p>ASU webspark is designed to be mobile friendly, making it easy for site visitors to view information on phones, tablets or other mobile devices. As new mobility standards and updates become available, site owners can quickly apply the update to a site in the site dashboard.</p>
<p> </p>
<p><a href="https://webapp4.asu.edu/mobile/about"><img src="/sites/default/files/resize/remote/5346f2699a7ecc2e5fa7dd4b90002266-280x57.jpg" width="280" height="57" /></a></p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['openasu-style-options'] = (object) array(
    'exported_path' => 'openasu-style-options',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/openasu-style-options',
      'router_path' => 'node/%',
      'link_title' => 'Navigation',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/styles',
      'identifier' => 'main-menu:node-name/openasu-style-options',
    ),
    'title' => 'Navigation ',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369980,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'openasu-style-options',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Navigation</h3><p>The following pre-set style options are available for site navigation. Site owners can select the style during the site start up process. Styles can also be changed within the site administration settings.</p><p>&nbsp;</p><h4>Menu Options</h4><p><strong>Black Menu Color</strong></p><p><img src="/sites/all/modules/openasu_demo/images/nav_black.png" data-file_info="%7B%22fid%22:%22182%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;<strong>Gold Menu Color</strong></p><p><img src="/sites/all/modules/openasu_demo/images/nav_gold.png" data-file_info="%7B%22fid%22:%22183%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p><strong>Grey Menu Color</strong></p><p><img src="/sites/all/modules/openasu_demo/images/nav_grey_0.png" data-file_info="%7B%22fid%22:%22185%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"><br>&nbsp;</p><p>&nbsp;</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Navigation</h3>
<p>The following pre-set style options are available for site navigation. Site owners can select the style during the site start up process. Styles can also be changed within the site administration settings.</p>
<p> </p>
<h4>Menu Options</h4>
<p><strong>Black Menu Color</strong></p>
<p><img src="/sites/default/files/resize/remote/6eccb505e4d579d39460898731b3eac5-550x99.png" width="550" height="99" /></p>
<p> <strong>Gold Menu Color</strong></p>
<p><img src="/sites/default/files/resize/remote/cc051ced98c6adb6a2c2d899ddafab17-550x99.png" width="550" height="99" /></p>
<p><strong>Grey Menu Color</strong></p>
<p><img src="/sites/default/files/resize/remote/c430b650ecc2be45607355685d429b21-550x99.png" width="550" height="99" /><br /> </p>
<p> </p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['quick-site-start'] = (object) array(
    'exported_path' => 'quick-site-start',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/quick-site-start',
      'router_path' => 'node/%',
      'link_title' => 'Quick Site Start Up',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/quick-site-start',
    ),
    'title' => 'Quick Site Start Up',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369860,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'quick-site-start',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Quick Site Start Up</h3><p>New site take approximately 15 minutes to create.</p><p>Learn about the start-up process with this step-by-step demonstration:</p><p><img src="/modules/file/icons/video-x-generic.png"> <a href="http://vimeo.com/66602882">Create an ASU webspark Drupal Web Site</a></p><p>&nbsp;</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Quick Site Start Up</h3>
<p>New site take approximately 15 minutes to create.</p>
<p>Learn about the start-up process with this step-by-step demonstration:</p>
<p><img src="/modules/file/icons/video-x-generic.png" width="16" height="16" /><a href="http://vimeo.com/66602882">Create an ASU webspark Drupal Web Site</a></p>
<p> </p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
    'field_embed_video' => array(
      'und' => array(
        0 => array(
          'video_url' => 'http://vimeo.com/66602882',
          'thumbnail_path' => 'public://video_embed_field_thumbnails/vimeo/66602882.jpg',
          'video_data' => 'a:24:{s:2:"id";i:66602882;s:5:"title";s:37:"Create an ASU WebSpark site (OpenASU)";s:11:"description";s:131:"See how easy it is to use ASU\'s new Drupal web hosting service to create a web site that\'s ASU branded, mobile-friendly and secure!";s:3:"url";s:25:"http://vimeo.com/66602882";s:11:"upload_date";s:19:"2013-05-20 18:56:46";s:15:"thumbnail_small";s:50:"http://b.vimeocdn.com/ts/438/085/438085235_100.jpg";s:16:"thumbnail_medium";s:50:"http://b.vimeocdn.com/ts/438/085/438085235_200.jpg";s:15:"thumbnail_large";s:50:"http://b.vimeocdn.com/ts/438/085/438085235_640.jpg";s:7:"user_id";i:18441605;s:9:"user_name";s:22:"UTO Drupal Development";s:8:"user_url";s:29:"http://vimeo.com/user18441605";s:19:"user_portrait_small";s:145:"http://www.gravatar.com/avatar/3fb1a3b2908a83abaf8f884be8a221d6?d=http%3A%2F%2Fb.vimeocdn.com%2Fimages_v6%2Fportraits%2Fportrait_30_blue.png&s=30";s:20:"user_portrait_medium";s:145:"http://www.gravatar.com/avatar/3fb1a3b2908a83abaf8f884be8a221d6?d=http%3A%2F%2Fb.vimeocdn.com%2Fimages_v6%2Fportraits%2Fportrait_75_blue.png&s=75";s:19:"user_portrait_large";s:147:"http://www.gravatar.com/avatar/3fb1a3b2908a83abaf8f884be8a221d6?d=http%3A%2F%2Fb.vimeocdn.com%2Fimages_v6%2Fportraits%2Fportrait_100_blue.png&s=100";s:18:"user_portrait_huge";s:147:"http://www.gravatar.com/avatar/3fb1a3b2908a83abaf8f884be8a221d6?d=http%3A%2F%2Fb.vimeocdn.com%2Fimages_v6%2Fportraits%2Fportrait_300_blue.png&s=300";s:21:"stats_number_of_likes";i:1;s:21:"stats_number_of_plays";i:117;s:24:"stats_number_of_comments";i:1;s:8:"duration";i:213;s:5:"width";i:1280;s:6:"height";i:720;s:4:"tags";s:96:"Drupal, ASU, Arizona State University, web hosting, Pantheon, OpenASU, video, web site, WebSpark";s:13:"embed_privacy";s:8:"anywhere";s:7:"handler";s:5:"vimeo";}',
          'embed_code' => NULL,
          'description' => NULL,
        ),
      ),
    ),
  );

  $content['resources'] = (object) array(
    'exported_path' => 'resources',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/resources',
      'router_path' => 'node/%',
      'link_title' => 'Resources',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/styles',
      'identifier' => 'main-menu:node-name/resources',
    ),
    'title' => 'Resources',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1374854160,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'resources',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Resources</h3><p>&nbsp;</p><p><a href="https://drupal.asu.edu/"><strong>ASU Drupal Community</strong><br></a>The main source for all Drupal news and reference guides within the ASU community.</p><p><a href="http://commguide.asu.edu/"><strong>Communication Style Guide</strong><br></a>The ASU Communication Guide is a collection of guidelines (or standards that are expected), information about branding in general, a definition of the ASU brand, downloadable logos, a toolbox of templates and various other resources to help you produce ASU-branded communications.</p><p><a href="http://commguide.asu.edu/downloads/logos"><strong>Logo Downloads</strong><br></a>Information about ASU logos and graphics as governed by the ASU Communication Guide.</p><p><strong><a href="http://commguide.asu.edu/resources/photos">Photography Resources</a></strong><br>Many ASU departments and colleges use flickr to manage and share their photo libraries.</p><p>&nbsp;</p><p>&nbsp;</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Resources</h3>
<p> </p>
<p><a href="https://drupal.asu.edu/"><strong>ASU Drupal Community</strong><br /></a>The main source for all Drupal news and reference guides within the ASU community.</p>
<p><a href="http://commguide.asu.edu/"><strong>Communication Style Guide</strong><br /></a>The ASU Communication Guide is a collection of guidelines (or standards that are expected), information about branding in general, a definition of the ASU brand, downloadable logos, a toolbox of templates and various other resources to help you produce ASU-branded communications.</p>
<p><a href="http://commguide.asu.edu/downloads/logos"><strong>Logo Downloads</strong><br /></a>Information about ASU logos and graphics as governed by the ASU Communication Guide.</p>
<p><strong><a href="http://commguide.asu.edu/resources/photos">Photography Resources</a></strong><br />Many ASU departments and colleges use flickr to manage and share their photo libraries.</p>
<p> </p>
<p> </p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['single-sign'] = (object) array(
    'exported_path' => 'single-sign',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/single-sign',
      'router_path' => 'node/%',
      'link_title' => 'Single Sign On',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/single-sign',
    ),
    'title' => 'Single Sign On',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369860,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'single-sign',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Single Sign On</h3><p>CAS (Central Authentication Service) is the built-in module for ASU single sign on authentication. This allows users to use their ASURITE login to create a new site or modify an existing site. Administrators can also use add additional administrators to an&nbsp;ASU webspark site using their ASURITE user name.</p><p>&nbsp;</p><h4><strong>How to Add Users to an OpenASU Site<br></strong></h4><p>&nbsp;</p><blockquote><p><strong>Step</strong> <strong>1</strong>: Navigate to Menu-People in the administration settings. Select "Add CAS user" to add an ASU user. Other users can also be granted access to the site by selecting the "Add user" option.&nbsp;<strong> </strong></p></blockquote><p><em>example settings display:</em><br><img src="/sites/all/modules/openasu_demo/images/adduser1.png" data-file_info="%7B%22fid%22:%2278%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><blockquote><p><strong>Step</strong> <strong>2</strong>: Enter the CAS username (ASURITE) to add an ASU user.</p></blockquote><p><em>example settings display:</em><br><img src="/sites/all/modules/openasu_demo/images/adduser2.png" data-file_info="%7B%22fid%22:%2279%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><blockquote><p><strong>Step</strong> <strong>3</strong>: Username, email address, password and status can be edited by selecting the individual user name in the People section.</p></blockquote><p><em>example settings display:</em><br><img src="/sites/all/modules/openasu_demo/images/adduser3.png" data-file_info="%7B%22fid%22:%2280%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><p>A users role is the type of site access they have been granted. An administrator has access to all areas of the site and can edit all configuration settings. An authenticated user is the basic level of permissions. These users can login to My ASU by utilizing the ASU Header, but do not have any editing permissions on the site.</p>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Single Sign On</h3>
<p>CAS (Central Authentication Service) is the built-in module for ASU single sign on authentication. This allows users to use their ASURITE login to create a new site or modify an existing site. Administrators can also use add additional administrators to an ASU webspark site using their ASURITE user name.</p>
<p> </p>
<h4><strong>How to Add Users to an OpenASU Site<br /></strong></h4>
<p> </p>
<blockquote><p><strong>Step</strong> <strong>1</strong>: Navigate to Menu-People in the administration settings. Select "Add CAS user" to add an ASU user. Other users can also be granted access to the site by selecting the "Add user" option. <strong> </strong></p>
</blockquote>
<p><em>example settings display:</em><br /><img src="/sites/default/files/resize/remote/aaa10167e97403ad66a111629e2e8aa9-500x99.png" width="500" height="99" /></p>
<p> </p>
<blockquote><p><strong>Step</strong> <strong>2</strong>: Enter the CAS username (ASURITE) to add an ASU user.</p>
</blockquote>
<p><em>example settings display:</em><br /><img src="/sites/default/files/resize/remote/1dcf8f588c86383c7598c322109c7d88-500x159.png" width="500" height="159" /></p>
<p> </p>
<blockquote><p><strong>Step</strong> <strong>3</strong>: Username, email address, password and status can be edited by selecting the individual user name in the People section.</p>
</blockquote>
<p><em>example settings display:</em><br /><img src="/sites/default/files/resize/remote/3cf7cae2c6a0f5310ee6e96c42b8801e-500x421.png" width="500" height="421" /></p>
<p> </p>
<p>A users role is the type of site access they have been granted. An administrator has access to all areas of the site and can edit all configuration settings. An authenticated user is the basic level of permissions. These users can login to My ASU by utilizing the ASU Header, but do not have any editing permissions on the site.</p>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['social-media'] = (object) array(
    'exported_path' => 'social-media',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/social-media',
      'router_path' => 'node/%',
      'link_title' => 'Social Media',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'parent_path' => 'node-name/features',
      'identifier' => 'main-menu:node-name/social-media',
    ),
    'title' => 'Social Media',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369920,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'social-media',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3>Social Media</h3><p>Social media is media that encourages two-way and multiple member conversations, as opposed to traditional one-way media.</p><p>The <strong><a href="http://commguide.asu.edu/">ASU Communication Guide</a></strong> provides guidelines for various social media channels including Facebook, Twitter and LinkedIn. ASU webspark allows administrators to incorporate social media channels in several ways.<br><br></p><p>&nbsp;<img src="/sites/all/modules/openasu_demo/images/facebook.png" data-file_info="%7B%22fid%22:%2272%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"><img src="/sites/all/modules/openasu_demo/images/twitter.png" data-file_info="%7B%22fid%22:%2273%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"><img src="/sites/all/modules/openasu_demo/images/linkedin.png" data-file_info="%7B%22fid%22:%2274%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"><img src="/sites/all/modules/openasu_demo/images/youtube.png" data-file_info="%7B%22fid%22:%2275%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"><img src="/sites/all/modules/openasu_demo/images/Vimeo.png" data-file_info="%7B%22fid%22:%2277%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"><img src="/sites/all/modules/openasu_demo/images/google.png" data-file_info="%7B%22fid%22:%2276%22,%22view_mode%22:%22default%22,%22type%22:%22media%22%7D"></p><p>&nbsp;</p><h4>How to Add Social Media</h4><p>&nbsp;</p><blockquote><p><strong>Step 1: </strong>Navigate to Menu-Structure-Blocks&nbsp;in the administration settings.</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 2: </strong>Find the block named Your Site Name on Facebook and click configure on the right of it.</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 3:</strong>&nbsp;Copy and paste the URL of your Facebook page to include on the site. &nbsp;For example,&nbsp;https://www.facebook.com/arizonastateuniversity</p><p>&nbsp;</p><p><strong>Step 4: </strong>Once the social media profile has been entered, the block can be assigned to specific pages or regions on the site. &nbsp;</p><p>&nbsp;</p></blockquote><blockquote><p><strong>Step 5:</strong>&nbsp;Click on "configure" on the far right. In the "REGION" dropdown list, select the region of the site in which the should display. Select "Save blocks".</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 6: </strong>If the social media icons should display on specific pages, select "configure" next to the social media block. In the section "Show block on specific pages", select "Only the listed pages". Copy and paste the page name from the URL in the box.&nbsp; (For example if the URL is "mysite.asu.edu/social-media" then the page name would be "social-media").</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 7:&nbsp;</strong> Select "Save block" to save changes.</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 8:&nbsp;</strong>To add a Google +, Twitter, Facebook, etc button navigate to the Modules page, find ShareThis, and click Configure.</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step9:&nbsp;</strong>&nbsp;Choose your desired settings and which social media sites you want to link to on the configuration page.</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 10:&nbsp;</strong>At the bottom of the page set the context to Node types Content Page, Check the box next to Only full view, Location set to Block and then save the block.</p></blockquote><p>&nbsp;</p><blockquote><p><strong>Step 11:&nbsp;</strong>Now the block created can be placed in a panel on a page or on the page directly wherever you would like.</p></blockquote>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3>Social Media</h3>
<p>Social media is media that encourages two-way and multiple member conversations, as opposed to traditional one-way media.</p>
<p>The <strong><a href="http://commguide.asu.edu/">ASU Communication Guide</a></strong> provides guidelines for various social media channels including Facebook, Twitter and LinkedIn. ASU webspark allows administrators to incorporate social media channels in several ways.</p>
<p> <img src="/sites/default/files/resize/remote/d5bb473e6a00fcbcc00714709176edbe-62x62.png" width="62" height="62" /><img src="/sites/default/files/resize/remote/da87eb122ab5bfdab756d42a55fd72d9-62x62.png" width="62" height="62" /><img src="/sites/default/files/resize/remote/28bf268cf8fb716a7adbb6221c00279c-62x62.png" width="62" height="62" /><img src="/sites/default/files/resize/remote/b9d0e0c051023c86767fc5871e29c3c1-62x62.png" width="62" height="62" /><img src="/sites/default/files/resize/remote/f8af8a5ea904662f0378deedb143cd8c-62x62.png" width="62" height="62" /><img src="/sites/default/files/resize/remote/363f15cb4f2f338082db078e5b0846c9-62x62.png" width="62" height="62" /></p>
<p> </p>
<h4>How to Add Social Media</h4>
<p> </p>
<blockquote><p><strong>Step 1: </strong>Navigate to Menu-Structure-Blocks in the administration settings.</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 2: </strong>Find the block named Your Site Name on Facebook and click configure on the right of it.</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 3:</strong> Copy and paste the URL of your Facebook page to include on the site.  For example, <a href="https://www.facebook.com/arizonastateuniversity">https://www.facebook.com/arizonastateuniversity</a></p>
<p> </p>
<p><strong>Step 4: </strong>Once the social media profile has been entered, the block can be assigned to specific pages or regions on the site.  </p>
<p> </p>
</blockquote>
<blockquote><p><strong>Step 5:</strong> Click on "configure" on the far right. In the "REGION" dropdown list, select the region of the site in which the should display. Select "Save blocks".</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 6: </strong>If the social media icons should display on specific pages, select "configure" next to the social media block. In the section "Show block on specific pages", select "Only the listed pages". Copy and paste the page name from the URL in the box.  (For example if the URL is "mysite.asu.edu/social-media" then the page name would be "social-media").</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 7: </strong> Select "Save block" to save changes.</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 8: </strong>To add a Google +, Twitter, Facebook, etc button navigate to the Modules page, find ShareThis, and click Configure.</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step9: </strong> Choose your desired settings and which social media sites you want to link to on the configuration page.</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 10: </strong>At the bottom of the page set the context to Node types Content Page, Check the box next to Only full view, Location set to Block and then save the block.</p>
</blockquote>
<p> </p>
<blockquote><p><strong>Step 11: </strong>Now the block created can be placed in a panel on a page or on the page directly wherever you would like.</p>
</blockquote>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

  $content['styles'] = (object) array(
    'exported_path' => 'styles',
    'link' => array(
      'menu_name' => 'main-menu',
      'link_path' => 'node-name/styles',
      'router_path' => 'node/%',
      'link_title' => 'Styles',
      'options' => array(),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 1,
      'expanded' => 0,
      'weight' => -47,
      'identifier' => 'main-menu:node-name/styles',
    ),
    'title' => 'Styles',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'panopoly_page',
    'language' => 'und',
    'created' => 1372369920,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'styles',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<h3><img src="/profiles/openasu/modules/contrib/wysiwyg/plugins/break/images/spacer.gif"><img src="/profiles/openasu/modules/contrib/wysiwyg/plugins/break/images/spacer.gif">Styles</h3><p>By using ASU webspark, all style configurations are created and ready to use. This section will provide more information on heading, content display and type options.</p><div class="panels-ipe-portlet-content"><div class="panel-pane pane-entity-field pane-node-body"><div class="pane-content"><div class="field field-name-body field-type-text-with-summary field-label-hidden"><div class="field-items"><div class="field-item even"><p>&nbsp;</p><h4>Typography</h4><p>Several pre-defined formats are available.</p><p>&nbsp;</p><h1>Heading 1</h1><p>&nbsp;</p></div><h2>Heading 2</h2><h3>Heading 3</h3><h4>Heading 4</h4><h5>Heading 5</h5><h6>Heading 6</h6><blockquote><p>Block quote.</p></blockquote><p>&nbsp;</p></div></div></div></div></div>',
          'summary' => '',
          'format' => 'panopoly_wysiwyg_text',
          'safe_value' => '<h3><img src="/profiles/openasu/modules/contrib/wysiwyg/plugins/break/images/spacer.gif" width="1" height="1" /><img src="/profiles/openasu/modules/contrib/wysiwyg/plugins/break/images/spacer.gif" width="1" height="1" />Styles</h3>
<p>By using ASU webspark, all style configurations are created and ready to use. This section will provide more information on heading, content display and type options.</p>
<div>
<div>
<div>
<div>
<div>
<div>
<p> </p>
<h4>Typography</h4>
<p>Several pre-defined formats are available.</p>
<p> </p>
<h1>Heading 1</h1>
<p> </p>
</div>
<h2>Heading 2</h2>
<h3>Heading 3</h3>
<h4>Heading 4</h4>
<h5>Heading 5</h5>
<h6>Heading 6</h6>
<blockquote><p>Block quote.</p>
</blockquote>
<p> </p>
</div>
</div>
</div>
</div>
</div>
',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_featured_status' => array(
      'und' => array(
        0 => array(
          'value' => 0,
        ),
      ),
    ),
  );

return $content;
}
