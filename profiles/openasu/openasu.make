api = 2
core = 7.x

;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Drupal Core
;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[drupal][type] = core
projects[drupal][version] = 7.56
; Drupal Core Patches
;projects[drupal][patch][1334818] = https://drupal.org/files/issues/D7-install-profile-ajax-1334818-8.patch

;;;;;;;;;;;;;;;;;;;;;;;;;;;
; The Panopoly Foundation
;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[panopoly_core][version] = 1.48
projects[panopoly_core][subdir] = panopoly

projects[panopoly_images][version] = 1.48
projects[panopoly_images][subdir] = panopoly

projects[panopoly_theme][version] = 1.48
projects[panopoly_theme][subdir] = panopoly

projects[panopoly_magic][version] = 1.48
projects[panopoly_magic][subdir] = panopoly

projects[panopoly_widgets][version] = 1.48
projects[panopoly_widgets][subdir] = panopoly

projects[panopoly_admin][version] = 1.48
projects[panopoly_admin][subdir] = panopoly

projects[panopoly_users][version] = 1.48
projects[panopoly_users][subdir] = panopoly

; The Panopoly Toolset
projects[panopoly_pages][version] = 1.48
projects[panopoly_pages][subdir] = panopoly

projects[panopoly_wysiwyg][version] = 1.48
projects[panopoly_wysiwyg][subdir] = panopoly

projects[panopoly_search][version] = 1.48
projects[panopoly_search][subdir] = panopoly
; Fixes DB update dependency ordering
; projects[panopoly_search][patch][2766677] = patches/panopoly-search-update-dependency-2766677-1.patch

projects[panopoly_test][version] = 1.48
projects[panopoly_test][subdir] = panopoly

; @TODO - Add patches for custom Webspark testing,
projects[panopoly_test][patch][137] = patches/webspark-847_panopoly-test-137-update-v-1.46.patch
projects[panopoly_test][patch][1370] = patches/webspark-847_behat_common.patch
projects[panopoly_test][patch][142] = patches/webspark-944_add-init-config-tests-panopoly-test.patch
projects[panopoly_test][patch][143] = patches/webspark-1066-panopoly-test-v146.patch
projects[panopoly_test][patch][1403] = patches/webspark-1066-panopoly-webspark-add-custom-tests-v143.patch


; ASU-specific, Webspark-agnostic modules (/custom directory contents)
; commenting this out until we update this repo
; @TODO - update the repo with latest modules
;projects[asu_drupal_modules][type] = module
;projects[asu_drupal_modules][directory_name] = custom
;projects[asu_drupal_modules][download][revision] = 9cd96b13a33a2bd112fdecabd36f2d35b0ca83c0
;projects[asu_drupal_modules][download][url] = https://github.com/ASU/asu-drupal-modules.git

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ASU Module Prerequisites
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[better_watchdog_ui][version] = 2.2
projects[better_watchdog_ui][type] = module
projects[better_watchdog_ui][subdir] = contrib

projects[cas_attributes][version] = 1.0-rc3
projects[cas_attributes][type] = module
projects[cas_attributes][subdir] = contrib

projects[email][version] = 1.3
projects[email][subdir] = contrib
projects[email][type] = module

; @TODO v2.0-beta2
projects[feeds][version] = 2.0-alpha9
projects[feeds][type] = module
projects[feeds][subdir] = contrib

projects[feeds_xpathparser][version] = 1.1
projects[feeds_xpathparser][type] = module
projects[feeds_xpathparser][subdir] = contrib

projects[job_scheduler][version] = 2.0-alpha3
projects[job_scheduler][type] = module
projects[job_scheduler][subdir] = contrib

projects[ldap][version] = 2.0-beta8
projects[ldap][type] = module
projects[ldap][subdir] = contrib
;; patch - see https://drupal.org/node/2182413, comment #10 - remove upon ldap update beyond beta8
projects[ldap][patch][2182413] = http://cgit.drupalcode.org/ldap/patch/?id=fe3a3d56ffebc9bd551c6d83a03172fae13517c3

projects[references][version] = 2.1
projects[references][type] = module
projects[references][subdir] = contrib

projects[smtp][version] = 1.4
projects[smtp][subdir] = contrib
projects[smtp][type] = module

projects[viewfield][version] = 2.0
projects[viewfield][type] = module
projects[viewfield][subdir] = contrib

