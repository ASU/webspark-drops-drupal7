; ASU RFI makefile

api = 2
core = 7.x

; Upload multidev and patch it

projects[multiblock][version] = 1.6
projects[multiblock][type] = module
projects[multiblock][subdir] = contrib
;projects[multiblock][patch][2185235] = https://www.drupal.org/files/issues/multiblock_cache-2185235-5.patch
;projects[multiblock][patch][1370966] = https://www.drupal.org/files/fix_config_per_instance-1370966-5.patch
;projects[multiblock][patch][1704146] = https://www.drupal.org/files/strict-warning-1704146.patch

; Added RFI dependencies here, vs. in openasu.make

projects[views_data_export][version] = 3.0-beta8
projects[views_data_export][type] = module
projects[views_data_export][subdir] = contrib

projects[mimemail][version] = 1.0-beta3
projects[mimemail][type] = module
projects[mimemail][subdir] = contrib

projects[honeypot][version] = 1.17
projects[honeypot][type] = module
projects[honeypot][subdir] = contrib

; pre-req for mimemail
projects[mailsystem][version] = 2.34
projects[mailsystem][type] = module
projects[mailsystem][subdir] = contrib
