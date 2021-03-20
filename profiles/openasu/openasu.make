core = 7.x
api = 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Drupal Core
;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[drupal][type] = core
projects[drupal][version] = 7.78

; Drupal Core Patches

;projects[drupal][patch][1334818] = https://drupal.org/files/issues/D7-install-profile-ajax-1334818-8.patch
projects[drupal][patch][1803048] = patches/ws-1514_array-flip-error-travis-ci-tests_1803048.patch
projects[drupal][patch][1353] = patches/ws-1353_update-output-DOM-cleanup.patch
projects[drupal][patch][1497] = patches/ws-1497_removed-seven-theme-IE-css.patch
projects[drupal][patch][948516] = https://www.drupal.org/files/issues/2019-08-09/drupal-948516-fieldset-arrows-43.patch

;;;;;;;;;;;;;;;;;;;;;;;;;;;
; The Panopoly Foundation
;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[panopoly_core][version] = 1.76
projects[panopoly_core][subdir] = panopoly

projects[panopoly_images][version] = 1.76
projects[panopoly_images][subdir] = panopoly

projects[panopoly_theme][version] = 1.76
projects[panopoly_theme][subdir] = panopoly
; v1.76 patch
projects[panopoly_theme][patch][] = i1875_panopoly-theme_v1.76-diff.patch

projects[panopoly_magic][version] = 1.76
projects[panopoly_magic][subdir] = panopoly
; Validation error with reusable FPPs. Updated in 1.52; Custom patch different from drupal.org/node/2813395
; projects[panopoly_magic][patch][2813395] = patches/ws-1236_title-cant-reuse-error_2813395.patch
projects[panopoly_magic][patch][] = patches/i1875_panopoly-magic_v1.76-diff.patch

projects[panopoly_widgets][version] = 1.76
projects[panopoly_widgets][subdir] = panopoly
projects[panopoly_widgets][patch][] = patches/i1875_panopoly-widgets_v1.76-diff.patch

projects[panopoly_admin][version] = 1.76
projects[panopoly_admin][subdir] = panopoly

projects[panopoly_users][version] = 1.76
projects[panopoly_users][subdir] = panopoly

; The Panopoly Toolset
projects[panopoly_pages][version] = 1.76
projects[panopoly_pages][subdir] = panopoly

projects[panopoly_wysiwyg][version] = 1.76
projects[panopoly_wysiwyg][subdir] = panopoly

projects[panopoly_search][version] = 1.76
projects[panopoly_search][subdir] = panopoly
; Fixes DB update dependency ordering
; projects[panopoly_search][patch][2766677] = patches/panopoly-search-update-dependency-2766677-1.patch

projects[panopoly_test][version] = 1.76
projects[panopoly_test][subdir] = panopoly
; ASU custom tests and modifications
;projects[panopoly_test][patch][137] = patches/webspark-847_panopoly-test-137-update-v-1.46.patch
;projects[panopoly_test][patch][1370] = patches/webspark-847_behat_common.patch
;projects[panopoly_test][patch][142] = patches/webspark-944_add-init-config-tests-panopoly-test.patch
;projects[panopoly_test][patch][143] = patches/webspark-1066-panopoly-test-v146.patch
; Last patch must be applied until the patches are combined down the road
;projects[panopoly_test][patch][1560] = patches/ws-1560-1353_panopoly-behat-widget-name-changes.patch
projects[panopoly_test][patch][1761] = i1875_panopoly-test_v1.76-patch-behat-dir.diff.patch
projects[panopoly_test][patch][1762] = i1875_panopoly-test_v1.76-patch-gitignore.diff.patch

; ASU-specific, Webspark-agnostic modules (/custom directory contents)
; No longer pulled from asu_drupal_modules repo

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ASU Module Prerequisites -- Webspark
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Latest Better Watchdog UI
projects[better_watchdog_ui][type] = module
projects[better_watchdog_ui][subdir] = contrib
projects[better_watchdog_ui][version] = 3.1

projects[cas_attributes][version] = 1.0-rc3
projects[cas_attributes][type] = module
projects[cas_attributes][subdir] = contrib

projects[email][version] = 1.3
projects[email][subdir] = contrib
projects[email][type] = module

projects[feeds][type] = module
projects[feeds][subdir] = contrib
projects[feeds][download][type] = "git"
projects[feeds][download][branch] = "7.x-2.x"
projects[feeds][download][url] = "https://git.drupalcode.org/project/feeds.git"
projects[feeds][download][revision] = "2ae6421979af46752c2697759567d85b5a79c9e1"

projects[feeds_xpathparser][version] = 1.1
projects[feeds_xpathparser][type] = module
projects[feeds_xpathparser][subdir] = contrib

projects[job_scheduler][version] = 2.0
projects[job_scheduler][type] = module
projects[job_scheduler][subdir] = contrib

