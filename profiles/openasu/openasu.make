api = 2
core = 7.x

; Drupal Core
projects[drupal][type] = core
projects[drupal][version] = 7.23

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
projects[asu_cas][download][revision] = 70a7c50
projects[asu_cas][download][branch] = 7.x-1.x
projects[asu_cas][download][url] = https://github.com/kalamuna/asu_cas.git

; Bootstrap and Theme Framework

projects[kalatheme][version] = 1.0-rc4
projects[kalatheme][type] = theme

projects[modernizr][version] = 3.1
projects[modernizr][subdir] = contrib

projects[openasu_bootstrap][version] = 1.x-dev
projects[openasu_bootstrap][type] = theme
projects[openasu_bootstrap][download][type] = git
projects[openasu_bootstrap][download][revision] = 8c3227d
projects[openasu_bootstrap][download][branch] = 7.x-1.x
projects[openasu_bootstrap][download][url] = https://github.com/kalamuna/openasu_bootstrap.git

libraries[bootstrap][download][type] = get
libraries[bootstrap][download][url] = https://github.com/kalamuna/asu_bootlibrary/archive/v2.3.0.zip

libraries[modernizr][download][type] = get
libraries[modernizr][download][url] = https://github.com/Modernizr/Modernizr/archive/v2.6.2.zip