projects[webform][version] = 4.14
projects[webform][type] = module
projects[webform][subdir] = contrib

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ASU Module prerequisites - Webspark Webstandards Components - contrib
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[backgroundfield][version] = 1.5
projects[backgroundfield][type] = module
projects[backgroundfield][subdir] = contrib
;; WEBSPARK-481 - BackgroundField image patch - default_image error
projects[backgroundfield][patch][1841978] = https://www.drupal.org/files/backgroundfield_undefined_index-1841978-18.patch

; CAS SSO Integration
projects[cas][version] = 1.5
projects[cas][subdir] = contrib

; @TODO v.2.0-beta5
projects[chosen][version] = 2.0-beta4
projects[chosen][type] = module
projects[chosen][subdir] = contrib

projects[easy_breadcrumb][version] = 2.12
projects[easy_breadcrumb][type] = module
projects[easy_breadcrumb][subdir] = contrib

projects[entity_view_mode][version] = 1.0-rc1
projects[entity_view_mode][type] = module
projects[entity_view_mode][subdir] = contrib

projects[field_collection][version] = 1.0-beta11
projects[field_collection][type] = module
projects[field_collection][subdir] = contrib

projects[flexslider][version] = 2.0-rc1
projects[flexslider][type] = module
projects[flexslider][subdir] = contrib

; @TODO v1.1 (or v2.5)
projects[fontawesome][version] = 1.0
projects[fontawesome][type] = module
projects[fontawesome][subdir] = contrib

; @TODO v1.15
projects[google_appliance][version] = 1.12
projects[google_appliance][type] = module
projects[google_appliance][subdir] = contrib

projects[maxlength][version] = 3.2-beta2
projects[maxlength][type] = module
projects[maxlength][subdir] = contrib

;; @TODO - Remove patch when file when submitted patch gets pulled into module
projects[missing_module][type] = module
projects[missing_module][subdir] = contrib
projects[missing_module][download][type] = "git"
projects[missing_module][download][branch] = "7.x-1.x"
projects[missing_module][download][url] = "http://git.drupal.org/project/missing_module.git"
projects[missing_module][download][revision] = 19492ccee8b8ac683b3a384e8663c09af55dc3af
projects[missing_module][patch][2854074] = patches/webspark-1052_missing-module_improvements-to-ux_2854074-5.patch

projects[panels_tabs][version] = 2.x-dev
projects[panels_tabs][type] = module
projects[panels_tabs][subdir] = contrib

;; @TODO - Update away from Dev commit of quicktabs
projects[quicktabs][type] = module
projects[quicktabs][subdir] = contrib
projects[quicktabs][download][type] = "git"
projects[quicktabs][download][branch] = "7.x-3.x"
projects[quicktabs][download][url] = "http://git.drupal.org/project/quicktabs.git"
projects[quicktabs][download][revision] = "758de4cc4995149a2de1d566b4209ec343581d27"

; Added for ASU Dir module
projects[react][version] = 2.0-beta2
projects[react][type] = module
projects[react][subdir] = contrib

;; Webspark Megamenu
projects[special_menu_items][version] = 2.0
projects[special_menu_items][subdir] = contrib
projects[special_menu_items][type] = module

projects[tb_megamenu][version] = 1.0-rc2
projects[tb_megamenu][type] = module
projects[tb_megamenu][subdir] = contrib
;; TODO - PATCH the CSS for tb_megamenu
projects[tb_megamenu][patch][] = patches/webspark-919_tb-megamenu_fix-breakpoints.patch
projects[tb_megamenu][patch][] = patches/webspark-935_tb-megamenu_fix-submenu-removal_7.x.patch
projects[tb_megamenu][patch][] = patches/webspark-1007-redux-tb_megamenu-tab_accessibility-7.x.patch
projects[tb_megamenu][patch][] = patches/webspark-1018_tb-megamenu_removing-mobile-button-for-ADA_7.x.patch

;projects[uuid_features][version] = 1.0-alpha4
;; grabbing alpha-4+dev-37 commit
projects[uuid_features][type] = module
projects[uuid_features][subdir] = contrib
projects[uuid_features][download][type] = "git"
projects[uuid_features][download][branch] = "7.x-1.x"
projects[uuid_features][download][url] = "http://git.drupal.org/project/uuid_features.git"
projects[uuid_features][download][revision] = "55a2d5070b6f238f40372070f70314cc4f8197d8"

projects[video_embed_field][version] = 2.0-beta11
projects[video_embed_field][type] = module
projects[video_embed_field][subdir] = contrib

