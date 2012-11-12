; Panopoly Core Makefile

api = 2
core = 7.x

; Panels and Chaos Tools Magic

projects[ctools][version] = 1.x-dev
projects[ctools][subdir] = contrib
projects[ctools][download][type] = git
projects[ctools][download][revision] = d6157d1
projects[ctools][download][branch] = 7.x-1.x
projects[ctools][patch][1822472] = http://drupal.org/files/1822472-exclude-all.patch

projects[panels][version] = 3.x-dev
projects[panels][subdir] = contrib
projects[panels][download][type] = git
projects[panels][download][revision] = 4e636d7
projects[panels][download][branch] = 7.x-3.x
projects[panels][patch][1069744] = http://drupal.org/files/1069744-ipe-inaccessible-pane-placeholders.patch
projects[panels][patch][1828684] = http://drupal.org/files/1828684-layout-fix-6.patch

projects[panels_breadcrumbs][version] = 2.x-dev
projects[panels_breadcrumbs][subdir] = contrib
projects[panels_breadcrumbs][download][type] = git
projects[panels_breadcrumbs][download][revision] = b79f3a8
projects[panels_breadcrumbs][download][branch] = 7.x-2.x
projects[panels_breadcrumbs][patch][1655296] = http://drupal.org/files/1655296-panels_breadcrumbs-panelizer-36.patch

projects[panelizer][version] = 3.x-dev
projects[panelizer][subdir] = contrib
projects[panelizer][download][type] = git
projects[panelizer][download][revision] = b783c23
projects[panelizer][download][branch] = 7.x-3.x
projects[panelizer][patch][1824566] = http://drupal.org/files/1824566-allow-panelizer-bundles-to-use-default-5.patch
projects[panelizer][patch][1772844] = http://drupal.org/files/1772844-reject-ipe-without-edit-permission.patch
projects[panelizer][patch][1655296] = http://drupal.org/files/1655296-panelizer-allow-breadcrumb-tabs-40.patch

projects[fieldable_panels_panes][version] = 1.2
projects[fieldable_panels_panes][subdir] = contrib
projects[fieldable_panels_panes][patch][1536944] = http://drupal.org/files/Fieldable_Panels_Pane-translatable_panes-1536944-11.patch
projects[fieldable_panels_panes][patch][1818132] = http://drupal.org/files/1818132-prevent-uuids.patch

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

projects[token][version] = 1.4
projects[token][subdir] = contrib

projects[entity][version] = 1.0-rc3
projects[entity][subdir] = contrib
projects[entity][patch][1514764] = http://drupal.org/files/1514764-fix_entity_conditions-20.patch

projects[libraries][version] = 2.0
projects[libraries][subdir] = contrib

; Field modules

projects[date][version] = 2.6
projects[date][subdir] = contrib

projects[entityreference][version] = 1.0-rc5
projects[entityreference][subdir] = contrib

projects[field_group][version] = 1.1
projects[field_group][subdir] = contrib

projects[link][version] = 1.0
projects[link][subdir] = contrib

; Harness the Power of Features and Apps with Default Content

projects[apps][version] = 1.0-beta7
projects[apps][subdir] = contrib
projects[apps][patch][1790902] = http://drupal.org/files/1790902-check-last-modified-existing.patch

projects[features][version] = 2.0-beta1
projects[features][subdir] = contrib

projects[strongarm][version] = 2.0
projects[strongarm][subdir] = contrib

projects[defaultconfig][version] = 1.0-alpha9
projects[defaultconfig][subdir] = contrib

projects[defaultcontent][version] = 1.x-dev
projects[defaultcontent][subdir] = contrib
projects[defaultcontent][download][type] = git
projects[defaultcontent][download][revision] = d8806d8
projects[defaultcontent][download][branch] = 7.x-1.x
projects[defaultcontent][patch][1754428] = http://drupal.org/files/1754428-allow-node-export-alter.patch
