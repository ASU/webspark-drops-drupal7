;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; PANOPOLY PROJECT PATCHES
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Patching a Panopoly-provided contrib projects requires 1) overriding Panopoly's makefiles with our own makefile
; directives for the same projects, 2) applying Panopoly's patches that get skipped due to the overriding makefile
; (if any), and then 3) applying our patches.
;
; These projects are installed first, before any other projects in the parent makefile.

; Media (module)
projects[media][type] = module
projects[media][subdir] = contrib
projects[media][download][type] = "git"
projects[media][download][branch] = "7.x-2.x"
projects[media][download][url] = "http://git.drupal.org/project/media.git"
; v 2.0-alpha3+98-dev - 2014-7-20
projects[media][download][revision] = "63824297d512b1993d4448eb851d2856f2d5df4e"

; Patches - Panopoly make file patches
projects[media][patch][] = https://www.drupal.org/files/issues/media-restore-edit-button-2192981-13.patch
projects[media][patch][] = https://www.drupal.org/files/issues/media-wysiwyg-alt-title-handling-2126697-27.patch
projects[media][patch][] = https://www.drupal.org/files/issues/media-alt-title-double-encoded-2308487-1.patch

; Patches - Webspark
; Review when Media module is upgraded to v. beta1
;; WEBSPARK-679 - WYSIWYG + Media module issues
projects[media][patch][] = patches/webspark-679_fix-HTML-encoded-macros-2028253-10.patch
; Remove when alpha4 or higher is installed.
projects[media][patch][] = patches/webspark-679_wysiwyg-multiple-editors-media-images-breaks.patch


; Radix Layouts (module)
projects[radix_layouts][type] = module
projects[radix_layouts][subdir] = contrib
projects[radix_layouts][version] = 3.4
;  Make Radix layouts conform to ASU's custom CSS to fix background images, etc.
projects[radix_layouts][patch][] = patches/webspark-420_radix-layouts_TPL-customizations.patch

; Field Group
projects[field_group][type] = module
projects[field_group][subdir] = contrib
projects[field_group][version] = 1.4
; Fix "Show" appears in horizontal tab
; https://www.drupal.org/files/issues/field-group-show-ajax-2042681-18-D7.patch
projects[field_group][patch][] = patches/github-148_field-group-show-ajax.patch
