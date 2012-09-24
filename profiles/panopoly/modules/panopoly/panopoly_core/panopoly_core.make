; Panopoly Core Makefile

api = 2
core = 7.x

; Panels and Chaos Tools Magic

projects[ctools][version] = 1.2
projects[ctools][subdir] = contrib
projects[ctools][patch][1294478] = http://drupal.org/files/dynamic-modal-1294478-34.patch
projects[ctools][patch][1774434] = http://drupal.org/files/1774434-ctools-allow-string-context-ui.patch
projects[ctools][patch][1754770] = http://drupal.org/files/blocks_dependency_issue-1754770-1.patch

projects[panels][version] = 3.3
projects[panels][subdir] = contrib
projects[panels][patch][1735336] = http://drupal.org/files/1735336-repaint-draghandle-ipe-initial.patch
projects[panels][patch][1788170] = http://drupal.org/files/panels-edit-context-overwrite.patch
projects[panels][patch][1772834] = http://drupal.org/files/1772834-fix-lost-context-6.patch
projects[panels][patch][1572202] = http://drupal.org/files/1572202-panels-ipe-panel-emptied-on-second-save.patch

projects[panels_breadcrumbs][version] = 2.x-dev
projects[panels_breadcrumbs][subdir] = contrib
projects[panels_breadcrumbs][download][type] = git
projects[panels_breadcrumbs][download][revision] = 531f589
projects[panels_breadcrumbs][download][branch] = 7.x-2.x

projects[panelizer][version] = 3.0-rc1
projects[panelizer][subdir] = contrib
projects[panelizer][patch][1572202] = http://drupal.org/files/1572202-panelizer-panel-emptied-on-second-save_1.patch

projects[fieldable_panels_panes][version] = 1.2
projects[fieldable_panels_panes][subdir] = contrib
projects[fieldable_panels_panes][patch][1536944] = http://drupal.org/files/Fieldable_Panels_Pane-translatable_panes-1536944-11.patch

projects[pm_existing_pages][version] = 1.4
projects[pm_existing_pages][subdir] = contrib

projects[fape][version] = 1.x-dev
projects[fape][subdir] = contrib
projects[fape][download][type] = git
projects[fape][download][revision] = 1143ee2
projects[fape][download][branch] = 7.x-1.x

; Views Magic

projects[views][version] = 3.5
projects[views][subdir] = contrib

projects[views_autocomplete_filters][version] = 1.0-beta1
projects[views_autocomplete_filters][subdir] = contrib

projects[views_bulk_operations][version] = 3.0
projects[views_bulk_operations][subdir] = contrib


; The Usual Suspects

projects[pathauto][version] = 1.2
projects[pathauto][subdir] = contrib
projects[pathauto][patch][936222] = http://drupal.org/files/936222-pathauto-persist.patch

projects[token][version] = 1.3
projects[token][subdir] = contrib

projects[entity][version] = 1.0-rc3
projects[entity][subdir] = contrib

projects[libraries][version] = 2.0
projects[libraries][subdir] = contrib

projects[devel][version] = 1.3
projects[devel][subdir] = contrib

; Harness the Power of Features and Apps with Default Content

projects[apps][version] = 1.0-beta7
projects[apps][subdir] = contrib
projects[apps][patch][1790902] = http://drupal.org/files/1790902-check-last-modified-existing.patch

projects[features][version] = 1.0
projects[features][subdir] = contrib

projects[strongarm][version] = 2.0
projects[strongarm][subdir] = contrib

projects[defaultcontent][version] = 1.x-dev
projects[defaultcontent][subdir] = contrib
projects[defaultcontent][download][type] = git
projects[defaultcontent][download][revision] = d8806d8
projects[defaultcontent][download][branch] = 7.x-1.x

projects[uuid][version] = 1.x-dev
projects[uuid][subdir] = contrib
projects[uuid][download][type] = git
projects[uuid][download][revision] = 806c301
projects[uuid][download][branch] = 7.x-1.x
