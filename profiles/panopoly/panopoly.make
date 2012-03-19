api = 2
core = 7.0
projects[drupal][type] = core

; Contrib - Foundation
projects[ctools][subdir] = contrib
projects[ctools][version] = 1.x-dev
projects[ctools][type] = module
projects[ctools][patch][HAX] = http://apps.getpantheon.com/sites/all/patches/ctools-modal-sizing.patch
; projects[ctools][patch][1477950] = http://drupal.org/files/ctools-restrict-style-plugins-p0-reroll.patch

projects[panels][subdir] = contrib
projects[panels][type] = module
projects[panels][version] = 3.x-dev
projects[panels][patch][HAX] = http://apps.getpantheon.com/sites/all/patches/panels-lazy-css-loading.patch

projects[panels_breadcrumbs][subdir] = contrib
projects[panels_breadcrumbs][type] = module
projects[panels_breadcrumbs][version] = 1.6

projects[panelizer][subdir] = contrib
projects[panelizer][type] = module
projects[panelizer][version] = 2.0

projects[fieldable_panels_panes][subdir] = contrib
projects[fieldable_panels_panes][version] = 1.x-dev
projects[fieldable_panels_panes][type] = module
projects[fieldable_panels_panes][patch][1423994] = http://drupal.org/files/fieldable_panels_uuid_patch_v4.patch

projects[pm_existing_pages][version] = 1.x-dev
projects[pm_existing_pages][type] = module
projects[pm_existing_pages][subdir] = contrib

projects[views][version] = 3.3
projects[views][type] = module
projects[views][subdir] = contrib

projects[token][version] = 1.0-rc1
projects[token][type] = module
projects[token][subdir] = contrib

projects[ds][version] = 1.5
projects[ds][type] = module
projects[ds][subdir] = contrib

; Contrib - Field UI and Content Types
projects[tablefield][version] = 2.0-beta6
projects[tablefield][type] = module
projects[tablefield][subdir] = contrib

projects[link][version] = 1.0
projects[link][type] = module
projects[link][subdir] = contrib

projects[date][version] = 2.2
projects[date][type] = module
projects[date][subdir] = contrib

projects[views_slideshow][version] = 3.0
projects[views_slideshow][type] = module
projects[views_slideshow][subdir] = contrib

projects[simple_gmap][version] = 1.0-rc1
projects[simple_gmap][type] = module
projects[simple_gmap][subdir] = contrib

projects[email][version] = 1.0
projects[email][type] = module
projects[email][subdir] = contrib

projects[phone][version] = 1.x-dev
projects[phone][type] = module
projects[phone][subdir] = contrib

projects[field_group][version] = 1.1
projects[field_group][type] = module
projects[field_group][subdir] = contrib

projects[office_hours][version] = 1.x-dev
projects[office_hours][type] = module
projects[office_hours][subdir] = contrib

projects[entityreference][version] = 1.0-beta5
projects[entityreference][type] = module
projects[entityreference][subdir] = contrib

projects[calendar][version] = 3.0
projects[calendar][subdir] = contrib
projects[calendar][type] = module
projects[calendar][patch][HAX] = http://apps.getpantheon.com/sites/all/patches/calendar-hax.patch

projects[file_entity][version] = 2.x-dev
projects[file_entity][type] = module
projects[file_entity][subdir] = contrib

; Contrib - Search
projects[search_api][version] = 1.0
projects[search_api][type] = module
projects[search_api][subdir] = contrib

projects[search_api_solr][version] = 1.0-rc1
projects[search_api_solr][type] = module
projects[search_api_solr][subdir] = contrib
projects[search_api_solr][patch][1407282] = http://drupal.org/files/1407282-search-api-solr-alternate-connection-reroll.patch

projects[facetapi][version] = 1.0-rc4
projects[facetapi][type] = module
projects[facetapi][subdir] = contrib

; Contrib - Media
projects[media][version] = 2.x-dev
projects[media][type] = module
projects[media][subdir] = contrib

projects[media_youtube][version] = 1.0-beta3
projects[media_youtube][type] = module
projects[media_youtube][subdir] = contrib

projects[media_vimeo][version] = 1.0-beta4
projects[media_vimeo][type] = module
projects[media_vimeo][subdir] = contrib

; Contrib - Menus and URLS
projects[pathauto][subdir] = contrib
projects[pathauto][type] = module
projects[pathauto][version] = 1.0

projects[menu_block][version] = 2.3
projects[menu_block][subdir] = contrib
projects[menu_block][type] = module

projects[taxonomy_menu][version] = 1.2
projects[taxonomy_menu][subdir] = contrib
projects[taxonomy_menu][type] = module
projects[taxonomy_menu][patch][1486510] = http://drupal.org/files/taxonomy-menu-no-vid-checking.patch

; Contrib - User Experience
projects[wysiwyg][subdir] = contrib
projects[wysiwyg][type] = module
projects[wysiwyg][version] = 2.x-dev 
projects[wysiwyg][patch][HAX] = http://apps.getpantheon.com/sites/all/patches/wysiwyg-table-format.patch
projects[wysiwyg][patch][356480] = http://apps.getpantheon.com/sites/all/patches/0001-356480-by-zhangtaihao-Shawn_Smiley-sun.-Lazy-load-ed.patch

