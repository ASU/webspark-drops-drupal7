;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; PANOPOLY PROJECT PATCHES
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Patching a Panopoly-provided contrib projects requires 1) overriding Panopoly's makefiles with our own makefile
; directives for the same projects, 2) applying Panopoly's patches that get skipped due to the overriding makefile
; (if any), and then 3) applying our patches.
;
; These projects are installed first, before any other projects in the parent makefile.

; panopoly_core.make

projects[fieldable_panels_panes][type] = module
projects[fieldable_panels_panes][subdir] = contrib
projects[fieldable_panels_panes][version] = 1.11
projects[fieldable_panels_panes][sha256] = db07832725054a264dfe536ac264f06032a9f816bf716bb89bc86667db5d7fa2
projects[fieldable_panels_panes][patch][2826205] = https://www.drupal.org/files/issues/fieldable_panels_panes-n2826205-39.patch
; Webspark - Fixes undefined index: bundle error - Will go into v1.12
projects[fieldable_panels_panes][patch][2825835] = patches/ws-1257_fpp-errors-after-bad-deletion_2825835.patch

projects[panelizer][version] = 3.4
projects[panelizer][subdir] = contrib
projects[panelizer][patch][1549608] = https://www.drupal.org/files/issues/panelizer-n1549608-26.patch
projects[panelizer][patch][2788851] = https://www.drupal.org/files/issues/panelizer-administer-panelizer-2788851-2.patch
; WEBSPARK-1033 - In panelizer dev branch on drupal.org; Will go into v3.5
projects[panelizer][patch][2843119] = https://www.drupal.org/files/issues/panelizer-undefined_index-2843119-D7_2.patch

projects[token][version] = 1.7
projects[token][subdir] = contrib
projects[token][sha256] = a84b6a1f43798d8d9da31915aa25fce0f62f59fae18c71e0775157e7aa9e1e44
; Webspark - Fixes arrows/theming issue in browse tokens window
projects[token][patch][2773825] = patches/webspark-897_token-browse-available-theme-fixes-2773825-1.patch

; panopoly_admin.make

; jQuery Update was moved to Panopoly Core, but is left in Panopoly Admin's
; .make file to retain a stable 1.x branch of Panopoly. See the following URL
; for more information: http://drupal.org/node/2492811
projects[jquery_update][version] = 3.0-alpha5
projects[jquery_update][subdir] = contrib
projects[jquery_update][patch][1251] = patches/ws-1251_jquery-update_downgradeto-1.12.2.patch
; @TODO -- Add patch for lowering jQuery_update's jQuery 1.12 trueversion to 1.12.2.

; panopoly_theme.make

projects[radix_layouts][type] = module
projects[radix_layouts][subdir] = contrib
projects[radix_layouts][version] = 3.4
projects[radix_layouts][sha256] =  9ead2347754b478b71cfa0ee16f343da1046a2e86e4071e56a5411cdb7f8a862
; WEBSPARK-420, etc. - Make Radix layouts conform to ASU's custom CSS to fix background images, etc.
projects[radix_layouts][patch][101] = patches/webspark-420_radix-layouts_TPL-customizations.patch
projects[radix_layouts][patch][102] = patches/webspark-743_add-two-brenham-layouts.patch
projects[radix_layouts][patch][103] = patches/webspark-743_added-png.patch
projects[radix_layouts][patch][104] = patches/webspark-1003-remove-section-tags-radix-layouts.patch

; panopoly_widgets.make

projects[media][version] = 2.19
projects[media][subdir] = contrib
; WEBSPARK-679 - WYSIWYG + Media module issues
projects[media][patch][679] = patches/webspark-679_fix-HTML-encoded-macros-2028253-10.patch
