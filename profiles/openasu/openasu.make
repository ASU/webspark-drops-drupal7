api = 2
core = 7.x

; Drupal Core

projects[drupal][type] = core
projects[drupal][version] = 7.32

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

; ASU Modules

projects[asu_brand][version] = 1.7
projects[asu_brand][subdir] = custom
projects[asu_brand][type] = module
projects[asu_brand][download][revision] = 4e2268c9
projects[asu_brand][download][branch] = header42
projects[asu_brand][download][url] = https://github.com/ASU/asu-drupal-brand.git

projects[asu_cas][version] = 7.x-1.5
projects[asu_cas][subdir] = custom
projects[asu_cas][type] = module
projects[asu_cas][download][revision] = f2c41254
projects[asu_cas][download][branch] = 7.x-1.x
projects[asu_cas][download][url] = https://github.com/ASU/asu-drupal-cas-client-config.git

projects[asu_userpicker][version] = 1.0
projects[asu_userpicker][subdir] = custom
projects[asu_userpicker][type] = module
projects[asu_userpicker][download][revision] = 95a01aadb043e9c2e6241a301e253d7c56e26b71
projects[asu_userpicker][download][tag] = 7.x-1.0
projects[asu_userpicker][download][url] = https://github.com/ASU/asu-drupal-userpicker.git

projects[asu_feeds][version] = 1.0-beta2
projects[asu_feeds][subdir] = custom
projects[asu_feeds][type] = module
projects[asu_feeds][download][revision] = 400daaf0
projects[asu_feeds][download][url] = https://github.com/ASU/asu-drupal-feeds.git

projects[ixr][version] = 1.0-beta2
projects[ixr][subdir] = custom
projects[ixr][type] = module
projects[ixr][download][revision] = 990012dd
projects[ixr][download][url] = https://github.com/ASU/asu-drupal-ixr.git

projects[asu_events][version] = 1.0-dev
projects[asu_events][subdir] = custom
projects[asu_events][type] = module
projects[asu_events][download][revision] = a2211824
projects[asu_events][download][url] = https://github.com/ASU/asu-drupal-events-feed.git

projects[asu_news][version] = 1.0-dev
projects[asu_news][subdir] = custom
projects[asu_news][type] = module
projects[asu_news][download][revision] = fc29af6a
projects[asu_news][download][url] = https://github.com/ASU/asu-drupal-news.git

; eAdvisor Feed Feature (depracated in lieu of ASU Degrees)
projects[asu_eadvisor_degree_feed_feature][version] = 1.0-beta1
projects[asu_eadvisor_degree_feed_feature][subdir] = custom
projects[asu_eadvisor_degree_feed_feature][type] = module
projects[asu_eadvisor_degree_feed_feature][download][revision] = 91278fd1
projects[asu_eadvisor_degree_feed_feature][download][url] = https://github.com/ASU/asu-drupal-eadvisor-degree-feed.git

; ASU Degrees (replacement for asu_eadvisor_degree_feed_feature)
; TODO - Update ASU Degrees module(s) to new repo or combine with other repos
projects[asu_degrees][version] = 1.0
projects[asu_degrees][type] = module
projects[asu_degrees][subdir] = custom
projects[asu_degrees][download][revision] = 814df0e9
projects[asu_degrees][download][branch] = asu_degrees
projects[asu_degrees][download][url] = https://github.com/ASU/asu-drupal-eadvisor-degree-feed.git

; Includes multiple Webspark features and modules
projects[webspark_featurescustom][type] = module
projects[webspark_featurescustom][subdir] = custom
projects[webspark_featurescustom][directory_name] = webspark_featurescustom
projects[webspark_featurescustom][download][type] = git
projects[webspark_featurescustom][download][revision] = dd0741fd
projects[webspark_featurescustom][download][branch] = master
projects[webspark_featurescustom][download][url] = https://github.com/ASU/webspark-webstandards-components.git

projects[asu_rfi][type] = module
projects[asu_rfi][subdir] = custom
projects[asu_rfi][download][type] = git
projects[asu_rfi][download][revision] = dd1c109e
projects[asu_rfi][download][branch] = master
projects[asu_rfi][download][url] = https://github.com/ASU/asu-drupal-rfi

; ASU Module Prerequisites

projects[references][version] = 2.1
projects[references][type] = module
projects[references][subdir] = contrib

projects[ldap][version] = 2.0-beta8
projects[ldap][type] = module
projects[ldap][subdir] = contrib
; patch - see https://drupal.org/node/2182413, comment #10 - remove upon ldap update beyond beta8
projects[ldap][patch][2182413] = http://cgit.drupalcode.org/ldap/patch/?id=fe3a3d56ffebc9bd551c6d83a03172fae13517c3

projects[cas_attributes][version] = 1.0-rc3
projects[cas_attributes][type] = module
projects[cas_attributes][subdir] = contrib

projects[calendar][version] = 3.4
projects[calendar][type] = module
projects[calendar][subdir] = contrib

projects[feeds][version] = 2.0-alpha8
projects[feeds][type] = module
projects[feeds][subdir] = contrib

projects[feeds_xpathparser][version] = 1.0-beta4
projects[feeds_xpathparser][type] = module
projects[feeds_xpathparser][subdir] = contrib
; patch for errors/warnings (only in dev version of module)
projects[feeds_xpathparser][patch][1998194] = https://www.drupal.org/files/feeds_xpath_parser_undefined_index_unique-1998194-2.patch