projects[ldap][type] = module
projects[ldap][subdir] = contrib
projects[ldap][version] = 2.5
; WEBSPARK-1926 - LDAP - PHP 7.4 patches
projects[ldap][patch][1926] = patches/i1926_ldap_php7.4-compliance.patch

projects[references][type] = module
projects[references][subdir] = contrib
projects[references][download][type] = "git"
projects[references][download][branch] = "7.x-2.x"
projects[references][download][url] = "https://git.drupalcode.org/project/references.git"
projects[references][download][revision] = "a7ad6b794f72dd4e669706b64bd8d6f1612cc0b4"

projects[smtp][subdir] = contrib
projects[smtp][type] = module
projects[smtp][download][type] = "git"
projects[smtp][download][branch] = "7.x-1.x"
projects[smtp][download][url] = "https://git.drupalcode.org/project/smtp.git"
projects[smtp][download][revision] = "47f4114b1e6d357708b6ffcade01241a11c41ef1"
; https://www.drupal.org/project/webform/issues/2966816
projects[smtp][patch][] = https://www.drupal.org/files/issues/2018-11-13/smtp-filepath_uri-2966816-27-D7_0.patch


projects[viewfield][version] = 2.0
projects[viewfield][type] = module
projects[viewfield][subdir] = contrib

projects[webform][version] = 4.19
projects[webform][type] = module
projects[webform][subdir] = contrib
projects[webform][patch][2894251] = https://www.drupal.org/files/issues/empty-pages-email-2894251-8.patch

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ASU Module prerequisites - Webspark Web Standards components - contrib
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[backgroundfield][version] = 1.5
projects[backgroundfield][type] = module
projects[backgroundfield][subdir] = contrib

; From https://www.drupal.org/files/backgroundfield_undefined_index-1841978-18.patch
; Webspark-1069
projects[backgroundfield][patch][1936252] = patches/webspark-1069-media-support-and-undefined-index.patch

; CAS SSO Integration
projects[cas][version] = 1.7
projects[cas][subdir] = contrib

projects[chosen][version] = 2.1
projects[chosen][type] = module
projects[chosen][subdir] = contrib

projects[easy_breadcrumb][version] = 2.17
projects[easy_breadcrumb][type] = module
projects[easy_breadcrumb][subdir] = contrib
projects[easy_breadcrumb][patch][3107889] = https://www.drupal.org/files/issues/2020-02-27/easy_breadcrumb_schema_no_dep.patch

projects[entity_view_mode][version] = 1.0-rc1
projects[entity_view_mode][type] = module
projects[entity_view_mode][subdir] = contrib

projects[field_collection][type] = module
projects[field_collection][subdir] = contrib
projects[field_collection][version] = 1.1
;projects[field_collection][download][branch] = "7.x-1.x"
;projects[field_collection][download][url] = "https://git.drupalcode.org/project/field_collection.git"
;projects[field_collection][download][revision] = "5f127681fcada4df97ce2903e65e1e4c52cc0dcd"

projects[flexslider][version] = 2.0-rc2
projects[flexslider][type] = module
projects[flexslider][subdir] = contrib

; @TODO v1.1 (or v2.5)
projects[fontawesome][version] = 1.0
projects[fontawesome][type] = module
projects[fontawesome][subdir] = contrib

projects[google_cse][version] = 2.5
projects[google_cse][type] = module
projects[google_cse][subdir] = contrib

projects[maxlength][version] = 3.3
projects[maxlength][type] = module
projects[maxlength][subdir] = contrib

projects[missing_module][type] = module
projects[missing_module][version] = 1.2
projects[missing_module][subdir] = contrib

projects[panels_tabs][version] = 2.x-dev
projects[panels_tabs][type] = module
projects[panels_tabs][subdir] = contrib

;; @TODO - Update away from Dev commit of quicktabs
projects[quicktabs][type] = module
projects[quicktabs][subdir] = contrib
projects[quicktabs][download][type] = "git"
projects[quicktabs][download][branch] = "7.x-3.x"
projects[quicktabs][download][url] = "http://git.drupalcode.org/project/quicktabs.git"
projects[quicktabs][download][revision] = "758de4cc4995149a2de1d566b4209ec343581d27"

; Added for ASU Dir module
projects[react][version] = 2.0-beta2
projects[react][type] = module
projects[react][subdir] = contrib

;; Webspark Megamenu
projects[special_menu_items][version] = 2.0
projects[special_menu_items][subdir] = contrib
projects[special_menu_items][type] = module

