/* $Id

-- SUMMARY --
BackgroundField is essentially an extension of the CCK ImageField that 
allows a CSS selector and background attributes to be set for a content-
type. This is particularly helpful for allowing your node authors to 
add images to a node that are integrated into the theme of the site.

-- EXAMPLE --
User A creates content-type Foo with 2 BackgroundFields, one with a CSS 
selector for "body" (the html body) and one for "#callout" (a div in 
the theme).
User B can then create a Foo node and add images that will become the 
body background image and the callout background.
Users could continue to create new nodes each specifying their own 
background and callout images unique to the node they create.

-- REQUIREMENTS --
CCK
FileField
ImageField


Note: If you only need the ability to set one theme background via the
drupal admin interface, you might consider the Background module.

-- CONTACT --
Current maintainer:
Jason Yee (jyee) - http://drupal.org/user/712186


