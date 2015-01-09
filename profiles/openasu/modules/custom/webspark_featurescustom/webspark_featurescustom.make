; Any .make requests for the submodules in webspark_featurescustom need to go here (Drush make only 
; checks for .make files in EXPLICITLY LISTED projects and does not parse submodules in subdirectories).

; Webspark News & Events

api = 2
core = 7.x

; Add Email module

projects[email][version] = 1.3
projects[email][subdir] = contrib
projects[email][type] = module
