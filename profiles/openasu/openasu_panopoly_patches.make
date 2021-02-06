core = 7.x
api = 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; PANOPOLY PROJECT PATCHES
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Patching a Panopoly-provided contrib projects requires 1) overriding Panopoly's makefiles with our own makefile
; directives for the same projects, 2) applying Panopoly's patches that get skipped due to the overriding makefile
; (if any), and then 3) applying our patches.
;
; These projects are installed first, before any other projects in the parent makefile.

; panopoly_core.make

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

; WEBSPARK-1573
projects[date][version] = 2.10
projects[date][subdir] = contrib
projects[date][patch][2449261] = https://www.drupal.org/files/issues/2018-08-30/date-cannot_create_references_to_from_string_offsets-2449261-14.patch
projects[date][patch][2889759] = https://www.drupal.org/files/issues/date-php7Offset-2889759-1.patch
projects[date][patch][2995679] = https://www.drupal.org/files/issues/2018-08-28/date-array_conversion-2995679-2-D7.patch
projects[date][patch][2843367-1] = https://www.drupal.org/files/issues/2019-01-16/2843367-php71-string-offset-47.patch
projects[date][patch][2843367-2] = https://www.drupal.org/files/issues/2843367-php71-string-offset-26.patch
projects[date][patch][3145639] = https://www.drupal.org/files/issues/2020-06-04/date-php74-3145639-2.patch

; panopoly_admin.make

; jQuery Update was moved to Panopoly Core, but is left in Panopoly Admin's
; .make file to retain a stable 1.x branch of Panopoly. See the following URL
; for more information: http://drupal.org/node/2492811
projects[jquery_update][version] = 3.0-alpha5
projects[jquery_update][subdir] = contrib
projects[jquery_update][patch][1251] = patches/ws-1251_jquery-update_downgradeto-1.12.2.patch
; @TODO -- Add patch for lowering jQuery_update's jQuery 1.12 trueversion to 1.12.2.

; Module filter theming changes
; Remove this if https://www.drupal.org/project/module_filter/issues/3075908 is ever adopted.
projects[module_filter][version] = 2.2
projects[module_filter][subdir] = contrib
projects[module_filter][patch][3075908] = https://www.drupal.org/files/issues/2019-08-19/module_filter-top_filter_theming_changes.patch

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
projects[radix_layouts][patch][1610] = patches/ws-1610_tablet-css-width.patch

; panopoly_widgets.make

projects[media][version] = 2.26
projects[media][subdir] = contrib
; WEBSPARK-679 - WYSIWYG + Media module issues
projects[media][patch][679] = patches/webspark-679_fix-HTML-encoded-macros-2028253-10.patch

; WEBSPARK-1404, WEBSPARK-1544, others
projects[views][type] = module
projects[views][subdir] = contrib
projects[views][version] = 3.24
; Add Panopoly patches
projects[views][patch][] = https://www.drupal.org/files/issues/views-exposed-sorts-2037469-26.patch
projects[views][patch][2977851] = https://www.drupal.org/files/issues/2019-09-23/2977851-views-php72-count-14_0.patch
projects[views][patch][2284423] = https://www.drupal.org/files/issues/2019-04-29/views-same_sort_twice-2284423-3.patch
projects[views][patch][3076826] = https://www.drupal.org/files/issues/2019-08-23/views-php7-3076826-2.patch
; Add local patches
projects[views][patch][] = patches/webspark-1404_set-views-handler-filter-maxlength-to-null.patch

; WEBSPARK-1507
projects[panopoly_theme][patch][] = https://www.drupal.org/files/issues/accordion-style-id-fix.2777847.8.patch

; WEBSPARK-819
; Overrides drupal-org.make from project ID: panopoly
; Patches MUST be applied in this order.
;; Panopoly
libraries[tinymce][download][type] = get
libraries[tinymce][download][url] = http://download.moxiecode.com/tinymce/tinymce_3.5.11.zip
libraries[tinymce][patch][1561882] = http://drupal.org/files/1561882-cirkuit-theme-tinymce-3.5.8.patch
libraries[tinymce][patch][2876031] = https://www.drupal.org/files/issues/tinymce-chrome58-fix-2876031-5.patch
;; WEBSPARK-819 patches
libraries[tinymce][patch][2876032] = https://raw.githubusercontent.com/ASU/asu-drupal-modules/master/patches/ws-819_img-padding-TinyMCE.patch
libraries[tinymce][patch][2876033] = https://raw.githubusercontent.com/ASU/asu-drupal-modules/master/patches/ws-819_img-padding-TinyMCE_min.patch

; WEBSPARK-1517
;; Patches Entity API contrib module
projects[entity][type] = module
projects[entity][subdir] = contrib
projects[entity][version] = 1.9
projects[entity][patch][] = https://www.drupal.org/files/issues/warning_array_flip-1803048-16.patch

; WEBSPARK-1903
;; Transliteration + MySQL 8.0.22+ issue fix
projects[transliteration][version] = 3.2
projects[transliteration][subdir] = contrib
projects[transliteration][patch][] = https://www.drupal.org/files/issues/2021-02-05/transliteration-MySQL-8-BINARY-fix-3196961-1.patch