; TB Megamenu
projects[tb_megamenu][type] = module
projects[tb_megamenu][subdir] = contrib
projects[tb_megamenu][download][branch] = "7.x-1.x"
projects[tb_megamenu][download][url] = "https://git.drupalcode.org/project/tb_megamenu.git"
projects[tb_megamenu][download][revision] = "dd9469f608002256657da56bf71128d542d25243"
;; TODO - PATCH the CSS for tb_megamenu
projects[tb_megamenu][patch][] = patches/webspark-919_tb-megamenu_fix-breakpoints.patch

projects[tb_megamenu][patch][] = patches/webspark-1007-redux-tb_megamenu-tab_accessibility-7.x.patch
projects[tb_megamenu][patch][] = patches/webspark-1018_tb-megamenu_removing-mobile-button-for-ADA_7.x.patch
; added patches/ path to 1304 path - rknesbit
projects[tb_megamenu][patch][] = patches/webspark-1086_tb-megamenu_fix-undefined-index_2571547-23.patch
projects[tb_megamenu][patch][] = patches/webspark-1379-AND-webspark-1304-tb_megamenu-classes-missing-AND-update-data-col-sizes-v1.64.patch

; UUID Features Integration
;projects[uuid_features][version] = 1.0-alpha4
;; grabbing latest version of DEV as of 2018-06-17
projects[uuid_features][type] = module
projects[uuid_features][subdir] = contrib
projects[uuid_features][download][type] = "git"
projects[uuid_features][download][branch] = "7.x-1.x"
projects[uuid_features][download][url] = "https://git.drupalcode.org/project/uuid_features.git"
projects[uuid_features][download][revision] = "63a676b0243838a1624a758a373aaca9444cce06"

projects[video_embed_field][version] = 2.0-beta11
projects[video_embed_field][type] = module
projects[video_embed_field][subdir] = contrib

projects[wysiwyg_template][version] = 2.12
projects[wysiwyg_template][type] = module
projects[wysiwyg_template][subdir] = contrib

; copied from asu_drupal_modules.make since the asu_drupal_modules repo needs to be updated and the
; asu_drupal_modules.make file is being ignored at the moment
; todo: remove if we go back to building from repo
projects[views_bootstrap][version] = 3.2
projects[views_bootstrap][type] = module
projects[views_bootstrap][subdir] = contrib

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ASU Custom (modules/custom) module dependencies
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; ASU News + Events dependencies
projects[addtocal][version] = 1.0
projects[addtocal][type] = module
projects[addtocal][subdir] = contrib

projects[feeds_tamper][version] = 1.2
projects[feeds_tamper][type] = module
projects[feeds_tamper][subdir] = contrib

projects[field_ellipsis][version] = 1.4
projects[field_ellipsis][type] = module
projects[field_ellipsis][subdir] = contrib

; ASU RFI dependencies - make file contents
; Upload multidev and patch it
projects[multiblock][version] = 1.1
projects[multiblock][type] = module
projects[multiblock][subdir] = contrib
projects[multiblock][patch][] = https://www.drupal.org/files/issues/multiblock_cache-2185235-5.patch
projects[multiblock][patch][] = https://www.drupal.org/files/fix_config_per_instance-1370966-5.patch

projects[views_data_export][version] = 3.2
projects[views_data_export][type] = module
projects[views_data_export][subdir] = contrib

projects[mimemail][version] = 1.1
projects[mimemail][type] = module
projects[mimemail][subdir] = contrib
projects[mimemail][patch][2947006] = https://www.drupal.org/files/issues/2018-05-28/mimemail-support_php_72-2947006-4.patch

projects[honeypot][version] = 1.22
projects[honeypot][type] = module
projects[honeypot][subdir] = contrib

; pre-req for mimemail
projects[mailsystem][version] = 2.35
projects[mailsystem][type] = module
projects[mailsystem][subdir] = contrib

projects[feeds_crawler][version] = 1.0-beta2
projects[feeds_crawler][type] = module
projects[feeds_crawler][subdir] = contrib

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Bootstrap and Theme Frameworks - Moved to Webspark repo (see WEBSPARK-366)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Base Theme - Kalatheme
;; @TODO - Remove completely

projects[kalatheme][version] = 3.0-rc2
projects[kalatheme][type] = theme
;; WEBSPARK-188 - CSS img url fix
projects[kalatheme][patch][] = patches/webspark-188.kalatheme-css-img-urls.patch
;; WEBSPARK-361 - Panopoly TPLs and row-full class
projects[kalatheme][patch][] = patches/webspark-361-kalatheme-panopoly-tpl-class-update.patch
;; WEBSPARK-565 - Added views-view-table.tpl.php, pending update to kalatheme
projects[kalatheme][patch][] = patches/webspark-565-add-views-tpl-to-kalatheme.patch
;; rjbonnel Github patches for spelling (remove when fixed in kalatheme update upstream)
projects[kalatheme][patch][] = patches/nojira-20150812-kalatheme-spelling-fix.patch
projects[kalatheme][patch][] = patches/nojira-20150812-kalatheme-admin-spelling-fix.patch
projects[kalatheme][patch][] = patches/nojira-20160715-kalatheme_fix-missing-index.patch
projects[kalatheme][patch][] = patches/webspark-1225-kalatheme-undefined-index-fix.patch

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ASU Module prerequisites - Webstandards additions - Libraries
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

