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
; v 2.0-beta1
projects[media][version] = 2.0-beta1
projects[media][sha256] = 4225713bdf9bf6f0eab8a2db92eb8c114125597d853f0a2d1cece71917f81d03

; Patches - Panopoly make file patches
projects[media][patch][] = https://www.drupal.org/files/issues/media-wysiwyg-alt-title-handling-2126697-27.patch
projects[media][patch][] = https://www.drupal.org/files/issues/media-alt-title-double-encoded-2308487-1.patch

; Patches - Webspark
; Review when Media module is upgraded to v. beta1
;; WEBSPARK-679 - WYSIWYG + Media module issues
projects[media][patch][] = patches/webspark-679_fix-HTML-encoded-macros-2028253-10.patch

; Radix Layouts (module)
projects[radix_layouts][type] = module
projects[radix_layouts][subdir] = contrib
projects[radix_layouts][version] = 3.4
;  Make Radix layouts conform to ASU's custom CSS to fix background images, etc.
projects[radix_layouts][patch][] = patches/webspark-420_radix-layouts_TPL-customizations.patch

; Field Group
projects[field_group][type] = module
projects[field_group][subdir] = contrib
projects[field_group][version] = 1.5
; Fix "Show" appears in horizontal tab
; https://www.drupal.org/files/issues/field-group-show-ajax-2042681-18-D7.patch
projects[field_group][patch][2042681] = https://www.drupal.org/files/issues/field-group-show-ajax-2042681-18-D7.patch

projects[module_filter][type] = module
projects[module_filter][subdir] = contrib
projects[module_filter][version] = 2.0
projects[module_filter][patch][] = patches/nojira-module_filter-fix_layout_issue.patch
