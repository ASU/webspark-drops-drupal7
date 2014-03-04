api = 2
core = 7.x

; Drupal Core

projects[drupal][type] = core
projects[drupal][version] = 7.23

; ASU Overrides

projects[simple_gmap][version] = 1.0
projects[simple_gmap][subdir] = contrib
projects[simple_gmap][patch][2070277] = https://drupal.org/files/21085150-simple-gmap-support-https-1.patch

; The Panopoly Foundation

projects[panopoly_core][version] = 1.0-rc5
projects[panopoly_core][subdir] = panopoly

projects[panopoly_images][version] = 1.0-rc5
projects[panopoly_images][subdir] = panopoly

projects[panopoly_theme][version] = 1.0-rc5
projects[panopoly_theme][subdir] = panopoly

projects[panopoly_magic][version] = 1.0-rc5
projects[panopoly_magic][subdir] = panopoly

projects[panopoly_widgets][version] = 1.0-rc5
projects[panopoly_widgets][subdir] = panopoly

projects[panopoly_admin][version] = 1.0-rc5
projects[panopoly_admin][subdir] = panopoly

projects[panopoly_users][version] = 1.0-rc5
projects[panopoly_users][subdir] = panopoly

; The Panopoly Toolset

projects[panopoly_pages][version] = 1.0-rc5
projects[panopoly_pages][subdir] = panopoly

projects[panopoly_wysiwyg][version] = 1.0-rc5
projects[panopoly_wysiwyg][subdir] = panopoly

projects[panopoly_search][version] = 1.0-rc5
projects[panopoly_search][subdir] = panopoly
projects[panopoly_search][patch][2063715] = https://drupal.org/files/2063715-panopoly-search-update-conditional-2.patch
projects[panopoly_search][patch][2111097] = https://drupal.org/files/2111097-panopoly_search-pantheon_apachesolr.patch

; Demo Content
projects[panopoly_demo][version] = 1.0-rc3
projects[panopoly_demo][subdir] = panopoly

; ASU Modules

projects[asu_brand][version] = 1.4
projects[asu_brand][subdir] = custom
projects[asu_brand][location] = https://webconsulting.asu.edu/fserver

projects[asu_cas][version] = 1.x-dev
projects[asu_cas][subdir] = custom
projects[asu_cas][type] = module
projects[asu_cas][download][type] = git
projects[asu_cas][download][revision] = 6a86794
projects[asu_cas][download][branch] = 7.x-1.x
projects[asu_cas][download][url] = https://github.com/kalamuna/asu_cas.git

projects[asu_userpicker][version] = 1.0
projects[asu_userpicker][subdir] = custom
projects[asu_userpicker][type] = module
projects[asu_userpicker][download][type] = git
projects[asu_userpicker][download][revision] = 95a01aadb043e9c2e6241a301e253d7c56e26b71
projects[asu_userpicker][download][tag] = 7.x-1.0
projects[asu_userpicker][download][url] = https://github.com/mlsamuelson/asu_userpicker.git

projects[asu_feeds][version] = 1.0-beta3
projects[asu_feeds][subdir] = custom
projects[asu_feeds][location] = http://webconsulting.asu.edu/fserver

projects[ixr][version] = 1.0-beta1
projects[ixr][subdir] = custom
projects[ixr][location] = http://webconsulting.asu.edu/fserver

projects[asu_events][version] = 1.0-dev
projects[asu_events][subdir] = custom
projects[asu_events][location] = https://webconsulting.asu.edu/fserver

projects[asu_news][version] = 1.0-dev
projects[asu_news][subdir] = custom
projects[asu_news][location] = https://webconsulting.asu.edu/fserver

projects[asu_eadvisor_degree_feed_feature][version] = 1.0-beta1
projects[asu_eadvisor_degree_feed_feature][subdir] = custom
projects[asu_eadvisor_degree_feed_feature][location] = https://webconsulting.asu.edu/fserver

; ASU Module Prerequisites

projects[references][version] = 2.1
projects[references][type] = module
projects[references][subdir] = contrib

projects[ldap][version] = 2.0-beta8
projects[ldap][type] = module
projects[ldap][subdir] = contrib

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

projects[field_group][version] = 1.1
projects[field_group][type] = module
projects[field_group][subdir] = contrib

projects[job_scheduler][version] = 2.0-alpha3
projects[job_scheduler][type] = module
projects[job_scheduler][subdir] = contrib

projects[viewfield][version] = 2.0
projects[viewfield][type] = module
projects[viewfield][subdir] = contrib

projects[views_php][version] = 1.x-dev
projects[views_php][type] = module
projects[views_php][subdir] = contrib

; Bootstrap and Theme Framework

projects[kalatheme][version] = 1.3
projects[kalatheme][type] = theme

projects[modernizr][version] = 3.1
projects[modernizr][subdir] = contrib

projects[openasu_bootstrap][version] = 1.x-dev
projects[openasu_bootstrap][type] = theme
projects[openasu_bootstrap][download][type] = git
projects[openasu_bootstrap][download][revision] = 1c5644e
projects[openasu_bootstrap][download][branch] = 7.x-1.x
projects[openasu_bootstrap][download][url] = https://github.com/kalamuna/openasu_bootstrap.git

libraries[bootstrap][download][type] = get
libraries[bootstrap][download][url] = https://github.com/kalamuna/asu_bootlibrary/archive/v2.3.1.zip

libraries[modernizr][download][type] = get
libraries[modernizr][download][url] = https://github.com/Modernizr/Modernizr/archive/v2.6.2.zip