projects[job_scheduler][version] = 2.0-alpha3
projects[job_scheduler][type] = module
projects[job_scheduler][subdir] = contrib

projects[multiblock][version] = 1.1
projects[multiblock][type] = module
projects[multiblock][subdir] = contrib

projects[viewfield][version] = 2.0
projects[viewfield][type] = module
projects[viewfield][subdir] = contrib

projects[views_bootstrap][version] = 3.1
projects[views_bootstrap][type] = module
projects[views_bootstrap][subdir] = contrib

projects[views_php][version] = 1.x-dev
projects[views_php][type] = module
projects[views_php][subdir] = contrib

projects[webform][version] = 3.21
projects[webform][type] = module
projects[webform][subdir] = contrib

; ASU Module prerequisites - Webspark Webstandards Components - contrib

projects[backgroundfield][version] = 1.5
projects[backgroundfield][type] = module
projects[backgroundfield][subdir] = contrib

projects[chosen][version] = 2.0-beta4
projects[chosen][type] = module
projects[chosen][subdir] = contrib

projects[easy_breadcrumb][version] = 2.12
projects[easy_breadcrumb][type] = module
projects[easy_breadcrumb][subdir] = contrib

projects[entity_view_mode][version] = 1.0-rc1
projects[entity_view_mode][type] = module
projects[entity_view_mode][subdir] = contrib

projects[features_override][version] = 2.0-rc2
projects[features_override][type] = module
projects[features_override][subdir] = contrib

projects[flexslider][version] = 2.0-alpha3
projects[flexslider][type] = module
projects[flexslider][subdir] = contrib

projects[fontawesome][version] = 1.0
projects[fontawesome][type] = module
projects[fontawesome][subdir] = contrib

projects[google_appliance][version] = 1.12
projects[google_appliance][type] = module
projects[google_appliance][subdir] = contrib

projects[maxlength][version] = 3.0-beta1
projects[maxlength][type] = module
projects[maxlength][subdir] = contrib

projects[panels_tabs][version] = 2.x-dev
projects[panels_tabs][type] = module
projects[panels_tabs][subdir] = contrib

projects[tb_megamenu][version] = 1.0-beta5
projects[tb_megamenu][type] = module
projects[tb_megamenu][subdir] = contrib
; TODO - PATCH the CSS for tb_megamenu
projects[tb_megamenu][patch][] = https://www.drupal.org/files/issues/webspark_megamenu-fixing_breakpoints.patch

;projects[uuid_features][version] = 1.0-alpha4
; grabbing alpha-4+dev-37 commit
projects[uuid_features][type] = module
projects[uuid_features][subdir] = contrib
projects[uuid_features][download][type] = "git"
projects[uuid_features][download][branch] = "7.x-1.x"
projects[uuid_features][download][url] = "http://git.drupal.org/project/uuid_features.git"
projects[uuid_features][download][revision] = "55a2d5070b6f238f40372070f70314cc4f8197d8"

projects[video_embed_field][version] = 2.0-beta8
projects[video_embed_field][type] = module
projects[video_embed_field][subdir] = contrib

projects[wysiwyg_template][version] = 2.11
projects[wysiwyg_template][type] = module
projects[wysiwyg_template][subdir] = contrib

; Bootstrap and Theme Framework

; Base Theme - Kalatheme

projects[kalatheme][version] = 3.0-rc2
projects[kalatheme][type] = theme
; WEBSPARK-188 - CSS img url fix
projects[kalatheme][patch][] = patches/webspark-188.kalatheme-css-img-urls.patch
; WEBSPARK-361 - Panopoly TPLs and row-full class
projects[kalatheme][patch][] = patches/webspark-361-kalatheme-panopoly-tpl-class-update.patch

projects[modernizr][version] = 3.1
projects[modernizr][subdir] = contrib

; Bootstrap and Theme Framework - Subtheme - Webspark

projects[asu_webspark_bootstrap][version] = 1.1
projects[asu_webspark_bootstrap][type] = theme
projects[asu_webspark_bootstrap][download][type] = git
projects[asu_webspark_bootstrap][download][revision] = 0e10c11d
projects[asu_webspark_bootstrap][download][branch] = 7.x-1.x
projects[asu_webspark_bootstrap][download][url] = https://github.com/ASU/webspark-theme-original.git

libraries[asu_webspark_bootstrap_bootstrap][download][type] = get
libraries[asu_webspark_bootstrap_bootstrap][download][url] = https://github.com/ASU/webspark-theme-original-library/archive/v3.1.1.zip

; Bootstrap and Theme Framework - Subtheme - Web Standards

projects[innovation][version] = beta6
projects[innovation][type] = theme
projects[innovation][download][type] = git
projects[innovation][download][revision] = 102d0b45
projects[innovation][download][branch] = master
projects[innovation][download][url] = https://github.com/ASU/webspark-theme-innovation.git

libraries[innovation_bootstrap][download][type] = get
libraries[innovation_bootstrap][download][url] = https://github.com/ASU/webspark-theme-innovation-bootstrap/archive/master.zip

; ASU Module prerequisites - Webstandards additions - Libraries

libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries

libraries[flexslider][download][type] = get
libraries[flexslider][download][url] = https://github.com/woothemes/FlexSlider/archive/version/2.2.2.zip

libraries[fontawesome][download][type] = get
libraries[fontawesome][download][url] = http://fontawesome.io/assets/font-awesome-4.2.0.zip

libraries[modernizr][download][type] = get
libraries[modernizr][download][url] = https://github.com/Modernizr/Modernizr/archive/v2.6.2.zip
