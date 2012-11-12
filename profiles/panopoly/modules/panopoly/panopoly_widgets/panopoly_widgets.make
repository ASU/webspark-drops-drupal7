; Panopoly Widgets Makefile

api = 2
core = 7.x

; Panopoly - Contrib - Fields

projects[tablefield][version] = 2.0
projects[tablefield][subdir] = contrib

projects[simple_gmap][version] = 1.0
projects[simple_gmap][subdir] = contrib

; Panopoly - Contrib - Widgets

projects[menu_block][version] = 2.3
projects[menu_block][subdir] = contrib

; Panopoly - Contrib - Files & Media

projects[file_entity][version] = 2.x-dev
projects[file_entity][subdir] = contrib
projects[file_entity][download][type] = git
projects[file_entity][download][revision] = 945bf90
projects[file_entity][download][branch] = 7.x-2.x

projects[media][version] = 2.x-dev
projects[media][subdir] = contrib
projects[media][download][type] = git
projects[media][download][revision] = 83c903d
projects[media][download][branch] = 7.x-2.x
projects[media][patch][1836020] = http://drupal.org/files/1836020-check-before-drop-media-update.patch
projects[media][patch][1496624] = http://drupal.org/files/1496624-ensure-media-table.patch

projects[media_youtube][version] = 1.0-beta3
projects[media_youtube][subdir] = contrib
projects[media_youtube][patch][1812976] = http://drupal.org/files/1812976-1x-fix-against-b3.patch

projects[media_vimeo][version] = 1.0-beta5
projects[media_vimeo][subdir] = contrib
projects[media_vimeo][patch][1823078] = http://drupal.org/files/1823078-1x-fix.patch
