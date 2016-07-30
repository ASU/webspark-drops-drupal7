api = 2
core = 7.x

; Drupal Core

projects[drupal][type] = core
projects[drupal][version] = 7.44
; Drupal Core Patches
projects[drupal][patch][1334818] = https://drupal.org/files/issues/D7-install-profile-ajax-1334818-8.patch

; The Panopoly Foundation

projects[panopoly_core][version] = 1.37
projects[panopoly_core][subdir] = panopoly

projects[panopoly_images][version] = 1.37
projects[panopoly_images][subdir] = panopoly

projects[panopoly_theme][version] = 1.37
projects[panopoly_theme][subdir] = panopoly

projects[panopoly_magic][version] = 1.37
projects[panopoly_magic][subdir] = panopoly

projects[panopoly_widgets][version] = 1.37
projects[panopoly_widgets][subdir] = panopoly

projects[panopoly_admin][version] = 1.37
projects[panopoly_admin][subdir] = panopoly

projects[panopoly_users][version] = 1.37
projects[panopoly_users][subdir] = panopoly

; The Panopoly Toolset

projects[panopoly_pages][version] = 1.37
projects[panopoly_pages][subdir] = panopoly

projects[panopoly_wysiwyg][version] = 1.37
projects[panopoly_wysiwyg][subdir] = panopoly

projects[panopoly_search][version] = 1.37
projects[panopoly_search][subdir] = panopoly
; Fixes DB update dependency ordering
projects[panopoly_search][patch][2766677] = patches/panopoly-search-update-dependency-2766677-1.patch

projects[panopoly_test][version] = 1.37
projects[panopoly_test][subdir] = panopoly
; @TODO - Add patches for custom Webspark testing
projects[panopoly_test][patch][137] = patches/webspark-847_panopoly-test-137-update.patch
projects[panopoly_test][patch][1372] = patches/webspark-847_panopoly-test-updates-3.patch

; ASU Custom, Webspark-agnostic modules
; Webspark-only modules kept in webspark_featurescustom

projects[asu_drupal_modules][type] = module
projects[asu_drupal_modules][directory_name] = custom
projects[asu_drupal_modules][download][revision] = 2fcb4275
projects[asu_drupal_modules][download][url] = https://github.com/ASU/asu-drupal-modules.git

; ASU Module Prerequisites

projects[references][version] = 2.1
projects[references][type] = module
projects[references][subdir] = contrib

projects[ldap][version] = 2.0-beta8
projects[ldap][type] = module
projects[ldap][subdir] = contrib
;; patch - see https://drupal.org/node/2182413, comment #10 - remove upon ldap update beyond beta8
projects[ldap][patch][2182413] = http://cgit.drupalcode.org/ldap/patch/?id=fe3a3d56ffebc9bd551c6d83a03172fae13517c3

; @TODO v2.2
projects[better_watchdog_ui][version] = 2.0
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

projects[smtp][version] = 1.4
projects[smtp][subdir] = contrib
projects[smtp][type] = module

projects[viewfield][version] = 2.0
projects[viewfield][type] = module
projects[viewfield][subdir] = contrib

; @TODO v1.0-alpha3
projects[views_php][version] = 1.x-dev
projects[views_php][type] = module
projects[views_php][subdir] = contrib

projects[webform][version] = 4.12
projects[webform][type] = module
projects[webform][subdir] = contrib

; ASU Module prerequisites - Webspark Webstandards Components - contrib

projects[backgroundfield][version] = 1.5
projects[backgroundfield][type] = module
projects[backgroundfield][subdir] = contrib
projects[backgroundfield][sha256] = 25c86aedfeb90d8e4a63aaee4f762415757a9d6ac2749466f3134e9b60d98261
;; WEBSPARK-481 - BackgroundField image patch - default_image error
projects[backgroundfield][patch][1841978] = https://www.drupal.org/files/backgroundfield_undefined_index-1841978-18.patch

; @TODO v1.5
;; CAS SSO Integration - pulled in from old asu_cas.make file
projects[cas][version] = 1.4
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

; @TODO v2.0-rc1
projects[flexslider][version] = 2.0-alpha3
projects[flexslider][type] = module
projects[flexslider][subdir] = contrib

; @TODO v1.1 (or v2.5)
projects[fontawesome][version] = 1.0
projects[fontawesome][type] = module
projects[fontawesome][subdir] = contrib

; @TODO v1.14
projects[google_appliance][version] = 1.12
projects[google_appliance][type] = module
projects[google_appliance][subdir] = contrib

projects[maxlength][version] = 3.2-beta2
projects[maxlength][type] = module
projects[maxlength][subdir] = contrib