libraries[ajax_solr][download][type] = get
libraries[ajax_solr][download][url] = https://github.com/evolvingweb/ajax-solr/archive/master.zip
libraries[ajax_solr][directory_name] = ajax_solr
libraries[ajax_solr][destination] = libraries
libraries[ajax_solr][download][sha256] = 5445d07305f99719e1cb9f277aaf0c3315728b0ea34df98f6990b45870007183

; 1 of 2 - CAS
libraries[CAS][download][type] = get
libraries[CAS][download][url] = https://github.com/Jasig/phpCAS/archive/1.3.6.zip
libraries[CAS][download][subtree] = phpCAS-1.3.6/source
libraries[CAS][directory_name] = CAS/source
;libraries[CAS][download][sha256] = 97d3ae33445c42d20c4933c888724247b21f0a4282b0e5b2cf9b7b08410d1c59
; 2 of 2
libraries[CAS_2][download][type] = file
libraries[CAS_2][download][url] = https://raw.githubusercontent.com/Jasig/phpCAS/1.3.6/CAS.php
libraries[CAS_2][directory_name] = CAS
;libraries[CAS_2][download][sha256] = c21352f1cef5fa8622f71637c7bfc8328aac4d15d34ad914859c2e725109d397

libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries
libraries[chosen][download][sha256] = 410147ddfb08f9a87f0272516fff7cd5ed5a4f0777c76f1b298d1106aa8405bd

libraries[flexslider][download][type] = get
libraries[flexslider][download][url] = https://github.com/woothemes/FlexSlider/archive/version/2.7.2.zip
;libraries[flexslider][download][sha256] = bd72421a8aa6f4b9cd3575f4eb58651f2b43c5dc00f0f8f80a373f71b5d1efcc
; @TODO - update SHA + download individual elements (vs. the entire library with demos, etc.)

; 1 of 2 - Font Awesome
libraries[fontawesome_css][download][type] = get
libraries[fontawesome_css][download][url] = https://github.com/FortAwesome/Font-Awesome/archive/v4.6.3.zip
libraries[fontawesome_css][download][subtree] = Font-Awesome-4.6.3/css
libraries[fontawesome_css][directory_name] = fontawesome/css
libraries[fontawesome_css][download][sha256] = dfae6770e811947487a22e731900f4cb478f69f0f4675bf8fc563885cf86c32e
; 2 of 2
libraries[fontawesome_fonts][download][type] = get
libraries[fontawesome_fonts][download][url] = https://github.com/FortAwesome/Font-Awesome/archive/v4.6.3.zip
libraries[fontawesome_fonts][download][subtree] = Font-Awesome-4.6.3/fonts
libraries[fontawesome_fonts][directory_name] = fontawesome/fonts

; 1 of 2 - jQTree
libraries[jqtree][download][type] = file
libraries[jqtree][download][url] = https://raw.githubusercontent.com/mbraak/jqTree/1.3.4/tree.jquery.js
libraries[jqtree][directory_name] = jqtree
libraries[jqtree][download][sha256] = 9a4580bc14b620f10af01954403e5911dc8fa805ec2036db45f640a2bd9c40c6
; 2 of 2
libraries[jqtree_css][download][type] = file
libraries[jqtree_css][download][url] = https://raw.githubusercontent.com/mbraak/jqTree/1.3.4/jqtree.css
libraries[jqtree_css][directory_name] = jqtree
libraries[jqtree_css][download][sha256] = bde5928fc25fa22625e4a1ab42e7abff041a13b7dcb6f9a29ca46d50b1a2dbf8

; React JS - For ASU Dir module - https://github.com/facebook/react/releases
libraries[reactjs][download][type] = get
libraries[reactjs][download][url] = https://github.com/facebook/react/releases/download/v0.14.7/react-0.14.7.zip
libraries[reactjs][download][subtree] = react-0.14.7/build
libraries[reactjs][directory_name] = react/build
libraries[reactjs][download][sha256] = 859ef4a715ded8aa32ab96544c26d0f7b7eba09dec964d44a6c63e3d8d842034

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; PANOPOLY PROJECT PATCHES
; The projects in the file(s) listed below are overridden versions of contrib modules maintained by Panopoly.
; They are installed by Drush make before any other projects listed in any parent .make files - including
; Panopoly's make files.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
includes[panopoly_patches] = openasu_panopoly_patches.make
