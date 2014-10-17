The Easy Breadcrumb module provides a plug-and-play block to be embedded in your
pages, typically at some place near the page's header. Easy Breadcrumb takes
advantage of the work you've already done for generating your paths' alias,
while it naturally encourages the creation of semantic and consistent paths.
This modules is currently available for Drupal 6.x and 7.x.

Easy Breadcrumb uses the current URL (path alias) and the current page's title
to automatically extract the breadcrumb's segments and its respective links.
Easy Breadcrumb is really a plug and play module, it auto-generates the
breadcrumb by using the current URL, the user needs to do anything to get it
working.

For example, having an URL like "gallery/videos/once-a-time-in-cartagena",
EasyBreadcrumb will automatically produces the breadcrumb
"Home >> Gallery >> Videos >> Once a time in Cartagena" or
"Home >> Videos >> Once a Time in Cartagena". Again, the breadcrumb presentation
will vary depending on your module's settings.

Requirements
  * Pathauto

Recommended modules:
  * Transliteration
      is useful if your site is likely contain characters beyond ASCII
      128. Like: ñ, ó, among others. After activate it, go to
      admin/config/search/path/settings and check the option Transliterate
      prior to creating alias.

Configuration:

  To start using it, just go to the admin modules page
  (URL "admin/modules/list"), locate it under the category "others" and activate
  it, then go to the blocks list page (URL "admin/structure/block") and locate
  the block named "Easy Breadcrumb", and configure it like any other block
  (region, URLs, etc.).

  The configuration page of this module is under
  "Admin > Configuration > User Interface > Easy Breadcrumb"
  (URL "admin/config/user-interface/easy-breadcrumb").

  Configurable parameters:

    * Disable the default Drupal's breadcrumb.
    * Include / Exclude invalid path alias as plain-text segments.
    * Include / Exclude the front page as a segment in the breadcrumb.
    * Include / Exclude the current page's title as a segment in the breadcrumb.
    * Use the real page's title when it is available instead of always deducing
      it from the URL.
    * Print the page's title as a link or as plain-text segment.
    * Use a custom separator between the breadcrumb's segments.
    * Choose a transformation mode for the segments' title.
    * Make the 'capitalizator' ignore some words (words not to be capitalized).

Module Page: http://drupal.org/project/easy_breadcrumb
