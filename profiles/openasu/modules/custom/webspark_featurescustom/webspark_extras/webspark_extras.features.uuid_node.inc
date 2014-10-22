<?php
/**
 * @file
 * webspark_extras.features.uuid_node.inc
 */

/**
 * Implements hook_uuid_features_default_content().
 */
function webspark_extras_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'title' => 'Help & Examples',
  'log' => '',
  'status' => 1,
  'comment' => 0,
  'promote' => 1,
  'sticky' => 0,
  'type' => 'panopoly_page',
  'language' => 'und',
  'created' => 1411595040,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => '9244310b-87f3-42ad-a1a2-5f7498372fd9',
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p>Please read through these instructions before starting to create your site.</p>
<p>
<!--break-->
</p>
<p>To remove this page from the menu, select the edit tab, then uncheck Menu options &gt; Provide a menu link.&nbsp; You can also unpublish or delete this page.</p>
<p>-----------</p>
<h3>Change a Page\'s Layout</h3>
<p>You can change the layout of your page content area (between header and footer) by clicking the "Change this layout" button at the bottom of the page. There are many layouts to choose from:</p>
<p>&nbsp;</p>
<p><img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/panopoly_layouts.png" border="0"></p>
<ol>
	<li>Choose a layout and click next.&nbsp;</li>
	<li>You\'ll be asked to verify which regions content should move to in the new layout.&nbsp; Drag and drop content panes to the correct regions.&nbsp; <em><strong>Remember:</strong> </em>heroes, content callouts, title banners, spotlights (slideshows) and other full-width elements must be placed in a <em>full-width row by themselves</em>.</li>
	<li>Click save and check your page.&nbsp; You may need to click "Customize this page" and rearrange content panes again.</li>
