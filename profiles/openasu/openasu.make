api = 2
core = 7.x

; Drupal Core

projects[drupal][type] = core
projects[drupal][version] = 7.39

; Drupal Core Patches
projects[drupal][patch][1334818] = https://drupal.org/files/issues/D7-install-profile-ajax-1334818-8.patch

; The Panopoly Foundation

projects[panopoly_core][version] = 1.13
projects[panopoly_core][subdir] = panopoly

projects[panopoly_images][version] = 1.13
projects[panopoly_images][subdir] = panopoly

projects[panopoly_theme][version] = 1.13
projects[panopoly_theme][subdir] = panopoly

projects[panopoly_magic][version] = 1.13
projects[panopoly_magic][subdir] = panopoly

projects[panopoly_widgets][version] = 1.13
projects[panopoly_widgets][subdir] = panopoly

projects[panopoly_admin][version] = 1.13
projects[panopoly_admin][subdir] = panopoly

projects[panopoly_users][version] = 1.13
projects[panopoly_users][subdir] = panopoly

; The Panopoly Toolset

projects[panopoly_pages][version] = 1.13
projects[panopoly_pages][subdir] = panopoly

projects[panopoly_wysiwyg][version] = 1.13
projects[panopoly_wysiwyg][subdir] = panopoly

projects[panopoly_search][version] = 1.13
projects[panopoly_search][subdir] = panopoly

; Demo Content

projects[panopoly_demo][version] = 1.13
projects[panopoly_demo][subdir] = panopoly

; ASU Custom, Webspark-agnostic modules
; Webspark-only modules kept in webspark_featurescustom

projects[asu_drupal_modules][type] = module
projects[asu_drupal_modules][directory_name] = custom
projects[asu_drupal_modules][download][revision] = 09660a8d
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

projects[better_watchdog_ui][version] = 2.0
projects[better_watchdog_ui][type] = module
projects[better_watchdog_ui][subdir] = contrib

projects[cas_attributes][version] = 1.0-rc3
projects[cas_attributes][type] = module
projects[cas_attributes][subdir] = contrib

;; For Webspark News & Events
;; Will be removed when news & events is deleted
projects[calendar][version] = 3.4
projects[calendar][type] = module
projects[calendar][subdir] = contrib

projects[email][version] = 1.3
projects[email][subdir] = contrib
projects[email][type] = module
;; end will be removed

projects[feeds][version] = 2.0-alpha9
projects[feeds][type] = module
projects[feeds][subdir] = contrib

projects[feeds_xpathparser][version] = 1.1
projects[feeds_xpathparser][type] = module
projects[feeds_xpathparser][subdir] = contrib

projects[job_scheduler][version] = 2.0-alpha3
projects[job_scheduler][type] = module
projects[job_scheduler][subdir] = contrib

projects[viewfield][version] = 2.0
projects[viewfield][type] = module
projects[viewfield][subdir] = contrib

projects[views_php][version] = 1.x-dev
projects[views_php][type] = module
projects[views_php][subdir] = contrib

projects[webform][version] = 3.24
projects[webform][type] = module
projects[webform][subdir] = contrib

; ASU Module prerequisites - Webspark Webstandards Components - contrib

projects[backgroundfield][version] = 1.5
projects[backgroundfield][type] = module
projects[backgroundfield][subdir] = contrib
;; WEBSPARK-481 - BackgroundField image patch - default_image error
projects[backgroundfield][patch][1841978] = https://www.drupal.org/files/backgroundfield_undefined_index-1841978-18.patch

;; CAS SSO Integration - pulled in from old asu_cas.make file
projects[cas][version] = 1.4
projects[cas][subdir] = contrib

projects[chosen][version] = 2.0-beta4
projects[chosen][type] = module
projects[chosen][subdir] = contrib

projects[easy_breadcrumb][version] = 2.12
projects[easy_breadcrumb][type] = module
projects[easy_breadcrumb][subdir] = contrib

