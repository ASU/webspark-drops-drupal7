; Panopoly Search Makefile

api = 2
core = 7.x

; Search API and Facet API Modules

projects[facetapi][version] = 1.2
projects[facetapi][subdir] = contrib

projects[search_api][version] = 1.3
projects[search_api][subdir] = contrib
projects[search_api][patch][1698098] = http://drupal.org/files/search-api-disabled-index-configure-link.patch
projects[search_api][patch][1827272] = http://drupal.org/files/1827272-request-path-7.patch

projects[search_api_solr][version] = 1.0-rc2
projects[search_api_solr][subdir] = contrib
projects[search_api_solr][patch][1407282] = http://drupal.org/files/1407282-variable_solr_connection_class-33.patch

projects[search_api_db][version] = 1.0-beta4
projects[search_api_db][subdir] = contrib

; Solr PHP Client Library

libraries[SolrPhpClient][download][type] = get
libraries[SolrPhpClient][download][url] = http://solr-php-client.googlecode.com/files/SolrPhpClient.r60.2011-05-04.zip
