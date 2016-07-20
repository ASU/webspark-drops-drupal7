api = 2
core = 7.x

; Drupal Core

projects[drupal][type] = core
projects[drupal][version] = 7.44
; Drupal Core Patches
projects[drupal][patch][1334818] = https://drupal.org/files/issues/D7-install-profile-ajax-1334818-8.patch

; The Panopoly Foundation

projects[panopoly_core][version] = 1.37
projects[panopoly_core][subdir] = panopoly
projects[panopoly_core][sha256] = 9e5a24b3c4800a99e0cef84751039558a3508f996e86b032615093b100fe451a

projects[panopoly_images][version] = 1.37
projects[panopoly_images][subdir] = panopoly
projects[panopoly_images][sha256] = 21ccee7dcf8a866c495ea7f967743aa413068478e4577f7a98966229e6634b8a

projects[panopoly_theme][version] = 1.37
projects[panopoly_theme][subdir] = panopoly
projects[panopoly_theme][sha256] = 77258bc19624b4d187884662a48afe31275d79c7e59733ae0c0b31edb472135f

projects[panopoly_magic][version] = 1.37
projects[panopoly_magic][subdir] = panopoly
projects[panopoly_magic][sha256] = 2e29a65cb312eca0f136e775e47b279c49608fa983b7f76ef68d8ac15a14bfb3

projects[panopoly_widgets][version] = 1.37
projects[panopoly_widgets][subdir] = panopoly
projects[panopoly_widgets][sha256] = 65a4df70e66c8fecd1cf07c2ca144bedc06bac8cfbe2edc15adf4074096e6bd7

projects[panopoly_admin][version] = 1.37
projects[panopoly_admin][subdir] = panopoly
projects[panopoly_admin][sha256] = 7a77529589d56afe51a3bb52768a7ac7a2e46cca774bbb7bd77d78daea61c982

projects[panopoly_users][version] = 1.37
projects[panopoly_users][subdir] = panopoly
projects[panopoly_users][sha256] = 2d102a7dd28dc2287183c3b50d2bcf34c94061ec380ffe03045fbc5967e0ad6f

; The Panopoly Toolset

projects[panopoly_pages][version] = 1.37
projects[panopoly_pages][subdir] = panopoly
projects[panopoly_pages][sha256] = f816ea71bc4329c3dab117e408c27b3777fdf0e9019f5392964ddebf1cf71da1

projects[panopoly_wysiwyg][version] = 1.37
projects[panopoly_wysiwyg][subdir] = panopoly
projects[panopoly_wysiwyg][sha256] = b83aaf62f1639516ba1d34f82b754558fd01071a71353cdb28ff24c34b139048

projects[panopoly_search][version] = 1.37
projects[panopoly_search][subdir] = panopoly
projects[panopoly_search][sha256] = 09be3a5e4e4e414253778e9db02ff8448aa53df06a671a20ead236bc116b45a7
; Fixes DB update dependency ordering
projects[panopoly_search][patch][2766677] = patches/panopoly-search-update-dependency-2766677-1.patch

projects[panopoly_test][version] = 1.37
projects[panopoly_test][subdir] = panopoly
projects[panopoly_test][sha256] = 7386762411d29bd9dbdade26fcd6f8c11ced6e98da483745555cdf6f716edd72
; @TODO - Add patches for custom Webspark testing
projects[panopoly_test][patch][137] = patches/webspark-847_panopoly-test-137-update.patch
projects[panopoly_test][patch][1372] = patches/webspark-847_panopoly-test-updates-3.patch

; ASU Custom, Webspark-agnostic modules
; Webspark-only modules kept in webspark_featurescustom

projects[asu_drupal_modules][type] = module
projects[asu_drupal_modules][directory_name] = custom
projects[asu_drupal_modules][download][revision] = 2fcb4275
projects[asu_drupal_modules][download][url] = https://github.com/ASU/asu-drupal-modules.git

; ASU Module Prerequisites

projects[references][version] = 2.1
projects[references][type] = module
projects[references][subdir] = contrib
projects[references][sha256] = 09727f5be7678afa11666a91d97861abc6086def19dd8695459ae5af7b5290a4


projects[ldap][version] = 2.0-beta8
projects[ldap][type] = module
projects[ldap][subdir] = contrib
projects[ldap][sha256] = 7a2ce4daff952ae42b7ac456f44629caca1208789497bac4c4b443e0041f05da
;; patch - see https://drupal.org/node/2182413, comment #10 - remove upon ldap update beyond beta8
projects[ldap][patch][2182413] = http://cgit.drupalcode.org/ldap/patch/?id=fe3a3d56ffebc9bd551c6d83a03172fae13517c3

