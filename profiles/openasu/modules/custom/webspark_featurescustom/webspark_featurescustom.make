; Any .make requests for the submodules in webspark_featurescustom need to go here (Drush make only 
; checks for .make files in EXPLICITLY LISTED projects and does not parse submodules in subdirectories).

api = 2
core = 7.x

; Webspark News & Events

; Add Email module

projects[email][version] = 1.3
projects[email][subdir] = contrib
projects[email][type] = module

; Webspark Megamenu

projects[special_menu_items][version] = 2.0
projects[special_menu_items][subdir] = contrib
projects[special_menu_items][type] = module

