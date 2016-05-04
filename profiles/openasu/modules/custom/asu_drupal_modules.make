; Master make file for Webspark drush make process
; All of the modules' .make files contents have been copied into this file because Drush make won't 
; traverse subdirectories of a module for .make files.

; ASU Degrees Make file contents

api = 2
core = 7.x

projects[views_bootstrap][version] = 3.1
projects[views_bootstrap][type] = module
projects[views_bootstrap][subdir] = contrib
projects[views_bootstrap][sha256] = bf9254d2b2af04c78bd3ee534932c04e6890e4d96dbf14efe559cf8a7345b201

; ASU RFI make file contents

; Upload multidev and patch it

projects[multiblock][version] = 1.2
projects[multiblock][type] = module
projects[multiblock][subdir] = contrib
projects[multiblock][sha256] = 9db947519ce58b901a13e236fa2ce97d55cd6603e73ab2fcd29bcb1b99bb3639

; Added RFI dependencies here, vs. in openasu.make

projects[views_data_export][version] = 3.0-beta9
projects[views_data_export][type] = module
projects[views_data_export][subdir] = contrib
projects[views_data_export][sha256] = 004aab9b208fd8d4be8ac831e1c947d60b79233a37a785ef36f2991e450d81e3

projects[honeypot][version] = 1.22
projects[honeypot][type] = module
projects[honeypot][subdir] = contrib
projects[honeypot][sha256] = 21c220ac6ee9b38b6c8f4c05f4e860361f626aee44a4b6ab29dfa190f9b504b6

; pre-req for mimemail
projects[mailsystem][version] = 2.34
projects[mailsystem][type] = module
projects[mailsystem][subdir] = contrib
projects[mailsystem][sha256] = 436c3421612d64f00ca3d1b9ba96f74d82a2c50e109bef8cd0c32aa8c92157d7

projects[mimemail][version] = 1.0-beta4
projects[mimemail][type] = module
projects[mimemail][subdir] = contrib
projects[mimemail][sha256] = 28365ac72206125bc41c42b35832906d06bbdbb15ffb0433915eff013f2f111e