projects[wysiwyg_filter][version] = 1.6-rc2
projects[wysiwyg_filter][subdir] = contrib
projects[wysiwyg_filter][type] = module

projects[better_formats][version] = 1.x-dev
projects[better_formats][subdir] = contrib
projects[better_formats][type] = module

projects[caption_filter][version] = 1.2
projects[caption_filter][type] = module
projects[caption_filter][subdir] = contrib

projects[image_resize_filter][version] = 1.13
projects[image_resize_filter][type] = module
projects[image_resize_filter][subdir] = contrib

projects[date_popup_authored][version] = 1.1-beta2
projects[date_popup_authored][subdir] = contrib
projects[date_popup_authored][type] = module

projects[admin][version] = 2.0-beta3
projects[admin][type] = module
projects[admin][subdir] = contrib

projects[module_filter][version] = 1.6
projects[module_filter][type] = module
projects[module_filter][subdir] = contrib

projects[views_bulk_operations][version] = 3.0-rc1
projects[views_bulk_operations][type] = module
projects[views_bulk_operations][subdir] = contrib

projects[simplified_menu_admin][version] = 1.0-beta2
projects[simplified_menu_admin][type] = module
projects[simplified_menu_admin][subdir] = contrib

projects[references_dialog][version] = 1.0-alpha3
projects[references_dialog][type] = module
projects[references_dialog][subdir] = contrib

projects[backports][version] = 1.0-alpha1
projects[backports][type] = module
projects[backports][subdir] = contrib

; Contrib - Products
projects[apps][subdir] = contrib
projects[apps][type] = module
projects[apps][version] = 1.x-dev
projects[apps][patch][1479164] = http://drupal.org/files/1479164-apps-permissions-check-modules-not-conf-reroll.patch
projects[apps][patch][1479536] = http://drupal.org/files/apps-multiple-install-servers-1479536-4.patch
projects[apps][patch][1480912] = http://drupal.org/files/apps-clean-up-the-cleanup.patch
projects[apps][patch][1482684] = http://drupal.org/files/apps-single-item-style.patch
projects[apps][patch][1484300] = http://drupal.org/files/apps-check-empty-multiple-servers.patch

projects[features][version] = 1.x-dev
projects[features][subdir] = contrib
projects[features][type] = module

projects[entity][version] = 1.0-rc1
projects[entity][type] = module
projects[entity][subdir] = contrib

projects[uuid][version] = 1.x-dev
projects[uuid][type] = module
projects[uuid][subdir] = contrib

projects[uuid_features][version] = 1.x-dev
projects[uuid_features][type] = module
projects[uuid_features][subdir] = contrib

projects[defaultcontent][version] = 1.0-alpha5
projects[defaultcontent][type] = module
projects[defaultcontent][subdir] = contrib
projects[defaultcontent][patch][1263536] = http://apps.getpantheon.com/sites/all/patches/base64_encode_files-1263536-1.patch

projects[strongarm][version] = 2.0-beta5
projects[strongarm][type] = module
projects[strongarm][subdir] = contrib

projects[libraries][version] = 1.0
projects[libraries][type] = module
projects[libraries][subdir] = contrib

; Contrib - Performance
projects[redis][version] = 2.0-alpha6
projects[redis][type] = module
projects[redis][subdir] = contrib

; Contrib - Development
projects[devel][subdir] = contrib
projects[devel][type] = module
projects[devel][version] = 1.2

; Contrib - Theme
projects[conditional_styles][subdir] = contrib
projects[conditional_styles][type] = module
projects[conditional_styles][version] = 2.1

projects[respondjs][subdir] = contrib
projects[respondjs][type] = module
projects[respondjs][version] = 1.0
projects[respondjs][patch][1477172] = http://drupal.org/files/respondjs_requirements_not_nag.patch

projects[fontyourface][subdir] = contrib
projects[fontyourface][type] = module
projects[fontyourface][version] = 2.2

; Libraries
libraries[tinymce][download][type] = get
libraries[tinymce][download][url] = http://apps.getpantheon.com/sites/all/libraries/tinymce-panopoly.tar.gz

libraries[solrphpclient][download][type] = get
libraries[solrphpclient][download][url] = http://solr-php-client.googlecode.com/files/SolrPhpClient.r60.2011-05-04.zip

libraries[markitup][download][type] = get
libraries[markitup][download][url] = http://apps.getpantheon.com/sites/all/libraries/markitup-panopoly.tar.gz

libraries[jquery.cycle][download][type] = get
libraries[jquery.cycle][download][url] = http://apps.getpantheon.com/sites/all/libraries/jquery-cycle.tar.gz

libraries[respondjs][download][type] = get
libraries[respondjs][download][url] = http://apps.getpantheon.com/sites/all/libraries/panopoly-respondjs.tar.gz