projects[panels_tabs][version] = 2.x-dev
projects[panels_tabs][type] = module
projects[panels_tabs][subdir] = contrib

;; Going to Git repo for dev commit of quicktabs
projects[quicktabs][type] = module
projects[quicktabs][subdir] = contrib
projects[quicktabs][download][type] = "git"
projects[quicktabs][download][branch] = "7.x-3.x"
projects[quicktabs][download][url] = "http://git.drupal.org/project/quicktabs.git"
projects[quicktabs][download][revision] = "758de4cc4995149a2de1d566b4209ec343581d27"

;; Webspark Megamenu
projects[special_menu_items][version] = 2.0
projects[special_menu_items][subdir] = contrib
projects[special_menu_items][type] = module

; @TODO v1.0-rc2
projects[tb_megamenu][version] = 1.0-beta5
projects[tb_megamenu][type] = module
projects[tb_megamenu][subdir] = contrib
; PATCH the CSS for tb_megamenu
;projects[tb_megamenu][patch][] = https://www.drupal.org/files/issues/webspark_megamenu-fixing_breakpoints.patch
projects[tb_megamenu][patch][] = patches/nojira-webspark-megamenu_fixing-breakpoints.patch

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

; @TODO v2.12
projects[wysiwyg_template][version] = 2.11
projects[wysiwyg_template][type] = module
projects[wysiwyg_template][subdir] = contrib

; Bootstrap and Theme Frameworks - Moved to Webspark repo (see WEBSPARK-366)

;; Base Theme - Kalatheme

; @TODO v3.2
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

projects[modernizr][version] = 3.1
projects[modernizr][subdir] = contrib

; ASU Module prerequisites - Webstandards additions - Libraries

libraries[ajax_solr][download][type] = get
libraries[ajax_solr][download][url] = https://github.com/evolvingweb/ajax-solr/archive/master.zip
libraries[ajax_solr][directory_name] = ajax_solr
libraries[ajax_solr][destination] = libraries
libraries[ajax_solr][download][sha256] = dbc2da964c94b939b80a2688bff6af90e66f8f08672cb66e5e1286019f8e8b40

; CAS - Get only source + root PHP from Github
; 1 of 2
libraries[CAS][download][type] = get
libraries[CAS][download][url] = https://github.com/Jasig/phpCAS/archive/1.3.4.zip
libraries[CAS][download][subtree] = phpCAS-1.3.4/source
libraries[CAS][directory_name] = CAS/source
libraries[CAS][download][sha256] = c8c73945c3503991d19e2a1f7f14b51c293dd2ed9ebae974450a85da03ca3eee
; 2 of 2
libraries[CAS_2][download][type] = file
libraries[CAS_2][download][url] = https://raw.githubusercontent.com/Jasig/phpCAS/1.3.4/CAS.php
libraries[CAS_2][directory_name] = CAS
libraries[CAS_2][download][sha256] = 74a3eeed33e84d927884a2cf01ab10c33cc445e891c6d773996ffb19cf841d23

libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.6.1/chosen_v1.6.1.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries
libraries[chosen][download][sha256] = e4b003203412771c9a554410561bb89a30975ba0e2d290f834ac5910ea7f8bc9

libraries[flexslider][download][type] = get
libraries[flexslider][download][url] = https://github.com/woothemes/FlexSlider/archive/version/2.2.2.zip
libraries[flexslider][download][sha256] = bd72421a8aa6f4b9cd3575f4eb58651f2b43c5dc00f0f8f80a373f71b5d1efcc

; 1 of 2
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

; Temporarily in non-ASU repo for v3.3.1 custom build
; @TODO - Move to official ASU repo
libraries[modernizr][download][type] = get
libraries[modernizr][download][url] = https://raw.githubusercontent.com/bjdevil21/asu-webspark-libraries/master/modernizr/modernizr-custom.js
libraries[modernizr][directory_name] = modernizr
libraries[modernizr][download][sha256] = 4f940bc0eac68623dc3874e8ccff90d4f827465f18d746234b635a2aa5890ff9

libraries[jqtree][download][type] = get
libraries[jqtree][download][url] = https://github.com/mbraak/jqTree/archive/0.22.0.zip
libraries[jqtree][directory_name] = jqtree
libraries[jqtree][destination] = libraries
libraries[jqtree][download][sha256] = 1a52b655f49e0c0778e0776d7d7f2afc2aa37a26ce9be110d7bc31b6e274d67d

; PANOPOLY PROJECT PATCHES
;; These projects are installed first, before any other projects in the parent makefile.

includes[panopoly_patches] = openasu_panopoly_patches.make
