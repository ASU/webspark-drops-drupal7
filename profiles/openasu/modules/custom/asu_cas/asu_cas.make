; ASO CAS Makefile

api = 2
core = 7.x

; CAS SSO Integration and Libraries

projects[cas][version] = 1.2
projects[cas][subdir] = contrib

libraries[CAS][download][type] = get
libraries[CAS][download][url] = https://github.com/Jasig/phpCAS/archive/1.3.2.zip