projects[entity_view_mode][version] = 1.0-rc1
projects[entity_view_mode][type] = module
projects[entity_view_mode][subdir] = contrib

projects[flexslider][version] = 2.0-alpha3
projects[flexslider][type] = module
projects[flexslider][subdir] = contrib

projects[fontawesome][version] = 1.0
projects[fontawesome][type] = module
projects[fontawesome][subdir] = contrib

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

projects[tb_megamenu][version] = 1.0-beta5
projects[tb_megamenu][type] = module
projects[tb_megamenu][subdir] = contrib
;; TODO - PATCH the CSS for tb_megamenu
projects[tb_megamenu][patch][] = https://www.drupal.org/files/issues/webspark_megamenu-fixing_breakpoints.patch

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

projects[wysiwyg_template][version] = 2.11
projects[wysiwyg_template][type] = module
projects[wysiwyg_template][subdir] = contrib

; Bootstrap and Theme Frameworks - Moved to Webspark repo (see WEBSPARK-366)

;; Base Theme - Kalatheme

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

projects[modernizr][version] = 3.1
projects[modernizr][subdir] = contrib

; ASU Module prerequisites - Webstandards additions - Libraries

libraries[ajax_solr][download][type] = get
libraries[ajax_solr][download][url] = https://github.com/evolvingweb/ajax-solr/archive/master.zip
libraries[ajax_solr][directory_name] = ajax_solr
libraries[ajax_solr][destination] = libraries

libraries[CAS][download][type] = get
libraries[CAS][download][url] = https://github.com/Jasig/phpCAS/archive/1.3.3.zip

libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries

libraries[flexslider][download][type] = get
libraries[flexslider][download][url] = https://github.com/woothemes/FlexSlider/archive/version/2.2.2.zip

libraries[fontawesome][download][type] = get
libraries[fontawesome][download][url] = https://github.com/FortAwesome/Font-Awesome/archive/v4.2.0.zip

libraries[modernizr][download][type] = get
libraries[modernizr][download][url] = https://github.com/Modernizr/Modernizr/archive/v2.6.2.zip

libraries[jqtree][download][type] = get
libraries[jqtree][download][url] = https://github.com/mbraak/jqTree/archive/0.22.0.zip
libraries[jqtree][directory_name] = jqtree
libraries[jqtree][destination] = libraries

; DEPRECATED PROJECTS - DO NOT USE AND LOOK FOR ALTERNATE SOLUTIONS ASAP

;; Will be replaced by alternate system that will work with the Hub's new asunews site
projects[asu_events][version] = 1.0-dev
projects[asu_events][subdir] = custom
projects[asu_events][type] = module
projects[asu_events][download][revision] = 9f04696f38b0999df42947ac6db0075d969ca553
projects[asu_events][download][url] = https://github.com/ASU/asu-drupal-events-feed.git

;; Will be replaced by alternate system that will work with the Hub's new asunews site
projects[asu_news][version] = 1.0-dev
projects[asu_news][subdir] = custom
projects[asu_news][type] = module
projects[asu_news][download][revision] = e52986872a63d0fe1123d819aba554d76f2c6e33
projects[asu_news][download][url] = https://github.com/ASU/asu-drupal-news.git

;; (DEPRECATED in lieu of ASU Degrees - asu_degrees module)
projects[asu_eadvisor_degree_feed_feature][version] = 1.0-beta1
projects[asu_eadvisor_degree_feed_feature][subdir] = custom
projects[asu_eadvisor_degree_feed_feature][type] = module
projects[asu_eadvisor_degree_feed_feature][download][revision] = 312c885e04f5cf64920b24fa1bc648c8f5a02989
projects[asu_eadvisor_degree_feed_feature][download][url] = https://github.com/ASU/asu-drupal-eadvisor-degree-feed.git

; PANOPOLY PROJECT PATCHES
;; These projects are installed first, before any other projects in the parent makefile.

includes[panopoly_patches] = openasu_panopoly_patches.make