</ol>
<p>-----------</p>
<h3>Customize a Page</h3>
<p>You can rearrange content, add new content, and add styles to your page by clicking the "Customize this page" button at the bottom of the page.</p>
<p>You\'ll see your current layout of regions in rows, with current content panes inside their current regions.</p>
<p>&nbsp;</p>
<p><img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/custom_page.png" border="0"></p>
<p>&nbsp;</p>
<h4>Rearrange Panes</h4>
<p>You can drag and drop content panes to new regions and new rows.&nbsp; <em><strong>Remember:</strong></em> heroes, content callouts, title banners, spotlights (slideshows) and other full-width elements must be placed in a <em>full-width row by themselves</em>.</p>
<h4>Add Content</h4>
<p>Click the Plus button &nbsp; <img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/plus.png" border="0"> &nbsp; on a region to add new content panes to it.&nbsp; Available content panes include:</p>
<p>&nbsp;</p>
<ul>
	<li>Exisiting blocks or content (\'Add content item\' link)</li>
	<li>Links, images. maps, tables, video, submenus, and lists</li>
	<li>ASU web standards elements, such as an ASU spotlights, title banner, or hero (see below for specifics on full-width elements)</li>
</ul>
<h4>Add Styles</h4>
<p>Click the paintbrush button &nbsp; <img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/brush.png" border="0"> &nbsp; on either a pane or row to add styles, spacing, background colors, alignment and more to a pane.&nbsp; For example, to add spacing above and below a row:</p>
<p>&nbsp;</p>
<ol>
	<li>Select \'Spacing and backgrounds\'&nbsp;&nbsp; and click \'Next.\'&nbsp;</li>
	<li>Select \'Add spacing above row\' and \'Add spacing below row\' and click save.</li>
</ol>
<p>-----------</p>
<h3>Heroes</h3>
<p><strong>Only add a hero to a <strong><strong><strong>a full-width top row by itself</strong></strong></strong>.&nbsp; (Do not add any other panes to this row.</strong> ) Change the page\'s layout if necessary.</p>
<ul>
	<li>Full-width.&nbsp;</li>
	<li>See standards site for requirements on where heroes can go - http://asu-ws.29thdrive.com</li>
	<li>You can only add a hero to the top of a page, and only to a single-column row.</li>
	<li>Have to choose either the two blue buttons (can change the url) or a single red button.</li>
	<li>To add spacing to a row or pane, click "Customize this page," then the paintbrush button &nbsp; <img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/brush.png" border="0"> &nbsp; on the pane or row, then "Spacing and background colors."</li>
</ul>
<p>-----------</p>
<h3>Content Callouts</h3>
<p><strong><strong>Only add a content callout to <strong><strong><strong>a full-width row by itself</strong></strong></strong>.&nbsp; (Do not add any other panes to this row.</strong> )</strong> Change the page\'s layout if necessary.</p>
<ul>
	<li>Content callouts are full-width....etc.&nbsp; See web standard guidelines on placement - http://asu-ws.29thdrive.com</li>
	<li>Edit existing content callouts with your own text, images and video links.</li>
	<li>Place content callouts in a pane:</li>
	<li>Click the Plus button &nbsp; <img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/plus.png" border="0"> &nbsp; in the Customize this page view</li>
<ol>
	<li>Click "Add content item" from left sidebar</li>
	<li>Search for content by starting title in the Piece of Content field.</li>
	<li>Under Display Settings, choose display type \'Content.\'</li>
	<li>Under Content Settings, choose \'Full content.\'</li>
	<li>Save.</li>
</ol>
<li>Style the content callout pane:</li>
<ol>
<li>Click the paintbrush button &nbsp; <img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/brush.png" border="0"> &nbsp; in the layout view</li>
<li>Choose \'ASU Standards custom styles\' and click Next</li>
<li>Add a row background color, row spacing, or pane spacing.</li>
</ol>
</ul>
<p>-----------</p>
<h3>Title Banners</h3>
<p><strong>Only add a title banner <strong><strong> to a full-width row by itself.&nbsp; (Do not add any other panes to this row.</strong> )</strong>&nbsp;</strong> Change the page\'s layout if necessary.</p>
<ol>
	<li>Click the Plus button &nbsp; <img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/plus.png" border="0"> &nbsp; in the Customize this page view</li>
	<li>Chose the banner title.&nbsp; Type the title of the page and upload a 1220 x 200 px image.&nbsp; Save.</li>
</ol>
<p>-----------</p>
<h3>ASU Spotlight (Flexslider)</h3>
<p><strong></strong><strong>Only add a spotlight (slideshow) <strong><strong> to <strong><strong><strong>a full-width row by itself</strong></strong></strong>.&nbsp; (Do not add any other panes to this row.</strong> )</strong>&nbsp;</strong> Change the page\'s layout if necessary.</p>
<ul>
	<li>Full-width slider, with title, action buttons, and customized placement</li>
	<li>Placing slider in a container will cause entire container to go full width, important to know if other elements are in container</li>
	<li>Slider settings such as animation and speed can be customized at Configuration-&gt;Media-&gt;ASU Spotlight</li>
</ul>
<ol>
	<li>&nbsp; <img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/plus.png" border="0"> &nbsp; &nbsp;in the Customize this page view</li>
	<li>Click "Add ASU Spotlight" in the left panel</li>
	<li>Enter information for each slide, including title, description, button placement and color</li>
	<li>Click Save</li>
</ol>
<p>-----------</p>
<h3 style="line-height: 1.44;">Mega Footer</h3>
<ul>
	<li>Module that can be enabled or disabled</li>
	<li>Customization is done on the block configure page by going to Structure &gt; Blocks, then clicking "Configure" on Mega Footer block</li>
	<li>Social media links that are not entered will not show output of the corresponding icon</li>
	<li>Non-required fields that are left blank will not be output also, including logo image upload field. &nbsp;</li>
	<li>Menu for the Mega Footer can be customized at Structure-&gt;Menus-&gt;Mega Footer Menu. &nbsp;Please note that the top-level menu items will be output as headings and not links. &nbsp;The links will also be output in an order which reflects the Mega Footer Menu item order.</li>
</ul>
<p>-----------</p>
<h3>Mega Menu</h3>
<ul>
	<li>To customize the menu navigate to Structure -&gt; TB Mega Menu.</li>
	<li>Once there, find the menu that will be customized and click "Config". &nbsp;In this instance that menu is main menu.</li>
	<li>For a quick tutorial on configuring please see&nbsp;http://www.youtube.com/watch?v=WnuhbFwsJ3M</li>
</ul>
<p>Any changes to the menu itself (adding links, changing where items link to, etc) will need to be made under Structure -&gt; Menus -&gt; Main menu. &nbsp;</p>
<p>-----------</p>
<h3>WYSIWYG</h3>
<p>The WYSIWYG offers additional features and styles that can be applied to any text area.&nbsp;</p>
<p><em><strong>Tip:</strong></em> Click the "Show/hide toolbars" button &nbsp; <img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/show.png" border="0"> &nbsp; to reveal all WYSIWYG options.</p>
<p><img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/toolbar.png" border="0"></p>
<ul>
	<li><strong>Headers:</strong> highlight the text you want to be a header. Click the \'Format\' dropdown and choose a header level.</li>
	<li><strong>Images:</strong> To left or right align an image so text flows around it, highlight the image and click the \'Styles\' dropdown, then choose an image alignment.&nbsp; You can also use the&nbsp;\'Styles\' dropdown to add rounded corners, borders and an oval shape to images.</li>
	<li><strong>Buttons:</strong> Create the red, gold, blue and grey web standard buttons by highlighting a link and choosing the style from the \'Styles\' drodown.&nbsp; See the standards site for requirements on gold and blue buttons - http://asu-ws.29thdrive.com</li>
	<li><strong>Templates:</strong> Add pre-built templates to a page or a pane by choosing the template button &nbsp; <img src="/profiles/openasu/modules/custom/webspark_featurescustom/webspark_extras/images/template.png" border="0"> &nbsp; in the WYSIWYG toolbar.&nbsp; The web standard "Explore Our Programs" box is pre-built for you.&nbsp; Create new templates at /admin/config/content/wysiwyg-templates</li>
</ul>
',
        'summary' => '',
        'format' => 'panopoly_html_text',
        'safe_summary' => '',
      ),
    ),
  ),
  'path' => array(
    'pathauto' => 0,
  ),
  'panelizer' => array(
    'page_manager' => array(
      'entity_type' => 'node',
      'name' => NULL,
      'no_blocks' => 0,
      'css_id' => 'page-page',
      'css' => '',
      'pipeline' => 'ipe',
      'contexts' => array(),
      'relationships' => array(),
      'view_mode' => 'page_manager',
      'css_class' => '',
      'title_element' => 'H2',
      'link_to_entity' => 1,
      'extra' => '',
      'did_uuid' => '16346c80-6fcf-4cee-bf7a-9c0173fc2916',
    ),
  ),
  'machine_name' => FALSE,
  'pathauto_perform_alias' => FALSE,
  'date' => '2014-09-24 14:44:00 -0700',
  'user_uuid' => 'a11a7bc9-a025-4156-835c-8a65da7265e9',
);
  return $nodes;
}
