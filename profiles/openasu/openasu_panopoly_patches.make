;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; PANOPOLY PROJECT PATCHES
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Patching a Panopoly-provided contrib projects requires 1) overriding Panopoly's makefiles with our own makefile
; directives for the same projects, 2) applying Panopoly's patches that get skipped due to the overriding makefile
; (if any), and then 3) applying our patches.
;
; These projects are installed first, before any other projects in the parent makefile.

; Media (module) - matches Panopoly 1.37 (from panopoly_widgets.make)
projects[media][type] = module
projects[media][subdir] = contrib
projects[media][version] = 2.0-beta1
projects[media][sha256] = 4225713bdf9bf6f0eab8a2db92eb8c114125597d853f0a2d1cece71917f81d03
projects[media][patch][2126697] = https://www.drupal.org/files/issues/media_wysiwyg_2126697-53.patch
projects[media][patch][2308487] = https://www.drupal.org/files/issues/media-alt-title-double-encoded-2308487-2.patch
projects[media][patch][2084287] = https://www.drupal.org/files/issues/media-file-name-focus-2084287-2.patch
projects[media][patch][2534724] = https://www.drupal.org/files/issues/media-browser_opens_twice-2534724-53.patch
; Patches - Webspark
; WEBSPARK-679 - WYSIWYG + Media module issues
projects[media][patch][] = patches/webspark-679_fix-HTML-encoded-macros-2028253-10.patch
; following taken from #56 on https://www.drupal.org/node/2317519
projects[media][patch][] = patches/webspark-679_wysiwyg-multiple-editors-media-images-breaks.patch

; Radix Layouts (module)
projects[radix_layouts][type] = module
projects[radix_layouts][subdir] = contrib
projects[radix_layouts][version] = 3.4
projects[radix_layouts][sha256] =  9ead2347754b478b71cfa0ee16f343da1046a2e86e4071e56a5411cdb7f8a862
;  Make Radix layouts conform to ASU's custom CSS to fix background images, etc.
projects[radix_layouts][patch][101] = patches/webspark-420_radix-layouts_TPL-customizations.patch
projects[radix_layouts][patch][102] = patches/webspark-743_add-two-brenham-layouts.patch
projects[radix_layouts][patch][103] = patches/webspark-743_added-png.patch

; Field Group
projects[field_group][type] = module
projects[field_group][subdir] = contrib
projects[field_group][version] = 1.5
projects[field_group][sha256] = 39cab5e1d126d2a0dc293205de1b837df66a03b9108d87d216965cd004f4ad28
; Fix "Show" appears in horizontal tab
; https://www.drupal.org/files/issues/field-group-show-ajax-2042681-18-D7.patch
projects[field_group][patch][2042681] = https://www.drupal.org/files/issues/field-group-show-ajax-2042681-18-D7.patch

projects[module_filter][type] = module
projects[module_filter][subdir] = contrib
projects[module_filter][version] = 2.0
projects[module_filter][sha256] = ab34514e6c8071fd6548600191575818ca11e013fd848b541766ac426278b977
projects[module_filter][patch][] = patches/nojira-module_filter-fix_layout_issue.patch

projects[token][version] = 1.6
projects[token][subdir] = contrib
; Fixes arrows/theming issue in browse tokens window
projects[token][patch][2773825] = patches/webspark-897_token-browse-available-theme-fixes-2773825-1.patch