; @TODO v2.2
projects[better_watchdog_ui][version] = 2.0
projects[better_watchdog_ui][type] = module
projects[better_watchdog_ui][subdir] = contrib
projects[better_watchdog_ui][sha256] = f4b5a0f18c752cc1be7823d556a3acf8a7648fbc19ff7506ba2c059c2f96b659

projects[cas_attributes][version] = 1.0-rc3
projects[cas_attributes][type] = module
projects[cas_attributes][subdir] = contrib
projects[cas_attributes][sha256] = c314facf2fbf391e01aa5455209325efbbc5a92fcb51923712152f7bf4435643

projects[email][version] = 1.3
projects[email][subdir] = contrib
projects[email][type] = module
projects[email][sha256] = 710d315a867fea0b2da69f9928818e93089d8cc5557d03c0dc38e3f16af0bf96
;; end will be removed

; @TODO v2.0-beta2
projects[feeds][version] = 2.0-alpha9
projects[feeds][type] = module
projects[feeds][subdir] = contrib
projects[feeds][sha256] = 3ecd9c52f42d12309645447697c2b058aca10a9bf788842e78727a64058a39ef

projects[feeds_xpathparser][version] = 1.1
projects[feeds_xpathparser][type] = module
projects[feeds_xpathparser][subdir] = contrib
projects[feeds_xpathparser][sha256] = c7958db5f0fec2e899628bebfb2b2e54262ccae97dd6d4b20fc8a2b3e51ee030

projects[job_scheduler][version] = 2.0-alpha3
projects[job_scheduler][type] = module
projects[job_scheduler][subdir] = contrib
projects[job_scheduler][sha256] = b3c8c35ca8add76904d9e0ef11058dc9433751fa1836773cee15dfe0270b304f

projects[viewfield][version] = 2.0
projects[viewfield][type] = module
projects[viewfield][subdir] = contrib
projects[viewfield][sha256] = 687c6c70f36df615f290c007f63c768f01c7075e94b06941ebe8f951eb0a0997

; @TODO v1.0-alpha3
projects[views_php][version] = 1.x-dev
projects[views_php][type] = module
projects[views_php][subdir] = contrib
projects[views_php][sha256] = 3b74733b2a42fe9c1a61a1b47f0e0f0104db05c0a3240420fe342885abe03cc6

projects[webform][version] = 4.12
projects[webform][type] = module
projects[webform][subdir] = contrib
projects[webform][sha256] = 853d7d9804a2c4cb0f4bceec845662cda6a60e074906d2f2c194efb1d304b329

; ASU Module prerequisites - Webspark Webstandards Components - contrib

projects[backgroundfield][version] = 1.5
projects[backgroundfield][type] = module
projects[backgroundfield][subdir] = contrib
projects[backgroundfield][sha256] = 25c86aedfeb90d8e4a63aaee4f762415757a9d6ac2749466f3134e9b60d98261
;; WEBSPARK-481 - BackgroundField image patch - default_image error
projects[backgroundfield][patch][1841978] = https://www.drupal.org/files/backgroundfield_undefined_index-1841978-18.patch

; @TODO v1.5
;; CAS SSO Integration - pulled in from old asu_cas.make file
projects[cas][version] = 1.4
projects[cas][subdir] = contrib
projects[cas][sha256] = f5eb676042cd43f420e3600831afdfb88b2694656dade8adfdfdc9a57bff0a18

; @TODO v.2.0-beta5
projects[chosen][version] = 2.0-beta4
projects[chosen][type] = module
projects[chosen][subdir] = contrib
projects[chosen][sha256] = b64aeec340d21a1e2c9beb501b1cddc392c656a1c95d26c155b1541324d0c3b2


projects[easy_breadcrumb][version] = 2.12
projects[easy_breadcrumb][type] = module
projects[easy_breadcrumb][subdir] = contrib
projects[easy_breadcrumb][sha256] = 50b869f514a58a7a2c9b2381528c1f4ec9ae8ab7d69eba0a99c1cd7418bd6524

projects[entity_view_mode][version] = 1.0-rc1
projects[entity_view_mode][type] = module
projects[entity_view_mode][subdir] = contrib
projects[entity_view_mode][sha256] = 18152ce088b930c5c46ba4ec3a422124f8fce6960b58ca32998d1b2ec43a3b06