projects[wysiwyg_template][version] = 2.12
projects[wysiwyg_template][type] = module
projects[wysiwyg_template][subdir] = contrib

; copied from asu_drupal_modules.make since the asu_drupal_modules repo needs to be updated and the
; asu_drupal_modules.make file is being ignored at the moment
; todo: remove if we go back to building from repo
projects[views_bootstrap][version] = 3.1
projects[views_bootstrap][type] = module
projects[views_bootstrap][subdir] = contrib

; ASU RFI make file contents

; Upload multidev and patch it

projects[multiblock][version] = 1.1
projects[multiblock][type] = module
projects[multiblock][subdir] = contrib
projects[multiblock][patch][] = https://www.drupal.org/files/issues/multiblock_cache-2185235-5.patch
projects[multiblock][patch][] = https://www.drupal.org/files/fix_config_per_instance-1370966-5.patch

; Added RFI dependencies here, vs. in openasu.make

projects[views_data_export][version] = 3.0-beta9
projects[views_data_export][type] = module
projects[views_data_export][subdir] = contrib

projects[mimemail][version] = 1.0-beta4
projects[mimemail][type] = module
projects[mimemail][subdir] = contrib

projects[honeypot][version] = 1.22
projects[honeypot][type] = module
projects[honeypot][subdir] = contrib

; pre-req for mimemail
projects[mailsystem][version] = 2.34
projects[mailsystem][type] = module
projects[mailsystem][subdir] = contrib

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

projects[modernizr][version] = 3.9
projects[modernizr][subdir] = contrib

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ASU Module prerequisites - Webstandards additions - Libraries
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

libraries[ajax_solr][download][type] = get
libraries[ajax_solr][download][url] = https://github.com/evolvingweb/ajax-solr/archive/master.zip
libraries[ajax_solr][directory_name] = ajax_solr
libraries[ajax_solr][destination] = libraries
libraries[ajax_solr][download][sha256] = d79493f28c47e8d5871d938d7146ab701f8666b785f50e00d9ab29e3a79f4376

; 1 of 2 - CAS
libraries[CAS][download][type] = get
libraries[CAS][download][url] = https://github.com/Jasig/phpCAS/archive/1.3.5.zip
libraries[CAS][download][subtree] = phpCAS-1.3.5/source
libraries[CAS][directory_name] = CAS/source
;libraries[CAS][download][sha256] = c8c73945c3503991d19e2a1f7f14b51c293dd2ed9ebae974450a85da03ca3eee
; 2 of 2
libraries[CAS_2][download][type] = file
libraries[CAS_2][download][url] = https://raw.githubusercontent.com/Jasig/phpCAS/1.3.5/CAS.php
libraries[CAS_2][directory_name] = CAS
;libraries[CAS_2][download][sha256] = 74a3eeed33e84d927884a2cf01ab10c33cc445e891c6d773996ffb19cf841d23

libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries
libraries[chosen][download][sha256] = 410147ddfb08f9a87f0272516fff7cd5ed5a4f0777c76f1b298d1106aa8405bd

libraries[flexslider][download][type] = get
libraries[flexslider][download][url] = https://github.com/woothemes/FlexSlider/archive/version/2.2.2.zip
libraries[flexslider][download][sha256] = bd72421a8aa6f4b9cd3575f4eb58651f2b43c5dc00f0f8f80a373f71b5d1efcc

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

; 1 of 2 - Modernizr.js
libraries[modernizr][download][type] = get
libraries[modernizr][download][url] = https://raw.githubusercontent.com/Modernizr/Modernizr/v2.8.3/modernizr.js
libraries[modernizr][directory_name] = modernizr
libraries[modernizr][download][sha256] = 7dfc3ef73c1284c7aff3c5cdac3812d212c8b899037d7860c8ba20a1defb9a7f
; 2 of 2
libraries[modernizr_feature_d][download][type] = get
libraries[modernizr_feature_d][download][url] = https://github.com/Modernizr/Modernizr/archive/v2.8.3.zip
libraries[modernizr_feature_d][download][subtree] = Modernizr-2.8.3/feature-detects
libraries[modernizr_feature_d][directory_name] = modernizr/feature-detects
libraries[modernizr_feature_d][download][sha256] = e9e8165a6ec2df5c9b72cafcee3c2b830656e010d9f64bbb1a571747359a8bd4

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
