api = 2
core = 7.x

; Drupal Core
projects[drupal][type] = core
projects[drupal][version] = 7.18

; The Panopoly Foundation

projects[panopoly_core][version] = 1.x-dev
projects[panopoly_core][subdir] = panopoly
projects[panopoly_core][download][type] = git
projects[panopoly_core][download][revision] = acbb2bb
projects[panopoly_core][download][branch] = 7.x-1.x

projects[panopoly_images][version] = 1.x-dev
projects[panopoly_images][subdir] = panopoly
projects[panopoly_images][download][type] = git
projects[panopoly_images][download][revision] = ba8c36e
projects[panopoly_images][download][branch] = 7.x-1.x

projects[panopoly_theme][version] = 1.x-dev
projects[panopoly_theme][subdir] = panopoly
projects[panopoly_theme][download][type] = git
projects[panopoly_theme][download][revision] = 4f45887
projects[panopoly_theme][download][branch] = 7.x-1.x

projects[panopoly_magic][version] = 1.x-dev
projects[panopoly_magic][subdir] = panopoly
projects[panopoly_magic][download][type] = git
projects[panopoly_magic][download][revision] = 9590324
projects[panopoly_magic][download][branch] = 7.x-1.x

projects[panopoly_widgets][version] = 1.x-dev
projects[panopoly_widgets][subdir] = panopoly
projects[panopoly_widgets][download][type] = git
projects[panopoly_widgets][download][revision] = 06359b8
projects[panopoly_widgets][download][branch] = 7.x-1.x

projects[panopoly_admin][version] = 1.x-dev
projects[panopoly_admin][subdir] = panopoly
projects[panopoly_admin][download][type] = git
projects[panopoly_admin][download][revision] = fedc685
projects[panopoly_admin][download][branch] = 7.x-1.x

projects[panopoly_users][version] = 1.x-dev
projects[panopoly_users][subdir] = panopoly
projects[panopoly_users][download][type] = git
projects[panopoly_users][download][revision] = 25642d7
projects[panopoly_users][download][branch] = 7.x-1.x

; The Panopoly Toolset

projects[panopoly_pages][version] = 1.x-dev
projects[panopoly_pages][subdir] = panopoly
projects[panopoly_pages][download][type] = git
projects[panopoly_pages][download][revision] = bae7bde
projects[panopoly_pages][download][branch] = 7.x-1.x

projects[panopoly_wysiwyg][version] = 1.x-dev
projects[panopoly_wysiwyg][subdir] = panopoly
projects[panopoly_wysiwyg][download][type] = git
projects[panopoly_wysiwyg][download][revision] = d681ade
projects[panopoly_wysiwyg][download][branch] = 7.x-1.x

projects[panopoly_search][version] = 1.x-dev
projects[panopoly_search][subdir] = panopoly
projects[panopoly_search][download][type] = git
projects[panopoly_search][download][revision] = 34bee3f
projects[panopoly_search][download][branch] = 7.x-1.x

projects[panopoly_demo][version] = 1.x-dev
projects[panopoly_demo][subdir] = panopoly
projects[panopoly_demo][download][type] = git
projects[panopoly_demo][download][revision] = a0ed0cf
projects[panopoly_demo][download][branch] = 7.x-1.x

; ASU Modules

projects[asu_brand][version] = 1.4
projects[asu_brand][subdir] = custom
projects[asu_brand][location] = https://webconsulting.asu.edu/fserver

projects[asu_cas][version] = 1.x-dev
projects[asu_cas][subdir] = custom
projects[asu_cas][download][type] = git
projects[asu_cas][download][revision] = 70a7c50
projects[asu_cas][download][branch] = 7.x-1.x
projects[asu_cas][download][url] = https://github.com/kalamuna/asu_cas.git

; Bootstrap Framework

projects[kalatheme][version] = 1.0-rc4
projects[kalatheme][type] = theme

projects[openasu_bootstrap][version] = 1.x-dev
projects[openasu_bootstrap][type] = theme
projects[openasu_bootstrap][download][type] = git
projects[openasu_bootstrap][download][revision] = 6aae928
projects[openasu_bootstrap][download][branch] = 7.x-1.x
projects[openasu_bootstrap][download][url] = https://github.com/kalamuna/openasu_bootstrap.git

libraries[bootstrap][download][type] = get
libraries[bootstrap][download][url] = https://github.com/kalamuna/asu_bootlibrary/archive/v2.3.0.zip

; Need 2.1 for Kalatheme RC4 - take this out when we move to Panopoly RC4

projects[libraries][version] = 2.1
projects[libraries][subdir] = contrib