; @TODO v2.0-rc1
projects[flexslider][version] = 2.0-alpha3
projects[flexslider][type] = module
projects[flexslider][subdir] = contrib
projects[flexslider][sha256] = 2c5a625067986ef3357234567c011022498f0c890a1a941de8e4ea30ba03c059

; @TODO v1.1 (or v2.5)
projects[fontawesome][version] = 1.0
projects[fontawesome][type] = module
projects[fontawesome][subdir] = contrib
projects[fontawesome][sha256] = daca43cab8a7b6f225be12415cdc1597bc55bc967be76ca923dc411454f3dda9

; @TODO v1.14
projects[google_appliance][version] = 1.12
projects[google_appliance][type] = module
projects[google_appliance][subdir] = contrib
projects[google_appliance][sha256] = 26d9885a8c32955ceac85ad22c957244dd5fcaf5b7cd1db661f9411b76bbe484

projects[maxlength][version] = 3.2-beta2
projects[maxlength][type] = module
projects[maxlength][subdir] = contrib
projects[maxlength][sha256] = 608b8cde956e42b4ad61622a3a9b3e66dd3ca03139d9f367141d91102c898247

projects[panels_tabs][version] = 2.x-dev
projects[panels_tabs][type] = module
projects[panels_tabs][subdir] = contrib
projects[panels_tabs][sha256] = 6e0ebf00a54e146b273a858d7ecd0c9592e3fbdca324d111e2ffd8f77b58c911

;; Going to Git repo for dev commit of quicktabs
projects[quicktabs][type] = module
projects[quicktabs][subdir] = contrib
projects[quicktabs][download][type] = "git"
projects[quicktabs][download][branch] = "7.x-3.x"
projects[quicktabs][download][url] = "http://git.drupal.org/project/quicktabs.git"
projects[quicktabs][download][revision] = "758de4cc4995149a2de1d566b4209ec343581d27"

;; Webspark Megamenu
projects[special_menu_items][version] = 2.0
projects[special_menu_items][subdir] = contrib
projects[special_menu_items][type] = module
projects[special_menu_items][sha256] = d4ed8827d78df86b0660f8f1ca4010d917448f9a22da90108ea47d6d8ef694e6

; @TODO v1.0-rc2
projects[tb_megamenu][version] = 1.0-beta5
projects[tb_megamenu][type] = module
projects[tb_megamenu][subdir] = contrib
projects[tb_megamenu][sha256] = 1b8266bd007f3f048c6923eb10b6c8e6c6ca99369cdacefb8a83f86c19573a17
; PATCH the CSS for tb_megamenu
;projects[tb_megamenu][patch][] = https://www.drupal.org/files/issues/webspark_megamenu-fixing_breakpoints.patch
projects[tb_megamenu][patch][] = patches/nojira-webspark-megamenu_fixing-breakpoints.patch

;projects[uuid_features][version] = 1.0-alpha4
;; grabbing alpha-4+dev-37 commit
projects[uuid_features][type] = module
projects[uuid_features][subdir] = contrib
projects[uuid_features][download][type] = "git"
projects[uuid_features][download][branch] = "7.x-1.x"
projects[uuid_features][download][url] = "http://git.drupal.org/project/uuid_features.git"
projects[uuid_features][download][revision] = "55a2d5070b6f238f40372070f70314cc4f8197d8"

projects[video_embed_field][version] = 2.0-beta11
projects[video_embed_field][type] = module
projects[video_embed_field][subdir] = contrib
projects[video_embed_field][sha256] = 4c5c4a3a2b067c100ca8a69fa8f4ece4ecc07382098b79c6527b9fcaedadb952

; @TODO v2.12
projects[wysiwyg_template][version] = 2.11
projects[wysiwyg_template][type] = module
projects[wysiwyg_template][subdir] = contrib
projects[wysiwyg_template][sha256] = b18438cee558bf6a340878e13b7a3d68e75ed7f5a1e3e255ed3d82a3de3e7751

; Bootstrap and Theme Frameworks - Moved to Webspark repo (see WEBSPARK-366)

;; Base Theme - Kalatheme

; @TODO v3.2
projects[kalatheme][version] = 3.0-rc2
projects[kalatheme][type] = theme
projects[kalatheme][sha256] = 4611e63d74330edb63578735e4b5ac5d2f8e221a943c4522a96ed1eed35c4cc8
;; WEBSPARK-188 - CSS img url fix
projects[kalatheme][patch][] = patches/webspark-188.kalatheme-css-img-urls.patch
;; WEBSPARK-361 - Panopoly TPLs and row-full class
projects[kalatheme][patch][] = patches/webspark-361-kalatheme-panopoly-tpl-class-update.patch
;; WEBSPARK-565 - Added views-view-table.tpl.php, pending update to kalatheme
projects[kalatheme][patch][] = patches/webspark-565-add-views-tpl-to-kalatheme.patch
;; rjbonnel Github patches for spelling (remove when fixed in kalatheme update upstream)
projects[kalatheme][patch][] = patches/nojira-20150812-kalatheme-spelling-fix.patch
projects[kalatheme][patch][] = patches/nojira-20150812-kalatheme-admin-spelling-fix.patch
projects[kalatheme][patch][] = patches/nojira-20160715-kalatheme_fix-missing-index.patch

projects[modernizr][version] = 3.1
projects[modernizr][subdir] = contrib
projects[modernizr][sha256] = e256ae811b875b954d9b4a79a1ab02db796f6e5a37feb7e8e3dcf4b81d15447c

; ASU Module prerequisites - Webstandards additions - Libraries

libraries[ajax_solr][download][type] = get
libraries[ajax_solr][download][url] = https://github.com/evolvingweb/ajax-solr/archive/master.zip
libraries[ajax_solr][directory_name] = ajax_solr
libraries[ajax_solr][destination] = libraries
libraries[ajax_solr][sha256] = dbc2da964c94b939b80a2688bff6af90e66f8f08672cb66e5e1286019f8e8b40

; CAS - Get only source + root PHP from Github
; 1 of 2
libraries[CAS][download][type] = get
libraries[CAS][download][url] = https://github.com/Jasig/phpCAS/archive/1.3.4.zip
libraries[CAS][download][subtree] = phpCAS-1.3.4/source
libraries[CAS][directory_name] = CAS/source
libraries[CAS][download][sha256] = c8c73945c3503991d19e2a1f7f14b51c293dd2ed9ebae974450a85da03ca3eee
; 2 of 2
libraries[CAS_2][download][type] = file
libraries[CAS_2][download][url] = https://raw.githubusercontent.com/Jasig/phpCAS/1.3.4/CAS.php
libraries[CAS_2][directory_name] = CAS
libraries[CAS_2][sha256] = 74a3eeed33e84d927884a2cf01ab10c33cc445e891c6d773996ffb19cf841d23

libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries
libraries[chosen][sha256] = 410147ddfb08f9a87f0272516fff7cd5ed5a4f0777c76f1b298d1106aa8405bd

libraries[flexslider][download][type] = get
libraries[flexslider][download][url] = https://github.com/woothemes/FlexSlider/archive/version/2.2.2.zip
libraries[flexslider][sha256] = bd72421a8aa6f4b9cd3575f4eb58651f2b43c5dc00f0f8f80a373f71b5d1efcc

; 1 of 2
libraries[fontawesome_css][download][type] = get
libraries[fontawesome_css][download][url] = https://github.com/FortAwesome/Font-Awesome/archive/v4.6.3.zip
libraries[fontawesome_css][download][subtree] = Font-Awesome-4.6.3/css
libraries[fontawesome_css][directory_name] = fontawesome/css
libraries[fontawesome_css][sha256] = dfae6770e811947487a22e731900f4cb478f69f0f4675bf8fc563885cf86c32e
; 2 of 2
libraries[fontawesome_fonts][download][type] = get
libraries[fontawesome_fonts][download][url] = https://github.com/FortAwesome/Font-Awesome/archive/v4.6.3.zip
libraries[fontawesome_fonts][download][subtree] = Font-Awesome-4.6.3/fonts
libraries[fontawesome_fonts][directory_name] = fontawesome/fonts

libraries[modernizr][download][type] = get
libraries[modernizr][download][url] = https://github.com/Modernizr/Modernizr/archive/v2.6.2.zip
libraries[modernizr][sha256] = 1fad7bf4340ddd915a6eb27eb056dfa1c4a51889db727e7ada76f57d86454998

libraries[jqtree][download][type] = get
libraries[jqtree][download][url] = https://github.com/mbraak/jqTree/archive/0.22.0.zip
libraries[jqtree][directory_name] = jqtree
libraries[jqtree][destination] = libraries
libraries[jqtree][sha256] = 1a52b655f49e0c0778e0776d7d7f2afc2aa37a26ce9be110d7bc31b6e274d67d

; PANOPOLY PROJECT PATCHES
;; These projects are installed first, before any other projects in the parent makefile.

includes[panopoly_patches] = openasu_panopoly_patches.make
